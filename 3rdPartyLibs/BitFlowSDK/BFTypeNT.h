//
// Creation:    BFTypeNT.h
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
#include "basetsd.h"
#include "stddef.h"

#if !defined(__BFTYPENT__)
#define __BFTYPENT__

    #if !defined(BITFLOW_TYPEDEFS)
        #define BITFLOW_TYPEDEFS

        #if !defined(KernelOS)
            typedef char                *PSTRING;
			#define PCIBus 5
        #endif

        typedef void                BFVOID,     *PBFVOID;
        typedef char                BFCHAR,     *PBFCHAR;
        typedef int                 BFBOOL,     *PBFBOOL;
		typedef unsigned int		BFUINT,		*PBFUINT;
		typedef	int					BFSINT,		*PBFSINT;
		typedef unsigned short		BFUSHORT,	*PBFUSHORT;
		typedef short				BFSSHORT,	*PBFSSHORT;
		typedef unsigned long		BFULONG,	*PBFULONG;
		typedef long				BFSLONG,	*PBFSLONG;
		typedef double				BFDOUBLE,	*PBFDOUBLE;

       #if defined(_MSC_VER)
			typedef unsigned __int64    BFU64,      *PBFU64;
			typedef __int64             BFS64,      *PBFS64;
            typedef unsigned __int32    BFU32,      *PBFU32;
            typedef __int32             BFS32,      *PBFS32;
            typedef unsigned __int16    BFU16,      *PBFU16;
            typedef __int16             BFS16,      *PBFS16;
            typedef unsigned __int8     BFU8,       *PBFU8;
            typedef __int8              BFS8,       *PBFS8;
        #else
			typedef unsigned long long	BFU64,      *PBFU64;
			typedef long long       	BFS64,      *PBFS64;
            typedef unsigned long       BFU32,      *PBFU32;
            typedef long                BFS32,      *PBFS32;
            typedef unsigned short      BFU16,      *PBFU16;
            typedef short               BFS16,      *PBFS16;
            typedef unsigned char       BFU8,       *PBFU8;
            typedef char                BFS8,       *PBFS8;
        #endif

		typedef BFU16				BFWCHAR,	*PBFWCHAR;

		// BFUPTR is used when storing a pointer in an integer
		// and accounts for the pointer size of the machine.

		#if (501 < __midl)
			typedef unsigned __int3264	BFUPTR,		*PBFUPTR;	
		#else
			typedef UINT_PTR				BFUPTR,		*PBFUPTR;
			typedef INT_PTR					BFSPTR,		*PBFSPTR;
			typedef size_t					BFSIZET,	*PBFSIZET;
		#endif

    #endif

    #if !defined(BFC)
        #define BFC
    #endif

	#if !defined(BFDLL)
		#if defined(KernelOS)
			#define BFDLL extern
		#elif defined(INDLL)|| defined(_WINDLL)
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
        #define BFCAPI		BFCDECL
    #endif

	#if defined(KernelOS) && !defined(_DEBUG) && defined(DBG) && DBG == 1
		#define _DEBUG
	#endif

	#if !defined(strnicmp)
		#define strnicmp _strnicmp
	#endif

	//#if !defined(stricmp)
	//	#define stricmp _stricmp
	//#endif

#endif

