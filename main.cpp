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

void ImageAndProjectInClosedLoop(int *CCD2DLPLookUp, CamData* MyCamera);

void ImageAndProjectInClosedLoop(int *CCD2DLPLookUp, CamData* MyCamera) {
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

	unsigned char* fromCCD;
	unsigned char* forDLP;
	fromCCD = (unsigned char *) malloc(NSIZEX * NSIZEY * sizeof(unsigned char));
	forDLP = (unsigned char *) malloc(NSIZEX * NSIZEY * sizeof(unsigned char));
	printf("allocated memory for fromCCD and forDLP\n");
	//Set everything to zero.
	int count = 0;
	while (count < NSIZEX * NSIZEY * sizeof(char)) {
		fromCCD[count] = 0;
		forDLP[count] = 0;
		count = count + 1;
	}


	printf("set fromCCD and forDLP to zero\n");
	printf("Sending zeros to DLP\n");

	T2DLP_SendFrame(forDLP, myDLP);
	printf("Outside of T2DLP_SendFrame()\n");

	IplImage *frame;
	IplImage *toDLP;
	frame = cvCreateImage(cvSize(NSIZEX, NSIZEY), IPL_DEPTH_8U, 1);
	toDLP = cvCreateImage(cvSize(NSIZEX, NSIZEY), IPL_DEPTH_8U, 1);

	printf("ran cvCreateImage twice.\n");

	printf("entering giant loop\n");
	int numFramesRec = 0;
	while (1 == 1) {
		if (MyCamera->iFrameNumber > lastFrameSeenOutside) {
			printf("Fresh frame ready from camera.\n");
			lastFrameSeenOutside = MyCamera->iFrameNumber;
			//Create a local copy of the image;

			printf("Starting memcpy \n");
			memcpy(fromCCD, MyCamera->iImageData, NSIZEX * NSIZEY
					* sizeof(unsigned char));
			CopyCharArrayToIplImage(fromCCD, frame, NSIZEX, NSIZEY);
			printf("Copied camera image to fromCCD \n");
			cvShowImage("FromCamera", frame);
			cvWaitKey(10);
			printf("Displayed frame in window FromCamera\n");

			numFramesRec++;

			printf("Converting image from CCD to DLP...\n");
			ConvertCharArrayImageFromCam2DLP(CCD2DLPLookUp, fromCCD, forDLP,
					NSIZEX, NSIZEY, NSIZEX, NSIZEY, 0);

			printf("\n=============ONE FRAME Converted!");
			T2DLP_SendFrame((unsigned char *) forDLP, myDLP); // Send image to DLP
			printf("Sent frame to dLP\n");
			//display frame that we grabbed from camera
			CopyCharArrayToIplImage(forDLP, toDLP, NSIZEX, NSIZEY);
			printf("Copied CharArrayToIplImage\n");
			cvShowImage("ToDLP", toDLP);
			cvWaitKey(10);
			printf("Wait until key is hit...\n");

			if (kbhit()) break;
			printf("Frame number %d", numFramesRec);
			//	if (numFramesRec==300) break;
			printf("Done waiting.\n");
			//	printf("Displayed DLP image on screen");
			printf("*");
		} else {
			//	printf("_");
		}

	}
	printf("Freeing memory\n");
	free(fromCCD);
	free(forDLP);
	printf("Releasing Images\n");
	cvReleaseImage(&toDLP);
	cvReleaseImage(&frame);
	//	cvDestroyAllWindows();
	T2DLP_off(myDLP);
	printf("Exiting DoTheCameraDLPThing()");

}

int main() {
	/** Read In Calibration Data ***/
	CalibData* Calib;
	CreateCalibData(Calib,cvSize(NSIZEX,NSIZEY),cvSize(NSIZEX,NSIZEY));
	LoadCalibFromFile(Calib,"calib.dat");


	/** Turn on Camera **/
	T2Cam_InitializeLib();
	CamData *MyCamera;
	T2Cam_AllocateCamData(&MyCamera);
	T2Cam_ShowDeviceSelectionDialog(&MyCamera);


	/** Start Grabbing Frames and Update the Internal Frame Number iFrameNumber **/
	T2Cam_GrabFramesAsFastAsYouCan(&MyCamera);


	/** Actually Do Something **/
	ImageAndProjectInClosedLoop(Calib->CCD2DLPLookUp, MyCamera);

	/***** Turn off Camera & DLP ****/
	T2Cam_TurnOff(&MyCamera);
	T2Cam_CloseLib();

	DestroyCalibData(Calib);
	printf("Good bye.\n");
	return 0;
}

