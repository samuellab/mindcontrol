/***************************************************************************
*
* BFEntTrans.h
*
* Configuratino structure token definitions and translations tables
*
* Copyright (C) 2000 by BitFlow, Inc.  All Rights Reserved.
*
* 12/04/02	rjd		moved tables to this central location
*
***************************************************************************/

#if !defined(__BFENTTRANS__) && !defined(KernelOS)
#define __BFENTTRANS__

#include "BFType.h"

// R2

// maximum number of CTAB entries
// NOTE: Do not change this number. Changing this number
// will make all the camera configuration files already 
// built no longer work.
#define R2ENT_CTAB_MAXE		50


// configuration tokens
#define R2EntRoadRunner		1
#define R2EntName			2
#define R2EntOwner			3
#define R2EntFileRev		4
#define R2EntModelComp		5
#define R2EntRevComp		6
#define R2EntAqTimeout		7
#define R2EntFormat			8
#define	R2EntPixBitDepth	9
#define R2EntXSize			10
#define R2EntYSize			11
#define	R2EntExpMod			12
#define R2EntDispCon0		13
#define R2EntCon0			14
#define R2EntCon1			15
#define R2EntCon2			16
#define R2EntCon3			17
#define R2EntCon4			18
#define R2EntCon5			19
#define R2EntCon6			20
#define R2EntCon7			21
#define R2EntCon8			22
#define R2EntCon9			23
#define R2EntCon10			24
#define R2EntCon11			25
#define R2EntDMACh0Mode		26
#define R2EntDMACh1Mode		27
#define R2EntDMAArb0		28				 
#define R2EntDMAArb1		29
#define R2EntCTab			30 // list
#define R2EntQMod			(31 + R2ENT_CTAB_MAXE) // list
#define R2EntComment		(32 + R2ENT_CTAB_MAXE + R2ENT_CTAB_MAXE)

// Maxentries plus max size of each list entry
#define R2CNF_ENTRIES_TOTAL	33
#define R2CNF_ENTRIES_MAX		(R2CNF_ENTRIES_TOTAL + R2ENT_CTAB_MAXE + R2ENT_CTAB_MAXE)

// R2CL

// maximum number of CTAB entries
// NOTE: Do not change this number. Changing this number
// will make all the camera configuration files already 
// built no longer work.
#define R2CLENT_CTAB_MAXE		50


// configuration tokens
#define R2CLEntRoadRunner		1
#define R2CLEntMake				2
#define R2CLEntModel			3 
#define R2CLEntMode				4 
#define R2CLEntOwner			5 
#define R2CLEntFileRev			6 
#define R2CLEntModelComp		7 
#define R2CLEntRevComp			8 
#define R2CLEntAqTimeout		9 
#define R2CLEntFormat			10
#define	R2CLEntPixBitDepth		11
#define R2CLEntXSize			12
#define R2CLEntYSize			13
#define	R2CLEntExpMod			14
#define R2CLEntDispCon0			15
#define R2CLEntCon0				16
#define R2CLEntCon1				17
#define R2CLEntCon2				18
#define R2CLEntCon3				19
#define R2CLEntCon4				20
#define R2CLEntCon5				21
#define R2CLEntCon6				22
#define R2CLEntCon7				23
#define R2CLEntCon8				24
#define R2CLEntCon9				25
#define R2CLEntCon10			26
#define R2CLEntCon11			27
#define R2CLEntDMACh0Mode		28
#define R2CLEntDMACh1Mode		29
#define R2CLEntDMAArb0			30				 
#define R2CLEntDMAArb1			31
#define R2CLEntCTab				32 // list
#define R2CLEntQMod				(33 + R2CLENT_CTAB_MAXE) // list
#define R2CLEntComment			(34 + R2CLENT_CTAB_MAXE + R2CLENT_CTAB_MAXE)

