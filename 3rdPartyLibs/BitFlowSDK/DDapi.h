/***************************************************************************
*
* FILE: ddapi.h
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
* 06/30/97	rjd - copy for DDRaw surface
*
***************************************************************************/

#ifndef _DDAPI_
#define _DDAPI_

#include "BFDef.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

BFDLL BOOL BFCAPI DDrawSurfCreate(PBFS32 DDrawSurfHandle,BFU32  dx,BFU32  dy,BFU32 PixDepth,HWND hWndOwner);
BFDLL BOOL BFCAPI DDrawSurfGetBitmap(BFS32 DDrawSurfHandle, PBFVOID *pBitmap, PBFS32 pPitch, PBFU32 pSCreenX, PBFU32 pScreenY);
BFDLL BOOL BFCAPI DDrawSurfTop(BFS32 DDrawSurfHandle);
BFDLL BOOL BFCAPI DDrawSurfBlit(BFS32 DDrawSurfHandle);
BFDLL BOOL BFCAPI DDrawSurfChangeSize(BFS32 DDrawSurfHandle,BFU32  dx,BFU32  dy,BFU32 PixDepth);
BFDLL BOOL BFCAPI DDrawSurfGetLut(BFS32 DDrawSurfHandle, PBFU8  pLut);
BFDLL BOOL BFCAPI DDrawSurfClose(BFS32 DDrawSurfHandle);
BFDLL BOOL BFCAPI DDrawSurfIsOpen(BFS32 DDrawSurfHandle);

BFDLL BOOL BFCAPI DDrawSurfVersion(PBFU32 pMajorVersion,PBFU32 pMinorVersion);

// if the application object is needed in the DLL, call this function to attach

void WINAPI InitDSDLL();

#ifdef __cplusplus
}
#endif

#endif // _DDAPI_
