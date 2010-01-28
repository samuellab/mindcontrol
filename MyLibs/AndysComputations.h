/*
 * AndysComputations.h
 *
 *  Created on: Aug 18, 2009
 *      Author: Andy
 */

#ifndef ANDYSCOMPUTATIONS_H_
#define ANDYSCOMPUTATIONS_H_


#define _N_TIME_PTS 100

typedef struct TimeProfileStruct{
	int tnum;
	int nframes;
	int total_time[_N_TIME_PTS];
	clock_t now;
	clock_t last;
}TimeProfile;


/*
 * Calculates the distance between two points on a ciruclar boundar
 * with total points PtsOnBound for two points with zero-indexed indices
 * IndexA and IndexB
 *
 */
int DistBetPtsOnCircBound(int PtsOnBound, int IndexA, int IndexB);



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
int EverySoOften(int frameNum, int HowOften);


/*
 * Given two clock_t objects, this function returns an int
 * containing the elapsed time in milliseconds
 *
 */
unsigned long msElapsed(clock_t start, clock_t end);



/*
 * takes a clock_t type and returns an integer with the number of seconds
 * For the reamining milliseconds use GetMilliseconds
 *
 */
int GetSeconds(clock_t time);

/*
 * takes a clock_t type and returns the remaining number of ms
 * since GetSeconds();
 *
 *
 */
int GetMilliSeconds(clock_t time);








#endif /* ANDYSCOMPUTATIONS_H_ */
