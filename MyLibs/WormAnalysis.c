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

#include <stdio.h>
#include <time.h>


//OpenCV Headers
#include <cxcore.h>
#include <highgui.h>
#include <cv.h>

//Timer Lib
#include "../3rdPartyLibs/tictoc.h"


#include "AndysOpenCVLib.h"
#include "AndysComputations.h"

// Andy's Libraries
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
	WormPtr->HeadIndex=0;
	WormPtr->TailIndex=0;
	WormPtr->ImgOrig =NULL;
	WormPtr->ImgSmooth =NULL;
	WormPtr->ImgThresh =NULL;

	WormPtr->frameNum=0;
	WormPtr->frameNumCamInternal=0;


	WormPtr->SizeOfImage.height = 0;
	WormPtr->SizeOfImage.width= 0;

	WormPtr->timestamp=0;

	/*** Initialze Worm Memory Storage***/
	InitializeWormMemStorage(WormPtr);

	/**** Allocate Memory for CvSeq ***/
	WormPtr->Boundary=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),WormPtr->MemStorage);
	WormPtr->Centerline=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),WormPtr->MemStorage);



	/*** Create Segmented Worm Object ***/
	WormPtr->Segmented= CreateSegmentedWormStruct();

	/** Position on plate information **/
	WormPtr->stageVelocity=cvPoint(0,0);

	return WormPtr;
}




/*
 *
 * Clears all the Memory and De-Allocates it
 */
void DestroyWormAnalysisDataStruct(WormAnalysisData* Worm){
	DestroySegmentedWormStruct(Worm->Segmented);
	if (Worm->ImgOrig !=NULL)	cvReleaseImage(&(Worm->ImgOrig));
	if (Worm->ImgThresh !=NULL) cvReleaseImage(&(Worm->ImgThresh));
	if (Worm->ImgSmooth !=NULL) cvReleaseImage(&(Worm->ImgSmooth));
	cvReleaseMemStorage(&((Worm)->MemScratchStorage));
	cvReleaseMemStorage(&((Worm)->MemStorage));
	free((Worm)->Segmented);
	free(Worm);
	Worm=NULL;
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
int RefreshWormMemStorage(WormAnalysisData* Worm){
	if (Worm->MemScratchStorage!=NULL){
		cvClearMemStorage(Worm->MemScratchStorage);
	}else{
		printf("Error! MemScratchStorage is NULL in RefreshWormMemStorage()!\n");
		return -1;
	}
	if (Worm->MemStorage!=NULL){
		cvClearMemStorage(Worm->MemStorage);
	} else{
		printf("Error! MemStorage is NULL in RefreshWormMemStorage()!\n");
		return -1;
	}
	return 0;
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

	/** Clear the Time Stamp **/
	Worm->timestamp=0;

}




/*
 * This function is run after IntializeEmptyImages.
 * And it loads a color original into the WormAnalysisData strucutre.
 * The color image is converted to an 8 bit grayscale image.
 *
 * It also sets the time stamp.
 */
void LoadWormColorOriginal(WormAnalysisData* Worm, IplImage* ImgColorOrig){
	CvSize CurrentSize = cvGetSize(ImgColorOrig);
	if ( (Worm->SizeOfImage.height != CurrentSize.height) || (Worm->SizeOfImage.width != CurrentSize.width) ){
		printf("Error. Image size does not match in LoadWormColorOriginal()");
		return;
	}
	cvCvtColor( ImgColorOrig, Worm->ImgOrig, CV_BGR2GRAY);

	/** Set the TimeStamp **/
	Worm->timestamp=clock();

}

/*
 * This function is run after IntializeEmptyImages.
 * And it loads a properly formated 8 bit grayscale image
 * into the WormAnalysisData strucutre.
 *
 * It also sets the timestamp.
 */
int LoadWormImg(WormAnalysisData* Worm, IplImage* Img){
	CvSize CurrentSize = cvGetSize(Img);
	if ( (Worm->SizeOfImage.height != CurrentSize.height) || (Worm->SizeOfImage.width != CurrentSize.width) ){
		printf("Error. Image size does not match in  LoadWormImg()");
		return -1;
	}
	/** Set the TimeStamp **/
	Worm->timestamp=clock();

	/** Copy the Image **/
	cvCopy( Img, Worm->ImgOrig,0);
	return 0;

}

/************************************************************/
/* Creating, Destroying WormAnalysisParam					*/
/*  					 									*/
/*															*/
/************************************************************/

/*
 *  Allocate memory for a WormAnalysisParam struct
 *  And set default values for the parameters.
 */
WormAnalysisParam* CreateWormAnalysisParam(){
	WormAnalysisParam* ParamPtr;
	ParamPtr=(WormAnalysisParam*) malloc(sizeof(WormAnalysisParam));

	/** Turn the System On or Off **/
	ParamPtr->OnOff=0;

	/** Single Frame Analysis Parameters **/
	ParamPtr->BinThresh=48;
	ParamPtr->GaussSize=1;
	ParamPtr->LengthScale=9;
	ParamPtr->LengthOffset=ParamPtr->LengthScale/2;
	ParamPtr->NumSegments=100;

	/** Default WormSpace GridSize **/
	ParamPtr->DefaultGridSize=cvSize(20,ParamPtr->NumSegments);

	/** Frame-to-Frame Temporal Analysis Parameters **/
	ParamPtr->TemporalOn=1;
	ParamPtr->InduceHeadTailFlip=0;

	ParamPtr->MaxLocationChange=70;
	ParamPtr->MaxPerimChange=10;

	/** DIsplay Parameters **/
	ParamPtr->DispRate=1;
	ParamPtr->Display=1;

	/**Illumination Parameters **/
	ParamPtr->SegStart=25;
	ParamPtr->SegStop=40;
	ParamPtr->DLPOn=0;

	ParamPtr->IllumInvert=0;
	ParamPtr->IllumFlipLR=0;
	ParamPtr->IllumSquareOrig=cvPoint(ParamPtr->DefaultGridSize.width/2,ParamPtr->DefaultGridSize.height/2);
	ParamPtr->IllumSquareRad=cvSize(ParamPtr->DefaultGridSize.width/4,ParamPtr->DefaultGridSize.height/4);
	ParamPtr->IllumDuration=15;
	ParamPtr->DLPOnFlash=0;



	ParamPtr->IllumLRC=3;
	ParamPtr->IllumSegRadius=5;
	ParamPtr->IllumSegCenter=25;
	ParamPtr->IllumFloodEverything=0;

	/** Illum Head-Tail Sweep **/
	ParamPtr->IllumSweepHT = 1;
	ParamPtr->IllumSweepOn=0;

	ParamPtr->ProtocolUse=0;
	ParamPtr->ProtocolStep=0;
	ParamPtr->ProtocolTotalSteps=0;

	/** Stage Control Parameters **/
	ParamPtr->stageTrackingOn=0;
	ParamPtr->stageSpeedFactor=25;

	/**Record Parameters **/
	ParamPtr->Record=0;

	return ParamPtr;
}


void DestroyWormAnalysisParam(WormAnalysisParam* ParamPtr){
	free(ParamPtr);
}


/************************************************************/
/* Creating, Destroying SegmentedWormStruct					*/
/*  					 									*/
/*															*/
/************************************************************/

/*
 * Creates a Segmented Worm Struct
 * Creates memory for the associated worm struct
 * and initializes the centerline and L&R boundaries
 * and sets everything else to null
 */
SegmentedWorm* CreateSegmentedWormStruct(){
/** Create a new instance of SegWorm **/
	SegmentedWorm* SegWorm;
SegWorm= (SegmentedWorm*) malloc(sizeof(SegmentedWorm));

SegWorm->Head=(CvPoint*) malloc (sizeof(CvPoint));
SegWorm->Tail=(CvPoint*) malloc (sizeof(CvPoint));

SegWorm->centerOfWorm=(CvPoint*) malloc (sizeof(CvPoint));
SegWorm->NumSegments=0;

/*** Setup Memory storage ***/

SegWorm->MemSegStorage=cvCreateMemStorage(0);

/*** Allocate Memory for the sequences ***/
SegWorm->Centerline=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),SegWorm->MemSegStorage);
SegWorm->LeftBound=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),SegWorm->MemSegStorage);
SegWorm->RightBound=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),SegWorm->MemSegStorage);

