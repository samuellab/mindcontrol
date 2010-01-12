//
// Creation:    BFRunTimeBth.h
// Created:     January 24, 2006
// Creator:     Stephen Sheedy
//
// Copyright (C) 1993-2006 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Run Time Functions
//
// Function prototypes for run time functions.
//
// History:
//
// 01/24/2006     sms     Created file.
//

#if !defined(__BFRUNTIMEBTH__)
#define __BFRUNTIMEBTH__

// errors
#define BFRUNTIME_ERROR		-1

#ifdef __cplusplus
extern "C" {
#endif


BFDLL  BFS32	BFC BFkbhit();
BFDLL  BFS32	BFC BFgetch();
BFDLL  BFU32	BFC BFsprintf(BFCHAR *Dest, BFSIZET DestSize, const BFCHAR *Format, ...);
BFDLL  BFU32	BFC BFstrcat(BFCHAR *Dest, BFSIZET DestSize, const BFCHAR *Source);
BFDLL  BFU32	BFC BFstrncpy(BFCHAR *Dest, BFSIZET DestSize, const BFCHAR *Source, BFSIZET Count);
BFDLL  BFU32	BFC BFstrcpy(BFCHAR *Dest, BFSIZET DestSize, const BFCHAR *Source);
BFDLL  BFS32	BFC BFsscanf32(const BFCHAR *Buffer, const BFCHAR *Format, PBFU32 value);
BFDLL  BFU32	BFC BFvsprintf(BFCHAR *Dest, BFSIZET DestSize, const BFCHAR *Format, va_list TheArgs);
BFDLL  BFS32	BFC BFstricmp(const BFCHAR *String1, const BFCHAR *String2);

#ifdef __cplusplus
}
#endif

#endif