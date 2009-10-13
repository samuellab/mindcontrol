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
CvMemStorage* g_storage = NULL;
CvMemStorage* scratchStorage=NULL;
CvMemStorage* more_storage=NULL;


IplImage* g_image = NULL;  // the original image
IplImage* g_gray=NULL;  //a grayscale version of the image
IplImage* thresh_img=NULL; // a thresholded version of the image


CvSeq* contours;
CvSeq* contourOfInterest;

CvSeq* VectBound;
//int Delta=11; // Coarse Grain factor (number of pixels away that is used to draw vectors)
int Delta=9;
int Offset=Delta/2; //Pixels to compensate for the CoarseGraininess (everythign is offset a little bit)
int CircleDiameterSize=10;

//int FileIndex=0;

int g_thresh = 48; //Value for image th reshoold
int gauss_size=4; // Size of gaussian that will be used for smoothing
int nc=0; // Number of contours






void on_trackbar(int){
	RefreshWormMemStorage(Worm);
	FindWormBoundary(Worm,Params);

	cvDrawContours(Worm->ImgSmooth, Worm->Boundary, cvScalar(255,0,0),cvScalar(0,255,0),100);
	cvShowImage("Original",Worm->ImgOrig);
	cvShowImage("Smoothed",Worm->ImgSmooth);
	cvShowImage("Thresholded",Worm->ImgThresh);


	GivenBoundaryFindWormHeadTail(Worm,Params);


	int i=0; //Generic counter



	if (GivenBoundaryFindWormHeadTail(Worm,Params)<0){
		printf("Error FindingWormHeadTail!\n");
	}




		//Draw a circle on the tail.
	//cvCircle(Worm->ImgSmooth,*(Worm->Tail),CircleDiameterSize,cvScalar(255,255,255),1,CV_AA,0);
	//cvCircle(Worm->ImgSmooth,*(Worm->Head),CircleDiameterSize*2,cvScalar(255,255,255),1,CV_AA,0);
	//	if (PRINTOUT) printf("MostCurvyIndex=%d\n",MostCurvyIndex);




	/****** Beginning Algorithm Outlined in
	 * http://wiki.client.fas.harvard.edu/index.php/AndyProjects/DLP_Project/2009:September#Devised_New_Algorithm_With_Marc
	 *
	 *
	 */

	/*****************************************************
	 * Start by creating two boundaries, A& B that cover the left and right side of the worm, seperated by the head
	 * and the tail.
	 *
	 */
	printf("Found Head And Tail without crashing.\n");
	return;
	CvSeq* ContourOfInterest;
	int HeadIndex;
	int TailIndex;

	//Slice the boundary into left and ridght
	CvSeq* OrigBoundA=cvSeqSlice(contourOfInterest,cvSlice(HeadIndex,TailIndex),more_storage,0);
	CvSeq* OrigBoundB=cvSeqSlice(contourOfInterest,cvSlice(TailIndex,HeadIndex),more_storage,0);
	cvSeqInvert(OrigBoundB);



	//Create sequences to store the Normalized Boundaries (the ones that are resampled to be the same length
	CvSeq* NBoundA=	cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),more_storage);
	CvSeq* NBoundB=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),more_storage);



	//Now we need to resample the left and right boundary to have the same number of points as min(L,R)
	if (OrigBoundA->total > OrigBoundB->total){
		resampleSeq(OrigBoundA,&NBoundA,OrigBoundB->total );
		NBoundB=OrigBoundB;
	}else{
		resampleSeq(OrigBoundB,&NBoundB,OrigBoundA->total );
		NBoundA=OrigBoundA;
	} //Now both NBoundA and NBoundB are the same length.


	if (PRINTOUT) printf("OrigBoundA->total=%d,OrigBoundB->total=%d\n",OrigBoundA->total,OrigBoundB->total);
	if (PRINTOUT) printf("NBoundA->total=%d,NBoundB->total=%d\n",NBoundA->total,NBoundB->total);








	/*************************************************************/
	/*
	 *
	 * Now Find the centerline
	 */


	if (PRINTOUT) printf("Beginning to find centerline\n");
	//Forward and Reverse Centerline
	CvSeq* centerline=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),more_storage);

	//Find Centerline from Head To Tail
	FindCenterline(NBoundA,NBoundB,&centerline);
	if (PRINTOUT) printf("Wrote centerline\n");


	//Now resample the centerline
	int NUMSEGMENTS = 100;
	CvSeq* SmoothUnresampledCenterline = smoothPtSequence (centerline, 0.5*centerline->total/NUMSEGMENTS, more_storage);
	CvSeq* Ncenterline=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),more_storage);
	resampleSeq(SmoothUnresampledCenterline,&Ncenterline,NUMSEGMENTS);

	CvSeq* OptBoundA=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),more_storage);
	CvSeq* OptBoundB=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),more_storage);

	//Smooth the Centerline (I am no longer actually smoothing the centerline because it has some problems)
	/*
	 *Smoothing the centerline using this algorithm has two main problems:
	 * 1) it takes long. According to Gprof it takes 60% of the time
	 * 2) It messes up the centerline near the head and tail by skipping points or something.
	 */
	//CvSeq* SmoothCenterline=smoothPtSequence (Ncenterline, 5, more_storage);
	CvSeq* SmoothCenterline=Ncenterline;


	if (ONSCREEN && DISPLAYSECTOR) DrawSequence(&g_gray,SmoothCenterline);
	if (ONSCREEN) cvShowImage("Contours",g_gray);

	//Use Marc's Magical Perpendicular Segmentation Algorithm (Because he's the man.)
	SegmentSides(OrigBoundA,OrigBoundB,SmoothCenterline,OptBoundA,OptBoundB);



	//Display the points slowly on screen
	if (ONSCREEN && DISPLAYSECTOR){
	for (i = 0; i < SmoothCenterline->total; i++) {
		CvPoint* tempPt = (CvPoint*) cvGetSeqElem(SmoothCenterline, i);
		CvPoint* tempPtA = (CvPoint*) cvGetSeqElem(OptBoundA, i);
		CvPoint* tempPtB = (CvPoint*) cvGetSeqElem(OptBoundB, i);
		if (PRINTOUT) printf("tempPt=( %d,%d)\t tempPtA =( %d,%d)\t tempPtB=( %d,%d)\n",tempPt->x,tempPt->y,tempPtA->x,tempPtA->y,tempPtB->x,tempPtB->y);
		cvCircle(g_gray, *tempPt, 1, cvScalar(255, 255, 255), 1);
		cvCircle(g_gray, *tempPtA, 1, cvScalar(255, 255, 255), 1);
		cvCircle(g_gray, *tempPtB, 1, cvScalar(255, 255, 255), 1);
		//cvLine(g_gray,*tempPtA,*tempPtB,cvScalar(255,255,255),1,CV_AA,0);

		cvLine(g_gray,*tempPt,*tempPtA,cvScalar(255,255,255),1,CV_AA,0);
		cvLine(g_gray,*tempPt,*tempPtB,cvScalar(255,255,255),1,CV_AA,0);
		cvShowImage("Contours", g_gray);
		if (HEAVYDIAGNOSTICS) cvWaitKey(100);

	}
	}

	if (ONSCREEN) cvShowImage("Contours", g_gray);




	/*
	 *
	 * Draw a rectangle on the worm to illuminate it.
	 */
	int radius=20;
//	IplImage** image, CvSeq* centerline, CvSeq* Boundary, int segment

	if (ILLUMINATE){
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,10);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,11);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,12);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,15);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,16);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundB,39);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundB,40);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundB,41);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,39);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,40);
	IlluminateWormSegment(&g_gray,SmoothCenterline,OptBoundA,41);
	}
	if (PRINTOUT) printf("About to show image.\n");
	if (ONSCREEN) cvShowImage("Contours", g_gray);
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



	//Load in Image Analysis Parameters
	Params->BinThresh=48;
	Params->GaussSize=4;
	Params->LengthScale=9;
	Params->LengthOffset=Params->LengthScale /2;


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


