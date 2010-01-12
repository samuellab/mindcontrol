//
// Creation:    R64Def.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// R64 Public Definitions
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__R64DEF__)
#define __R64DEF__

#include "BFDef.h"

// Sizes

#define R64CTAB_MAXADDR		(128 * 1024)

// General Purpose Output Pins

typedef enum _R64GPOutPin
{
    R64GPOut0	= BFGPOut0,							// Pin 0.
    R64GPOut1	= BFGPOut1,							// Pin 1.
    R64GPOut2	= BFGPOut2,							// Pin 2. 
    R64GPOut3	= BFGPOut3,							// Pin 3.
    R64GPOut4	= BFGPOut4,							// Pin 4.
    R64GPOut5	= BFGPOut5,							// Pin 5. 
    R64GPOut6	= BFGPOut6							// Pin 6. 
} R64GPOutPin, *R64GPOutPinPtr;

#define R64GPOutAll	(R64GPOut0 | R64GPOut1 | R64GPOut2 | R64GPOut3 | R64GPOut4 | R64GPOut5 | R64GPOut6)

// Clock Frequency Modes

typedef enum _R64FreqMode
{
    R64Freq000 = 0,								// 00.0 Megahertz. 
    R64Freq037,									// 03.75 Megahertz.
    R64Freq075,									// 07.5 Megahertz.
    R64Freq150,									// 15.0 Megahertz.
    R64Freq240,									// 24.0 Megahertz.
    R64Freq300,									// 30.0 Megahertz.
    R64Freq480,									// 48.0 Megahertz.
    R64Freq600									// 60.0 Megahertz.
} R64FreqMode, *R64FreqModePtr;



// ctabs

typedef enum _R64CTabControl
{
    R64CTab				= BFCTab,
    R64HCTab			= BFHCTab,
    R64VCTab			= BFVCTab,
    R64HCTabHStart		= BFHCTab0,
    R64HCTabHReset		= BFHCTab1,
    R64HCTabENHLoad		= BFHCTab2,
    R64HCTabReserved	= BFHCTab3,
    R64HCTabGPH0		= BFHCTab4,
    R64HCTabGPH1		= BFHCTab5,
    R64HCTabGPH2		= BFHCTab6,
    R64HCTabGPH3		= BFHCTab7,
    R64VCTabVStart		= BFVCTab0,
    R64VCTabVReset		= BFVCTab1,
    R64VCTabENVLoad		= BFVCTab2,
    R64VCTabIRQ			= BFVCTab3,
    R64VCTabGPV0		= BFVCTab4, 
    R64VCTabGPV1		= BFVCTab5,
    R64VCTabGPV2		= BFVCTab6,
    R64VCTabGPV3		= BFVCTab7,
} R64CTabControl, *R64CTabControlPtr;

#endif

