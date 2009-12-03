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
 * Calculates the distance between two points on a ciruclar boundar
 * with total points PtsOnBound for two points with zero-indexed indices
 * IndexA and IndexB
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
 * takes a clock_t type and returns an integer with the number of seconds
 * For the reamining milliseconds use GetMilliseconds
 *
 */
int GetSeconds(clock_t time){
	double seconds = (double) time / (double) CLOCKS_PER_SEC;
	return (int) seconds;
}

/*
 * takes a clock_t type and returns the remaining number of ms
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


/************************************************/
/*   Marc's Timing Profiler
 *
 */
/************************************************/

/*
 * Creates Marc's time profiler object and sets all
 * values to zero.
 *
 * This object is used to create profiles of what
 * takes how long to execute in the code.
 *
 */
TimeProfile* CreateTimeProfiler(){
	TimeProfile* p=(TimeProfile*) malloc(sizeof(TimeProfile));
	p->nframes=0;
	p->nframes=0;
	p->now=0;
	p->last=0;

	for (int j = 0; j < _N_TIME_PTS; ++j) {
		p->total_time[j] = 0;
	}
	/** Create memory and objects **/
	return p;
}


/*
 *  Destroy's the time profiler object.
 */
void DestroyTimeProfiler(TimeProfile** profiler){
	free(profiler);
	*profiler=NULL;
}

/*
 * Resets the timer. And prepares it for subsequent tocs.
 * Usage: one Tic() followed by many Toc()'s
 *
 */
void Tic(TimeProfile* profiler){
	profiler->last = clock();
	profiler->tnum = 0;
	++(profiler->nframes);
}

/*
 * Defines the end of the current time period for profiling. And prepares for subsequent timings.
 * Usage: one Tic() followed by many Toc()'s
 *
 */

void Toc(TimeProfile* profiler){
	profiler->total_time[profiler->tnum++] += ((profiler->now = clock()) - profiler->last);
	profiler->last = profiler->now;
}

/*
 *
 * Print out the time profiler
 * generated from the Tic() followed by Tocs()
 */
void DisplayTimeProfile(TimeProfile* profiler){
	int nrecordedtime = profiler->tnum;
	for (int j = 0; j < nrecordedtime; ++j) {
		printf("\nProfile Results\ntime %d: total time %d\ttime per frame:%g\n", j, profiler->total_time[j], (1.0*profiler->total_time[j])/profiler->nframes);
	}

}





