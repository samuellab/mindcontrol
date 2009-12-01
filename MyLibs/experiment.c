/*
 * experiment.c
 *
 *	The experiment.c/.h library is designed to be an extremely high level library.
 *	The idea here is to have all of the elements of an experiment laid out, such that
 *	a user need only to call a few high level functions to run an experiment.
 *
 *  Created on: Nov 30, 2009
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


//OpenCV Headers
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>

//Andy's Personal Headers
#include "AndysOpenCVLib.h"
#include "Talk2Camera.h"
#include "Talk2DLP.h"
#include "Talk2Matlab.h"
#include "AndysComputations.h"
#include "TransformLib.h"
#include "WormAnalysis.h"
#include "WriteOutWorm.h"


#include "experiment.h"






/*
 * Creates a new experiment object and sets values to zero.
 */
Experiment* CreateExperimentStruct(){

	/** Create Experiment Object **/
	Experiment* exp;
	exp=(Experiment*) malloc(sizeof(Experiment));

	/*************************************/
	/**  Set Everything to zero or NULL **/
	/*************************************/

	/** GuiWindowNames **/
	exp->WinDisp=NULL;
	exp->WinCon1=NULL;
	exp->WinCon2=NULL;
	exp->WinCon3=NULL;

	/** Error information **/
	exp->e=0;

	/** CommandLine Input **/
	exp->argv=NULL;
	exp->argc=0;

	/** Camera Input**/
	exp->MyCamera=NULL;

	/** DLP Output **/
	exp->myDLP=0;

	/** Calibration Data  Object**/
	exp->Calib=NULL;


	/** User-configurable Worm-related Parameters **/
	exp->Params=NULL;

	/** Information about Our Worm **/
	exp->Worm=NULL;

	/** Information about the Previous frame's Worm **/
	exp->PrevWorm=NULL;

	/** internal IplImage **/
	exp->SubSampled=NULL; // Image used to subsample stuff
	exp->HUDS=NULL;  //Image used to generate the Heads Up Display

	/** Internal Frame data types **/
	exp->fromCCD=NULL;
	exp->forDLP=NULL;
	exp->IlluminationFrame=NULL;

	/** Write Data To File **/
	exp->DataWriter=NULL;

	/** Write Video To File **/
	exp->Vid=NULL;  //Video Writer
	exp->VidHUDS=NULL;

	/** Timing  Information **/
	exp->now=0;
	exp->last=0;

	/** Frame Rate Information **/
	exp->nframes=0;
	exp->prevFrames=0;
	exp->prevTime=0;

	/** Macros **/
	exp->RECORDVID=0;
	exp->RECORDDATA=0;


	return exp;

}



/*
 * Load the command line arguments into the experiment object
 */
void LoadCommandLineArguments(Experiment* exp, int argc, char** argv){
	exp->argc=argc;
	exp->argv=argv;
}


/*
 * Handle CommandLine Arguments
 * Parses commandline arguments.
 * Decides if user wants to record video or recorddata
 */

int HandleCommandLineArguments(Experiment* exp){

	if (exp->argc==0) {
		printf("Programming error. Run LoadCommandLineArguments() before HandleCommandLineArguments()");
		return -1;
	}

	/** Handle Variable Arguments **/
	if( exp->argc !=1 && exp->argc!=3 ){
		printf("Runs the camera and DLP in closed loop.\n");
		printf("Run without any arguments, or, to save data in a directory use the following usage:\n");
		printf("\tClosedLoop.exe D:/Data/MyDirectory/  basefilename\n\n");
		printf("IMPORTANT: Remember to include the trailing slash on the directory!");

		return -1;
	}

	if (exp->argc ==3 ){ /** The user implicitly wants to record data **/
		exp->RECORDVID=1;
		exp->RECORDDATA=1;
	}

	return 0;


}
/** GUI **/

/* Assigns Default window names to the experiment object
 *
 */
void AssignWindowNames(Experiment* exp){

	char* disp1= (char*) malloc(strlen("Display"));
	char* control1= (char*) malloc(strlen("Controls"));
	char* control2= (char*) malloc(strlen("MoreControls"));
	char* control3= (char*) malloc(strlen("EvenMoreControls"));
	exp->WinDisp=disp1;
	exp->WinCon1=control1;
	exp->WinCon2=control2;
	exp->WinCon3=control3;

}

