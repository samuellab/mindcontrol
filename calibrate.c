/*
 * Copyright 2010 Andrew Leifer et al <leifer@fas.harvard.edu>
 * This file is part of MindControl.
 *
 * MindControl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU  General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MindControl s distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MindControl. If not, see <http://www.gnu.org/licenses/>.
 *
 * For the most up to date version of this software, see:
 * https://github.com/samuellab/mindcontrol
 *
 *
 *
 * NOTE: If you use any portion of this code in your research, kindly cite:
 * Leifer, A.M., Fang-Yen, C., Gershow, M., Alkema, M., and Samuel A. D.T.,
 * 	"Optogenetic manipulation of neural activity with high spatial resolution in
 *	freely moving Caenorhabditis elegans," Nature Methods, Submitted (2010).
 */


/*
 * calibrate.c
 *
 *  Created on: Aug 12, 2009
 *      Author: Andy
 */

/*
 * Note this is only valid for ImagingSource cameras. This has now been superseded
 * by the file calibrateFG.cpp
 *
 */

/*
 * This function is the part of the program that initializes the camera
 * Tells the camera to grab frames and then checks to see if new frames have arrived
 * When new frames arrive it sends them to the DLP.
 *
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


typedef struct {
	int inputradius;
	int gauss_radius;
	int rel_intensity_thresh;
} CircProp;


void CalibrationTest(int *CCD2DLPLookUp, CamData* MyCamera);

//int CalibrateAPoint(CvPoint PointOnDLP, CvSeq* CalibSeq, int numframes,
//		CircProp* MyCirc, CamData* MyCamera, long MyDLP);

/*
 * This function displays a circle on the DLP and images it with a camera for a number of frames specified by numframes.
 *
 * ANDY MORE DESCRIPTION HERE!
 *
 *
 */
int CalibrateAPoint(CvPoint PointOnDLP, CvSeq* CalibSeq, int numframes,
		CircProp* MyCirc, CamData* MyCamera, long myDLP) {
	int COUNTFLAG;
	if (numframes == NULL) {
		COUNTFLAG = 0; //Break on Escape
	} else {
		COUNTFLAG = 1; //Brake on Number of Frames
	}

	/*Create Windows*/
	cvNamedWindow("SentToDLP", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("SentToDLP", 0, 0);
	cvNamedWindow("FromCamera", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("FromeCamer", 500, 500);
	cvCreateTrackbar("InputRad", "FromCamera", &(MyCirc->inputradius), 10, NULL);
	cvCreateTrackbar("GaussRad", "FromCamera", &(MyCirc->gauss_radius), 30,
			NULL);
	cvCreateTrackbar("RelIntThresh", "FromCamera",
			&(MyCirc->rel_intensity_thresh), 10, NULL);

	//Declarem Images
	unsigned char *image2DLP;
	image2DLP
			= (unsigned char*) malloc(NSIZEX * NSIZEY * sizeof(unsigned char));

	IplImage *dlpImage;
	dlpImage = cvCreateImage(cvSize(NSIZEX, NSIZEY), IPL_DEPTH_8U, 1);

	char c;
	IplImage *frame;
	IplImage *tempframe;
	frame = cvCreateImage(cvSize(NSIZEX, NSIZEY), IPL_DEPTH_8U, 1);
	tempframe = cvCloneImage(frame);

	CvPoint MinPoint, MaxPoint;
	double minvalue, maxvalue;
	CvScalar mean;
	CvScalar stdev;

	long lastFrameSeenOutside = 0;
	long numberOfFramesReceived = 0;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* PtsForGivenCircle = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq),
			sizeof(CvPoint), storage);

	//Draw the Circle
	cvSetZero(dlpImage);
	cvCircle(dlpImage, PointOnDLP, MyCirc->inputradius + 1,
			CV_RGB(255,255,255), CV_FILLED, 8);

	//Send the Circle to DLP
	copyIplImageToCharArray(dlpImage, image2DLP);
	T2DLP_SendFrame((unsigned char *) image2DLP, myDLP);
	//cvWaitKey(10);

	//Display the Circle on the screen
	cvShowImage("SentToDLP", dlpImage);

	while (1) { //While the user hasn't hit escape, or while we are counting down a specified number of frames
		if (MyCamera->iFrameNumber > lastFrameSeenOutside) {
			lastFrameSeenOutside = MyCamera->iFrameNumber;
			numberOfFramesReceived++;

			//Convert the Camera Image to an IplImage
			CopyCharArrayToIplImage(MyCamera->iImageData, frame, NSIZEX, NSIZEY);

			// Smooth the image in preparation for finding its brightest point
			cvSmooth(frame, tempframe, CV_GAUSSIAN, (MyCirc->gauss_radius) * 2
					+ 1, (MyCirc->gauss_radius) * 2 + 1);

			//Find the pixel with the maximal intensity
			cvMinMaxLoc(tempframe, &minvalue, &maxvalue, &MinPoint, &MaxPoint,
					NULL);
			cvAvgSdv(tempframe, &mean, &stdev);

			printf("x: %d, y: %d,\t value: %d \t mean: %f, stdev: %f\n",
					MaxPoint.x, MaxPoint.y, (int) maxvalue, mean.val[0],
					stdev.val[0]);
			//Draw the square.
			SafeDrawSquare(&frame, &MaxPoint, 7);
			//Display the image
			cvShowImage("FromCamera", frame);

			/*If we are a significant number of standard deviations above the background than we
			 * should register the point we've detected as valid.
			 */

			if (maxvalue > ((MyCirc->rel_intensity_thresh) * stdev.val[0])
					+ mean.val[0]) {
				cvSeqPush(PtsForGivenCircle, &MaxPoint);
			} else {
				printf("Spot fails relative intensity threshold.\n");
			}

			//Keep looping until the user hits escape
			c = cvWaitKey(2);
			if (COUNTFLAG) {
				if (numberOfFramesReceived == numframes)

					break;
			} else {

				if (c == 27)
					break;
			}
		} cvWaitKey(1); //Wait while looping.

	}

	//SEt the DLP to zero.
	cvSetZero(dlpImage);
	copyIplImageToCharArray(dlpImage, image2DLP);
	T2DLP_SendFrame((unsigned char *) image2DLP, myDLP);

	// Now we  find the median.
	CvPoint medpt = GetMedianOfPoints(PtsForGivenCircle);
	PairOfPoints newpt;
	newpt.alpha = PointOnDLP;
	newpt.beta = medpt;
	//If the median is not -1, -1, AND if the number of valid points is greater than half of the expected number of points
	if ((newpt.beta.x != -1 && newpt.beta.y != -1) && PtsForGivenCircle->total
			> numframes / 2) {
		cvSeqPush(CalibSeq, &newpt);
	} else {
		printf("Tossing out the calibration of this point.\n");
	}

	printf("Median Found x: %d, y: %d\n", medpt.x, medpt.y);
	cvClearMemStorage(storage);// Clear the memory (its no longer needed.)
	free(image2DLP);
	cvReleaseImage(&dlpImage);
	cvReleaseImage(&frame);
	cvReleaseImage(&tempframe);
	cvDestroyAllWindows();
	return 0;

}

