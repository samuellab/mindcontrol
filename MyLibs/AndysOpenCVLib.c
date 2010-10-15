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
 * AndysOpenCVLib.c
 *
 *  Created on: July 13, 2009
 *      Author: Andy
 */

#include <highgui.h>
#include <cxcore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AndysOpenCVLib.h"
#include <limits.h>

#define PRINTOUT 0



/***************************************************************
 * Private Functions
 ***************************************************************
 */


/*
 * The compartive function used to sort a sequence of points by their y value
 *
 */
static int cmp_funcy( const void* _a, const void* _b, void* userdata );


/*
 * The compartive function used to sort a sequence of points by their x value
 *
 */
static int cmp_funcx( const void* _a, const void* _b, void* userdata );

/*
 * The compartive function used to sort a sequence of points by their y value
 *
 */




/*
 * Draws a square on "image" with radius "radius" centered on point "pt"
 * If any part of the square would fall outside of the image, than the function doesn't do anything.
 */
void SafeDrawSquare(IplImage** image, CvPoint* pt, int radius){
	IplImage* img = *image;
	int nsizey=img->height;
	int nsizex=img->width;
	if (   ((pt->x+radius)< nsizex ) &&(  (pt->x-radius)> 0 )&& ((pt->y+radius)< nsizey ) && (  (pt->y-radius)> 0) ){
	cvRectangle(img,cvPoint( (pt->x)-radius ,(pt->y)-radius ), cvPoint( (pt->x)+radius ,(pt->y)+radius ),CV_RGB( 255, 255, 255 ),1,8,0 );
	}else{
		printf("square off screen in SafeDrawSquare()");
	}
}




static int cmp_funcy( const void* _a, const void* _b, void* userdata )
{
    CvPoint* a = (CvPoint*)_a;
    CvPoint* b = (CvPoint*)_b;
    int y_diff = a->y - b->y;
    return y_diff;
}

/*
 * The compartive function used to sort a sequence of points by their x value
 *
 */

static int cmp_funcx( const void* _a, const void* _b, void* userdata )
{
    CvPoint* a = (CvPoint*)_a;
    CvPoint* b = (CvPoint*)_b;
    int x_diff = a->x - b->x;
    return x_diff;
}



/***************************************************************
 * Working with the Frame Data Type
 ***************************************************************
 */

/*
 * Creates a frame. Allocates memory for frame structure.
 * Allocates memory for binary image.
 * Allocates memory for IplImage
 *
 */
Frame* CreateFrame(CvSize size){
	/*** Allocate memory for the Frame OBject ***/
	Frame* myFrame = (Frame*) malloc(sizeof(Frame));
	myFrame->size=size;

	/*** Allocate memory for the image ***/
	myFrame->binary=(unsigned char *) malloc(size.width* size.height * sizeof(unsigned char));
	myFrame->iplimg=cvCreateImage(size, IPL_DEPTH_8U, 1);

	/*** Set Binary Image to Zero ***/
	int count=0;
	while (count < myFrame->size.height * myFrame->size.width * sizeof(char)) {
		myFrame->binary[count] = 0;
		count++;
	}
	return myFrame;
}

/*
 * Destroys a frame.
 * Deallocates memory for binary image.
 * Deallocates memory for IplImage
 * Deallocates memory for Frame structure
 * Set's myFrame pointer to null.
 */
void DestroyFrame(Frame** myFrame){
	cvReleaseImage(&( (*myFrame)->iplimg));
	free( (*myFrame)->binary);
	free(*myFrame);
	*myFrame=NULL;
}

/*
 * RefreshFrame
 *
 * This function sets all of the pixels of a frame to zero
 * in both the iplImage and binary representations of the frame.
 */
void RefreshFrame(Frame* myFrame){
	cvSetZero(myFrame->iplimg);
	LoadFrameWithImage(myFrame->iplimg,myFrame);
}

/*
 * Load the Frame with a Binary Image
 *
 * copies the binary image into the frame's memory and
 * then copies the charArray to an iplImage and stores that
 * in the frame also
 *
 * NOTE: the binary image must have size myFrame->size
 *
 */
void LoadFrameWithBin(unsigned char* binsrc, Frame* myFrame){
	memcpy(myFrame->binary, binsrc, myFrame->size.width * myFrame->size.height * sizeof(unsigned char));
	CopyCharArrayToIplImage(myFrame->binary, myFrame->iplimg, myFrame->size.width, myFrame->size.height);
}

/*
 * Load the Frame with a IplImage
 *
 * copies the IplImage into the frame's memory and
 * then converts it to a binary image and stores that
 * in the frame also
 *
 * NOTE: the image must have size myFrame->size
 *
 */