/*
 * Release the memopry associated with window names
 * and set their pointers to Null
 */
void ReleaseWindowNames(Experiment* exp){
	if (exp->WinDisp!=NULL) free(exp->WinDisp);
	if (exp->WinCon1!=NULL) free(exp->WinCon1);
	if (exp->WinCon2!=NULL) free(exp->WinCon2);
	if (exp->WinCon3!=NULL) free(exp->WinCon3);

	exp->WinDisp=NULL;
	exp->WinCon1=NULL;
	exp->WinCon2=NULL;
	exp->WinCon3=NULL;
}


/*
 * SetupGui
 *
 */
void SetupGUI(Experiment* exp){
	WormAnalysisParam* Params=exp->Params;

	cvNamedWindow(exp->WinDisp);
	cvNamedWindow(exp->WinCon1);
	cvResizeWindow(exp->WinCon1,450,700);


	/** SelectDispilay **/
	cvCreateTrackbar("SelDisplay", exp->WinCon1, &(Params->Display), 7, (int) NULL);


	/** On Off **/
	cvCreateTrackbar("On",exp->WinCon1,&(Params->OnOff),1,(int) NULL);

	/** Temporal Coding **/
	cvCreateTrackbar("TemporalIQ",exp->WinCon1,&(Params->TemporalOn),1, (int) NULL);

	/** Segmentation Parameters**/
	cvCreateTrackbar("Threshold", exp->WinCon1, &(Params->BinThresh),255, (int) NULL);
	cvCreateTrackbar("Gauss=x*2+1",exp->WinCon1, &(Params->GaussSize),15,(int) NULL);
	cvCreateTrackbar("ScalePx",exp->WinCon1, &(Params->LengthScale),50, (int) NULL);
	cvCreateTrackbar("Proximity",exp->WinCon1,&(Params->MaxLocationChange),100, (int) NULL);


	/**Illumination Parameters **/
	cvCreateTrackbar("Center",exp->WinCon1,&(Params->IllumSegCenter),100, (int) NULL);
	cvCreateTrackbar("Radius",exp->WinCon1,&(Params->IllumSegRadius),100, (int) NULL);
	cvCreateTrackbar("LRC",exp->WinCon1,&(Params->IllumLRC),3,(int) NULL);
	cvCreateTrackbar("DLPOn",exp->WinCon1,&(Params->DLPOn),1,(int) NULL);

	/** Record Data **/
	cvCreateTrackbar("RecordOn",exp->WinCon1,&(Params->Record),1,(int) NULL);


	/****** Setup Debug Control Panel ******/
	cvNamedWindow(exp->WinCon2);
	cvResizeWindow(exp->WinCon2,450,200);
	cvCreateTrackbar("FloodLight",exp->WinCon2,&(Params->IllumFloodEverything),1,(int) NULL);
	return;

}


/*** Start Video Camera ***/



/*
 * Initialize camera library
 * Allocate Camera Data
 * Select Camera and Show Properties dialog box
 * Start Grabbing Frames as quickly as possible
 */
void RollCamera(Experiment* exp){
	/** Turn on Camera **/
	T2Cam_InitializeLib();
	T2Cam_AllocateCamData(&(exp->MyCamera));
	T2Cam_ShowDeviceSelectionDialog(&(exp->MyCamera));
	/** Start Grabbing Frames and Update the Internal Frame Number iFrameNumber **/
	T2Cam_GrabFramesAsFastAsYouCan(&(exp->MyCamera));
}



/**** Read in Calibration Data ***/
/*
 * Create calibration Data structure
 * Load calibration data from file
 * return -1 if the calibration from file doesn't exist.
 */
int HandleCalibrationData(Experiment* exp){
	exp->Calib =CreateCalibData(cvSize(NSIZEX,NSIZEY),cvSize(NSIZEX,NSIZEY));
	int ret=LoadCalibFromFile(exp->Calib,"calib.dat");
	if (ret!=0){
		printf("Error reading in calibrationfile!!\nPlease run CalibrateApparatus to generate calibration file calib.dat\nThank you.\nGoodbye.\n");
		return -1;
	}
	return 0;

}


