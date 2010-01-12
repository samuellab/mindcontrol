
// Creation:    R2CamStd.h
// Created:     March 15, 1999
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// Precompiled Header Include File for R2Cam
//
// History:
//
// 3/15/99		rbs		Created. 
// 		 

//
// System Includes
//

#define VC_EXTRALEAN			// Exclude rarely-used stuff from Windows headers.

#if !defined(_WINDOWS_)
#include <Windows.h>
#endif

//
// BF Driver Includes
//

#if !defined(__BFAPI__)
#include "BFApi.h"
#endif

#if !defined(__BFAPIPRV__)
#include "BFApiPrv.h"
#endif

//
// R2 Driver Includes
//

#if !defined(__R2CAMAPI__)
#include "R2CamApi.h"
#endif

#if !defined(__R2API__)
#include "R2Api.h"
#endif

#if !defined(__R2APIPRV__)
#include "R2ApiPrv.h"
#endif

#if !defined(__R2INFO__)
#include "R2Info.h"
#endif



