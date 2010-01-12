/***************************************************************************
*
* RvBoard.h
*
* Public defines, parameters and structures.
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* 06/25/96	rjd		created
*
***************************************************************************/

#ifndef __RVBOARD__
#define __RVBOARD__ 

#include "BFSystem.h"
#include "BFDef.h"
#include "BFBoard.h"
#include "BFTabError.h"

// Error messages used during driver open phase.

#define RVSYS_ERROR						BFSYS_ERROR
#define RVSYS_ERROR_REGISTRY			BFSYS_ERROR_REGISTRY
#define RVSYS_ERROR_NOTFOUND			BFSYS_ERROR_NOTFOUND
#define RVSYS_ERROR_SIZE				BFSYS_ERROR_SIZE
#define RVSYS_ERROR_ALLOCACTION			BFSYS_ERROR_ALLOCACTION
#define RVSYS_ERROR_CREATEFILE			BFSYS_ERROR_CREATEFILE

// Board state.

#define RVSYS_STATUS_ALLOCATED			BFSYS_STATUS_ALLOCATED
#define	RVSYS_STATUS_HANDLEOPEN			BFSYS_STATUS_HANDLEOPEN
#define RVSYS_STATUS_CAMALLOC			BFSYS_STATUS_CAMALLOC
#define RVSYS_STATUS_BRDINIT			BFSYS_STATUS_BRDINIT
#define RVSYS_STATUS_MUTEXLIVES			BFSYS_STATUS_MUTEXLIVES

// Board open options.

#define RvSysInitialize					BFSysInitialize			// Initialize the system. 
#define RvSysExclusive					BFSysExclusive			// If not already open, open exclusively. 
#define RvSysNoIntThread				BFSysNoIntThread		// Do not activate interrupt thread.
#define RvSysNoCameraOpen				BFSysNoCameraOpen		// Do not open any camera configurations.
#define RvSysNoAlreadyOpenMess			BFSysNoAlreadyOpenMess	// Supress already open warning message.
#define RvSysNoOpenErrorMess			BFSysNoOpenErrorMess	// Supress error pop-ups in RvBrdOpen.

// Camera open options.

#define RvSysConfigure					BFSysConfigure

// Acquistion commands.

#define RvConFreeze						BFConFreeze
#define RvConAbort						BFConAbort
#define RvConSnap						BFConSnap
#define RvConGrab						BFConGrab
#define RvConReset						BFConReset
	
// General endable/disable flags.

#define RvConDisable					BFConDisable
#define RvConEnable						BFConEnable

// Acquisition modes.

#define RvConWait						BFConWait
#define RvConAsync						BFConAsync

// DMA commands.

#define RvConDMAGo						BFConDMAGo
#define RvConDMAAbort					BFConDMAAbort
#define	RvConDMAReset					BFConDMAReset

// parameters for RvBrdInquire()

#define RvBrdInqModel					BFBrdInqModel
#define RvBrdInqScanType				BFBrdInqScanType
#define RvBrdInqColorDecoder			BFBrdInqColorDecoder
#define RvBrdInqAnalogType				BFBrdInqAnalogType
#define RvBrdInqIDReg					BFBrdInqIDReg
#define RvBrdInqNumCams					BFBrdInqNumCams

// return values for RvBrdInquire() 
// RvBrdInqModel

#define RvBrdValUnkown					BFBrdValUnknown
#define RvBrdValModel010				BFBrdValModel010
#define RvBrdValModel110				BFBrdValModel110
#define RvBrdValModel220				BFBrdValModel220
#define RvBrdValModel330				BFBrdValModel330
#define RvBrdValModel440				BFBrdValModel440

// RvBrdInqScanType

#define RvBrdValVariable				BFBrdValVariable
#define RvBrdValStandard				BFBrdValStandard

// RvBrdInqColorDecoder

#define RvBrdValDecoderMounted			BFBrdValDecoderMounted
#define RvBrdValNoDecoder				BFBrdValNoDecoder

// RvBrdInqAnalogType

#define RvBrdValSingle					BFBrdValSingle
#define RvBrdValDifferential			BFBrdValDifferential

// parameters for RvCamInquire() can also be passed to RvBrdInquire to inquire of current camera

#define RvCamInqMask					BFCamInqMask // used to pass member to camera function
#define RvCamInqXSize					BFCamInqXSize
#define RvCamInqYSize0					BFCamInqYSize0
#define RvCamInqYSize1					BFCamInqYSize1
#define RvCamInqYSize2					BFCamInqYSize2
#define RvCamInqYSize3					BFCamInqYSize3
#define RvCamInqFormat					BFCamInqFormat
#define RvCamInqPixBitDepth				BFCamInqPixBitDepth
#define RvCamInqBytesPerPix				BFCamInqBytesPerPix
#define RvCamInqAqTimeout				BFCamInqAqTimeout
#define RvCamInqFrameSize0				BFCamInqFrameSize0
#define RvCamInqFrameSize1				BFCamInqFrameSize1
#define RvCamInqFrameSize2				BFCamInqFrameSize2
#define RvCamInqFrameSize3				BFCamInqFrameSize3
#define RvCamInqFrameWidth				BFCamInqFrameWidth
#define RvCamInqBitsPerSequence			BFCamInqBitsPerSequence
#define RvCamInqPixBitDepthDisplay		BFCamInqPixBitDepthDisplay
#define RvCamInqBytesPerPixDisplay		BFCamInqBytesPerPixDisplay
#define RvCamInqBitsPerSequenceDisplay	BFCamInqBitsPerSequenceDisplay
#define RvCamInqDisplayFrameSize0		BFCamInqDisplayFrameSize0
#define RvCamInqDisplayFrameWidth		BFCamInqDisplayFrameWidth

