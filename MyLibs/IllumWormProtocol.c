/*
 * WormIllumProtocol.c
 *
 * This library is designed to have objects and functions used to
 * write, analyze and excecute illumination protocols written for worms.
 *
 * As such it relies on the high level WormAnalysis library.
 * But Other libraries like WriteOutWorm likely depend upon it.
 *
 *
 *  Created on: Nov 11, 2009
 *      Author: Andy
 */

#include <stdio.h>
#include <time.h>

//OpenCV Headers
#include <cxcore.h>
#include <highgui.h>
#include <cv.h>

// Andy's Libraries

#include "AndysOpenCVLib.h"
#include "WormAnalysis.h"
#include "IllumWormProtocol.h"

