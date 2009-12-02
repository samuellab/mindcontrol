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

	disp1="Display";
	control1="Controls";
	control2="MoreControls";
	control3="EvenMoreControls";


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


	printf("Begining to setup GUI\n");

	cvNamedWindow(exp->WinDisp);
	cvNamedWindow(exp->WinCon1);
	cvResizeWindow(exp->WinCon1,450,700);

	printf("Ping\n");


	/** SelectDispilay **/
	cvCreateTrackbar("SelDisplay", "Controls"	, &(exp->Params->Display), 7, (int) NULL);
	printf("Pong\n");

	/** On Off **/
	cvCreateTrackbar("On",exp->WinCon1,&(exp->Params->OnOff),1,(int) NULL);

	/** Temporal Coding **/
	cvCreateTrackbar("TemporalIQ",exp->WinCon1,&(exp->Params->TemporalOn),1, (int) NULL);


	/** Segmentation Parameters**/
	cvCreateTrackbar("Threshold", exp->WinCon1, &(exp->Params->BinThresh),255, (int) NULL);
	cvCreateTrackbar("Gauss=x*2+1",exp->WinCon1, &(exp->Params->GaussSize),15,(int) NULL);
	cvCreateTrackbar("ScalePx",exp->WinCon1, &(exp->Params->LengthScale),50, (int) NULL);
	cvCreateTrackbar("Proximity",exp->WinCon1,&(exp->Params->MaxLocationChange),100, (int) NULL);


	/**Illumination Parameters **/
	cvCreateTrackbar("Center",exp->WinCon1,&(exp->Params->IllumSegCenter),100, (int) NULL);
	cvCreateTrackbar("Radius",exp->WinCon1,&(exp->Params->IllumSegRadius),100, (int) NULL);
	cvCreateTrackbar("LRC",exp->WinCon1,&(exp->Params->IllumLRC),3,(int) NULL);
	cvCreateTrackbar("DLPOn",exp->WinCon1,&(exp->Params->DLPOn),1,(int) NULL);

	/** Record Data **/
	cvCreateTrackbar("RecordOn",exp->WinCon1,&(exp->Params->Record),1,(int) NULL);


	/****** Setup Debug Control Panel ******/
	cvNamedWindow(exp->WinCon2);
	cvResizeWindow(exp->WinCon2,450,200);
	cvCreateTrackbar("FloodLight",exp->WinCon2,&(exp->Params->IllumFloodEverything),1,(int) NULL);
	printf("Created trackbars and windows\n");
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



/*
 * This function allocates images and frames
 * And a Worm Object
 *
 * And a Parameter Object
 * For internal manipulation
 *
 *
 */
void InitializeExperiment(Experiment* exp){


	/*** Create IplImage **/
		IplImage* SubSampled=cvCreateImage(cvSize(NSIZEX/2,NSIZEY/2),IPL_DEPTH_8U,1);
		IplImage* HUDS=cvCreateImage(cvSize(NSIZEX,NSIZEY),IPL_DEPTH_8U,1); ;

		exp->SubSampled=SubSampled;
		exp->HUDS=HUDS;

		/*** Create Frames **/
		Frame* fromCCD =CreateFrame(cvSize(NSIZEX,NSIZEY));
		Frame* forDLP =CreateFrame(cvSize(NSIZEX,NSIZEY));
		Frame* IlluminationFrame=CreateFrame(cvSize(NSIZEX,NSIZEY));

		exp->fromCCD=fromCCD;
		exp->forDLP=forDLP;
		exp->IlluminationFrame=IlluminationFrame;

		/** Create Worm Data Struct and Worm Parameter Struct **/
		WormAnalysisData* Worm=CreateWormAnalysisDataStruct();
		WormAnalysisParam* Params=CreateWormAnalysisParam();
		InitializeEmptyWormImages(Worm,cvSize(NSIZEX,NSIZEY));
		InitializeWormMemStorage(Worm);

		exp->Worm=Worm;
		exp->Params=Params;


		/** Setup Previous Worm **/
		WormGeom* PrevWorm=CreateWormGeom();
		exp->PrevWorm=PrevWorm;
}


/*
 * Free up all of the different allocated memory for the
 * experiment.
 *
 */
