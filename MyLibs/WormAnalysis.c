#include <stdio.h>



//OpenCV Headers
#include <cxcore.h>
#include <highgui.h>
#include <cv.h>

// Andy's Libraries
#include "AndysOpenCVLib.h"
#include "AndysComputations.h"

#include "WormAnalysis.h"

/*
 *
 * Every function here should have the word Worm in it
 * because every function here is worm specific
 */


/************************************************************/
/* Creating, Destroying and Memory for 						*/
/*  WormAnalysisDataStruct 									*/
/*															*/
/************************************************************/



/*
 *  Create the WormAnalysisDataStruct
 *  Initialize Memory Storage
 *  Set all Pointers to Null.
 *  Run CvCreate Sequence
 *
 *  Note this does not allocate memory for images because the user may not know
 *  what size image is wanted yet.
 *
 *  To do that use LoadWormColorOriginal()
 *
 */
WormAnalysisData* CreateWormAnalysisDataStruct(){
	WormAnalysisData* WormPtr;
	WormPtr=(WormAnalysisData*) malloc(sizeof(WormAnalysisData));

	/*** Set Everythingm To NULL ***/
	WormPtr->Head=NULL;
	WormPtr->Tail=NULL;
	WormPtr->HeadIndex=NULL;
	WormPtr->TailIndex=NULL;
	WormPtr->ImgOrig =NULL;
	WormPtr->ImgSmooth =NULL;
	WormPtr->ImgThresh =NULL;

	WormPtr->SizeOfImage.height = NULL;
	WormPtr->SizeOfImage.width= NULL;

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
void DestroyWormAnalysisDataStruct(WormAnalysisData* Worm){
	if (Worm->ImgOrig !=NULL)	cvReleaseImage(&(Worm->ImgOrig));
	if (Worm->ImgThresh !=NULL) cvReleaseImage(&(Worm->ImgThresh));
	if (Worm->ImgSmooth !=NULL) cvReleaseImage(&(Worm->ImgSmooth));
	cvReleaseMemStorage(&(Worm->MemScratchStorage));
	cvReleaseMemStorage(&(Worm->MemStorage));
	free(Worm);
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
	if (Worm->MemScratchStorage!=NULL)cvClearMemStorage(Worm->MemScratchStorage);
	if (Worm->MemStorage!=NULL) cvClearMemStorage(Worm->MemStorage);
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



/************************************************************/
/* Creating, Destroying WormAnalysisParam					*/
/*  					 									*/
/*															*/
/************************************************************/

/*
 *  Allocate memory for a WormAnalysisParam struct
 */
WormAnalysisParam* CreateWormAnalysisParam(){
	WormAnalysisParam* ParamPtr;
	ParamPtr=(WormAnalysisParam*) malloc(sizeof(WormAnalysisParam));


	ParamPtr->BinThresh=NULL;
	ParamPtr->GaussSize=NULL;
	ParamPtr->LengthOffset=NULL;
	ParamPtr->LengthScale=NULL;

	return ParamPtr;
}


void DestroyWormAnalysisParam(WormAnalysisParam* ParamPtr){
	free(ParamPtr);
}



/************************************************************/
/* Higher Level Routines									*/
/*  					 									*/
/*															*/
/************************************************************/



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
int GivenBoundaryFindWormHeadTail(WormAnalysisData* Worm, WormAnalysisParam* Params) {
	if (Worm->Boundary->total < 2) {
		/**Error! There is no Boundary **/
		return -1;
	}

	/* **********************************************************************/
	/*  Express the Boundary in the form of a series of vectors connecting 	*/
	/*  two pixels a Delta pixels apart.									*/
	/* **********************************************************************/

	/* Create Temperorary CvSeq to store the boundary as a
	 * series of vectors.
	 */
	CvSeq* VectBound = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq),
			sizeof(CvPoint), Worm->MemScratchStorage);

	//We walk around the boundary using the high-speed reader and writer objects.
	CvSeqReader readerA;
	CvSeqReader readerB; //readerB will point a Delta points ahead of readerB.
	CvSeqWriter writer;

	/**** Local Variables ***/
	int i;
	CvPoint TempVec;
	CvPoint* boundPt; //Temp storage of the the current pt on the boundary
	CvPoint* boundPtDelta; //Temp storage of the pt Detla away on the boundary
	int TotalBPts = Worm->Boundary->total;

	/*** Initializing Read & Write Apparatus ***/
	cvStartReadSeq(Worm->Boundary, &readerA, 0);
	cvStartReadSeq(Worm->Boundary, &readerB, 0);
	cvStartAppendToSeq(VectBound, &writer);

	//Let's increment readerB delta times to gtet it into place
	for (i = 0; i < Params->LengthOffset; i++) {
		CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerB);
	}

	/*
	 * Loop through all the boundary and draw vectors connecting one boundary point to the next.
	 */
	for (i = 0; i < TotalBPts; i++) {
		boundPt = (CvPoint*) readerA.ptr;
		boundPtDelta = (CvPoint*) readerB.ptr;

		CV_NEXT_SEQ_ELEM( Worm->Boundary->elem_size, readerA);
		CV_NEXT_SEQ_ELEM( Worm->Boundary->elem_size, readerB);
		TempVec = cvPoint((boundPtDelta->x) - (boundPt->x), (boundPtDelta->y)
				- (boundPt->y));

		CV_WRITE_SEQ_ELEM( TempVec , writer );

	}
	cvEndWriteSeq(&writer);

	/* **********************************************************************/
	/*  Find the Tail 													 	*/
	/*  Take dot product of neighboring vectors. Tail is location of		*/
	/*	 smallest dot product												*/
	/* **********************************************************************/

	CvPoint* VecA;
	CvPoint* VecB;

	/*
	 * Now Let's loop through the entire boundary to find the tail, which will be the curviest point.
	 */
	float MostCurvy = 1000; //Smallest value.
	float CurrentCurviness; //Metric of CurrentCurviness. In this case the dot product.
	int MostCurvyIndex = 0;
	CvPoint* Tail;

	cvStartReadSeq(VectBound, &readerA, 0);
	cvStartReadSeq(VectBound, &readerB, 0);
	CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerA);
	for (i = 0; i < TotalBPts; i++) {
		VecA = (CvPoint*) readerA.ptr;
		VecB = (CvPoint*) readerB.ptr;

		//Find the curviness by taking the dot product.
		CurrentCurviness = PointDot(VecA, VecB);
		CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerA);
		CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerB);
		if (CurrentCurviness < MostCurvy) { //If this locaiton is curvier than the previous MostCurvy location
			MostCurvy = CurrentCurviness; //replace the MostCurvy point
			MostCurvyIndex = i;
		}
	}

	//Set the tail to be the point on the boundary that is most curvy.
	Worm->Tail = (CvPoint*) cvGetSeqElem(Worm->Boundary, (MostCurvyIndex
			+ Params->LengthOffset) % TotalBPts);

	/* **********************************************************************/
	/*  Find the Head 													 	*/
	/* 	Excluding the neighborhood of the Tail, the head is the location of */
	/*	 the smallest dot product											*/
	/* **********************************************************************/

	float SecondMostCurvy = 1000;
	int SecondMostCurvyIndex = 0;
	int DistBetPtsOnBound;
	DistBetPtsOnBound = 0;
	CvPoint* Head;

	cvStartReadSeq(VectBound, &readerA, 0);
	cvStartReadSeq(VectBound, &readerB, 0);
	CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerA);
	for (i = 0; i < TotalBPts; i++) {
		VecA = (CvPoint*) readerA.ptr;
		VecB = (CvPoint*) readerB.ptr;
		CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerA);
		CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerB);

		//Find the curviness by taking the normalized dot product.
		CurrentCurviness = PointDot(VecA, VecB);

		//We need to find out if the current curvy point is close to the most curvy point.
		//This is tricky because the boundary wraps around. We need this if statement to find the radius.
		// ANDY: Decomp this into its own function for legibility.
		DistBetPtsOnBound = DistBetPtsOnCircBound(TotalBPts, i, MostCurvyIndex);
		//If we are at least a 1/4 of the total boundary away from the most curvy point.
		if (DistBetPtsOnBound > (TotalBPts / 4)) {
			//If this location is curvier than the previous SecondMostCurvy location
			if (CurrentCurviness < SecondMostCurvy) {
				SecondMostCurvy = CurrentCurviness; //replace the MostCurvy point
				SecondMostCurvyIndex = i;
			}
		}
	}

	Worm->Head = (CvPoint*) cvGetSeqElem(Worm->Boundary,
			(SecondMostCurvyIndex +Params->LengthOffset) % TotalBPts);

	Worm->TailIndex = MostCurvyIndex +Params->LengthOffset;
	Worm->HeadIndex = SecondMostCurvyIndex +Params->LengthOffset;

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
