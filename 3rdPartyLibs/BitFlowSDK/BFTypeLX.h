//
// Creation:    BFTypeLX.h
// Created:     June 6, 2001
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2001 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Description:
//
// BitFlow Driver Public Type Definitions
//
// History:
//
// 06/06/01     rbs     Created file.
//

#if !defined(__BFTYPELX__)
#define __BFTYPELX__

    #if !defined(BITFLOW_TYPEDEFS)
        #define BITFLOW_TYPEDEFS

        #if !defined(KernelOS)
            typedef char                *PSTRING;
			#define PCIBus 5
        #endif

        typedef void                BFVOID,     *PBFVOID;
        typedef char                BFCHAR,     *PBFCHAR;
        typedef int                 BFBOOL,     *PBFBOOL;

        #if defined(_MSC_VER)
            typedef unsigned __int32    BFU32,      *PBFU32;
            typedef __int32             BFS32,      *PBFS32;
            typedef unsigned __int16    BFU16,      *PBFU16;
            typedef __int16             BFS16,      *PBFS16;
            typedef unsigned __int8     BFU8,       *PBFU8;
            typedef __int8              BFS8,       *PBFS8;
        #else
            typedef unsigned long       BFU32,      *PBFU32;
            typedef long                BFS32,      *PBFS32;
            typedef unsigned short      BFU16,      *PBFU16;
            typedef short               BFS16,      *PBFS16;
            typedef unsigned char       BFU8,       *PBFU8;
            typedef char                BFS8,       *PBFS8;
        #endif

		typedef BFU16				BFWCHAR,	*PBFWCHAR;
    #endif

    #if !defined(BFC)
        #define BFC
    #endif

	#if !defined(BFDLL)
		#if defined(KernelOS)
			#define BFDLL extern
		#elif defined(INDLL)
			#define BFDLL __declspec(dllexport)
		#else
			#define BFDLL __declspec(dllimport)
		#endif
	#endif 
	
	#if !defined(BFCDECL)
		#define BFCDECL		__cdecl
	#endif

	#if !defined(BFSTDCALL)
		#define BFSTDCALL	__stdcall
	#endif
		
    #if !defined(BFCAPI)
        #define BFCAPI		BFSTDCALL
    #endif

#endif