return SegWorm;
}

/*
 * Creates a Segmented Worm Struct
 * and utilizes the speicfied memory storage.
 *
 */
SegmentedWorm* CreateSegmentedWormStructReuseMem(CvMemStorage* mem){
/** Create a new instance of SegWorm **/
SegmentedWorm* SegWorm;
SegWorm= (SegmentedWorm*) malloc(sizeof(SegmentedWorm));

SegWorm->Head=NULL;
SegWorm->Tail=NULL;
SegWorm->centerOfWorm=NULL;
SegWorm->NumSegments=0;

/*** Setup Memory storage ***/

SegWorm->MemSegStorage=mem;

/*** Allocate Memory for the sequences ***/
SegWorm->Centerline=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),SegWorm->MemSegStorage);
SegWorm->LeftBound=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),SegWorm->MemSegStorage);
SegWorm->RightBound=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),SegWorm->MemSegStorage);

return SegWorm;
}


void DestroySegmentedWormStruct(SegmentedWorm* SegWorm){
cvReleaseMemStorage(&(SegWorm->MemSegStorage));
free((SegWorm->Head));
free((SegWorm->Tail));
free((SegWorm->centerOfWorm));


free(SegWorm);
}


/** Clear a SegmentedWorm struct but not dallocate memory. **/
void ClearSegmentedInfo(SegmentedWorm* SegWorm){
	//SegWorm->Head=NULL; /** This is probably a mistake **/
	//SegWorm->Tail=NULL; /** This is probably a mistake  because memory is not reallocated later.**/

	if (SegWorm->LeftBound!=NULL){
		cvClearSeq(SegWorm->LeftBound);
	}else{
		printf("SegWorm->LeftBound==NULL");
	}
	if (SegWorm->RightBound!=NULL){
			cvClearSeq(SegWorm->RightBound);
		}else{
			printf("SegWorm->RightBound==NULL");
		}

	if (SegWorm->Centerline!=NULL){
			cvClearSeq(SegWorm->Centerline);
		}else{
			printf("SegWorm->Centerline==NULL");
		}


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
	/** This function currently takes around 5-7 ms **/
	/**
	 * Before I forget.. plan to make this faster by:
	 *  a) using region of interest
	 *  b) decimating to make it smaller (maybe?)
	 *  c) resize
	 *  d) not using CV_GAUSSIAN for smoothing
	 */
	TICTOC::timer().tic("cvSmooth");
	cvSmooth(Worm->ImgOrig,Worm->ImgSmooth,CV_GAUSSIAN,Params->GaussSize*2+1);
	//cvSmooth(Worm->ImgOrig,Worm->ImgSmooth,CV_MEDIAN,Params->GaussSize*2+1);
	//cvSmooth(Worm->ImgOrig,Worm->ImgSmooth,CV_BLUR,Params->GaussSize*2+1,Params->GaussSize*2+1);
	TICTOC::timer().toc("cvSmooth");
	TICTOC::timer().tic("cvThreshold");
	cvThreshold(Worm->ImgSmooth,Worm->ImgThresh,Params->BinThresh,255,CV_THRESH_BINARY );
	TICTOC::timer().toc("cvThreshold");
	CvSeq* contours;
	IplImage* TempImage=cvCreateImage(cvGetSize(Worm->ImgThresh),IPL_DEPTH_8U,1);
	cvCopy(Worm->ImgThresh,TempImage);
	TICTOC::timer().tic("cvFindContours");
	cvFindContours(TempImage,Worm->MemStorage, &contours,sizeof(CvContour),CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE,cvPoint(0,0));
	TICTOC::timer().toc("cvFindContours");
	TICTOC::timer().tic("cvLongestContour");
	if (contours) LongestContour(contours,&(Worm->Boundary));
	TICTOC::timer().toc("cvLongestContour");
	cvReleaseImage(&TempImage);

}


