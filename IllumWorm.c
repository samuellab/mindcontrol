/*
 * ~/workspace/OpticalMindControl/IllumWorm.c
 * IllumWorm.c
 *
 * IllumWorm.c is based on main.c
 * This is designed to work with the slow ImagingSource 30fps camera
 * Every time the camera captures a new image, the routines that were in SegmentFrame.c are
 * run to process the image, identify a picture of a worm and output another image to the DLP.
 *
 *
 *  Created on: 7 October 2009
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

#define PRINTOUT 0

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
	if (PRINTOUT) printf("allocated memory for fromCCD and forDLP\n");
	//Set everything to zero.
	int count = 0;
	while (count < NSIZEX * NSIZEY * sizeof(char)) {
		fromCCD[count] = 0;
		forDLP[count] = 0;
		count = count + 1;
	}


	if (PRINTOUT) printf("set fromCCD and forDLP to zero\n");
	if (PRINTOUT) printf("Sending zeros to DLP\n");

	T2DLP_SendFrame(forDLP, myDLP);
	if (PRINTOUT) printf("Outside of T2DLP_SendFrame()\n");

	IplImage *frame;
	IplImage *toDLP;
	frame = cvCreateImage(cvSize(NSIZEX, NSIZEY), IPL_DEPTH_8U, 1);
	toDLP = cvCreateImage(cvSize(NSIZEX, NSIZEY), IPL_DEPTH_8U, 1);

	if (PRINTOUT) printf("ran cvCreateImage twice.\n");

	if (PRINTOUT) printf("entering giant loop\n");
	int numFramesRec = 0;
	while (1 == 1) {
		if (MyCamera->iFrameNumber > lastFrameSeenOutside) {
			if (PRINTOUT) printf("Fresh frame ready from camera.\n");
			lastFrameSeenOutside = MyCamera->iFrameNumber;
			//Create a local copy of the image;

			if (PRINTOUT) printf("Starting memcpy \n");
			memcpy(fromCCD, MyCamera->iImageData, NSIZEX * NSIZEY
					* sizeof(unsigned char));

			/*
			 * Copy the Character array from the new camera into an IplImage
			 */
			CopyCharArrayToIplImage(fromCCD, frame, NSIZEX, NSIZEY);
			if (PRINTOUT) printf("Copied camera image to fromCCD \n");

			//Increment the number of frames recorded
			numFramesRec++;

//			cvShowImage("FromCamera", frame);
//			cvWaitKey(10);
//			if (PRINTOUT) printf("Displayed frame in window FromCamera\n");

			/*
			 *
			 * Right in here is where we want to Analyze Image
			 *
			 */

			if (PRINTOUT) printf("Converting image from CCD to DLP...\n");
			ConvertCharArrayImageFromCam2DLP(CCD2DLPLookUp, fromCCD, forDLP,
					NSIZEX, NSIZEY, NSIZEX, NSIZEY, 0);

			if (PRINTOUT) printf("\n=============ONE FRAME Converted!");
			T2DLP_SendFrame((unsigned char *) forDLP, myDLP); // Send image to DLP
			if (PRINTOUT) printf("Sent frame to dLP\n");
			//display frame that we grabbed from camera
			CopyCharArrayToIplImage(forDLP, toDLP, NSIZEX, NSIZEY);
			if (PRINTOUT) printf("Copied CharArrayToIplImage\n");
			cvShowImage("ToDLP", toDLP);
			cvWaitKey(10);
			if (PRINTOUT) printf("Wait until key is hit...\n");

			if (kbhit()) break;
			if (PRINTOUT) printf("Frame number %d", numFramesRec);
			//	if (numFramesRec==300) break;
			if (PRINTOUT) printf("Done waiting.\n");
			//	printf("Displayed DLP image on screen");
			printf("*");
		} else {
			//	printf("_");
		}

	}
	if (PRINTOUT) printf("Freeing memory\n");
	free(fromCCD);
	free(forDLP);
	if (PRINTOUT) printf("Releasing Images\n");
	cvReleaseImage(&toDLP);
	cvReleaseImage(&frame);
	//	cvDestroyAllWindows();
	T2DLP_off(myDLP);
	if (PRINTOUT) printf("Exiting DoTheCameraDLPThing()");

}

int main() {

	FILE *fp;
	int result;
	/*************** Read Calibration from File ****************/
	int *CCD2DLPLookUp;
	CCD2DLPLookUp = (int *) malloc(2 * NSIZEX * NSIZEY * sizeof(int));

	printf("Now trying to open again\n");
	if ((fp = fopen("calib.dat", "rb")) == NULL) {
		printf("Cannot open file.\n");
	}
	printf("opened..\n");
	result = 0;
	result = fread(CCD2DLPLookUp, sizeof(int) * 2 * NSIZEX * NSIZEY, 1, fp);
	if (result != 1) {
		printf("Read error!\n");
	} else
		printf("Read was successful.\n");

	printf("Trying to close calib.dat \n");
	fflush(stdout);
	fclose(fp);
	printf("close succeeded\n");
	fflush(stdout);

	/** Turn on Camera **/

	T2Cam_InitializeLib();
	CamData *MyCamera;
	T2Cam_AllocateCamData(&MyCamera);
	printf("Allocated Camera: %d\n", *MyCamera);
	T2Cam_ShowDeviceSelectionDialog(&MyCamera);
	printf("Set Camera Properties: %d\n", *MyCamera);
	//Tell the Camera To Start and to call the callback function
	//The Call back function will store the frame form the camera and update the iFrameNumber
	T2Cam_GrabFramesAsFastAsYouCan(&MyCamera);
	printf("Told Camera to Grab Frames as Quickly as Possible: %d\n", *MyCamera);
	printf("About to enter DoThecameraDLPThing() \n");

	ImageAndProjectInClosedLoop(CCD2DLPLookUp, MyCamera);

	/***** Turn off Camera & DLP ****/
	printf("Outside of DoTheCameraDLPThing About to turn off camera %d\n",
			*MyCamera);
	T2Cam_TurnOff(&MyCamera);
	printf("Turned off camera\n");
	T2Cam_CloseLib();
	return 0;

}

