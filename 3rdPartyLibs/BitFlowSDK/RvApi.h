/***************************************************************************
*
* RvApi.h
*
* Header file for New Rv Kernel driver API for Windows NT.
* This should/will be the only interface to the kernel for both Rv
* and BF libraries. This eventually should be in its own DLL.
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* 03/06/96	rjd		created
*
***************************************************************************/

#ifndef __RVAPI__
#define __RVAPI__

#include "BFDef.h"
#include "RvType.h"
#include "RvDef.h"
#include "RvBoard.h"
#include "RvTabError.h"
#include "RvConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(KernelOS)

// System Open and Initialization

RVDLL RVRC		RVCAPI RvSysBoardFindByNum(BFU32 Number, PBFENTRY pEntry);
RVDLL RVRC		RVCAPI RvBrdOpen(PBFENTRY pEntry, Raven *pBoard, BFU32 Mode);
RVDLL RVRC	    RVCAPI RvBrdCamSel(Raven Board, BFU32 CamIndex, BFU32 Mode);
RVDLL RVRC	    RVCAPI RvBrdCamSetCur(Raven pBoard, PRVCAM pCam, BFU32 Mode);
RVDLL RVRC	    RVCAPI RvBrdInquire(Raven Board, BFU32 Member, PBFU32 pVal);
RVDLL RVRC		RVCAPI RvBrdClose(Raven Board);
RVDLL RVRC		RVCAPI RvBrdAqTimeoutSet(Raven Board, BFU32 Timeout);
RVDLL RVRC	    RVCAPI RvBrdAqSigGetCur(Raven Board, PBFVOID *pAqSig, BFU32 AqEngine);
RVDLL RVRC	    RVCAPI RvBrdAqSigSetCur(Raven pBoard, PBFVOID pAqSig, BFU32 AqEngine);
RVDLL RVRC		RVCAPI RvBrdCamGetFileName(Raven Board, BFU32 Num, PBFCHAR CamName);

RVDLL RVRC	    RVCAPI RvBrdCamGetCur(Raven Board, PRVCAM *pCam);

RVDLL RVRC		RVCAPI RvDrvOpen(Raven *pBoard);
RVDLL RVRC		RVCAPI RvDrvClose(Raven Board);

// Acquisition

RVDLL RVRC	    RVCAPI RvAqSetup(Raven Board, PBFVOID pDest, BFU32 DestSize, BFS32 Stride, BFU32 LutBank, BFU8 QuadBank, BFBOOL FirstBank, BFU32 QTabMode, BFU32 AqEngine);
RVDLL RVRC	    RVCAPI RvAqCommand(Raven Board, BFU32 Command, BFU32 Mode, BFU8 QuadBank, BFU32 AqEngine);
RVDLL RVRC	    RVCAPI RvAqCleanUp(Raven Board, BFU32 AqEngine);
RVDLL RVRC	    RVCAPI RvAqWaitDone(Raven Board, BFU32 AqEngine);
RVDLL RVRC	    RVCAPI RvAqNextBankSet(Raven Board, BFU8 QuadBank, BFU32 AqEngine);

RVDLL RVRC		RVCAPI RvAqFrameSize(Raven Board, BFU32 XSize, BFU32 YSize, BFU32 AqEngine);
RVDLL RVRC		RVCAPI RvAqROISet(Raven Board, BFU32 XOffset, BFU32 YOffset, BFU32 XSize, BFU32 YSize, BFU32 AqEngine);


// Camera Configuration

RVDLL RVRC	    RVCAPI RvCamOpen(Raven Board, PBFCHAR CamName, PRVCAM *pCam);
RVDLL RVRC	    RVCAPI RvCamInquire(Raven Board, PRVCAM pCam, BFU32 Member, PBFU32 pVal);
RVDLL RVRC	    RVCAPI RvCamClose(Raven Board, PRVCAM pCam);
RVDLL RVRC		RVCAPI RvCamAqTimeoutSet(Raven Board, PRVCAM pCam, BFU32 Timeout);

// Signal Functions