/*
 * Finds the Worm's Head and Tail.
 * Requires Worm->Boundary
 *
 */
int GivenBoundaryFindWormHeadTail(WormAnalysisData* Worm, WormAnalysisParam* Params) {
	if (Worm->Boundary->total < 2*Params->NumSegments) {
		printf("Error in GivenBoundaryFindWormHeadTail(). The Boundary has too few points.");
		return -1;
	}

	/*** Clear Out Scratch Storage ***/
	cvClearMemStorage(Worm->MemScratchStorage);

	/* **********************************************************************/
	/*  Express the Boundary in the form of a series of vectors connecting 	*/
	/*  two pixels a Delta pixels apart.									*/
	/* **********************************************************************/

	/* Create A Matrix to store all of the dot products along the boundary.
	 */
	CvSeq* DotProds= cvCreateSeq(CV_32SC1,sizeof(CvSeq),sizeof(int),Worm->MemScratchStorage);

	//We walk around the boundary using the high-speed reader and writer objects.
	CvSeqReader ForeReader; //ForeReader reads delta pixels ahead
	CvSeqReader Reader; 	//Reader reads delta pixels behind
	CvSeqReader BackReader; //BackReader reads delta pixels behind


	/**** Local Variables ***/
	int i;
	CvPoint* Pt;
	CvPoint* AheadPt;
	CvPoint* BehindPt;
	CvPoint AheadVec;
	CvPoint BehindVec;
	int TotalBPts = Worm->Boundary->total;

	/*** Initializing Read & Write Apparatus ***/
	int AheadPtr=0;
	int BehindPtr=0;
	int Ptr=0;
	int* DotProdPtr;
	int DotProdVal;


	/*
	 * Loop through all the boundary and compute the dot products between the ForeVec and BackVec.
	 *
	 * Note: ForeVec and BackVec have the same "handedness" along the boundary.
	 */
	//printf ("total boundary elements = %d\n", TotalBPts); //debug MHG 10/19/09
	for (i = 0; i < TotalBPts; i++) {
		AheadPtr = (i+Params->LengthScale)%TotalBPts;
		BehindPtr = (i+TotalBPts-Params->LengthScale)%TotalBPts;
		Ptr = (i)%TotalBPts;

		//printf("AheadPtr=%d, BehindPtr=%d,Ptr=%d\n", AheadPtr,BehindPtr,Ptr);


		AheadPt = (CvPoint*) cvGetSeqElem(Worm->Boundary,AheadPtr);
		Pt = (CvPoint*) cvGetSeqElem(Worm->Boundary,Ptr);
		BehindPt=(CvPoint*) cvGetSeqElem(Worm->Boundary,BehindPtr);


		/** Compute the Forward Vector **/
		AheadVec = cvPoint((AheadPt->x) - (Pt->x), (AheadPt->y)
				- (Pt->y));

		/** Compute the Rear Vector **/
		BehindVec= cvPoint((Pt->x) - (BehindPt->x), (Pt->y)
				- (BehindPt->y));

		/** Store the Dot Product in our Mat **/
		DotProdVal=PointDot(&AheadVec,&BehindVec);
		cvSeqPush(DotProds,&DotProdVal); //<--- ANDY CONTINUE HERE!

	//	printf("i= %d, DotProdVal=%d\n", i, DotProdVal);
	//	cvWaitKey(0);

	}


	/* **********************************************************************/
	/*  Find the Tail 													 	*/
	/*  Take dot product of neighboring vectors. Tail is location of		*/
	/*	 smallest dot product												*/
	/* **********************************************************************/


	/*
	 * Now Let's loop through the entire boundary to find the tail, which will be the curviest point.
	 */
	float MostCurvy = 1000; //Smallest value.
	float CurrentCurviness; //Metric of CurrentCurviness. In this case the dot product.
	int MostCurvyIndex = 0;
	int TailIndex;

	for (i = 0; i < TotalBPts; i++) {
		DotProdPtr = (int*) cvGetSeqElem(DotProds,i);
		if (*DotProdPtr < MostCurvy) { //If this locaiton is curvier than the previous MostCurvy location
			MostCurvy = *DotProdPtr; //replace the MostCurvy point
			MostCurvyIndex = i;
		}
	}

	//Set the tail to be the point on the boundary that is most curvy.
	Worm->Tail = (CvPoint*) cvGetSeqElem(Worm->Boundary, MostCurvyIndex);
	Worm->TailIndex=MostCurvyIndex;

	/* **********************************************************************/
	/*  Find the Head 													 	*/
	/* 	Excluding the neighborhood of the Tail, the head is the location of */
	/*	 the smallest dot product											*/
	/* **********************************************************************/

	float SecondMostCurvy = 1000;
	int SecondMostCurvyIndex = 0;
	int DistBetPtsOnBound;
	DistBetPtsOnBound = 0;


	for (i = 0; i < TotalBPts; i++) {
		DotProdPtr =(int*) cvGetSeqElem(DotProds,i);

		DistBetPtsOnBound = DistBetPtsOnCircBound(TotalBPts, i, MostCurvyIndex);
		//If we are at least a 1/4 of the total boundary away from the most curvy point.
		if (DistBetPtsOnBound > (TotalBPts / 4)) {
			//If this location is curvier than the previous SecondMostCurvy location
			if (*DotProdPtr< SecondMostCurvy) {
				SecondMostCurvy = *DotProdPtr; //replace the MostCurvy point
				SecondMostCurvyIndex = i;
			}
		}
	}

	Worm->Head = (CvPoint*) cvGetSeqElem(Worm->Boundary,
			SecondMostCurvyIndex);

	Worm->HeadIndex = SecondMostCurvyIndex;
	cvClearMemStorage(Worm->MemScratchStorage);
	return 0;
}



