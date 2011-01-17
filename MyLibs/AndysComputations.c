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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "AndysComputations.h"



/*
 * Calculates the distance between two points on a ciruclar boundary
 * with total points PtsOnBound for two points with zero-indexed indices
 * IndexA and IndexB.
 *
 */
int DistBetPtsOnCircBound(int PtsOnBound, int IndexA, int IndexB){
	int distance;
	if (labs(IndexA-IndexB)<labs(PtsOnBound- labs(IndexA-IndexB))){//go with the smallest value
		distance=labs(IndexA-IndexB);
	}else{
		distance=labs(PtsOnBound- labs(IndexA-IndexB));
	}
	return distance;
}


/*
 * This is a wrapper for the modulo function.
 * Every time frameNum is divisible by HowOften with no remainder
 * the function returnst true (1).
 * Otherwise it returns false (0).
 *
 * If HowOften is 0 then the function always returns false.
 * If the inputs are invalid then the function returns -1.
 *
 */
int EverySoOften(int frameNum, int HowOften){
	if ( frameNum<0 || HowOften<0) return -1;
	if (HowOften==0) return 0;
	if ((frameNum % HowOften)==0){
		return 1;
	}
	return 0;
}


/*
 * Given two clock_t objects, this function returns an int
 * containing the elapsed time in milliseconds
 *
 */
unsigned long msElapsed(clock_t start, clock_t end){
	unsigned long temp = (end-start * 1000);
	return temp / CLOCKS_PER_SEC;
}



/*
 * Takes a clock_t type and returns an integer with the number of seconds
 * For the reamining milliseconds use GetMilliseconds
 *
 */
int GetSeconds(clock_t time){
	double seconds = (double) time / (double) CLOCKS_PER_SEC;
	return (int) seconds;
}

/*
 * Takes a clock_t type and returns the remaining number of ms
 * since GetSeconds();
 *
 *
 */
int GetMilliSeconds(clock_t time){
	/* Get number of seconds very accurately */
	double seconds = (double) time / (double) CLOCKS_PER_SEC;

	/* Round off to get the whole number of seconds */
	int rounded= (int) seconds;

	/* Subtract off the whole number of secods and multiply by 1000 */
	double ms= ( (double) seconds-rounded) *1000;
	return (int) ms;
}

/*
 * Toggles an integer from zero to 1.
 * If x is nonzero, sets x to zero.
 * If x is zero, sets x to one.
 */
void Toggle(int* x){
	if (*x==0) {
		*x=1;
	} else {
		*x=0;
	}
	return;
}

/*
 * Safely decrement an integer value, as long as the result will not be less than min.
 */
void Decrement(int* x, int min){
	if ((*x) >min) (*x)--;
	return;
}

/*
 * Safely increment an integer value as long as the result will not be grater than max.
 */
void Increment (int* x, int max){
	if ((*x) < max) (*x)++;
	return;
}


