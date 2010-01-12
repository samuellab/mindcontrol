/***************************************************************************
*
* BFSerial.h
*
* BitFlow serial interface API
* 
* Function prototypes
*
* Copyright (C) 2004 by BitFlow, Inc.  All Rights Reserved.
*
* 12/13/2004	sms		created
*
***************************************************************************/
#include "BFDef.h"

#ifndef __BFSERIALH__
#define __BFSERIALH__

#ifndef BFSERIALEXPORT
	#define BFSERIALEXPORT __declspec(dllexport)
#endif

#ifndef BFSERIALCC
	#define BFSERIALCC __cdecl
#endif

/* Serial Reference Structure */
typedef struct _SerRefStruc
{
	Bd			hBoard;
	PBFSIGNAL	pCLReadSignal;		// Used by the clSerialRead function
	PBFSIGNAL	pBFCLReadSignal;	// Used by the BFCLSerialRead function
	BFU32		serialIndex;
		
} SerRefStruc, *pSerRefStruc;

typedef enum _DataBits
{
	DataBits_5 = 0,
	DataBits_6,
	DataBits_7,
	DataBits_8

} DataBits, *DataBitsPtr;

typedef enum _Parity
{
	ParityEven = 0,
	ParityOdd,
	ParityNone,

} Parity, *ParityPtr;

typedef enum _StopBits
{
	StopBits_1 = 0,
	StopBits_15,
	StopBits_2,
	
} StopBits, *StopBitsPtr;

// BitFlow error codes
#define BFCL_ERROR_SERNOTFOUND  -1000	// The serial device was not found
#define BFCL_ERROR_BRDNOTFOUND  -1001	// There are no R2 boards installed
#define BFCL_ERROR_BRDOPEN		-1002	// Error opening board
#define BFCL_ERROR_THRE			-1003	// Transmitter Holding Register not empty (THRE)
#define BFCL_ERROR_TEMT			-1004	// Transmitter not empty (TEMT)
#define BFCL_ERROR_FIFO_EN		-1005	// FIFO's are not enabled
#define BFCL_ERROR_RCVRFIFO		-1006	// Error in RCVR FIFO
#define BFCL_ERROR_BAUDRATE		-1008   // Invalid Buad Rate
#define BFCL_ERROR_DATABITS		-1009	// Invalid number of data bits
#define	BFCL_ERROR_PARITY		-1010	// Invalid parity parameter
#define BFCL_ERROR_15STOP5DATA  -1011	// To use 1.5 number of stop bits, 5 data bits must be used.
#define BFCL_ERROR_2STOP5DATA	-1012	// Can't use 5 data bits with 2 stop bits
#define BFCL_ERROR_STOPBITS		-1013	// Invalid number of stop bits.
#define BFCL_ERROR_NOSIGNAL		-1014	// Can't create signal
#define BFCL_ERROR_NOSTRUC		-1016	// Can't create ref structure
#define BFCL_ERROR_NULLPTR		-1017	// BFNULL pointer
#define BFCL_ERROR_BYTES_AVAIL	-1018	// Error getting the number of bytes available in the buffer
#define BFCL_ERROR_FLUSH_PORT	-1019	// Error flushing the port
#define BFCL_ERROR_DATA_IN		-1020	// The receive buffer could not be emptied

/* WARNINGS */
#define BFCL_WARN_SIG_CANCEL	-1015	// BFSerialRead signal was cancelled

#ifdef __cplusplus
extern "C"{
#endif

BFSERIALEXPORT int BFSERIALCC
clBFSerialSettings(void* serialRef, unsigned int baudRate, 
				 unsigned int dataBits,
				 unsigned int parity,
				 unsigned int stopBits);

BFSERIALEXPORT int BFSERIALCC
clBFSerialRead(void* serialRef, char* buffer, unsigned int* bufferSize );

BFSERIALEXPORT int BFSERIALCC
clBFSerialCancelRead(void* serialRef);

BFSERIALEXPORT int BFSERIALCC
clBFGetBaudRate(void* serialRef, unsigned int* baudRate);

BFSERIALEXPORT int BFSERIALCC
clBFSerialInit(Bd hBoard, void** serialRefPtr);

BFSERIALEXPORT void BFSERIALCC
clBFSerialClose(void* serialRef);

BFSERIALEXPORT int BFSERIALCC
clBFGetSerialRef(unsigned int portNum, void** serRefPtr);

BFSERIALEXPORT BFRC BFSERIALCC 
BFSVersion(PBFU32 pMajorVersion, PBFU32 pMinorVersion);

#ifdef __cplusplus
}
#endif

#endif

