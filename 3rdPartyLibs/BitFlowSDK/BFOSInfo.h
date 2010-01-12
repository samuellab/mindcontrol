//
// Creation:    BFOSInfo.h
// Created:     June 10, 2004
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2004 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// BitFlow driver operating system specific driver information structure.
//
// History:
//
// 06/10/04     rbs     Created file.
//

#if !defined(__BFOSINFO__)
#define __BFOSINFO__

#include "BFWhatSystem.h"

// System Specific Device Info Includes

#if defined(KernelNT) || defined(UserNT)
#include "BFOSInfoNT.h"
#endif

#if defined(KernelLX) || defined(UserLX)
#include "BFOSInfoLX.h"
#endif

#if defined(KernelPT) || defined(UserPT)
#include "BFOSInfoPT.h"
#endif

#endif

