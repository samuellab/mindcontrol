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
#include <conio.h>
#include <math.h>

//C++ hearder
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


void SetupSegmentationGUI(WormAnalysisParamStruct* Params){

	cvNamedWindow("Display");
	cvNamedWindow("Controls");
	cvResizeWindow("Controls",300,700);


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
	cvCreateTrackbar("SegStart","Controls",&(Params->SegStart),100, (int) NULL);
	cvCreateTrackbar("SegEnd","Controls",&(Params->SegStop),100, (int) NULL);


	return;

}

int DispVid(int frameNum, int HowOften){
	if (frameNum==NULL || HowOften==NULL || frameNum<0 || HowOften<0) return 0;
	if (HowOften==0) return 0;
	if ((frameNum % HowOften)==0){
		return 1;
	}
	return 0;
}



int main (int argc, char** argv){
	int RECORDVID=0;
	if( argc > 2  ){
		printf("Runs the camera and DLP in closed loop. Specify an optional .avi file to write out.\n");
		return -1;
	}
	char* fileout;
	if (argc ==2 ){
		fileout=argv[1];
		RECORDVID=1;
	}



	DisplayOpenCVInstall();
	/** Read In Calibration Data ***/
	CalibData* Calib =CreateCalibData(cvSize(NSIZEX,NSIZEY),cvSize(NSIZEX,NSIZEY));
	int ret=LoadCalibFromFile(Calib,"calib.dat");
	if (ret!=0){
		printf("Error reading in calibration!! \n");
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
	cvWaitKey(500);
	unsigned long lastFrameSeenOutside = 0;

	/** Prepare Video Out **/
	CvVideoWriter* Vid;
	if (RECORDVID) Vid =cvCreateVideoWriter(fileout,CV_FOURCC('P','I','M','1'),30,cvSize(NSIZEX,NSIZEY),0);

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


	int e;
	int FramesReceived=0;
	while (1 == 1) {
		if (MyCamera->iFrameNumber > lastFrameSeenOutside) {
			e=0;
			lastFrameSeenOutside = MyCamera->iFrameNumber;
			FramesReceived++;
			/*** Create a local copy of the image***/
			LoadFrameWithBin(MyCamera->iImageData,fromCCD);

			if (Params->OnOff==0){
				/**Don't perform any analysis**/
				cvShowImage("Display", fromCCD->iplimg);
				printf("Analysis is off. Displaying camera.\n");
				cvWaitKey(10);
				continue;
			}


			/***********************
			 * Segment Frame
			 */

			/*** Load Frame into Worm **/
			if (!e) e=RefreshWormMemStorage(Worm);
			if (!e) e=LoadWormImg(Worm,fromCCD->iplimg);

			/*** Find Worm Boundary ***/
			if (!e) FindWormBoundary(Worm,Params);

			/*** Find Worm Head and Tail ***/
			if (!e) e=GivenBoundaryFindWormHeadTail(Worm,Params);
			/** If we are doing temporal analysis, improve the WormHeadTail estimate based on prev frame **/
			if (Params->TemporalOn && !e) PrevFrameImproveWormHeadTail(Worm,Params,PrevWorm);


			/*** Segment the Worm ***/
			if (!e) e=SegmentWorm(Worm,Params);

			/** Update PrevWorm Info **/
			if (!e) LoadWormGeom(PrevWorm,Worm);


			/*** Do Some Illumination ***/
			if (!e) SimpleIlluminateWorm(Worm,IlluminationFrame,Params->SegStart,Params->SegStop);



			if (!e) TransformFrameCam2DLP(IlluminationFrame,forDLP,Calib);
			if (!e) T2DLP_SendFrame((unsigned char *) forDLP->binary, myDLP); // Send image to DLP

			/*** DIsplay Some Monitoring Output ***/
				if (!e &&  DispVid(FramesReceived,Params->DispRate) ){
					/** There are no errors and we are displaying a frame **/
					switch (Params->Display) {
						case 1:
							 cvShowImage("Display", Worm->ImgOrig);
							 if (RECORDVID) cvWriteFrame(Vid,Worm->ImgOrig);
							break;
						case 2:
							 cvShowImage("Display",Worm->ImgThresh);
							 if (RECORDVID) cvWriteFrame(Vid,Worm->ImgThresh);
							 break;
						case 3:
							 DisplayWormHeadTail(Worm,"Display");
							 break;
						case 4:
							DisplayWormSegmentation(Worm,"Display");
							break;
						case 5:
							cvShowImage("Display",IlluminationFrame->iplimg);
							if (RECORDVID) cvWriteFrame(Vid,IlluminationFrame->iplimg);
							break;
						case 6:
							cvShowImage("Display", forDLP->iplimg);
							if (RECORDVID) cvWriteFrame(Vid,forDLP->iplimg);
							break;
						default:
							break;
					}
					cvWaitKey(1);

				}


				if (!e){
					printf("*");
				} else {
					printf(":(\n");
				}

		}
		if (kbhit()) break;
		if (e) cvWaitKey(1); /**Wait so that we don't end up in a loop lockign up the UI in case of error**/

	}

	/** Finish Writing Video to File and Release Writer **/
	if (RECORDVID) cvReleaseVideoWriter(&Vid);

	DestroyFrame(&fromCCD);
	DestroyFrame(&forDLP);
	DestroyWormGeom(&PrevWorm);

	//	cvDestroyAllWindows();
	T2DLP_off(myDLP);

	/***** Turn off Camera & DLP ****/
	T2Cam_TurnOff(&MyCamera);
	T2Cam_CloseLib();
	DestroyCalibData(Calib);
	printf("Good bye.\n");
	return 0;
}

