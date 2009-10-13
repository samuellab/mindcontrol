#include <stdio.h>



//OpenCV Headers
#include <cxcore.h>
#include <highgui.h>
#include <cv.h>

#include "AndysOpenCVLib.h"

#include "WormAnalysis.h"

/*
 *
 * Every function here should have the word Worm in it
 * because every function here is worm specific
 */


/*
 *  Create the WormAnalysisDataStruct
 *  Initialize Memory Storage
 *  Set all Pointers to Null.
 *  Run CvCreate Sequence
 *
 *  Note this does not allocate memory for images because the user may not know
 *  what size image is wanted yet.
 *
 */
WormAnalysisData* CreateWormAnalysisDataStruct(){
	WormAnalysisData* WormPtr;
	WormPtr=malloc(sizeof(WormAnalysisData));

	/*** Set Everythingm To NULL ***/
	WormPtr->Head=NULL;
	WormPtr->Tail=NULL;
	WormPtr->HeadIndex=NULL;
	WormPtr->TailIndex=NULL;
	WormPtr->ImgOrig =NULL;
	WormPtr->ImgSmooth =NULL;
	WormPtr->ImgThresh =NULL;
	WormPtr->SizeOfImage=NULL;

	/*** Initialze Worm Memory Storage***/
	InitializeWormMemStorage(WormPtr);


	/**** Allocate Memory for CvSeq ***/
	WormPtr->Boundary=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),WormPtr->MemStorage);
	WormPtr->Centerline=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),WormPtr->MemStorage);;
	WormPtr->SegmentCenterline=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),WormPtr->MemStorage);;
	WormPtr->SegmentLeft=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),WormPtr->MemStorage);;
	WormPtr->SegmentRight=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),WormPtr->MemStorage);;

	return WormPtr;
}

/*
 *
 * Clear's all the Memory and De-Allocates it
 */
void DestroyWormAnalysisDataStruct(WormAnalysisData* WormPtr){
	if (Worm->ImgOrig !=NULL)	cvReleaseImage(&(Worm->ImgOrig));
	if (Worm->ImgThresh !=NULL) cvReleaseImage(&(Worm->ImgThresh));
	if (Worm->ImgSmooth !=NULL) cvReleaseImage(&(Worm->ImgSmooth));
	cvReleaseMemStorage(&(Worm->MemScratchStorage));
	cvReleaseMemStorage(&(Worm->MemStorage));
	free(WormPtr);
}

/*
 * Create dynamic memory storage for the worm
 *
 */
void InitializeWormMemStorage(WormAnalysisData* Worm){
	Worm->MemScratchStorage=cvCreateMemStorage(0);
	Worm->MemStorage=cvCreateMemStorage(0);
}

/*
 * Refersh dynamic memory storage for the worm
 * (clear the memory without freing it)
 *
 */
void RefreshWormMemStorage(WormAnalysisData* Worm){
	cvClearMemStorage(Worm->MemScratchStorage);
	cvClearMemStorage(Worm->MemStorage);
}




/*
 * Create Blank Images for WormAnalysisData
 *
 */

void InitializeEmptyWormImages(WormAnalysisData* Worm, CvSize ImageSize){
	Worm->SizeOfImage=ImageSize;
	Worm->ImgOrig= cvCreateImage(ImageSize,IPL_DEPTH_8U,1);
	Worm->ImgSmooth=cvCreateImage(ImageSize,IPL_DEPTH_8U,1);
	Worm->ImgThresh=cvCreateImage(ImageSize,IPL_DEPTH_8U,1);

}




/*
 * This function is run after IntializeEmptyImages.
 * And it loads a color original into the WormAnalysisData strucutre.
 * The color image is converted to an 8 bit black and white.
 */
void LoadWormColorOriginal(WormAnalysisData* Worm, IplImage* ImgColorOrig){
	CvSize CurrentSize = cvGetSize(ImgColorOrig);
	if ( (Worm->SizeOfImage.height != CurrentSize.height) || (Worm->SizeOfImage.width != CurrentSize.width) ){
		printf("Error. Image size does not match in ");
		return;
	}
	cvCvtColor( ImgColorOrig, Worm->ImgOrig, CV_BGR2GRAY);

}




/*
 * Smooths, thresholds and finds the worms contour.
 * The original image must already be loaded into Worm.ImgOrig
 * The Smoothed image is deposited into Worm.ImgSmooth
 * The thresholded image is deposited into Worm.ImgThresh
 * The Boundary is placed in Worm.Boundary
 *
 */
