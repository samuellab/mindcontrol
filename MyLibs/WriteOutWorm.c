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
#include "WriteOutWorm.h"
#include "AndysOpenCVLib.h"
#include "WormAnalysis.h"



/*
 * Sets up the WriteToDisk  given the base of a filname.
 *
 * e.g. if you want to create a files named myexperiment.yaml and myexperiment.mov
 * pass in the string "myexperiment"
 *
 */
WriteOut* SetUpWriteToDisk(char* filename){
	WriteOut Files;
	Files->datafile=strcat(filename,".yaml");
	/**  SetUp Write Out to File **/
	Files->fs=cvOpenFileStorage(,Worm->MemStorage,CV_STORAGE_WRITE);
	cvWriteComment(Files->fs, "Worm experiment data made from mindcontrol project.\nleifer@fas.harvard.edu");
	cvStartWriteStruct(fs,"Frames",CV_NODE_SEQ,NULL);
	return 0;
}

int AppendWormFrameToDisk(WormAnalysisData* Worm, WriteOut* Files){
	cvStartWriteStruct(fs,NULL,CV_NODE_MAP,NULL);
		cvWriteInt(fs,"FrameNumber",Worm->frameNum);
		cvStartWriteStruct(fs,"Head",CV_NODE_MAP,NULL);
		cvWriteInt(fs,"x",0);
			cvWriteInt(fs,"x",Worm->Segmented->Head->x);
			cvWriteInt(fs,"y",Worm->Segmented->Head->y);
		cvEndWriteStruct(fs);
		}
		cvStartWriteStruct(fs,"Tail",CV_NODE_MAP,NULL);
			cvWriteInt(fs,"x",Worm->Segmented->Tail->x);
			cvWriteInt(fs,"y",Worm->Segmented->Tail->y);
		cvEndWriteStruct(fs);


		cvWrite(fs,"BoundaryA",Worm->Segmented->LeftBound);
		cvWrite(fs,"BoundaryB",Worm->Segmented->RightBound);
		cvWrite(fs,"SegmentedCenterline",Worm->Segmented->Centerline);
	cvEndWriteStruct(fs

	return 0;
}

int FinishWriteToDisk(){
	return 0;
}
