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

#ifndef ANDYSOPENCVLIB_H_
 #error "#include AndysOpenCVLib.h" must appear in source files before "#include WormAnalysis.h"
#endif


typedef struct WormAnalysisParamStruct{
	/** Turn Analysis On Generally **/
	int OnOff;



	/** Single Frame Analysis Parameters**/
	int LengthScale;
	int LengthOffset;
	int BinThresh;
	int GaussSize;
	int NumSegments;

	/** Frame to Frame Temporal Analysis**/
	int TemporalOn;
	int InduceHeadTailFlip;

	int MaxLocationChange;
	int MaxPerimChange;

	/** Display Stuff**/
	int DispRate; //Deprecated
	int Display;

	/** Defaul Wormspace GridSize for illumination **/
	CvSize DefaultGridSize;


	/** Illumination Parameters **/
	int IllumSegCenter; // Deprecated
	int IllumSegRadius; // Deprecated
	int IllumLRC; // Deprecated
	int SegStart; // Deprecated
	int SegStop; // Deprecated




	int IllumInvert;
	int IllumFlipLR;
	CvPoint IllumSquareOrig; // rectangular cursor location
	CvSize IllumSquareRad; //  rectangular cursor size
	int IllumFloodEverything;
	int DLPOn;

	/** Illumination Head to Tail Sweep **/
	int IllumSweepHT; // head or tail direction
	int IllumSweepOn;

	/** Timed DLP On **/
	int IllumDuration; // in tenthsOfSeconds
	int DLPOnFlash;

	int ProtocolUse;
	int ProtocolStep;
	int ProtocolTotalSteps;

	/** Stage Control Parameters **/
	int stageTrackingOn;
	int stageSpeedFactor;

	/** Record Data Parameters **/
	int Record;

} WormAnalysisParam;

typedef struct SegmentedWormStruct{
	CvSeq* Centerline;
	CvSeq* LeftBound;
	CvSeq* RightBound;
	CvPoint* Head;
	CvPoint* Tail;
	CvMemStorage* MemSegStorage;
	int NumSegments;
	CvPoint* centerOfWorm;
} SegmentedWorm;





typedef struct WormImageAnalysisStruct{
	CvSize SizeOfImage;

	/** Frame Info **/
	int frameNum;
	int frameNumCamInternal;

	/** Images **/
	IplImage* ImgOrig;
	IplImage* ImgSmooth;
	IplImage* ImgThresh;

	/** Memory **/
	CvMemStorage* MemStorage;
	CvMemStorage* MemScratchStorage;

	/** Features **/
	CvSeq* Boundary;
	CvPoint* Head;
	CvPoint* Tail;
	int TailIndex;
	int HeadIndex;
	CvSeq* Centerline;

	/** TimeStamp **/
	unsigned long timestamp;

	/** Segmented Worm **/
	SegmentedWorm* Segmented;

	/** Information about location on plate **/
	CvPoint stageVelocity; //compensating velocity of stage.


	//WormIlluminationData* Illum;
}WormAnalysisData;



/*
 * Struct to hold basic geometric information about
 * the location of the previous worm
 *
 * This can be used in combination with the
 * Parameters->PersistantOn=1 to do frame-to-frame
 * intelligent temporal error checking
 *
 *
 */
typedef struct WormGeomStruct{
	CvPoint Head;
	CvPoint Tail;
	int Perimeter;
}WormGeom;


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

/*
 * Creates a Segmented Worm Struct
 * and utilizes the speicfied memory storage.
 *
 */
SegmentedWorm* CreateSegmentedWormStructReuseMem(CvMemStorage* mem);

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
 * This function reverses the head and the tail of a worm.
 *
 * Note: it does not reverse the sequences that describe the worm's boundary
 * or its segmentation.
 *
 */
int ReverseWormHeadTail(WormAnalysisData* Worm);


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
 * This is another wrapper for Illuminate Worm.
 * In this paradigm center is the segment with which the illumination centers on
 * radius is the number of segments wide that the illumination encompasses
 * and lrc is either 0,1,2,3 for nothing, left,right,DLP
 */
int SimpleIlluminateWormLR(SegmentedWorm* SegWorm, Frame* IllumFrame,int center, int radius, int lrc);

/*
 * This Function segments a worm.
 * It requires that certain information be present in the WormAnalysisData struct Worm
 * It requires Worm->Boundary be full
 * It requires that Params->NumSegments be greater than zero
 *
 */
int SegmentWorm(WormAnalysisData* Worm, WormAnalysisParam* Params);


/**
 *
 * Creates the Worm heads up display for monitoring or for saving to disk
 * You must first pass a pointer to an IplImage that has already been allocated and
 * has dimensions of Worm->SizeOfImage
 *
 *
 */
int CreateWormHUDS(IplImage* TempImage, WormAnalysisData* Worm, WormAnalysisParam* Params, Frame* IlluminationFrame);

/*****************************************
 *
 * Monitoring functions
 *
 */

/*
 * Displays the original image of the worm
 * highlighting the head and tail in the window WindowName
 *
 */
void DisplayWormHeadTail(WormAnalysisData* Worm, char* WindowName);

/*
 * This function overlays the illumination frame translucently
 * over the original image.
 * It also draws the worm's boundary and the worm's head and tail.
 *
 */
void DisplayWormHUDS(WormAnalysisData* Worm, WormAnalysisParam* Params, Frame* IlluminationFrame,char* WindowName);

/*
 * Generates the original image of the worm
 * with segmentation
 * And also the head and tail.
 */
void DisplayWormSegmentation(WormAnalysisData* Worm, IplImage* ImgOut);


/*
 * Displays the original image and the points of the
 * segmented boundary and then the points of the centerline
 */
void DisplaySegPts(WormAnalysisData* Worm, char* WindowName);


/*****
 * Function related to the simpler Worm Geometery OBject
 */

/* Create a Worm Geometry Object
 *
 */
WormGeom* CreateWormGeom();

/*
 * Set the values inside the Worm Geometry object to NULL
 *
 */
void ClearWormGeom(WormGeom* SimpleWorm);

/*
 * Frees the memory allocated to the Worm Geometry object
 * and sets its pointer to NULL
 */
void DestroyWormGeom(WormGeom** SimpleWorm);

/*
 *Populates LoadWormGeom with geometry data from Worm Object Worm
 */
void LoadWormGeom(WormGeom* SimpleWorm, WormAnalysisData* Worm);

/***********************
 * Temporal Analysis Tools
 *
 */

/*
 *
 * Returns 1 if the worm is consistent with previous frame.
 * Returns 0 if the worm's head and tail had been reversed from
 *      	  previous frame and fixes the problem.
 * Returns -1 if the head and the tail do not match the previous frame at all
 * Returns 2 if there is no previous worm information
 */
int PrevFrameImproveWormHeadTail(WormAnalysisData* Worm, WormAnalysisParam* Params, WormGeom* PrevWorm);

/*
 * Converts the slider bar used to specify an origin into a coordinate on wormspace.
 *
 */
CvPoint ConvertSlidlerToWormSpace(CvPoint SliderOrigin,CvSize gridSize);



#endif /* WORMANALYSIS_H_ */
