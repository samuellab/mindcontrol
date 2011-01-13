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
 * experiment.h
 *
 *	The experiment.c/.h library is designed to be an extremely high level library.
 *	The idea here is to have all of the elements of an experiment laid out, such that
 *	a user need only to call a few high level functions to run an experiment.
 *
 *  Created on: Nov 30, 2009
 *      Author: Andy
 */

#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

#ifndef WORMANALYSIS_H_
 #error "#include WormAnalysis.h" must appear in source files before "#include experiment.h"
#endif
#ifndef ILLUMWORMPROTOCOL_H_
 #error "#include IllumWormProtocol.h" must appear in source files before "#include experiment.h"
#endif
#ifndef WRITEOUTWORM_H_
 #error "#include WriteOutWorm.h" must appear in source files before "#include experiment.h"
#endif
#ifndef TALK2DLP_H_
 #error "#include Talk2DLP.h" must appear in source files before "#include experiment.h"
#endif
#ifndef TALK2CAMERA_H_
 #error "#include Talk2Camera.h" must appear in source files before "#include experiment.h"
#endif
#ifndef TALK2CAMERA_H_
 #error "#include Talk2Stage.h" must appear in source files before "#include experiment.h"
#endif
#ifndef TALK2FRAMEGRABBER_H_
 #error "#include Talk2FrameGrabber.h" must appear in source files before "#include experiment.h"
#endif
#ifndef ANDYSOPENCVLIB_H_
 #error "#include AndysOpenCVLib.h" must appear in source files before "#include experiment.h"
#endif


#define EXP_ERROR -1
#define EXP_SUCCESS 0
#define EXP_VIDEO_RAN_OUT 1

typedef struct ExperimentStruct{
	/** Simulation? True/false **/
	int SimDLP; //1= simulate the DLP, 0= real DLP
	int VidFromFile; // 1 =Video from File, 0=Video From Camera

	/** GuiWindowNames **/
	char* WinDisp ;
	char* WinCon1;
	char* WinCon2;
	char* WinCon3;


	/** CommandLine Input **/
	char** argv;
	int argc;
	char* dirname;
	char* outfname;
	char* infname;
	char* protocolfname;

	/** Protocol Data **/
    Protocol* p;
    int pflag;

	/** Camera Input**/
	CamData* MyCamera;

	/** FrameGrabber Input**/
	FrameGrabber* fg;
	bool UseFrameGrabber;

	/** Video Capture (for simulation mode) **/
	CvCapture* capture;

	/** MostRecently Observed CameraFrameNumber **/
	unsigned long lastFrameSeenOutside;

	/** DLP Output **/
	long myDLP;

	/** Calibration Data  Object**/
	CalibData* Calib;

	/** User-configurable Worm-related Parameters **/
	WormAnalysisParam* Params;

	/** Information about Our Worm **/
	WormAnalysisData* Worm;

	/** Information about the Previous frame's Worm **/
	WormGeom* PrevWorm;

	/** Segmented Worm in DLP Space **/
	SegmentedWorm* segWormDLP;

	/** internal IplImage **/
	IplImage* SubSampled; // Image used to subsample stuff
	IplImage* HUDS;  //Image used to generate the Heads Up Display
	IplImage* CurrentSelectedImg;

	/** Internal Frame data types **/
	Frame* fromCCD;
	Frame* forDLP;
	Frame* IlluminationFrame;

	/** Write Data To File **/
	WriteOut* DataWriter;

	/** Write Video To File **/
	CvVideoWriter* Vid;  //Video Writer
	CvVideoWriter* VidHUDS;

	/** Timing  Information **/
	clock_t now;
	clock_t last;

	/** Illumination Timer **/
	double illumStart;

	/** Illum Head-To-Tail Sweep Internal Variables **/
	double illumSweepHTtimer;


	/** Frame Rate Information **/
	int nframes;
	int prevFrames;
	long prevTime;

	/** Macros **/
	int RECORDVID;
	int RECORDDATA;

	/** Stage Control **/
	int stageIsPresent;
	HANDLE stage; // Handle to USB stage object
	CvPoint stageVel; //Current velocity of stage
	CvPoint stageCenter; // Point indicating center of stage.
	CvPoint stageFeedbackTargetOffset; //Target of the stage feedback loop as a delta distance in pixels from the center of the image
	int stageIsTurningOff; //1 indicates stage is turning off. 0 indicates stage is on or off.

	/** Error Handling **/
	int e;

} Experiment;



/*
 * Creates a new experiment object and sets values to zero.
 */
Experiment* CreateExperimentStruct();


/*
 * Load the command line arguments into the experiment object
 */
void LoadCommandLineArguments(Experiment* exp, int argc, char** argv);

/*
 * Handle CommandLine Arguments
 * Parses commandline arguments.
 * Decides if user wants to record video or recorddata
 */
int HandleCommandLineArguments(Experiment* exp);



