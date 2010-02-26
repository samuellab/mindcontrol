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
#include <sys/time.h>

//Windows Header
#include <windows.h>

//C++ header
#include <iostream>
#include <limits>

using namespace std;


//OpenCV Headers
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>

//Andy's Personal Headers
#include "MyLibs/AndysOpenCVLib.h"
#include "MyLibs/Talk2Camera.h"
#include "MyLibs/Talk2FrameGrabber.h"
#include "MyLibs/Talk2DLP.h"
#include "MyLibs/Talk2Matlab.h"
#include "MyLibs/AndysComputations.h"
#include "MyLibs/WormAnalysis.h"
#include "MyLibs/WriteOutWorm.h"
#include "MyLibs/IllumWormProtocol.h"
#include "MyLibs/TransformLib.h"
#include "MyLibs/experiment.h"


//3rd Party Libraries
#include "3rdPartyLibs/tictoc.h"

/** Global Variables (for multithreading) **/
UINT Thread(LPVOID lpdwParam);
IplImage* CurrentImg;
bool DispThreadHasStarted;
bool MainThreadHasStopped;
bool DispThreadHasStopped;
bool UserWantsToStop;

int main (int argc, char** argv){
	int DEBUG=0;
	if (DEBUG){
		cvNamedWindow("Debug");
	//	cvNamedWindow("Debug2");
	}


	/** Display output about the OpenCV setup currently installed **/
	DisplayOpenCVInstall();

	/** Create a new experiment object **/
	Experiment* exp=CreateExperimentStruct();


	/** Create memory and objects **/
	InitializeExperiment(exp);
	exp->e=0; //set errors to zero.


	/** Deal with CommandLineArguments **/
	LoadCommandLineArguments(exp,argc,argv);
	if (HandleCommandLineArguments(exp)==-1) return -1;

	/** Read In Calibration Data ***/
	if (HandleCalibrationData(exp)<0) return -1;

	/** Load protocol YAML file **/
	if (exp->pflag) LoadProtocol(exp);

	/** Start Camera or Vid Input **/
	RollVideoInput(exp);

	/** Prepare DLP ***/
	if (!(exp->SimDLP)){
		exp->myDLP= T2DLP_on();
	}

	/** Setup Segmentation Gui **/
	AssignWindowNames(exp);


	/** Start New Thread **/
	DWORD dwThreadId;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) Thread, (void*) exp,
				0, &dwThreadId);
	if (hThread == NULL) {
		printf("Cannot create thread.\n");
		return -1;
	}



	// wait for thread
	DispThreadHasStarted=FALSE;
	DispThreadHasStopped=FALSE;
	MainThreadHasStopped=FALSE;
	while (!DispThreadHasStarted)
		Sleep(10);





	/** SetUp Data Recording **/
	exp->e = SetupRecording(exp);

	/*Start the frame rate timer */
	StartFrameRateTimer(exp);

	/** Quit now if we have some errors **/
	if(exp->e != 0) return -1;

	/** Giant While Loop Where Everything Happens **/
	TICTOC::timer().tic("WholeLoop");
	int VideoRanOut=0;
	UserWantsToStop=0;
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
				/**Don't perform any analysis**/;
				continue;
			}

			/** Handle Transient Illumination Timing **/
			HandleIlluminationTiming(exp);

			/** If the DLP is not displaying right now, than turn off the mirrors */
			ClearDLPifNotDisplayingNow(exp);


			/** Load Image into Our Worm Objects **/

			if (exp->e == 0) exp->e=RefreshWormMemStorage(exp->Worm);
			if (exp->e == 0) exp->e=LoadWormImg(exp->Worm,exp->fromCCD->iplimg);

			TICTOC::timer().tic("EntireSegmentation");
			/** Do Segmentation **/
			DoSegmentation(exp);
			TICTOC::timer().toc("EntireSegmentation");

			TICTOC::timer().tic("TransformSegWormCam2DLP");
			if (exp->e == 0){
				TransformSegWormCam2DLP(exp->Worm->Segmented, exp->segWormDLP,exp->Calib);
			}
			TICTOC::timer().toc("TransformSegWormCam2DLP");

			/*** Do Some Illumination ***/

			if (exp->e == 0) {
				/** Clear the illumination pattern **/
				SetFrame(exp->forDLP,0);
				SetFrame(exp->IlluminationFrame,0);


				if (exp->Params->IllumFloodEverything) {
					SetFrame(exp->IlluminationFrame,128); // Turn all of the pixels on
					SetFrame(exp->forDLP,128); // Turn all of the pixels o

				} else {
					if (!(exp->Params->ProtocolUse)) /** if not running the protocol **/{
						/** Otherwise Actually illuminate the  region of the worm your interested in **/
						/** Do the Illumination in Camera space for Display **/

						DoOnTheFlyIllumination(exp);
					//	SimpleIlluminateWormLR(exp->Worm->Segmented, exp->IlluminationFrame, exp->Params->IllumSegCenter, exp->Params->IllumSegRadius, exp->Params->IllumLRC);

						/** Repeat but for the DLP space for sending to DLP **/
					//	SimpleIlluminateWormLR(exp->segWormDLP, exp->forDLP, exp->Params->IllumSegCenter, exp->Params->IllumSegRadius, exp->Params->IllumLRC);
					} else{


						/** Illuminate The worm in Camera Space **/
						TICTOC::timer().tic("IlluminateFromProtocol()");

						IlluminateFromProtocol(exp->Worm->Segmented,exp->IlluminationFrame,exp->p,exp->Params);

						/** Illuminate the worm in DLP space **/
						IlluminateFromProtocol(exp->segWormDLP,exp->forDLP,exp->p,exp->Params);
						TICTOC::timer().toc("IlluminateFromProtocol()");

					}

				}
				/** If InvertIllumination is turned on, then do that now **/
				if (exp->Params->IllumInvert) InvertIllumination(exp);
			}



			TICTOC::timer().tic("SendFrameToDLP");
			if (exp->e == 0 && exp->Params->DLPOn && !(exp->SimDLP)) T2DLP_SendFrame((unsigned char *) exp->forDLP->binary, exp->myDLP); // Send image to DLP
			TICTOC::timer().toc("SendFrameToDLP");


			/*** DIsplay Some Monitoring Output ***/
			if (exp->e == 0) CreateWormHUDS(exp->HUDS,exp->Worm,exp->Params,exp->IlluminationFrame);

			if (exp->e == 0 &&  EverySoOften(exp->Worm->frameNum,exp->Params->DispRate) ){
				TICTOC::timer().tic("DisplayOnScreen");
				/** Setup Display but don't actually send to screen **/
				PrepareSelectedDisplay(exp);
				TICTOC::timer().toc("DisplayOnScreen");
			}





			if (exp->e == 0) {
				TICTOC::timer().tic("DoWriteToDisk()");
				DoWriteToDisk(exp);
				TICTOC::timer().toc("DoWriteToDisk()");
			}


			if (exp->e != 0) printf("\nError in main loop. :(\n");

		}
		if (UserWantsToStop) break;
			TICTOC::timer().toc("OneLoop");

	}
	TICTOC::timer().toc("WholeLoop");
	/** Flag to tell thread to stop  **/
	MainThreadHasStopped=TRUE;

	TICTOC::timer().tic("FinishRecording()");
	FinishRecording(exp);
	TICTOC::timer().toc("FinishRecording()");

	if (!(exp->SimDLP)) 	{
		T2DLP_clear(exp->myDLP);
		T2DLP_off(exp->myDLP);
	}

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
//	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);

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

	int key;
	int k=0;
	while (!MainThreadHasStopped) {

		//needed for display window
			if (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
				DispatchMessage(&Msg);


			TICTOC::timer().tic("DisplayThreadGuts");
			TICTOC::timer().tic("cvShowImage");
			if (exp->Params->OnOff){
				cvShowImage("Display",exp->CurrentSelectedImg);
			}else{
				cvShowImage(exp->WinDisp, exp->fromCCD->iplimg);
			}
			TICTOC::timer().toc("cvShowImage");


			/** If we are using protocols and we havec chosen a new protocol step **/
			if (exp->Params->ProtocolUse && (prevProtocolStep!= exp->Params->ProtocolStep))  {
				cvZero(rectWorm);
				IllumRectWorm(rectWorm,exp->p,exp->Params->ProtocolStep);
				prevProtocolStep=exp->Params->ProtocolStep;
				/** Update the Protocol **/
				cvShowImage("ProtoIllum",rectWorm);

			}

			TICTOC::timer().toc("DisplayThreadGuts");
			UpdateGUI(exp);
			key=cvWaitKey(100);
			if (HandleKeyStroke(key,exp)) {
				printf("\n\nEscape key pressed!\n\n");
				UserWantsToStop=1;

			}
			UpdateGUI(exp);
			if(EverySoOften(k,4)){
				/** Move the stage to keep the worm centered in the field of view **/

				AdjustStageToKeepObjectAtTarget(exp->stage,exp->Worm->Segmented->centerOfWorm,)

				/** Write the Recent Frame Number to File to be accessed by the Annotation System **/
				TICTOC::timer().tic("WriteRecentFrameNumberToFile()");
				WriteRecentFrameNumberToFile(exp);
				TICTOC::timer().toc("WriteRecentFrameNumberToFile()");
			}
			k++;

	}

	//if (exp->pflag) cvReleaseImage(&rectWorm);

	//	printf("%s",TICTOC::timer().generateReportCstr());
		printf("\nDisplayThread: Goodbye!\n");
		DispThreadHasStopped=TRUE;
	return 0;
}

