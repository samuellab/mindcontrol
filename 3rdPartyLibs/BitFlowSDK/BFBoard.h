//
// Creation:    BFBoard.h
// Created:     August 19, 1999
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.  
//
// Description:
//
// BitFlow Driver Open and Close Definitions
//
// 08/19/99     rbs     Consolidated from R2Board.h & RvBoard.h.
//

#ifndef __BFBOARD__
#define __BFBOARD__ 

// Error messages used during driver open phase. 

#define BFSYS_ERROR							0x00010001
#define BFSYS_ERROR_REGISTRY				0x00010002										  
#define BFSYS_ERROR_NOTFOUND				0x00010003
#define BFSYS_ERROR_SIZE					0x00010004
#define BFSYS_ERROR_ALLOCACTION				0x00010005
#define BFSYS_ERROR_CREATEFILE				0x00010006
#define BFSYS_ERROR_NOTREADY				0x00010007

// Board state.

#define BFSYS_STATUS_ALLOCATED				0x00000001
#define	BFSYS_STATUS_HANDLEOPEN				0x00000002
#define BFSYS_STATUS_CAMALLOC				0x00000004
#define BFSYS_STATUS_BRDINIT				0x00000008
#define BFSYS_STATUS_MUTEXLIVES				0x00000010

// Board open options.

#define BFSysInitialize						0x00000001	// Initialize the system. 
#define BFSysExclusive						0x00000002	// If not already open, open exclusively. 
#define BFSysNoIntThread					0x00000004	// Do not activate interrupt thread.
#define BFSysNoCameraOpen					0x00000008	// Do not open any camera configurations.
#define BFSysNoAlreadyOpenMess				0x00000020	// Supress already open warning message.
#define BFSysNoOpenErrorMess				0x00000040	// Supress all error popups in open function
#define BFSysSecondProcessOpen				0x000000E8	// Allow the board to be opened twice in the same process (includes some of the above modes).
#define BFSysAllowTwoOpens					0x00000100  // Allow the board to be opened twic ein the same process, and initialized.

// Camera open options.

#define BFSysConfigure						1

// Acquistion commands.

#define BFConFreeze							0
#define BFConAbort							1
#define BFConSnap							2
#define BFConGrab							3
#define BFConReset							5

// General enable/disable flags.

#define BFConDisable						0
#define BFConEnable							1

// Acquisition modes.

#define BFConWait							1
#define BFConAsync							2

// DMA commands. 
//
// Note these start at offset 10 to catch bugs
// when confusing BFConAbort with BFConDMAAbort.

#define BFConDMAGo							10
#define BFConDMAAbort						11
#define	BFConDMAReset						12

// Interrupt enable/disable flags.

#define BFIntTypeAll						0x0000
#define BFIntTypeHW							0x0001
#define BFIntTypeFIFO						0x0002
#define BFIntTypeDMADone					0x0003
#define BFIntTypeEOD						0x0004
#define BFIntTypeCTab						0x0005
#define BFIntTypeCCUJ						0x0006
#define BFIntTypeCCUK						0x0007
#define BFIntTypeDMAOnly					0x0008
#define BFIntTypeEOFDMAJ					0x0009
#define BFIntTypeEOFDMAK					0x000a
#define BFIntTypeTrig						0x000b
#define BFIntTypeSerial						0x000c
#define BFIntTypeQL							0x000d
#define BFIntTypeOthers						0x000e
#define BFIntTypeEOF						0x000f

// Interrupt modes
#define BFIntModeDefault					0x0030	// Interrupts happen on the default schedule
#define BFIntModeEOFAq						0x0031	// EOF interrupts only during grab

// Maximum number of interrupt types for all boards. Note that this constant
// should always be set to a number larger than the last interrupt defined above.

#define BFIntCount							0x0020

// This is the size of the circular queue that holds interrupt status for every
// interrupt that occurs while processing interrupts. 

#define	BFIntQueueCount						16

// for compatiblity

#define BFIntTypeQuadDone					BFIntTypeEOD  	

// generic define for not changing a parameter value
#define BFIgnore							0xEF

// Trigger Modes

#define BFTrigFreeRun						0x0001
#define BFTrigOneShot						0x0002
#define BFTrigAqCmd							0x0003
#define BFTrigAqCmdStartStop				0x0004
#define BFTrigContinuousData				0x0005
#define BFTrigOneShotSelfTriggered			0x0006
#define BFTrigOneShotStartAStopB			0x0007
#define BFTrigOneShotStartAStopA			0x0008
#define BFTrigSnapQualified					0x0009
#define BFTrigContinuousDataQualified		0x000A
#define BFTrigOneShotStartAStopALevel		0x000B
#define BFTrigNTGOneShot					0x000C
#define BFTrigTriggeredGrab					0x000D
#define BFTrigModeUnknown					0x1000

