/*
 * SegmentFrame.c
 *
 *  Created on: Aug 25, 2009
 *      Author: andy
 *
 *   Based in large part on the example on p.242 of the O'Reilly Book: Learning OpenCV
 */





#include <stdio.h>

//OpenCV Headers
#include <highgui.h>
#include <cv.h>

//Andy's Personal Headers
#include "MyLibs/AndysOpenCVLib.h"

//C Libraries
#include <string.h>
#include <math.h>

#define PRINTOUT 1
#define ONSCREEN 1
#define DRAWBOUNDARY 0

/*
 * This is a wrapper function to run cvFindContours that I am using so that the profiler
 * will catch this function. This will be useful for finding out what is taking so long when I run the code.
 *
 */
void FindContoursWrapper(CvArr* image, CvMemStorage* memoryStorage, CvSeq**  contours);


/*
 * Illuminate a segment of the worm. Either the right, or left side.
 * Takes a sequence of the centerline. Uses the preceeding point to find a vector
 * along the centerline, than draws a rectangle perpendicular to this vector, a radius rsquared pixels
 * away from the centerline
 */
void IlluminateWormSegment(IplImage** image, CvSeq* centerline, int segment, int rsquared);







void on_trabckar(int);
CvMemStorage* g_storage = NULL;
CvMemStorage* scratchStorage=NULL;
CvMemStorage* more_storage=NULL;


IplImage* g_image = NULL;  // the original image
IplImage* g_gray=NULL;  //a grayscale version of the image
IplImage* thresh_img=NULL; // a thresholded version of the image


CvSeq* contours;
CvSeq* contourOfInterest;

CvSeq* VectBound;
//int Delta=11; // Coarse Grain factor (number of pixels away that is used to draw vectors)
int Delta=9;
int Offset=Delta/2; //Pixels to compensate for the CoarseGraininess (everythign is offset a little bit)
int CircleDiameterSize=10;

//int FileIndex=0;

int g_thresh = 48; //Value for image th reshoold
int gauss_size=4; // Size of gaussian that will be used for smoothing
int nc=0; // Number of contours




void FindContoursWrapper(CvArr* image, CvMemStorage* memoryStorage, CvSeq**  contours){
	cvFindContours(image,memoryStorage, contours,sizeof(CvContour),CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE,cvPoint(0,0));

}





