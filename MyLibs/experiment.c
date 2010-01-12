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
#include <unistd.h>
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <assert.h>

//C++ header
#include <iostream>
#include <limits>


//OpenCV Headers
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>

//Timer Lib
#include "../3rdPartyLibs/tictoc.h"

//Andy's Personal Headers
#include "AndysOpenCVLib.h"
#include "Talk2Camera.h"
#include "Talk2DLP.h"
#include "Talk2Matlab.h"
#include "AndysComputations.h"
#include "WormAnalysis.h"
#include "IllumWormProtocol.h"
#include "TransformLib.h"
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

	/** Simulation? True/False **/
	exp->SimDLP=0;
	exp->VidFromFile=0;

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
	exp->outfname=NULL;
	exp->infname=NULL;
	exp->dirname=NULL;
	exp->protocolfname=NULL;

	/** Protocol Data **/
	exp->p=NULL;
	exp->pflag=0;

	/** Camera Input**/
	exp->MyCamera=NULL;

	/** Video input **/
	exp->capture=NULL;

	/** Last Observerd CamFrameNumber **/
	exp->lastFrameSeenOutside=0;

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

	/** Segmented Worm in DLP Space **/
	exp->segWormDLP=NULL;

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

	/** Error Handling **/
	exp->e=0;

	return exp;

}



/*
 * Load the command line arguments into the experiment object
 */
void LoadCommandLineArguments(Experiment* exp, int argc, char** argv){
	exp->argc=argc;
	exp->argv=argv;
}



void displayHelp(){
	printf("Given a video stream, this software analyzes each frame, finds a worm and generates an illumination pattern.\n");
	printf("\nUsage:\n");
	printf("If run with no arguments, the software uses video from an attached camera, illuminates a worm with an attached DLP and records no data.\n");
	printf("Optional arguments:\n");
	printf("\t-o\tbaseFileName\n\t\tWrite video and data output to file using the specified base file name.\n");
	printf("\t-d\tD:/Path/To/My/Directory/\n\t\tWrite the video and data output to the specified directory. NOTE: it is important to have the trailing slash.\n");
	printf("\t-i\tInputVideo.avi\n\t\tNo camera. Use video file source instead.\n");
	printf("\t-s\n\t\tSimulate the existence of DLP. (No physical DLP required.)\n"); // <----- ANDY ADD SIMULATE FUNCTIONALITYkkk
}


/*
 * Handle CommandLine Arguments
 * Parses commandline arguments.
 * Decides if user wants to record video or recorddata
 */

int HandleCommandLineArguments(Experiment* exp) {
	int dflag = 0;
	opterr = 0;

	int c;
	while ((c = getopt(exp->argc, exp->argv, "si:d:o:p:")) != -1) {
		switch (c) {
		case 'i': /** specify input video file **/
			exp->VidFromFile = 1;
			exp->infname = optarg;
			if (optarg == NULL) {
				printf(
						"Error. Given -i switch but no input video file was specified.\n");
				return -1;
			}
			break;

		case 'd': /** specifiy directory **/
			dflag = 1;
			if (optarg != NULL) {
				exp->dirname = optarg;
			} else {
				exp->dirname = "./"; // set to default, local directory;
			}
			break;

		case 'o': /** specify base filename of output **/
			if (optarg != NULL) {
				exp->outfname = optarg;
			} else {
				exp->outfname = "worm"; // set the base filename to the devault of worm;
			}
			exp->RECORDVID = 1;
			exp->RECORDDATA = 1;
			break;

		case 's': /** Run in DLP simulation Mode **/
			exp->SimDLP = 1;
			break;

		case 'p': /** Load Protocol **/
			if (optarg != NULL) {
				exp->protocolfname = optarg;
				exp->pflag=1;
			} else {
				fprintf(stderr, "Detected '-p' switch but no protocol file specified\n");
			}
			break;


		case '?':
			if (optopt == 'i' || optopt == 'c' || optopt == 'd' || optopt
					== 's') {
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				displayHelp();
				return -1;
			} else if (isprint(optopt)) {
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
				displayHelp();
				return -1;
			} else {
				fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
				displayHelp();
				return -11;
			}
		default:
			displayHelp();
			return -1;
		} // end of switch

	} // end of while loop
	return 1;
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

	/** If we have loaded a protocol, set up protocol specific sliders **/
	if (exp->pflag){
		cvCreateTrackbar("Protocol",exp->WinCon2,&(exp->Params->ProtocolUse),1,(int) NULL);
		cvCreateTrackbar("ProtoStep",exp->WinCon2,&(exp->Params->ProtocolStep),exp->p->Steps->total - 1,(int) NULL);
	}
	printf("Created trackbars and windows\n");
	return;

}


