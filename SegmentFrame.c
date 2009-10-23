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
#include "MyLibs/WormAnalysis.h"


//C Libraries
#include <string.h>
#include <math.h>



//Global Variables
/* Create a new instance of the WormAnalysis Data structure */
WormAnalysisData* Worm;
WormAnalysisParam* Params;
Frame* IlluminationFrame;
WormGeom* PrevWorm;


void on_trabckar(int);



void on_trackbar(int){
	RefreshWormMemStorage(Worm);
	FindWormBoundary(Worm,Params);

	cvDrawContours(Worm->ImgSmooth, Worm->Boundary, cvScalar(255,0,0),cvScalar(0,255,0),100);
	cvShowImage("Original",Worm->ImgOrig);
	cvShowImage("Thresholded",Worm->ImgThresh);



	if (GivenBoundaryFindWormHeadTail(Worm,Params)<0){
		printf("Error FindingWormHeadTail!\n");
	}

	/** If we are doing temporal analysis, improve the WormHeadTail estimate based on prev frame **/
	if (Params->TemporalOn) PrevFrameImproveWormHeadTail(Worm,Params,PrevWorm);

	SegmentWorm(Worm,Params);
	//Draw a circle on the tail.
	DisplayWormHeadTail(Worm,"Boundary");
	DisplayWormSegmentation(Worm,"Contours");

	/** Illuminate the Worm**/
	if (SimpleIlluminateWorm(Worm,IlluminationFrame,20,30)==0) cvShowImage("ToDLP",IlluminationFrame->iplimg);

	/** Update PrevWorm Info **/
	LoadWormGeom(PrevWorm,Worm);


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


	CvCapture* capture;
	IplImage* tempImg;

	printf("This program reads in an avi, finds a worm, and segments it.");
	if( argc != 2  ) return -1;
	capture = cvCreateFileCapture(argv[1]);

	/*
	 * Load in the first image to get the size of the image
	 *
	 */

	tempImg=cvQueryFrame(capture);
	if (tempImg==NULL) printf("There was an error querying the frame!\n");

	/*
	 * Fill up the Worm structure with Emtpy Images
	 */
	InitializeEmptyWormImages(Worm,cvGetSize(tempImg));
	InitializeWormMemStorage(Worm);

	/*
	 * Allocate memory for IlluminationFrame
	 */
	 IlluminationFrame=CreateFrame(cvGetSize(tempImg));

	 /*
	  * Allocate Memory for PrevWorm
	  */

	 PrevWorm=CreateWormGeom();

	/*
	 * Load in the Color Source Image
	 */


	cvNamedWindow("Original");
	cvNamedWindow("ToDLP");
	cvNamedWindow("Boundary");
	cvNamedWindow( "Thresholded");
	cvNamedWindow( "Contours", 1);
	cvNamedWindow("Controls");
	cvResizeWindow("Controls",300,400);



	cvCreateTrackbar("Threshold", "Controls", &(Params->BinThresh),255, on_trackbar);
	cvCreateTrackbar("Gauss=x*2+1","Controls", &(Params->GaussSize),5, on_trackbar);
	cvCreateTrackbar("ScalePx","Controls", &(Params->LengthScale),50,on_trackbar);
	cvCreateTrackbar("TemporalIQ","Controls",&(Params->TemporalOn),1, on_trackbar);
	cvCreateTrackbar("Proximity","Controls",&(Params->MaxLocationChange),100, on_trackbar);





	int i=0;
	while(1){

		if (i!=0) tempImg=cvQueryFrame( capture);
		if (tempImg==NULL) {
			printf("tempImg is NULL at frame %d.\n I assume this means we're done.",i);
			break;
		}
		i++;
		LoadWormColorOriginal(Worm,tempImg);
		on_trackbar(0);
		char c= cvWaitKey(33);
		if (c==27) break;
	}




if (0){
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



	cvWaitKey(0);
	DestroyWormAnalysisDataStruct(Worm);
	DestroyWormAnalysisParam(Params);



	return 0;
}


