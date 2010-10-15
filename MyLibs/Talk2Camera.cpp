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
 * Talk2Camera.c
 *
 * Created on 16 July 2009
 *   by Anddrew Leifer
 *   leifer@fas.harvard.edu
 *
 *   Talk2Camera is a library to interface with ImagingSource camera's
 *   It uses a number of supplied wrapper libraries from the ImagingSource
 *
 *   It depends on: tisgrabber.h, tisgrabber.lib and tisgrabber.dll
 *
 */
#include "../3rdPartyLibs/tisgrabber.h"
#include "Talk2Camera.h"
#include <stdio.h>
#include <stdlib.h>

// Do we print debugging output?


/*
 * Initalizes the library and provides the  license key for
 * the Imaging control software. The function returns a
 * non-zero value if successful.
 */
int T2Cam_InitializeLib() {
	//HardCode in the key to initialize the ImagingSource Library
	return IC_InitLibrary("ISB3200208905");
}



void T2Cam_CloseLib() {
	//HardCode in the key to initialize the ImagingSource Library
	IC_CloseLibrary();
}


/*
 * Given a pointer to a CamData type, this function will allocate
 * memory.
 */
void T2Cam_AllocateCamData(CamData** MyCamera) {
	printf("inside T2Cam_AllocateCamData\n");
	*MyCamera = (CamData*) malloc(sizeof(CamData));
}

/*
 * Show the Device Selection Dialog and return a handle to the frame
 * grabber
 */
void T2Cam_ShowDeviceSelectionDialog(CamData** CameraInfo) {
	printf("There are this many devices: %d\n",IC_ListDevices(NULL,NULL));

	printf("Inside T2Cam_ShowDeviceSelectionDialog()\n");
	HGRABBER tempgrabber=NULL;
	printf("opening DeviceSelectionDialog...\n");
	tempgrabber=IC_ShowDeviceSelectionDialog(NULL);
	(*CameraInfo)->hGrabber =tempgrabber;
	int ret;
	ret=IC_IsDevValid((*CameraInfo)->hGrabber);
	if (ret==0) {
		printf("This device is not valid!!!\n");
	}else{
		printf("The device is valid.\n");
	}

}

/*
 * Set's up the camera in continuous mode and tells the camera to begin
 * continuously grabbing frames and calling the callback function.
 *  This requires a pointer to a CamData type
 * that has memory already allocated.
 *
 * This begins thread that calls a Callback function
 *  that immediately begins dumping data into CameraDataStruct
 */
void T2Cam_GrabFramesAsFastAsYouCan(CamData** CameraDataStruct) {
	int iResult;
	printf("SetFrameReadyCallback..\n");
	iResult = IC_SetFrameReadyCallback((*CameraDataStruct)->hGrabber, *callback,
			*CameraDataStruct);
	printf("SetFormat...\n");
	IC_SetFormat((*CameraDataStruct)->hGrabber, Y800);
	printf("Set Continuous mode");
	IC_SetContinuousMode((*CameraDataStruct)->hGrabber, 0); //1 means snap continously
	IC_StartLive((*CameraDataStruct)->hGrabber, 0); //Set to 1 to display
}

/*
 *
 * Takes a CameraDataStruct with an initialized frame grabber
 * and turns it off. De Allocates Camera Data.
 *
 */
void T2Cam_TurnOff(CamData** CameraDataStruct) {
	printf("Inside T2Cam_TurnOff()\n");
	int ret;
	int FLAG=0;
	//if still open -> stop and release grabber
	if ((*CameraDataStruct)->hGrabber) {
		printf("(*CameraDataStruct)->hGrabber is TRUE\n");
		ret=IC_SuspendLive( (*CameraDataStruct)->hGrabber );
		switch (ret) {
			case IC_SUCCESS :
				printf("Camera was succesffully Suspended\n");
				IC_StopLive((*CameraDataStruct)->hGrabber);
				printf("Live was stopped\n");
				break;
			case IC_ERROR  :
				printf("An error occurred in IC_SuspendLive()... Embarrassingly, this appears to be normal and benign. Sorry. \n ");
				FLAG=1;
				break;
			case IC_NO_DEVICE  :
				printf("No device opened\n");
				break;
			case IC_NO_HANDLE:
				printf("hGrabber is Null\n");
				break;
			default:
				break;
		}

		IC_CloseVideoCaptureDevice((*CameraDataStruct)->hGrabber);
		IC_ReleaseGrabber(&((*CameraDataStruct)->hGrabber));
		printf("Grabber Released\n");
		ret=0;
		ret=IC_IsDevValid(  (*CameraDataStruct)->hGrabber ) ;
		if (ret==1){
			printf("FAIL!!! The hgrabber is still open!!");
		}else{
			printf("Success. There is no valid video capture device opened.\n ");
		}

		free(*CameraDataStruct);
		printf("Releasing memory from CamData struct\n");
	}else{
		printf("No open hgrabber in T2Cam_TurnOff()\n.");
		}
	printf("Exiting T2Cam_TurnOff()");
}

/*
 * In continuousmode, callback is called every time the camera acquires
 * a new frame. The callback populates the data structure "Data" using the
 * CamData datatype.
 *
 * Inside this function a dummy variable CallBackDataStruct is used.
 * (my name, not the sample code.) I believe what is going on is that the
 * CallBackDataStruct is a pointer to Data and we are just using it to
 * impose the "structure-ness" of the struct onto the pre-existing data in data.
 *
 * I find this a bit confusing but its basically the same as the sample code
 * with different variable names.
 *
 */
void _cdecl callback(HGRABBER hGrabber, unsigned char* pData,
		unsigned long frameNumber, void* Data) {
	CamData *CallBackDataStruct;
	CallBackDataStruct = (CamData *) Data;
	if (PRINT_DEBUG) {
		printf("callback called \n");
	}
	//if (!CallBackDataStruct->iProcessing) {
		//CallBackDataStruct->iProcessing = 1;
		CallBackDataStruct->iImageData = pData; //Copy the frame data into the structure.
		CallBackDataStruct->iFrameNumber = frameNumber;
		if (PRINT_DEBUG) {
			printf("Within callback: iframeNumber %d \n", frameNumber);
		}
		//CallBackDataStruct->iProcessing = 0;
	//}
}