/*** Start Video Camera ***/



/*
 * Initialize camera library
 * Allocate Camera Data
 * Select Camera and Show Properties dialog box
 * Start Grabbing Frames as quickly as possible
 * *
 * OR open up the video file for reading.
 */
void RollVideoInput(Experiment* exp){
	if (exp->VidFromFile){
		/** Define the File catpure **/
		exp->capture=cvCreateFileCapture(exp->infname);
	}else{

	/** Turn on Camera **/
	T2Cam_InitializeLib();
	T2Cam_AllocateCamData(&(exp->MyCamera));
	T2Cam_ShowDeviceSelectionDialog(&(exp->MyCamera));
	/** Start Grabbing Frames and Update the Internal Frame Number iFrameNumber **/
	T2Cam_GrabFramesAsFastAsYouCan(&(exp->MyCamera));

	}
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

		/** Create SegWormDLP object using memory from the worm object **/
		exp->segWormDLP=CreateSegmentedWormStruct();

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


	/** Free up Strings **/
	exp->dirname=NULL;
	exp->infname=NULL;
	exp->outfname=NULL;

	/** The segmented worm DLP structure **/
	// Note that the memorystorage for the Cvseq's are in exp->worm->Memorystorage
	free(exp->segWormDLP);

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
}




/*********************************************
 *
 * Image Acquisition
 *
 */



/** Grab a Frame from either camera or video source
 *
 */
int GrabFrame(Experiment* exp){

	if (!(exp->VidFromFile)){ /** If This isn't a simulation.. **/
		exp->lastFrameSeenOutside = exp->MyCamera->iFrameNumber;


		/*** Create a local copy of the image***/
		LoadFrameWithBin(exp->MyCamera->iImageData,exp->fromCCD);
	} else {

		IplImage* tempImg;
		/** Grab the frame from the video **/
		tempImg=cvQueryFrame(exp->capture);


		if (tempImg==NULL){
			printf("There was an error querying the frame from video!\n");
			return -1;
		}

		/** Create a new temp image that is grayscale and of the same size **/
		IplImage* tempImgGray=cvCreateImage(cvGetSize(tempImg),IPL_DEPTH_8U,1);


		/** Convert Color to GrayScale **/
		cvCvtColor(tempImg,tempImgGray,CV_RGB2GRAY);


		/** Load the frame into the fromCCD frame object **/
		/*** ANDY! THIS WILL FAIL BECAUSE THE SIZING ISN'T RIGHT **/
		LoadFrameWithImage(tempImgGray,exp->fromCCD);
		cvReleaseImage(&tempImgGray);
		/*
		 * Note: for some reason thinks crash when you go cvReleaseImage(&tempImg)
		 * And there don't seem to be memory leaks if you leave it. So I'm going to leave it in place.
		 *
		 */
	}

	exp->Worm->frameNum++;
	return 0;
}


/*
 * Is a frame ready from the camera?
 *
 */
