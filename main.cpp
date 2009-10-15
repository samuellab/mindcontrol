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

void ImageAndProjectInClosedLoop(CalibData* Calib, CamData* MyCamera);

void ImageAndProjectInClosedLoop(CalibData* Calib, CamData* MyCamera) {
	int thresh;

	cvNamedWindow("FromCamera", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("FromCamera", 200, 200);
	cvNamedWindow("ToDLP", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("ProcessedImage", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("ProcessedImage",500,0);
//	cvCreateTrackbar("Threshold", "ProcessedImage", thresh, 255, NULL);

	cvWaitKey(500);
	//Prepare the DLP
	long myDLP;
	printf("Turning DLP on...");
	myDLP = T2DLP_on(); // Turn DLP On
	printf("DLP turned on.\n");
	unsigned long lastFrameSeenOutside = 0;

	Frame* fromCCD =CreateFrame(cvSize(NSIZEX,NSIZEY));
	Frame* forDLP =CreateFrame(cvSize(NSIZEX,NSIZEY));



	printf("entering giant loop\n");
	int numFramesRec = 0;
	while (1 == 1) {
		if (MyCamera->iFrameNumber > lastFrameSeenOutside) {
			printf("Fresh frame ready from camera.\n");
			lastFrameSeenOutside = MyCamera->iFrameNumber;
			//Create a local copy of the image;
			LoadFrameWithBin(MyCamera->iImageData,fromCCD);
			printf("LoadFrameWith Bin\n");
			cvShowImage("FromCamera", fromCCD->iplimg);
			cvWaitKey(1);
			numFramesRec++;
		//	ConvertCharArrayImageFromCam2DLP(CCD2DLPLookUp, fromCCD->binary, forDLP->binary,
			//		NSIZEX, NSIZEY, NSIZEX, NSIZEY, 0);
			TransformFrameCam2DLP(fromCCD,forDLP,Calib);
			printf("ConvertCharArayImageFromCam2DLP\n");
			T2DLP_SendFrame((unsigned char *) forDLP->binary, myDLP); // Send image to DLP
			printf("Sent frame to dLP\n");
			//display frame that we grabbed from camera
			CopyCharArrayToIplImage(forDLP->binary, forDLP->iplimg, NSIZEX, NSIZEY);
			printf("Copied CharArrayToIplImage\n");
			cvShowImage("ToDLP", forDLP->iplimg);
			cvWaitKey(1);
			printf("Wait until key is hit...\n");
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
	printf("Exiting DoTheCameraDLPThing()");

}

int main() {
	/** Read In Calibration Data ***/
	CalibData* Calib =CreateCalibData(cvSize(NSIZEX,NSIZEY),cvSize(NSIZEX,NSIZEY));
	int ret=LoadCalibFromFile(Calib,"calib.dat");
	if (ret!=0){
		printf("Error reading in calibration!! \n",ret);
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



	/** Actually Do Something **/
	ImageAndProjectInClosedLoop(Calib->CCD2DLPLookUp, MyCamera);

	/***** Turn off Camera & DLP ****/
	T2Cam_TurnOff(&MyCamera);
	T2Cam_CloseLib();

	DestroyCalibData(Calib);
	printf("Good bye.\n");
	return 0;
}

