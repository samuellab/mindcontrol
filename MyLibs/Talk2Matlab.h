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
 * Talk2Matlab.h
 *
 *  Created on: Jul 29, 2009
 *      Author: Andy
 *
 *      This includes functions to that call an installed version of MATLAB.
 *      In general MATLAB, has much more higher-level image processing routines than C or OpenCV.
 *      From a programmer's perspective, MATLAB is easier to code. Unfortuantely it is not fast, which is why most
 *      of the OpticalMindControl program is done in OpenCV. Occasionally there are tasks, like image calibration
 *      where time is not critical. In these instances, the image processing work is handed off to MATLAB.
 *
 *      Note that this library also requires openCV, and my custom AndysOpenCVLib.h
 *
 *
 */

#ifndef TALK2MATLAB_H_
#define TALK2MATLAB_H_

#include "AndysOpenCVLib.h"

#include <highgui.h>
#include <cv.h>
#include <cxcore.h>





/*
 * Takes a sequence of format PairOfPoints composed of tuples of calibrated cvPoints. Also takes
 * an integer array that is preallocated to size 2*NSIZEX*NSIZEY*sizeof(int). This integer array is
 * populated such that CCD2DLPLookUp[ccd_x][ccd_y][x] is the x value of the pixel in DLP space
 * corresponding to a pixel at (ccd_x,ccd_y) in CCD space.
 *
 */
int T2Matlab_GenLookUpTable(CvSeq *CalibPoints, int *CCD2DLPLookUp, int nsizex, int nsizey, int CCDsizex, int CCDsizey);

#endif /* TALK2MATLAB_H_ */

