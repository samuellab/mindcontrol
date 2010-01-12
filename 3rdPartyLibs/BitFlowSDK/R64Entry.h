/***************************************************************************
*
* R64entry.h
*
* Defines the format for text and binary camera configuration files
*
* This is a source file; it is NOT considered part of the API.
*
* Copyright (C) 2002 by BitFlow, Inc.  All Rights Reserved.
*
* 05/29/02	rbs		Cloned from R64Entry.h.
*
***************************************************************************/

#ifndef __R64ENTRY__
#define __R64ENTRY__

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

typedef BFCNFENTRY BFCNFENTRY; // make specific for R64

static BFCNFENTRY R64entries[R64CNF_ENTRIES_TOTAL] = 
{
// ID					keyname				type												size				comment
R64EntR64,				R64_TOKEN,			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// value must be camera
R64EntMake,				"MAKE",				BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// Manafacturer of camera			//NEEDWORK, must be bigger
R64EntModel,			"MODEL",			BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Model of camera					//NEEDWORK, must be bigger
R64EntMode,				"MODE",				BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Mode camera is in				//NEEDWORK, must be bigger
R64EntOwner,			"OWNER",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// origonal builder
R64EntFileRev,			"REVISION",			BFCNFDATA_BFU32,									1,					// how many times been changed
R64EntModelComp,		"MODELCOMP",		BFCNFDATA_BFU32,									1,					// HW model compatibility value
R64EntRevComp,			"REVCOMP",			BFCNFDATA_BFU32,									1,					// HW revision compatibility value
R64EntAqTimeout,		"AQTIMEOUT",		BFCNFDATA_BFU32,									1,					// Acquistion timeout
R64EntFormat,			"FORMAT",			BFCNFDATA_BFU32,									1,					// Camera format
R64EntFlashMux,			"FLASHMUX",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// required flash file for MUX
R64EntFlashDCC,			"FLASHDCC",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// required flash file for DCC
R64EntPixBitDepth,		"PIXBITDEPTH",		BFCNFDATA_BFU32,									1,					// Pixel depth
R64EntXSize,			"XSIZE",			BFCNFDATA_BFU32,									1,					// X size
R64EntYSize,			"YSIZE",			BFCNFDATA_BFU32,									1,					// Y size
R64EntExpMod,			"EXPMOD",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Exposure model parameters
R64EntCon0,				"CON0"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon1,				"CON1"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon2,				"CON2"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon3,				"CON3"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon4,				"CON4"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon5,				"CON5"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon6,				"CON6"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon7,				"CON7"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon8,				"CON8"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon9,				"CON9"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon10,			"CON10"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon11,			"CON11"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon12,			"CON12"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon13,			"CON13"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon14,			"CON14"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon15,			"CON15"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon16,			"CON16"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon17,			"CON17"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon18,			"CON18"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon19,			"CON19"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon20,			"CON20"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon21,			"CON21"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon22,			"CON22"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon23,			"CON23"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon24,			"CON24"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon25,			"CON25"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon26,			"CON26"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCon27,			"CON27"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
R64EntCTab,				"CTAB"	,			BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		R64ENT_CTAB_MAXE,	// CTAB
R64EntQMod,				"QTABMODEL"	,		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFENT_QMOD_MAXE,	// QMOD
R64EntComment,			"COMMENTS",			BFCNFDATA_STRING,									BFCNF_OWNER_MAXCOM,	// Commments
0,						"",					0,													0
};

