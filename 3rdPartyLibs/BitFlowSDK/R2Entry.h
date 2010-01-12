/***************************************************************************
*
* r2entry.h
*
* Defines the format for text and binary camera configuration files
*
* This is a source file; it is NOT considered part of the API.
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* 05/13/96	rjd		creation
*
***************************************************************************/

#ifndef __R2ENTRY__
#define __R2ENTRY__

/*
* This structure array describes a data structure.  Each element in the
* array corresponds to one key or item.  It can exist in one of three
* forms:
* 1. Text file or buffer
* 2. Data structure in memory
* 3. Binary file or buffer
* A standard set of routines are use to translate between the three forms.
* There are four basic types of keys:
* 1. BFCNFDATA_BFU16 - 16 bit unsigned integer
* 2. BFCNFDATA_BFU32 - 32 bit unsigned integer
* 3. BFCNFDATA_STRINGSZX - A string of fixed lenght (can be smaller with zero padding)
* 4. BFCNFDATA_STRING - A string of unlimited length
* Each of these can be modified by the following:
* 1. BFCNFDATA_PAIR - two identical type items on same line speperated by space(s)
* 2. BFCNFDATA_LIST - items of same type repeat up to size number of elements
*
* RULES:
* 1. Last entry must have ID = 0.
* 2. Only on BFCNFDATA_STRING is allowed and it must be at the end of the list
* 3. The IDs must be monotincally increasing
* 4. IDs that follow BFCNFDATA_LIST items must be greater than list ID + max # items in list
* 5. STRING and STRINGSZX cannot be modified with either LIST or PAIR
* 
*/

typedef BFCNFENTRY BFCNFENTRY; // make specific for R2

static BFCNFENTRY r2entries[R2CNF_ENTRIES_TOTAL] = 
{
// ID					keyname				type												size				comment
R2EntRoadRunner,		"ROADRUNNER",		BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// value must be camera
R2EntName,				"NAME",				BFCNFDATA_STRINGSZX,								BFCNF_NAME_MAXC,	// name of camera
R2EntOwner,				"OWNER",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// origonal builder
R2EntFileRev,			"REVISION",			BFCNFDATA_BFU32,									1,					// how many times been changed
R2EntModelComp,			"MODELCOMP",		BFCNFDATA_BFU32,									1,					// HW model compatibility value
R2EntRevComp,			"REVCOMP",			BFCNFDATA_BFU32,									1,					// HW revision compatibility value
R2EntAqTimeout,			"AQTIMEOUT",		BFCNFDATA_BFU32,									1,					// Acquistion timeout
R2EntFormat,			"FORMAT",			BFCNFDATA_BFU32,									1,					// Camera format
R2EntPixBitDepth,		"PIXBITDEPTH",		BFCNFDATA_BFU32,									1,					// Pixel depth
R2EntXSize,				"XSIZE",			BFCNFDATA_BFU32,									1,					// X size
R2EntYSize,				"YSIZE",			BFCNFDATA_BFU32,									1,					// Y size
R2EntExpMod,			"EXPMOD",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Exposure model parameters
R2EntDispCon0,			"DISPCON0",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Con0 settings for DMA to bitmap
R2EntCon0,				"CON0"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon1,				"CON1"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon2,				"CON2"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon3,				"CON3"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon4,				"CON4"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon5,				"CON5"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon6,				"CON6"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon7,				"CON7"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon8,				"CON8"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon9,				"CON9"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon10,				"CON10"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCon11,				"CON11"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntDMACh0Mode,		"DMA_CH0_MODE",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntDMACh1Mode,		"DMA_CH1_MODE",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntDMAArb0,			"DMA_ARB0",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntDMAArb1,			"DMA_ARB1",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2EntCTab,				"CTAB"	,			BFCNFDATA_BFU16|BFCNFDATA_LIST|BFCNFDATA_PAIR,		R2ENT_CTAB_MAXE,	// CTAB
R2EntQMod,				"QTABMODEL"	,		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFENT_QMOD_MAXE,	// QMOD
R2EntComment,			"COMMENTS",			BFCNFDATA_STRING,									BFCNF_OWNER_MAXCOM,	// Commments
0,						"",					0,													0
};

#endif //__R2ENTRY__
































