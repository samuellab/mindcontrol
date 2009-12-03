/*
 * WormIllumProtocol.c
 *
 * This library is designed to have objects and functions used to
 * write, analyze and excecute illumination protocols written for worms.
 *
 * As such it relies on the high level WormAnalysis library.
 * But Other libraries like WriteOutWorm likely depend upon it.
 *
 *
 *  Created on: Nov 11, 2009
 *      Author: Andy
 */

#include <stdio.h>
#include <time.h>

//OpenCV Headers
#include <cxcore.h>
#include <highgui.h>
#include <cv.h>

// Andy's Libraries

#include "AndysOpenCVLib.h"
#include "WormAnalysis.h"
#include "IllumWormProtocol.h"



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
Protocol* CreateProtocol(){
	Protocol* MyProto= (Protocol*) malloc(sizeof(Protocol*));
	MyProto->GridSize.height=0;
	MyProto->GridSize.width=0;
	MyProto->ProtocolFilename=NULL;
	MyProto->data=NULL;
	MyProto->memory=cvCreateMemStorage();
}



void DestroyProtocol(Protocol** MyProto){
	/** **/
	/** if BLAH is not NULL release BLAH **/

	cvReleaseMemStorage((*MyProto)->memory);
	free(MyProto);
	*MyProto=NULL;
}








/*******************************************/
/*
 * Illumination Objects
 */
/*******************************************/

/*
 * An illumination montage consists of a sequence of pointers to polygons
 *
 */
CvSeq* CreateIlluminationMontage(CvMemStorage* memory){
	CvSeq* myIllumMontage=cvCreateSeq(CV_SEQ_ELTYPE_PTR,sizeof(CvSeq),sizeof(CvSeq*),memory);
}



/*******************************************/
/*
 * Polygon Objects
 */
/*******************************************/

/*
 * Given a memory object, this will create a polygon object that is a CvSeq.
 *
 */
CvSeq* CreatePolygon(CvMemStorage* memory){
	CvSeq* myPoly=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),memory);
}




