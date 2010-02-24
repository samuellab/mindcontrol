/*
 * WriteOutWorm.c
 *
 *  Created on: Nov 3, 2009
 *      Author: Andy
 */
#include <stdio.h>
#include <time.h>
#include <string.h>

//OpenCV Headers
#include <cxcore.h>
#include <highgui.h>
#include <cv.h>

// Andy's Libraries

#include "AndysComputations.h"
#include "AndysOpenCVLib.h"
#include "WormAnalysis.h"
#include "version.h"

#include "WriteOutWorm.h"





/*
 * Shortcut function to create a filename.
 * Basically just concatenates three strings together.
 *
 */
char* CreateFileName(const char* dir, const char* core, const char* suffix){

	/* Prepare String with Time Stamp */
	char timestamp[30];
	time_t curtime;
	struct tm *loctime;
	/* Get the current time. */
		curtime= time (NULL);
	/* Convert to Local Time */
	loctime = localtime (&curtime);
	strftime(timestamp,30,"%Y%m%d_%H%M_",loctime);
	/* Allocate memory for filename */
	char* filename= (char*) malloc(strlen(timestamp)+strlen(dir)+strlen(core)+strlen(suffix)+1);


	/*Concatenate Strings */
	strcpy(filename,dir);
	strcat(filename,timestamp);
	strcat(filename,core);
	strcat(filename,suffix);
	printf("Preparing filename: %s\n",filename);

	free(&timestamp);
	return filename;
}

/*
 * Destroy's a filename and deallocates the poitner and such.
 */
void DestroyFilename(char** filename){
	free(*filename);
	*filename=NULL;
}


/*
 * Allocates memory for and creates a DataWriter object and sets all values to zero or NULL;
 */
WriteOut* CreateDataWriter(){
	WriteOut* DataWriter =(WriteOut*) malloc(sizeof(WriteOut));
	DataWriter->error=0;
	DataWriter->fs=NULL;
	return DataWriter;
}

/*
 * Sets up the WriteToDisk  given the base of a filname.
 * Creates a WriteOut Object.
 *
 * e.g. if you want to create a files named myexperiment.yaml and myexperiment.mov
 * pass in the string "myexperiment"
 *
 */
WriteOut* SetUpWriteToDisk(const char* dirfilename, const char* outfilename,  CvMemStorage* Mem){
	/** Create new instance of WriteOut object **/
	WriteOut* DataWriter = CreateDataWriter();

	/** Create Filenames **/
	char* YAMLDataFileName = CreateFileName(dirfilename, outfilename, ".yaml");

	/** Open YAML Data File for writing**/
	DataWriter->fs=cvOpenFileStorage(YAMLDataFileName,Mem,CV_STORAGE_WRITE);
	if (DataWriter->fs==0) {
		printf("DataWriter->fs is zero! Could you have specified the wrong directory?\n");
		--(DataWriter->error);
	}




	/** If there were errors, return immediately **/
	if (DataWriter->error < 0) return DataWriter;


	/** Write the header for the YAML data file **/
	cvWriteComment(DataWriter->fs, "Remote Control Worm Experiment Data Log\nMade by OpticalMindControl software\nleifer@fas.harvard.edu\n",0);
	cvWriteString(DataWriter->fs, "gitHash", build_git_sha,0);
	cvWriteString(DataWriter->fs, "gitBuildTime",build_git_time,0);

	/** Write Out Current Time**/
	  struct tm *local;
	  time_t t;

	  t = time(NULL);
	  local = localtime(&t);

	cvWriteString(DataWriter->fs, "ExperimentTime",asctime(local),0);

	free(YAMLDataFileName);
	return DataWriter;
}


/*
 * Start the process of writing out frames. (Formerly this was contained in SetUpWriteToDisk)
 */
void BeginToWriteOutFrames(WriteOut* DataWriter){
	cvStartWriteStruct(DataWriter->fs,"Frames",CV_NODE_SEQ,NULL);
	return;
}

/*
 * Writes the command line argument to YAML.
 */
void WriteOutCommandLineArguments(WriteOut* DataWriter,int argc, char** argv){
	char** largv=argv; /* Local Args */
	char* command= (char *) malloc(sizeof(char)*500);
	*command=0;
    while(argc--)
            sprintf(command +strlen(command) ,"%s ", *largv++);
    cvWriteString(DataWriter->fs,"Command",command);
}


/*
 *  Write out to YAML the default grid size for non-protocol based illumination
 */
