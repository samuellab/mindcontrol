/*
 * SegmentFrame.c
 *
 *  Created on: Aug 25, 2009
 *      Author: andy
 *
 *   Based in large part on the example on p.242 of the O'Reilly Book: Learning OpenCV
 */

//Adding a comment.



#include <stdio.h>

//OpenCV Headers
#include <highgui.h>
#include <cv.h>

//Andy's Personal Headers
#include "MyLibs/AndysOpenCVLib.h"
#include "MyLibs/Global.h"
#include "MyLibs/WormAnalysis.h"


//C Libraries
#include <string.h>
#include <math.h>



//Global Variables
/* Create a new instance of the WormAnalysis Data structure */
WormAnalysisData* Worm;
WormAnalysisParam* Params;






void on_trabckar(int);





void on_trackbar(int){
	RefreshWormMemStorage(Worm);
	FindWormBoundary(Worm,Params);

	cvDrawContours(Worm->ImgSmooth, Worm->Boundary, cvScalar(255,0,0),cvScalar(0,255,0),100);
	cvShowImage("Original",Worm->ImgOrig);
	cvShowImage("Thresholded",Worm->ImgThresh);


	GivenBoundaryFindWormHeadTail(Worm,Params);



	if (GivenBoundaryFindWormHeadTail(Worm,Params)<0){
		printf("Error FindingWormHeadTail!\n");
	}

	SegmentWorm(Worm,Params);
	//Draw a circle on the tail.
	DisplayWormHeadTail(Worm,"Smoothed");


	//Display the points slowly on screen
	int i;
	for (i = 0; i < Worm->Segmented->Centerline->total; i++) {
		CvPoint* tempPt = (CvPoint*) cvGetSeqElem(Worm->Segmented->Centerline, i);
		CvPoint* tempPtA = (CvPoint*) cvGetSeqElem(Worm->Segmented->RightBound, i);
		CvPoint* tempPtB = (CvPoint*) cvGetSeqElem(Worm->Segmented->LeftBound, i);
		cvCircle(Worm->ImgSmooth, *tempPt, 1, cvScalar(255, 255, 255), 1);
		cvCircle(Worm->ImgSmooth, *tempPtA, 1, cvScalar(255, 255, 255), 1);
		cvCircle(Worm->ImgSmooth, *tempPtB, 1, cvScalar(255, 255, 255), 1);
		//cvLine(g_gray,*tempPtA,*tempPtB,cvScalar(255,255,255),1,CV_AA,0);

		cvLine(Worm->ImgSmooth,*tempPt,*tempPtA,cvScalar(255,255,255),1,CV_AA,0);
		cvLine(Worm->ImgSmooth,*tempPt,*tempPtB,cvScalar(255,255,255),1,CV_AA,0);
		cvShowImage("Contours", Worm->ImgSmooth);

	}


	/*
	 *
	 * Draw a rectangle on the worm to illuminate it.
	 */

//	IplImage** image, CvSeq* centerline, CvSeq* Boundary, int segment

//	if (ILLUMINATE){
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,10);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,11);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,12);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,15);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,16);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundB,39);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundB,40);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundB,41);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,39);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,40);
//	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,41);
//	}

}





int main (int argc, char** argv){
	/* This will let us know if  the intel primitives are installed*/
	DisplayOpenCVInstall();
	Worm=CreateWormAnalysisDataStruct();
	Params=CreateWormAnalysisParam();

	IplImage* tempImg;
	if (PRINTOUT) printf("This program reads in a jpg, finds a worm, and segments it.");
	if( argc != 2 || !(tempImg = cvLoadImage(argv[1])) ) return -1;
	printf("About to Initialize Empty Images\n");

	/*
	 * Fill up the Worm structure with Emtpy Images
	 */
	InitializeEmptyWormImages(Worm,cvGetSize(tempImg));
	InitializeWormMemStorage(Worm);

	/*
	 * Load in the Color Source Image
	 */
	LoadWormColorOriginal(Worm,tempImg);
	cvReleaseImage(&tempImg);

	cvNamedWindow("Original");
	cvNamedWindow("Smoothed");
	cvNamedWindow( "Thresholded");
	cvNamedWindow( "Contours", 1);
	cvNamedWindow("Controls");
	cvResizeWindow("Controls",300,400);



	cvCreateTrackbar("Threshold", "Controls", &(Params->BinThresh),255, on_trackbar);
	cvCreateTrackbar("Gauss=x*2+1","Controls", &(Params->GaussSize),5, on_trackbar);
	cvCreateTrackbar("ScalePx","Controls", &(Params->LengthScale),15,on_trackbar);
	cvCreateTrackbar("Offset Comp","Controls",&(Params->LengthOffset),15, on_trackbar);




if (TIMETEST){
	/*
	 * Time Test
	 *
	 */
	int NumLoops=1000;
	int i;
	printf("Ready...\n");
	cvWaitKey();
	printf("Start a Thousand Loops\n");
	for (i=0; i<NumLoops; i++){
	on_trackbar(0);
	if (i%100==0) printf(".");
	}
	printf("Finished!\n");
}

	printf("About to enter on_trackbar(0)\n");

	on_trackbar(0);
	printf("Finished on_trackbar(0)\n");

	cvWaitKey(0);
	DestroyWormAnalysisDataStruct(Worm);
	DestroyWormAnalysisParam(Params);



	return 0;
}


