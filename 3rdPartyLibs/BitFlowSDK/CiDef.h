/***************************************************************************
*
* CiType.h
*
* Generic camera interface API
* 
* Types and defines for Ci library
*
* Copyright (C) 1998 by BitFlow, Inc.  All Rights Reserved.
*
* 04/21/98	rjd		created
*
***************************************************************************/

#if !defined(__CITYPE__)
    #define __CITYPE__

#include "BFDef.h"
#include "R2TabError.h"
#include "RvTabError.h"
#include "R64TabError.h"


/*
* DEFINES
*/

/*
* Everything is ok
*/

#define CI_OK							0x00000000		// Everything is happy

/*
* Error types. These are not the normal
* R2 or RV error types, which are put in the
* error stack. These are high level errors
* which result from not being able to 
* communicate with the board libraries
*/

#define CISYS_ERROR_SYSTEM				0x10000000		// Error talking to registry
#define CISYS_ERROR_NOTFOUND			0x10000001		// This number board of this type does not exist
#define CISYS_ERROR_NOTSUPPORTED		0x10000002		// The function call is not supported by the board type.
#define CISYS_ERROR_UNKNOWN_TYPE		0x10000003		// this board type is unkown
#define CISYS_ERROR_BAD_ENTRY			0x10000004		// board entry structure is bad
#define CISYS_ERROR_OPENING				0x10000005		// error opening the board
#define CISYS_ERROR_BAD_BOARDPTR		0x10000006		// Bd structure is unkown
#define CISYS_ERROR_UNKNOWN_PARAMETER	0x10000007		// Ci parameter does not translate to board paramter
#define CISYS_ERROR_BAD_REGID			0x10000008		// Register ID index passed to regiter function is too big
#define CISYS_ERROR_UNKNOWN_TAPS		0x10000009		// Unable to determine the number of taps
#define CISYS_ERROR_ZERO_TAPS			0x1000000A		// There are no active channels
#define CISYS_ERROR_TIMEOUT				0x1000000B		// The function timed out.

/*
* Board Types
*/

#define CISYS_TYPE_R2					FF_ROADRUNNER		// RoadRunner
#define CISYS_TYPE_RV					FF_RAVEN			// Raven
#define CISYS_TYPE_R64					FF_R64				// R64
#define CISYS_TYPE_ANY					FF_BITFLOW_MODERN	// Opens board based on board number, ignoring board type
#define CISYS_TYPE_TOTAL				0x00000003			// total number of board types
#define CISYS_TYPE_MASK					0x0000ffff			// model info only

/*
* version
*/

#define CI_SDK_VERSION_MAJOR			BF_SDK_VERSION_MAJOR
#define CI_SDK_VERSION_MINOR			BF_SDK_VERSION_MINOR

/*
*  TYPES
*/

typedef BFSIGNAL CiSIGNAL,*PCiSIGNAL;

// LUT Mode Types

typedef enum _CiLutMode
{
    CiLut8Bit = BFLut8Bit, 
    CiLut12Bit = BFLut12Bit,
    CiLut16Bit = BFLut16Bit,
	CiLutSkip = BFLutSkip
} CiLutMode, *CiLutModePtr;

// LUT Bank Types

typedef enum _CiLutBank
{
    CiLutBank0 = BFLutBank0,
    CiLutBank1 = BFLutBank1,
    CiLutBank2 = BFLutBank2,
    CiLutBank3 = BFLutBank3,
	CiLutBypass = BFLutBypass
} CiLutBank, *CiLutBankPtr;

// LUT Lane Types

typedef enum _CiLutLane
{
    CiLutLane0      = BFLutLane0,
    CiLutLane1      = BFLutLane1,
    CiLutLane2      = BFLutLane2,
    CiLutLane3      = BFLutLane3,
    CiLutTwoLanes   = BFLutTwoLanes,
    CiLutFourLanes  = BFLutFourLanes
} CiLutLane, *CiLutLanePtr;

// QTab on-board banks.

typedef enum _CiQTabBank
{
    CiQTabBank0 = BFQTabBank0,
    CiQTabBank1 = BFQTabBank1,
    CiQTabBank2 = BFQTabBank2,
    CiQTabBank3 = BFQTabBank3
} CiQTabBank, *CiQTabBankPtr;

// Software Trigger Selectors

typedef enum _CiTrigSelect
{
    CiTrigA = BFTrigA,					// Select trigger A.
    CiTrigB = BFTrigB					// Select trigger B. 
} CiTrigSelect, *CiTrigSelectPtr;

// These are hack for now

#define CiConWait						BFConWait
#define CiConAsync						BFConAsync

#define CiConFreeze						BFConFreeze
#define CiConAbort						BFConAbort
#define CiConSnap						BFConSnap
#define CiConGrab						BFConGrab
#define CiConReset						BFConReset

