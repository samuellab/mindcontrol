//
// Creation:    BFVersion.h
// Created:     April 13, 2000
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2000 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// BitFlow Driver Version Information
//
// History:
//
// 04/13/00     rbs     Created file.
//

#if !defined(__BFVERSION__)
#define __BFVERSION__

#if !defined(__BFTYPE__)
	#include "BFType.h"
#endif

// Version defines used for BitFlow style version management.

#define BF_SDK_V1						0x05
#define BF_SDK_V2						0x02
#define BF_SDK_V3						0x00
#define BF_SDK_V4						0x00

// Combined version formats. 	

#define BF_SDK_VERSION					(BF_SDK_V1 << 12 | BF_SDK_V2 << 8 | BF_SDK_V3 << 4 | BF_SDK_V4)
#define BF_SDK_VERSION_MINOR			(BF_SDK_V2 << 8 | BF_SDK_V3 << 4 | BF_SDK_V4)			

#define BF_SDK_VERSION_BUG				0x80000000			// Debug versions are denoted by setting highest major bit.

#if defined(_DEBUG)
    #define BF_SDK_VERSION_MAJOR		(BF_SDK_V1 | BF_SDK_VERSION_BUG)
#else
    #define BF_SDK_VERSION_MAJOR		BF_SDK_V1
#endif									  

// Version defines used to build version resources.

#ifdef LINX_BUILD_TARGET

	#define BF_PRODUCT_NAME_STRING			"LinX SDK\0"
	#define BF_LEGAL_COPYRIGHT_STRING		"Copyright © 2008-2009 LinX Corporation\0"
	#define BF_COMPANY_STRING				"LinX Corporation\0"
	#define BF_INTERNAL_NAME				"LinX.sys\0"

#else

	#define BF_PRODUCT_NAME_STRING			"BitFlow SDK\0"
	#define BF_LEGAL_COPYRIGHT_STRING		"Copyright © 1996-2009 BitFlow Inc\0"
	#define BF_COMPANY_STRING				"BitFlow Inc\0"
	#define BF_INTERNAL_NAME				"BitFlow.sys\0"

#endif

#define BF_PRODUCT_VERSION_NUMBERS		5, 2, 0, 0
#define BF_PRODUCT_VERSION_STRING		"5.2.0.0\0"

#define BF_FILE_VERSION_NUMBERS			5, 2, 0,0
#define BF_FILE_VERSION_STRING			"5.2.0.0\0"

#if defined(BuildWinXP)
	#if defined(_DEBUG)
		#define BF_SPECIAL_BUILD_STRING		"Debug PnP\0"
	#else
		#define BF_SPECIAL_BUILD_STRING		"Release PnP\0"
	#endif
#else
	#if defined(_DEBUG)
		#define BF_SPECIAL_BUILD_STRING		"Debug\0"
	#else
		#define BF_SPECIAL_BUILD_STRING		"Release\0"
	#endif
#endif

#endif


