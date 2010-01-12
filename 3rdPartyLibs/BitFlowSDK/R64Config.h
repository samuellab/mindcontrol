/***************************************************************************
*
* R64Config.h
*
* Definitions of data structures to support configuration of R64 system
*
* Copyright (C) 2002 by BitFlow, Inc.  All Rights Reserved.
*
* 05/29/02	rbs		Cloned from R2Config.h.
*
***************************************************************************/

#if !defined(__R64CONFIG__) && !defined(KernelOS)
#define __R64CONFIG__

#include "R64Type.h"
#include "BFEntTrans.h"


// header signature 
#define R64CNF_NREGS			132


/*
* Camera description defines
*/
#define R64CNF_FORM_LINEFORMAT_MASK		0x00000007
#define R64CNF_FORM_NONINTERLACED		0x00000001
#define R64CNF_FORM_DATAFORMAT_MASK		0x00000070
#define R64CNF_FORM_BI_SERIAL			0x00000010	// two serial pixels
#define R64CNF_FORM_TRY_SERIAL			0x00000020	// three serial pixels
#define R64CNF_FORM_QUAD_SERIAL			0x00000040	// four serial pixels


#endif // __R64CONFIG__
