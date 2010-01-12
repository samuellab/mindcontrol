//
// Creation:    BFTypePT.h
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

#if !defined(__BFTYPEPT__)
#define __BFTYPEPT__

    #if !defined(BITFLOW_TYPEDEFS)
        #define BITFLOW_TYPEDEFS

        #if !defined(KernelOS)
            typedef char                *PSTRING;
			#define PCIBus 5
        #endif

        typedef void                BFVOID,     *PBFVOID;
        typedef char                BFCHAR,     *PBFCHAR;
        typedef int                 BFBOOL,     *PBFBOOL;
		typedef unsigned int		BFUINT;
		typedef	int					BFSINT;
		typedef unsigned short		BFUSHORT;
		typedef short				BFSSHORT;
		typedef unsigned long		BFULONG;
		typedef long				BFSLONG;
		typedef double				BFDOUBLE;

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
            typedef unsigned int       	BFU32,      *PBFU32;
            typedef int                	BFS32,      *PBFS32;
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

	// If windows set the proper call types.

	#if defined(_MSC_VER) && defined(_WIN32)
		#define MS_Default_C_Call					__cdecl
		#define MS_Win32_API_Call					__stdcall
		#define MS_Shared_Library_Export			__declspec(dllexport)
		#define MS_Shared_Library_Import			__declspec(dllimport)
	#else
		#define MS_Default_C_Call
		#define MS_Win32_API_Call
		#define MS_Shared_Library_Export
		#define MS_Shared_Library_Import
	#endif

	#if !defined(BFDLL)
		#if defined(KernelOS)
			#define BFDLL extern
		#elif defined(INDLL) || defined(_WINDLL)
			#define BFDLL MS_Shared_Library_Export
		#else
			#define BFDLL MS_Shared_Library_Import
		#endif
	#endif 
	
	#if !defined(BFCDECL)
		#define BFCDECL		MS_Default_C_Call	
	#endif

	#if !defined(BFSTDCALL)
		#define BFSTDCALL	MS_Win32_API_Call
	#endif
		
    #if !defined(BFCAPI)
        #define BFCAPI		BFSTDCALL
    #endif

	#if !defined(strnicmp)
		#define strnicmp strncmp
	#endif

	//#if !defined(stricmp)
	//	#define stricmp strcmp
	//#endif
	
	// Disable exception handling stuff.
	
	#if !defined(try)
		#define try
	#endif

	#if !defined(except)
		#define except(a) if(a)
	#endif

#endif