// board open mode options

#define CiSysInitialize					BFSysInitialize			// initialize system 
#define CiSysExclusive					BFSysExclusive			// open only if no else has, and no subsequent opens
#define CiSysNoIntThread				BFSysNoIntThread		// do not start interrupt IRP thread
#define CiSysNoCameraOpen				BFSysNoCameraOpen		// do not open any configured cameras
#define CiSysNoAlreadyOpenMess			BFSysNoAlreadyOpenMess	// no already open message (suppress only the warning)
#define CiSysNoOpenErrorMess			BFSysNoOpenErrorMess	// suppress all dialogs in open function


// parameters for CiBrdInquire()

#define CiBrdInqModel					BFBrdInqModel
#define CiBrdInqSpeed					BFBrdInqSpeed
#define CiBrdInqLUT						BFBrdInqLUT
#define CiBrdInqIDReg					BFBrdInqIDReg
#define CiBrdInqNumCams					BFBrdInqNumCams
#define CiBrdAttachedCamera0FileName	BFBrdAttachedCamera0FileName
#define CiBrdInqScanType				BFBrdInqScanType
#define CiBrdInqColorDecoder			BFBrdInqColorDecoder
#define CiBrdInqAnalogType				BFBrdInqAnalogType

// paramenters for CiCamInquire() can also be passed to CiBrdInquire to inquire of current camera

#define CiCamInqMask					BFCamInqMask // used to pass member to camera function
#define CiCamInqXSize					BFCamInqXSize
#define CiCamInqYSize0					BFCamInqYSize0
#define CiCamInqFormat					BFCamInqFormat
#define CiCamInqPixBitDepth				BFCamInqPixBitDepth
#define CiCamInqBytesPerPix				BFCamInqBytesPerPix
#define CiCamInqAqTimeout				BFCamInqAqTimeout
#define CiCamInqFrameSize0				BFCamInqFrameSize0
#define CiCamInqDisplayFrameSize0		BFCamInqDisplayFrameSize0
#define CiCamInqFrameWidth				BFCamInqFrameWidth
#define CiCamInqDisplayFrameWidth		BFCamInqDisplayFrameWidth
#define CiCamInqPixBitDepthDisplay		BFCamInqPixBitDepthDisplay
#define CiCamInqBytesPerPixDisplay		BFCamInqBytesPerPixDisplay
#define CiCamInqBitsPerSequence			BFCamInqBitsPerSequence
#define CiCamInqBitsPerSequenceDisplay	BFCamInqBitsPerSequenceDisplay
#define CiCamInqHasCamControl			BFCamInqHasCamControl
#define CiCamInqCamType					BFCamInqCamType
#define CiCamInqControlType				BFCamInqControlType
#define CiCamInqYSize1					BFCamInqYSize1
#define CiCamInqYSize2					BFCamInqYSize2
#define CiCamInqYSize3					BFCamInqYSize3
#define CiCamInqFrameSize1				BFCamInqFrameSize1
#define CiCamInqFrameSize2				BFCamInqFrameSize2
#define CiCamInqFrameSize3				BFCamInqFrameSize3

// general endable/disable flags

#define CiConDisable					BFConDisable
#define CiConEnable						BFConEnable

// dma commands

#define CiConDMAGo						BFConDMAGo
#define CiConDMAAbort					BFConDMAAbort
#define	CiConDMAReset					BFConDMAReset

// QTAB Modes			
			
#define	CiQTabModeOneBank				RvQTabModeOneBank
#define	CiQTabModeTwoBanks				RvQTabModeTwoBanks
#define	CiQTabModeFourBanks				RvQTabModeFourBanks
									
// Trigger Modes

#define CiTrigFreeRun					BFTrigFreeRun
#define CiTrigOneShot					BFTrigOneShot
#define CiTrigAqCmd						BFTrigAqCmd
#define CiTrigAqCmdStartStop			BFTrigAqCmdStartStop
#define CiTrigContinuousData			BFTrigContinuousData
#define CiTrigOneShotSelfTriggered		BFTrigOneShotSelfTriggered
#define CiTrigOneShotStartAStopB		BFTrigOneShotStartAStopB
#define CiTrigOneShotStartAStopA		BFTrigOneShotStartAStopA
#define CiTrigModeUnknown				BFTrigModeUnknown
#define CiTrigSnapQualified				BFTrigSnapQualified
#define CiTrigContinuousDataQualified	BFTrigContinuousDataQualified
#define CiTrigOneShotStartAStopALevel	BFTrigOneShotStartAStopALevel	
#define CiTrigNTGOneShot				BFTrigNTGOneShot
#define CiTrigTriggeredGrab				BFTrigTriggeredGrab

// Polarity

