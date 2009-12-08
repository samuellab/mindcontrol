/*
 * IllumWormProtocol.h
 *
 *  Created on: Nov 11, 2009
 *      Author: Andy
 */

#ifndef ILLUMWORMPROTOCOL_H_
#define ILLUMWORMPROTOCOL_H_


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



void DestroyProtocolObject(Protocol** MyProto);

void LoadProtocolWithFilename(const char* str, Protocol* myP);

void LoadProtocolWithDescription(const char* str, Protocol* myP);






/*
 * Write everything out to YAML
 *
 */
void WriteProtocolToYAML(Protocol* myP);

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




#endif /* ILLUMWORMPROTOCOL_H_ */