void LoadFrameWithImage(IplImage* imgsrc, Frame* myFrame){
	if (imgsrc->height!=myFrame->iplimg->height || imgsrc->width!=myFrame->iplimg->width ){
		printf(" imgsrc->height=%d\n",imgsrc->height);
		printf(" myFrame->iplimg->height=%d\n",myFrame->iplimg->height);
		printf(" imgsrc->width=%d\n",imgsrc->width);
		printf(" myFrame->iplimg->width=%d\n",myFrame->iplimg->width);
		printf("ERROR!!! Trying to load images of one size into a frame of another size.\n");
		return;
	}

	cvCopy(imgsrc,myFrame->iplimg,0);
	copyIplImageToCharArray(myFrame->iplimg,myFrame->binary);
}


/*
 * This function sets all the pixels to the specified value for both the binary and iplimage
 * component of a frame
 *
 */
void SetFrame(Frame* myFrame, int value){
	/** Set all the pixels to value**/
	cvSet(myFrame->iplimg,cvScalar(value),(CvArr *) NULL);
	copyIplImageToCharArray(myFrame->iplimg,myFrame->binary);
}




/***************************************************************
 * Conversions to and From IplImage to CharArray
 ***************************************************************
 */



/*
 * copies the 8 bit image data in src to the character array arr
 * arr must be preallocated and be src->width*src->height in size
 */

void copyIplImageToCharArray(const IplImage *src, unsigned char *arr) {
	int i;
	if (src == NULL || arr == NULL) {
		printf("NULL passed to copyIplImageToCharArray\n");
		return;
	}
//	*arr = (unsigned char*) malloc(src->width * src->height
//			* sizeof(unsigned char));
	for (i = 0; i < src->height; i++) {
		memcpy(arr + i * src->width, src->imageData + i * src->widthStep,
				src->width);
	}

}

/*
 * Copies an unsigned character array into an allocated iplImage
 * fails if dst->width != nsizex or dst->height != nsizey
 *
 */
int CopyCharArrayToIplImage(const unsigned char *arr, IplImage *dest,  int nsizex,
		int nsizey) {
	int i;
	if (arr == NULL || dest == NULL) {
		printf("NULL passed to CharArrayToIplImage\n");
		return -1;
	}
	if (dest->width != nsizex || dest->height != nsizey) {
		printf("dimension mismatch in copychararraytoiplimage");
		return -1;
	}
	//dest = cvCreateImage(cvSize(nsizex, nsizey), IPL_DEPTH_8U, 1);
	for (i = 0; i < dest->height; i++) {
		memcpy(dest->imageData + i * dest->widthStep, arr + i*dest->width, dest->width);
	}
	return 0;
}

/**************************************************************
 * Useful OpenCv shortcuts
 *
 *
 */

/*
 * Prints out some input, like whether the Intel Performance Primitives are installed
 *
 */
void DisplayOpenCVInstall(){
	char* libraries;
	char* modules;
	cvGetModuleInfo(0, (const char**) &libraries, (const char**) &modules);
	printf("Libraries: %s\nModules: %s\n", libraries, modules);
}

/*
 *
 * Given a sequence of x,y CvPoints, this function returns a point
 * containing the mean x and mean y values of the points.
 *
 */
CvPoint  GetMedianOfPoints(CvSeq* seq){
		if (seq==NULL){
			printf("ERROR. seq is null");
			return cvPoint(-1,-1);
		}
		if (seq->total==0){
			printf("ERROR in GetMedianOfPoints. seq has no elements!");
			return cvPoint(-1,-1);
		}

		int xmed;
		int ymed;
		int midpoint=0;
		if (seq->total > 1) {
			midpoint= (int) (seq->total/2);
		}


		cvSeqSort( seq, cmp_funcy, 0 /* userdata is not used here */ );
		CvPoint* pt=(CvPoint*) cvGetSeqElem( seq, midpoint);
		ymed=pt->y;
		cvSeqSort( seq, cmp_funcx, 0 /* userdata is not used here */ );
		pt=(CvPoint*) cvGetSeqElem( seq, midpoint);
		xmed=pt->x;
		return cvPoint(xmed,ymed);
}



/*
 * Given a list of contours, this finds the contour with the longest perimiter and points ContourOfInterst to this contour.
 *
 * Note this uses the same memory storage for the contourOfInterst, as that of the contour.
*/
void LongestContour(CvSeq* contours, CvSeq** ContourOfInterest){
	CvSeq* biggestContour;
	//printf("---Finding Longest Contour---\n");
	int biggest=0;
		for (contours; contours!=NULL; contours=contours->h_next){
		//printf("%d elements\n",contours->total);
		if (contours->total > biggest){
			biggest=contours->total;
			biggestContour=contours;
			//printf("Currently the biggest!\n");
		}
	}
	*ContourOfInterest=cvCloneSeq(biggestContour);
}

/*
 * Takes the cross product of two vectors representated in cartesian coordinates as CvPoint (x,y)
 *
 */
