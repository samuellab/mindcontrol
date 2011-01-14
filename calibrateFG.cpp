/*
 * Copyright 2010 Andrew Leifer et al <leifer@fas.harvard.edu>
 * This file is part of MindControl.
 *
 * MindControl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU  General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MindControl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MindControl. If not, see <http://www.gnu.org/licenses/>.
 *
 * For the most up to date version of this software, see:
 * http://github.com/samuellab/mindcontrol
 *
 *
 *
 * NOTE: If you use any portion of this code in your research, kindly cite:
 * Leifer, A.M., Fang-Yen, C., Gershow, M., Alkema, M., and Samuel A. D.T.,
 * 	"Optogenetic manipulation of neural activity with high spatial resolution in
 *	freely moving Caenorhabditis elegans," Nature Methods, Submitted (2010).
 */

/*
 *
 *  Calibrate the position of the mirrors relative to the pixels of the camera.
 *  This replaces the now obsolete calibrate.c file.
 *
 *  This routine works by flipping the mirrors so as to scan a point
 *  across the camera. The software records the location of the mirror
 *  and the corresponding light on the camera and then opens MATLAB
 *  to generate a lookup table to transform between camera space and
 *  mirror space based on the measured points. The calibration is stored in
 *  calib.dat
 *
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
	Frame* temp2;
	Frame* background;

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
	int minIntensityAboveMean; // Number of intensity units that a pt must have above the mean to be valid.

	/** Size of Objects **/
	CvSize DLPsize;
	CvSize Camsize;


	/** Calibrated Points CvSeq Stuff **/
	CvMemStorage* calibstorage;
	CvSeq* CalibSeq;

	/** Parameters **/
	int StepSize;
	int LoopsPerPt;

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
	c->fromCCD=NULL;
	c->toDLP=NULL;
	c->temp=NULL;
	c->temp2=NULL;
	c->background=NULL;

	/** Internal Variables **/
	c->MinPoint=cvPoint(0,0);
	c->MaxPoint=cvPoint(0,0);
	c->minvalue=0;
	c->maxvalue=0;

	/** Circle properties **/
	c->CircRadius=4;
	c->gauss_radius=6;
	c->rel_intensity_thresh=0;
	c->minIntensityAboveMean=1;

	/** Sizing Info **/
	c->DLPsize=cvSize(0,0);
	c->Camsize=cvSize(0,0);

	/** Lookup Table **/
	c->CCD2DLPLookUp=NULL;

	/** Calibrated Points CvSeq Stuff **/
	c->calibstorage=NULL;
	c->CalibSeq=NULL;

	/** Parameters **/
	c->StepSize=0;
	c->LoopsPerPt=0;

	return c;


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
	c->temp=CreateFrame(c->Camsize);
	c->temp2=CreateFrame(c->Camsize);
	c->background=CreateFrame(c->Camsize);

	/** Calibration Data Sequences **/

	c->calibstorage = cvCreateMemStorage(0);
	c->CalibSeq = cvCreateSeq(0, sizeof(CvSeq), sizeof(PairOfPoints), c->calibstorage);

	return;
}

void DestroyCalibrationSession(CalibrationSession* c){
	DestroyFrame(&(c->fromCCD));
	DestroyFrame(&(c->toDLP));

	free(c);
	return;

}

/*
 * Set size of camera and DLP
 */
void SetHardwareDimensions(CalibrationSession* c, CvSize DLPsize, CvSize Camsize){
	c->Camsize=Camsize;
	c->DLPsize=DLPsize;
	printf("For now the camera and the DLP must have the same dimensions.");
	assert(Camsize.width==DLPsize.width && Camsize.height==DLPsize.height);
	return;
}