void on_trackbar(int){
	if ( g_storage==NULL ){
		g_gray=cvCreateImage(cvGetSize(g_image),8,1);
		thresh_img=cvCreateImage(cvGetSize(g_image),8,1);
		g_storage = cvCreateMemStorage(0);
		more_storage=cvCreateMemStorage(0);
		scratchStorage=cvCreateMemStorage(0);
	}else{
	cvClearMemStorage(g_storage);
	cvClearMemStorage(more_storage);
	cvClearMemStorage(scratchStorage);
	}

	int i=0; //Generic counter


	if (PRINTOUT) printf("\n\nInside on_trackbar()\n");

	cvCvtColor( g_image, g_gray, CV_BGR2GRAY);

	cvSmooth(g_gray,g_gray,CV_GAUSSIAN,gauss_size*2+1);
	if (ONSCREEN) cvShowImage("Smoothed",g_gray);
	cvThreshold(g_gray,thresh_img,g_thresh,255,CV_THRESH_BINARY );
	if (ONSCREEN) cvShowImage("Thresholded",thresh_img);
	//Attempting a multipass threshold smooth approach.


	FindContoursWrapper(thresh_img,g_storage, &contours);
	//nc=cvFindContours(thresh_img,g_storage, &contours,sizeof(CvContour),CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE,cvPoint(0,0));

	if( contours ) {
		LongestContour(contours,&contourOfInterest);
		if (PRINTOUT) printf("****ContourOfInterest has length %d*****\n",contourOfInterest->total);
		if (DRAWBOUNDARY) cvDrawContours(g_gray, contourOfInterest, cvScalar(255,0,0),cvScalar(0,255,0),100);
		if (PRINTOUT) printf("Drew Contours\n");
	}



	/*
	 * Find The Head and the Tail
	 */

	//Create vectors some Delta apart.
	CvPoint* boundPt;
	CvPoint* boundPtDelta;
	int TotalBPts=contourOfInterest->total ;
	if (PRINTOUT) printf("Total Boundary Pts is %d\n",TotalBPts);



		VectBound=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),scratchStorage);


	//Let's walk around the boundary;
	//For speed, lets create two special reader object.
	CvSeqReader readerA;
	CvSeqReader readerB; //readerB will point a Delta points ahead of readerB.
	// And a writer object
	CvSeqWriter writer;

	CvPoint TempVec;

	cvStartReadSeq(contourOfInterest,&readerA,0);
	cvStartReadSeq(contourOfInterest,&readerB,0);
	cvStartAppendToSeq(VectBound,&writer);
	if (PRINTOUT) printf("Started ReadSeq and AppendToSeq\nIncrementing Delta\n");
	//Let's increment readerB delta times
	for (i=0; i<Delta;i++){
		CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerB);
	}
	if (PRINTOUT) printf("Beginning to loop through contourOfInterest\n");

	if (TotalBPts<1) printf("Error! TotalBpts <1 !!\n");
	/*
	 *
	 * Loop through all the boundary and draw vectors connect one boundary point to the next.
	 *
	 */
	for (i = 0; i<TotalBPts; i++) {
		boundPt=(CvPoint*)readerA.ptr;
		boundPtDelta=(CvPoint*)readerB.ptr;

		CV_NEXT_SEQ_ELEM( contourOfInterest->elem_size, readerA);
		CV_NEXT_SEQ_ELEM( contourOfInterest->elem_size, readerB);
		TempVec=cvPoint( (boundPtDelta->x)-(boundPt->x) , (boundPtDelta->y)-(boundPt->y) );
		//if(TempVec.x==0|| TempVec.y==0) printf("TempVec contains zero values!\n");
		//printf("sizeof(TempVec)=%d\n",sizeof(TempVec));
		CV_WRITE_SEQ_ELEM( TempVec , writer );

		//Draw A line
		//cvLine(g_gray,*boundPt,cvPoint(boundPt->x+TempVec->x,boundPt->y+TempVec->y),cvScalar(255,255,255),1,CV_AA,0);

	}
	if (PRINTOUT) printf("Preparing cvEndWriteSeq()\n");
	cvEndWriteSeq(&writer);

	if (PRINTOUT) printf("After walking along contour, VectBound->total = %d\n", VectBound->total);

	/*
	 * Now that we have a sequence of vectors that follow the worm's boundary, we need to take the dot
	 * product between neighboring vectors. And find the Smallest Dot Product. This is the tail.
	 */

	CvPoint* VecA;
	CvPoint* VecB;


	/*
	 * Now Let's loop through the entire boundary to find the tail, which will be the curviest point
	 * excluding those points around the tail.
	 */
	float MostCurvy=1000; //Smallest value.
	float CurrentCurviness;  //Metric of CurrentCurviness. In this case the dot product.
	int MostCurvyIndex=0;
	CvPoint* Tail;


	cvStartReadSeq(VectBound,&readerA,0);
	cvStartReadSeq(VectBound,&readerB,0);
	CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerA);
	for (i=0; i<TotalBPts; i++){
		VecA=(CvPoint*)readerA.ptr;
		VecB=(CvPoint*)readerB.ptr;

		//Find the curviness by taking the normalized dot product.
		CurrentCurviness=PointDot(VecA,VecB);
		CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerA);
		CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerB);
		if ( CurrentCurviness<MostCurvy){ //If this locaiton is curvier than the previous MostCurvy location
			MostCurvy=CurrentCurviness; //replace the MostCurvy point
			MostCurvyIndex=i;
		}
	}

	//Set the tail to be the point on the boundary that is most curvy.
	Tail=(CvPoint*)cvGetSeqElem(contourOfInterest, (MostCurvyIndex+Offset)%TotalBPts );

	//Draw a circle on the tail.
	cvCircle(g_gray,*Tail,CircleDiameterSize,cvScalar(255,255,255),1,CV_AA,0);
	if (PRINTOUT) printf("MostCurvyIndex=%d\n",MostCurvyIndex);


	//This is for the Head
	float SecondMostCurvy=1000;
	int SecondMostCurvyIndex=0;
	int DistBetPtsOnBound;
	DistBetPtsOnBound=0;
	CvPoint* Head;

	cvStartReadSeq(VectBound,&readerA,0);
	cvStartReadSeq(VectBound,&readerB,0);
	CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerA);
	for (i=0; i<TotalBPts; i++){
		VecA=(CvPoint*)readerA.ptr;
		VecB=(CvPoint*)readerB.ptr;
		CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerA);
			CV_NEXT_SEQ_ELEM( VectBound->elem_size, readerB);

			//Find the curviness by taking the normalized dot product.
			CurrentCurviness=PointDot(VecA,VecB);

			//We need to find out if the current curvy point is close to the most curvy point.
			//This is tricky because the boundary wraps around. We need this if statement to find the radius.
			// ANDY: Decomp this into its own function for legibility.
			if (labs(i-MostCurvyIndex)<labs(TotalBPts-(i-MostCurvyIndex))){//go with the smallest value
				DistBetPtsOnBound=labs(i-MostCurvyIndex);
			}else{
				DistBetPtsOnBound=labs(TotalBPts-(i-MostCurvyIndex));
			}
			//If we are at least a 1/4 of the total boundary away from the most curvy point.
			if (DistBetPtsOnBound> (TotalBPts/4) ){
			//If this location is curvier than the previous SecondMostCurvy location
				if ( CurrentCurviness<SecondMostCurvy){
					SecondMostCurvy=CurrentCurviness; //replace the MostCurvy point
					SecondMostCurvyIndex=i;
				}
			}
		}

	if (PRINTOUT) printf("SecondMostCurvyIndex=%d\n",SecondMostCurvyIndex);

	Head=(CvPoint*)cvGetSeqElem(contourOfInterest, (SecondMostCurvyIndex+Offset)%TotalBPts );
	cvCircle(g_gray,*Head,CircleDiameterSize*2/5,cvScalar(255,255,255),1,CV_AA,0);

	/*************************************************************/
	/*
	 *
	 * Now Find the centerline using only the variables, contourOfInterst, MostCurvyIndex, SecondMostCrvyIndex
	 *
	 *
	 */
	if (PRINTOUT) printf("Beginning to find centerline\n");

	CvSeq* boundary=contourOfInterest;
	int TailIndex=MostCurvyIndex+Offset;
	int HeadIndex=SecondMostCurvyIndex+Offset;

	/*
	 * First we're going to trace out the centerline by the tip of the head and the tail.
	 * I'm going to use two different algorithms for speed. One only does the head/tail regions and the other does
	 * the  rest of the worm.
	 */
	//If centerline hasn't been initialized yet, we need to create it
	CvSeq* centerline=NULL;
	if (centerline == NULL) {
		centerline=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),more_storage);
	} else{ // Or if it already has been set-up, we just want to clear the elements in the sequence
		cvClearSeq(centerline);
	}

	if (PRINTOUT) printf("Beginning to initialize sequence readers and writers\n");
