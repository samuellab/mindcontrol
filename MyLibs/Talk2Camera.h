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
 * Talk2Camera.h
 *
 *  Created on: Jul 16, 2009
 *      Author: Andy
 */

#ifndef TALK2CAMERA_H_
#define TALK2CAMERA_H_
#include "../3rdPartyLibs/tisgrabber.h"
#include <stdio.h>

#define PRINT_DEBUG 0

/*
 * We define a new variable type, "CamData" which is a struct that
 * holds information about the current Data in the camera.
 *
 * The actual data resides in *iImageData
 * The i notation indicates that these are internal values. e.g.
 * iFrameNumber refers to the FrameNumber that the camera sees,
 *
 */
typedef struct CamDataStruct CamData;
struct CamDataStruct {
	HGRABBER hGrabber;
	int iDeviceCount;
	int iHeight;
	int iWidth;
	int iBitsPerPixel;
	unsigned char *iImageData;
	COLORFORMAT iColorFormat;
	int iProcessing;
	unsigned long iFrameNumber;
};

/*
 * Rows and pixels of camera
 */
#define CCDSIZEX 1024
#define CCDSIZEY 768

/*
 * Initalizes the library and provides the  license key for
 * the Imaging control software. The function returns a
 * non-zero value if successful.
 */
int T2Cam_InitializeLib();

/*
 * Closes the library.
 *
 */
void T2Cam_CloseLib();

/*
 * In continuousmode, callback is called every time the camera acquires
 * a new frame. The callback populates the data structure "Data" using the
 * CamData data type.
 *
 */
void _cdecl callback(HGRABBER hGrabber, unsigned char* pData,
		unsigned long frameNumber, void*);

/*
 * Given a pointer to a CamData type, this function will allocate
 * memory.
 */
void T2Cam_AllocateCamData(CamData** CameraDataStruct);

/*
 * Show the Device Selection Dialog, initilize the camera and store the resulting
 * framegrabber handle in CamData->hgrabber.
 *
 * CameraInfo must already have memory allocated
 */
void T2Cam_ShowDeviceSelectionDialog(CamData** CameraInfo);

/*
 * Sets up the camera in continuous mode and tells the camera to begin
 * continuously grabbing frames and calling the callback function.
 *  This requires a pointer to a CamData type
 * that has memory already allocated.
 *
 * This begins thread that calls a Callback function
 *  that immediately begins dumping data into CameraDataStruct
 */
void T2Cam_GrabFramesAsFastAsYouCan(CamData** CameraDataStruct);

/*
 *
 * Takes a CameraDataStruct with an initialized frame grabber
 * and turns it off.
 *
 */
void T2Cam_TurnOff(CamData** CameraDataStruct);


void T2Matlab_ArrayTest();

#endif /* TALK2CAMERA_H_ */
