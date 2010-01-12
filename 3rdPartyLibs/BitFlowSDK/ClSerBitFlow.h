/***************************************************************************
*
* ClSerBitflow.h
*
* Camera Link API
* 
* Function prototypes
*
* Copyright (C) 2001 by BitFlow, Inc.  All Rights Reserved.
*
* 01/04/2001	sms		created
*
***************************************************************************/
#include "BFDef.h"
#include "BFSerialDef.h"
#include "BFSerial.h"


#ifndef __CLSERBITFLOWH__
#define __CLSERBITFLOWH__

#ifndef CLSERBITFLOWEXPORT
	#define CLSERBITFLOWEXPORT __declspec(dllexport)
#endif

#ifndef CLSERBITFLOWCC
	#define CLSERBITFLOWCC __cdecl
#endif


#ifdef __cplusplus
extern "C"{
#endif

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clFlushPort(void* serialRef);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clGetErrorText(int errorCode, char* errorText, unsigned int* errorTextSize);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clGetManufacturerInfo(char* ManufacturerName, unsigned int* bufferSize, 
					  unsigned int* version);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clGetNumBytesAvail(void* serialRef, unsigned int* numBytes);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clGetNumSerialPorts(unsigned int* numSerialPorts);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clGetSerialPortIdentifier(unsigned int serialIndex, char* portID, 
						  unsigned int* bufferSize);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clGetSupportedBaudRates(void* serialRef, unsigned int* baudRates);

CLSERBITFLOWEXPORT void CLSERBITFLOWCC
clSerialClose(void* serialRef);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clSerialInit(unsigned int serialIndex, void** serialRefPtr);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clSerialRead(void* serialRef, char* buffer, unsigned int* bufferSize,
			 unsigned int serialTimeout);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clSerialWrite(void* serialRef, char* buffer, unsigned int* bufferSize,
			  unsigned int serialTimeout);

CLSERBITFLOWEXPORT int CLSERBITFLOWCC
clSetBaudRate(void* serialRef, unsigned int baudRate);

CLSERBITFLOWEXPORT void* CLSERBITFLOWCC
GetSerialRef(unsigned int portNum);

#ifdef __cplusplus
}
#endif

#endif

// Support fuctions
BFU32 UARTInit(Bd Board);
