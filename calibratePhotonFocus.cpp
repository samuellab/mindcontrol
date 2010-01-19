/*
 * ~/workspace/OpticalMindControl/main.cpp
 * main.cpp
 *
 *  Created on: Jul 20, 2009
 *      Author: Andy
 */

//Standard C headers
#include <unistd.h>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <math.h>


//Windows Header

//C++ header
#include <iostream>
#include <limits>

using namespace std;


//OpenCV Headers
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include <assert.h>

//Andy's Personal Headers
#include "MyLibs/AndysOpenCVLib.h"
#include "MyLibs/Talk2FrameGrabber.h"
#include "MyLibs/Talk2DLP.h"
#include "MyLibs/Talk2Matlab.h"
#include "MyLibs/AndysComputations.h"
#include "MyLibs/TransformLib.h"


typedef struct CalibrationSessionStruct {
	int *CCD2DLPLookUp;
	long myDLP;

	FrameGrabber* fg;


	/** Circle Drawing properties**/
	int CircRadius;
	int gauss_radius;
	int rel_intensity_thresh;
	/** Size of Objects **/
	CvSize DLPsize;
	CvSize Camsize;
}CalibrationSession;



/*
 * Create the calibration session structure
 *
 */
CalibrationSession* CreateCalibrationSession(){
	CalibrationSession* c = (CalibrationSession* ) malloc(sizeof(CalibrationSession) );

	/** Set Everything to Zero **/
	c->myDLP=0;
	c->fg=NULL;

	/** Circle properties **/
	c->CircRadius=4;
	c->gauss_radius=10;
	c->rel_intensity_thresh=4;

	c->DLPsize=cvSize(0,0);
	c->Camsize=cvSize(0,0);
	c->CCD2DLPLookUp=NULL;


}




/*
 * Allocate memory for the members of the calibration session structure
 */
void InitializeCalibrationSession(CalibrationSession* c){

	if (!(c->Camsize.width==c->DLPsize.width && c->Camsize.height==c->DLPsize.height) || c->Camsize.width==0 || c->DLPsize.width==0 || c->Camsize.height==0 || c->DLPsize.height==0){
		printf("The dimensions of the Camera or the DLP are invalid in IntializeCalibtraionSession()\n");
		assert(0);
	}

	c->	CCD2DLPLookUp = (int *) malloc(2 * c->Camsize.width * c->Camsize.height * sizeof(int));

}

/*
 * Set size of camera and DLP
 */
void SetHardwareDimensions(CalibrationSession* c, CvSize DLPsize, CvSize Camsize){
	c->Camsize=Camsize;
	c->DLPsize=DLPsize;

	printf("For now the camera and the DLP must have the same dimensions.");
	assert(Camsize.width==DLPsize.width && Camsize.height==DLPsize.height);

}



FrameGrabber* TurnOnFrameGrabber(){
	FrameGrabber* fg= CreateFrameGrabberObject();
	InitializeFrameGrabber(fg);
	FrameGrabberSetRegionOfInterest(fg,0,0,1024,768);
	PrepareFrameGrabberForAcquire(fg);
}


