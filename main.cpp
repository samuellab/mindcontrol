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


void SetupSegmentationGUI(){
	cvNamedWindow("Original");
	cvNamedWindow("Boundary");
	cvNamedWindow( "Thresholded");
	cvNamedWindow( "Contours", 1);
	cvNamedWindow("Controls");
	cvResizeWindow("Controls",300,400);



	cvCreateTrackbar("Threshold", "Controls", &(Params->BinThresh),255, on_trackbar);
	cvCreateTrackbar("Gauss=x*2+1","Controls", &(Params->GaussSize),5, on_trackbar);
	cvCreateTrackbar("ScalePx","Controls", &(Params->LengthScale),15,on_trackbar);
	cvCreateTrackbar("Offset Comp","Controls",&(Params->LengthOffset),15, on_trackbar);
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
	cvNamedWindow("ProcessedImage", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("ProcessedImage",500,0);




	/** Prepare DLP ***/

	long myDLP= T2DLP_on();
	cvWaitKey(500);
	unsigned long lastFrameSeenOutside = 0;

	/*** Create Frames **/
	Frame* fromCCD =CreateFrame(cvSize(NSIZEX,NSIZEY));
	Frame* forDLP =CreateFrame(cvSize(NSIZEX,NSIZEY));

	/** Create Worm Data Struct and Worm Parameter Struct **/
	WormAnalysisData* Worm=CreateWormAnalysisDataStruct();
	WormAnalysisParam* Params=CreateWormAnalysisParam();
	InitializeEmptyWormImages(Worm,cvSize(NSIZEX,NSIZEY));
	InitializeWormMemStorage(Worm);





	while (1 == 1) {
		if (MyCamera->iFrameNumber > lastFrameSeenOutside) {
			lastFrameSeenOutside = MyCamera->iFrameNumber;
			/*** Create a local copy of the image***/
			LoadFrameWithBin(MyCamera->iImageData,fromCCD);

			cvShowImage("FromCamera", fromCCD->iplimg);
			cvWaitKey(1);


			/*** Segment Frame***/



			TransformFrameCam2DLP(fromCCD,forDLP,Calib);
			T2DLP_SendFrame((unsigned char *) forDLP->binary, myDLP); // Send image to DLP
			cvShowImage("ToDLP", forDLP->iplimg);
			cvWaitKey(1);
			if (kbhit()) break;
			printf("*");
		} else {
			//	printf("_");
		}

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

