/*
 * WriteOutWorm.h
 *
 *  Created on: Nov 3, 2009
 *      Author: Andy
 */

#ifndef WRITEOUTWORM_H_
#define WRITEOUTWORM_H_


typedef struct WriteOutStruct{
	/** Current Frame **/
	CvFileStorage* fs;
	// Whatever the video file id thingie is.
} WriteOut;

/*
 * Sets up the WriteToDisk  given the base of a filname.
 * Creates a WriteOut Object.
 *
 * e.g. if you want to create a files named myexperiment.yaml and myexperiment.mov
 * pass in the string "myexperiment"
 *
 */
WriteOut* SetUpWriteToDisk(char* filename, CvMemStorage* Mem);

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
int AppendWormFrameToDisk(WormAnalysisData* Worm, WriteOut* DataWriter);

/*
 * Finish writing to disk and close the file and such.
 * Destroys the Data Writer
 *
 */
int FinishWriteToDisk(WriteOut** DataWriter);


#endif /* WRITEOUTWORM_H_ */
