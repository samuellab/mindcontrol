/*
 * T2DLP.h
 *
 *  Created on: Jul 3, 2009
 *      Author: Andy
 */

#ifndef T2DLP_H_
#define T2DLP_H_

//Andy: I need to move this to the .h file soon.
long T2DLP_on(); //returns the ID of the DMD
int T2DLP_off(long alpid); //takes an ID of the DMD
int T2DLP_SendFrame(unsigned char *image, long alpid);
unsigned char *SampleImages( unsigned long nSizeX, unsigned long nSizeY );


#define	T2DLP_HAPPY	 	0
#define	T2DLP_SAD		-1


/*Hard Code in the dimensions.
 *  We are Using ALPB_DMDTYPE_XGA_055X
 *  Which is XGA .55 Type X
 *  1024 by 768 mirrors
 */
#define NSIZEX 1024
#define NSIZEY 768

#endif /* T2DLP_H_ */