// Maxentries plus max size of each list entry
#define R2CLCNF_ENTRIES_TOTAL	35
#define R2CLCNF_ENTRIES_MAX		(R2CLCNF_ENTRIES_TOTAL + R2CLENT_CTAB_MAXE + R2CLENT_CTAB_MAXE)


// R64

// maximum number of CTAB entries
// NOTE: Do not change this number. Changing this number
// will make all the camera configuration files already 
// built no longer work.
#define R64ENT_CTAB_MAXE		50

// configuration tokens
#define R64EntR64			1
#define R64EntMake			2
#define R64EntModel			3 
#define R64EntMode			4 
#define R64EntOwner			5 
#define R64EntFileRev		6 
#define R64EntModelComp		7 
#define R64EntRevComp		8 
#define R64EntAqTimeout		9 
#define R64EntFormat		10
#define R64EntFlashMux		11
#define R64EntFlashDCC		12
#define	R64EntPixBitDepth	13
#define R64EntXSize			14
#define R64EntYSize			15
#define	R64EntExpMod		16
#define R64EntCon0			17
#define R64EntCon1			18
#define R64EntCon2			19
#define R64EntCon3			20
#define R64EntCon4			21
#define R64EntCon5			22
#define R64EntCon6			23
#define R64EntCon7			24
#define R64EntCon8			25
#define R64EntCon9			26
#define R64EntCon10			27
#define R64EntCon11			28
#define R64EntCon12			29
#define R64EntCon13			30
#define R64EntCon14			31
#define R64EntCon15			32
#define R64EntCon16			33
#define R64EntCon17			34
#define R64EntCon18			35
#define R64EntCon19			36
#define R64EntCon20			37
#define R64EntCon21			38
#define R64EntCon22			39
#define R64EntCon23			40
#define R64EntCon24			41
#define R64EntCon25			42
#define R64EntCon26			43
#define R64EntCon27			44
#define R64EntCTab			45 // list
#define R64EntQMod			(46 + R64ENT_CTAB_MAXE) // list
#define R64EntComment		(47 + R64ENT_CTAB_MAXE + R64ENT_CTAB_MAXE)

// Maxentries plus max size of each list entry
#define R64CNF_ENTRIES_TOTAL	48
#define R64CNF_ENTRIES_MAX		(R64CNF_ENTRIES_TOTAL + R64ENT_CTAB_MAXE + R64ENT_CTAB_MAXE)

// Alta

