/***************************************************************************
*
* FILE: BFIO.h
*
* PURPOSE: Support fucnctios for the Disk IO dll
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


#ifndef __BFIO__
#define __BFIO__

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

// support functions.
BFBOOL CheckParams(std::string FileName, PBFU32 BufferArray, BFU32 NumBuffers, 
				   BFU32 XSize, BFU32 YSize, BFU32 BitDepth, BFU32 Options);


BFU32 SaveBMP(std::string FileName,	PBFU32 pBuffer, BFU32 XSize, 
				BFU32 YSize, BFU32 BitDepth, BFU32 Options);

BFU32 ReadBMP(std::string FileName, PBFU32 pBuffer, BFU32 XSize, BFU32 YSize, 
			  BFU32 BitDepth);



BFU32 SaveTiff(std::string FileName, PBFU32 pBuffer, BFU32 XSize, 
				BFU32 YSize, BFU32 BitDepth, BFU32 Options);

BFU32 ReadTiff(std::string FileName, PBFU32 pBuffer, BFU32 XSize, BFU32 YSize, 
			   BFU32 BitDepth);



BFU32 SaveRaw(std::string FileName,	PBFU32 pBuffer, BFU32 XSize, 
				BFU32 YSize, BFU32 BitDepth, BFU32 Options);

BFU32 ReadRawImage(std::string FileName, PBFU32 pBuffer, BFU32 XSize, BFU32 YSize, 
			  BFU32 BitDepth);

BFU32 WriteRawTextInfo(std::string FileName, BFU32 XSize, BFU32 YSize, 
					   BFU32 BitDepth);



BFU32 SaveAVI(std::string FileName, PBFU32 *pBuffer, BFU32 XSize, BFU32 YSize, 
				BFU32 BitDepth, BFU32 NumBuffers, BFU32 Options);

BFU32 ReadAVI(std::string FileName, PBFU32 *pBuffer, BFU32 XSize, BFU32 YSize, 
				BFU32 BitDepth, BFU32 NumBuffers, BFU32 StartNum);

BFU32 CreateDIBHeader(LPBITMAPINFO *pBitmapInfo, PBFU32 BitmapInfoSize,
					  BFU32 XSize, BFU32 YSize, BFU32 BitDepth);

void FreeDIBHeader(LPBITMAPINFO pBitmapInfo);

BFBOOL FileExist(std::string FileName);

#ifdef __cplusplus
}
#endif

#endif /* __BFIO__ */
