//
// Creation:    R64Info.h
// Created:     May 28, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// R64 Public Definitions
//
// History:
//
// 05/28/02     rbs     Created file.
//

#if !defined(__R64INFO__)
#define __R64INFO__

#if !defined(__BFSYSTEM)
#include "BFSystem.h"
#endif

#if !defined(__R64TYPE__)
#include "R64Type.h"
#endif

// Registry key paths.

#ifdef LINX_BUILD_TARGET
	#define R64K_ROOT						"System\\CurrentControlSet\\Services\\LinX\\Ginga"
	#define R64K_DEVICE						"GingaDev"

	#define R64K_FAMILY						"Ginga"
	#define R64_TOKEN						"GINGADG"
	#define R64K_CONFIG_PATH				"GingaDGe"
	#define R64_CAMFILE_EXT					".gdg"
	#define R64_CAMFILE_FOLDER				"\\GingaDGe"
	
	#define ALTA_FAMILY						"GingaPPe"
	#define ALTA_TOKEN						"GINGAPPe"
	#define ALTA_CONFIG_PATH				"GingaPPe"
	#define ALTA_CAMFILE_EXT				".gpp"
	#define ALTA_CAMFILE_FOLDER				"\\GingaPPe"

	#define ALTACO_FAMILY					"GingaPPCe"
	#define ALTACO_TOKEN					"GINGAPPCe"
	#define ALTACO_CONFIG_PATH				"GingaPPCe"
	#define ALTACO_CAMFILE_EXT				".gpc"
	#define ALTACO_CAMFILE_FOLDER			"\\GingaPPCe"
#else
	#define R64K_ROOT						"System\\CurrentControlSet\\Services\\BitFlow\\R64"
	#define R64K_DEVICE						"R64Dev"

	#define R64K_FAMILY						"R64"
	#define R64_TOKEN						"R64"
	#define R64K_CONFIG_PATH				"R64"
	#define R64_CAMFILE_EXT					".r64"
	#define R64_CAMFILE_FOLDER				"\\R64"
	
	#define ALTA_FAMILY						"Alta-AN"
	#define ALTA_TOKEN						"ALTA"
	#define ALTA_CONFIG_PATH				"Anlg"
	#define ALTA_CAMFILE_EXT				".anlg"
	#define ALTA_CAMFILE_FOLDER				"\\Anlg"

	#define ALTACO_FAMILY					"Alta-CO"
	#define ALTACO_TOKEN					"COMP"
	#define ALTACO_CONFIG_PATH				"Comp"
	#define ALTACO_CAMFILE_EXT				".comp"
	#define ALTACO_CAMFILE_FOLDER			"\\Comp"
#endif


// Standard Pseudo Device

#define R64K_PSEUDO_VENDOR_ID			BF_PCI_VEN_ID
#define R64K_PSEUDO_DEVICE_ID			0x3000
#define R64K_PSEUDO_SUB_VENDOR_ID		0x0000
#define R64K_PSEUDO_SUB_SYSTEM_ID		0x0000

// Alta-AN Psuedo Device
#define ALTA_PSEUDO_VENDOR_ID			BF_PCI_VEN_ID
#define ALTA_PSEUDO_DEVICE_ID			0x5000
#define ALTA_PSEUDO_SUB_VENDOR_ID		0x0000
#define ALTA_PSEUDO_SUB_SYSTEM_ID		0x0000
#define ALTA_PSEUDO_INFO_HI				0x1000
#define ALTA_PSEUDO_INFO_LO				0x0000

// Alta-CI Psuedo Device
#define ALTACO_PSEUDO_VENDOR_ID			BF_PCI_VEN_ID
#define ALTACO_PSEUDO_DEVICE_ID			0x6000
#define ALTACO_PSEUDO_SUB_VENDOR_ID		0x0000
#define ALTACO_PSEUDO_SUB_SYSTEM_ID		0x0000
#define ALTACO_PSEUDO_INFO_HI			0x1000
#define ALTACO_PSEUDO_INFO_LO			0x0000

// Interrupt Flag Bits

#define R64_INT_FLAG_CTAB				0x0001
#define R64_INT_FLAG_OVSTEP				0x0002
#define R64_INT_FLAG_HW					0x0004
#define R64_INT_FLAG_TRIG				0x0008
#define R64_INT_FLAG_SER				0x0010
#define R64_INT_FLAG_QUAD				0x0020
#define R64_INT_FLAG_EOF				0x0040

#define R64_INT_FLAG_R64				0x1000
#define R64_INT_FLAG_QL					0x2000
#define R64_INT_FLAG_OTHERS				0x4000

#define R64_INT_MASK_BOARD_INTS			0x0fff		// Mask for board interrupts that must be fully processed. 

// CMDWRITE Write Enable Id

#define R64_CMDWRITE_NONE				0
#define R64_CMDWRITE_INT_CTAB			1
#define R64_CMDWRITE_INT_OVSTEP			2
#define R64_CMDWRITE_INT_HW				3
#define R64_CMDWRITE_INT_TRIG			4
#define R64_CMDWRITE_INT_QUAD			5
#define R64_CMDWRITE_INT_EOF			6

// QTab Attributes

#define R64_DMA_QUAD_LOCAL_ONCEONLY		BF_DMA_QUAD_LOCAL_ONCEONLY

// QTab Next Quad State Bits

#define R64_DMA_QUAD_NEXT_HOST			BF_DMA_QUAD_NEXT_HOST
#define R64_DMA_QUAD_NEXT_EOC			BF_DMA_QUAD_NEXT_EOC
#define R64_DMA_QUAD_NEXT_INT			BF_DMA_QUAD_NEXT_INT
#define R64_DMA_QUAD_NEXT_WRITE			BF_DMA_QUAD_NEXT_WRITE

// Maximum Number of Fields

#define R64_NUMFIELDS					1

#if !defined(KernelOS)

// User level R64 information.

typedef struct _R64InfoUsr
{

	PBFVOID pCurQTab;				// void version of pointer to current (most recent write) QTAB
	PBFVOID pAqQTab;				// void version of pointer to AqSetup() allocated QTABS
	PBFVOID pCurAqSig;				// void version of pointer to current signal used for high level acquisition

} R64InfoUsr, *pR64InfoUsr;

// Useful macros to get things out of the device info block.

#define GetR64Info(BoardId) (BoardId == BFNULL ? BFNULL : ((pBFInfoUsr)BoardId)->pXXInfoUsr == BFNULL ? BFNULL : (pR64InfoUsr)((pBFInfoUsr)BoardId)->pXXInfoUsr)

#endif

#if defined(KernelOS)

// Kernel level R64 information.

typedef struct _R64InfoKrn
{
    BFBOOL		BoardTest;			// Test flag read from the registry.
	BFBOOL		Stop00All;			// Set True to enable exit after driver builds R2Info.
} R64InfoKrn, *pR64InfoKrn;


// Useful macros to get things out of the device info block.

#define GetR64Info(BoardId) (BoardId == BFNULL ? BFNULL : ((pBFInfoKrn)BoardId)->pXXInfoKrn == BFNULL ? BFNULL : (pR64InfoKrn)((pBFInfoKrn)BoardId)->pXXInfoKrn)

#endif

#endif