/**
 * The illumination sweep is a feature that lets the user automatically
 * increment an on-the-fly illumination step by step across the worm
 */
int HandleIlluminationSweep(Experiment* exp);

/** Handle Transient Illumination Timing **/
int HandleIlluminationTiming(Experiment* exp);

/*
 * Flips the simulation variable to on.
 */
void SetExpToSimulation(Experiment* exp);

/* Assigns Default window names to the experiment object
 *
 */
void AssignWindowNames(Experiment* exp);

/*
 * Release the memopry associated with window names
 * and set their pointers to Null
 */
void ReleaseWindowNames(Experiment* exp);


/*
 * SetupGui
 *
 */
void SetupGUI(Experiment* exp);

/*
 * Update's trackbar positions for variables that can be changed by the software
 *
 */
void UpdateGUI(Experiment* exp);


/*
 * Initialize camera library
 * Allocate Camera Data
 * Select Camera and Show Properties dialog box
 * Start Grabbing Frames as quickly as possible
 *
 * OR open up the video file for reading.
 */
void RollVideoInput(Experiment* exp);

/** Grab a Frame from either camera or video source
 *
 */
int GrabFrame(Experiment* exp);

/*
 * Create calibration Data structure
 * Load calibration data from file
 * return -1 if the calibration from file doesn't exist.
 */
int HandleCalibrationData(Experiment* exp);




/*
 * This function allocates images and frames
 * And a Worm Object
 *
 * And a Parameter Object
 * For internal manipulation
 *
 *
 */
void InitializeExperiment(Experiment* exp);


/*
 * Free up all of the different allocated memory for the
 * experiment.
 *
 */
void ReleaseExperiment(Experiment* exp);




/*********************************************
 *
 * Image Acquisition
 *
 */

/*
 * Is a frame ready from the camera?
 */
int isFrameReady(Experiment* exp);

/******************
 * Recording
 */

/* Destroy the experiment object.
 * To be run after ReleaseExperiment()
 */
void DestroyExperiment(Experiment** exp);


/*
 * Setsup data recording and video recording
 * Will record video if exp->RECORDVID is 1
 * and record data if exp->RECORDDATA is 1
 *
 */
int SetupRecording(Experiment* exp);


/*
 * Finish writing video and  and data
 * and release
 *
 */
void FinishRecording(Experiment* exp);


/************************************************/
/*   Frame Rate Routines
 *
 */
/************************************************/

/*
 *This is the frame rate timer.
 */
void StartFrameRateTimer(Experiment* exp);

/*
 * If more than a second has elapsed
 * Calculate the frame rate and print i tout
 *
 */
void CalculateAndPrintFrameRate(Experiment* exp);



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
void ClearDLPifNotDisplayingNow(Experiment* exp);


/*
 * Given an image in teh worm object, segment the worm
 *
 */
void DoSegmentation(Experiment* exp);


/*
 * Preparesthe Selected Display
 *
 */
void PrepareSelectedDisplay(Experiment* exp);


/*
 * Use the slider bar to generate a rectangle in an arbitrary location and illuminate with it on the fly
 *
 */
int DoOnTheFlyIllumination(Experiment* exp);

/**
 * Invert the illumination, so white becomes black and vice-versa.
 */
void InvertIllumination(Experiment* exp);


/*
 *
 * Handle KeyStroke
 *
 * Returns 1 when the user is trying to exit
 *
 */
int HandleKeyStroke(int c, Experiment* exp);

/*
 * Write video and data to Disk
 *
 */
void DoWriteToDisk(Experiment* exp);

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
void LoadProtocol(Experiment* exp);

/*
 *  Releases a protocol from the experiment object.
 */
void ReleaseProtocolFromExperiment(Experiment* exp);


/*
 * Writes a recent frame number to file
 */
int WriteRecentFrameNumberToFile(Experiment* exp);


/**************************************************
 * Stage Tracking and FEedback System
 *
 * This should really probably go in a special library called Stage Tracking
 * that depends on both OpenCV AND Talk2STage.c, but its a huge pain to modify the makefile
 * to create a new library that has only one function in it.
 *
 * Alternatively this could conceivably go in Talk2Stage.c, but then I find it weird
 * that Talk2Stage.c should depend on OpenCV, because ultimatley it should be more general.
 *
 * It doesn't really belong in experiment.c either because it is not a method of experiment.c
 * But for now that is where it will sit.
 *
 */

/*
 * Scan for the USB device.
 */
int InvokeStage(Experiment* exp);

/*
 * Update the Stage Tracker.
 * If the Stage tracker is not initialized, don't do anything.
 * If the stage tracker is initialized then either do the tracking,
 * or if we are in the process of turning off tracking off, then tell
 * the stage to halt and update flags.
 */
int HandleStageTracker(Experiment* exp);

int ShutOffStage(Experiment* exp);


#endif /* EXPERIMENT_H_ */
