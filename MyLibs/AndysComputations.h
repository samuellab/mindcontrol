/*
 * AndysComputations.h
 *
 *  Created on: Aug 18, 2009
 *      Author: Andy
 */

#ifndef ANDYSCOMPUTATIONS_H_
#define ANDYSCOMPUTATIONS_H_


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


#endif /* ANDYSCOMPUTATIONS_H_ */
