/*
 * ~/workspace/OpticalMindControl/main.cpp
 * main.cpp
 *
 *  Created on: Jul 20, 2009
 *      Author: Andy
 */

//Standard C headers
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <math.h>

//C++ header
#include <iostream>
#include <limits>

using namespace std;

//OpenCV Headers
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>

//Andy's Personal Headers
#include "MyLibs/AndysOpenCVLib.h"
#include "MyLibs/Talk2Camera.h"
#include "MyLibs/Talk2DLP.h"
#include "MyLibs/Talk2Matlab.h"
#include "MyLibs/AndysComputations.h"
#include "MyLibs/TransformLib.h"
#include "MyLibs/WormAnalysis.h"
#include "MyLibs/WriteOutWorm.h"
#include "MyLibs/experiment.h"






int main (int argc, char** argv){
	/** Display output about the OpenCV setup currently installed **/
	DisplayOpenCVInstall();

	/** Create a new experiment object **/
	Experiment* exp=CreateExperimentStruct();

	/** Deal with CommandLineArguments **/
	LoadCommandLineArguments(exp,argc,argv);
	if (HandleCommandLineArguments(exp)==-1) return -1;


	for (int j = 0; j < _N_TIME_PTS; ++j) {
		total_time[j] = 0;
	}



	/** Read In Calibration Data ***/
	if (HandleCalibrationData(exp)<0) return -1;

	/** Start Camera **/
	RollCamera(exp);


	/** Prepare DLP ***/
	long myDLP= T2DLP_on();
	unsigned long lastFrameSeenOutside = 0;


	/*** Create IplImage **/
	IplImage* SubSampled=cvCreateImage(cvSize(NSIZEX/2,NSIZEY/2),IPL_DEPTH_8U,1);
	IplImage* HUDS=cvCreateImage(cvSize(NSIZEX,NSIZEY),IPL_DEPTH_8U,1); ;

	/*** Create Frames **/
	Frame* fromCCD =CreateFrame(cvSize(NSIZEX,NSIZEY));
	Frame* forDLP =CreateFrame(cvSize(NSIZEX,NSIZEY));
	Frame* IlluminationFrame=CreateFrame(cvSize(NSIZEX,NSIZEY));

	/** Create Worm Data Struct and Worm Parameter Struct **/
	WormAnalysisData* Worm=CreateWormAnalysisDataStruct();
	WormAnalysisParam* Params=CreateWormAnalysisParam();
	InitializeEmptyWormImages(Worm,cvSize(NSIZEX,NSIZEY));
	InitializeWormMemStorage(Worm);

	/** Setup Segmentation Gui **/
	SetupGUI(exp);

	/** Setup Previous Worm **/
	WormGeom* PrevWorm=CreateWormGeom();


	/** SetUp Data Recording **/
	printf("About to setup recording\n");
	WriteOut* DataWriter;
	char* DataFileName;
	if (exp->RECORDDATA)	{
		DataFileName=CreateFileName(argv[1],argv[2],".yaml");
		DataWriter=SetUpWriteToDisk(DataFileName,Worm->MemStorage);
		printf("Initialized data recording\n");
		DestroyFilename(&DataFileName);
	}

	/** Set Up Video Recording **/
	char* MovieFileName;
	char* HUDSFileName;
	CvVideoWriter* Vid;  //Video Writer
	CvVideoWriter* VidHUDS;
	if (exp->RECORDVID) {
		MovieFileName=CreateFileName(argv[1],argv[2],".avi");
		HUDSFileName=CreateFileName(argv[1],argv[2],"_HUDS.avi");
		Vid = cvCreateVideoWriter(MovieFileName, CV_FOURCC('M','J','P','G'), 30,
					cvSize(NSIZEX/2, NSIZEY/2), 0);
		VidHUDS=cvCreateVideoWriter(HUDSFileName, CV_FOURCC('M','J','P','G'), 30,
					cvSize(NSIZEX/2, NSIZEY/2), 0);
		DestroyFilename(&MovieFileName);
		DestroyFilename(&HUDSFileName);
		printf("Initialized video recording\n");
	}



	int e;

	/** initialize start time **/
	long prevTime=clock();
	int prevFrames=0;

	Worm->frameNum=0;
	int tnum = 0;
	int nframes = 0;
	while (1) {
		if (exp->MyCamera->iFrameNumber > lastFrameSeenOutside) {
			e=0;
			lastFrameSeenOutside = exp->MyCamera->iFrameNumber;
			Worm->frameNum++;

			/*** Print out Frame Rate ***/
			if ( (Worm->timestamp-prevTime) > CLOCKS_PER_SEC){
				printf("%d fps\n",Worm->frameNum-prevFrames);
				prevFrames=Worm->frameNum;
				prevTime=Worm->timestamp;
			}


			/*** Create a local copy of the image***/
			LoadFrameWithBin(exp->MyCamera->iImageData,fromCCD);


			/** Do we even bother doing analysis?**/
			if (Params->OnOff==0){
				/**Don't perform any analysis**/
				cvShowImage("Display", fromCCD->iplimg);
				cvWaitKey(10);
				continue;
			}

			clock_t now;
			clock_t last = clock();
			tnum = 0;
			++nframes;
			/** If the DLP is not displaying **/
			if (Params->DLPOn==0){
				/** Clear the DLP **/
				RefreshFrame(IlluminationFrame);
				T2DLP_SendFrame((unsigned char *) IlluminationFrame->binary, myDLP);
			}
			total_time[tnum++] += ((now = clock()) - last); //0
			last = now;


			/***********************
			 * Segment Frame
			 */

			/*** Load Frame into Worm **/
			if (!e) e=RefreshWormMemStorage(Worm);
			if (!e) e=LoadWormImg(Worm,fromCCD->iplimg);

			total_time[tnum++] += ((now = clock()) - last); //1
			last = now;

			/*** <------------ 31fps ***/

			/*** Find Worm Boundary ***/
			if (!e) FindWormBoundary(Worm,Params);

			total_time[tnum++] += ((now = clock()) - last); //2
			last = now;


			/*** Find Worm Head and Tail ***/
			if (!e) e=GivenBoundaryFindWormHeadTail(Worm,Params);
			/** If we are doing temporal analysis, improve the WormHeadTail estimate based on prev frame **/
			if (Params->TemporalOn && !e) PrevFrameImproveWormHeadTail(Worm,Params,PrevWorm);

			total_time[tnum++] += ((now = clock()) - last); //3
			last = now;



			/*** Segment the Worm ***/
			if (!e) e=SegmentWorm(Worm,Params);
			total_time[tnum++] += ((now = clock()) - last); //4
			last = now;


			/*** <------------ 31fps ***/


			/** Update PrevWorm Info **/
			if (!e) LoadWormGeom(PrevWorm,Worm);
			total_time[tnum++] += ((now = clock()) - last); //5
			last = now;


			/*** Do Some Illumination ***/

			if (!e) {
				if (Params->IllumFloodEverything) {
					SetFrame(IlluminationFrame,128); // Turn all of the pixels on
				} else {
					/** Otherwise Actually illuminate the  region of the worm your interested in **/
					SimpleIlluminateWormLR(Worm, IlluminationFrame, Params->IllumSegCenter, Params->IllumSegRadius, Params->IllumLRC);
				}
			}
			total_time[tnum++] += ((now = clock()) - last); //6
			last = now;

			/*** <------------ 31fps ***/
			if (!e) TransformFrameCam2DLP(IlluminationFrame,forDLP,exp->Calib);
			total_time[tnum++] += ((now = clock()) - last); //7
			last = now;


			/*** <------------ 26fps ***/



			if (!e && Params->DLPOn) T2DLP_SendFrame((unsigned char *) forDLP->binary, myDLP); // Send image to DLP
			total_time[tnum++] += ((now = clock()) - last); //8
			last = now;




			/*** DIsplay Some Monitoring Output ***/
			if (!e) CreateWormHUDS(HUDS,Worm,Params,IlluminationFrame);
				if (!e &&  EverySoOften(Worm->frameNum,Params->DispRate) ){
					/** There are no errors and we are displaying a frame **/
					switch (Params->Display) {
						case 0:
							 cvShowImage("Display", Worm->ImgOrig);
							break;
						case 1:
							cvShowImage("Display",HUDS);
							break;
						case 2:
							 cvShowImage("Display",Worm->ImgThresh);
							 break;
						case 3:
							 DisplayWormHeadTail(Worm,"Display");
							 break;
						case 4:
							DisplayWormSegmentation(Worm,"Display");
							break;
						case 5:
							cvShowImage("Display",IlluminationFrame->iplimg);
							break;
						case 6:
							cvShowImage("Display", forDLP->iplimg);
							break;
						default:
							break;
					}
					cvWaitKey(1); // Pause one millisecond for things to display onscreen.


					total_time[tnum++] += ((now = clock()) - last); //9
					last = now;

					/** Record VideoFrame to Disk**/
					if (exp->RECORDVID && Params->Record) {
						cvResize(Worm->ImgOrig,SubSampled,CV_INTER_LINEAR);
						cvWriteFrame(Vid,SubSampled);
						cvResize(HUDS,SubSampled,CV_INTER_LINEAR);
						cvWriteFrame(VidHUDS,SubSampled);
					}
					total_time[tnum++] += ((now = clock()) - last); //10
					last = now;

					/** Record data frame to diskl **/
					if (exp->RECORDDATA && Params->Record) AppendWormFrameToDisk(Worm,Params,DataWriter);
					total_time[tnum++] += ((now = clock()) - last); //11
					last = now;

				}



				if (!e){
					printf("*");
				} else {
					printf("\n:(\n");
				}
				total_time[tnum++] += ((now = clock()) - last); //12
			    last = now;

		}
		if (kbhit()) break;
		if (e) cvWaitKey(1); /**Wait so that we don't end up in a loop lockign up the UI in case of error**/

	}
	int nrecordedtime = tnum;
	for (int j = 0; j < nrecordedtime; ++j) {
		printf("time %d: total time %d\ttime per frame:%g\n", j, total_time[j], (1.0*total_time[j])/nframes);
	}
	/** Finish Writing Video to File and Release Writer **/
	cvReleaseImage(&SubSampled);
	if (exp->RECORDVID) {
		cvReleaseVideoWriter(&Vid);
		cvReleaseVideoWriter(&VidHUDS);
	}
	if (exp->RECORDDATA) FinishWriteToDisk(&DataWriter);

	/** Free Up Memory **/
	DestroyFrame(&fromCCD);
	DestroyFrame(&forDLP);
	DestroyWormGeom(&PrevWorm);

	//	cvDestroyAllWindows();
	T2DLP_off(myDLP);

	/***** Turn off Camera & DLP ****/
	T2Cam_TurnOff(&(exp->MyCamera));
	T2Cam_CloseLib();
	DestroyCalibData(exp->Calib);
	printf("\nGood bye.\n");
	return 0;
}

