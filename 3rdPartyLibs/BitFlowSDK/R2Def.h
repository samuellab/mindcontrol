//
// Creation:    R2Def.h
// Created:     April 23, 1996
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// RoadRunner Public Definitions
//
// History:
//
// 04/23/96     rbs     Created file.
//

#if !defined(__R2DEF__)
#define __R2DEF__

#include "BFDef.h"

// Device specific hardware limits.

#define R2QTabChanMax			1			// Maximum number of QTab DMA channels supported by Raven boards.
#define R2QTabBankMax			2			// Maximum number of QTab banks supported by Raven boards.
#define R2QTabFieldMax			1			// Maximum number of QTab fields supported by Raven boards.
#define R2QTabEngineMax			1			// Maximum number of QTab acquire engines supported by Raven boards.

// sizes
#define R2CTAB_MAXADDR 32 * 1024
#define R2QTAB_MAXADDR 32 * 1024

// LUT Mode Types

typedef enum _R2LutMode
{
    R2Lut8Bit = BFLut8Bit, 
    R2Lut12Bit = BFLut12Bit,
    R2Lut16Bit = BFLut16Bit
} R2LutMode, *R2LutModePtr;

// LUT Bank Types

typedef enum _R2LutBank
{
    R2LutBank0 = BFLutBank0,
    R2LutBank1 = BFLutBank1,
	R2LutBypass = BFLutBypass
} R2LutBank, *R2LutBankPtr;

// LUT Lane Types

typedef enum _R2LutLane
{
    R2LutLane0      = BFLutLane0,
    R2LutLane1      = BFLutLane1,
    R2LutLane2      = BFLutLane2,
    R2LutLane3      = BFLutLane3,
    R2LutTwoLanes   = BFLutTwoLanes,
    R2LutFourLanes  = BFLutFourLanes
} R2LutLane, *R2LutLanePtr;

// QTab on-board banks.

typedef enum _R2QTabBank
{
    R2QTabBank0 = BFQTabBank0,
    R2QTabBank1 = BFQTabBank1
} R2QTabBank, *R2QTabBankPtr;

// Clock Frequency Modes

typedef enum _R2FreqMode
{
    R2Freq000 = 0,              // 00.0 Megahertz. 
    R2Freq025,                  // 02.5 Megahertz.
    R2Freq050,                  // 05.0 Megahertz.
    R2Freq075,                  // 07.5 Megahertz.
    R2Freq100,                  // 10.0 Megahertz.
    R2Freq150,                  // 15.0 Megahertz.
    R2Freq200,                  // 20.0 Megahertz.
    R2Freq300                   // 30.0 Megahertz.
} R2FreqMode, *R2FreqModePtr;

// Clock Control Modes

typedef enum _R2ClockMode
{
    R2ClockRaw = 0,             // Unmodified external clock.
    R2ClockDelay10 = 1,         // External clock delayed by 10 nanoseconds. 
    R2ClockDelay20 = 2,         // External clock delayed by 20 nanoseconds.
    R2ClockRawInv = 4,          // Inverted external clock.
    R2ClockDelay10Inv = 5,      // Inverted clock delayed by 10 nanoseconds.
    R2ClockDelay20Inv = 6,      // Inverted clock delayed by 20 nanoseconds.
    R2ClockInternal = 7         // Internal clock. 
} R2ClockMode, *R2ClockModePtr;

// General Purpose Output Pins

typedef enum _R2GPOutPin
{
    R2GPOut0    = 1,            // Pin 0.
    R2GPOut1    = 2,            // Pin 1.
    R2GPOut2    = 4             // Pin 2. 
} R2GPOutPin, *R2GPOutPinPtr;

// Acquisition Trigger Switch

typedef enum _R2TrigAqCmdSwitch
{
    R2TrigAqCmdOff = 0,         // Disable triggered command acquisition.
    R2TrigAqCmdOn               // Enable triggered command acquisition. 
} R2TrigAqCmdSwitch, *R2TrigAqCmdSwitchPtr;

// Software Trigger Selectors

typedef enum _R2TrigSelect
{
    R2TrigA = BFTrigA,                // Select trigger A.
    R2TrigB = BFTrigB                 // Select trigger B. 
} R2TrigSelect, *R2TrigSelectPtr;

// Trigger Control Modes

typedef enum _R2TrigConMode
{
    R2TrigRisingA = 0,
    R2TrigFallingA,
    R2TrigRisingAToB,
    R2TrigFallingAToB,
    R2TrigContinuous
} R2TrigConMode, *R2TrigConModePtr;

