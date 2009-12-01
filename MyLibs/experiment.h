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

#define _N_TIME_PTS 100
static int total_time[_N_TIME_PTS];
static int _n_frames_run = 0;

typedef struct ExperimentStruct{
	/** GuiWindowNames **/
	char* WinDisp ;
	char* WinCon1;
	char* WinCon2;
	char* WinCon3;

	/** Error information **/
	int e;

	/** CommandLine Input **/
	char** argv;
	int argc;

	/** Camera Input**/
	CamData* MyCamera;

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

	/** internal IplImage **/
	IplImage* SubSampled; // Image used to subsample stuff
	IplImage* HUDS;  //Image used to generate the Heads Up Display

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

	/** Frame Rate Information **/
	int nframes;
	int prevFrames;
	long prevTime;

	/** Macros **/
	int RECORDVID;
	int RECORDDATA;
	/* test */

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
 * Initialize camera library
 * Allocate Camera Data
 * Select Camera and Show Properties dialog box
 * Start Grabbing Frames as quickly as possible
 */
void RollCamera(Experiment* exp);

/*
 * Create calibration Data structure
 * Load calibration data from file
 * return -1 if the calibration from file doesn't exist.
 */
int HandleCalibrationData(Experiment* exp);
#endif /* EXPERIMENT_H_ */