/*
 * This function reverses the head and the tail of a worm.
 *
 * Note: it does not reverse the sequences that describe the worm's boundary
 * or its segmentation.
 *
 */
int ReverseWormHeadTail(WormAnalysisData* Worm){
	if (Worm->Head==NULL || Worm->Tail==NULL ){
		printf("Error! Head or Tail is NULL in ReverseWormHeadTail().\n");
		return -1;
	}
	CvPoint* tempa=Worm->Head;
	CvPoint* tempb=Worm->Tail;
	int tempindexa=Worm->HeadIndex;
	int tempindexb=Worm->TailIndex;

	/** Reverse Head and Tail **/
	Worm->Head=tempb;
	Worm->Tail=tempa;

	/*** Reverse Head and Tail Index **/
	Worm->HeadIndex=tempindexb;
	Worm->TailIndex=tempindexa;
	return 0;
}





/*
 * DEPRECATED!!
 * This is a Wrapper function for Illuminate Worm Segment
 * It will create an image of a range of segments on both sides of the worm
 *
 * It stores an IplImage in the frame and a binary copy in the frame.
 *
 * It has a lot of copying of images though. Hopefully this won't be too slow.
 *
 */
int SimpleIlluminateWorm(WormAnalysisData* Worm, Frame* IllumFrame,int start, int end){
	IplImage* TempImage=cvCreateImage(Worm->SizeOfImage, IPL_DEPTH_8U, 1);
	if (start>end){
		printf("ERROR: In SimpleIlluminateWorm, start is greater than end! \n");
		return -1;
	}
	if ((start<0)|| (end<0)) {
		printf("ERROR: In SimpleIlluminateWorm, start and end must be greater than 0! \n");
		return -1;
	}

	if ((start > Worm->Segmented->NumSegments)|| (end >Worm->Segmented->NumSegments)) {
			printf("ERROR: Segment Out of Bounds! \n");
			return -1;
		}


	/** Check to See if the Worm->Segmented has any NULL values**/
	if (Worm->Segmented->Centerline==NULL || Worm->Segmented->LeftBound==NULL || Worm->Segmented->RightBound ==NULL ){
		printf("Error! The Worm->Segmented had NULL children. in SimpleIlluminateWorm()\n");
		return -1;
	}

	/** Check to See that the Segmented Values are Not Zero **/
	if (Worm->Segmented->Centerline->total==0 || Worm->Segmented->LeftBound->total==0 || Worm->Segmented->RightBound->total ==0 ){
		printf("Error! At least one of the following: Centerline or Right and Left Boundaries in Worm->Segmented has zero points in SimpleIlluminateWorm()\n");
		return -1;
	}

	int i;
	for (i=start; i<end; i++){
	IlluminateWormSegment(TempImage,Worm->Segmented->Centerline,Worm->Segmented->LeftBound,i);
	IlluminateWormSegment(TempImage,Worm->Segmented->Centerline,Worm->Segmented->RightBound,i);
	}
		LoadFrameWithImage(TempImage,IllumFrame);
	//	cvShowImage("TestOut",IllumFrame);

	cvReleaseImage(&TempImage);
	return 0;
}
/*
 * This is another wrapper for Illuminate Worm.
 * In this paradigm center is the segment with which the illumination centers on
 * radius is the number of segments wide that the illumination encompasses
 * and lrc is either 0,1,2,3 for nothing, left,right,DLP
 */
