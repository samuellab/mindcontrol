/*
 * ~/workspace/OpticalMindControl/main.cpp
 * main.cpp
 *
 *  Created on: Jul 20, 2009
 *      Author: Andy
 */

//Standard C headers
#include <unistd.h>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <math.h>


//Windows Header

//C++ header
#include <iostream>
#include <limits>

using namespace std;


//OpenCV Headers
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include <assert.h>

//Andy's Personal Headers
#include "MyLibs/AndysOpenCVLib.h"
#include "MyLibs/Talk2FrameGrabber.h"
#include "MyLibs/Talk2DLP.h"
#include "MyLibs/Talk2Matlab.h"
#include "MyLibs/AndysComputations.h"
#include "MyLibs/TransformLib.h"


typedef struct CalibrationSessionStruct {
	/** Calibration Transfomration **/
	int *CCD2DLPLookUp;

	/** Input Output **/
	long myDLP;
	FrameGrabber* fg;

	/** Frames **/
	Frame* fromCCD;
	Frame* toDLP;
	Frame* temp;

	/** Internal Variables **/
	CvPoint MinPoint;
	CvPoint MaxPoint;
	double minvalue;
	double maxvalue;
	CvScalar mean;
	CvScalar stdev;

	/** Circle Drawing properties**/
	int CircRadius;
	int gauss_radius;
	int rel_intensity_thresh;
	/** Size of Objects **/
	CvSize DLPsize;
	CvSize Camsize;
}CalibrationSession;



/*
 * Create the calibration session structure
 *
 */
CalibrationSession* CreateCalibrationSession(){
	CalibrationSession* c = (CalibrationSession* ) malloc(sizeof(CalibrationSession) );

	/** Set Everything to Zero **/

	/** Input/Output **/
	c->myDLP=0;
	c->fg=NULL;


	/*** Frames **/
	fromCCD=NULL;
	toDLP=NULL;

	/** Internal Variables **/
	MinPoint=cvPoint(0,0);
	MaxPoint=cvPoint(0,0);
	minvalue=0;
	maxvalue=0;

	/** Circle properties **/
	c->CircRadius=4;
	c->gauss_radius=10;
	c->rel_intensity_thresh=4;

	c->DLPsize=cvSize(0,0);
	c->Camsize=cvSize(0,0);
	c->CCD2DLPLookUp=NULL;


}




/*
 * Allocate memory for the members of the calibration session structure
 */
void InitializeCalibrationSession(CalibrationSession* c){

	if (!(c->Camsize.width==c->DLPsize.width && c->Camsize.height==c->DLPsize.height) || c->Camsize.width==0 || c->DLPsize.width==0 || c->Camsize.height==0 || c->DLPsize.height==0){
		printf("The dimensions of the Camera or the DLP are invalid in IntializeCalibtraionSession()\n");
		assert(0);
	}

	/** Calibration Lookup Table **/
	c->	CCD2DLPLookUp = (int *) malloc(2 * c->Camsize.width * c->Camsize.height * sizeof(int));

	/** Frames **/
	c->fromCCD=CreateFrame(c->Camsize);
	c->toDLP=CreateFrame(c->DLPsize);

}

void DestroyCalibrationSession(CalibrationSession* c){
	DestroyFrame(&(c->fromCCD));
	DestroyFrame(&(c->toDLP));

	free(c);

}

/*
 * Set size of camera and DLP
 */
void SetHardwareDimensions(CalibrationSession* c, CvSize DLPsize, CvSize Camsize){
	c->Camsize=Camsize;
	c->DLPsize=DLPsize;

	printf("For now the camera and the DLP must have the same dimensions.");
	assert(Camsize.width==DLPsize.width && Camsize.height==DLPsize.height);

}



FrameGrabber* TurnOnFrameGrabber(){
	FrameGrabber* fg= CreateFrameGrabberObject();
	InitializeFrameGrabber(fg);
	FrameGrabberSetRegionOfInterest(fg,0,0,1024,768);
	PrepareFrameGrabberForAcquire(fg);
}


void SetupGUI(CalibrationSession* c){
	cvNamedWindow("FromCamera", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("FromCamera", 200, 200);
	cvNamedWindow("ToDLP", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("InputRad", "FromCamera", &(c->CircRadius), 10, NULL);
	cvCreateTrackbar("GaussRad", "FromCamera", &(c->gauss_radius), 30,			NULL);
	cvCreateTrackbar("RelIntThresh", "FromCamera",
				&(c->rel_intensity_thresh), 10, NULL);

}

void DrawCircleOnDLP(cvPoint center, CalibrationSession* c){

	cvSetZero(c->toDLP->iplimg);
	cvCircle(c->toDLP->iplimge, center, c->CircRadius+ 1,
			CV_RGB(255,255,255), CV_FILLED, 8);
	copyIplImageToCharArray(c->toDLP->ilpimg,toDLP->binary);
	T2DLP_SendFrame((unsigned char *) c->toDLP->binary, c->myDLP);
	cvShowImage("SentToDLP",c->toDLP->iplimg);
}

void AnalyzePointInFrame(CalibrationSession* c){
	cvSmooth(c->fromCCD->iplimg, c->temp->iplimg, CV_GAUSSIAN, (c->gauss_radius) * 2
			+ 1, (c->gauss_radius) * 2 + 1);


	//Find the pixel with the maximal intensity
	cvMinMaxLoc(c->temp->iplimg, &(c->minvalue), &(c->maxvalue), &(c->MinPoint), &(c->MaxPoint),
			NULL);
	cvAvgSdv(c->temp->iplimg, &(c->mean), &(c->stdev));

	printf("x: %d, y: %d,\t value: %d \t mean: %f, stdev: %f\n",
			c->MaxPoint.x, c->MaxPoint.y, (int) c->maxvalue, c->mean.val[0],
					c->stdev.val[0]);
	//Display the image

}

int main (int argc, char** argv){


	/** Display output about the OpenCV setup currently installed **/
	DisplayOpenCVInstall();

	/** Create session object **/
	CalibrationSession* c = CreateCalibrationSession();

	/** Set the size of the objects **/
	SetHardwareDimensions(c,cvSize(NSIZEX,NSIZEY)cvSize(NSIZEX,NSIZEY));

	/** Allocate memory for the variables we will be using this session **/
	InitializeCalibrationSession(c);

	/** Start Camera or Vid Input **/
	c->fg= TurnOnFrameGrabber();

	/** Prepare DLP ***/
	c->myDLP= T2DLP_on();

	/** Setup GUI **/
	SetupGUI(c);



	/** Draw A circle on the DLP so we can focus on the camera **/
	printf("Showing camera.\n Press any key to continue!\n");
	while (!kbhit()){
		/** Draw Circle on DLP **/
		DrawCircleOnDLP(cvPoint(c->Camsize.width/2,c->Camsize.height/2 ),c);

		/** Grab new frame from camera **/
		AcquireFrame(c->fg);
		LoadFrameWithBin(c->fg->HostBuf,c->fromCCD);

		/** Analyze the image from the camera **/
		AnalyzePointInFrame(c);

		/** Draw a square on the image and display it **/
		SafeDrawSquare(&(c->fromCCD->iplimg) , &(c->MaxPoint), `7);
		cvShowImage("FromCCD",c->fromCCD->iplimg);
		cvWaitKey(30);

	}
	T2DLP_clear(c->myDLP);



	/*** Start the actual calibration **/







	printf("\n Good bye.\n");
	return 0;
}


