/***************************************************************************
*
* FILE: BDapi.h
*
* PURPOSE: Public interface into Display Surface DLL
*
* LEGAL THINGS:
*
* Copyright (C) 1994 by BitFlow, Inc.  All Rights Reserved.
*
* REVISION HISTORY:
*
* 07/11/96	rjd - stolen from RAptor SDK DSDLL
* 06/30/97	rjd - copy from disp surface
* 07/21/97	rjd - copy from DDRAW
*
***************************************************************************/

#ifndef _BDAPI_
#define _BDAPI_

#include "BFDef.h"

#ifdef __cplusplus			 
extern "C" {
#endif  /* __cplusplus */

BFDLL BOOL BFCAPI BitDirectSurfCreate(PBFS32 pBitDirectSurfHandle,BFU32 dx,BFU32 dy,BFU32 PixDepth,HWND hWndOwner,Bd hBoard);
BFDLL BOOL BFCAPI BitDirectSurfTop(BFS32 BitDirectSurfHandle);
BFDLL BOOL BFCAPI BitDirectSurfGetLut(BFS32 BitDirectSurfHandle, PBFU8  pLut);
BFDLL BOOL BFCAPI BitDirectSurfClose(BFS32 BitDirectSurfHandle);
BFDLL BOOL BFCAPI BitDirectSurfIsOpen(BFS32 BitDirectSurfHandle);
BFDLL BOOL BFCAPI BitDirectSurfGetDisplayQTab(BFS32 BitDirectSurfHandle, RQTabHeadPtr *pDispQTabHead);

BFDLL BOOL BFCAPI BitDirectSurfVersion(PBFU32 pMajorVersion,PBFU32 pMinorVersion);

// if the application object is needed in the DLL, call this function to attach
void WINAPI InitDSDLL();

#ifdef __cplusplus
}
#endif

#endif // _BDAPI_
