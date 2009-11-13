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


void SetupSegmentationGUI(WormAnalysisParamStruct* Params){

	cvNamedWindow("Display");
	cvNamedWindow("Controls");
	cvResizeWindow("Controls",450,700);


	/** SelectDispilay **/
	cvCreateTrackbar("SelDisplay", "Controls", &(Params->Display), 7, (int) NULL);


	/** On Off **/
	cvCreateTrackbar("On","Controls",&(Params->OnOff),1,(int) NULL);

	/** Temporal Coding **/
	cvCreateTrackbar("TemporalIQ","Controls",&(Params->TemporalOn),1, (int) NULL);

	/** Segmentation Parameters**/
	cvCreateTrackbar("Threshold", "Controls", &(Params->BinThresh),255, (int) NULL);
	cvCreateTrackbar("Gauss=x*2+1","Controls", &(Params->GaussSize),15,(int) NULL);
	cvCreateTrackbar("ScalePx","Controls", &(Params->LengthScale),50, (int) NULL);
	cvCreateTrackbar("Proximity","Controls",&(Params->MaxLocationChange),100, (int) NULL);


	/**Illumination Parameters **/
	cvCreateTrackbar("Center","Controls",&(Params->IllumSegCenter),100, (int) NULL);
	cvCreateTrackbar("Radius","Controls",&(Params->IllumSegRadius),100, (int) NULL);
	cvCreateTrackbar("LRC","Controls",&(Params->IllumLRC),3,(int) NULL);
	cvCreateTrackbar("DLPOn","Controls",&(Params->DLPOn),1,(int) NULL);

	/** Record Data **/
	cvCreateTrackbar("RecordOn","Controls",&(Params->Record),1,(int) NULL);

	return;

}
#define _N_TIME_PTS 100
static int total_time[_N_TIME_PTS];
static int _n_frames_run = 0;

int main (int argc, char** argv){
	int RECORDVID=0;
	int RECORDDATA=0;

	for (int j = 0; j < _N_TIME_PTS; ++j) {
		total_time[j] = 0;
	}

	/** Handle Variable Arguments **/
	if( argc !=1 && argc!=3 ){
		printf("Runs the camera and DLP in closed loop.\n");
		printf("Run without any arguments, or, to save data in a directory use the following usage:\n");
		printf("\tClosedLoop.exe D:/Data/MyDirectory/  basefilename\n\n");
		printf("IMPORTANT: Remember to include the trailing slash on the directory!");

		return -1;
	}

	if (argc ==3 ){ /** The user implicitly wants to record data **/
		RECORDVID=1;
		RECORDDATA=1;
	}


	DisplayOpenCVInstall();
	/** Read In Calibration Data ***/
	CalibData* Calib =CreateCalibData(cvSize(NSIZEX,NSIZEY),cvSize(NSIZEX,NSIZEY));
	int ret=LoadCalibFromFile(Calib,"calib.dat");
	if (ret!=0){
		printf("Error reading in calibrationfile!!\nPlease run CalibrateApparatus to generate calibration file calib.dat\nThank you.\nGoodbye.\n");
		return 0;
	}






	/** Turn on Camera **/
	T2Cam_InitializeLib();
	CamData *MyCamera;
	T2Cam_AllocateCamData(&MyCamera);
	T2Cam_ShowDeviceSelectionDialog(&MyCamera);


	/** Start Grabbing Frames and Update the Internal Frame Number iFrameNumber **/
	T2Cam_GrabFramesAsFastAsYouCan(&MyCamera);



	/** Prepare DLP ***/
	long myDLP= T2DLP_on();
	T2DLP_clear(myDLP);
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
	SetupSegmentationGUI(Params);

	/** Setup Previous Worm **/
	WormGeom* PrevWorm=CreateWormGeom();


	/** SetUp Dataa Recording **/
	printf("About to setup recording\n");
	WriteOut* DataWriter;
	char* DataFileName;
	if (RECORDDATA)	{
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
	if (RECORDVID) {
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
		if (MyCamera->iFrameNumber > lastFrameSeenOutside) {
			e=0;
			lastFrameSeenOutside = MyCamera->iFrameNumber;
			Worm->frameNum++;

			/*** Print out Frame Rate ***/
			if ( (Worm->timestamp-prevTime) > CLOCKS_PER_SEC){
				printf("%d fps\n",Worm->frameNum-prevFrames);
				prevFrames=Worm->frameNum;
				prevTime=Worm->timestamp;
			}


			/*** Create a local copy of the image***/
			LoadFrameWithBin(MyCamera->iImageData,fromCCD);


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

			if (!e) SimpleIlluminateWormLR(Worm, IlluminationFrame, Params->IllumSegCenter, Params->IllumSegRadius, Params->IllumLRC);
			total_time[tnum++] += ((now = clock()) - last); //6
			last = now;

			/*** <------------ 31fps ***/
			if (!e) TransformFrameCam2DLP(IlluminationFrame,forDLP,Calib);
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
					if (RECORDVID && Params->Record) {
						cvResize(Worm->ImgOrig,SubSampled,CV_INTER_LINEAR);
						cvWriteFrame(Vid,SubSampled);
						cvResize(HUDS,SubSampled,CV_INTER_LINEAR);
						cvWriteFrame(VidHUDS,SubSampled);
					}
					total_time[tnum++] += ((now = clock()) - last); //10
					last = now;

					/** Record data frame to diskl **/
					if (RECORDDATA && Params->Record) AppendWormFrameToDisk(Worm,Params,DataWriter);
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
	if (RECORDVID) {
		cvReleaseVideoWriter(&Vid);
		cvReleaseVideoWriter(&VidHUDS);
	}
	if (RECORDDATA) FinishWriteToDisk(&DataWriter);

	/** Free Up Memory **/
	DestroyFrame(&fromCCD);
	DestroyFrame(&forDLP);
	DestroyWormGeom(&PrevWorm);

	//	cvDestroyAllWindows();
	T2DLP_off(myDLP);

	/***** Turn off Camera & DLP ****/
	T2Cam_TurnOff(&MyCamera);
	T2Cam_CloseLib();
	DestroyCalibData(Calib);
	printf("\nGood bye.\n");
	return 0;
}