//	CvSeqReader readerA;
//	CvSeqReader readerB;
//	CvSeqWriter writer;
	cvStartReadSeq(boundary,&readerA,0);
	cvStartReadSeq(boundary,&readerB,0);
	//Set our pointer to the location along the boundary of the Tail.
	cvSetSeqReaderPos(&readerA,TailIndex,0);
	cvSetSeqReaderPos(&readerB,TailIndex,0);
	cvStartAppendToSeq(centerline,&writer);

	CvPoint* SideA;
	CvPoint* SideB;
	CvPoint MidPt;



	if (PRINTOUT) printf("Entering midpoint finding For Loop\n");

	/*
	 * Let's Push two pointers from the tail to the head. Find the midpoint and write it to another sequence,
	 * called centerline. We will keep doing this until one of our pointers bumps into the head.
	 *
	 * AND Let's do the same thing from the head to the tail and meet in the center!
	 * we will keep track of the loop index at which point the first pair of pointers cross each other
	 * on one side and the second pair of pointers cross one another on the other side
	 * for that overlapping
	 */
	i=0;
	do {
		SideA=(CvPoint*)readerA.ptr;
		SideB=(CvPoint*)readerB.ptr;

		MidPt=cvPoint( (int) (SideA->x + SideB->x)/2, (int) (SideA->y + SideB->y)/2   );
	//	if (PRINTOUT) printf("MidPt= ( %d, %d )\n", MidPt.x, MidPt.y);
		//Find the midpoint, and write it to the sequence (auto-increments)
		CV_WRITE_SEQ_ELEM( MidPt, writer);
		//cvSeqPush(centerline,&MidPt);

		//Push the pointers along the boundaries in opposite directions
		CV_NEXT_SEQ_ELEM(sizeof(CvPoint),readerA);
		CV_PREV_SEQ_ELEM(sizeof(CvPoint),readerB);

		if (i> TotalBPts/2) {
			printf("Error. Malformed Worm!!! Breaking Loop\n");

			break ; // ANDY SOMETHING IS CRASHING IN THIS LOOP SOMETIMES!~!
		}
		// I NEED TO ADD SOME ERROR CHECKING
		i++;


	} while ( cvGetSeqReaderPos(&readerA)!=HeadIndex && cvGetSeqReaderPos(&readerB)!=HeadIndex  ) ;
	if (PRINTOUT) printf("Finished midpoint finding For Loop\n");
	cvEndWriteSeq( &writer );
	if (PRINTOUT) printf("Wrote centerline\n");



	/*
	 *
	 * Now we will use this centerline to help us define the left and right boundary of the worm
	 * in such a way that the points are spaced out to compensate for curvature.
	 * E.g. when the boundary of the worm curves towards the centerline ,
	 * there are less points than when the boundary of the worm curves away from the centerline.
	 *
	 */


	//	CvSeqReader readerA;
	//	CvSeqReader readerB;
	CvSeqReader readerC;
	CvSeqWriter writerA;
	CvSeqWriter writerB;

		CvSeq* OrigBoundA=cvSeqSlice(boundary,cvSlice(HeadIndex,TailIndex),more_storage,0);
		CvSeq* OrigBoundB=cvSeqSlice(boundary,cvSlice(TailIndex,HeadIndex),more_storage,0);
		cvSeqInvert(OrigBoundB);

