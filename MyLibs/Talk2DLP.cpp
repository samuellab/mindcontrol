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
Talk2DLP.cpp
This is the first iteration of my interface to talk to the DLP.
It utilizes the ALPbasic dll from vialux.
It is roughly follows the sample code in Console ALP-4.cpp included with the
ALPBasic software

3 July 2009
Andrew Leifer
leifer@fas.harvard.edu
*/



#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "../3rdPartyLibs/alpbasic.h"
#include "Talk2DLP.h"



long T2DLP_on(){
	printf("Trying to turn the DLP on.\n");
	long ret; // this is for what the ALPbDevAlloc will return
	unsigned long serial; // This will be the serial number for
	long alpid; // Create an ID for the DMD.

	//Allocate memory for the DMD
	ret = AlpbDevAlloc( 0, &alpid );
	if (0>ret) {// If that didn't work
		printf("DLP Error: AlpbDevAlloc\n"); //clean up.
		AlpbDevFree((ALPB_HDEVICE) alpid );	// close device driver
		return (long) T2DLP_SAD; //throw an error.

	}

	// Query serial number
	ret = AlpbDevInquire( alpid, ALPB_DEV_SERIAL, &serial );
	if (0>ret){
		printf("Error: AlpbDevInquire (Serial number)\n");
		AlpbDevFree((ALPB_HDEVICE) alpid );	// close device driver
		return (long) T2DLP_SAD;
	}
	printf( "The allocated ALP has the serial number %f\n", serial );
	printf("Alpid is %f\n",alpid);
	T2DLP_clear(alpid);
	return alpid;
}



/*
 * Clear the DLP mirrors
 */
int T2DLP_clear(long myDLP){
	AlpbDevReset((ALPB_HDEVICE) myDLP, ALPB_RESET_GLOBAL,0);
	return 0;
}

int T2DLP_off(long alpid){
	printf("Inside T2DLP_off().. Closing the device driver.");
	AlpbDevReset((ALPB_HDEVICE) alpid, ALPB_RESET_GLOBAL,0);
	AlpbDevFree((ALPB_HDEVICE) alpid );	// close device driver
	return T2DLP_HAPPY;
}

int T2DLP_SendFrame(unsigned char * image, long alpid){
	//printf("Inside T2DLP_SendFrame()\nAbout to call AlpbDevLoadRows()\n");
	long ret;
	ret= AlpbDevLoadRows( alpid, image, 0, NSIZEY-1 );
	if (0>ret){
		printf("DLP: Error sending image to DLP.\n");
	}
	//printf("About to reset mirrors.\n");
	// Reset DMD mirrors
	ret = AlpbDevReset( alpid, ALPB_RESET_GLOBAL, 0 );
	//printf("Exiting T2DLP_SendFrame()\n");
	return (int) ret;
}




unsigned char *SampleImages( unsigned long nSizeX, unsigned long nSizeY )
{
	unsigned long x, y;
	unsigned char *image;

	image = (unsigned char*) malloc( nSizeX*nSizeY*3 );
	if (NULL != image) {
		// Picture 0: horizontal bars
		for (y=0; y<nSizeY; y++)
			FillMemory(
				image + 0*nSizeY*nSizeX + y*nSizeX,	// row start address
				nSizeX,	// row size in bytes
				(y&64)? 0 : 128 );	// image data: either 0 or 128

		// Picture 1:  checkered pattern
		for (y=0; y<nSizeY; y++)
			for (x=0; x<nSizeX; x++)
				image[1*nSizeY*nSizeX + y*nSizeX + x] =	
					(unsigned char) ((x^y)& 32)? 0 : 128;

		// Picture 2:  vertical bars
		for (y=0; y<nSizeY; y++)
			for (x=0; x<nSizeX; x++)
				image[2*nSizeY*nSizeX + y*nSizeX + x] =	
					(unsigned char) (x&256)? 0 : 128;
	}

	return image;
}