#define AltaEntAlta					1		
#define AltaEntMake					2
#define AltaEntModel				3
#define AltaEntMode					4
#define AltaEntOwner				5
#define AltaEntFileRev				6
#define AltaEntModelComp			7
#define AltaEntRevComp				8
#define AltaEntAqTimeout			9
#define AltaEntFormat				10
#define AltaEntFlashMux				11
#define AltaEntPixBitDepth			12
#define AltaEntXSize				13
#define AltaEntYSize				14
#define AltaEntExpMod				15
#define AltaEntCon0					16
#define AltaEntCon1					17
#define AltaEntCon2					18
#define AltaEntCon3					19
#define AltaEntCon4					20
#define AltaEntCon5					21
#define AltaEntCon6					22
#define AltaEntCon7					23
#define AltaEntCon8					24
#define AltaEntCon9					25
#define AltaEntCon10				26
#define AltaEntCon11				27
#define AltaEntCon12				28
#define AltaEntCon13				29
#define AltaEntCon14				30
#define AltaEntCon15				31
#define AltaEntCon16				32
#define AltaEntCon17				33
#define AltaEntCon18				34
#define AltaEntCon19				35
#define AltaEntCon20				36
#define AltaEntCon21				37
#define AltaEntCon22				38
#define AltaEntCon23				39
#define AltaEntCon24				40
#define AltaEntCon25				41
#define AltaEntCon26				42
#define AltaEntCon27				43
#define AltaEntCon42				44
#define AltaEntCon43				45
#define AltaEntCon44				46
#define AltaEntCon45				47
#define AltaEntCon46				48
#define AltaEntCon47				49
#define AltaEntCon48				50
#define AltaEntCon49				51
#define AltaEntCon50				52
#define AltaEntAFEDevID				53
#define AltaEntAFESyncStat			54
#define AltaEntAFESyncPol			55
#define AltaEntAFEHSyncSlicer		56
#define AltaEntAFESOGSlicer			57
#define AltaEntAFEInCnf				58
#define AltaEntAFERedGain			59
#define AltaEntAFEGreenGain			60
#define AltaEntAFEBlueGain	 		61
#define AltaEntAFERedOffs	 		62
#define AltaEntAFEGreenOffs			63
#define AltaEntAFEBlueOffs			64
#define AltaEntAFEOffsDACCnf		65
#define AltaEntAFEBandwidth			66
#define AltaEntAFEPLLHTotalMSB		67
#define AltaEntAFEPLLHTotalLSB		68
#define AltaEntAFEPLLSamplePhase	69
#define AltaEntAFEPLLPrecoast		70
#define AltaEntAFEPLLPostcoast		71
#define AltaEntAFEPLLMisc	 		72
#define AltaEntAFEDCRstrPisMSB		73
#define AltaEntAFEDCRstrPixLSB		74
#define AltaEntAFEDCRrstWidth		75
#define AltaEntAFEABLCCnf	 		76
#define AltaEntAFEOutFormat			77
#define AltaEntAFEHSOutWidth		78
#define AltaEntAFEOutSigDisable		79
#define AltaEntAFEPowerCon	 		80
#define AltaEntAFEPLLTuning			81
#define AltaEntAFERedABLC	 		82
#define AltaEntAFEGreenABLC			83
#define AltaEntAFEBlueABLC	 		84
#define AltaEntAFEDCRstrClamp		85
#define AltaEntAFESyncSepCon		86
#define AltaEntCTab					87
#define AltaEntQMod			(88 + R64ENT_CTAB_MAXE) // list
#define AltaEntComment		(89 + R64ENT_CTAB_MAXE + R64ENT_CTAB_MAXE)

// Maxentries plus max size of each list entry
#define ALTACNF_ENTRIES_TOTAL	90
#define ALTACNF_ENTRIES_MAX		(ALTACNF_ENTRIES_TOTAL + R64ENT_CTAB_MAXE + R64ENT_CTAB_MAXE)

// Alta

#define AltaCoEntAlta				1		
#define AltaCoEntMake				2
#define AltaCoEntModel				3
#define AltaCoEntMode				4
#define AltaCoEntOwner				5
#define AltaCoEntFileRev			6
#define AltaCoEntModelComp			7
#define AltaCoEntRevComp			8
#define AltaCoEntAqTimeout			9
#define AltaCoEntFormat				10
#define AltaCoEntFlashMux			11
#define AltaCoEntPixBitDepth		12
#define AltaCoEntXSize				13
#define AltaCoEntYSize				14
#define AltaCoEntExpMod				15
#define AltaCoEntCon0				16
#define AltaCoEntCon1				17
#define AltaCoEntCon2				18
#define AltaCoEntCon3				19
#define AltaCoEntCon4				20
#define AltaCoEntCon5				21
#define AltaCoEntCon6				22
#define AltaCoEntCon7				23
#define AltaCoEntCon8				24
#define AltaCoEntCon9				25
#define AltaCoEntCon10				26
#define AltaCoEntCon11				27
#define AltaCoEntCon12				28
#define AltaCoEntCon13				29
#define AltaCoEntCon14				30
#define AltaCoEntCon15				31
#define AltaCoEntCon16				32
#define AltaCoEntCon17				33
#define AltaCoEntCon18				34
#define AltaCoEntCon19				35
#define AltaCoEntCon20				36
#define AltaCoEntCon21				37
#define AltaCoEntCon22				38
#define AltaCoEntCon23				39
#define AltaCoEntCon24				40
#define AltaCoEntCon25				41
#define AltaCoEntCon26				42
#define AltaCoEntCon27				43
#define AltaCoEntCon42				44
#define AltaCoEntCon43				45
#define AltaCoEntCon44				46
#define AltaCoEntCon45				47
#define AltaCoEntCon46				48
#define AltaCoEntCon47				49
#define AltaCoEntCon48				50
#define AltaCoEntCon49				51
#define AltaCoEntCon50				52
#define AltaCoAFECommand			53 // list
#define AltaCoEntCTab				(54 + BFCNF_AFE_COMMAND_MAXE)
#define AltaCoEntQMod				(55 + BFCNF_AFE_COMMAND_MAXE + R64ENT_CTAB_MAXE) // list
#define AltaCoEntComment			(56 + BFCNF_AFE_COMMAND_MAXE + R64ENT_CTAB_MAXE + R64ENT_CTAB_MAXE) // list

