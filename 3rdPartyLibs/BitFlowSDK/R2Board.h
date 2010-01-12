/***************************************************************************
*
* R2Board.h
*
* Public defines, parameters and structures.
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* 06/25/96	rjd		created
*
***************************************************************************/

#ifndef __R2BOARD__
#define __R2BOARD__ 

#include "BFSystem.h"
#include "BFDef.h"
#include "BFBoard.h"
#include "BFTabError.h"

// Error messages used during driver open phase.

#define R2SYS_ERROR							BFSYS_ERROR
#define R2SYS_ERROR_REGISTRY				BFSYS_ERROR_REGISTRY
#define R2SYS_ERROR_NOTFOUND				BFSYS_ERROR_NOTFOUND
#define R2SYS_ERROR_SIZE					BFSYS_ERROR_SIZE
#define R2SYS_ERROR_ALLOCACTION				BFSYS_ERROR_ALLOCACTION
#define R2SYS_ERROR_CREATEFILE				BFSYS_ERROR_CREATEFILE

// Board state.

#define R2SYS_STATUS_ALLOCATED				BFSYS_STATUS_ALLOCATED
#define	R2SYS_STATUS_HANDLEOPEN				BFSYS_STATUS_HANDLEOPEN
#define R2SYS_STATUS_CAMALLOC				BFSYS_STATUS_CAMALLOC
#define R2SYS_STATUS_BRDINIT				BFSYS_STATUS_BRDINIT
#define R2SYS_STATUS_MUTEXLIVES				BFSYS_STATUS_MUTEXLIVES

// Board open options.

#define R2SysInitialize						BFSysInitialize			// Initialize the system. 
#define R2SysExclusive						BFSysExclusive			// If not already open, open exclusively. 
#define R2SysNoIntThread					BFSysNoIntThread		// Do not activate interrupt thread.
#define R2SysNoCameraOpen					BFSysNoCameraOpen		// Do not open any camera configurations.
#define R2SysNoAlreadyOpenMess				BFSysNoAlreadyOpenMess	// Supress already open warning message.
#define R2SysNoOpenErrorMess				BFSysNoOpenErrorMess	// Supress error pop-ups in R2BrdOpen

// Camera open options.

#define R2SysConfigure						BFSysConfigure

// Acquistion commands.

#define R2ConFreeze							BFConFreeze
#define R2ConAbort							BFConAbort
#define R2ConSnap							BFConSnap
#define R2ConGrab							BFConGrab
#define R2ConReset							BFConReset

// General enable/disable flags.

#define R2ConDisable						BFConDisable
#define R2ConEnable							BFConEnable

// Acquisition modes.

#define R2ConWait							BFConWait
#define R2ConAsync							BFConAsync

// DMA commands.

#define R2ConDMAGo							BFConDMAGo
#define R2ConDMAAbort						BFConDMAAbort
#define	R2ConDMAReset						BFConDMAReset

// parameters for R2BrdInquire()

#define R2BrdInqModel						BFBrdInqModel
#define R2BrdInqSpeed						BFBrdInqSpeed
#define R2BrdInqLUT							BFBrdInqLUT
#define R2BrdInqIDReg						BFBrdInqIDReg
#define R2BrdInqNumCams						BFBrdInqNumCams
#define R2BrdAttachedCamera0FileName		BFBrdAttachedCamera0FileName

// return values for R2BrdInquire() 

#define R2BrdValModel11						BFBrdValModel11
#define R2BrdValModel12						BFBrdValModel12
#define R2BrdValModel13						BFBrdValModel13
#define R2BrdValModel14						BFBrdValModel14
#define R2BrdValModel23						BFBrdValModel23
#define R2BrdValModel24						BFBrdValModel24
#define R2BrdValModel44						BFBrdValModel44
#define R2BrdValLUT8And12					BFBrdValLUT8And12
#define R2BrdValLUT16						BFBrdValLUT16
#define R2BrdValLUTNone						BFBrdValLUTNone
#define R2BrdValSpeedNormal					BFBrdValSpeedNormalR2
#define R2BrdValSpeed40MHz					BFBrdValSpeed40MHzR2

// parameters for R2CamInquire() can also be passed to R2BrdInquire to inquire of current camera

