/*
 * Talk2FrameGrabber.h
 *
 *  Created on: Jan 11, 2010
 *      Author: Andy
 */

#ifndef TALK2FRAMEGRABBER_H_
#define TALK2FRAMEGRABBER_H_

/** BitFlow SDK includes **/
#include    "CiApi.h"
#include	"BFApi.h"
#include	"BFErApi.h"
#include	"DSApi.h"


/*
 * Thread to update the video display
 * using the BitFlow SDK.
 *
 */


typedef struct FrameGrabberStruct {

	PBFU8 HostBuf;

	PBFVOID pBitmap; // Location of BitMap for Display
	int hDspSrf; // handle to display surface
	Bd hBoard; //Pointer to the board
	BFBOOL Running; // Lets the small thread know if the main code is running
	BFU32 ImageSize; //Overall image size (not x-y coordinates)
	BFU32 BitDepth;

	BFU32 OrigTrigMode;
	BFBOOL WasOneShot;

	BFU32 xsize;
	BFU32 ysize;

	int keeplooping;
	int overflowcount;

	/** Random Trigger settings **/
	BFU32 TrigMode, TrigAPolarity, TrigBPolarity, TrigAssign;

	BFBOOL ContinuousData;

} FrameGrabber;




FrameGrabber* CreateFrameGrabberObject();



/*
 * Higher Level Function to Ready the frameGrabber
 * Creates framegragbber object
 * Initilizes the frame grabber
 * sets the region of interest
 * and prepares the FrameGrabber for Acuisiation
 *
 */
FrameGrabber* TurnOnFrameGrabber();

/*
 * Initializes the frame grabber with a fg object
 * that has already been created using CreateFrameGrabberObject()
 *
 */
int InitializeFrameGrabber(FrameGrabber* fg);


/**
 * Set the region of interest to grab from from the frame grabber.
 * This in effect will override the camera file settings.
 * xsize must be  multiple of 4
 *
 * Runthis before PrepareFrameGrabberForAcquire
 */
int FrameGrabberSetRegionOfInterest(FrameGrabber* fg,int xoff, int yoff,int xsize,int ysize);

int PrepareFrameGrabberForAcquire(FrameGrabber* fg);


/*
 * The acquired frame is plopped into fg->Hostbuf
 */
int AcquireFrame(FrameGrabber* fg);

int CloseFrameGrabber(FrameGrabber* fg);


#endif /* TALK2FRAMEGRABBER_H_ */