int PointCross(CvPoint* VecA, CvPoint* VecB){
	return (VecA->x)*(VecB->y) - (VecA->y)*(VecB->x);

}




/*
 * Takes the dot product of two vectors representated in cartesian coordinates as CvPoint (x,y)
 *
 */
int PointDot(CvPoint* VecA, CvPoint* VecB){
	return (VecA->x)*(VecB->x) + (VecA->y)*(VecB->y);

}


/*
 * Normalizes vectors representated in cartesian coordinates as CvPoint (x,y) and takes the cross product.
 *
 */
float NormPointCross(CvPoint* VecA, CvPoint* VecB){
	float Ax = (float) VecA->x;
	float Ay = (float) VecA->y;
	float Bx = (float) VecB->x;
	float By = (float) VecB->y;
	return (Ax*By -  Ay*Bx) / ( cvSqrt(Ax*Ax+Ay*Ay)*cvSqrt(Bx*Bx+By*By) ) ;

}




/*
 * Normalizes two vectors representated in cartesian coordinates as CvPoint (x,y) and returns their dot ptorduct.
 *
 */
float NormPointDot(CvPoint* VecA, CvPoint* VecB){
	float Ax = (float) VecA->x;
	float Ay = (float) VecA->y;
	float Bx = (float) VecB->x;
	float By = (float) VecB->y;

	return ( (Ax*Bx+Ay*By) /  ( cvSqrt(Ax*Ax+Ay*Ay)*cvSqrt(Bx*Bx+By*By) ) );

}




/* Function Draws a Sequence of CvPoint's with little cirlces.
 * This function uses only a sequence and an image.
 *
 */

void DrawSequence(IplImage** image, CvSeq* Seq) {
	int i;
	for (i = 0; i < Seq->total; i++) {
		CvPoint* tempPt = (CvPoint*) cvGetSeqElem(Seq, i);
		cvCircle(*image, *tempPt, 1, cvScalar(255, 255, 255), 1);

	}
}





/*
 * This function resamples a sequence of points on a boundary so as to keep the number of points
 * per arc length constant.
 *
 * It does this by first resampling to the specified points through decimation, then calculating
 * the arc length and then interpolating between those points so as to keep constant point density.
 *
 *	Note that this function resampleSeq always includes the first point of the sequence
 *	but it does not necessarily include the last point.
 *	As long as the initial number of points is large compared to the Numsegments requested,
 *	then the last point should be fairly close.
 */

