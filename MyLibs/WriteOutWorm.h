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

	/** Experiment Time **/

} WriteOut;




/*
 * Shortcut function to create a filname.
 * Basically just concatenates three strings together.
 *
 */
char* CreateFileName(const char* dir, const char* core, const char* suffix);

/*
 * Destroy's a filename and deallocates the poitner and such.
 */
void DestroyFilename(char**);


/*
 * Sets up the WriteToDisk  given the base of a filname.
 * Creates a WriteOut Object.
 *
 * e.g. if you want to create a files named myexperiment.yaml and myexperiment.mov
 * pass in the string "myexperiment"
 *
 */
WriteOut* SetUpWriteToDisk(const char* filename, CvMemStorage* Mem);

/*
 * Start the process of writing out frames. (Formerly this was contained in SetUpWriteToDisk)
 */
void BeginToWriteOutFrames(WriteOut* DataWriter);

/*
 * Writes the command line argument to YAML.
 */
void WriteOutCommandLineArguments(WriteOut* DataWriter,int argc, char** argv);

/*
 *  Write out to YAML the default grid size for non-protocol based illumination
 */
void WriteOutDefaultGridSize(WriteOut* DataWriter, WormAnalysisParam* Param);

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
int AppendWormFrameToDisk(WormAnalysisData* Worm, WormAnalysisParam* Params, WriteOut* DataWriter);

/*
 * Finish writing to disk and close the file and such.
 * Destroys the Data Writer
 *
 */
int FinishWriteToDisk(WriteOut** DataWriter);


#endif /* WRITEOUTWORM_H_ */