// Triger Polarity

#define BFTrigAssertedHigh					0x000d
#define BFTrigAssertedLow					0x000e

// Trigger Selectsion

#define BFTrigDiff							0x0000
#define BFTrigTTL							0x0001
#define BFTrigOpto							0x0002
#define BFTrigAlt							0x0003

// Encoder Modes

#define BFEncFreeRun						0x0001
#define BFEncOneShot						0x0002
#define BFEncOneShotSelfTriggered			0x0003
#define BFEncNTGOneShot						0x0004
#define BFEncModeUnknown					0x1000

// Encoder Polarity

#define BFEncAssertedHigh					0x000d
#define BFEncAssertedLow					0x000e

// Encoder Selections

#define BFEncDiff							0x0000
#define BFEncTTL							0x0001
#define BFEncOpto							0x0002
#define BFEncAlt							0x0003
#define BFEncA								0x0004
#define BFEncAlt1							0x0005
#define BFEncAlt2							0x0006
#define BFEncAlt3							0x0007
#define BFEncUnknown						0x0008


//  KEngineTrigger 

#define BFTrigJandKSameSource				0x000a
#define BFTrigJbyAandKbyB					0x000b
#define BFTrigJbyAandKFreerun				0x000c


// Horizontal trigger modes for encoders 1-3

#define BFTrigSeparate						0x000f
#define BFTrigAllFrom0						0x0010

// trigger edges					

#define BFTrigAssert						0x0011
#define BFTrigDeassert						0x0012

// external trigger modes			

#define BFExTrigConnect						0x0013
#define BFExTrigDisconnect					0x0014

// trigger status

#define BFTrigHigh							0x0015
#define BFTrigLow							0x0016

// Camera brand info (used on EXPMOD first parameter) parameter

#define BFCamModelDalsaLineScanWithPRIN		0x00000001
#define BFCamModelNumberOfModels			1

// Camera control masks (used on EXPMOD second parameter) parameter

#define BFCamTypeMask						0x0000000f
#define BFCamControlTypeMask				0x000000f0

// Camera Control and exposure mode parameters

#define BFCamNoControl						0x00000000
#define BFCamTypeLineScan					0x00000001	// R2CamTypeMask
#define BFCamTypeAreaScan					0x00000002	
#define BFCamHasExposureControlOnly			0x00000010	// R2CamControlTypeMask
#define BFCamHasRateControlOnly				0x00000020
#define BFCamHasIndpendentRateAndExposure	0x00000030
#define BFCamHasDependentRateAndExposure	0x00000040
#define BFCamTypeNumberOfTypes				2
#define BFCamHasNumberOfHases				4

// Priorities for set exposure/rate functions

#define BFCamExposurePriority				0x00000000
#define BFCamRatePriority					0x00000001
#define BFCamFailOnNotExact					0x00000002
#define BFCamExposureUnimportant			0x00000003
#define BFCamRateUnimportant				0x00000004

// QTAB creation options

#define BFDMAOptEOC							0x0001
#define BFDMAOptInt							0x0002
#define BFDMADataMem						0x0003
#define BFDMABitmap							0x0004
#define BFDMAOptFieldInt					0x0005
#define BFDMAPhysical						0x0008 // keep as 8 in order to be or'ed

// parameters for XXBrdInquire()
enum _BRDINQ
{
	BFBrdInqModel = 0x0001,
	BFBrdInqSpeed,
	BFBrdInqLUT,						
	BFBrdInqIDReg,
	BFBrdInqNumCams,
	BFBrdAttachedCamera0FileName,
	BFBrdInqScanType,		
	BFBrdInqColorDecoder,
	BFBrdInqAnalogType,
	BFBrdInqDPMSize,
	BFBrdInqConnector,
};


// return values for XXBrdInquire() 
enum _BRDINQRETURN
{
// BFBrdInqModel
	BFBrdValUnknown = 0x1000,
	BFBrdValModel11,						
	BFBrdValModel12,					
	BFBrdValModel13,						
	BFBrdValModel14,					
	BFBrdValModel23,						
	BFBrdValModel24,						
	BFBrdValModel44,						
	BFBrdValModel010,					
	BFBrdValModel110,					
	BFBrdValModel220,					
	BFBrdValModel330,					
	BFBrdValModel440,					
	BFBrdValModelR64Dif,
	BFBrdValModelR64ClF,
	BFBrdValModelR64ClD,
	BFBrdValModelR64DifB,
	BFBrdValModelR64ClFB,				
	BFBrdValModelR64ClDB,				
	BFBrdValModelR64DifH,				
	BFBrdValModelR64ClFH,				
	BFBrdValModelR64ClDH,				
	BFBrdValModelR64DifHB,
	BFBrdValModelR64ClFHB,				
	BFBrdValModelR64ClDHB,				
	BFBrdValModelKbn2B,				
	BFBrdValModelKbn2F,					
	BFBrdValModelKbn4B,					
	BFBrdValModelKbn4F,		
	BFBrdValModelNeonB,
	BFBrdValModelNeonD,
	BFBrdValModelAltaAN1,
	BFBrdValModelAltaAN2,
	BFBrdValModelAltaAN4,
	BFBrdValModelAltaCO1,
	BFBrdValModelAltaCO2,
	BFBrdValModelAltaCO4,


// BFBrdInqLUT