// Maxentries plus max size of each list entry
#define ALTACOCNF_ENTRIES_TOTAL	57
#define ALTACOCNF_ENTRIES_MAX		(ALTACOCNF_ENTRIES_TOTAL + BFCNF_AFE_COMMAND_MAXE + R64ENT_CTAB_MAXE + R64ENT_CTAB_MAXE)


typedef enum
{
	BFGenEntBF	= 0,
	BFGenEntName,
	BFGenEntMake,
	BFGenEntModel,
	BFGenEntMode,
	BFGenEntOwner,
	BFGenEntFileRev,
	BFGenEntModelComp,
	BFGenEntRevComp,
	BFGenEntAqTimeout,
	BFGenEntFormat,
	BFGenEntFlashMux,
	BFGenEntFlashDCC,
	BFGenEntPixBitDepth,
	BFGenEntXSize,
	BFGenEntYSize,
	BFGenEntExpMod,
	BFGenEntDispCon0,		
	BFGenEntCon0,		
	BFGenEntCon1,		
	BFGenEntCon2,		
	BFGenEntCon3,		
	BFGenEntCon4,		
	BFGenEntCon5,		
	BFGenEntCon6,		
	BFGenEntCon7,		
	BFGenEntCon8,		
	BFGenEntCon9,		
	BFGenEntCon10,		
	BFGenEntCon11,		
	BFGenEntCon12,		
	BFGenEntCon13,		
	BFGenEntCon14,		
	BFGenEntCon15,		
	BFGenEntCon16,		
	BFGenEntCon17,		
	BFGenEntCon18,		
	BFGenEntCon19,		
	BFGenEntCon20,		
	BFGenEntCon21,		
	BFGenEntCon22,		
	BFGenEntCon23,		
	BFGenEntCon24,		
	BFGenEntCon25,		
	BFGenEntCon26,		
	BFGenEntCon27,		
	BFGenEntDMACh0Mode,
	BFGenEntDMACh1Mode,
	BFGenEntDMAArb0,
	BFGenEntDMAArb1,
	BFGenEntCTab,		
	BFGenEntQMod,		
	BFGenEntComment,
	BFGenEntNoMatch,
	BFGenEntTableSize
} BFGenEnt;


