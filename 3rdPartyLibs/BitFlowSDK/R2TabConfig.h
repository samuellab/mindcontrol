//
// Creation:    R2TabConfig.h
// Created:     October 1, 1999
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// RoadRunner Device Configuration Definitons
//
// History:
//
// 10/01/99     rbs     Created file.
//

#if !defined(__R2TABCONFIG__)
#define __R2TABCONFIG__

#include "R2Type.h"

// Device IDs

// RoadRunner Family

#define BF_PCI_R2				0x0000			// RoadRunner Device ID

// BitFlow RoadRunner Options

#define BF_PCI_R2_CLINK			0x0800			// CameraLink RoadRunner. 
#define BF_PCI_R2_MODIFIED		0x0400			// RoadRunner with special modifications (model 12 that is really a model 11). 
#define BF_PCI_R2_40MHZ			0x0200			// 40 MHz receivers.
#define BF_PCI_R2_LUT16			0x0100			// 16 bit LUT.
#define BF_PCI_R2_CHANNELS		0x00f0			// RoadRunner channels.
#define BF_PCI_R2_TAPS			0x000f			// RoadRunner taps.
#define BF_PCI_R2_PMC			0x0001			// PMC RoadRunner.
#define BF_PCI_R2_VALID			0x8000			// SubVendorId information is valid.

// RoadRunner Options Information Record.

typedef struct _R2OpsRec
{
	BFBOOL	Speed40;							// True for 40 megahertz. False for normal.
	BFBOOL	HaveLuts;							// True if board has luts.
	BFBOOL	Lut16;								// True for 16 bit luts. False for 8/12 bit luts.
	BFU32	Channels;							// Number of channels.
	BFU32	Taps;								// Number of digital taps.
} R2OpsRec, *R2OpsPtr;

// Useful macro to pull the device specific options out of the VFO record.

#define GetR2Ops(pVFO)	(pVFO == BFNULL || (pVFO->Family & FF_ROADRUNNER) == 0 ? BFNULL : (R2OpsPtr)&pVFO->OpSpace[0])

#endif