void WriteOutDefaultGridSize(WriteOut* DataWriter, WormAnalysisParam* Param){
	/** Write out default grid size for non-protocol illumination **/
	cvStartWriteStruct(DataWriter->fs,"DefaultGridSizeForNonProtocolIllum",CV_NODE_MAP,NULL);
		cvWriteInt(DataWriter->fs,"x",Param->DefaultGridSize.width);
		cvWriteInt(DataWriter->fs,"y",Param->DefaultGridSize.height);
	cvEndWriteStruct(DataWriter->fs);

	return;
}

/*
 * Writes Out information of one frame of the worm to a disk
 * in YAML format.
 *
 * Note the Worm object must have the following fields
 * Worm->frameNum
 * Worm->Segmented->Head
 * Worm->Segmented->Tail
 * Worm->Segmented->LeftBound
 * Worm->Segmented->RightBound
 * Worm->Segmented->Centerline
 *
 * and Params object must have
 * Params->DLPOn
 * Params->IllumSegCenter
 * Params->IllumSegRadius
 * Params->IllumLRC
 *
 * And more now!
 */
int AppendWormFrameToDisk(WormAnalysisData* Worm, WormAnalysisParam* Params, WriteOut* DataWriter){

	CvFileStorage* fs=DataWriter->fs;

	cvStartWriteStruct(fs,NULL,CV_NODE_MAP,NULL);
		/** Frame Number Info **/
		cvWriteInt(fs,"FrameNumber",Worm->frameNum);

		/** TimeStamp **/
		cvWriteInt(fs,"sElapsed",GetSeconds(Worm->timestamp));
		cvWriteInt(fs,"msRemElapsed",GetMilliSeconds(Worm->timestamp));


		/** Segmentation Info **/
		if(cvPointExists(Worm->Segmented->Head)){
		cvStartWriteStruct(fs,"Head",CV_NODE_MAP,NULL);
			cvWriteInt(fs,"x",Worm->Segmented->Head->x);
			cvWriteInt(fs,"y",Worm->Segmented->Head->y);
		cvEndWriteStruct(fs);
		}

		if(cvPointExists(Worm->Segmented->Tail)){
		cvStartWriteStruct(fs,"Tail",CV_NODE_MAP,NULL);
			cvWriteInt(fs,"x",Worm->Segmented->Tail->x);
			cvWriteInt(fs,"y",Worm->Segmented->Tail->y);
		cvEndWriteStruct(fs);
		}


		if(cvSeqExists(Worm->Segmented->LeftBound)) cvWrite(fs,"BoundaryA",Worm->Segmented->LeftBound);
		if(cvSeqExists(Worm->Segmented->RightBound)) cvWrite(fs,"BoundaryB",Worm->Segmented->RightBound);
		if(cvSeqExists(Worm->Segmented->Centerline)) cvWrite(fs,"SegmentedCenterline",Worm->Segmented->Centerline);

		/** Illumination Information **/
		cvWriteInt(fs,"DLPIsOn",Params->DLPOn);
		cvWriteInt(fs,"FloodLightIsOn",Params->IllumFloodEverything);
		cvWriteInt(fs,"IllumInvert",Params->IllumInvert);

		CvPoint origin=ConvertSlidlerToWormSpace(Params->IllumSquareOrig,Params->DefaultGridSize);
		cvStartWriteStruct(fs,"IllumRectOrigin",CV_NODE_MAP,NULL);
			cvWriteInt(fs,"x",origin.x);
			cvWriteInt(fs,"y",origin.y);
		cvEndWriteStruct(fs);

		cvStartWriteStruct(fs,"IllumRectRadius",CV_NODE_MAP,NULL);
			cvWriteInt(fs,"x",Params->IllumSquareRad.width);
			cvWriteInt(fs,"y",Params->IllumSquareRad.height);
		cvEndWriteStruct(fs);



		/** Protocol Information **/

		cvWriteInt(fs,"ProtocolIsOn",Params->ProtocolUse);
		cvWriteInt(fs,"ProtocolStep",Params->ProtocolStep);
	cvEndWriteStruct(fs);

	return 0;
}

/*
 * Finish writing to disk and close the file and such.
 * Destroys the Data Writer
 *
 */
int FinishWriteToDisk(WriteOut** DataWriter){
	CvFileStorage* fs=(*DataWriter)->fs;
	/** Finish writing this structure **/
	cvEndWriteStruct(fs);

	/** Close File Storage and Finish Writing Out to File **/
	cvReleaseFileStorage(&fs);
	free(*DataWriter);
	*DataWriter=NULL;
	return 0;
}
