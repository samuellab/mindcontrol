//
// Creation:    BFSystem.h
// Created:     May 11, 2001
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// BitFlow driver operating system specific definitions.
//
// History:
//
// 05/11/01     rbs     Created file.
//

#if !defined(__BFSYSTEM__)
#define __BFSYSTEM__

#include "BFWhatSystem.h"

// System Specific System Includes

#if defined(KernelNT) || defined(UserNT)
	#include "BFSystemNT.h"
#endif

#if defined(KernelLX) || defined(UserLX)
	#include "BFSystemLX.h"
#endif

#if defined(KernelPT) || defined(UserPT)
#	include "BFSystemPT.h"
#endif

#endif