// R2 translation table
static BFU32 R2TransTable[BFGenEntTableSize] = 
{
	R2EntRoadRunner,		// BFEntBF,
	R2EntName,				// BFEntName,
	BFGenEntNoMatch,		// BFEntMake,
	BFGenEntNoMatch,		// BFEntModel,
	BFGenEntNoMatch,		// BFEntMode,
	R2EntOwner,				// BFEntOwner,
	R2EntFileRev,			// BFEntFileRev,
	R2EntModelComp,			// BFEntModelComp,
	R2EntRevComp,			// BFEntRevComp,
	R2EntAqTimeout,			// BFEntAqTimeout,
	R2EntFormat,			// BFEntFormat,
	BFGenEntNoMatch,		// BFEntFlashMux,
	BFGenEntNoMatch,		// BFEntFlashDCC,
	R2EntPixBitDepth,		// BFEntPixBitDepth,
	R2EntXSize,				// BFEntXSize,
	R2EntYSize,				// BFEntYSize,
	R2EntExpMod,			// BFEntExpMod,
	R2EntDispCon0,			// BFEntDispCon0,		
	R2EntCon0,				// BFEntCon0,		
	R2EntCon1,				// BFEntCon1,		
	R2EntCon2,				// BFEntCon2,		
	R2EntCon3,				// BFEntCon3,		
	R2EntCon4,				// BFEntCon4,		
	R2EntCon5,				// BFEntCon5,		
	R2EntCon6,				// BFEntCon6,		
	R2EntCon7,				// BFEntCon7,		
	R2EntCon8,				// BFEntCon8,		
	R2EntCon9,				// BFEntCon9,		
	R2EntCon10,				// BFEntCon10,		
	R2EntCon11,				// BFEntCon11,		
	BFGenEntNoMatch,		// BFEntCon12,		
	BFGenEntNoMatch,		// BFEntCon13,		
	BFGenEntNoMatch,		// BFEntCon14,		
	BFGenEntNoMatch,		// BFEntCon15,		
	BFGenEntNoMatch,		// BFEntCon16,		
	BFGenEntNoMatch,		// BFEntCon17,		
	BFGenEntNoMatch,		// BFEntCon18,		
	BFGenEntNoMatch,		// BFEntCon19,		
	BFGenEntNoMatch,		// BFEntCon20,		
	BFGenEntNoMatch,		// BFEntCon21,		
	BFGenEntNoMatch,		// BFEntCon22,		
	BFGenEntNoMatch,		// BFEntCon23,		
	BFGenEntNoMatch,		// BFEntCon24,		
	BFGenEntNoMatch,		// BFEntCon25,		
	BFGenEntNoMatch,		// BFEntCon26,		
	BFGenEntNoMatch,		// BFEntCon27,		
	R2EntDMACh0Mode,		// BFGenEntDMACh0Mode,
	R2EntDMACh1Mode,		// BFGenEntDMACh1Mode,
	R2EntDMAArb0,			// BFGenEntDMAArb0,
	R2EntDMAArb1,			// BFGenEntDMAArb1,
	R2EntCTab,				// BFEntCTab,		
	R2EntQMod,				// BFEntQMod,		
	R2EntComment,			// BFEntComment,
	BFGenEntNoMatch,		// BFGenEntNoMatch,
};