void resampleSeqConstPtsPerArcLength(CvSeq* sequence, CvSeq* ResampledSeq, int Numsegments) {
	if (sequence==NULL || ResampledSeq==NULL) {
		printf("Error! sequence passed to resampleSeqConstPtsPerArcLength() is NULL!\n");
		return;
	}
	if (sequence->total < 1) printf("Error! Sequence passed to resampleSeq() is empty!\n");


	/**********************************
	 * Step I: Decimate the boundary while
	 * calculating cumsum
	 */

	/** Let's create a struct that holds our decimated subsampled sequence, and the cumsum arclength **/
	typedef struct PtAndSumStruct
	{
	    int x;
	    int y;
	    float sum;
	}PtAndSum;


	CvSeq* decimated = cvCreateSeq(0, sizeof(CvSeq), sizeof(PtAndSum), sequence->storage);






	/** n-1 is the number of decimated points between sampled points**/
	float n = (float) ( sequence->total -1 )/ (float) ( Numsegments-1);
	CvSeqReader reader;
	CvSeqWriter writer;
	cvStartReadSeq(sequence, &reader, 0);
	cvStartAppendToSeq(decimated, &writer);
	CvPoint* tempPt;
	PtAndSum curr;


	tempPt = (CvPoint*) reader.ptr;
	curr.x=tempPt->x; curr.y=tempPt->y; curr.sum=0;


	int i=0;
	int tempPos;





	while (i<Numsegments){
		tempPos=(int) (i *n + 0.5);
		cvSetSeqReaderPos(&reader, tempPos, 0);
		tempPt = (CvPoint*) reader.ptr;

		/** Current sum= cumsum at prev pt + distance between current Pt and Previous Pt **/
		curr.sum=curr.sum+dist(*tempPt,cvPoint(curr.x,curr.y));

		/** Update Current Pt**/
		curr.x=tempPt->x;
		curr.y=tempPt->y;


		CV_WRITE_SEQ_ELEM( curr, writer );
		if (!(tempPos < sequence->total && tempPos >= 0)){
					printf(" Error. Position to set sequence reader to is out of range in resampleSeq()\n");
		}
		i++;
	}

	cvEndWriteSeq(&writer);





	int totalArcLength=curr.sum;
//	printf("Moving on to part II\n");

	/**************************************************
	 * Part II: Interpolate so as to keep constant
	 * number of pts per arc length
	 *
	 */

	n=0;
	i=0;
	float s; // s is length along arc of current point

	/*
	 * Let's introduce some terminology.
	 *
	 * The decimated boundary is now made of Numsegments number of "vertices."
	 * We will find new "points" along the boundary by interpolating between the vertices.
	 *
	 */

	/** n-1 is the optimum arc length between points**/
		n = (float) ( curr.sum)/ (float) ( Numsegments-1); //Andy: these -1's make sense. I tested for the case 10 pts equally spaced distance 1 apart.**/


		PtAndSum* prevVertex;
		PtAndSum* currVertex;


		/** Start reading through sequence of decimated points **/
		cvStartReadSeq(decimated, &reader, 0);

		/** Start Writing output **/
		cvStartAppendToSeq(ResampledSeq, &writer);

		currVertex = (PtAndSum*) reader.ptr;
		prevVertex = currVertex;
		double DistBetVertices=0;
		double t=0;
		CvPoint interpPt;
		CvPoint2D32f unitVec;

		int k=0; // decimated counter;

		/** For each point we are looking for **/

		while (i<Numsegments){ // while working on the ith point to create (starting with zero)
			s=(float)i* n; // The point should lie a distance s along the arc length


			k=0;

			/** Loop until we find some vertices that do s **/
			while (!(  (s>= prevVertex->sum )&& (s <= currVertex->sum) )){



//				printf("\n\ns=%f,i=%d,k=%d\n",s,i,k);
//				printf("prevVertex->sum = %f\n",prevVertex->sum );
//				printf("currVertex->sum = %f\n",currVertex->sum );



				/** Special case when we are seeking to find the vertices that enclose the last point **/
				if (i==Numsegments-1){
					/** select the second-to-last vertex of the sequence **/
					cvSetSeqReaderPos(&reader,decimated->total-2,0);
					prevVertex= (PtAndSum*) reader.ptr;
					/** set the current vertex to the end vertex of the sequence **/
					CV_NEXT_SEQ_ELEM(sizeof(PtAndSum),reader);
					currVertex = (PtAndSum*) reader.ptr;
					k++; // just for kicks increment k
					break;
				}

				/** prevVertex=currVertex **/
				prevVertex=currVertex;

				/** Increment currVertex**/
				CV_NEXT_SEQ_ELEM(sizeof(PtAndSum),reader);
				k++;
				currVertex = (PtAndSum*) reader.ptr;



			}


			/** Interpolate & record output 	**/
			DistBetVertices=(double) currVertex->sum - (double) prevVertex->sum;
//			printf("DistBetVertices=%f\n",DistBetVertices);

			/** t is the arc length beyond the previous vertex (s=prevVertex->sum+t)**/
			t = (double) s - prevVertex->sum; //Think of t as the parameter in a parametric equation

			if (t<0) printf("ERROR! This should never happen!\n");



			if (DistBetVertices <1 ) { // If the two points are the same.
				unitVec.x=0;  /** Avoid dividing by zero **/
				unitVec.y=0;
			} else {
				/** Calculate the unit vector that points from prevVertex to currVertex **/
				unitVec=cvPoint2D32f( (double) (currVertex->x-prevVertex->x) / (double) DistBetVertices  ,
						(double) (currVertex->y-prevVertex->y) / (double) DistBetVertices);
			}

			/** Parametric equation **/
			interpPt=cvPoint((int) ((int) prevVertex->x+unitVec.x * t+0.5),(int) ((int) prevVertex->y +unitVec.y * t+0.5));

			/** Actually write the newly found interpolated point **/
			CV_WRITE_SEQ_ELEM(interpPt, writer);

			i++;

		}


		cvEndWriteSeq(&writer);
}




/*
 *
 * Resamples a boundary and stores it by omitting points. There is no interpolation.
 *
 *	Note that this function resampleSeq always includes the first point of the sequence
 *	in the new sequence, but it does not necessarily include the last point.
 */
void resampleSeq(CvSeq* sequence, CvSeq* ResampledSeq, int Numsegments) {
	if (sequence->total < 1) printf("Error! Sequence passed to resampleSeq() is empty!\n");

	float n = (float) ( sequence->total -1 )/ (float) ( Numsegments-1);
	CvSeqReader reader;
	CvSeqWriter writer;
	cvStartReadSeq(sequence, &reader, 0);
	cvStartAppendToSeq(ResampledSeq, &writer);
	if (PRINTOUT) printf("Seq->total=%d; n=%f\n", sequence->total, n);
	CvPoint* tempPt;
	int i=0;
	int tempPos;



	while (i<Numsegments){
		tempPos=(int) (i *n + 0.5);
		cvSetSeqReaderPos(&reader, tempPos, 0);
		tempPt = (CvPoint*) reader.ptr;
		CV_WRITE_SEQ_ELEM( *tempPt, writer );
		if (!(tempPos < sequence->total && tempPos >= 0)){
					printf(" Error. Position to set sequence reader to is out of range in resampleSeq()\n");
		}
		i++;
	}


	cvEndWriteSeq(&writer);
}