	BFBrdValLUT8And12,
	BFBrdValLUT16,
	BFBrdValLUTNone,

// BFBrdInqSpeed

	BFBrdValSpeedNormalR2,				
	BFBrdValSpeed40MHzR2,				
	BFBrdValSpeedNormalR64,
	BFBrdValSpeed40MHzR64,				

// BFBrdInqScanType

	BFBrdValVariable,					
	BFBrdValStandard,					

// BFBrdInqColorDecoder

	BFBrdValDecoderMounted,				
	BFBrdValNoDecoder,					

// BFBrdInqAnalogType

	BFBrdValSingle,						
	BFBrdValDifferential,				

// BFBrdInqConnector
	BFBrdValCon0Or0and1,					
	BFBrdValCon1Or2and3,					
	BFBrdValCon2,						
	BFBrdValCon3,
};

// can't figure out answer to questions
#define BFBrdValUnknown						0xffffffff

// parameters for XXCamInquire() can also be passed 
// to XXBrdInquire to inquire of current camera

enum _CAMINQ
{
	BFCamInqMask = 0x00010000,
	BFCamInqXSize,						
	BFCamInqYSize0,						
	BFCamInqFormat,						
	BFCamInqPixBitDepth,
	BFCamInqBytesPerPix,
	BFCamInqAqTimeout,
	BFCamInqFrameSize0,					
	BFCamInqDisplayFrameSize0,
	BFCamInqFrameWidth,
	BFCamInqDisplayFrameWidth,
	BFCamInqPixBitDepthDisplay,
	BFCamInqBytesPerPixDisplay,
	BFCamInqBitsPerSequence,
	BFCamInqBitsPerSequenceDisplay,
	BFCamInqHasCamControl,
	BFCamInqCamType,
	BFCamInqControlType,
	BFCamInqYSize1,
	BFCamInqYSize2,
	BFCamInqYSize3,
	BFCamInqFrameSize1,
	BFCamInqFrameSize2,
	BFCamInqFrameSize3,
};

// NTG parameters

// output signals
#define BFNTGOutputCC1		0x0001
#define BFNTGOutputCC2		0x0002
#define BFNTGOutputCC3		0x0004
#define BFNTGOutputCC4		0x0008
#define BFNTGOutputGP0		0x0010
#define BFNTGOutputGP1		0x0020
#define BFNTGOutputGP2		0x0040
#define BFNTGOutputGP3		0x0080
#define BFNTGOutputGP4		0x0100
#define BFNTGOutputGP5		0x0200
#define BFNTGOutputGP6		0x0400

// trigger modes
enum _NTGMODE
{
	BFNTGModeFreeRun,
	BFNTGModeOneShotTrigger, 
	BFNTGModeOneShotEncoder
};

// NTG Limits Karbon/Neon
#define NTGPeriodFrameMaxKN		291271.1111		// maximum time in milliseconds when NTG time base is frame mode (based on 24 bit registers)
#define NTGPeriodLineMaxKN		2275.5556		// maximum time in milliseconds when NTG time base is line mode (based on 24 bit registers)
#define NTGBitPeriodCoarseKN	0.017361111		// amount of time (milliseconds) represented LSB when NTG time base is frame
#define NTGBitPeriodFineKN		0.000135634		// amount of time (milliseconds) represented LSB when NTG time base is line

// NTG Limits Alta
#define NTGPeriodFrameMaxAl		429496.704		// maximum time in milliseconds when NTG time base is frame mode (based on 24 bit registers)
#define NTGPeriodLineMaxAl		3355.443		// maximum time in milliseconds when NTG time base is line mode (based on 24 bit registers)
#define NTGBitPeriodCoarseAl	0.025600000		// amount of time (milliseconds) represented LSB when NTG time base is frame
#define NTGBitPeriodFineAl		0.000200000		// amount of time (milliseconds) represented LSB when NTG time base is line

// Encoder Divider stuff

enum _ENCDIV_CLK_SEL
{
	BFEncDiv50MHz = 0,
};

#endif

