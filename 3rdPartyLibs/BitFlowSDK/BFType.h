//
// Creation:    BFType.h
// Created:     March 15, 1996
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Description:
//
// BitFlow Driver Public Type Definitions
//
// History:
//
// 03/15/96     rbs     Created file.
//

#if !defined(__BFTYPE__)
#define __BFTYPE__

// this file determines the target build
#include "BuildTarget.h"


#include "BFWhatSystem.h"

// System Specific Types

#if defined(KernelNT) || defined(UserNT)
	#include "BFTypeNT.h"
#endif

#if defined(KernelLX) || defined(UserLX)
	#include "BFTypeLX.h"
#endif

#if defined(KernelPT) || defined(UserPT)
	#include "BFTypePT.h"
#endif

// Non-system Specific Types

#if !defined(True)
    #define True    1
#endif

#if !defined(False)
    #define False   0
#endif

#if !defined(TRUE)
    #define TRUE    1
#endif

#if !defined(FALSE)
    #define FALSE   0
#endif

#if !defined(BFNULL)
    #define BFNULL    0
#endif

#if !defined(MAX_STRING)
    #define MAX_STRING 256
#endif

#if !defined(MIN_STRING)
    #define MIN_STRING 32
#endif

#if !defined(try) && !defined(__cplusplus)
	#define try __try
#endif

#if !defined(except) && !defined(__cplusplus)
	#define except __except
#endif

typedef void ***Bd;             // BitFlow board handle.

#if !defined(RAP_UBER_DRIVER)
	typedef BFU32 BFRC;			// BitFlow return code.
#endif
	
typedef BFRC *BFRC_Ptr;			// BitFlow return code pointer.

typedef PBFVOID PBFCNF;			// Generic camera configuration.

#if !defined(COMPANYREGKEY)

	#ifdef LINX_BUILD_TARGET
		#define COMPANYREGKEY "LinX"
	#else
		#define COMPANYREGKEY "BitFlow"
	#endif

#endif

// Record that holds 64 bit Tick values produced by BFTick.

typedef struct _BFTickRec
{
    BFU32   LowBits;
    BFU32   HighBits;
} BFTickRec, *BFTickPtr;

// Record that holds 64 bit time stamp values.

typedef struct _BFStampRec
{
    BFU32   LowBits;
    BFU32   HighBits;
} BFStampRec, *BFStampPtr;

#endif