/*
 *
 * Returns the squared distance between two points
 *
 */
int sqDist(CvPoint pta, CvPoint ptb){
	return (  ((pta.x - ptb.x)*(pta.x - ptb.x) ) + ((pta.y - ptb.y)*(pta.y - ptb.y)  ) );
}

/*
 * Finds the distance between two points
 * and returns the value as a float
 *
 */
float dist(CvPoint a, CvPoint b){
	return ( sqrt( (float) sqDist(a,b))  );
}

/*
 * WHOA!! THIS FUNCTION IS ALL SCREWED UP AND CAUSING PROBLEMS!!
 *
 * Given two points a and b , and a sequence of CvPoints
 * this function will find the points that walk the line
 * between a and b and append those
 * the end of the sequence
 *
 * Note that the output  includes point a, but not point b.
 */
int GetLineFromEndPts(CvPoint a, CvPoint b, CvSeq* contour){
	if (contour==NULL) {
		printf("ERROR! contour in GetLineFromEndPts() is NULL!\n");
		return -1;
	}
	float d=dist(a,b);
	/** Normalized vector with components i and j pointing along the line**/
	float ihat= ( (float) (b.x -a.x) ) /d;
	float jhat= ( (float) (b.y -a.y) ) /d;

	CvPoint currPt; /* Current Point On integer grid*/
	CvPoint prevPt=a; /* Prev Point on integer grid */
	currPt=a;

	/** Prepare Writer for Appending Points to Seq **/
	CvSeqWriter writer;
	cvStartAppendToSeq( contour, &writer );


//	printf("GetLineFromEndPts()\n");
//	printf("a=( %d , %d), b=( %d, %d), dist= %f\n",a.x,a.y,b.x,b.y, d);





	int t;
	float tempPtx;
	float tempPty;
	int signx=1;
	int signy=1;

	for (t = 0; t <  (int) (d+0.5) ; ++t) {

		/** Our target point is now defined by a parametric equation **/
		tempPtx=(float) t * ihat + (float) a.x;
		tempPty=(float) t * jhat + (float) a.y;

		/** We will want to round and we need to know the number's sign to round correctly **/
		if (tempPtx<0) {
			signx=-1;
		} else {
			signx=1;
		}
		if (tempPty<0) {
			signy=-1;
		} else{
			signy=1;
		}


		/** Round to an integer value. Note that we need the sign before we add/subtract .5 **/
		currPt=cvPoint((int) ( tempPtx + (float) signx * 0.5 ) ,
					(int) ( tempPty + (float) signy * 0.5 ));


		/** If first point, OR the current approx point is not the same as prev **/
		if ( t==0 ||  !( currPt.x == prevPt.x && currPt.y == prevPt.y   )   ){

			/** Write out the point **/
			CV_WRITE_SEQ_ELEM( currPt, writer );

//		printf(" t=%d\n",t);
//		printf(" currPt.x=%d\n",currPt.x);
//		printf(" currPt.y=%d\n",currPt.y);


		}
		prevPt=currPt;
	}
	cvEndWriteSeq( &writer );
	return 1;
}


/*
 * Given a CvSeq of CvPoints defining a polygon, this function
 * will create a contour of the outline of the polygon.
 *
 * Note this assumes that last point in the polygon sequence
 * connects to the first point.
 *
 * polygon and contour must be CvSeq's that already have
 * CvMemStorage associated with them
 */
int CvtPolySeq2ContourSeq(CvSeq* polygon, CvSeq* contour ){
	if (polygon==NULL || contour==NULL){
		printf("ERROR! CvtPolySeq2ContourSeq was passed a NULL sequence!\n ");
		return -1;
	}

	/** Setup reader for the polygon **/
	CvSeqReader VertexReader;
	cvStartReadSeq(polygon,&VertexReader);

	CvSeqReader NextVertexReader;
	cvStartReadSeq(polygon,&NextVertexReader);
	CV_NEXT_SEQ_ELEM(polygon->elem_size,NextVertexReader);

	int k;
	for (k = 0; k < (polygon->total) ; ++k) {
		/** Get the current and next vertices **/
		CvPoint* currVertex =(CvPoint*) VertexReader.ptr;
		CvPoint* nextVertex =(CvPoint*) NextVertexReader.ptr;
		/**Find all the points in between & append them to the contour **/
		GetLineFromEndPts(*currVertex,*nextVertex,contour);


		/** Increment **/
		/** CV_NEXT_SEQ_ELEM will loop around when it runs off the seq **/
		CV_NEXT_SEQ_ELEM(polygon->elem_size,VertexReader);
		CV_NEXT_SEQ_ELEM(polygon->elem_size,NextVertexReader);
	}

	return 1;
}