int SimpleIlluminateWormLR(SegmentedWorm* SegWorm, Frame* IllumFrame,int center, int radius, int lrc){
	IplImage* TempImage=cvCreateImage(cvGetSize(IllumFrame->iplimg), IPL_DEPTH_8U, 1);
	if (0>center || center > SegWorm->NumSegments){
		printf("ERROR: Segmented out of bounds! \n");
		return -1;
	}
//	printf("cente=%d,radius=%d,lrc=%d",center,radius,lrc);
	int endSeg=0;
	int startSeg=0;
	if ( (center+radius) > SegWorm->NumSegments-1){
		endSeg=SegWorm->NumSegments-1;
	}else{
		endSeg=center+radius;
	}

	if ( (center-radius) <0){
		startSeg=0;
	}else{
		startSeg=center-radius;
	}
//	printf("startSeg=%d,endSeg=%d\n",startSeg,endSeg);


	/** Check to See if the SegWorm has any NULL values**/
	if (SegWorm->Centerline==NULL || SegWorm->LeftBound==NULL || SegWorm->RightBound ==NULL ){
		printf("Error! The SegWorm had NULL children. in SimpleIlluminateWorm()\n");
		return -1;
	}

	/** Check to See that the Segmented Values are Not Zero **/
	if (SegWorm->Centerline->total==0 || SegWorm->LeftBound->total==0 || SegWorm->RightBound->total ==0 ){
		printf("Error! At least one of the following: Centerline or Right and Left Boundaries in SegWorm has zero points in SimpleIlluminateWorm()\n");
		return -1;
	}

	int i;
	for (i=startSeg; i<endSeg; i++){
	if (lrc==1 || lrc==3) IlluminateWormSegment(TempImage,SegWorm->Centerline,SegWorm->LeftBound,i);
	if (lrc >1) IlluminateWormSegment(TempImage,SegWorm->Centerline,SegWorm->RightBound,i);
	}
		LoadFrameWithImage(TempImage,IllumFrame);
	//	cvShowImage("TestOut",IllumFrame);

	cvReleaseImage(&TempImage);
	return 0;
}



/*
 * Illuminate a segment of the worm. Either the right, or left side.
 * Takes a sequence of the centerline. Uses the preceeding point to find a vector
 * along the centerline, than draws a rectangle perpendicular to this vector, a radius rsquared pixels
 * away from the centerline
 */
void IlluminateWormSegment(IplImage* image, CvSeq* centerline, CvSeq* Boundary, int segment){
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
	cvFillConvexPoly(image,myPolygon,4,cvScalar(255,255,255),CV_AA);
	//cvShowImage("TestOut",image);
	if (PRINTOUT) printf("After cvFillConvexPoly\n");



}





/*
 * This Function segments a worm.
 * It requires that certain information be present in the WormAnalysisData struct Worm
 * It requires Worm->Boundary be full
 * It requires that Params->NumSegments be greater than zero
 *
 */
int SegmentWorm(WormAnalysisData* Worm, WormAnalysisParam* Params){
	if (cvSeqExists(Worm->Boundary) == 0){
		printf("Error! No boundary found in SegmentWorm()\n");
		return -1;
	}




	Worm->Segmented->NumSegments=Params->NumSegments;

	/***Clear Out any stale Segmented Information Already in the Worm Structure***/
	ClearSegmentedInfo(Worm->Segmented);

	Worm->Segmented->Head=Worm->Head;
	Worm->Segmented->Tail=Worm->Tail;

	/*** It would be nice to check that Worm->Boundary exists ***/

	/*** Clear Out Scratch Storage ***/
	cvClearMemStorage(Worm->MemScratchStorage);


	/*** Slice the boundary into left and right components ***/
	if (Worm->HeadIndex==Worm->TailIndex) printf("Error! Worm->HeadIndex==Worm->TailIndex in SegmentWorm()!\n");
	CvSeq* OrigBoundA=cvSeqSlice(Worm->Boundary,cvSlice(Worm->HeadIndex,Worm->TailIndex),Worm->MemScratchStorage,1);
	CvSeq* OrigBoundB=cvSeqSlice(Worm->Boundary,cvSlice(Worm->TailIndex,Worm->HeadIndex),Worm->MemScratchStorage,1);

	if (OrigBoundA->total < Params->NumSegments || OrigBoundB->total < Params->NumSegments ){
		printf("Error in SegmentWorm():\n\tWhen splitting  the original boundary into two, one or the other has less than the number of desired segments!\n");
		printf("OrigBoundA->total=%d\nOrigBoundB->total=%d\nParams->NumSegments=%d\n",OrigBoundA->total,OrigBoundB->total,Params->NumSegments);
		printf("Worm->HeadIndex=%d\nWorm->TailIndex=%d\n",Worm->HeadIndex,Worm->TailIndex);
		return -1; /** Andy make this return -1 **/

	}

	cvSeqInvert(OrigBoundB);


	/*** Resample One of the Two Boundaries so that both are the same length ***/

	//Create sequences to store the Normalized Boundaries
	CvSeq* NBoundA=	cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),Worm->MemScratchStorage);
	CvSeq* NBoundB=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),Worm->MemScratchStorage);

	//Resample L&R boundary to have the same number of points as min(L,R)
	if (OrigBoundA->total > OrigBoundB->total){
		resampleSeq(OrigBoundA,NBoundA,OrigBoundB->total );
		NBoundB=OrigBoundB;
	}else{
		resampleSeq(OrigBoundB,NBoundB,OrigBoundA->total );
		NBoundA=OrigBoundA;
	}
	//Now both NBoundA and NBoundB are the same length.



	/*
	 * Now Find the Centerline
	 *
	 */

	/*** Clear out Stale Centerline Information ***/
	cvClearSeq(Worm->Centerline);

	/*** Compute Centerline, from Head To Tail ***/
	FindCenterline(NBoundA,NBoundB,Worm->Centerline);



	/*** Smooth the Centerline***/
	CvSeq* SmoothUnresampledCenterline = smoothPtSequence (Worm->Centerline, 0.5*Worm->Centerline->total/Params->NumSegments, Worm->MemScratchStorage);

	/*** Note: If you wanted to you could smooth the centerline a second time here. ***/


	/*** Resample the Centerline So it has the specified Number of Points ***/
	//resampleSeq(SmoothUnresampledCenterline,Worm->Segmented->Centerline,Params->NumSegments);

	resampleSeqConstPtsPerArcLength(SmoothUnresampledCenterline,Worm->Segmented->Centerline,Params->NumSegments);

	/** Save the location of the centerOfWorm as the point halfway down the segmented centerline **/
	Worm->Segmented->centerOfWorm= CV_GET_SEQ_ELEM( CvPoint , Worm->Segmented->Centerline, Worm->Segmented->NumSegments / 2 );

	/*** Remove Repeat Points***/
	//RemoveSequentialDuplicatePoints (Worm->Segmented->Centerline);

	/*** Use Marc's Perpendicular Segmentation Algorithm
	 *   To Segment the Left and Right Boundaries and store them
	 */
	SegmentSides(OrigBoundA,OrigBoundB,Worm->Segmented->Centerline,Worm->Segmented->LeftBound,Worm->Segmented->RightBound);
	return 0;

}


