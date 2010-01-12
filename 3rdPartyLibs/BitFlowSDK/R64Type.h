//
// Creation:    R64Type.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// R64 Driver Public Type Definitions
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__R64TYPE__)
    #define __R64TYPE__

    #if !defined(__BFTYPE__)
        #include "BFType.h"
    #endif

    #if !defined(R64C)
        #define R64C	BFC
    #endif

	#if !defined(R64DLL)
		#define R64DLL	BFDLL
	#endif 
	
    #if !defined(R64CAPI)
        #define R64CAPI	BFCAPI
    #endif

    typedef Bd			R64;				// R64 board handle.

    typedef BFRC		R64RC, *R64RC_Ptr;	// R64 return code.    

	typedef PBFCNF		PR64CAM;			// Configuration specific type for R64 cameras.


#endif

