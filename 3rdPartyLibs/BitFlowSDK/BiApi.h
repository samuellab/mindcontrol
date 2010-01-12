/***************************************************************************
*
* BIApi.h
*
* BufIn API
* 
* Function prototypes
*
* Copyright (C) 1999 by BitFlow, Inc.  All Rights Reserved.
*
* 06/25/99  sms		Create
*
***************************************************************************/

#ifndef __BIAPI__
#define __BIAPI__


#include "BFDef.h"
#include "BiDef.h"
#include "BiError.h"

#ifdef __cplusplus
extern "C" {
#endif


/* Board */
BFDLL BFRC		BFCAPI BiBrdOpen(BFU32 BrdType, BFU32 BrdNumber, Bd *pBrdHandle);
BFDLL BFRC		BFCAPI BiBrdOpenEx(BFU32 BrdType, BFU32 BrdNumber, Bd *pBrdHandle, BFU32 Options);
BFDLL BFRC		BFCAPI BiBrdOpenCam(BFU32 BrdType, BFU32 BrdNumber, Bd *pBrdHandle, PBFCHAR ForceCamFile);
BFDLL BFRC		BFCAPI BiBrdInquire(Bd Board, BFU32 InquireVar, PBFU32 Val);
BFDLL BFRC		BFCAPI BiBrdClose(Bd Board);

/* Memory Allocation */
BFDLL BFRC		BFCAPI BiBufferAllocCam(Bd Board, PBIBA pBufArray, BFU32 NumBuffers);
BFDLL BFRC		BFCAPI BiBufferAllocAlignedCam(Bd Board, PBIBA pBufArray, BFU32 NumBuffers, BFSIZET Alignment);
BFDLL BFRC		BFCAPI BiBufferAlloc(Bd Board, PBIBA pBufArray, BFU32 XSize, BFU32 YSize, BFU32 PixDepth, BFU32 NumBuffers);
BFDLL BFRC		BFCAPI BiBufferAllocAligned(Bd Board, PBIBA pBufArray, BFU32 XSize, BFU32 YSize, BFU32 PixDepth, BFU32 NumBuffers, BFSIZET Alignment);
BFDLL BFRC		BFCAPI BiBufferAssign(Bd Board, PBIBA pBufArray, PBFU32 *pMemArray, BFU32 NumBuffers);
BFDLL BFRC		BFCAPI BiBufferFree(Bd Board, PBIBA pBufArray);
BFDLL BFRC		BFCAPI BiBufferUnassign(Bd Board, PBIBA pBufArray);
BFDLL BFRC		BFCAPI BiBufferArrayGet(Bd Board, PBIBA pBufArray, PBFU32 **BufferArry);
BFDLL BFRC		BFCAPI BiBufferClear(Bd Board, PBIBA pBufArray);

/* Acquisition */
BFDLL BFRC		BFCAPI BiSeqAqSetup(Bd Board, PBIBA pBufArray, BFU32 Options);
BFDLL BFRC		BFCAPI BiCircAqSetup(Bd Board, PBIBA pBufArray, BFU32 ErrorMode, BFU32 Options);
BFDLL BFRC		BFCAPI BiSeqCleanUp(Bd Board, PBIBA pBufArray);
BFDLL BFRC		BFCAPI BiCircCleanUp(Bd Board, PBIBA pBufArray);

/* Sequence Capture Management */
BFDLL BFRC		BFCAPI BiSeqParameters(Bd Board, PBIBA pBufArray, BFU32 StartFrame, BFU32 NumFrames, BFU32 SkipFrames);
BFDLL BFRC		BFCAPI BiSeqWaitDone(Bd Board, PBIBA pBufArray, BFU32 Timeout);
BFDLL BFRC		BFCAPI BiSeqControl(Bd Board, PBIBA pBufArray, BFU32 Command, BFU32 Options);
BFDLL BFRC		BFCAPI BiSeqErrorWait(Bd Board, PBIBA pBufArray);
BFDLL BFRC		BFCAPI BiSeqErrorCheck(Bd Board, PBIBA pBufArray);
BFDLL BFRC		BFCAPI BiSeqStatusGet(Bd Board, PBIBA pBufArray, PBFU32 Frame);
BFDLL BFRC		BFCAPI BiSeqWaitDoneFrame(Bd Board, PBIBA pBufArray, BFU32 TimeOut);
BFDLL BFRC		BFCAPI BiSeqBufferStatus(Bd Board, PBIBA pBufArray, BFU32 BufferNumber, PBiSeqInfo BufferInfo);
BFDLL BFRC		BFCAPI BiSeqBufferStatusClear(Bd Board, PBIBA pBufArray);

/* Circular Capture Management */
BFDLL BFRC		BFCAPI BiCirControl(Bd Board, PBIBA pBufArray, BFU32 Command, BFU32 Options);
BFDLL BFRC		BFCAPI BiCirErrorWait(Bd Board, PBIBA pBufArray);
BFDLL BFRC		BFCAPI BiCirErrorCheck(Bd Board, PBIBA pBufArray);
BFDLL BFRC		BFCAPI BiCirWaitDoneFrame(Bd Board, PBIBA pBufArray, BFU32 Timeout, PBiCirHandle CirHandle);
BFDLL BFRC		BFCAPI BiCirStatusSet(Bd Board, PBIBA pBufArray, BiCirHandle CirHandle, BFU32 Status);
BFDLL BFRC		BFCAPI BiCirBufferStatusSet(Bd Board, PBIBA pBufArray, BFU32 BufferNumber, BFU32 Status);
BFDLL BFRC		BFCAPI BiCirStatusGet(Bd Board, PBIBA pBufArray, BiCirHandle CirHandle, PBFU32 Status);
BFDLL BFRC		BFCAPI BiCirBufferStatusGet(Bd Board, PBIBA pBufArray, BFU32 BufferNumber, PBFU32 Status);
BFDLL BFRC		BFCAPI BiCirBufferSetNext(Bd Board, PBIBA pBufArray, BFU32 BufferNumber);
BFDLL BFRC		BFCAPI BiCirBufferAdd(Bd Board, PBIBA pBufArray, BFU32 NumBuffer);

/* Trigger */
BFDLL BFRC		BFCAPI BiTrigModeSet(Bd Board, BFU32 TriggerMode, BFU32 TrigPolarity);
BFDLL BFRC		BFCAPI BiTrigModeGet(Bd Board, PBFU32 TriggerMode, PBFU32 TrigPolarity);
BFDLL BFRC		BFCAPI BiTrigForce(Bd Board, BFU32 Mode);

/* Error */
BFDLL BFRC		BFCAPI BiErrorShow(Bd Board, BFRC ErrorNum);
BFDLL BFRC		BFCAPI BiErrorTextGet(Bd Board, BFRC ErrorNum, PBFCHAR ErrorText, PBFU32 ErrorTextSize);
BFDLL BFRC		BFCAPI BiErrorList();

/* Buffer Disk I/O Functions */
BFDLL BFRC		BFCAPI BiDiskBufWrite(Bd Board, PBIBA pBufArray, BFU32 FirstBufNumber, BFU32 NumBufs, PBFCHAR FileName, BFSIZET FileNameSize, BFU32 Options);
BFDLL BFRC		BFCAPI BiDiskBufRead(Bd Board, PBIBA pBufArray, BFU32 FirstBufNumber, BFU32 NumBufs, PBFCHAR FileName);
BFDLL BFRC		BFCAPI BiDiskParamRead(Bd Board, PBFCHAR FileName, PBFU32 XSize, PBFU32 YSize, PBFU32 PixDepth, PBFU32 NumFrames);

/* Misc */
BFDLL BFRC		BFCAPI BiControlStatusGet(Bd Board, PBIBA pBufArray, PBFBOOL Start, PBFBOOL Stop, PBFBOOL Abort, PBFBOOL Pause, PBFBOOL Cleanup);
BFDLL BFRC		BFCAPI BiCaptureStatusGet(Bd Board, PBIBA pBufArray, PBFU32 Captured, PBFU32 Missed); 
BFDLL BFRC		BFCAPI BiDVersion(PBFU32 pMajorVersion,PBFU32 pMinorVersion);
BFDLL BFRC		BFCAPI BiBufferQueueSize(Bd Board, PBIBA pBufArray, PBFU32 NumFrames);
BFDLL BFRC		BFCAPI BiInternalTimeoutSet(Bd Board, PBIBA pBufArray, BFU32 TimeoutValue);

/* Camera Configuration */
BFDLL BFRC		BFCAPI BiCamOpen(Bd Board, PBIBA pBufArray, PCHAR CamName, PBFCNF *pCam);
BFDLL BFRC		BFCAPI BiCamClose(Bd Board, PBIBA pBufArray, PBFCNF pCam);
BFDLL BFRC		BFCAPI BiCamSel(Bd Board, PBIBA pBufArray, BFU32 CamIndex, BFU32 Mode);
BFDLL BFRC		BFCAPI BiCamGetCur(Bd Board, PBIBA pBufArray, PBFCNF *pCam);
BFDLL BFRC		BFCAPI BiCamSetCur(Bd Board, PBIBA pBufArray, PBFCNF pCam, BFU32 Mode);
BFDLL BFRC		BFCAPI BiCamGetFileName(Bd Board, PBIBA pBufArray, BFU32 Num, PBFCHAR CamName);


/* DLL only functions. */
BFDLL BFRC	BFCAPI BiInqParameterSet(Bd Board, PBFU32 InquireVar);
BFRC BFCAPI AllocateErrorStack(PBIBA pBufArray);

#ifdef __cplusplus
}
#endif

#endif /* __BIAPI__ */