static BFCNFENTRY AltaEntries[ALTACNF_ENTRIES_TOTAL] = 
{
// ID					keyname				type												size				comment
AltaEntAlta,			ALTA_TOKEN,			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// value must be camera
AltaEntMake,			"MAKE",				BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// Manafacturer of camera			//NEEDWORK, must be bigger
AltaEntModel,			"MODEL",			BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Model of camera					//NEEDWORK, must be bigger
AltaEntMode,			"MODE",				BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Mode camera is in				//NEEDWORK, must be bigger
AltaEntOwner,			"OWNER",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// origonal builder
AltaEntFileRev,			"REVISION",			BFCNFDATA_BFU32,									1,					// how many times been changed
AltaEntModelComp,		"MODELCOMP",		BFCNFDATA_BFU32,									1,					// HW model compatibility value
AltaEntRevComp,			"REVCOMP",			BFCNFDATA_BFU32,									1,					// HW revision compatibility value
AltaEntAqTimeout,		"AQTIMEOUT",		BFCNFDATA_BFU32,									1,					// Acquistion timeout
AltaEntFormat,			"FORMAT",			BFCNFDATA_BFU32,									1,					// Camera format
AltaEntFlashMux,		"FLASHMUX",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// required flash file for MUX
AltaEntPixBitDepth,		"PIXBITDEPTH",		BFCNFDATA_BFU32,									1,					// Pixel depth
AltaEntXSize,			"XSIZE",			BFCNFDATA_BFU32,									1,					// X size
AltaEntYSize,			"YSIZE",			BFCNFDATA_BFU32,									1,					// Y size
AltaEntExpMod,			"EXPMOD",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Exposure model parameters
AltaEntCon0,			"CON0"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon1,			"CON1"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon2,			"CON2"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon3,			"CON3"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon4,			"CON4"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon5,			"CON5"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon6,			"CON6"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon7,			"CON7"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon8,			"CON8"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon9,			"CON9"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon10,			"CON10"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon11,			"CON11"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon12,			"CON12"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon13,			"CON13"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon14,			"CON14"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon15,			"CON15"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon16,			"CON16"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon17,			"CON17"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon18,			"CON18"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon19,			"CON19"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon20,			"CON20"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon21,			"CON21"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon22,			"CON22"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon23,			"CON23"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon24,			"CON24"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon25,			"CON25"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon26,			"CON26"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon27,			"CON27"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon42,			"CON42"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon43,			"CON43"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon44,			"CON44"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon45,			"CON45"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon46,			"CON46"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon47,			"CON47"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon48,			"CON48"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon49,			"CON49"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCon50,			"CON50"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEDevID,				"AFE_DEVID",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFESyncStat,				"AFE_SYNC_STAT",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFESyncPol,				"AFE_SYNC_POL",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEHSyncSlicer,			"AFE_HSYNC_SLICER",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFESOGSlicer,			"AFE_SOG_SLICER",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEInCnf,				"AFE_IN_CNF",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFERedGain,				"AFE_RED_GAIN",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEGreenGain,			"AFE_GREEN_GAIN",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEBlueGain,	 			"AFE_BLUE_GAIN",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFERedOffs,	 			"AFE_RED_OFFS",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEGreenOffs,			"AFE_GREEN_OFFS",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEBlueOffs,				"AFE_BLUE_OFFS",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEOffsDACCnf,			"AFE_OFFS_DAC_CNF",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEBandwidth,			"AFE_BANDWIDTH",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntAFEPLLHTotalMSB,			"AFE_PLL_HTOTAL_MSB",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEPLLHTotalLSB,			"AFE_PLL_HTOTAL_LSB",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEPLLSamplePhase,		"AFE_PLL_SAMPLE_PHASE",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEPLLPrecoast,			"AFE_PLL_PRE_COAST",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEPLLPostcoast,			"AFE_PLL_POST_COAST",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEPLLMisc,	 			"AFE_PLL_MISC",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEDCRstrPisMSB,			"AFE_DC_RSTR_PIX_MSB",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEDCRstrPixLSB,			"AFE_DC_RSTR_PIX_LSB",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEDCRrstWidth,			"AFE_DC_RSTR_WIDTH",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEABLCCnf,	 			"AFE_ABLC_CNF",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEOutFormat,			"AFE_OUT_FORMAT",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEHSOutWidth,			"AFE_HSOUT_WIDTH",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEOutSigDisable,		"AFE_OUT_SIG_DISABLE",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEPowerCon,	 			"AFE_POWER_CON",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEPLLTuning,			"AFE_PLL_TUNING",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFERedABLC,	 			"AFE_RED_ABLC",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEGreenABLC,			"AFE_GREEN_ABLC",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEBlueABLC,	 			"AFE_BLUE_ABLC",		BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFEDCRstrClamp,			"AFE_DC_RSTR_CLAMP",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,					1,					// Register
AltaEntAFESyncSepCon,			"AFE_SYNC_SEP_CON",	BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaEntCTab,			"CTAB"	,			BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		R64ENT_CTAB_MAXE,	// CTAB
AltaEntQMod,			"QTABMODEL"	,		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFENT_QMOD_MAXE,	// QMOD
AltaEntComment,			"COMMENTS",			BFCNFDATA_STRING,									BFCNF_OWNER_MAXCOM,	// Commments
0,						"",					0,													0
};