void SetupGUI(CalibrationSession* c){
	cvNamedWindow("FromCamera", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("ToDLP", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("InputRad", "FromCamera", &(c->CircRadius), 10, NULL);
	cvCreateTrackbar("GaussRad", "FromCamera", &(c->gauss_radius), 30,			NULL);
	cvCreateTrackbar("RelIntThresh", "FromCamera",
				&(c->rel_intensity_thresh), 10, NULL);
	cvCreateTrackbar("MinIntAboveMean","FromCamera", &(c->minIntensityAboveMean),10,NULL);
	return;

}

void DrawCircleOnDLP(CvPoint center, CalibrationSession* c){

	cvSetZero(c->toDLP->iplimg);
	cvCircle(c->toDLP->iplimg, center, c->CircRadius+ 1,
			CV_RGB(255,255,255), CV_FILLED, 8);
	copyIplImageToCharArray(c->toDLP->iplimg,c->toDLP->binary);
	T2DLP_SendFrame((unsigned char *) c->toDLP->binary, c->myDLP);
	cvShowImage("SentToDLP",c->toDLP->iplimg);
	return;
}

void AnalyzePointInFrame(CalibrationSession* c){
	if (c->fromCCD==NULL || c->temp == NULL || c->temp2==NULL ) printf("ERROR! c->fromCCD, c->temp, or c->temp2 are NULL!\n");


	/** Subtract background **/
	cvSub(c->fromCCD->iplimg, c->background->iplimg,c->temp2->iplimg);

	/** Apply Gaussian Smooth **/
	cvSmooth(c->temp2->iplimg, c->temp->iplimg, CV_GAUSSIAN, (c->gauss_radius) * 2
			+ 1, (c->gauss_radius) * 2 + 1);



	//Find the pixel with the maximal intensity
	cvMinMaxLoc(c->temp->iplimg, &(c->minvalue), &(c->maxvalue), &(c->MinPoint), &(c->MaxPoint),
			NULL);
	cvAvgSdv(c->temp->iplimg, &(c->mean), &(c->stdev));

	printf("x: %d, y: %d,\t value: %d \t mean: %f, stdev: %f\n",
			c->MaxPoint.x, c->MaxPoint.y, (int) c->maxvalue, c->mean.val[0],
					c->stdev.val[0]);


}

void CheckFGSizeMatch(IplImage* img, FrameGrabber* fg){
	if ((int) fg->xsize != img->width   ||  (int) fg->ysize != img->height){
		printf("In CheckFGSizeMAtch, size from framegrabber does not match size in IplImage fromCCD!\n");
		printf(" fg->xsize=%d\n",(int) fg->xsize);
		printf(" img->width=%d\n",img->width);
		printf(" fg->ysize=%d\n",(int)  fg->ysize);
		printf(" img->height=%d\n",img->height);
	}


	return;
}

/*
 * Draws a circle and sends it to the DLP. Acquires a frame from the camera
 * and then conducts an analysis of the frame from the camera.
 */
void SendPt2DLPAndObserve(CvPoint pt, CalibrationSession* c ){
	/** Draw Circle on DLP **/
	DrawCircleOnDLP(pt,c);


	/** Grab new frame from camera **/
	AcquireFrame(c->fg);

	/** Check that our image is properly sized **/
	CheckFGSizeMatch(c->fromCCD->iplimg,c->fg);

	LoadFrameWithBin(c->fg->HostBuf,c->fromCCD);

	/** Analyze the image from the camera **/
	AnalyzePointInFrame(c);
	return;

}


/*
 * Takes the background image
 */
void TakeBakgroundImage(CalibrationSession* c){
	/** Let's take a background image so that we can subtract it off **/
	printf("\nTaking a background image. \n");
	T2DLP_clear(c->myDLP);
	cvWaitKey(10);
	AcquireFrame(c->fg);

	/** Check that our image is properly sized **/
	CheckFGSizeMatch(c->background->iplimg,c->fg);

	/** Load the binary image data from the frame grabber into our background variable **/
	LoadFrameWithBin(c->fg->HostBuf,c->background);
	printf("\nBackground image acquried.\n");
	return;

}



void CalibrateAPoint(CvPoint pt, CalibrationSession* c){
	int k;


	/** Create sequence to store the max point for each frame **/
	CvSeq* Pts= cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), c->calibstorage);
	cvClearSeq(Pts);


	/** For each frame find the location of the brightest pixel **/
	for (k = 0; k <	c->LoopsPerPt; ++k) {

		/** Make pt on DLP, observe on Camera**/
		SendPt2DLPAndObserve(pt,c);

		/** Draw a square on the image and display it **/
		SafeDrawSquare(&(c->fromCCD->iplimg) , &(c->MaxPoint), 7);

		cvShowImage("ToDLP",c->toDLP->iplimg);
		cvShowImage("FromCamera",c->fromCCD->iplimg);
		cvWaitKey(3);



		/** Is the Point Valid? **/
		if ((c->maxvalue > ((c->rel_intensity_thresh) * c->stdev.val[0])
					+ c->mean.val[0]) &&  c->maxvalue-c->mean.val[0] > c->minIntensityAboveMean   ) {
				cvSeqPush(Pts, &(c->MaxPoint));
			} else {
				printf("Tossing frame. Spot fails relative intensity threshold.\n");
		}
	}


	/** Find the median point **/
	PairOfPoints pair;
	pair.alpha=pt;
	pair.beta= GetMedianOfPoints(Pts);

	//If both points in the are greater than zero AND if the number of valid points is greater than half of the expected number of points
	if ((pair.beta.x >0 && pair.beta.y > 0) && Pts->total > c->LoopsPerPt / 2) {
		cvSeqPush(c->CalibSeq, &pair);
		printf("Median Found ( %d, %d )\n", pair.beta.x, pair.beta.y);
	} else {
		printf("Tossing out the calibration for this point.\n");
	}

	cvClearSeq(Pts);

}

