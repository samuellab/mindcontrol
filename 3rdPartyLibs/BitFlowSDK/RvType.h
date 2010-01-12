//
// Creation:    RvType.h
// Created:     June 18, 1996
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Raven Driver Public Type Definitions
//
// History:
//
// 06/18/96     rbs     Created file.
//

#if !defined(__RVTYPE__)
    #define __RVTYPE__

    #if !defined(__BFTYPE__)
        #include "BFType.h"
    #endif

    #if !defined(RVC)
        #define RVC		BFC
    #endif

	#if !defined(RVDLL)
		#define RVDLL	BFDLL
	#endif 

    #if !defined(RVCAPI)
        #define RVCAPI	BFCAPI
    #endif

    typedef Bd			Raven;				// Raven board handle.

    typedef BFRC		RVRC, *RVRC_Ptr;	// Raven return code.    

	typedef PBFCNF		PRVCAM;				// Configuration specific type for Rv cameras.

#endif

