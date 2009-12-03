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

	int e=0;


	/*Start the frame rate timer */
	StartFrameRateTimer(exp);




	/** Giant While Loop Where Everything Happens **/
	while (1) {
		if (exp->MyCamera->iFrameNumber > lastFrameSeenOutside) {
			e=0;
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


			/*** <segmentworm> ***/

			/** Load Image into Our Worm Objects **/
			/*** Load Frame into Worm **/
			if (!e) e=RefreshWormMemStorage(exp->Worm);
			if (!e) e=LoadWormImg(exp->Worm,exp->fromCCD->iplimg);

			Toc(exp->profiler); //1


			/*** Find Worm Boundary ***/
			if (!e) FindWormBoundary(exp->Worm,exp->Params);

			Toc(exp->profiler); //2


			/*** Find Worm Head and Tail ***/
			if (!e) e=GivenBoundaryFindWormHeadTail(exp->Worm,exp->Params);
			/** If we are doing temporal analysis, improve the WormHeadTail estimate based on prev frame **/
			if (exp->Params->TemporalOn && !e) PrevFrameImproveWormHeadTail(exp->Worm,exp->Params,exp->PrevWorm);

			Toc(exp->profiler); //3



			/*** Segment the Worm ***/
			if (!e) e=SegmentWorm(exp->Worm,exp->Params);
			Toc(exp->profiler); //4



			/** Update PrevWorm Info **/
			if (!e) LoadWormGeom(exp->PrevWorm,exp->Worm);

			Toc(exp->profiler); //5

			/*** </segmentworm> ***/


			/*** Do Some Illumination ***/

			if (!e) {
				if (exp->Params->IllumFloodEverything) {
					SetFrame(exp->IlluminationFrame,128); // Turn all of the pixels on
				} else {
					/** Otherwise Actually illuminate the  region of the worm your interested in **/
					SimpleIlluminateWormLR(exp->Worm, exp->IlluminationFrame, exp->Params->IllumSegCenter, exp->Params->IllumSegRadius, exp->Params->IllumLRC);
				}
			}
			Toc(exp->profiler); //6


			/*** <------------ 31fps ***/
			if (!e) TransformFrameCam2DLP(exp->IlluminationFrame,exp->forDLP,exp->Calib);
			Toc(exp->profiler); //7

			/*** <------------ 26fps ***/



			if (!e && exp->Params->DLPOn) T2DLP_SendFrame((unsigned char *) exp->forDLP->binary, exp->myDLP); // Send image to DLP
			Toc(exp->profiler); //8



			/*** DIsplay Some Monitoring Output ***/
			if (!e) CreateWormHUDS(exp->HUDS,exp->Worm,exp->Params,exp->IlluminationFrame);
				if (!e &&  EverySoOften(exp->Worm->frameNum,exp->Params->DispRate) ){
					/** There are no errors and we are displaying a frame **/
					switch (exp->Params->Display) {
						case 0:
							 cvShowImage(exp->WinDisp, exp->Worm->ImgOrig);
							break;
						case 1:
							cvShowImage(exp->WinDisp,exp->HUDS);
							break;
						case 2:
							 cvShowImage(exp->WinDisp,exp->Worm->ImgThresh);
							 break;
						case 3:
							 DisplayWormHeadTail(exp->Worm,exp->WinDisp);
							 break;
						case 4:
							DisplayWormSegmentation(exp->Worm,exp->WinDisp);
							break;
						case 5:
							cvShowImage(exp->WinDisp,exp->IlluminationFrame->iplimg);
							break;
						case 6:
							cvShowImage(exp->WinDisp, exp->forDLP->iplimg);
							break;
						default:
							break;
					}
					cvWaitKey(1); // Pause one millisecond for things to display onscreen.


					Toc(exp->profiler); //9

					/** Record VideoFrame to Disk**/
					if (exp->RECORDVID && exp->Params->Record) {
						cvResize(exp->Worm->ImgOrig,exp->SubSampled,CV_INTER_LINEAR);
						cvWriteFrame(exp->Vid,exp->SubSampled);
						cvResize(exp->HUDS,exp->SubSampled,CV_INTER_LINEAR);
						cvWriteFrame(exp->VidHUDS,exp->SubSampled);
					}
					Toc(exp->profiler); //10

					/** Record data frame to diskl **/
					if (exp->RECORDDATA && exp->Params->Record) AppendWormFrameToDisk(exp->Worm,exp->Params,exp->DataWriter);
					Toc(exp->profiler); //11
				}



				if (!e){
					printf("*");
				} else {
					printf("\n:(\n");
				}
				Toc(exp->profiler); //12
		}
		if (kbhit()) break;
		if (e) cvWaitKey(1); /**Wait so that we don't end up in a loop lockign up the UI in case of error**/

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

