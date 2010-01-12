//
// Creation:    RvDef.h
// Created:     April 23, 1996
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// Raven Public Definitions
//
// History:
//
// 04/23/96     rbs     Created file.
//

#if !defined(__RVDEF__)
#define __RVDEF__

#include "BFDef.h"

// Device specific hardware limits.

#define RvQTabChanMax			2			// Maximum number of QTab DMA channels supported by Raven boards.
#define RvQTabBankMax			4			// Maximum number of QTab banks supported by Raven boards.
#define RvQTabFieldMax			2			// Maximum number of QTab fields supported by Raven boards.
#define RvQTabEngineMax			4			// Maximum number of QTab acquire engines supported by Raven boards.

// sizes
#define RVQTAB_MAXADDR 32 * 1024


// LUT Bank Types

typedef enum _RvLutBank
{
    RvLutBank0 = BFLutBank0,
    RvLutBank1 = BFLutBank1,
    RvLutBank2 = BFLutBank2,
    RvLutBank3 = BFLutBank3,
	RvLutBypass = BFLutBypass
} RvLutBank, *RvLutBankPtr;

// LUT Lane Types

typedef enum _RvLutLane
{
    RvLutLane0      = BFLutLane0,
    RvLutLane1      = BFLutLane1,
    RvLutLane2      = BFLutLane2,
    RvLutLane3      = BFLutLane3,
    RvLutFourLanes  = BFLutFourLanes
} RvLutLane, *RvLutLanePtr;

// QTab on-board banks.

typedef enum _RvQTabBank
{
    RvQTabBank0 = BFQTabBank0,
    RvQTabBank1 = BFQTabBank1,
    RvQTabBank2 = BFQTabBank2,
    RvQTabBank3 = BFQTabBank3
} RvQTabBank, *RvQTabBankPtr;

// Software Trigger Selectors

typedef enum _RvTrigSelect
{
    RvTrigA = BFTrigA,                // Select trigger A.
    RvTrigB = BFTrigB                 // Select trigger B. 
} RvTrigSelect, *RvTrigSelectPtr;

#define RvGPOutAll (BFGPOut0 | BFGPOut1 | BFGPOut2 | BFGPOut3 | BFGPOut4 | BFGPOut5)

#endif