//		/*
//		 *
//		 * As a Diagnostic Let's try to display our slices
//		 *
//		 */
//		for (i = 0; i < OrigBoundA->total; i++) {
//			CvPoint* tempPt = (CvPoint*) cvGetSeqElem(OrigBoundA, i);
//			cvCircle(g_gray, *tempPt, 1, cvScalar(255, 255, 255), 1);
//			cvWaitKey(5);
//			cvShowImage("Contours", g_gray);
//		}
//		for (i = 0; i < OrigBoundB->total; i++) {
//			CvPoint* tempPt = (CvPoint*) cvGetSeqElem(OrigBoundB, i);
//			cvCircle(g_gray, *tempPt, 1, cvScalar(255, 255, 255), 1);
//			cvWaitKey(5);
//			cvShowImage("Contours", g_gray);
//		}
//		printf("Hit Enter to continue\n");
//		cvWaitKey(0);


		if (PRINTOUT ){
			printf("OrigBoundA->total=%d , OrigBoundB->total=%d \n",OrigBoundA->total, OrigBoundB->total);
			cvWaitKey(0);
		}


		cvStartReadSeq(OrigBoundA,&readerA,0);
		cvStartReadSeq(OrigBoundB,&readerB,0);
		cvStartReadSeq(centerline,&readerC,0);

		CvSeq* OptimizedBoundaryA=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),more_storage);
		CvSeq* OptimizedBoundaryB=cvCreateSeq(CV_SEQ_ELTYPE_POINT,sizeof(CvSeq),sizeof(CvPoint),more_storage);


		//Set our pointer to the location along the boundary of the Tail.
		cvStartAppendToSeq(OptimizedBoundaryA,&writerA);
		cvStartAppendToSeq(OptimizedBoundaryB,&writerB);


		/*
		 * Let's define a new struct that captures all of the info for a single configuration
		 * The idea will be to push the pointer on the boundary around and find the configuration
		 * that minimizes the square distance
		 *
		 */
		typedef struct CenterlineBoundaryInstanceStruct{
			CvPoint Center;
			CvPoint SideA;
			CvPoint SideB;
			int sqdistA;
			int sqdistB;
			int indexA;
			int indexB;
		} CntrBndInst;

		CntrBndInst PrevConfig;
		CntrBndInst CurrConfig;



		//Let's have counters to keep track of where we are in Boundary A and Boundary B
		int BoundAIndex=0;
		int BoundBIndex=0;
		int FIRSTRUNFLAG=1;

		//Let's record the the first point of the centerline as the first point of the boundary.
		CvPoint* Temp=(CvPoint*) readerC.ptr;
		CV_WRITE_SEQ_ELEM( *Temp, writerA);
		CV_WRITE_SEQ_ELEM( *Temp, writerB);
		int LastRecordedBoundaryIndex=0;


		// Here the variable i acts as the centerline index counter.
		/*
		 * We will loop through points along the centerline and we will find the point along the
		 * boundary that corresponds best and record those points to form a new optimized
		 * description of the boundary. (Later on we will use THIS description of the boundary
		 * to find an optimized description of the centerline too.)
		 *
		 */
		for (i=0;i<centerline->total;i++){
			if (PRINTOUT) printf("i=%d PUSHING UP THE CENTERLINE\n",i);
			// This is the first time we are trying to find a boundary for a given centerpoint
			//Let's see what are current configuration is
				CurrConfig.Center =  *((CvPoint*) readerC.ptr);
				CurrConfig.SideA=*((CvPoint*)readerA.ptr);
				CurrConfig.SideB =*((CvPoint*)readerB.ptr);
				CurrConfig.sqdistA=sqDist(CurrConfig.SideA,CurrConfig.Center);
				CurrConfig.sqdistB=sqDist(CurrConfig.SideB,CurrConfig.Center);
				CurrConfig.indexA=BoundAIndex;
				CurrConfig.indexB=BoundBIndex;
				PrevConfig=CurrConfig;



			//If the distance between the centerline and boundary is smaller than last time
			// OR if this is the first time we're doing the comparison
			while ( (CurrConfig.sqdistA <= PrevConfig.sqdistA)){

				printf("Now we are incrementing the pointer along the boundary.\n");
				//We are about to take in the new configuration save the current as the previuos
				PrevConfig.SideA=CurrConfig.SideA;
				PrevConfig.sqdistA=CurrConfig.sqdistA;
				PrevConfig.indexA=CurrConfig.indexA;

				//Push the pointer up the boundary
				CV_NEXT_SEQ_ELEM(sizeof(CvPoint),readerA);
				BoundAIndex++;
				if (BoundAIndex > OrigBoundA->total) {
						if (PRINTOUT) printf("BoundAIndex=%d exceeds OrigBoundA->total=%d\n",BoundAIndex,OrigBoundA->total);
						break;
				}


				//Calculate the new parts of the new configuration
				CurrConfig.SideA=*((CvPoint*)readerA.ptr);
				CurrConfig.sqdistA=sqDist(CurrConfig.SideA,CurrConfig.Center);
				CurrConfig.indexA=BoundAIndex;
				if (PRINTOUT) printf("CurrConfig.SideA.x=%d,CurrConfig.SideA.y=%d\n",CurrConfig.SideA.x,CurrConfig.SideA.y);
				if (PRINTOUT) printf("CurrConfig.sqdistA= %d, \t PrevConfig.sqdistA= %d\n", CurrConfig.sqdistA,PrevConfig.sqdistA  );
				if (PRINTOUT) printf("BoundAIndex=%d\n", BoundAIndex);

			}

			/*
			 * Now that we've exited the while loop we know that
			 * the Current Configuration is less optimal then the Previous Configuration
			 */


			//Let's write out the Previous Configuration.
			//If this particuar pt on the Boundary has not been recorded already,
			if (PrevConfig.indexA != LastRecordedBoundaryIndex){
					//Then we should record it
					CV_WRITE_SEQ_ELEM( PrevConfig.SideA, writerA);
					//And we should take note of the fact that we recorded it
					LastRecordedBoundaryIndex=PrevConfig.indexA;
				} //Otherwise we should not record it


		/*
		 * NOW WE REPEAT THIS LOOP AND IF STATEMENM FOR SIDE B
		 *
		 */
			LastRecordedBoundaryIndex=0;

			//If the distance between the centerline and boundary is smaller than last time
			// OR if this is the first time we're doing the comparison
			while ( (CurrConfig.sqdistB <= PrevConfig.sqdistB)){

				printf("Now we are incrementing the pointer along the B-side boundary.\n");
				//We are about to take in the new configuration save the current as the previuos
				PrevConfig.SideB=CurrConfig.SideB;
				PrevConfig.sqdistB=CurrConfig.sqdistB;
				PrevConfig.indexB=CurrConfig.indexB;

				//Push the pointer up the boundary
				CV_NEXT_SEQ_ELEM(sizeof(CvPoint),readerB);
				BoundBIndex++;
				if (BoundBIndex > OrigBoundB->total) {
					if (PRINTOUT) printf("BoundBIndex=%d exceeds OrigBoundB->total=%d\n",BoundBIndex,OrigBoundB->total);
					break;
			}


				//Calculate the new parts of the new configuration
				CurrConfig.SideB=*((CvPoint*)readerB.ptr);
				CurrConfig.sqdistB=sqDist(CurrConfig.SideB,CurrConfig.Center);
				CurrConfig.indexB=BoundBIndex;
				if (PRINTOUT) printf("CurrConfig.SideB.x=%d,CurrConfig.SideB.y=%d\n",CurrConfig.SideB.x,CurrConfig.SideB.y);
				if (PRINTOUT) printf("CurrConfig.sqdistB= %d, \t PrevConfig.sqdistB= %d\n", CurrConfig.sqdistB,PrevConfig.sqdistB  );
				if (PRINTOUT) printf("BoundBIndex=%d\n", BoundBIndex);

			}

			/*
			 * Now that we've exited the while loop we know that
			 * the Current Configuration is less optimal then the Previous Configuration
			 */


			//Let's write out the Previous Configuration.
			//If this particuar pt on the Boundary has not been recorded already,
			if (PrevConfig.indexB != LastRecordedBoundaryIndex){
					//Then we should record it
					CV_WRITE_SEQ_ELEM( PrevConfig.SideB, writerB);
					//And we should take note of the fact that we recorded it
					LastRecordedBoundaryIndex=PrevConfig.indexB;
				} //Otherwise we should not record it

		}





	/*
	 *
	 * Now that we have a centerline, we would like to define a coordinate system, say 100 points
	 * along the centerline. The correct way to do this would be to calculate the arclength along the
	 * centerline and then make everything evenly spaced. The problem is, that this would require taking a
	 * lot of square roots, which would be computationally intensive.
	 *
	 * For now, we will cheat. We will assume that we have so many points along the centerline N, that
	 * when course-grained, they are rouglhy evenly spaced.
	 *
	 * To implement this we will walk aong the centerline and record the coordinates of the first 99 every (n=N/100)th
	 * points. The 100th point will be the Head.
	 *
	 * This is not great, because the points will likely not be equally spaced, but it should be a good start.
	 *
	 */

	//	CvSeqReader readerA;
	//	CvSeqWriter writer;
	int NUMSEGMENTS = 100;
	CvSeq* centerCoordinate;
		centerCoordinate = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq),
				sizeof(CvPoint), more_storage);

	/*
	 * Resample the centerline.
	 *
	 */
	resampleSeq(centerline,&centerCoordinate,NUMSEGMENTS);

	CvSeq* BoundarySideA;
	CvSeq* BoundarySideB;
	BoundarySideA= cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq),
					sizeof(CvPoint), more_storage);
	BoundarySideB = cvCreateSeq(CV_SEQ_ELTYPE_POINT, sizeof(CvSeq),
					sizeof(CvPoint), more_storage);
