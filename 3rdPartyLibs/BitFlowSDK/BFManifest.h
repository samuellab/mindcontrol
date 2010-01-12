/***************************************************************************
*
* BFManifest.h
*
* Manifest for BitFlow MFC applications
* 
* This file can be included in "stdafx.h" files for MFC applications.
* Note that this file must be included after the standard windows includes.
*
* Copyright (C) 2006 by BitFlow, Inc.  All Rights Reserved.
*
* 11/27/2006	rjd		Create
*
***************************************************************************/

#ifndef __BFMANIFEST__
#define __BFMANIFEST__

// Microsoft includes the manifest only for UNICODE applications
#ifdef _UNICODE 
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

#endif // __BFMANIFEST__