void CalibrationTest(int *CCD2DLPLookUp, CamData* MyCamera) {
	/*========== Set Up Camera ============*/
	cvNamedWindow("FromCamera", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("FromCamera", 200, 200);

	IplImage *frame;
	frame = cvCreateImage(cvSize(NSIZEX, NSIZEY), IPL_DEPTH_8U, 1);
	long lastFrameSeenOutside = 0;
	long numberOfFramesReceived = 0;
	printf("Align camera. Then Hit escape to continue.\n");
	/************Display Camera********/
	unsigned char *tempframestorage;
	tempframestorage = (unsigned char *) malloc(NSIZEX * NSIZEY * sizeof(char));
	cvWaitKey(500);
	char c = 0;
	while (1) {
		if (MyCamera->iFrameNumber > lastFrameSeenOutside) {
			lastFrameSeenOutside = MyCamera->iFrameNumber;
			numberOfFramesReceived++;
			printf(".o");
			//display frame that we grabbed from camera
			tempframestorage = (unsigned char *) memcpy(
					(void*) tempframestorage, (void*) MyCamera->iImageData,
					NSIZEX * NSIZEY * sizeof(char));
			CopyCharArrayToIplImage(tempframestorage, frame, NSIZEX, NSIZEY);
			printf("char array copied\n");
			double minvalue;
			double maxvalue;
			CvPoint MaxPoint;
			CvPoint MinPoint;

			cvMinMaxLoc(frame, &minvalue, &maxvalue, &MinPoint, &MaxPoint, NULL);
			printf("x: %d, y: %d\n", MaxPoint.x, MaxPoint.y);

			cvShowImage("FromCamera", frame);
			c = cvWaitKey(2);
			if (c == 27)
				break;
		}
		cvWaitKey(1);

	}
	free((void *) tempframestorage);
	cvReleaseImage(&frame);
	cvDestroyAllWindows();
	/**********************************/

	printf("Turning DLP on..\n");
	long myDLP = T2DLP_on(); //Turn DLP on.


	CircProp MyCirc;
	MyCirc.inputradius = 4;
	MyCirc.gauss_radius = 10;
	MyCirc.rel_intensity_thresh = 4;

	/* Calibration Parameters */
	int FramesPerCalib = 10;
	//number of pixels to move between capoints
	// obviously smaller takes more time but has more points for calibration
	int CalStepSize = 100;

	CvSeq* CalibSeq;
	CvMemStorage* calibstorage = cvCreateMemStorage(0);
	CalibSeq
			= cvCreateSeq(0, sizeof(CvSeq), sizeof(PairOfPoints), calibstorage);
	//Do a test run of the calibration so that the user can set the parameters correctlyk
	printf("Adjust the parameters to detect the spot and then hit escape.\n");
	printf("Be sure to check when the lamp is off as well.");
	CalibrateAPoint(cvPoint((int) NSIZEX / 2, (int) NSIZEX / 2), CalibSeq,
			NULL, &MyCirc, MyCamera, myDLP);
	//Clear the point storted in the line above. This was a practice run.
	cvClearSeq(CalibSeq);

	/*** Build Up a set of calibrated points ***/
	int calx = 0;
	int caly = 0;
	c = 0;
	while (caly < NSIZEY) {
		calx = 0;
		while (calx < NSIZEX) {
			//CALIBRATE A POINT
			CalibrateAPoint(cvPoint(calx, caly), CalibSeq, FramesPerCalib,
					&MyCirc, MyCamera, myDLP);

			calx = calx + CalStepSize;
			c = cvWaitKey(2);
			if (c == 27)
				break;
		}
		caly = caly + CalStepSize;
	}

	printf("CalibSeq contains %d calibrated pairs of points.\n",
			CalibSeq->total);

	printf("Talking to MATLAB....\n");
	/**********************************************************************/

	//	int *CCD2DLPLookUp;
	//	CCD2DLPLookUp = (int *) malloc(2 * NSIZEX * NSIZEY * sizeof(int));
	//******** GENERATE LOOKUP TABLE IN MATLAB *********/
	T2Matlab_GenLookUpTable(CalibSeq, CCD2DLPLookUp, NSIZEX, NSIZEY, CCDSIZEX, CCDSIZEY);
	printf(
			"Returned from T2Matlab_GenLookUpTable(CalibSeq, CCD2DLPLookUp, NSIZEX, NSIZEY);\n");
	T2DLP_off(myDLP);

}


int main(){

	//DisplayOpenCVInstall();

	T2Cam_InitializeLib();
	CamData *MyCamera;
	T2Cam_AllocateCamData(&MyCamera);
	printf("Allocated Camera: %d\n", *MyCamera);
	T2Cam_ShowDeviceSelectionDialog(&MyCamera);
	printf("Set Camera Properties: %d\n", *MyCamera);
	//Tell the Camera To Start and to call the callback function
	//The Call back function will store the frame form the camera and update the iFrameNumber
	T2Cam_GrabFramesAsFastAsYouCan(&MyCamera);
	printf("Told Camera to Grab Frames as Quickly as Possible: %d\n",
			*MyCamera);

	int *CCD2DLPLookUp;
	CCD2DLPLookUp = (int *) malloc(2 * NSIZEX * NSIZEY * sizeof(int));

	CalibrationTest(CCD2DLPLookUp, MyCamera);



	/********** Write Calibration to File **********/
	int result;
	cvWaitKey(100);

	printf("Opening file for writing...\n");
	FILE *fp;
	cvWaitKey(100);
	printf("Trying to open... calib.dat\n");
	if ((fp = fopen("calib.dat", "wb+")) == NULL) {
		printf("Cannot open file.\n");
	}
	printf("opened..\n");
	result=0;

	result=fwrite(CCD2DLPLookUp, sizeof(int)* 2 * NSIZEX * NSIZEY ,1, fp);
	if ( result != 1) {
		printf("Write error!\n");
	} else
		printf("Write was successful.\n");

	printf("Trying to close calib.dat\n");
	fflush(stdout);
	fclose(fp);
	printf("close succeeded\n");
	fflush(stdout);
	/***** Turn off Camera & DLP ****/
	printf("Outside of DoTheCameraDLPThing About to turn off camera %d\n",
			*MyCamera);
	T2Cam_TurnOff(&MyCamera);
	printf("Turned off camera\n");

	T2Cam_CloseLib();


	return 0;
}
