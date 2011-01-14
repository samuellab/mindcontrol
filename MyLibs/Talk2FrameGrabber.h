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

#define T2FG_ERROR -1
#define T2FG_SUCCESS 0

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
 * Set the acquisition timeout time, t, in ms.
 *
 * This must be greater than the exposure time, or all of your exposures will timeout.
 * If this number is too high, then when the camera has an error, it will hang your program for a long time.
 *
 */
int setAcquisitionTimeout(FrameGrabber* fg, int t);


/*
 * The acquired frame is plopped into fg->Hostbuf
 */
int AcquireFrame(FrameGrabber* fg);

int CloseFrameGrabber(FrameGrabber* fg);


#endif /* TALK2FRAMEGRABBER_H_ */