/*
 * Given two CvSeq containing CvPoint's this function returns the midpoint.
 * Note that the two CvSeq's have to be resampled to the same length.
 * Use, for example, ResampleSeq().
 *
 */
void FindCenterline(CvSeq* NBoundA, CvSeq* NBoundB, CvSeq* centerline) {

	CvSeqReader readerA;
	CvSeqReader readerB;
	CvSeqWriter writer;
	cvStartReadSeq(NBoundA, &readerA, 0);
	cvStartReadSeq(NBoundB, &readerB, 0);
	//Set our pointer to the location along the boundary of the Tail.
	cvStartAppendToSeq(centerline, &writer);

	CvPoint* SideA;
	CvPoint* SideB;
	CvPoint MidPt;

	int i = 0;
	do {
		SideA = (CvPoint*) readerA.ptr;
		SideB = (CvPoint*) readerB.ptr;

		MidPt = cvPoint((int) (SideA->x + SideB->x) / 2, (int) (SideA->y
				+ SideB->y) / 2);
		//	if (PRINTOUT) printf("SideA= ( %d, %d )\tSideB= ( %d, %d )\n", SideA->x, SideA->y,SideB->x,SideB->y);
		//	if (PRINTOUT) printf("MidPt= ( %d, %d )\n", MidPt.x, MidPt.y);
		//Find the midpoint, and write it to the sequence (auto-increments)
		CV_WRITE_SEQ_ELEM( MidPt, writer);

		//Push the pointers along the boundaries in opposite directions
		CV_NEXT_SEQ_ELEM(sizeof(CvPoint),readerA);
		CV_NEXT_SEQ_ELEM(sizeof(CvPoint),readerB);
		i++;

	} while (i < NBoundA->total);
	cvEndWriteSeq(&writer);

}



/*
 * Given a point, and a boundary, this function returns the coordinates of the closest point on the boundary.
 */
CvPoint FindNearestPt(CvPoint CenterLinePt,CvSeq* Boundary){
	CvSeqReader reader;
	cvStartReadSeq(Boundary, &reader, 0);
	CvPoint* CurrPoint; //The current point we are considering
	CvPoint* ClosestPoint=(CvPoint*) reader.ptr; //The previous closest point (which we initalize here)
	int shortestDist =sqDist(CenterLinePt,*ClosestPoint); //The Previous shortest distance (which we initalize herE)
	int currDist;
	for (int i=0;i<Boundary->total;i++){
		CurrPoint =(CvPoint*) reader.ptr;
		currDist=sqDist(CenterLinePt,*CurrPoint);
		if (currDist<=shortestDist){
			//Update the shortest distance
			shortestDist=currDist;
			//Copy the contents from CurrPoint to Closest Point;
			*ClosestPoint = *CurrPoint;

		}
		//Move up a point along the boundary
		CV_NEXT_SEQ_ELEM(sizeof(CvPoint),reader);
	}
	return *ClosestPoint;
}


/*
 * Given a point and a corresponding vector,  find the point along a contour that is perpendicular
 * to the specified point.
 */
CvPoint FindNormalPt(CvPoint* Centerline, CvPoint* CenterVec, CvSeq* Contour){
	CvPoint* VecToTarget;
	CvPoint* Target;
	CvPoint BestTarget;
	int DotProd;
	int LowestDotProd;
	CvSeqReader reader;
	cvStartReadSeq(Contour, &reader, 0);

	//Make one iteration before the Loop
	Target=(CvPoint*) reader.ptr;
	*VecToTarget=cvPoint(Target->x-Centerline->x,Target->y-Centerline->y );
	LowestDotProd=PointDot(CenterVec,VecToTarget);


	for (int i=0;i<Contour->total;i++){
		Target=(CvPoint*) reader.ptr;
		*VecToTarget=cvPoint(Target->x-Centerline->x,Target->y-Centerline->y );
		DotProd=PointDot(CenterVec,VecToTarget);
		if (DotProd<=LowestDotProd){
			//Update the Lowest Dot product
			LowestDotProd=DotProd;
			//Save this point as the best one yet
			BestTarget=*Target;
		}
		//Move up a point along the boundary
		CV_NEXT_SEQ_ELEM(sizeof(CvPoint),reader);

	}

	return BestTarget;

}



/*
 *
 * Marc's Functions
 *
 */