// QTAB Modes						
#define	RvQTabModeOneBank				0
#define	RvQTabModeTwoBanks				1
#define	RvQTabModeFourBanks				2
									
// modes

#define RvTrigFreeRun					BFTrigFreeRun
#define RvTrigOneShot					BFTrigOneShot
#define RvTrigOneShotStartStop			BFTrigOneShotStartAStopA
#define RvTrigAqCmd						BFTrigAqCmd
#define RvTrigAqCmdStartStop			BFTrigAqCmdStartStop
#define RvTrigContinuousData			BFTrigContinuousData
#define RvTrigModeUnkown				BFTrigModeUnknown
#define RvTrigOneShotSelfTriggered		BFTrigOneShotSelfTriggered

// Polarity

#define RvTrigAssertedHigh				BFTrigAssertedHigh
#define RvTrigAssertedLow				BFTrigAssertedLow

//  KEngineTrigger 

#define RvTrigJandKSameSource			BFTrigJandKSameSource
#define RvTrigJbyAandKbyB				BFTrigJbyAandKbyB
#define RvTrigJbyAandKFreerun			BFTrigJbyAandKFreerun

// Horizontal trigger modes for encoders 1-3

#define RvTrigSeparate					BFTrigSeparate
#define RvTrigAllFrom0					BFTrigAllFrom0

// trigger edges	
				
#define RvTrigAssert					BFTrigAssert
#define RvTrigDeassert					BFTrigDeassert

// external trigger modes	
		
#define RvExTrigConnect					BFExTrigConnect
#define RvExTrigDisconnect				BFExTrigDisconnect

// Sizes of various memory chunks.

#define RV8BITLUTSIZE					0x100
#define RVNUMLUTBANKS					4
#define RVHCTABSIZE						(8*1024)
#define RVVCTABSIZE						(32*1024)
#define RVQTABSIZE						(32*1024)					// this is entries, table is 128k bytes, or 8K quads
#define RVQTABBANKSIZE_1				(32*1024)					// size of bank in one bank mode
#define RVQTABBANKSIZE_2				(RVQTABBANKSIZE_1 / 2)		// size of bank in two bank mode
#define RVQTABBANKSIZE_4				(RVQTABBANKSIZE_1 / 4)		// size of bank in four bank mode
#define RVQTABBANKSTART1_2				(RVQTABBANKSIZE_2)			// start of bank one in two bank mode
#define RVQTABBANKSTART1_4				(RVQTABBANKSIZE_4)			// start of bank one in four bank mode
#define RVQTABBANKSTART2_4				(2 * RVQTABBANKSIZE_4)		// start of bank two in four bank mode
#define RVQTABBANKSTART3_4				(3 * RVQTABBANKSIZE_4)		// start of bank three in four bank mode

// QTAB creation options

#define RvDMAOptEOC						BFDMAOptEOC
#define RvDMAOptInt						BFDMAOptInt
#define RvDMAOptFieldInt				BFDMAOptFieldInt

// interrupt types

#define RvIntTypeAll					BFIntTypeAll
#define RvIntTypeHW						BFIntTypeHW
#define RvIntTypeFIFO					BFIntTypeFIFO
#define RvIntTypeDMADone				BFIntTypeDMADone
#define RvIntTypeEOD					BFIntTypeEOD
#define RvIntTypeCCUJ					BFIntTypeCCUJ
#define RvIntTypeCCUK					BFIntTypeCCUK
#define RvIntTypeDMAOnly				BFIntTypeDMAOnly
#define RvIntTypeEOFDMAJ				BFIntTypeEOFDMAJ
#define RvIntTypeEOFDMAK				BFIntTypeEOFDMAK

// compatibility

#define RvIntTypeQuadDone				RvIntTypeEOD

// unadvertised modes

#define RV_UNADDMODE_NOCOMBINEQUADS		BF_UNADDMODE_NOCOMBINEQUADS
#define RV_UNADDMODE_HOSTVGAGARBAGE		BF_UNADDMODE_HOSTVGAGARBAGE
#define RV_UNADDMODE_FASTQTABDOWNLOAD	BF_UNADDMODE_FASTQTABDOWNLOAD


#if !defined(KernelOS)

typedef BFSIGNAL RVSIGNAL, *PRVSIGNAL;

#endif // KernelOS


#endif //__RVBOARD__
