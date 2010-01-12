/***************************************************************************
*
* R2Config.h
*
* Definitions of data structures to support configuration of RoadRunner system
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* 05/13/96	rjd		creation
* 08/05/99	rjd		modified QTAB model paramters
*
***************************************************************************/

#if !defined(__R2CONFIG__) && !defined(KernelOS)
#define __R2CONFIG__

#include "R2Type.h"
#include "BFEntTrans.h"


// header signature 
#define R2CNF_NREGS			132
/*
* Camera description defines
*/
#define R2CNF_FORM_LINEFORMAT_MASK		0x00000007
#define R2CNF_FORM_NONINTERLACED		0x00000001
#define R2CNF_FORM_DATAFORMAT_MASK		0x00000070
#define R2CNF_FORM_BI_SERIAL			0x00000010	// two serial pixels
#define R2CNF_FORM_TRY_SERIAL			0x00000020	// three serial pixels
#define R2CNF_FORM_QUAD_SERIAL			0x00000040	// four serial pixels



#endif // __R2CONFIG__
