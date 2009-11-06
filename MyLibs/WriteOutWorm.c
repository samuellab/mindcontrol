/*
 * WriteOutWorm.c
 *
 *  Created on: Nov 3, 2009
 *      Author: Andy
 */

//OpenCV Headers
#include <cxcore.h>
#include <highgui.h>
#include <cv.h>

// Andy's Libraries

#include "AndysOpenCVLib.h"
#include "WormAnalysis.h"

#include "WriteOutWorm.h"

/*
 * Sets up the WriteToDisk  given the base of a filname.
 *
 * e.g. if you want to create a files named myexperiment.yaml and myexperiment.mov
 * pass in the string "myexperiment"
 *
 */
WriteOut* SetUpWriteToDisk(char* filename,WormAnalysisData* Worm){
	WriteOut* Files;
	/**  SetUp Write Out to File **/
	Files->fs=cvOpenFileStorage(strcat(filename,".yaml"),Worm->MemStorage,CV_STORAGE_WRITE);
	//cvWriteComment(Files->fs, "Worm experiment data made from mindcontrol project.\nleifer@fas.harvard.edu");
	cvStartWriteStruct(Files->fs,"Frames",CV_NODE_SEQ,NULL);
	return 0;
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
 */
int AppendWormFrameToDisk(WormAnalysisData* Worm, WriteOut* Files){
	CvFileStorage* fs=Files->fs;
	cvStartWriteStruct(fs,NULL,CV_NODE_MAP,NULL);
		cvWriteInt(fs,"FrameNumber",Worm->frameNum);
		if(cvPointExists(Worm->Segmented->Head)){
		cvStartWriteStruct(fs,"Head",CV_NODE_MAP,NULL);
		cvWriteInt(fs,"x",0);
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
	cvEndWriteStruct(fs);
	return 0;
}

/*
 * Finish writing to disk and close the file and such.
 *
 */
int FinishWriteToDisk(WriteOut* Files){
	CvFileStorage* fs=Files->fs;
	/** Finish writing this structure **/
	cvEndWriteStruct(fs);
	/** Close File Storage and Finish Writing Out to File **/
	cvReleaseFileStorage(&fs);
	return 0;
}
