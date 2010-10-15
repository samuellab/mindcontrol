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
 * WriteOutWorm.h
 *
 *  Created on: Nov 3, 2009
 *      Author: Andy
 */


/*
 *
 * This library contains functions to write out frame-by-frame information about
 * the worm's position, orientation and the illumination stimuli that it is receiving.
 *
 * All of the data is written out using YAML which is a human and computer readable file
 * format.
 *
 */


#ifndef WRITEOUTWORM_H_
#define WRITEOUTWORM_H_


typedef struct WriteOutStruct{

	CvFileStorage* fs; //Experiment data in YAML format
	char* filename;
	int error;


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
WriteOut* SetUpWriteToDisk(const char* dirfilename, const char* outfilename,  CvMemStorage* Mem);

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