void FindWormBoundary(WormAnalysisData* Worm, WormAnalysisParam* Params){
	cvSmooth(Worm->ImgOrig,Worm->ImgSmooth,CV_GAUSSIAN,Params->GaussSize*2+1);
	cvThreshold(Worm->ImgSmooth,Worm->ImgThresh,Params->BinThresh,255,CV_THRESH_BINARY );
	CvSeq* contours;
	cvFindContours(Worm->ImgThresh,Worm->MemStorage, &contours,sizeof(CvContour),CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE,cvPoint(0,0));
	if (contours) LongestContour(contours,&(Worm->Boundary));

}


/*
 * Finds the Worm's Head and Tail.
 * Requires Worm->Boundary
 *
 */
int GivenBoundaryFindWormHeadTail(WormAnalysisData* Worm, WormAnalysisParam* Params){
	if (Worm->Boundary->total <2) {
		/**Error! There is no Boundary **/
		return -1;
	}



	return 0;
}


/*
 * Illuminate a segment of the worm. Either the right, or left side.
 * Takes a sequence of the centerline. Uses the preceeding point to find a vector
 * along the centerline, than draws a rectangle perpendicular to this vector, a radius rsquared pixels
 * away from the centerline
 */
void IlluminateWormSegment(IplImage** image, CvSeq* centerline, CvSeq* Boundary, int segment){
	int PRINTOUT=0;
	if (segment <1) {
		if (PRINTOUT) printf("ERROR: segment <1 :  Choose a segment along the worm that is at least 1.\n ");
		return;
	}

	int rfactor=2;

	CvPoint* PtAlongCenterline;
	CvPoint* PrevPtAlongCenterline;
	CvPoint* PtAlongBoundary;
	CvPoint* PrevPtAlongBoundary;


	CvPoint VecToBound; //Vector Perpendicular to the segment
	CvPoint PrevVecToBound;

	PtAlongCenterline=(CvPoint*) cvGetSeqElem(centerline,segment);
	PrevPtAlongCenterline=(CvPoint*) cvGetSeqElem(centerline,segment-1);

	PtAlongBoundary=(CvPoint*) cvGetSeqElem(Boundary,segment);
	PrevPtAlongBoundary=(CvPoint*) cvGetSeqElem(Boundary,segment-1);

	VecToBound= cvPoint(PtAlongBoundary->x - PtAlongCenterline->x ,PtAlongBoundary->y - PtAlongCenterline->y );
	PrevVecToBound= cvPoint(PrevPtAlongBoundary->x - PrevPtAlongCenterline->x ,PrevPtAlongBoundary->y - PrevPtAlongCenterline->y );
	if (PRINTOUT) printf("VecToBound=( %d,%d )\n",VecToBound.x, VecToBound.y);
	if (PRINTOUT) printf("PrevVecToBound=( %d,%d )\n",PrevVecToBound.x, PrevVecToBound.y);

	//What we want to do is double the length of the vectors and add them to the centerline
	// To find a point that sticks out a specific radius from the worm.

	CvPoint FarPt=cvPoint( PtAlongBoundary->x + 2* VecToBound.x ,  PtAlongBoundary->y + 2* VecToBound.y);
	CvPoint PrevPt=cvPoint( PrevPtAlongBoundary->x + 2* PrevVecToBound.x ,  PrevPtAlongBoundary->y + 2* PrevVecToBound.y );



	if (PRINTOUT) printf("Before cvFillConvexPoly\n");

	//cvRectangle(*image,cvPoint(10,10),cvPoint(300,300),cvScalar(255,255,255),1,CV_AA,0);
	//cvFillPoly(*image,pt,nRectpoints,nRectangles,cvScalar(255,255,255),CV_AA,0);
	//{&FarPt, &PrevPT, PtAlongCenterline, PrevPtAlongCenterline};
	// JUST
	CvPoint myPolygon[4];
	myPolygon[0]=FarPt;
	myPolygon[1]=PrevPt;
	myPolygon[3]=*PtAlongCenterline;
	myPolygon[2]=*PrevPtAlongCenterline;
	if (PRINTOUT) printf("FarPt=(%d,%d)\nPrevPt=(%d,%d)\n*PtAlongCenterline=(%d,%d)\n*PrevPtAlongCenterline=(%d,%d)\n",FarPt.x,FarPt.y,PrevPt.x,PrevPt.y,PtAlongBoundary->x,PtAlongBoundary->y,PrevPtAlongCenterline->x,PrevPtAlongCenterline->y);
	cvFillConvexPoly(*image,myPolygon,4,cvScalar(255,255,255),CV_AA);
	if (PRINTOUT) printf("After cvFillConvexPoly\n");



}
