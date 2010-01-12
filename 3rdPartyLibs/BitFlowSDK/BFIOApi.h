/***************************************************************************
*
* FILE: BFIOApi.h
*
* PURPOSE: Public interface into Disk IO dll
*
* LEGAL THINGS:
*
* Copyright (C) 2002 by BitFlow, Inc.  All Rights Reserved.
*
* REVISION HISTORY:
*
* 10/23/2002	sms - created
*
***************************************************************************/


#ifndef __BFIOAPI__
#define __BFIOAPI__

#include "BFDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// Dialog to specify a file name to save
BFDLL BFU32 BFCAPI BFIOSaveDlg(BFBOOL SingleFrame, char* FileName, BFSIZET FileNameSize);

// write a single file to disk
BFDLL BFU32	BFCAPI BFIOWriteSingle(char* FileName, PBFU32 pBuffer, 
									 BFU32 XSize, BFU32 YSize, 
									 BFU32 BitDepth, BFU32 Options);

// write a sequence of files to disk
BFDLL BFU32	BFCAPI BFIOWriteMultiple(char* FileName, PBFU32 *pBufArray,
					BFU32 StartNum,	BFU32 XSize, BFU32 YSize, 
					BFU32 BitDepth,	BFU32 NumBuffers, BFU32 Options);

// read a single file from disk
BFDLL BFU32	BFCAPI BFIOReadSingle(char* FileName, PBFU32 pBuffer, 
							        BFU32 XSize, BFU32 YSize, BFU32 BitDepth);

// read a sequence of files from disk
BFDLL BFU32	BFCAPI BFIOReadMultiple(char* FileName, PBFU32 *pBufArray,
									  BFU32 XSize, BFU32 YSize, BFU32 BitDepth,
									  BFU32 NumBuffers, BFU32 AVIStartFrame);

// read the parameter info from a file on disk
BFDLL BFU32 BFCAPI BFIOReadParameters(char* FileName, PBFU32 XSize, PBFU32 YSize, 
									  PBFU32 BitDepth, PBFU32 NumFrames);
									  
// Dialog to retreive a file 
BFDLL BFU32	BFCAPI BFIOOpenDlg(char* FileName, BFSIZET FileNameSize);

// Show error code details in a dialog box
BFDLL BFU32 BFCAPI BFIOErrorShow( BFU32 ErrorCode);

// Return the dll version
BFDLL BFRC BFCAPI BFIOVersion(PBFU32 pMajorVersion,PBFU32 pMinorVersion);



#ifdef __cplusplus
}
#endif

#endif /* __BFIOAPI__ */
