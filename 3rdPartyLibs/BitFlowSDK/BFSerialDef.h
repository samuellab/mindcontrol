/***************************************************************************
*
* BFSerialDef.h
*
* Bitflow serial interface API
* 
* Defines from "clallserial.h" for source files that cannot include "clallserial.h"
*
* Copyright (C) 2004 by BitFlow, Inc.  All Rights Reserved.
*
* 12/13/2004	sms		created
*
***************************************************************************/

#if !defined(__BFSERIALDEF__)
#define __BFSERIALDEF__

// CL Version constants
#define CL_DLL_VERSION_NO_VERSION 1
#define CL_DLL_VERSION_1_0		  2
#define CL_DLL_VERSION_1_1		  3

// CL baud rate constants
#define CL_BAUDRATE_9600		1
#define CL_BAUDRATE_19200		2
#define CL_BAUDRATE_38400		4
#define CL_BAUDRATE_57600		8
#define CL_BAUDRATE_115200		16
#define CL_BAUDRATE_230400		32
#define CL_BAUDRATE_460800		64
#define CL_BAUDRATE_921600		128

// CL Error Codes
#define CL_ERR_NO_ERR					0
#define CL_ERR_BUFFER_TOO_SMALL			-10001
#define CL_ERR_MANU_DOES_NOT_EXIST		-10002
#define CL_ERR_PORT_IN_USE				-10003
#define CL_ERR_TIMEOUT					-10004
#define CL_ERR_INVALID_INDEX			-10005
#define CL_ERR_INVALID_REFERENCE		-10006
#define CL_ERR_ERROR_NOT_FOUND			-10007
#define CL_ERR_BAUD_RATE_NOT_SUPPORTED	-10008
#define CL_ERR_UNABLE_TO_LOAD_DLL		-10098
#define CL_ERR_FUNCTION_NOT_FOUND		-10099


#endif