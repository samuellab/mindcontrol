//
// Creation:    R2Type.h
// Created:     June 18, 1996
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// RoadRunner Driver Public Type Definitions
//
// History:
//
// 06/18/96     rbs     Created file.
//

#if !defined(__R2TYPE__)
    #define __R2TYPE__

    #if !defined(__BFTYPE__)
        #include "BFType.h"
    #endif

    #if !defined(R2C)
        #define R2C		BFC
    #endif

	#if !defined(R2DLL)
		#define R2DLL	BFDLL
	#endif 
	
    #if !defined(R2CAPI)
        #define R2CAPI	BFCAPI
    #endif

    typedef Bd			RdRn;				// RoadRunner board handle.

    typedef BFRC		R2RC, *R2RC_Ptr;	// RoadRunner return code.    

	typedef PBFCNF		PR2CAM;				// Configuration specific type for R2 cameras.


#endif

