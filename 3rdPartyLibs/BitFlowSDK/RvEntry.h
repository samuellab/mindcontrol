/***************************************************************************
*
* RvEntry.h
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

#ifndef __RVENTRY__
#define __RVENTRY__

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
* 2. Only one BFCNFDATA_STRING is allowed and it must be at the end of the list
* 3. The IDs must be monotincally increasing
* 4. IDs that follow BFCNFDATA_LIST items must be greater than list ID + max # items in list
* 5. STRING and STRINGSZX cannot be modified with either LIST or PAIR
* 
*/

static BFCNFENTRY rventries[RVCNF_ENTRIES_TOTAL] = 
{
// ID					keyname				type												size				comment
RvEntRaven,				"RAVEN",		    BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// value must be camera
RvEntMake,				"MAKE",				BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// Manafacturer of camera			//NEEDWORK, must be bigger
RvEntModel,				"MODEL",			BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Model of camera					//NEEDWORK, must be bigger
RvEntMode,				"MODE",				BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Mode camera is in				//NEEDWORK, must be bigger
RvEntOwner,				"OWNER",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// origonal builder					//NEEDWORK, must be bigger
RvEntFileRev,			"REVISION",			BFCNFDATA_BFU32,									1,					// how many times been changed
RvEntModelComp,			"MODELCOMP",		BFCNFDATA_BFU32,									1,					// HW model compatibility value
RvEntRevComp,			"REVCOMP",			BFCNFDATA_BFU32,									1,					// HW revision compatibility value
RvEntAqTimeout,			"AQTIMEOUT",		BFCNFDATA_BFU32,									1,					// Acquistion timeout
RvEntFormat,			"FORMAT",			BFCNFDATA_BFU32,									1,					// Camera format
RvEntPixBitDepth,		"PIXBITDEPTH",		BFCNFDATA_BFU32,									1,					// Pixel depth
RvEntNumCameras,		"NUMCAMS",			BFCNFDATA_BFU32,									1,					// Number of cameras attached
RvEntXSize,				"XSIZE",			BFCNFDATA_BFU32,									1,					// X size
RvEntYSize0,			"YSIZE0",			BFCNFDATA_BFU32,									1,					// Y size for camera(s) on 0
RvEntYSize1,			"YSIZE1",			BFCNFDATA_BFU32,									1,					// Y size for camera(s) on 1
RvEntYSize2,			"YSIZE2",			BFCNFDATA_BFU32,									1,					// Y size for camera(s) on 2
RvEntYSize3,			"YSIZE3",			BFCNFDATA_BFU32,									1,					// Y size for camera(s) on 3
RvEntExpMod,			"EXPMOD",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Exposure model parameters
RvEntCon0,				"CON0"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon1,				"CON1"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon2,				"CON2"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon3,				"CON3"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon4,				"CON4"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon5,				"CON5"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon6,				"CON6"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon7,				"CON7"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon8,				"CON8"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon9,				"CON9"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon10,				"CON10"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon11,				"CON11"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon12,				"CON12"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon13,				"CON13"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon14,				"CON14"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon15,				"CON15"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon16,				"CON16"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon17,				"CON17"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon18,				"CON18"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon19,				"CON19"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon20,				"CON20"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon21,				"CON21"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon22,				"CON22"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon23,				"CON23"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon24,				"CON24"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon25,				"CON25"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon26,				"CON26"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon27,				"CON27"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon28,				"CON28"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon29,				"CON29"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon30,				"CON30"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon31,				"CON31"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon32,				"CON32"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon33,				"CON33"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon34,				"CON34"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon35,				"CON35"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon36,				"CON36"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon37,				"CON37"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon38,				"CON38"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon39,				"CON39"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon40,				"CON40"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon41,				"CON41"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon42,				"CON42"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon43,				"CON43"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon44,				"CON44"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntCon45,				"CON45"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntDMACh0Mode,		"DMA_CH0_MODE",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntDMACh1Mode,		"DMA_CH1_MODE",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntDMAArb0,			"DMA_ARB0",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntDMAArb1,			"DMA_ARB1",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
RvEntBtCmd0,			"BT_CMND0",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtCmd2,			"BT_CMND2",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtCmd3,			"BT_CMND3",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtCmd4,			"BT_CMND4",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtCmd5,			"BT_CMND5",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtCmd6,			"BT_CMND6",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtCmd7,			"BT_CMND7",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtBrightness,		"BT_BRIGHTNESS",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtContrast,		"BT_CONTRAST",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtSaturation,		"BT_SATURATION",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtHue,				"BT_HUE",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtHclock,			"BT_HCLOCK",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtHdelay,			"BT_HDELAY",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtActivepix,		"BT_ACTIVEPIX",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtVdelay,			"BT_VDELAY",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtActivelines,		"BT_ACTIVELINES",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtScfreq,			"BT_SCFREQ",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtAgcdelay,		"BT_AGCDELAY",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtBurstdelay,		"BT_BURSTDELAY",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtSamplerate,		"BT_SAMPLERATE",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntBtPolarity,		"BT_POLARITY",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Bt Register
RvEntQMod0,				"QTABMODEL0",		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFENT_QMOD_MAXE,	// QMOD for camera(s) on 0
RvEntQMod1,				"QTABMODEL1",		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFENT_QMOD_MAXE,	// QMOD for camera(s) on 1
RvEntQMod2,				"QTABMODEL2",		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFENT_QMOD_MAXE,	// QMOD for camera(s) on 2
RvEntQMod3,				"QTABMODEL3",		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFENT_QMOD_MAXE,	// QMOD for camera(s) on 3
RvEntComment,			"COMMENTS",			BFCNFDATA_STRING,									BFCNF_OWNER_MAXCOM,	// Commments
0,						"",					0,													0
};

#endif //__RVENTRY__
