static BFCNFENTRY AltaCOEntries[ALTACOCNF_ENTRIES_TOTAL] = 
{
// ID					keyname				type												size				comment
AltaCoEntAlta,			ALTACO_TOKEN,		BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// value must be camera
AltaCoEntMake,			"MAKE",				BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// Manafacturer of camera			//NEEDWORK, must be bigger
AltaCoEntModel,			"MODEL",			BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Model of camera					//NEEDWORK, must be bigger
AltaCoEntMode,			"MODE",				BFCNFDATA_STRINGSZX,								BFCNF_LINE_MAXC,	// Mode camera is in				//NEEDWORK, must be bigger
AltaCoEntOwner,			"OWNER",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// origonal builder
AltaCoEntFileRev,		"REVISION",			BFCNFDATA_BFU32,									1,					// how many times been changed
AltaCoEntModelComp,		"MODELCOMP",		BFCNFDATA_BFU32,									1,					// HW model compatibility value
AltaCoEntRevComp,		"REVCOMP",			BFCNFDATA_BFU32,									1,					// HW revision compatibility value
AltaCoEntAqTimeout,		"AQTIMEOUT",		BFCNFDATA_BFU32,									1,					// Acquistion timeout
AltaCoEntFormat,		"FORMAT",			BFCNFDATA_BFU32,									1,					// Camera format
AltaCoEntFlashMux,		"FLASHMUX",			BFCNFDATA_STRINGSZX,								BFCNF_OWNER_MAXC,	// required flash file for MUX
AltaCoEntPixBitDepth,	"PIXBITDEPTH",		BFCNFDATA_BFU32,									1,					// Pixel depth
AltaCoEntXSize,			"XSIZE",			BFCNFDATA_BFU32,									1,					// X size
AltaCoEntYSize,			"YSIZE",			BFCNFDATA_BFU32,									1,					// Y size
AltaCoEntExpMod,		"EXPMOD",			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Exposure model parameters
AltaCoEntCon0,			"CON0"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon1,			"CON1"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon2,			"CON2"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon3,			"CON3"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon4,			"CON4"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon5,			"CON5"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon6,			"CON6"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon7,			"CON7"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon8,			"CON8"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon9,			"CON9"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon10,			"CON10"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon11,			"CON11"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon12,			"CON12"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon13,			"CON13"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon14,			"CON14"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon15,			"CON15"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon16,			"CON16"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon17,			"CON17"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon18,			"CON18"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon19,			"CON19"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon20,			"CON20"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon21,			"CON21"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon22,			"CON22"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon23,			"CON23"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon24,			"CON24"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon25,			"CON25"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon26,			"CON26"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon27,			"CON27"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon42,			"CON42"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon43,			"CON43"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon44,			"CON44"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon45,			"CON45"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon46,			"CON46"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon47,			"CON47"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon48,			"CON48"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon49,			"CON49"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoEntCon50,			"CON50"	,			BFCNFDATA_BFU32|BFCNFDATA_PAIR,						1,					// Register
AltaCoAFECommand,		"AFE_COMMAND",		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFCNF_AFE_COMMAND_MAXE,	// List of AFE programming commands
AltaCoEntCTab,			"CTAB"	,			BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		R64ENT_CTAB_MAXE,	// CTAB
AltaCoEntQMod,			"QTABMODEL"	,		BFCNFDATA_BFU32|BFCNFDATA_LIST|BFCNFDATA_PAIR,		BFENT_QMOD_MAXE,	// QMOD
AltaCoEntComment,		"COMMENTS",			BFCNFDATA_STRING,									BFCNF_OWNER_MAXCOM,	// Commments
0,								"",									0,												0
};

#endif //__R64ENTRY__
































