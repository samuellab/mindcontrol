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
	cvNamedWindow("Original");
	cvNamedWindow("Boundary");
	cvNamedWindow( "Thresholded");
	cvNamedWindow( "Contours", 1);
	cvNamedWindow("Controls");
	cvResizeWindow("Controls",300,400);



	cvCreateTrackbar("Threshold", "Controls", &(Params->BinThresh),255, (int) NULL);
	cvCreateTrackbar("Gauss=x*2+1","Controls", &(Params->GaussSize),15,(int) NULL);
	cvCreateTrackbar("ScalePx","Controls", &(Params->LengthScale),50, (int) NULL);
	cvCreateTrackbar("TemporalIQ","Controls",&(Params->TemporalOn),1, (int) NULL);
	cvCreateTrackbar("Proximity","Controls",&(Params->MaxLocationChange),100, (int) NULL);
	return;

}





int main() {
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



	/*** SetUp Gui ***/
	cvNamedWindow("FromCamera", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("FromCamera", 200, 200);
	cvNamedWindow("ToDLP", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("TestOut", CV_WINDOW_AUTOSIZE);





	/** Prepare DLP ***/
	long myDLP= T2DLP_on();
	cvWaitKey(500);
	unsigned long lastFrameSeenOutside = 0;

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
	while (1 == 1) {
		if (MyCamera->iFrameNumber > lastFrameSeenOutside) {
			e=0;
			lastFrameSeenOutside = MyCamera->iFrameNumber;

			/*** Create a local copy of the image***/
				LoadFrameWithBin(MyCamera->iImageData,fromCCD);

				if (!e) cvShowImage("FromCamera", fromCCD->iplimg);
				cvWaitKey(1);


				/***********************
				 * Segment Frame
				 */

				/*** Load Frame into Worm **/
				if (!e) e=RefreshWormMemStorage(Worm);
				if (!e) e=LoadWormImg(Worm,fromCCD->iplimg);

				/*** Find Worm Boundary ***/
				if (!e) FindWormBoundary(Worm,Params);
				printf("Worm->Boundary->total=%d\n",Worm->Boundary->total);

				/*** Find Worm Head and Tail ***/
				if (!e) e=GivenBoundaryFindWormHeadTail(Worm,Params);
				/** If we are doing temporal analysis, improve the WormHeadTail estimate based on prev frame **/
				if (Params->TemporalOn && !e) PrevFrameImproveWormHeadTail(Worm,Params,PrevWorm);


				/*** Segment the Worm ***/
				if (!e) e=SegmentWorm(Worm,Params);

				/** Update PrevWorm Info **/
				if (!e) LoadWormGeom(PrevWorm,Worm);



				/*** DIsplay Some Monitoring Output ***/
				if (!e) cvShowImage("Original",Worm->ImgOrig);
				if (!e) cvShowImage("Thresholded",Worm->ImgThresh);
				if (!e) DisplayWormHeadTail(Worm,"Boundary");
				if (!e) DisplayWormSegmentation(Worm,"Contours");



				/*** Do Some Illumination ***/
				if (!e) SimpleIlluminateWorm(Worm,IlluminationFrame,20,30);
				if (!e) cvShowImage("TestOut",IlluminationFrame->iplimg);


				if (!e) TransformFrameCam2DLP(IlluminationFrame,forDLP,Calib);
				if (!e) T2DLP_SendFrame((unsigned char *) forDLP->binary, myDLP); // Send image to DLP
				if (!e) cvShowImage("ToDLP", forDLP->iplimg);
				cvWaitKey(1);
				if (!e){
					printf("*");
				} else {
					printf(":(\n");
				}

		}
		if (kbhit()) break;

	}

	DestroyFrame(&fromCCD);
	DestroyFrame(&forDLP);

	//	cvDestroyAllWindows();
	T2DLP_off(myDLP);

	/***** Turn off Camera & DLP ****/
	T2Cam_TurnOff(&MyCamera);
	T2Cam_CloseLib();

	DestroyCalibData(Calib);
	printf("Good bye.\n");
	return 0;
}