//
//	/*
//	 * Resamle the left and right boundaries OLD SCHOOl STYLE
//	 *
//	 */
//	if (PRINTOUT) printf("Resampling BoundarySideA\n");
//	resampleSeq(cvSeqSlice(boundary,cvSlice(TailIndex,HeadIndex),more_storage,0),&BoundarySideA,NUMSEGMENTS);
//	if (PRINTOUT) printf("BoundarySideA->total=%d\n",BoundarySideA->total);
//	if (PRINTOUT) printf("Resampling BoundarySideB\n");
//	resampleSeq(cvSeqSlice(boundary,cvSlice(HeadIndex,TailIndex),more_storage,0),&BoundarySideB,NUMSEGMENTS);
//	if (PRINTOUT) printf("BoundarySideB->total=%d\n",BoundarySideB->total);
//	//cvSeqInvert(BoundarySideB); // we need to reorder the boundary





	/*
	 * Resamle the left and right boundaries OLD SCHOOl STYLE
	 *
	 */
	if (PRINTOUT) printf("Resampling BoundarySideA\n");
	resampleSeq(OptimizedBoundaryA,&BoundarySideA,NUMSEGMENTS);
	if (PRINTOUT) printf("BoundarySideA->total=%d\n",BoundarySideA->total);
	if (PRINTOUT) printf("Resampling BoundarySideB\n");
	resampleSeq(OptimizedBoundaryB,&BoundarySideB,NUMSEGMENTS);
	if (PRINTOUT) printf("BoundarySideB->total=%d\n",BoundarySideB->total);
	//cvSeqInvert(BoundarySideB); // we need to reorder the boundary







	/*
	 *
	 * Draw a rectangle on the worm to illuminate it.
	 */
	int radius=20;