// R2 Cl translation table
static BFU32 R2CLTransTable[BFGenEntTableSize] = 
{
	R2CLEntRoadRunner,		// BFEntBF,
	BFGenEntNoMatch,		// BFEntName,
	R2CLEntMake,			// BFEntMake,
	R2CLEntModel,			// BFEntModel,
	R2CLEntMode,			// BFEntMode,
	R2CLEntOwner,			// BFEntOwner,
	R2CLEntFileRev,			// BFEntFileRev,
	R2CLEntModelComp,		// BFEntModelComp,
	R2CLEntRevComp,			// BFEntRevComp,
	R2CLEntAqTimeout,		// BFEntAqTimeout,
	R2CLEntFormat,			// BFEntFormat,
	BFGenEntNoMatch,		// BFEntFlashMux,
	BFGenEntNoMatch,		// BFEntFlashDCC,
	R2CLEntPixBitDepth,		// BFEntPixBitDepth,
	R2CLEntXSize,			// BFEntXSize,
	R2CLEntYSize,			// BFEntYSize,
	R2CLEntExpMod,			// BFEntExpMod,
	R2CLEntDispCon0,		// BFEntDispCon0,		
	R2CLEntCon0,			// BFEntCon0,		
	R2CLEntCon1,			// BFEntCon1,		
	R2CLEntCon2,			// BFEntCon2,		
	R2CLEntCon3,			// BFEntCon3,		
	R2CLEntCon4,			// BFEntCon4,		
	R2CLEntCon5,			// BFEntCon5,		
	R2CLEntCon6,			// BFEntCon6,		
	R2CLEntCon7,			// BFEntCon7,		
	R2CLEntCon8,			// BFEntCon8,		
	R2CLEntCon9,			// BFEntCon9,		
	R2CLEntCon10,			// BFEntCon10,		
	R2CLEntCon11,			// BFEntCon11,		
	BFGenEntNoMatch,		// BFEntCon12,		
	BFGenEntNoMatch,		// BFEntCon13,		
	BFGenEntNoMatch,		// BFEntCon14,		
	BFGenEntNoMatch,		// BFEntCon15,		
	BFGenEntNoMatch,		// BFEntCon16,		
	BFGenEntNoMatch,		// BFEntCon17,		
	BFGenEntNoMatch,		// BFEntCon18,		
	BFGenEntNoMatch,		// BFEntCon19,		
	BFGenEntNoMatch,		// BFEntCon20,		
	BFGenEntNoMatch,		// BFEntCon21,		
	BFGenEntNoMatch,		// BFEntCon22,		
	BFGenEntNoMatch,		// BFEntCon23,		
	BFGenEntNoMatch,		// BFEntCon24,		
	BFGenEntNoMatch,		// BFEntCon25,		
	BFGenEntNoMatch,		// BFEntCon26,		
	BFGenEntNoMatch,		// BFEntCon27,		
	R2CLEntDMACh0Mode,		// BFGenEntDMACh0Mode,
	R2CLEntDMACh1Mode,		// BFGenEntDMACh1Mode,
	R2CLEntDMAArb0,			// BFGenEntDMAArb0,
	R2CLEntDMAArb1,			// BFGenEntDMAArb1,
	R2CLEntCTab,			// BFEntCTab,		
	R2CLEntQMod,			// BFEntQMod,		
	R2CLEntComment,			// BFEntComment,
	BFGenEntNoMatch,		// BFGenEntNoMatch,
};

// R64 translation table
static BFU32 R64TransTable[BFGenEntTableSize] = 
{
	R64EntR64,				// BFEntBF,
	BFGenEntNoMatch,		// BFEntName,
	R64EntMake,				// BFEntMake,
	R64EntModel,			// BFEntModel,
	R64EntMode,				// BFEntMode,
	R64EntOwner,			// BFEntOwner,
	R64EntFileRev,			// BFEntFileRev,
	R64EntModelComp,		// BFEntModelComp,
	R64EntRevComp,			// BFEntRevComp,
	R64EntAqTimeout,		// BFEntAqTimeout,
	R64EntFormat,			// BFEntFormat,
	R64EntFlashMux,			// BFEntFlashMux,
	R64EntFlashDCC,			// BFEntFlashDCC,
	R64EntPixBitDepth,		// BFEntPixBitDepth,
	R64EntXSize,			// BFEntXSize,
	R64EntYSize,			// BFEntYSize,
	R64EntExpMod,			// BFEntExpMod,
	BFGenEntNoMatch,		// BFEntDispCon0,		
	R64EntCon0,				// BFEntCon0,		
	R64EntCon1,				// BFEntCon1,		
	R64EntCon2,				// BFEntCon2,		
	R64EntCon3,				// BFEntCon3,		
	R64EntCon4,				// BFEntCon4,		
	R64EntCon5,				// BFEntCon5,		
	R64EntCon6,				// BFEntCon6,		
	R64EntCon7,				// BFEntCon7,		
	R64EntCon8,				// BFEntCon8,		
	R64EntCon9,				// BFEntCon9,		
	R64EntCon10,			// BFEntCon10,		
	R64EntCon11,			// BFEntCon11,		
	R64EntCon12,			// BFEntCon12,		
	R64EntCon13,			// BFEntCon13,		
	R64EntCon14,			// BFEntCon14,		
	R64EntCon15,			// BFEntCon15,		
	R64EntCon16,			// BFEntCon16,		
	R64EntCon17,			// BFEntCon17,		
	R64EntCon18,			// BFEntCon18,		
	R64EntCon19,			// BFEntCon19,		
	R64EntCon20,			// BFEntCon20,		
	R64EntCon21,			// BFEntCon21,		
	R64EntCon22,			// BFEntCon22,		
	R64EntCon23,			// BFEntCon23,		
	R64EntCon24,			// BFEntCon24,		
	R64EntCon25,			// BFEntCon25,		
	R64EntCon26,			// BFEntCon26,		
	R64EntCon27,			// BFEntCon27,		
	BFGenEntNoMatch,		// BFGenEntDMACh0Mode,
	BFGenEntNoMatch,		// BFGenEntDMACh1Mode,
	BFGenEntNoMatch,		// BFGenEntDMAArb0,
	BFGenEntNoMatch,		// BFGenEntDMAArb1,
	R64EntCTab,				// BFEntCTab,		
	R64EntQMod,				// BFEntQMod,		
	R64EntComment,			// BFEntComment,
	BFGenEntNoMatch,		// BFGenEntNoMatch,
};