/*void SegmentSides (const CvSeq *contourA, const CvSeq *contourB, const CvSeq *centerline, CvSeq *segmentedA, CvSeq *segmentedB) {
 * all sequences are allocated sequences of CvPoint
 * const sequences are input
 * non const sequences are output and should be empty
 * contourA and contourB should be oriented so that they run from the nearest point to c0 (e.g. the head
 * to the nearest point to cN
 *
 * given a centerline c0 thru cN and contours on either side of the center line,
 * fills two new sequences with points according to these rules:
 *
 * a0/b0, aN/bN are the first (and last) points in A/B not equal to c0 (cN)
 * aj/bj is the intersection of the perpendicular to the centerline at point cj and the contour A,B
 *
 * aj is found by:  t(j) = c(j+1)-c(j-1);  x(k) = A(k)-c(j);  find k that minimizes abs(t(j)*x(k));  aj = A(k)
 *
 * finally, we enforce the rule that points in the segmented contour must have the same order as the original;
 * i.e. if index k > j, then segmentedA(k) comes later in contourA than segmentedA(j)
 *
 * MHG 9/16/09
 */
void SegmentSides (const CvSeq *contourA, const CvSeq *contourB, const CvSeq *centerline, CvSeq *segmentedA, CvSeq *segmentedB) {
	int j,lastA, lastB;
	int ptincrement;
	int noduplicates = 0;
	CvPoint current, forward, backward, tangent;



	/** This defines the search area with which we will look for a point on the boundary **/
	ptincrement = 3*((contourA->total > contourB->total ? contourA->total : contourB->total) / centerline->total + 1);



	lastA=0;
	lastB=0;
	/** walk along the centerline and find the points perpendicular to the tangent of the centerline along the boundary **/
		for (j = 0; j < centerline->total; j++) {

			/** Find the point behind current on the centerline **/
			if (j==0){
				/** If current is the first point on the centerline **/
				/** Use the Head as backwards **/
				backward = *(CvPoint *) cvGetSeqElem (contourA, 0);
			}else{
				backward = *(CvPoint *) cvGetSeqElem (centerline, j - 1);
			}

			/** Find the current point along the centerline **/
			current = *(CvPoint *) cvGetSeqElem (centerline, j);

			/** Find the point in front of current on the centerline **/
			if (j==centerline->total-1){
				/** If current is the last point on the centerline **/
				/** use the tail as forward **/
				forward = *(CvPoint *) cvGetSeqElem (contourA, centerline->total-1);
			}else{
				forward = *(CvPoint *) cvGetSeqElem (centerline, j+1);
			}
			/** The tangent vector is forward minus backward **/
			tangent.x = forward.x - backward.x;
			tangent.y = forward.y - backward.y;

			/** Find the index along the boundary for the perpendicular pointer and store it **/
			lastA = FindPerpPoint (current, tangent, contourA, lastA - ptincrement, lastA + ptincrement);
			lastB = FindPerpPoint (current, tangent, contourB, lastB - ptincrement, lastB + ptincrement);
			cvSeqPush (segmentedA, cvGetSeqElem(contourA, lastA));
			cvSeqPush (segmentedB, cvGetSeqElem(contourB, lastB));
		}

}


/*int FirstDoesNotMatch (CvPoint a, const CvSeq *b, int startInd, int dir)
 *
 *given a sequence of CvPoints b, starting at index startInd and proceeding in
 *direction dir (dir = +1 or -1, no error checking), finds the first point in b
 *that does not equal a, and returns its index
 *returns -1 in case of failure
 *
 ** MHG 9/16/09
 */
int FirstDoesNotMatch (CvPoint a, const CvSeq *b, int startInd, int dir) {
	CvPoint pt;
	for ( ;startInd >=0 && startInd < b->total;startInd += dir) {
		pt = *(CvPoint *) cvGetSeqElem (b, startInd);
		if (pt.x != a.x || pt.y != a.y)
			return startInd;
	}
	return -1;
}
/*int FindPerpPoint (CvPoint x, CvPoint t, const CvSeq *a, int startInd, int endInd) {
 *
 * a is sequence of CvPoint
 * finds the point in a that minimizes abs(dot (a(k)-x, t)) k in [startInd,endInd)
 * note that endInd is not included in search
 *
 * minimum point is the absolute minimum on the interval found by computing the quantity at every point
 *
 ** MHG 9/16/09
 */
int FindPerpPoint (CvPoint x, CvPoint t, const CvSeq *a, int startInd, int endInd) {
	int j, trialadp, bestadp, bestInd = startInd;
	CvPoint current;
	bestadp = INT_MAX;
	startInd = startInd > 0 ? startInd : 0;
	endInd = endInd < a->total ? endInd : a->total;
	for (j = startInd; j < endInd; j++) {
		current = *(CvPoint *) cvGetSeqElem (a, j);
		trialadp =  ((current.x - x.x)*t.x + (current.y - x.y)*t.y);
		trialadp = trialadp < 0 ? -trialadp : trialadp;
		if (trialadp < bestadp) {
			bestadp = trialadp;
			bestInd = j;
		}
	}
	return bestInd;
}