void WriteCalibrationToFile(int* CCD2DLPLookup, CvSize size, const char * filename ){

	/** Open File **/
	FILE *fp;
	if ((fp = fopen(filename, "wb+")) == NULL) {
		printf("ERROR: Cannot open file to write calibration\n");
		return;
	}

	/** Write lookup table to disk **/
	int result=fwrite(CCD2DLPLookup, sizeof(int)* 2 * size.width* size.height,1, fp);

	if ( result != 1) {
		printf("Write error!\n");
	} else{
		printf("Write was successful.\n");
	}

	fclose(fp);

	return;
}

int main (int argc, char** argv){


	/** Display output about the OpenCV setup currently installed **/
	DisplayOpenCVInstall();

	/** Create session object **/
	CalibrationSession* c = CreateCalibrationSession();

	/** Set the size of the objects **/
	SetHardwareDimensions(c,cvSize(NSIZEX,NSIZEY),cvSize(NSIZEX,NSIZEY));

	/** Allocate memory for the variables we will be using this session **/
	InitializeCalibrationSession(c);


	/** Set Parameters **/
	c->StepSize=100; //pixels
	c->LoopsPerPt=20; // Number of frames we use to calibrate a given point

	/** Start Camera **/
	c->fg= TurnOnFrameGrabber();

	/** Set the acquisition timeout to be very long to give the camera time to take long exposures, as is typical with calibration **/
	setAcquisitionTimeout(c->fg,200);

	/** Prepare DLP ***/
	c->myDLP= T2DLP_on();

	/** Setup GUI **/
	SetupGUI(c);



	/** Let's take a background image so that we can subtract it off **/
	TakeBakgroundImage(c);


	/** Draw A circle on the DLP so we can focus on the camera **/
	printf("Showing camera.\n Press any key to continue!\n");
	while (!kbhit()){

		/** Make pt on DLP, observe on Camera**/
		SendPt2DLPAndObserve(cvPoint(c->Camsize.width/2,c->Camsize.height/2 ),c);

		/** Draw a square on the image and display it **/
		SafeDrawSquare(&(c->fromCCD->iplimg) , &(c->MaxPoint), 7);
		cvShowImage("ToDLP",c->toDLP->iplimg);
		cvWaitKey(2);
		cvShowImage("FromCamera",c->fromCCD->iplimg);
		cvWaitKey(2);

	}
	T2DLP_clear(c->myDLP);



	/*** Build Up a set of calibrated points ***/
	int calx = 0;
	int caly = 0;


	printf(" Beginning calibration..\n");

	while (caly < c->DLPsize.height ) {
		calx = 0;

		while (calx < c->DLPsize.width) {

			CalibrateAPoint(cvPoint(calx,caly),c);

			calx = calx + c->StepSize;
		}
		caly = caly + c->StepSize;
	}

	T2DLP_clear(c->myDLP);

	/** Generate Look Up Table in Matlab **/
	cvDestroyAllWindows();

	printf("Talking to MATLAB....\n");
	T2Matlab_GenLookUpTable(c->CalibSeq, c->CCD2DLPLookUp, c->DLPsize.width, c->DLPsize.height, c->Camsize.width, c->Camsize.height);

	/** Write calibration to file **/
	WriteCalibrationToFile(c->CCD2DLPLookUp,c->Camsize,"calib.dat");

	/** Turn everything Off **/
	T2DLP_off(c->myDLP);
	CloseFrameGrabber(c->fg);

	DestroyCalibrationSession(c);


	printf("\n Good bye.\n");
	return 0;
}