// Alta-AN translation table
static BFU32 AltaTransTable[BFGenEntTableSize] = 
{
	AltaEntAlta,			// BFEntBF,
	BFGenEntNoMatch,		// BFEntName,
	AltaEntMake,			// BFEntMake,
	AltaEntModel,			// BFEntModel,
	AltaEntMode,			// BFEntMode,
	AltaEntOwner,			// BFEntOwner,
	AltaEntFileRev,			// BFEntFileRev,
	AltaEntModelComp,		// BFEntModelComp,
	AltaEntRevComp,			// BFEntRevComp,
	AltaEntAqTimeout,		// BFEntAqTimeout,
	AltaEntFormat,			// BFEntFormat,
	AltaEntFlashMux,		// BFEntFlashMux,
	BFGenEntNoMatch,		// BFEntFlashDCC,
	AltaEntPixBitDepth,		// BFEntPixBitDepth,
	AltaEntXSize,			// BFEntXSize,
	AltaEntYSize,			// BFEntYSize,
	AltaEntExpMod,			// BFEntExpMod,
	BFGenEntNoMatch,		// BFEntDispCon0,		
	AltaEntCon0,			// BFEntCon0,		
	AltaEntCon1,			// BFEntCon1,		
	AltaEntCon2,			// BFEntCon2,		
	AltaEntCon3,			// BFEntCon3,		
	AltaEntCon4,			// BFEntCon4,		
	AltaEntCon5,			// BFEntCon5,		
	AltaEntCon6,			// BFEntCon6,		
	AltaEntCon7,			// BFEntCon7,		
	AltaEntCon8,			// BFEntCon8,		
	AltaEntCon9,			// BFEntCon9,		
	AltaEntCon10,			// BFEntCon10,		
	AltaEntCon11,			// BFEntCon11,		
	AltaEntCon12,			// BFEntCon12,		
	AltaEntCon13,			// BFEntCon13,		
	AltaEntCon14,			// BFEntCon14,		
	AltaEntCon15,			// BFEntCon15,		
	AltaEntCon16,			// BFEntCon16,		
	AltaEntCon17,			// BFEntCon17,		
	AltaEntCon18,			// BFEntCon18,		
	AltaEntCon19,			// BFEntCon19,		
	AltaEntCon20,			// BFEntCon20,		
	AltaEntCon21,			// BFEntCon21,		
	AltaEntCon22,			// BFEntCon22,		
	AltaEntCon23,			// BFEntCon23,		
	AltaEntCon24,			// BFEntCon24,		
	AltaEntCon25,			// BFEntCon25,		
	AltaEntCon26,			// BFEntCon26,		
	AltaEntCon27,			// BFEntCon27,		
	BFGenEntNoMatch,		// BFGenEntDMACh0Mode,
	BFGenEntNoMatch,		// BFGenEntDMACh1Mode,
	BFGenEntNoMatch,		// BFGenEntDMAArb0,
	BFGenEntNoMatch,		// BFGenEntDMAArb1,
	AltaEntCTab,			// BFEntCTab,		
	AltaEntQMod,			// BFEntQMod,		
	AltaEntComment,			// BFEntComment,
	BFGenEntNoMatch,		// BFGenEntNoMatch,
};

