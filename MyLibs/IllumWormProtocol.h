/*
 * IllumWormProtocol.h
 *
 * Depends on WormAnalysis.h
 * which depends on AndysOpenCVLib.h
 *
 *  Created on: Nov 11, 2009
 *      Author: Andy
 */

#ifndef ILLUMWORMPROTOCOL_H_
#define ILLUMWORMPROTOCOL_H_


#ifndef WORMANALYSIS_H_
 #error "#include WormAnalysis.h" must appear in source files before "#include IllumWormProtocol.h"
#endif


typedef struct ProtocolStruct{
	CvSize GridSize;//height is length of worm
					//width is width of worm
	char* Filename;
	char* Description;
	CvSeq* Steps;
	CvMemStorage* memory;

}Protocol;

typedef struct WormPolygonStruct{
	CvSize GridSize; //height is length of worm
					//width is width of worm
	CvSeq* Points;
}WormPolygon;




/*******************************************/
/*
 * Protocol Objects
 */
/*******************************************/

/*
 * Create a Protocol Object and set all of its values to zero or NULL
 * The Protocol object has some descriptions and a CvSeq object that
 * points to sequences of polygons for illumination.
 * Each step can contain an arbitrary number of polygons.
 * Each polygon can contain an arbitrary number of points.
 *
 */
Protocol* CreateProtocolObject();



int VerifyProtocol(Protocol* p);

void DestroyProtocolObject(Protocol** MyProto);

void LoadProtocolWithFilename(const char* str, Protocol* myP);

void LoadProtocolWithDescription(const char* str, Protocol* myP);






/*
 * Write everything out to its own YAML file
 *
 */
void WriteProtocolToYAML(Protocol* myP);

/**
 * Write out a Protocol to YAML file, given an initialized CvFileStorage
 */
void WriteProtocol(Protocol* myP, CvFileStorage* fs);


/*******************************************/
/*
 * Steps Objects
 */
/*******************************************/


/*
 * A steps object is a cvSeq containing pointers to
 * Illumination Montages (whcih are in turn cvSeq's of pointers to Polygons).
 *
 */
CvSeq* CreateStepsObject(CvMemStorage* memory);



/*******************************************/
/*
 * Illumination Objects
 */
/*******************************************/

/*
 * An illumination montage consists of a sequence of pointers to polygons
 *
 */
CvSeq* CreateIlluminationMontage(CvMemStorage* memory);



/*******************************************/
/*
 * Polygon Objects
 */
/*******************************************/

/*******************************************/
/*
 * Polygon Objects
 */
/*******************************************/

/*
 * Given a memory object, this will create a polygon object that is a CvSeq.
 *
 */
WormPolygon* CreateWormPolygon(CvMemStorage* memory,CvSize mySize);

/*
 *
 * Creates a worm polygon object from a CvSeq of Points.
 * This will clone the CvSeq and copy it into the memory storage
 * specified
 */
WormPolygon* CreateWormPolygonFromSeq(CvMemStorage* memory,CvSize GridSize,CvSeq* points);

/*
 * Destroys a polygon but doesn't free up the CvMemStorage that that polygon used
 *
 */
void DestroyWormPolygon(WormPolygon** myPoly);


/*******************************************/
/*
 * Misc
 */
/*******************************************/


/*
 * Simple function to copy a string
 */
char *copyString (const char *src);


/************************************
 *
 * Illumination Routines
 *
 */


/*
 * Returns a pointer to a montage of illumination polygons
 * corresponding to a specific protocol step.
 *
 * NOTE: all polygons have been converted into contours so that they
 * have at least one vertex per grid point on the worm-grid
 */
CvSeq* GetMontageFromProtocolInterp(Protocol* p, int step);
/*
 * This function makes a black image.
 *
 */
IplImage* GenerateRectangleWorm(CvSize size);

/*
 * Illuminate a rectangle worm
 */
void IllumRectWorm(IplImage* rectWorm,Protocol* p,int step);

/*
 * Creates an illumination image in image space
 * according to an illumination montage.
 *
 * To use with protocol, use GetMontageFromProtocolInterp() first
 */
void IllumWorm(SegmentedWorm* segworm, CvSeq* IllumMontage, IplImage* img,CvSize gridSize);


/************************************************
 *
 *
 * VERY HIGH LEVEL
 *
 */


/*
 * Illuminate the Segmented worm using the protocol in p
 * with step specified in Params->ProtocolStep
 *
 * and writing to dest
 */
int IlluminateFromProtocol(SegmentedWorm* SegWorm,Frame* dest, Protocol* p,WormAnalysisParam* Params);


/*****************
 * File INput Output
 *
 */

/*
 * Load a  Protocol From yaml File
 *
 */
Protocol* LoadProtocolFromFile(const char* filename);



#endif /* ILLUMWORMPROTOCOL_H_ */