void SetupGUI(CalibrationSession* c){
	cvNamedWindow("FromCamera", CV_WINDOW_AUTOSIZE);
	cvMoveWindow("FromCamera", 200, 200);
	cvNamedWindow("ToDLP", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("InputRad", "FromCamera", &(c->CircRadius), 10, NULL);
	cvCreateTrackbar("GaussRad", "FromCamera", &(c->gauss_radius), 30,			NULL);
	cvCreateTrackbar("RelIntThresh", "FromCamera",
				&(c->rel_intensity_thresh), 10, NULL);

}

void DrawCircleOnDLP(cvPoint center, CalibrationSession* c){
	Frame* toDLP=CreateFrame(c->Camsize);
	cvSetZero(toDLP->iplimg);
	cvCircle(toDLP->iplimge, center, c->CircRadius+ 1,
			CV_RGB(255,255,255), CV_FILLED, 8);
	copyIplImageToCharArray(toDLP->ilpimg,toDLP->binary);
	T2DLP_SendFrame((unsigned char *) toDLP->binary, c->myDLP);
}


int main (int argc, char** argv){


	/** Display output about the OpenCV setup currently installed **/
	DisplayOpenCVInstall();

	/** Create session object **/
	CalibrationSession* c = CreateCalibrationSession();

	/** Set the size of the objects **/
	SetHardwareDimensions(c,cvSize(NSIZEX,NSIZEY)cvSize(NSIZEX,NSIZEY));

	/** Allocate memory for the variables we will be using this session **/
	InitializeCalibrationSession(c);

	/** Start Camera or Vid Input **/
	c->fg= TurnOnFrameGrabber();

	/** Prepare DLP ***/
	c->myDLP= T2DLP_on();

	/** Setup GUI **/
	SetupGUI(c);



	/** Draw A circle on the DLP so we can focus on the camera **/
	DrawCircleOnDLP(cvPoint(c->Camsize.width/2,c->Camsize.height/2 ),c);




	/**********************************
	 *
	 * EVERYTHING BELOW HERE IS JUNK
	 */






	/** Giant While Loop Where Everything Happens **/
	TICTOC::timer().tic("WholeLoop");
	int VideoRanOut=0;
	while (1) {
		_TICTOC_TIC_FUNC
		TICTOC::timer().tic("OneLoop");
		if (isFrameReady(exp)) {

			/** Set error to zero **/
			exp->e=0;
			TICTOC::timer().tic("GrabFrame()");
			/** Grab a frame **/
			if (GrabFrame(exp)<0){
				VideoRanOut=1;
				printf("Video ran out!\n");
				break;
			}
			TICTOC::timer().toc("GrabFrame()");


			/** Calculate the frame rate and every second print the result **/
			CalculateAndPrintFrameRate(exp);


			/** Do we even bother doing analysis?**/
			if (exp->Params->OnOff==0){
				/**Don't perform any analysis**/
				cvShowImage(exp->WinDisp, exp->fromCCD->iplimg);
				cvWaitKey(10);
				continue;
			}

			/** Handle Transient Illumination Timing **/
			HandleIlluminationTiming(exp);

			/** If the DLP is not displaying right now, than turn off the mirrors */
			ClearDLPifNotDisplayingNow(exp);


			/** Load Image into Our Worm Objects **/

			if (!(exp->e)) exp->e=RefreshWormMemStorage(exp->Worm);
			if (!(exp->e)) exp->e=LoadWormImg(exp->Worm,exp->fromCCD->iplimg);

			TICTOC::timer().tic("EntireSegmentation");
			/** Do Segmentation **/
			DoSegmentation(exp);
			TICTOC::timer().toc("EntireSegmentation");

			TICTOC::timer().tic("TransformSegWormCam2DLP");
			if (!(exp->e)){
				TransformSegWormCam2DLP(exp->Worm->Segmented, exp->segWormDLP,exp->Calib);
			}
			TICTOC::timer().toc("TransformSegWormCam2DLP");

			/*** Do Some Illumination ***/

			if (!(exp->e)) {

				if (exp->Params->IllumFloodEverything) {
					SetFrame(exp->IlluminationFrame,128); // Turn all of the pixels on
				} else {
					if (!(exp->Params->ProtocolUse)) /** if not running the protocol **/{
					/** Otherwise Actually illuminate the  region of the worm your interested in **/
					/** Do the Illumination in Camera space for Display **/
					SimpleIlluminateWormLR(exp->Worm->Segmented, exp->IlluminationFrame, exp->Params->IllumSegCenter, exp->Params->IllumSegRadius, exp->Params->IllumLRC);

					/** Repeat but for the DLP space for sending to DLP **/
					SimpleIlluminateWormLR(exp->segWormDLP, exp->forDLP, exp->Params->IllumSegCenter, exp->Params->IllumSegRadius, exp->Params->IllumLRC);
					} else{


						/** Illuminate The worm in Camera Space **/
						TICTOC::timer().tic("IlluminateFromProtocol()");
						IlluminateFromProtocol(exp->Worm->Segmented,exp->IlluminationFrame,exp->p,exp->Params);

						/** Illuminate the worm in DLP space **/
						IlluminateFromProtocol(exp->segWormDLP,exp->forDLP,exp->p,exp->Params);
						TICTOC::timer().toc("IlluminateFromProtocol()");

					}
				}


			}




			if (!(exp->e) && exp->Params->DLPOn && !(exp->SimDLP)) T2DLP_SendFrame((unsigned char *) exp->forDLP->binary, exp->myDLP); // Send image to DLP

			/*** DIsplay Some Monitoring Output ***/
			if (!(exp->e)) CreateWormHUDS(exp->HUDS,exp->Worm,exp->Params,exp->IlluminationFrame);

			if (!(exp->e) &&  EverySoOften(exp->Worm->frameNum,exp->Params->DispRate) ){
				TICTOC::timer().tic("DisplayOnScreen");
				DoDisplaySelectedDisplay(exp);
				TICTOC::timer().toc("DisplayOnScreen");
			}





			if (!(exp->e)) {
				TICTOC::timer().tic("DoWriteToDisk()");
				DoWriteToDisk(exp);
				TICTOC::timer().toc("DoWriteToDisk()");
			}


			if (exp->e) printf("\nError in main loop. :(\n");

		}
		if (kbhit()) break;
			TICTOC::timer().toc("OneLoop");

	}
	TICTOC::timer().toc("WholeLoop");
	/** Flag to tell thread to stop  **/
	MainThreadHasStopped=TRUE;

	TICTOC::timer().tic("FinishRecording()");
	FinishRecording(exp);
	TICTOC::timer().toc("FinishRecording()");

	if (!(exp->SimDLP)) 	T2DLP_off(exp->myDLP);

	if (!(exp->VidFromFile) && !(exp->UseFrameGrabber)){
		/***** Turn off Camera & DLP ****/
		T2Cam_TurnOff(&(exp->MyCamera));
		T2Cam_CloseLib();
	}

	if (!(exp->VidFromFile) && (exp->UseFrameGrabber)){
		CloseFrameGrabber(exp->fg);
	}


	ReleaseExperiment(exp);
	DestroyExperiment(&exp);


	printf("%s",TICTOC::timer().generateReportCstr());

	printf("Waiting for DisplayThread to Stop...");
	while (!DispThreadHasStopped){
		printf(".");
		Sleep(500);
		cvWaitKey(10);
	}
	printf("\nMain Thread: Good bye.\n");
	return 0;
}


/**
 * Thread to display image. 
 */
UINT Thread(LPVOID lpdwParam) {
	Experiment* exp= (Experiment*) lpdwParam;
	printf("DisplayThread: Hello!\n");
	MSG Msg;

	SetupGUI(exp);
	cvWaitKey(30);
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

	printf("Beginning ProtocolStep Display\n");
	DispThreadHasStarted = TRUE;
	cvWaitKey(30);

	/** Protocol WormSpace Display **/
	int prevProtocolStep;
	IplImage* rectWorm;
	if (exp->pflag){ /** If a protocol was loaded **/
		rectWorm= GenerateRectangleWorm(exp->p->GridSize);
		cvZero(rectWorm);
		IllumRectWorm(rectWorm,exp->p,exp->Params->ProtocolStep);
		prevProtocolStep=exp->Params->ProtocolStep;
		cvShowImage("ProtoIllum",rectWorm);
	}

	printf("Starting DispThread loop\n");


	while (!MainThreadHasStopped) {

		//needed for display window
			if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
				DispatchMessage(&Msg);


			TICTOC::timer().tic("DisplayThreadGuts");
			TICTOC::timer().tic("cvShowImage");
			cvShowImage("Display",exp->CurrentSelectedImg);
			TICTOC::timer().toc("cvShowImage");


			/** If we are using protocols and we havec chosen a new protocol step **/
			if (exp->Params->ProtocolUse && (prevProtocolStep!= exp->Params->ProtocolStep))  {
				cvZero(rectWorm);
				IllumRectWorm(rectWorm,exp->p,exp->Params->ProtocolStep);
				/** Update the Protocol **/
				cvShowImage("ProtoIllum",rectWorm);

			}

			TICTOC::timer().toc("DisplayThreadGuts");
			UpdateGUI(exp);
			Sleep(100);
	}

	//if (exp->pflag) cvReleaseImage(&rectWorm);

	//	printf("%s",TICTOC::timer().generateReportCstr());
		printf("\nDisplayThread: Goodbye!\n");
		DispThreadHasStopped=TRUE;
	return 0;
}

