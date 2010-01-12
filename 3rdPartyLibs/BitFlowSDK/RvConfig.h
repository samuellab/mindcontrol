/***************************************************************************
*
* RvConfig.h
*
* Definitions of data structures to support configuration of Raven system
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* 05/13/96	rjd		creation
*
***************************************************************************/

#if !defined(__RVCONFIG__) && !defined(RV_KERNEL)
#define __RVCONFIG__

#include "RvType.h"

/*
* Defines IDs for camera entry structure
* These are specific for PRVCAM
*/



#define RVCNF_FORM_LINEFORMAT_MASK		0x000000FF
#define RVCNF_FORM_NONINTERLACED		0x00000001
#define RVCNF_FORM_INTERLACED			0x00000002
#define RVCNF_FORM_DATAFORMAT_MASK		0x00000F00

/*
* Camera description defines
*/

// list(s) sizes
#define RVENT_QMOD_MAXE		10
// entry indexes
#define RvEntRaven		    1
#define RvEntMake			2
#define RvEntModel			4
#define RvEntMode			5
#define RvEntOwner			6
#define RvEntFileRev		7
#define RvEntModelComp		8
#define RvEntRevComp		9
#define RvEntAqTimeout		10
#define RvEntFormat			11
#define	RvEntPixBitDepth	12
#define RvEntNumCameras		13
#define RvEntXSize			14
#define RvEntYSize0			15
#define RvEntYSize1			16
#define RvEntYSize2			17
#define RvEntYSize3			18
#define	RvEntExpMod			19
#define RvEntCon0			20
#define RvEntCon1			21
#define RvEntCon2			22
#define RvEntCon3			23
#define RvEntCon4			24
#define RvEntCon5			25
#define RvEntCon6			26
#define RvEntCon7			27
#define RvEntCon8			28
#define RvEntCon9			29
#define RvEntCon10			30
#define RvEntCon11			31
#define RvEntCon12			32
#define RvEntCon13			33
#define RvEntCon14			34
#define RvEntCon15			35
#define RvEntCon16			36
#define RvEntCon17			37
#define RvEntCon18			38
#define RvEntCon19			39
#define RvEntCon20			40
#define RvEntCon21			41
#define RvEntCon22			42
#define RvEntCon23			43
#define RvEntCon24			44
#define RvEntCon25			45
#define RvEntCon26			46
#define RvEntCon27			47
#define RvEntCon28			48
#define RvEntCon29			49
#define RvEntCon30			50
#define RvEntCon31			51
#define RvEntCon32			52
#define RvEntCon33			53
#define RvEntCon34			54
#define RvEntCon35			55
#define RvEntCon36			56
#define RvEntCon37			57
#define RvEntCon38			58
#define RvEntCon39			59
#define RvEntCon40			60
#define RvEntCon41			61
#define RvEntCon42			62
#define RvEntCon43			63
#define RvEntCon44			64 
#define RvEntCon45			65
#define RvEntDMACh0Mode		66
#define RvEntDMACh1Mode		67
#define RvEntDMAArb0		68			 
#define RvEntDMAArb1		69
#define RvEntBtCmd0			70
#define	RvEntBtCmd2			71
#define	RvEntBtCmd3			72
#define	RvEntBtCmd4			73
#define	RvEntBtCmd5			74
#define	RvEntBtCmd6			75
#define	RvEntBtCmd7			76
#define	RvEntBtBrightness	77
#define	RvEntBtContrast		78
#define	RvEntBtSaturation	79
#define	RvEntBtHue			80
#define	RvEntBtHclock		81
#define	RvEntBtHdelay		82
#define	RvEntBtActivepix	83
#define	RvEntBtVdelay		84
#define	RvEntBtActivelines	85
#define	RvEntBtScfreq		86
#define	RvEntBtAgcdelay		87
#define	RvEntBtBurstdelay	88
#define	RvEntBtSamplerate	89
#define	RvEntBtPolarity		90
#define RvEntQMod0			91									// list
#define RvEntQMod1			(91 + RVENT_QMOD_MAXE)				// list
#define RvEntQMod2			(91 + 2 * RVENT_QMOD_MAXE)			// list
#define RvEntQMod3			(91 + 3 * RVENT_QMOD_MAXE)			// list
#define RvEntComment		(91 + 4 * RVENT_QMOD_MAXE)			// list
// size of list + 1
#define RVCNF_ENTRIES_TOTAL	96
// Maxentries plus max size of each list entry
#define RVCNF_ENTRIES_MAX		(RVCNF_ENTRIES_TOTAL + 4 * RVENT_QMOD_MAXE)


#endif // __RVCONFIG__

