/***************************************************************************
*
* R2CamApi.h
*
* Header file for New R2 Kernel driver API for Windows NT.
* This should/will be the only interface to the kernel for both R2
* and BF libraries. This eventually should be in its own DLL.
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* 03/06/96	rjd		created
*
***************************************************************************/

#ifndef __R2CAMAPI__
#define __R2CAMAPI__

#include "R2Type.h"
#include "R2Board.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(KernelOS)

// Camera Control Functions

R2DLL R2RC	R2CAPI R2CamLineScanTimingFreeRunGetRange(RdRn Board,BFU32 PixelClockFrequency, PBFU32 pMinExposureTime,PBFU32 pMaxExposureTime,PBFU32 pMinLineRate,PBFU32 pMaxLineRate);
R2DLL R2RC	R2CAPI R2CamLineScanTimingFreeRunSet(RdRn Board,BFU32 PixelClockFrequency, PBFU32 pExposureTime,PBFU32 pLineRate,BFU32 Priority); 
R2DLL R2RC	R2CAPI R2CamLineScanTimingFreeRunGet(RdRn Board,BFU32 PixelClockFrequency, PBFU32 pExposureTime,PBFU32 pLineRate);
R2DLL R2RC	R2CAPI R2CamLineScanTimingOneShotGetRange(RdRn Board,BFU32 PixelClockFrequency, PBFU32 pMinExposureTime,PBFU32 pMaxExposureTime);
R2DLL R2RC	R2CAPI R2CamLineScanTimingOneShotSet(RdRn Board,BFU32 PixelClockFrequency, PBFU32 pExposureTime); 
R2DLL R2RC	R2CAPI R2CamLineScanTimingOneShotGet(RdRn Board,BFU32 PixelClockFrequency,PBFU32 pExposureTime);

#endif // KernelOS

#ifdef __cplusplus
}
#endif

#endif // __R2CAMAPI__
