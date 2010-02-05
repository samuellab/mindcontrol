
/** C includes **/
#include <assert.h>
#include    <stdio.h>
#include    <conio.h>

/** BitFlow SDK includes **/


#include "Talk2FrameGrabber.h"

/*
 *
 * This library is a bit of a hack.
 *
 * The idea is that sometimes we want to compile libraries that depend on hardware
 * in a hardware independent way. This is useful for simulations and debugging on
 * machines that don't have the hardware installed nor the SDK's and libraries
 * that come with the hardware.
 *
 *
 * So to avoid linker errors I am writing this DontTalk2FrameGrabber.cpp
 * which basically redefines all of the hardware specific functions.
 */



void T2FrameGrabber_errormsg(){
	printf("\n\nERROR.\n");
	printf("It appears as though a FrameGrabber-specific function was called.\n");
	printf("This software was compiled without the FrameGrabber specific libraries.\n");
	printf("Try running the software without useing the frame grabber, -g, switch.\n\n");
}

FrameGrabber* CreateFrameGrabberObject(){

	T2FrameGrabber_errormsg();
	assert(0);

	return 0;

}

/*
 * Higher Level Function to Ready the frameGrabber
 * Creates framegragbber object
 * Initilizes the frame grabber
 * sets the region of interest
 * and prepares the FrameGrabber for Acuisiation
 *
 */
FrameGrabber* TurnOnFrameGrabber(){
	T2FrameGrabber_errormsg();
		assert(0);
		return 0;

}



/*
 * Initializes the frame grabber with a fg object
 * that has already been created using CreateFrameGrabberObject()
 *
 */
int InitializeFrameGrabber(FrameGrabber* fg){

	T2FrameGrabber_errormsg();
	assert(0);

	return 0;

}

/**
 * Set the region of interest to grab from from the frame grabber.
 * This in effect will override the camera file settings.
 * xsize must be  multiple of 4
 *
 * Runthis before PrepareFrameGrabberForAcquire
 */
int FrameGrabberSetRegionOfInterest(FrameGrabber* fg,int xoff, int yoff,int xsize,int ysize){
	T2FrameGrabber_errormsg();
	assert(0);

	return 0;
}


int PrepareFrameGrabberForAcquire(FrameGrabber* fg){
	T2FrameGrabber_errormsg();
	assert(0);

	return 0;

}



/*
 * The acquired frame is plopped into fg->Hostbuf
 */
int AcquireFrame(FrameGrabber* fg){
	T2FrameGrabber_errormsg();
	assert(0);

	return 0;
}


int CloseFrameGrabber(FrameGrabber* fg){

	T2FrameGrabber_errormsg();
	assert(0);

	return 0;
}
