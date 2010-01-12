//
// Creation:    R64Board.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// R64 Board Definitions  
//
// History:
//
// 05/06/02     rbs     Created.
// 

#ifndef __R64BOARD__
#define __R64BOARD__ 

#include "BFSystem.h"
#include "BFDef.h"
#include "BFBoard.h"
#include "BFTabError.h"

// Sizes of various memory chunks.

#define R64HCTABSIZE						BFR64HCTABSIZE		// Number of horizontal CTab entries in CTab table.
#define R64VCTABSIZE						BFR64VCTABSIZE		// Number of vertical CTab entries in CTab table.
#define R64DPMSIZE							(128 * 1024)		// Size of the R64 DPM memory in bytes words. 
#define R64KBN2DDPMSIZE						(64 * 1024)			// Size of the Karbon 2 DPM memory in bytes words. 
#define R64KBN4DDPMSIZE						(64 * 1024)			// Size of the Karbon 4 DPM memory in bytes words. 	
#define R64KBN2FDPMSIZE						(128 * 1024)		// Size of the Karbon 2 DPM memory in bytes words. 
#define R64KBN4FDPMSIZE						(128 * 1024)		// Size of the Karbon 4 DPM memory in bytes words. 	

#define R64NEONDPMSIZE						(16 * 1024)			// Size of the Neon DPM memory in bytes words. 
#define R64ALTADPMSIZE						(16 * 1024)			// Size of the Alta DPM memory in bytes words. //NEEDSWORK, set actual size
#define R64NUMCTABCOLS						16
#define R64HCTABJUMP						0x2000
#define R64VCTABJUMP						0x8000
#define R64PCPHCI							0x08
#define R648BITLUTSIZE						0x100
#define R64NUMLUTBANKS						4
#define RLECTABHBASE						0					// location of first entry in horzonatal RLE CTABs
#define RLECTABVBASE						256					// location of first entry in vertical RLE CTABs
#define RLEHCTABSIZE						16					// number of entries in the horiztonal RLE CTab
#define RLEVCTABSIZE						16					// number of entries in the vertical RLE CTab
#define RLECTABRESETH						1 << 25				// bit in the Horiztonal RLE CTabs that causes a reset	
#define RLECTABRESETV						1 << 25				// bit in the Horiztonal RLE CTabs that causes a reset	

// Video Sources

typedef enum _VidSrc
{
	VidSrcCamera = 0,
	VidSrcCameraNoValid,
	VidSrcReserved,
	VidSrcHorizontalWedge,
	VidSrcDynamicWedge,
	VidSrc0x00,
	VidSrc0xff,
	VidSrc0xaa,
	VidSrc0x55,
	VidSrc0xabcdef0123456789,
	VidSrcVerticalWedge
} VidSrc;

// Structures

// Entry record for a BitFlow board found in the system.

typedef BFENTRY R64ENTRY, *PR64ENTRY;

// R64 interrupt signal.

#if !defined(KernelOS)

typedef BFSIGNAL R64SIGNAL, *PR64SIGNAL;

#endif

#endif