// Acquisition Control Modes

typedef enum _R2AqConMode
{
    R2AqFreeze = 0,
    R2AqAbort,
    R2AqSnap,
    R2AqGrab
} R2AqConMode, *R2AqConModePtr;

// Multiplexer Channels

typedef enum _R2MuxChannel
{
    R2ChanA = 0,
    R2ChanB,
    R2ChanC,
    R2ChanD
} R2MuxChannel, *R2MuxChannelPtr;

// Multiplexer Channel Packing Options

typedef enum _R2MuxPackOpt
{
    R2Disable,              // Channels: ABCD 
    R2Tap0000,              // Channels: ABC 
    R2Tap1111,              // Channels: ABD 
    R2Tap2222,              // Channels: CD 
    R2Tap3333,              // Channels: CD 
    R2Tap1010,              // Channels: AB 
    R2Tap3232,              // Channels: CD 
    R2Tap3210,              // Channels: ABCD 
    R2Tap10_10To8,          // Channels: AB 
    R2Tap10_12To8,          // Channels: AB 
    R2Tap10_14To8,          // Channels: AB 
    R2Tap32_10To8,          // Channels: CD 
    R2Tap32_12To8,          // Channels: CD 
    R2Tap32_14To8           // Channels: CD 
} R2MuxPackOpt, *R2MuxPackOptPtr;

// Timing Generator MUX Sample Rates

typedef enum _R2TG_Sample
{
    R2Sample8 = 0,          // Sample 8 bit MUX data at 1/4 the pixel rate into each 8 bit FIFO lane.
    R2Sample16,             // Sample 16 bit MUX data at 1/2 the pixel rate into two paired 8 bit FIFO lanes.
    R2Sample32,             // Sample 32 bit MUX data at the full pixel rate into all four 8 bit FIFO lanes.
    R2SampleHalf8           // Sample 8 bit MUX data at 1/8 the pixel rate into each 8 bit FIFO lane (1/2 zoom).

} R2TG_Sample, *R2TG_SamplePtr;

// Tap Mirror Switch

typedef enum _R2MirrorSwitch
{
    R2MirrorOn = 0,         // Disable triggered acquisition.
    R2MirrorOff             // Enable triggered acquisition. 
} R2MirrorSwitch, *R2MirrorSwitchPtr;

// Horizontal and Vertical Address Counter Control

typedef enum _R2CTabMode
{
    R2FreeRun = 0,          // Set HCount/VCount to run free. 
    R2OneShot               // Set HCount/VCount to wait for Encoder/Trigger. 
} R2CTabMode, *R2CTabModePtr;

// Horizontal And Vertical Control Table Masks

typedef enum _R2CTabControl
{
	R2CTab				= BFCTab,
	R2HCTab 			= BFHCTab,
	R2VCTab 			= BFVCTab,
	R2HCTabHStop		= BFHCTab0,
	R2HCTabHStart		= BFHCTab1,
	R2HCTabClamp		= BFHCTab2,
	R2HCTabField		= BFHCTab3,
	R2HCTabHStrobe		= BFHCTab4,
	R2HCTabHCon0		= BFHCTab5,
	R2HCTabHCon1		= BFHCTab6,
	R2HCTabHCon2		= BFHCTab7,
	R2VCTabVStop		= BFVCTab0,
	R2VCTabVLoad		= BFVCTab1,
	R2VCTabVStart		= BFVCTab2,
	R2VCTabIRQ			= BFVCTab3,
	R2VCTabVStrobe		= BFVCTab4,
	R2VCTabVCon0		= BFVCTab5,
	R2VCTabVCon1		= BFVCTab6,
	R2VCTabVCon2		= BFVCTab7
} R2CTabControl, *R2CTabControlPtr;

// define values to match CamVert and HW Manual
#define R2VCTabVEnd R2VCTabVStop
#define R2HCTabHEnd R2HCTabHStop

typedef enum _R2CTabLoadPoint
{
	R2HLoad = 0x800,
	R2VLoad = 0x1000
} R2CTabLoadPoint, *R2CTabLoadPointPtr;

typedef enum _R2CTabValue
{
    R2CTabClear = 0x0000,
    R2CTabSet   = 0xffff
} R2CTabValue, *R2CTabValuePtr;

#define R2GPOutAll	(BFGPOut0 | BFGPOut1 | BFGPOut2)
#define R2CLGPOutAll (BFGPOut0 | BFGPOut1 | BFGPOut2 | BFGPOut3 | BFGPOut4 | BFGPOut5)

#endif