/**
 *
 * Creates the Worm heads up display for monitoring or for saving to disk
 * You must first pass a pointer to an IplImage that has already been allocated and
 * has dimensions of Worm->SizeOfImage
 *
 *
 */
int CreateWormHUDS(IplImage* TempImage, WormAnalysisData* Worm, WormAnalysisParam* Params, Frame* IlluminationFrame){

	int CircleDiameterSize=10;

	/** Overly a translucent image of the illumination pattern**/

	double weighting=0.20; //Alpha blend weighting
	if (Params->DLPOn) weighting=0.45; // if DLP is on make the illumination pattern more opaque
	cvAddWeighted(Worm->ImgOrig,1,IlluminationFrame->iplimg,weighting,0,TempImage);

	//Want to also display boundary!
	cvDrawContours(TempImage, Worm->Boundary, cvScalar(255,0,0),cvScalar(0,255,0),100);

//	DrawSequence(&TempImage,Worm->Segmented->LeftBound);
//	DrawSequence(&TempImage,Worm->Segmented->RightBound);

	cvCircle(TempImage,*(Worm->Tail),CircleDiameterSize,cvScalar(255,255,255),1,CV_AA,0);
	cvCircle(TempImage,*(Worm->Head),CircleDiameterSize/2,cvScalar(255,255,255),1,CV_AA,0);

	/** Prepare Text **/
	CvFont font;
	cvInitFont(&font,CV_FONT_HERSHEY_TRIPLEX ,1.0,1.0,0,2,CV_AA);

	/** Display DLP On Off **/
	if (Params->DLPOn) {
		cvPutText(TempImage,"DLP ON",cvPoint(20,70),&font,cvScalar(255,255,255));
	}
	/** Display Recording if we are recording **/
	if (Params->Record){
		cvPutText(TempImage,"Recording",cvPoint(20,100),&font,cvScalar(255,255,255));

	} else {
		if (Params->DLPOn) cvPutText(TempImage,"Did you forget to record?",cvPoint(20,100),&font,cvScalar(255,255,255));
	}


	/*** Let the user know if the illumination flood light is on ***/
	if (Params->IllumFloodEverything){
		cvPutText(TempImage,"Floodlight",cvPoint(20,130),&font,cvScalar(255,255,255));
	}

	char protoNum[20];
	/** If we are using protocols, display the protocol number **/
	if (Params->ProtocolUse){
		sprintf(protoNum,"Step %d",Params->ProtocolStep);
		cvPutText(TempImage,protoNum,cvPoint(20,160),&font,cvScalar(255,255,255));

	}
	free(protoNum);


	char frame[30];
	sprintf(frame,"%d",Worm->frameNum);
	cvPutText(TempImage,frame,cvPoint(Worm->SizeOfImage.width- 200,Worm->SizeOfImage.height - 10),&font,cvScalar(255,255,255) );
	free( frame);
	return 0;
}


/************************************************************/
/* Monitoring Routines										*/
/* These routines help visualize whats going on.			*/
/*	They also help with debugging							*/
/************************************************************/




/*
 * Displays the original image of the worm
 * highlighting the head and tail
 * And displays the worm's boundary
 *
 */
void DisplayWormHeadTail(WormAnalysisData* Worm, char* WindowName){
	int CircleDiameterSize=10;
	IplImage* TempImage=cvCreateImage(cvGetSize(Worm->ImgSmooth),IPL_DEPTH_8U,1);
	cvCopy(Worm->ImgOrig,TempImage,0);
	//Want to also display boundary!
	cvDrawContours(TempImage, Worm->Boundary, cvScalar(255,0,0),cvScalar(0,255,0),100);
	cvCircle(TempImage,*(Worm->Tail),CircleDiameterSize,cvScalar(255,255,255),1,CV_AA,0);
	cvCircle(TempImage,*(Worm->Head),CircleDiameterSize/2,cvScalar(255,255,255),1,CV_AA,0);
	cvShowImage(WindowName,TempImage);
	cvReleaseImage(&TempImage);
}


/*
 * This function overlays the illumination frame translucently
 * over the original image.
 * It also draws the worm's boundary and the worm's head and tail.
 *
 */