/* void RemoveSequentialDuplicatePoints (CvSeq *seq)
 *
 * seq is a sequence of CvPoint
 * removes any duplicated points that occur in sequence;  e.g. (1,1), (1,1), (1,2) --> (1,1), (1,2)
 * but (1,1),(1,2),(1,1) --> (1,1),(1,2),(1,1)
 *
 *MHG 9/16/09
 */
void RemoveSequentialDuplicatePoints (CvSeq *seq) {
	int j;
	CvPoint a, b;
	for (j = 0; j < seq->total - 1; ) {
		a = *(CvPoint *) cvGetSeqElem(seq, j);
		b = *(CvPoint *) cvGetSeqElem(seq, j+1);
		if (a.x == b.x && a.y == b.y) {
			cvSeqRemove(seq, j+1);
		} else{
			j++;
		}
	}
}

/*void ConvolveInt1D (const int *src, int *dst, int length, int *kernel, int klength, int normfactor)
 * pads end points with end values
 * andy will comment later
 *
 */
void ConvolveInt1D (const int *src, int *dst, int length, int *kernel, int klength, int normfactor) {
	int j, k, ind, anchor, sum;
	anchor = klength/2;
	for (j = 0; j < length; j++) {
		sum = 0;
		for (k = 0; k < klength; k++) {
			ind = j + k - anchor;
			ind = ind > 0 ? ind : 0;
			ind = ind < length ? ind : (length - 1);
			sum = sum + src[ind]*kernel[k];
		}
		dst[j] = (int) (1.0*sum/normfactor + 0.5);
	}
}

void ConvolveCvPtSeq (const CvSeq *src, CvSeq *dst, int *kernel, int klength, int normfactor) {
	int j, *x, *y, *xc, *yc;
	CvPoint pt;

	x = (int *) malloc (src->total * sizeof(int));
	y = (int *) malloc (src->total * sizeof(int));
	xc = (int *) malloc (src->total * sizeof(int));
	yc = (int *) malloc (src->total * sizeof(int));

	for (j = 0; j < src->total; j++) {
		x[j] = ((CvPoint *) cvGetSeqElem(src, j))->x;
		y[j] = ((CvPoint *) cvGetSeqElem(src, j))->y;
	}
	ConvolveInt1D(x, xc, src->total, kernel, klength, normfactor);
	ConvolveInt1D(y, yc, src->total, kernel, klength, normfactor);

	for (j = 0; j < src->total; j++) {
		pt.x = xc[j];
		pt.y = yc[j];
		cvSeqPush(dst, &pt);
	}

	free(x);
	free(y);
	free(xc);
	free(yc);
}

void CreateGaussianKernel (double sigma, int **kernel, int *klength, int *normfactor) {
	int ll, ul, x;
	double n;
	ll = (int) (-3 * sigma) - 1;
	ul = (int) (3 * sigma) + 1;
	*klength = ul - ll + 1;
	*kernel = (int*) malloc (*klength * sizeof(int));

	*normfactor = 0;
	if (PRINTOUT) printf ("kernel = ");
	n = exp(-1.0*ll*ll/(2*sigma*sigma));
	for (x = 0; x < *klength; x++) {
		(*kernel)[x] =(int) (exp(-1.0*(x+ll)*(x+ll)/(2*sigma*sigma))/n + 0.5);
		*normfactor += (*kernel)[x];
		if (PRINTOUT) printf ("%d\t", (*kernel)[x]);
	}
	if (PRINTOUT) printf("\nnormfactor = %d\n", *normfactor);

}

CvSeq *smoothPtSequence (const CvSeq *src, double sigma, CvMemStorage *mem) {
	int *kernel, klength, normfactor;
	CvSeq *dst = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq), sizeof(CvPoint), mem);
	CreateGaussianKernel(sigma, &kernel, &klength, &normfactor);
	ConvolveCvPtSeq(src, dst, kernel, klength, normfactor);
	free(kernel);
	return dst;
}



/*** Testing Functions ***/
/*
 * Check's to see if sequence exists
 * Exists=nonzero
 * False = 0
 */
bool cvSeqExists(CvSeq* MySeq){
	if((MySeq != NULL) && (MySeq->total >0)){
		return 1;
	} else{
		return 0;
	}

}


/*
 * Check's to see if point exists
 * Exists=nonzero
 * False = 0
 */
bool cvPointExists(CvPoint* MyPt){
	if((MyPt != NULL) && (MyPt->x >=0) && (MyPt->y >=0)){
			return 1;
		} else{
			return 0;
		}


}

/* DEPRECATED. DOESN'T DO ANYTHING
 * Always returns 1.
 */
bool IntExists(int MyInt){
			return 1;
}


/*
 *  If x is greater than max, the function returns max;
 *  If x is less then min, the function returns min.
 *  Ohterwise the function returns x
 *
 */
int CropNumber(int min, int max, int x){
	if (x>max) return max;
	if (x<min) return min;
	return x;
}