//	IlluminateWormSegment(&g_gray,centerCoordinate,10,radius);
//	IlluminateWormSegment(&g_gray,centerCoordinate,11,radius);
//	IlluminateWormSegment(&g_gray,centerCoordinate,12,radius);
//	IlluminateWormSegment(&g_gray,centerCoordinate,13,radius);
//	IlluminateWormSegment(&g_gray,centerCoordinate,14,radius);



	printf("About to show image.\n");
	DrawSequence(&g_gray,centerline);
//	DrawSequence(&g_gray,BoundarySideA);
	for (i = 0; i < BoundarySideA->total; i++) {
		CvPoint* tempPt = (CvPoint*) cvGetSeqElem(BoundarySideA, i);
		cvCircle(g_gray, *tempPt, 1, cvScalar(255, 255, 255), 1);
		cvWaitKey(5);
		cvShowImage("Contours", g_gray);
	}

	//	DrawSequence(&g_gray,BoundarySideB);
//	for (i = 0; i < BoundarySideB->total; i++) {
//		CvPoint* tempPt = (CvPoint*) cvGetSeqElem(BoundarySideB, i);
//		cvCircle(g_gray, *tempPt, 1, cvScalar(255, 255, 255), 1);
//		cvWaitKey(5);
//		cvShowImage("Contours", g_gray);
//	}