#define R2CamInqMask						BFCamInqMask // used to pass member to camera function
#define R2CamInqXSize						BFCamInqXSize
#define R2CamInqYSize						BFCamInqYSize0
#define R2CamInqFormat						BFCamInqFormat
#define R2CamInqPixBitDepth					BFCamInqPixBitDepth
#define R2CamInqBytesPerPix					BFCamInqBytesPerPix
#define R2CamInqAqTimeout					BFCamInqAqTimeout
#define R2CamInqHostFrameSize				BFCamInqFrameSize0
#define R2CamInqDisplayFrameSize			BFCamInqDisplayFrameSize0
#define R2CamInqHostFrameWidth				BFCamInqFrameWidth
#define R2CamInqDisplayFrameWidth			BFCamInqDisplayFrameWidth
#define R2CamInqPixBitDepthDisplay			BFCamInqPixBitDepthDisplay
#define R2CamInqBytesPerPixDisplay			BFCamInqBytesPerPixDisplay
#define R2CamInqBitsPerSequence				BFCamInqBitsPerSequence
#define R2CamInqBitsPerSequenceDisplay		BFCamInqBitsPerSequenceDisplay
#define R2CamInqHasCamControl				BFCamInqHasCamControl
#define R2CamInqCamType						BFCamInqCamType
#define R2CamInqControlType					BFCamInqControlType

// Camera brand info (used on EXPMOD first parameter) parameter

#define R2CamModelDalsaLineScanWithPRIN		BFCamModelDalsaLineScanWithPRIN
#define R2CamModelNumberOfModels			BFCamModelNumberOfModels

// Camera control masks (used on EXPMOD second parameter) parameter

#define R2CamTypeMask						BFCamTypeMask
#define R2CamControlTypeMask				BFCamControlTypeMask

// Camera Control and exposure mode parameters

#define R2CamNoControl						BFCamNoControl
#define R2CamTypeLineScan					BFCamTypeLineScan	// R2CamTypeMask
#define R2CamTypeAreaScan					BFCamTypeAreaScan	
#define R2CamHasExposureControlOnly			BFCamHasExposureControlOnly	// R2CamControlTypeMask
#define R2CamHasRateControlOnly				BFCamHasRateControlOnly
#define R2CamHasIndpendentRateAndExposure	BFCamHasIndpendentRateAndExposure
#define R2CamHasDependentRateAndExposure	BFCamHasDependentRateAndExposure
#define R2CamTypeNumberOfTypes				BFCamTypeNumberOfTypes
#define R2CamHasNumberOfHases				BFCamHasNumberOfHases

// Priorities for set exposure/rate functions

#define R2CamExposurePriority				BFCamExposurePriority
#define R2CamRatePriority					BFCamRatePriority
#define R2CamFailOnNotExact					BFCamFailOnNotExact
#define R2CamExposureUnimportant			BFCamExposureUnimportant
#define R2CamRateUnimportant				BFCamRateUnimportant


// non-error return values from signal wait functions

#define R2_SIGNAL_TIMEOUT					BF_SIGNAL_TIMEOUT
#define R2_SIGNAL_CANCEL					BF_SIGNAL_CANCEL

// tranlsation of BF error returns into old R2 error returns.
// THis is for backwards compatiblity

#define R2_BAD_SEMAPHORE					BF_BAD_SEMAPHORE
#define R2_BAD_SIGNAL						BF_BAD_SIGNAL
#define R2_WAIT_FAILED						BF_WAIT_FAILED

// Sizes of various memory chunks

#define R28BITLUTSIZE						0x100
#define R212BITLUTSIZE						0x1000
#define R216BITLUTSIZE						0x10000
#define R2NUMLUTBANKS						2
#define R2HCTABSIZE							(8*1024)
#define R2VCTABSIZE							(32*1024)
#define R2QTABSIZE							(32*1024)			// table size in 32bit words.
#define R2QTABBANKSIZE						(R2QTABSIZE / 2)    // There are two equal size QTab banks. 
#define R2NUMCTABCOLS						16
#define R2HCTABJUMP							0x800
#define R2VCTABJUMP							0x1000


// QTAB creation options

#define R2DMAOptEOC							BFDMAOptEOC
#define R2DMAOptInt							BFDMAOptInt
#define R2DMADataMem						BFDMADataMem
#define R2DMABitmap							BFDMABitmap
#define R2DMAPhysical						BFDMAPhysical

// interrupt types

#define R2IntTypeAll						BFIntTypeAll
#define R2IntTypeHW							BFIntTypeHW
#define R2IntTypeFIFO						BFIntTypeFIFO
#define R2IntTypeDMADone					BFIntTypeDMADone
#define R2IntTypeEOD						BFIntTypeEOD
#define R2IntTypeDMAOnly					BFIntTypeDMAOnly
#define R2IntTypeCTab						BFIntTypeCTab
#define R2IntTypeSerial						BFIntTypeSerial
#define R2IntTypeTrig						BFIntTypeTrig

// compatibility

#define R2IntTypeQuadDone					R2IntTypeEOD

// trigger edges
					
#define R2TrigAssert						BFTrigAssert
#define R2TrigDeassert						BFTrigDeassert

/*
* Structures
*/ 

// structured used to report found in system
typedef BFENTRY R2ENTRY, *PR2ENTRY;

#if !defined(KernelOS)

typedef BFSIGNAL R2SIGNAL, *PR2SIGNAL;

#endif // KernelOS

#endif //__R2BOARD__
