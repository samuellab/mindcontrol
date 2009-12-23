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
#include "MyLibs/Talk2DLP.h"
#include "MyLibs/Talk2Matlab.h"
#include "MyLibs/AndysComputations.h"
#include "MyLibs/TransformLib.h"
#include "MyLibs/WormAnalysis.h"
#include "MyLibs/WriteOutWorm.h"
#include "MyLibs/experiment.h"

//3rd Party Libraries
#include "3rdPartyLibs/tictoc.h"



int main (int argc, char** argv){
	/** Display output about the OpenCV setup currently installed **/
	DisplayOpenCVInstall();

	/** Create a new experiment object **/
	Experiment* exp=CreateExperimentStruct();


	/** Create memory and objects **/
	InitializeExperiment(exp);

	/** Deal with CommandLineArguments **/
	LoadCommandLineArguments(exp,argc,argv);
	if (HandleCommandLineArguments(exp)==-1) return -1;

	/** Read In Calibration Data ***/
	if (HandleCalibrationData(exp)<0) return -1;

	/** Start Camera or Vid Input **/
	RollVideoInput(exp);

	/** Prepare DLP ***/
	if (!(exp->SimDLP)){
		exp->myDLP= T2DLP_on();
	}

	/** Setup Segmentation Gui **/
	AssignWindowNames(exp);
	SetupGUI(exp);

	/** SetUp Data Recording **/
	SetupRecording(exp);

	/*Start the frame rate timer */
	StartFrameRateTimer(exp);

	/** Giant While Loop Where Everything Happens **/
	TICTOC::timer().tic("WholeLoop");
	int VideoRanOut=0;
	while (1) {
		_TICTOC_TIC_FUNC
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



			/** If the DLP is not displaying right now, than turn off the mirrors */
			ClearDLPifNotDisplayingNow(exp);



			/** Load Image into Our Worm Objects **/

			if (!(exp->e)) exp->e=RefreshWormMemStorage(exp->Worm);
			if (!(exp->e)) exp->e=LoadWormImg(exp->Worm,exp->fromCCD->iplimg);

			TICTOC::timer().tic("EntireSegmentation");
			/** Do Segmentation **/
			DoSegmentation(exp);
			TICTOC::timer().toc("EntireSegmentation");


			/*** Do Some Illumination ***/

			if (!(exp->e)) {
				if (exp->Params->IllumFloodEverything) {
					SetFrame(exp->IlluminationFrame,128); // Turn all of the pixels on
				} else {
					/** Otherwise Actually illuminate the  region of the worm your interested in **/
					SimpleIlluminateWormLR(exp->Worm, exp->IlluminationFrame, exp->Params->IllumSegCenter, exp->Params->IllumSegRadius, exp->Params->IllumLRC);
				}
			}


			/*** <------------ 31fps ***/
			TICTOC::timer().tic("TransformFrameCam2DLP");
			if (!(exp->e)) TransformFrameCam2DLP(exp->IlluminationFrame,exp->forDLP,exp->Calib);
			TICTOC::timer().toc("TransformFrameCam2DLP");
			/*** <------------ 26fps ***/



			if (!(exp->e) && exp->Params->DLPOn && !(exp->SimDLP)) T2DLP_SendFrame((unsigned char *) exp->forDLP->binary, exp->myDLP); // Send image to DLP

			/*** DIsplay Some Monitoring Output ***/
			if (!(exp->e)) CreateWormHUDS(exp->HUDS,exp->Worm,exp->Params,exp->IlluminationFrame);

			if (!(exp->e) &&  EverySoOften(exp->Worm->frameNum,exp->Params->DispRate) ){
				TICTOC::timer().tic("DisplayOnScreen");
				DoDisplaySelectedDisplay(exp);
				TICTOC::timer().toc("DisplayOnScreen");
			}



			if (!(exp->e)) DoWriteToDisk(exp);


			if (!(exp->e)){
				printf("*");
			} else {
				printf("\n:(\n");
			}

		}
		if (kbhit()) break;
		if (exp->e) cvWaitKey(1); /**Wait so that we don't end up in a loop lockign up the UI in case of error**/

	}
	TICTOC::timer().toc("WholeLoop");
	printf("%s",TICTOC::timer().generateReportCstr());

	FinishRecording(exp);

	if (!(exp->SimDLP)){
	//	cvDestroyAllWindows();
	T2DLP_off(exp->myDLP);

	/***** Turn off Camera & DLP ****/
	T2Cam_TurnOff(&(exp->MyCamera));
	T2Cam_CloseLib();
	}

	ReleaseExperiment(exp);
	DestroyExperiment(&exp);


	printf("\nGood bye.\n");
	return 0;
}