void ReleaseExperiment(Experiment* exp){
	/** Free up Frames **/
	if (exp->fromCCD!=NULL) DestroyFrame(&(exp->fromCCD));
	if (exp->forDLP!=NULL) DestroyFrame(&(exp->forDLP));
	if (exp->IlluminationFrame!=NULL) DestroyFrame(&(exp->IlluminationFrame));


	/** Free up Worm Objects **/
	if (exp->Worm!=NULL) {
		DestroyWormAnalysisDataStruct((exp->Worm));
		exp->Worm=NULL;
	}

	if (exp->Params!=NULL){
		DestroyWormAnalysisParam((exp->Params));
		exp->Params=NULL;
	}
	if (exp->PrevWorm!=NULL) {
		DestroyWormGeom(&(exp->PrevWorm));
		exp->PrevWorm=NULL;
	}

	/** Free up internal iplImages **/
	if (exp->SubSampled!=NULL) cvReleaseImage(&(exp->SubSampled));
	if (exp->HUDS!=NULL) cvReleaseImage(&(exp->HUDS));

	/** Free Up Calib Data **/
	if (exp->Calib!=NULL) DestroyCalibData(exp->Calib);

	/** Release Window Names **/
	ReleaseWindowNames(exp);

}

/* Destroy the experiment object.
 * To be run after ReleaseExperiment()
 */
void DestroyExperiment(Experiment** exp){
	free(*exp);
	*exp=NULL;
	printf("Andy is awesome.\n");
}


/*********************** RECORDING *******************/

/*
 * Sets up data recording and video recording
 * Will record video if exp->RECORDVID is 1
 * and record data if exp->RECORDDATA is 1
 *
 */
void SetupRecording(Experiment* exp){

	printf("About to setup recording\n");;
	char* DataFileName;
	if (exp->RECORDDATA)	{
		DataFileName=CreateFileName(exp->argv[1],exp->argv[2],".yaml");
		exp->DataWriter=SetUpWriteToDisk(DataFileName,exp->Worm->MemStorage);
		printf("Initialized data recording\n");
		DestroyFilename(&DataFileName);
	}

	/** Set Up Video Recording **/
	char* MovieFileName;
	char* HUDSFileName;

	if (exp->RECORDVID) {
		MovieFileName=CreateFileName(exp->argv[1],exp->argv[2],".avi");
		HUDSFileName=CreateFileName(exp->argv[1],exp->argv[2],"_HUDS.avi");
		exp->Vid = cvCreateVideoWriter(MovieFileName, CV_FOURCC('M','J','P','G'), 30,
					cvSize(NSIZEX/2, NSIZEY/2), 0);
		exp->VidHUDS=cvCreateVideoWriter(HUDSFileName, CV_FOURCC('M','J','P','G'), 30,
					cvSize(NSIZEX/2, NSIZEY/2), 0);
		DestroyFilename(&MovieFileName);
		DestroyFilename(&HUDSFileName);
		printf("Initialized video recording\n");
	}





}

/*
 * Finish writing video and  and data
 * and release
 *
 */
void FinishRecording(Experiment* exp){
	/** Finish Writing Video to File and Release Writer **/
	if (exp->Vid!=NULL) cvReleaseVideoWriter(&(exp->Vid));
	if (exp->VidHUDS!=NULL) cvReleaseVideoWriter(&(exp->VidHUDS));

	/** Finish Writing to Disk **/
	if (exp->RECORDDATA) FinishWriteToDisk(&(exp->DataWriter));

}




/************************************************/
/*   Timing Routines
 *
 */
/************************************************/

/*
 *This is the frame rate timer.
 */
void StartFrameRateTimer(Experiment* exp){
	exp->prevTime=clock();
	exp->prevFrames=0;
	printf("Quan is awesome.\n");

}

/*
 * If more than a second has elapsed
 * Calculate the frame rate and print i tout
 *
 */
void CalculateAndPrintFrameRate(Experiment* exp){
	/*** Print out Frame Rate ***/
	if ( (exp->Worm->timestamp-exp->prevTime) > CLOCKS_PER_SEC){
		printf("%d fps\n",exp->Worm->frameNum-exp->prevFrames);
		exp->prevFrames=exp->Worm->frameNum;
		exp->prevTime=exp->Worm->timestamp;
	}
}