void DisplayWormHUDS(WormAnalysisData* Worm, WormAnalysisParam* Params, Frame* IlluminationFrame,char* WindowName){
	IplImage* TempImage =cvCreateImage(Worm->SizeOfImage,IPL_DEPTH_8U,1);
	CreateWormHUDS(TempImage,Worm,Params,IlluminationFrame);
	cvShowImage(WindowName,TempImage);
	cvReleaseImage(&TempImage);
}



/*
 * Generates the original image of the worm
 * with segmentation
 * And also the head and tail.
 */
void DisplayWormSegmentation(WormAnalysisData* Worm, IplImage* ImgOut){
	IplImage* TempImage=ImgOut;
	cvCopyImage(Worm->ImgOrig,TempImage);

	int i;
	for (i = 0; i < Worm->Segmented->Centerline->total; i++) {
		CvPoint* tempPt = (CvPoint*) cvGetSeqElem(Worm->Segmented->Centerline, i);
		CvPoint* tempPtA = (CvPoint*) cvGetSeqElem(Worm->Segmented->RightBound, i);
		CvPoint* tempPtB = (CvPoint*) cvGetSeqElem(Worm->Segmented->LeftBound, i);
		cvCircle(TempImage, *tempPt, 1, cvScalar(255, 255, 255), 1);
		cvCircle(TempImage, *tempPtA, 1, cvScalar(255, 255, 255), 1);
		cvCircle(TempImage, *tempPtB, 1, cvScalar(255, 255, 255), 1);
		cvDrawContours(TempImage,Worm->Boundary,cvScalar(255,255,255),cvScalar(255,255,255),1,1,CV_AA);

		cvLine(TempImage,*tempPt,*tempPtA,cvScalar(255,255,255),1,CV_AA,0);
		cvLine(TempImage,*tempPt,*tempPtB,cvScalar(255,255,255),1,CV_AA,0);

		int CircleDiameterSize=10;
		cvCircle(TempImage,*(Worm->Tail),CircleDiameterSize,cvScalar(255,255,255),1,CV_AA,0);
		cvCircle(TempImage,*(Worm->Head),CircleDiameterSize/2,cvScalar(255,255,255),1,CV_AA,0);


	}


}


/*
 * Displays the original image and the points of the
 * segmented boundary and then the points of the centerline
 */
void DisplaySegPts(WormAnalysisData* Worm, char* WindowName){
	printf("NEW FRAME============\n");
	IplImage* TempImage=cvCreateImage(cvGetSize(Worm->ImgOrig),IPL_DEPTH_8U,1);
	cvCopyImage(Worm->ImgOrig,TempImage);
	int CircleDiameterSize=10;
	int i;
	printf("Worm->Segmented->Centerline->total=%d\n",Worm->Segmented->Centerline->total);
	for (i = 0; i < Worm->Segmented->Centerline->total; i++) {
		CvPoint* tempPt = (CvPoint*) cvGetSeqElem(Worm->Segmented->Centerline, i);

		cvCircle(TempImage,*tempPt,1,cvScalar(255,255,255),1,CV_AA,0);

		cvWaitKey(30);cvShowImage(WindowName, TempImage); printf("( %d , %d )\n",tempPt->x, tempPt->y);
		}

	printf("Worm->Segmented->RightBound->total=%d\n",Worm->Segmented->RightBound->total);
	for (i = 0; i < Worm->Segmented->RightBound->total; i++) {

		CvPoint* tempPtA = (CvPoint*) cvGetSeqElem(Worm->Segmented->RightBound, i);
		CvPoint* tempPtB = (CvPoint*) cvGetSeqElem(Worm->Segmented->LeftBound, i);

		cvCircle(TempImage,*tempPtA,1,cvScalar(255,255,255),1,CV_AA,0);
		cvCircle(TempImage,*tempPtB,1,cvScalar(255,255,255),1,CV_AA,0);
		cvWaitKey(30);cvShowImage(WindowName, TempImage); printf("A: ( %d, %d ) B: ( %d, %d ) \n",tempPtA->x, tempPtA->y,tempPtB->x, tempPtB->y);
	}

	cvCircle(TempImage,*(Worm->Tail),CircleDiameterSize,cvScalar(255,255,255),1,CV_AA,0);
	cvCircle(TempImage,*(Worm->Head),CircleDiameterSize/2,cvScalar(255,255,255),1,CV_AA,0);

	cvShowImage(WindowName, TempImage);
	///// ANDY DELETE THIS NEXT LINE SOON!!!!
	cvReleaseImage(&TempImage);

}



/*
 * Displays the original image of the worm
 * highlighting the head and tail
 * draws the boundaries and also overlays the illumination
 *
 */
void DisplayIlluminatedWorm(WormAnalysisData* Worm, Frame* IllumFrame,char* WindowName){
	int CircleDiameterSize=10;
	IplImage* TempImage=cvCreateImage(cvGetSize(Worm->ImgOrig),IPL_DEPTH_8U,1);
	cvCopy(Worm->ImgOrig,TempImage,0);
	/** ANDY IMPLEMENTED cvAddWeighted() Here **/
	cvDrawContours(TempImage, Worm->Boundary, cvScalar(255,0,0),cvScalar(0,255,0),100);
	cvCircle(TempImage,*(Worm->Tail),CircleDiameterSize,cvScalar(255,255,255),1,CV_AA,0);
	cvCircle(TempImage,*(Worm->Head),CircleDiameterSize/2,cvScalar(255,255,255),1,CV_AA,0);


	cvShowImage(WindowName,TempImage);
	cvReleaseImage(&TempImage);
}