int isFrameReady(Experiment* exp){
	if (!(exp->VidFromFile)){ /** If This isn't a simulation.. **/
		/** check if we have a new frame read **/
		return (exp->MyCamera->iFrameNumber > exp->lastFrameSeenOutside);
	} else{
		/** Otherwise this is a simulation **/

		/** fake like we're waiting for something **/
		//cvWaitKey(0);
		return 1;
	}
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
		if (exp->dirname==NULL || exp->outfname==NULL  ) printf("exp->dirname or exp->outfname is NULL!\n");
		DataFileName=CreateFileName(exp->dirname,exp->outfname,".yaml");
		exp->DataWriter=SetUpWriteToDisk(DataFileName,exp->Worm->MemStorage);
		printf("Initialized data recording\n");
		DestroyFilename(&DataFileName);
	}

	/** Set Up Video Recording **/
	char* MovieFileName;
	char* HUDSFileName;

	if (exp->RECORDVID) {
		if (exp->dirname==NULL || exp->outfname==NULL  ) printf("exp->dirname or exp->outfname is NULL!\n");

		MovieFileName=CreateFileName(exp->dirname,exp->outfname,".avi");
		HUDSFileName=CreateFileName(exp->dirname,exp->outfname,"_HUDS.avi");


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
/*   Frame Rate Routines
 *
 */
/************************************************/

/*
 *This is the frame rate timer.
 */
void StartFrameRateTimer(Experiment* exp){
	exp->prevTime=clock();
	exp->prevFrames=0;

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




/************************************************/
/*   Action Chunks
 *
 */
/************************************************/


/*
 * If the DLP is on, don't do anything.
 * If the DLP is off, clear the IlluminationFrame
 * and send that to the DLP so that none of hte DLP mirrors
 * are exposed
 */
void ClearDLPifNotDisplayingNow(Experiment* exp){
	/** If the DLP is not displaying **/
	if (exp->Params->DLPOn==0){
		/** Clear the DLP **/
		RefreshFrame(exp->IlluminationFrame);
		if (!(exp->SimDLP)) T2DLP_SendFrame((unsigned char *) exp->IlluminationFrame->binary, exp->myDLP);
	}
}

/*
 * Given an image in teh worm object, segment the worm
 *
 */
void DoSegmentation(Experiment* exp) {
	_TICTOC_TIC_FUNC
	/*** <segmentworm> ***/

	/*** Find Worm Boundary ***/

	TICTOC::timer().tic("_FindWormBoundary",exp->e);
	if (!(exp->e)) FindWormBoundary(exp->Worm,exp->Params);
	TICTOC::timer().toc("_FindWormBoundary",exp->e);



	/*** Find Worm Head and Tail ***/
	if (!(exp->e)) exp->e=GivenBoundaryFindWormHeadTail(exp->Worm,exp->Params);
	/** If we are doing temporal analysis, improve the WormHeadTail estimate based on prev frame **/
	if (exp->Params->TemporalOn && !(exp->e)) PrevFrameImproveWormHeadTail(exp->Worm,exp->Params,exp->PrevWorm);




	/*** Segment the Worm ***/
	if (!(exp->e)) exp->e=SegmentWorm(exp->Worm,exp->Params);



	/** Update PrevWorm Info **/
	if (!(exp->e)) LoadWormGeom(exp->PrevWorm,exp->Worm);

	/*** </segmentworm> ***/
	_TICTOC_TOC_FUNC

}

/*
 * Display the Selected Display
 *
 */
void DoDisplaySelectedDisplay(Experiment* exp){
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

}


/*
 * Write video and data to Disk
 *
 */
void DoWriteToDisk(Experiment* exp){

	/** Record VideoFrame to Disk**/
	if (exp->RECORDVID && exp->Params->Record) {
		cvResize(exp->Worm->ImgOrig,exp->SubSampled,CV_INTER_LINEAR);
		cvWriteFrame(exp->Vid,exp->SubSampled);
		cvResize(exp->HUDS,exp->SubSampled,CV_INTER_LINEAR);
		cvWriteFrame(exp->VidHUDS,exp->SubSampled);
	}

	/** Record data frame to diskl **/
	if (exp->RECORDDATA && exp->Params->Record) AppendWormFrameToDisk(exp->Worm,exp->Params,exp->DataWriter);

}


/*********************
 *
 *  Protocol related functions
 *
 */

/*
 * Load a protocol from a YAML file into the
 * experiment structure.
 *
 * Protocol filename must be specified in exp->protocolfname
 */
void LoadProtocol(Experiment* exp){
	exp->p=LoadProtocolFromFile(exp->protocolfname);
	/** Set the protocol to be enabled by default. **/
	exp->Params->ProtocolUse=1;
}

/*
 *  Releases a protocol from the experiment object.
 */
void ReleaseProtocolFromExperiment(Experiment* exp){
	if (exp->p==NULL) return;
	DestroyProtocolObject(&(exp->p));
	return;
}