// Alta-CO translation table

static BFU32 AltaCOTransTable[BFGenEntTableSize] = 
{
	AltaCoEntAlta,			// BFEntBF,
	BFGenEntNoMatch,		// BFEntName,
	AltaCoEntMake,			// BFEntMake,
	AltaCoEntModel,			// BFEntModel,
	AltaCoEntMode,			// BFEntMode,
	AltaCoEntOwner,			// BFEntOwner,
	AltaCoEntFileRev,		// BFEntFileRev,
	AltaCoEntModelComp,		// BFEntModelComp,
	AltaCoEntRevComp,		// BFEntRevComp,
	AltaCoEntAqTimeout,		// BFEntAqTimeout,
	AltaCoEntFormat,		// BFEntFormat,
	AltaCoEntFlashMux,		// BFEntFlashMux,
	BFGenEntNoMatch,		// BFEntFlashDCC,
	AltaCoEntPixBitDepth,	// BFEntPixBitDepth,
	AltaCoEntXSize,			// BFEntXSize,
	AltaCoEntYSize,			// BFEntYSize,
	AltaCoEntExpMod,		// BFEntExpMod,
	BFGenEntNoMatch,		// BFEntDispCon0,		
	AltaCoEntCon0,			// BFEntCon0,		
	AltaCoEntCon1,			// BFEntCon1,		
	AltaCoEntCon2,			// BFEntCon2,		
	AltaCoEntCon3,			// BFEntCon3,		
	AltaCoEntCon4,			// BFEntCon4,		
	AltaCoEntCon5,			// BFEntCon5,		
	AltaCoEntCon6,			// BFEntCon6,		
	AltaCoEntCon7,			// BFEntCon7,		
	AltaCoEntCon8,			// BFEntCon8,		
	AltaCoEntCon9,			// BFEntCon9,		
	AltaCoEntCon10,			// BFEntCon10,		
	AltaCoEntCon11,			// BFEntCon11,		
	AltaCoEntCon12,			// BFEntCon12,		
	AltaCoEntCon13,			// BFEntCon13,		
	AltaCoEntCon14,			// BFEntCon14,		
	AltaCoEntCon15,			// BFEntCon15,		
	AltaCoEntCon16,			// BFEntCon16,		
	AltaCoEntCon17,			// BFEntCon17,		
	AltaCoEntCon18,			// BFEntCon18,		
	AltaCoEntCon19,			// BFEntCon19,		
	AltaCoEntCon20,			// BFEntCon20,		
	AltaCoEntCon21,			// BFEntCon21,		
	AltaCoEntCon22,			// BFEntCon22,		
	AltaCoEntCon23,			// BFEntCon23,		
	AltaCoEntCon24,			// BFEntCon24,		
	AltaCoEntCon25,			// BFEntCon25,		
	AltaCoEntCon26,			// BFEntCon26,		
	AltaCoEntCon27,			// BFEntCon27,		
	BFGenEntNoMatch,		// BFGenEntDMACh0Mode,
	BFGenEntNoMatch,		// BFGenEntDMACh1Mode,
	BFGenEntNoMatch,		// BFGenEntDMAArb0,
	BFGenEntNoMatch,		// BFGenEntDMAArb1,
	AltaCoEntCTab,			// BFEntCTab,		
	AltaCoEntQMod,			// BFEntQMod,		
	AltaCoEntComment,		// BFEntComment,
	BFGenEntNoMatch,		// BFGenEntNoMatch,
};


#endif // __BFENTTRANS__


