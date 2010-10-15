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
 * DontTalk2Cam.c
 *
 *  Created on: Dec 17, 2009
 *      Author: Andy
 */
#include <assert.h>
#include <Talk2Camera.h>

/**
 *
 * This library is a bit of a hack.
 *
 * The idea is that sometimes we want to compile libraries like experiment.c
 * that access hardware specific functionality such as functions in:
 *	Talk2Camera.c
 *
 * Anyway. The point is that I would like to be able to occasionally include libraries
 * that call functions in these libraries, even though I don't actually
 * ever use these functions at runtime.
 *
 * So to avoid linker errors I am writing this Talk2Camera.c
 * which basically redefines all of the camera specific functions.
 */

void T2Cam_errormsg(){
	printf("\n\nERROR.\n");
	printf("It appears as though a camera-specific function was called.\n");
	printf("This software was compiled without camera-spefici libraries.\n");
	printf("Try running the software using a video file as input by invoking the -i switch.\n\n");
}

/*
 * Initalizes the library and provides the  license key for
 * the Imaging control software. The function returns a
 * non-zero value if successful.
 */
int T2Cam_InitializeLib(){
	T2Cam_errormsg();
	assert(0);
	return 0;
}

/*
 * Closes the library.
 *
 */
void T2Cam_CloseLib(){
	T2Cam_errormsg();
	assert(0);
}


/*
 * In continuousmode, callback is called every time the camera acquires
 * a new frame. The callback populates the data structure "Data" using the
 * CamData data type.
 *
 */
void _cdecl callback(HGRABBER hGrabber, unsigned char* pData,
		unsigned long frameNumber, void*){
	T2Cam_errormsg();
	assert(0);
}

/*
 * Given a pointer to a CamData type, this function will allocate
 * memory.
 */
void T2Cam_AllocateCamData(CamData** CameraDataStruct){
	T2Cam_errormsg();
	assert(0);
}

/*
 * Show the Device Selection Dialog, initilize the camera and store the resulting
 * framegrabber handle in CamData->hgrabber.
 *
 * CameraInfo must already have memory allocated
 */
void T2Cam_ShowDeviceSelectionDialog(CamData** CameraInfo){
	T2Cam_errormsg();
	assert(0);
}

/*
 * Sets up the camera in continuous mode and tells the camera to begin
 * continuously grabbing frames and calling the callback function.
 *  This requires a pointer to a CamData type
 * that has memory already allocated.
 *
 * This begins thread that calls a Callback function
 *  that immediately begins dumping data into CameraDataStruct
 */
void T2Cam_GrabFramesAsFastAsYouCan(CamData** CameraDataStruct){
	T2Cam_errormsg();
	assert(0);
}

/*
 *
 * Takes a CameraDataStruct with an initialized frame grabber
 * and turns it off.
 *
 */
void T2Cam_TurnOff(CamData** CameraDataStruct){
	T2Cam_errormsg();
	assert(0);
}

