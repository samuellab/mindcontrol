//
// Creation:    R64TabConfig.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// R64 Device Configuration Definitons
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__R64TABCONFIG__)
#define __R64TABCONFIG__

#include "R64Type.h"


// R64 Options 

//InfoLo
#define BF_PCI_R64_CL			0x0001			// CameraLink instead of differential.
#define BF_PCI_R64_256K_DPM		0x0002			// 256K DPM instead of 128K DPM.
#define BF_PCI_R64_FAST			0x0004			// High speed receivers.
#define BF_PCI_R64_PMC			0x0008			// PMC board.
#define BF_PCI_R64_FULL			0x0010			// Full CL instead of dual CL.
#define BF_PCI_R64_PLDA			0x0100			// Board has PLDA DMA Engine

// InfoHi
#define BF_PCI_R64_DCC_MASK		0x0038			// Custom DCC tag number bit mask. 
#define BF_PCI_R64_DCC_SHIFT	3				// Custom DCC tag number shift count. 
#define BF_PCI_R64_REV_MASK		0xf000			// Board revision bit mask.
#define BF_PCI_R64_REV_SHIFT	24				// Board revision shift count.
#define BF_PCI_R64_MUX_MASK		0x0007			// Custom MUX tag number bit mask.
#define BF_PCI_R64_MUX_SHIFT	0				// Custom MUX tag number shift count.


// Karbon/Neon Options 

// InfoLo
#define BF_PCI_KBN_INPUT_MASK	0x000f			// Input type bit mask
#define BF_PCI_KBN_INPUT_SHIFT	0x0000			// Input type shift count
#define BF_PCI_KBN_SLAVE		0x0010			// Set if configuration is a slave
#define BF_PCI_KBN_NO_DOWNLOAD	0x0020			// Set if board should not be downloaded

#define BF_PCI_KBN_INPUT_MAX_CL	0x0008			// The maximum value for the INPUT bits that indicate the input is CL

// InfoHi
#define BF_PCI_KBN_NUM_CFGS		0xF000			// Number of configuration spaces
#define BF_PCI_KBN_INFO_SRC		0x0010			// Source of INFOLO and INFOHI (1 = downloader, 0 = registry)
#define BF_PCI_KBN_IP_MASK		0x000f			// Custom MUX tag number bit mask.
#define BF_PCI_KBN_IP_SHIFT		0				// Custom MUX tag number shift count.

// SubVenderID

//  Options Information Record.

typedef struct _R64OpsRec
{
	BFBOOL	BigDPM;								// True for 256K DPM.
	BFBOOL	Fast;								// True for a fast board.
	BFBOOL	Full;								// True for a full CL board.
	BFBOOL	Slave;								// True for Slave VFGs on Karbon
	BFBOOL	NoDownload;							// True if board should not be downloaoded
	BFU32	MUX;								// MUX tag number.
	BFU32	DCC;								// DCC tag number.
} R64OpsRec, *R64OpsPtr;

// Useful macro to pull the device specific options out of the VFO record.

#define GetR64Ops(pVFO)	(pVFO == BFNULL || (pVFO->Family & FF_R64) == 0 ? BFNULL : (R64OpsPtr)&pVFO->OpSpace[0])

#endif