////	 Draw lines connecting sequence
	cvStartReadSeq(BoundarySideA,&readerA,0);
	cvStartReadSeq(BoundarySideB,&readerB,0);
	//cvSetSeqReaderPos(&readerA, 2, 1);
	for (i=0;i<BoundarySideA->total;i++){

		SideA=(CvPoint*)readerA.ptr;
		SideB=(CvPoint*)readerB.ptr;
		cvLineAA(g_gray,*SideA,*SideB,255,0);
		CV_NEXT_SEQ_ELEM(sizeof(CvPoint),readerA);
		CV_NEXT_SEQ_ELEM(sizeof(CvPoint),readerB);
//		cvWaitKey(300);
//		cvShowImage("Contours", g_gray);
	}


	if (ONSCREEN) cvShowImage("Contours", g_gray);
}





int main (int argc, char** argv){

	if (PRINTOUT) printf("This program reads in a jpg, finds a worm, and segments it.");
	if( argc != 2 || !(g_image = cvLoadImage(argv[1])) ) return -1;

	cvNamedWindow("Original");
	if (ONSCREEN) cvShowImage("Original",g_image);
	cvNamedWindow("Smoothed");
	cvNamedWindow( "Thresholded");
	cvNamedWindow( "Contours", 1);
	cvNamedWindow("Controls");
	cvCreateTrackbar("Threshold", "Controls", &g_thresh,255, on_trackbar);
	cvCreateTrackbar("Gauss=x*2+1","Controls", &gauss_size,5, on_trackbar);
	cvCreateTrackbar("ScalePx","Controls", &Delta,15,on_trackbar);
	cvCreateTrackbar("Offset Comp","Controls",&Offset,15, on_trackbar);


//	/*
//	 * Time Test
//	 *
//	 */
//	int NumLoops=1000;
//	int i;
//	printf("Ready...\n");
//	cvWaitKey();
//	printf("Start a Thousand Loops\n");
//	for (i=0; i<NumLoops; i++){
//	on_trackbar(0);
//	if (i%100==0) printf(".");
//	}
//	printf("Finished!\n");

	on_trackbar(0);
	cvWaitKey();
	cvReleaseImage(&g_gray);
	cvReleaseImage(&thresh_img);
	cvReleaseImage(&g_image);
	return 0;
}