/**************************************
 *
 * Worm Geometry Object
 *
 * Note this is mostly useful for Temporal Analysis
 *
 */

/* Create a Worm Geometry Object
 *
 */
WormGeom* CreateWormGeom(){
	WormGeom* SimpleWorm= (WormGeom*) malloc(sizeof(WormGeom));
	ClearWormGeom(SimpleWorm);
	return SimpleWorm;

}

/*
 * Set the values inside the Worm Geometry object to NULL
 *
 */
void ClearWormGeom(WormGeom* SimpleWorm){
	if (SimpleWorm==NULL){
			return;
		}
	SimpleWorm->Head.x=0;
	SimpleWorm->Head.y=0;
	SimpleWorm->Perimeter=0;
	SimpleWorm->Tail.x=0;
	SimpleWorm->Tail.y=0;
}

/*
 * Frees the memory allocated to the Worm Geometry object
 * and sets its pointer to NULL
 */
void DestroyWormGeom(WormGeom** SimpleWorm){
	if (*SimpleWorm==NULL) return;
	free(*SimpleWorm);
	*SimpleWorm=NULL;
}

/*
 *Populates LoadWormGeom with geometry data from Worm Object Worm
 */
void LoadWormGeom(WormGeom* SimpleWorm, WormAnalysisData* Worm){
	if (SimpleWorm==NULL){
		printf("Error SimpleWorm is NULL in LoadWormGeom()!\n");
		return;
	}
	ClearWormGeom(SimpleWorm);
	SimpleWorm->Head=*(Worm->Head);
	SimpleWorm->Tail=*(Worm->Tail);
	SimpleWorm->Perimeter=Worm->Boundary->total;
}


/*********************************************
 * Temporal Analysis
 */

/*
 *
 * Returns 1 if the worm is consistent with previous frame.
 * Returns 0 if the worm's head and tail had been reversed from
 *      	  previous frame and fixes the problem.
 * Returns -1 if the head and the tail do not match the previous frame at all
 * Returns 2 if there is no previous worm information
 */
int PrevFrameImproveWormHeadTail(WormAnalysisData* Worm,
		WormAnalysisParam* Params, WormGeom* PrevWorm) {
	int DEBUG = 0;
	if (PrevWorm->Head.x == NULL || PrevWorm->Head.y == NULL
			|| PrevWorm->Tail.y == NULL || PrevWorm->Tail.x == NULL
			|| PrevWorm->Perimeter == NULL) {
		/** No previous worm to provide information **/
		if (DEBUG)
			printf("No previous worm to provide information.\n");
		return 2;
	}


	/** Is the Worm's Head and Tail Close to the Previous Frames **/
	CvPoint CurrHead=cvPoint(Worm->Head->x,Worm->Head->y);
	CvPoint CurrTail=cvPoint(Worm->Tail->x,Worm->Tail->y);
	int SqDeltaHead  = sqDist(CurrHead, PrevWorm->Head);
	int SqDeltaTail = sqDist(CurrTail, PrevWorm->Tail);
	if (DEBUG) printf("=======================\n");
	if (DEBUG) printf("CurrHead=(%d,%d),CurrTail=(%d,%d)\n",Worm->Head->x,Worm->Head->y,Worm->Tail->x,Worm->Tail->y);
	if (DEBUG) printf("PrevHead=(%d,%d),PrevTail=(%d,%d)\n",PrevWorm->Head.x,PrevWorm->Head.y,PrevWorm->Tail.x,PrevWorm->Tail.y);
	if (DEBUG) printf("SqDeltaTail=%d,SqDeltaHead=%d\n",SqDeltaTail,SqDeltaHead);

	int rsquared=(Params->MaxLocationChange) * (Params->MaxLocationChange);

	if ((SqDeltaHead > rsquared) || (SqDeltaTail > rsquared)) {
		/** The previous head/tail locations aren't close.. **/
		/** Is the inverse close? **/
		int SqDeltaHeadInv = sqDist(CurrHead, PrevWorm->Tail);
		int SqDeltaTailInv = sqDist(CurrTail, PrevWorm->Head);
		if (DEBUG) printf("SqDeltaTailInv=%d,SqDeltaHeadInv=%d\n",SqDeltaTailInv,SqDeltaTailInv);
		if ( (SqDeltaHeadInv < rsquared) || (SqDeltaTailInv < rsquared )){
			/** The inverse is close, so let's reverse the Head Tail**/
			ReverseWormHeadTail(Worm);
			if (DEBUG) printf("ReversedWormHeadTail\n");
			return 0;

		} else {
			/** The Head and Tail is screwed up and its not related to simply inverted **/
			if (DEBUG) printf(
					"Head moved by a squared distance of %d pixels\n Tail moved by a squared distance of %d pixels\n",
					SqDeltaHead, SqDeltaTail);
			if (DEBUG)
				printf("Head and Tail Screwed Up");
			return -1;

		}
	}
	if (DEBUG)
			printf("All good.\n");
	return 1; /** The Head and Tail are within the required distance **/

}


/*
 * Converts the slider bar used to specify an origin into a coordinate on wormspace.
 *
 */
CvPoint ConvertSlidlerToWormSpace(CvPoint SliderOrigin,CvSize gridSize){
	return cvPoint( SliderOrigin.x- ( gridSize.width / 2 ) , SliderOrigin.y  );
}