#define CiTrigAssertedHigh				BFTrigAssertedHigh
#define CiTrigAssertedLow				BFTrigAssertedLow


// trigger edges	
				
#define CiTrigAssert					BFTrigAssert
#define CiTrigDeassert					BFTrigDeassert

// external trigger modes
			
#define CiExTrigConnect					BFExTrigConnect
#define CiExTrigDisconnect				BFExTrigDisconnect

// trigger status

#define CiTrigHigh						BFTrigHigh
#define CiTrigLow						BFTrigLow

// Encoder modes

#define CiEncFreeRun				BFEncFreeRun
#define CiEncOneShot				BFEncOneShot
#define CiEncOneShotSelfTriggered	BFEncOneShotSelfTriggered
#define CiEncModeUnknown			BFEncModeUnknown

// Encoder Polarity

#define CiEncAssertedHigh		BFEncAssertedHigh
#define CiEncAssertedLow		BFEncAssertedLow

// Encoder Selections

#define CiEncDiff				BFEncDiff
#define CiEncTTL				BFEncTTL
#define CiEncOpto				BFEncOpto
#define CiEncAlt				BFEncAlt
#define CiEncA					BFEncA
#define CiEncAlt1				BFEncAlt1
#define CiEncAlt2				BFEncAlt2
#define CiEncAlt3				BFEncAlt3
#define CiEncUnknown			BFEncUnknown


// Horizontal trigger modes for encoders 1-3

#define CiTrigSeparate					BFTrigSeparate
#define CiTrigAllFrom0					BFTrigAllFrom0


//  KEngineTrigger 

#define CiTrigJandKSameSource			BFTrigJandKSameSource
#define CiTrigJbyAandKbyB				BFTrigJbyAandKbyB
#define CiTrigJbyAandKFreerun			BFTrigJbyAandKFreerun


// Sizes of various memory chunks

#define CI8BITLUTSIZE					0xffffffff
#define CI12BITLUTSIZE					0xfffffffe
#define CI16BITLUTSIZE					0xfffffffd
#define CINUMLUTBANKS					0xfffffffc
#define CIQTABBANKSIZE					0xfffffffb
#define CIHCTABSIZE						0xfffffffa
#define CIVCTABSIZE						0xfffffff9
#define CIQTABSIZE						0xfffffff8		// this is entries, table is 128k bytes, or 8K quads
#define CIQTABBANKSIZE_1				0xfffffff7		// size of bank in one bank mode
#define CIQTABBANKSIZE_2				0xfffffff6		// size of bank in two bank mode
#define CIQTABBANKSIZE_4				0xfffffff5		// size of bank in four bank mode
#define CIQTABBANKSTART1_2				0xfffffff4		// start of bank one in two bank mode
#define CIQTABBANKSTART1_4				0xfffffff3		// start of bank one in four bank mode
#define CIQTABBANKSTART2_4				0xfffffff2		// start of bank two in four bank mode
#define CIQTABBANKSTART3_4				0xfffffff1		// start of bank three in four bank mode
#define CINUMCTABCOLS					0xfffffff0

// QTAB creation options

#define CiDMAOptEOC						BFDMAOptEOC
#define CiDMAOptInt						BFDMAOptInt
#define CiDMADataMem					BFDMADataMem
#define CiDMABitmap						BFDMABitmap
#define CiDMAOptFieldInt				BFDMAOptFieldInt

// camera open options

#define CiSysConfigure					0x0001

#define CiIgnore						BFIgnore

/*
* STRUCTURES
*/

// pointer to a found board to open
#ifdef GOING_AWAY

typedef struct _CiENTRY	
{
	BFENTRY R2Entry;
	BFENTRY RVEntry;
	BFENTRY R64Entry;
} CiENTRY, *PCiENTRY;

#else

#define CiENTRY BFENTRY
#define PCiENTRY PBFENTRY

#endif

#define CiIntTypeAll					BFIntTypeAll
#define CiIntTypeHW						BFIntTypeHW	
#define CiIntTypeFIFO					BFIntTypeFIFO
#define CiIntTypeDMADone				BFIntTypeDMADone
#define CiIntTypeEOD					BFIntTypeEOD
#define CiIntTypeCTab					BFIntTypeCTab
#define CiIntTypeDMAOnly				BFIntTypeDMAOnly
#define CiIntTypeCCUJ					BFIntTypeCCUJ
#define	CiIntTypeCCUK					BFIntTypeCCUK
#define CiIntTypeEOFDMAJ				BFIntTypeEOFDMAJ
#define	CiIntTypeEOFDMAK				BFIntTypeEOFDMAK
#define CiIntTypeTrig					BFIntTypeTrig
#define CiIntTypeSerial					BFIntTypeSerial

// for compability

#define CiIntTypeQuadDone				CiIntTypeEOD

#endif // __CITYPE__
