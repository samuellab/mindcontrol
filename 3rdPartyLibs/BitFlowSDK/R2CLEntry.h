/***************************************************************************
*
* R2CLEntry.h
*
* Defines the format for text and binary camera configuration files
*
* This is a source file; it is NOT considered part of the API.
*
* Copyright (C) 2000 by BitFlow, Inc.  All Rights Reserved.
*
* 11/01/00	rjd		creation
*
***************************************************************************/

#ifndef __R2CLENTRY__
#define __R2CLENTRY__

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

static BFCNFENTRY r2clentries[R2CLCNF_ENTRIES_TOTAL] = 
{
// ID					keyname				type												size				comment
R2CLEntRoadRunner,		"ROADRUNNER",		BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// value must be camera
R2CLEntMake,			"MAKE",				BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// Manafacturer of camera			//NEEDWORK, must be bigger
R2CLEntModel,			"MODEL",			BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Model of camera					//NEEDWORK, must be bigger
R2CLEntMode,			"MODE",				BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Mode camera is in				//NEEDWORK, must be bigger
R2CLEntOwner,			"OWNER",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// origonal builder
R2CLEntFileRev,			"REVISION",			BFCNFDATA_BFU32,									1,					// how many times been changed
R2CLEntModelComp,		"MODELCOMP",		BFCNFDATA_BFU32,									1,					// HW model compatibility value
R2CLEntRevComp,			"REVCOMP",			BFCNFDATA_BFU32,									1,					// HW revision compatibility value
R2CLEntAqTimeout,		"AQTIMEOUT",		BFCNFDATA_BFU32,									1,					// Acquistion timeout
R2CLEntFormat,			"FORMAT",			BFCNFDATA_BFU32,									1,					// Camera format
R2CLEntPixBitDepth,		"PIXBITDEPTH",		BFCNFDATA_BFU32,									1,					// Pixel depth
R2CLEntXSize,			"XSIZE",			BFCNFDATA_BFU32,									1,					// X size
R2CLEntYSize,			"YSIZE",			BFCNFDATA_BFU32,									1,					// Y size
R2CLEntExpMod,			"EXPMOD",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Exposure model parameters
R2CLEntDispCon0,		"DISPCON0",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Con0 settings for DMA to bitmap
R2CLEntCon0,			"CON0"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon1,			"CON1"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon2,			"CON2"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon3,			"CON3"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon4,			"CON4"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon5,			"CON5"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon6,			"CON6"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon7,			"CON7"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon8,			"CON8"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon9,			"CON9"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon10,			"CON10"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCon11,			"CON11"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntDMACh0Mode,		"DMA_CH0_MODE",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntDMACh1Mode,		"DMA_CH1_MODE",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntDMAArb0,			"DMA_ARB0",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntDMAArb1,			"DMA_ARB1",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R2CLEntCTab,			"CTAB"	,			BFCNFDATA_BFU16|BFCNFDATA_LIST|BFCNFDATA_PAIR,		R2ENT_CTAB_MAXE,	// CTAB
R2CLEntQMod,			"QTABMODEL"	,		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFENT_QMOD_MAXE,	// QMOD
R2CLEntComment,			"COMMENTS",			BFCNFDATA_STRING,									BFCNF_OWNER_MAXCOM,	// Commments
0,						"",					0,													0
};

#endif //__R2CLENTRY__
































