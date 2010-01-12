//
// Creation:    RvTabConfig.h
// Created:     October 1, 1999
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// Raven Device Configuration Definitons
//
// History:
//
// 10/01/99     rbs     Created file.
//

#if !defined(__RVTABCONFIG__)
#define __RVTABCONFIG__

#include "RvType.h"

// Device IDs

// Raven Family

#define BF_PCI_RV				0x1000			// Raven Device ID

// BitFlow Raven Options

#define BF_PCI_RV_VSCAN			0x0400			// Variable scan support.
#define BF_PCI_RV_NTSC			0x0200			// NTSC Brooktree chip mounted.  
#define BF_PCI_RV_DIFF			0x0100 			// Differential analog inputs.
#define BF_PCI_RV_ADC			0x00f0			// Raven A/D converters.
#define BF_PCI_RV_CHANNELS		0x000f			// Raven channels.
#define BF_PCI_RV_40MHZ			0x0100			// 40 MHz receivers.
#define BF_PCI_RV_MUX			0x00e0			// Mux type from 0 to 3 for 6K, 10K30, 10K50 and 10K100 sized FPGAs. 
#define BF_PCI_RV_SRAMS			0x0018			// Number of SRAMs from 0 to 2.
#define BF_PCI_RV_PLL			0x0004			// Non-standard size PLL FPGA mounted.
#define BF_PCI_RV_LBC			0x0002			// Non-standard size LBC FPGA mounted.
#define	BF_PCI_RV_CCU			0x0001			// Non-standard size CCU FPGA mounted.
 
//	Raven FPGA Types

typedef enum _RVMUX
{
	RVMUX2C = 0, 
	RVMUX4C3, 
	RVMUX4C5,
	RVMUX4C10
} RVMUX;
	 
// Raven Options Information Record.

typedef struct _RvOpsRec
{
	BFBOOL	VariableScan;						// True for variable scan. False for standard scan.
	BFBOOL	NTSC;								// True if BT chip mounted. False if BT not mounted.
	BFBOOL	Differential;						// True for differential. False for single ended.
	BFU32	ADConverters;						// Number of A/D converters.
	BFU32	Channels;							// Number of channels.
	BFBOOL	Speed40;							// True for 40 megahertz. False for normal.
	BFU32	SRAMS;								// Number of SRAMS loaded.
	RVMUX	MUXType;							// Set to RVMUX2C, RVMUX4C3, RVMUX4C5 or RVMUX4C10.
	BFBOOL	PLLType;							// Set False for Normal.
	BFBOOL	LBCType;							// Set False for Normal.
	BFBOOL	CCUType;							// Set False for Normal.
} RvOpsRec, *RvOpsPtr;

// Useful macro to pull the device specific options out of the VFO record.

#define GetRvOps(pVFO)	(pVFO == BFNULL || (pVFO->Family & FF_RAVEN) == 0 ? BFNULL : (RvOpsPtr)&pVFO->OpSpace[0])

#endif
