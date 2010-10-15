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
 * This function generates an illumination montage containing a square in worm space
 * at a location specified.
 *
 * This function is most useful when it takes input from a slider bar.
 *
 * In that manner the user can specify a rectangular (in worm space) region of illumination
 * at run time.
 *
 */
int GenerateSimpleIllumMontage(CvSeq* montage, CvPoint origin, CvSize radius, CvSize gridSize);


/*
 * Illuminate a rectangle worm
 */
void IllumRectWorm(IplImage* rectWorm,Protocol* p,int step,int FlipLR);

/*
 * Creates an illumination image in image space
 * according to an illumination montage.
 *
 * To use with protocol, use GetMontageFromProtocolInterp() first
 *
 * When FlipLR is set to 1, the illumination pattern is reflected across the worm's centerline.
 */
void IllumWorm(SegmentedWorm* segworm, CvSeq* IllumMontage, IplImage* img,CvSize gridSize, int FlipLR);


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
