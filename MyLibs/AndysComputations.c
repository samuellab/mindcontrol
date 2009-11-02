/*
 * AndysComputations.c
 *
 *  Created on: Aug 18, 2009
 *      Author: Andy
 */

/*
 * This library contains functions that perform custom image processing-related computations that are independent
 * of the OpenCV library.
 *
 * Other custom computer vision routines are stored in AndysOpenCVLib.h and AndysOpenCVLib.c
 *
 *
 */

#include "AndysComputations.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Calculates the distance between two points on a ciruclar boundar
 * with total points PtsOnBound for two points with zero-indexed indices
 * IndexA and IndexB
 *
 */
int DistBetPtsOnCircBound(int PtsOnBound, int IndexA, int IndexB){
	int distance;
	if (labs(IndexA-IndexB)<labs(PtsOnBound-(IndexA-IndexB))){//go with the smallest value
		distance=labs(IndexA-IndexB);
	}else{
		distance=labs(PtsOnBound-(IndexA-IndexB));
	}
	return distance;
}


/*
 * This is a wrapper for the modulo function.
 * Every time  framenumber is divisible by HowOftne with no remainder
 * the function returnst true (1).
 * Otherwise it returns false (0).
 *
 * If HowOften is 0 then the function always returns false.
 * If the inputs are invalid then the function returns -1.
 *
 */
int EverySoOften(int frameNum, int HowOften){
	if (frameNum==NULL || HowOften==NULL || frameNum<0 || HowOften<0) return -1;
	if (HowOften==0) return 0;
	if ((frameNum % HowOften)==0){
		return 1;
	}
	return 0;
}