RVDLL RVRC		RVCAPI RvSignalCreate(Raven Board, BFU32 Type, PRVSIGNAL pSignal);
RVDLL RVRC		RVCAPI RvSignalWait(Raven Board, PRVSIGNAL pSignal, BFU32 TimeOut, PBFU32 pNumInts);
RVDLL RVRC		RVCAPI RvSignalNextWait(Raven Board, PRVSIGNAL pSignal, BFU32 TimeOut);
RVDLL RVRC		RVCAPI RvSignalCancel(Raven Board, PRVSIGNAL pSignal);
RVDLL RVRC		RVCAPI RvSignalQueueSize(Raven Board, PRVSIGNAL pSignal,PBFU32 pNumInts);
RVDLL RVRC	    RVCAPI RvSignalQueueClear(Raven Board, PRVSIGNAL pSignal);
RVDLL RVRC		RVCAPI RvSignalFree(Raven Board, PRVSIGNAL pSignal);

// Quad Table Functions

RVDLL RVRC	    RVCAPI RvRelQTabCreate(Raven Board, PRVCAM pCam, PBFVOID pDest, BFU32 BufferSize, BFS32 Stride, RQTabHeadPtr pRelQTabHead, BFU32 LutBank, BFU32 Options, BFU32 AqEngine);
RVDLL RVRC	    RVCAPI RvRelQTabFree(Raven Board, RQTabHeadPtr pRelQTabHead);
RVDLL RVRC	    RVCAPI RvRelQTabCreateRoi(Raven Board, PRVCAM pCam, PBFVOID pDest, BFU32 BufferSize, BFS32 Stride, RQTabHeadPtr pRelQTabHead, BFU32 LutBank, BFU32 Options, BFU32 DestX, BFU32 DestY, BFU32 DestDx, BFU32 DestDy, BFU32 AqEngine);

// Mid Level Control Functions

RVDLL RVRC		RVCAPI RvConAqCommand(Raven Board, BFU32 Command, BFU32 AqEngine);
RVDLL RVRC		RVCAPI RvConSwTrigStat(Raven Board, BFU32 BFTrig, PBFU32 Status );
RVDLL RVRC		RVCAPI RvConExTrigStatus(Raven Board, BFU32 BFTrig, PBFU32 Mode);
RVDLL RVRC		RVCAPI RvConFIFOReset(Raven Board);
RVDLL RVRC		RVCAPI RvConCTabReset(Raven Board);
RVDLL RVRC		RVCAPI RvConGPOutSet(Raven Board, BFU32 Mask, BFU32 Value);
RVDLL RVRC		RVCAPI RvConGPOutGet(Raven Board, PBFU32 Value);

// misc
RVDLL RVRC		RVCAPI RvShutdown(Raven Board,BFU32 AqEngine);

// Version Control Functions

RVDLL RVRC	    RVCAPI RvDVersion(PBFU32 pMajorVeraion, PBFU32 pMinorVersion);

// Alternate spellings.

#define RvShutDown	RvShutdown
#define Qtab		QTab

#endif // !defined(KernelOS)

// Quad Tables

RVDLL RVRC		RVCAPI RvPhysQTabCreate(Raven Board, RQTabHeadPtr pRelQTabHead, BFU32 AqEngine);
RVDLL RVRC		RVCAPI RvPhysQTabWrite(Raven Board, RQTabHeadPtr pRelQTabHead, BFU32 Offset);
RVDLL RVRC		RVCAPI RvPhysQTabEngage(Bd Board, RQTabHeadPtr pRelQTabHead);
RVDLL RVRC		RVCAPI RvPhysQTabChainLink(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 NumInChain);
RVDLL RVRC		RVCAPI RvPhysQTabChainBreak(Bd Board, RQTabHeadPtrPtr ChainArray);
RVDLL RVRC		RVCAPI RvPhysQTabChainEngage(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 FrameNum);
RVDLL RVRC		RVCAPI RvPhysQTabChainProgress(Bd Board, RQTabHeadPtrPtr ChainArray, PBFU32 pFrameNum, PBFU32 pLineNum);
RVDLL RVRC		RVCAPI RvPhysQTabFree(Raven Board, RQTabHeadPtr pRelQTabHead);
RVDLL BFU32		RVCAPI RvQTabPeek(Raven Board, BFU8 Bank, BFU32 Index);
RVDLL RVRC		RVCAPI RvQTabPoke(Raven Board, BFU8 Bank, BFU32 Index, BFU32 Value);
RVDLL RVRC		RVCAPI RvQTabRead(Raven Board, BFU8 Bank, BFU32 Index, BFU32 NumEntries, PBFVOID pDest);
RVDLL RVRC		RVCAPI RvQTabWrite(Raven Board, BFU8 Bank, BFU32 Index, BFU32 NumEntries, PBFVOID pSource);
RVDLL RVRC		RVCAPI RvQTabFill(Raven Board, BFU8 Bank, BFU32 Index, BFU32 NumEntries, BFU32 Value);