/*
 * Illuminate a segment of the worm. Either the right, or left side.
 * Takes a sequence of the centerline. Uses the preceeding point to find a vector
 * along the centerline, than draws a rectangle perpendicular to this vector, a radius rsquared pixels
 * away from the centerline
 */
void IlluminateWormSegment(IplImage** image, CvSeq* centerline, int segment, int rsquared){
	if (segment <1) {
		printf("ERROR: segment <1 :  Choose a segment along the worm that is at least 1.\n ");
		return;
	}

	CvPoint* PtAlongCenterline;
	CvPoint* PrevPtAlongCenterline;
	CvPoint Vec; //Vector along the segment
	CvPoint PerpVec; //Vector Perpendicular to the segment
	PtAlongCenterline=(CvPoint*) cvGetSeqElem(centerline,segment);
	PrevPtAlongCenterline=(CvPoint*) cvGetSeqElem(centerline,segment-1);
	Vec= cvPoint(PtAlongCenterline->x - PrevPtAlongCenterline->x ,PtAlongCenterline->y - PrevPtAlongCenterline->y );
	printf("Vec=( %d,%d )\n",Vec.x, Vec.y);
	// To find the two vectors perpindicular to (x,y)  we have just +/- (-y,x)
	PerpVec=cvPoint( 0 - Vec.y,Vec.x);

	CvPoint* pt[1];
	CvPoint ptt[4];
	pt[0]= & (ptt[0]);

	pt[0]=&(ptt[0]);
	pt[0][0].x=PtAlongCenterline->x;
	pt[0][0].y=PtAlongCenterline->y;
	pt[0][3].x= pt[0][0].x+ rsquared/( (PerpVec.y)^2+(PerpVec.x)^2)  * PerpVec.x;
	pt[0][3].y= pt[0][0].y+ rsquared/( (PerpVec.y)^2+(PerpVec.x)^2)  * PerpVec.y;
	pt[0][1].x=PrevPtAlongCenterline->x;
	pt[0][1].y=PrevPtAlongCenterline->y;
	pt[0][2].x= pt[0][1].x+ rsquared/( (PerpVec.y)^2+(PerpVec.x)^2)  * PerpVec.x;
	pt[0][2].y= pt[0][1].y+ rsquared/( (PerpVec.y)^2+(PerpVec.x)^2)  * PerpVec.y;
	printf("Pt1=( %d, %d)\nPt2=( %d, %d)\nPt3=( %d, %d)\nPt4=( %d, %d)\n",pt[0][0].x,pt[0][0].y,pt[0][1].x,pt[0][1].y,pt[0][2].x,pt[0][2].y,pt[0][3].x,pt[0][3].y);

	//CvPoint rectangle[]={cvPoint(x1,y1), cvPoint(x2,y2), cvPoint(x3,y3), cvPoint(x4,y4)};
	//CvPoint* rectangleArr[1]={rectangle};
	int nRectpoints[1];
	nRectpoints[0]=4;
	int nRectangles=1;




	printf("Before cvFillPoly\n");

	//cvRectangle(*image,cvPoint(10,10),cvPoint(300,300),cvScalar(255,255,255),1,CV_AA,0);
	cvFillPoly(*image,pt,nRectpoints,nRectangles,cvScalar(255,255,255),CV_AA,0);
	printf("After cvFillPoly\n");



}


