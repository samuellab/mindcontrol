//
// Creation:    BFSystemNT.h
// Created:     May 11, 2001
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// BitFlow driver Windows NT operating system specific definitions.
//
// History:
//
// 05/11/01     rbs     Created file.
//

#if !defined(__BFSYSTEMNT__)
#define __BFSYSTEMNT__

#if defined(KernelNT)

	//
	// Windows NT Kernel Level Includes
	//

	#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers.

	#if !defined(_NTDDK_)
	#include <NTDDK.h>
	#endif

	#if !defined(_INC_STDARG)
	#include <StdArg.h>
	#endif

	#if !defined(_INC_STDIO)
	#include <StdIO.h>
	#endif

	#if !defined(_INC_STRING)
	#include <String.h>
	#endif

	#if !defined(_INC_CTYPE)
	#include <CType.h>
	#endif

	#if !defined(_INC_LIMITS)
	#include <Limits.h>
	#endif

	//#if !defined(_INC_NTSTRSAFE)
	//#include <ntstrsafe.h>
	//#endif

#endif	// KernelNT

#if defined(UserNT)		 

	#define VC_EXTRALEAN        // Exclude rarely-used stuff from Windows headers.

	//
	// Windows NT User Level Includes
	//

	#if !defined(_WINDOWS_)
	#include <Windows.h>
	#endif

	#if !defined(_INC_TIME)
	#include <Time.h>
	#endif

	#if !defined(_INC_STDIO)
	#include <StdIo.h>
	#endif

	#if !defined(_INC_STDLIB)
	#include <StdLib.h>
	#endif

	#if !defined(_INC_STRING)
	#include <String.h>
	#endif

	#if !defined(_INC_PROCESS)
	#include <Process.h>
	#endif

	#if !defined(_WINIOCTL_)
	#include <WinIoCtl.h>
	#endif

	#if !defined(_INC_CRTDBG) 
	#include <CrtDbg.h>
	#endif

	#if !defined(_INC_DIRECT) 
	#include <Direct.h>
	#endif

	#if !defined(_INC_IO) 
	#include <IO.h>
	#endif

#endif	// UserNT

#endif