RVDLL RVRC		RVCAPI RvQTabRamp(Raven Board, BFU8 Bank, BFU32 StartIndex, BFU32 EndIndex, BFU32 StartVal, BFU32 EndVal);
RVDLL RVRC		RVCAPI RvChainSIPEnable(Bd Board, RQTabHeadPtrPtr ChainArray);
RVDLL RVRC		RVCAPI RvChainSIPDisable(Bd Board, RQTabHeadPtrPtr ChainArray);

// Mid Level Control Functions

RVDLL RVRC	    RVCAPI RvConAqStatus(Raven Board, PBFU32 pStatus, BFU32 AqEngine);
RVDLL RVRC	    RVCAPI RvConInt(Raven Board, BFU32 IntType, BFU32 Action);
RVDLL RVRC		RVCAPI RvConVTrigModeSet(Raven Board, BFU32 TrigMode, BFU32 TrigAssignments, BFU32 TrigAPolarity, BFU32 TrigBPolarity);
RVDLL RVRC		RVCAPI RvConVTrigModeGet(Raven Board, PBFU32 TrigMode, PBFU32 TrigAssignments, PBFU32 TrigAPolarity, PBFU32 TrigBPolarity);
RVDLL RVRC		RVCAPI RvConHTrigModeSet(Raven Board, BFU32 TrigMode, BFU32 TrigAssignments, BFU32 TrigPolarity);
RVDLL RVRC		RVCAPI RvConHTrigModeGet(Raven Board, PBFU32 TrigMode, PBFU32 TrigAssignments, PBFU32 TrigPolarity);
RVDLL RVRC		RVCAPI RvConVTrigger(Raven Board, BFU32 RvTrig, BFU32 AssertType);
RVDLL RVRC		RVCAPI RvConExTrigConnect(Raven Board, BFU32 RvTrig, BFU32 Mode);
RVDLL RVRC		RVCAPI RvConDMACommand(Raven Board, BFU32 Command, BFU32 DMAChannel);
RVDLL RVRC	    RVCAPI RvConDMAProgress(Raven Board, RQTabHeadPtr pRelQTabHead, PBFU32 pBytesAqed, BFU32 DMAChannel);

//  LUTS

RVDLL BFU32		RVCAPI RvLutPeek(Raven Board, BFU8 Bank, BFU8 Lane, BFU32 Addr);
RVDLL RVRC		RVCAPI RvLutPoke(Raven Board, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 Value);
RVDLL RVRC		RVCAPI RvLutRead(Raven Board, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 NumEntries, PBFVOID pDest);
RVDLL RVRC		RVCAPI RvLutWrite(Raven Board, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 NumEntries, PBFVOID pSource);
RVDLL RVRC		RVCAPI RvLutFill(Raven Board, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 NumEntries, BFU32 Val);
RVDLL RVRC		RVCAPI RvLutRamp(Raven Board, BFU8 Bank, BFU8 Lane, BFU32 StartAddr, BFU32 EndAddr, BFU32 StartVal, BFU32 EndVal);

#ifdef __cplusplus
}
#endif

#endif // __RVAPI__
