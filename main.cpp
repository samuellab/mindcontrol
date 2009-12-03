/*
 * ~/workspace/OpticalMindControl/main.cpp
 * main.cpp
 *
 *  Created on: Jul 20, 2009
 *      Author: Andy
 */

//Standard C headers
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

	/** Start Camera **/
	RollCamera(exp);

	/** Prepare DLP ***/
	exp->myDLP= T2DLP_on();
	unsigned long lastFrameSeenOutside = 0;


	/** Setup Segmentation Gui **/
	AssignWindowNames(exp);
	SetupGUI(exp);


	/** SetUp Data Recording **/
	SetupRecording(exp);



	/*Start the frame rate timer */
	StartFrameRateTimer(exp);




	/** Giant While Loop Where Everything Happens **/
	while (1) {
		if (exp->MyCamera->iFrameNumber > lastFrameSeenOutside) {
			exp->e=0;
			lastFrameSeenOutside = exp->MyCamera->iFrameNumber;
			exp->Worm->frameNum++;

			/** Calculate the frame rate and every second print the result **/
			CalculateAndPrintFrameRate(exp);

			/*** Create a local copy of the image***/
			LoadFrameWithBin(exp->MyCamera->iImageData,exp->fromCCD);


			/** Do we even bother doing analysis?**/
			if (exp->Params->OnOff==0){
				/**Don't perform any analysis**/
				cvShowImage(exp->WinDisp, exp->fromCCD->iplimg);
				cvWaitKey(10);
				continue;
			}


			Tic(exp->profiler);

			/** If the DLP is not displaying right now, than turn off the mirrors */
			ClearDLPifNotDisplayingNow(exp);

			Toc(exp->profiler); //0

			/***********************
			 * Segment Frame
			 */



			/** Load Image into Our Worm Objects **/
			/*** Load Frame into Worm **/
			if (!(exp->e)) exp->e=RefreshWormMemStorage(exp->Worm);
			if (!(exp->e)) exp->e=LoadWormImg(exp->Worm,exp->fromCCD->iplimg);

			Toc(exp->profiler); //1

			/** Do Segmentation **/
			DoSegmentation(exp);


			/*** Do Some Illumination ***/

			if (!(exp->e)) {
				if (exp->Params->IllumFloodEverything) {
					SetFrame(exp->IlluminationFrame,128); // Turn all of the pixels on
				} else {
					/** Otherwise Actually illuminate the  region of the worm your interested in **/
					SimpleIlluminateWormLR(exp->Worm, exp->IlluminationFrame, exp->Params->IllumSegCenter, exp->Params->IllumSegRadius, exp->Params->IllumLRC);
				}
			}
			Toc(exp->profiler); //6


			/*** <------------ 31fps ***/
			if (!(exp->e)) TransformFrameCam2DLP(exp->IlluminationFrame,exp->forDLP,exp->Calib);
			Toc(exp->profiler); //7

			/*** <------------ 26fps ***/



			if (!(exp->e) && exp->Params->DLPOn) T2DLP_SendFrame((unsigned char *) exp->forDLP->binary, exp->myDLP); // Send image to DLP
			Toc(exp->profiler); //8



			/*** DIsplay Some Monitoring Output ***/
			if (!(exp->e)) CreateWormHUDS(exp->HUDS,exp->Worm,exp->Params,exp->IlluminationFrame);

			if (!(exp->e) &&  EverySoOften(exp->Worm->frameNum,exp->Params->DispRate) ){
				DoDisplaySelectedDisplay(exp);
			}
			Toc(exp->profiler); //9

			if (!(exp->e)) DoWriteToDisk(exp);


			if (!(exp->e)){
				printf("*");
			} else {
				printf("\n:(\n");
			}
				Toc(exp->profiler); //12
		}
		if (kbhit()) break;
		if (exp->e) cvWaitKey(1); /**Wait so that we don't end up in a loop lockign up the UI in case of error**/

	}
	DisplayTimeProfile(exp->profiler);
	FinishRecording(exp);


	//	cvDestroyAllWindows();
	T2DLP_off(exp->myDLP);

	/***** Turn off Camera & DLP ****/
	T2Cam_TurnOff(&(exp->MyCamera));
	T2Cam_CloseLib();

	ReleaseExperiment(exp);
	DestroyExperiment(&exp);

	printf("\nGood bye.\n");
	return 0;
}

