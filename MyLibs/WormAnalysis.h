/*
 * WormAnalysis.h
 *
 *  Created on: Oct 12, 2009
 *      Author: andy
 *
 *      This library contains functions that are specific to analyzing worms.
 *
 *      Functions in this library depend on:
 *      	AndysOpenCVLib.h
 *      	AndysComputations.h
 */

#ifndef WORMANALYSIS_H_
#define WORMANALYSIS_H_

typedef struct WormAnalysisParamStruct{
	int LengthScale;
	int LengthOffset;
	int BinThresh;
	int GaussSize;
	int NumSegments;
} WormAnalysisParam;

typedef struct SegmentedWormStruct{
	CvSeq* Centerline;
	CvSeq* LeftBound;
	CvSeq* RightBound;
	CvPoint* Head;
	CvPoint* Tail;
	CvMemStorage* MemSegStorage;
	int NumSegments;
} SegmentedWorm;


typedef struct WormImageAnalysisStruct{
	CvSize SizeOfImage;
	IplImage* ImgOrig;
	IplImage* ImgSmooth;
	IplImage* ImgThresh;
	CvMemStorage* MemStorage;
	CvMemStorage* MemScratchStorage;
	CvSeq* Boundary;
	CvPoint* Head;
	CvPoint* Tail;
	int TailIndex;
	int HeadIndex;
	CvSeq* Centerline;
	SegmentedWorm* Segmented;
}WormAnalysisData;


typedef struct WormIlluminationStcut{
	IplImage* IlluminationPattern;
	CvSeq* SegmentCenterline;
	CvSeq* SegmentLeft;
	CvSeq* SegmentRight;
	int* IlluminationArr;
}WormIlluminationData;



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
WormAnalysisData* CreateWormAnalysisDataStruct();




/*
 *
 * Clear's all the Memory and De-Allocates it
 */
void DestroyWormAnalysisDataStruct(WormAnalysisData* WormPtr);



/*
 * Create dynamic memory storage for the worm
 *
 */
void InitializeWormMemStorage(WormAnalysisData* Worm);

/*
 * Refersh dynamic memory storage for the worm
 * (clear the memory without freing it)
 *
 */
int RefreshWormMemStorage(WormAnalysisData* Worm);


/*
 * Clear and de-allocate the memory storage for the worm
 *
 */
void DeallocateWormMemStorage(WormAnalysisData* Worm);


/*
 * Create Blank Images for WormAnalysisData given the image size.
 *
 */
void InitializeEmptyWormImages(WormAnalysisData* Worm, CvSize ImageSize);

/*
 * This function is run after IntializeEmptyImages.
 * And it loads a color original into the WoirmAnalysisData strucutre.
 * The color image is converted to an 8 bit grayscale.
 *
 *
 */
void LoadWormColorOriginal(WormAnalysisData* Worm, IplImage* ImgColorOrig);


/*
 * This function is run after IntializeEmptyImages.
 * And it loads a properly formated 8 bit grayscale image
 * into the WormAnalysisData strucutre.
 */
int LoadWormImg(WormAnalysisData* Worm, IplImage* Img);



/************************************************************/
/* Creating, Destroying WormAnalysisParam					*/
/*  					 									*/
/*															*/
/************************************************************/

/*
 *  Allocate memory for a WormAnalysisParam struct
 */
WormAnalysisParam* CreateWormAnalysisParam();

void DestroyWormAnalysisParam(WormAnalysisParam* ParamPtr);


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
SegmentedWorm* CreateSegmentedWormStruct();

void DestroySegmentedWormStruct(SegmentedWorm* SegWorm);

/*
 * Clears information from an already allocated segmented worm
 * Data object.
 */
void ClearSegmentedInfo(SegmentedWorm* SegWorm);

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
void FindWormBoundary(WormAnalysisData* Worm, WormAnalysisParam* WormParams);





/*
 * Finds the Worm's Head and Tail.
 * Requires Worm->Boundary
 *
 */
int GivenBoundaryFindWormHeadTail(WormAnalysisData* Worm, WormAnalysisParam* Params);


/*
 * This is a Wrapper function for Illuminate Worm Segment
 * It will create an image of a range of segments on both sides of the worm
 *
 * It stores an IplImage in the frame and a binary copy in the frame.
 *
 * It has a lot of copying of images though. Hopefully this won't be too slow.
 *
 */
int SimpleIlluminateWorm(WormAnalysisData* Worm, Frame* IllumFrame,int start, int end);

/*
 * Illuminate a segment of the worm. Either the right, or left side.
 * Takes a sequence of the centerline. Uses the preceeding point to find a vector
 * along the centerline, than draws a rectangle perpendicular to this vector, a radius rsquared pixels
 * away from the centerline
 */
void IlluminateWormSegment(IplImage* image, CvSeq* centerline, CvSeq* Boundary, int segment);



/*
 * This Function segments a worm.
 * It requires that certain information be present in the WormAnalysisData struct Worm
 * It requires Worm->Boundary be full
 * It requires that Params->NumSegments be greater than zero
 *
 */
int SegmentWorm(WormAnalysisData* Worm, WormAnalysisParam* Params);


/*
 * Displays the original image of the worm
 * highlighting the head and tail in the window WindowName
 *
 */
void DisplayWormHeadTail(WormAnalysisData* Worm, char* WindowName);

/*
 * Displays the original image of the worm
 * with segmentation in window WindowName
 *
 */
void DisplayWormSegmentation(WormAnalysisData* Worm, char* WindowName);


#endif /* WORMANALYSIS_H_ */
