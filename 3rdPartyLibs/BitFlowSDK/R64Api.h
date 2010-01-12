//
// Creation:    R64Api.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// R64 API Generic Board Access Functions    
//
// History:
//
// 05/06/02     rbs     Created.
// 

#ifndef __R64API__
#define __R64API__

#include "BFDef.h"
#include "R64Type.h"
#include "R64Def.h"
#include "R64Board.h"
#include "R64TabError.h"
#include "R64Config.h"
#include "R64Info.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(KernelOS)

// System Open and Initialization
	
R64DLL R64RC	R64CAPI R64SysBoardFindByNum(BFU32 Number, PR64ENTRY pEntry);
R64DLL R64RC	R64CAPI R64BrdOpen(PR64ENTRY pEntry,R64 *pBoard, BFU32 Mode);
R64DLL R64RC	R64CAPI R64BrdOpenCam(PR64ENTRY pEntry, R64 *pBoard, BFU32 Mode, PBFCHAR ForceCamFile);
R64DLL R64RC	R64CAPI R64BrdCamSel(R64 Board, BFU32 CamIndex, BFU32 Mode);
R64DLL R64RC	R64CAPI R64BrdCamSetCur(R64 pBoard, PR64CAM pCam, BFU32 Mode);
R64DLL R64RC	R64CAPI R64BrdInquire(R64 Board, BFU32 Member, PBFU32 pVal);
R64DLL R64RC	R64CAPI R64BrdClose(R64 Board);
R64DLL R64RC	R64CAPI R64BrdAqTimeoutSet(R64 Board, BFU32 Timeout);
R64DLL R64RC	R64CAPI R64BrdAqSigGetCur(R64 Board, PBFVOID *pAqSig);
R64DLL R64RC	R64CAPI R64BrdAqSigSetCur(R64 pBoard, PBFVOID pAqSig);

R64DLL R64RC	R64CAPI R64BrdCamGetCur(R64 Board, PR64CAM *pCam);
R64DLL R64RC	R64CAPI R64BrdCamGetFileName(R64 Board, BFU32 Num, PBFCHAR CamName);

R64DLL R64RC	R64CAPI R64DrvOpen(R64 *pBoard, BFU32 Mode);
R64DLL R64RC	R64CAPI R64DrvClose(R64 Board);

// Acquisition

R64DLL R64RC	R64CAPI R64AqSetup(R64 Board, PBFVOID pDest, BFU32  DestSize, BFS32 Stride,BFU32 DestType);
R64DLL R64RC	R64CAPI R64AqCommand(R64 Board,BFU32 Command, BFU32 Mode);
R64DLL R64RC	R64CAPI R64AqCleanUp(R64 Board);
R64DLL R64RC	R64CAPI R64AqWaitDone(R64 Board);
R64DLL R64RC	R64CAPI R64AqReengage(R64 Board);

R64DLL R64RC	R64CAPI R64AqFrameSize(R64 Board,BFU32 XSize,BFU32 YSize);
R64DLL R64RC	R64CAPI R64AqROISet(R64 Board, BFU32 XOffset, BFU32 YOffset, BFU32 XSize, BFU32 YSize);

// Two Brd functions
R64DLL R64RC	R64CAPI R64AqSetup2Brds(R64 Board1, R64 Board2, PBFVOID pDest, BFU32  DestSize, BFS32 Stride,BFU32 DestType);
R64DLL R64RC	R64CAPI R64AqCleanUp2Brds(R64 Board1, R64 Board2);

// Camera Configuration

R64DLL R64RC	R64CAPI R64CamOpen(R64 Board, PBFCHAR CamName, PR64CAM *pCam);
R64DLL R64RC	R64CAPI R64CamInquire(R64 Board,PR64CAM pCam,BFU32 Member, PBFU32 pVal);
R64DLL R64RC	R64CAPI R64CamClose(R64 Board, PR64CAM pCam);
R64DLL R64RC	R64CAPI R64CamAqTimeoutSet(R64 Board,PR64CAM pCam, BFU32 Timeout);

// Interrupt Signals

R64DLL R64RC	R64CAPI R64SignalCreate(R64 Board, BFU32 Type, PR64SIGNAL pSignal);
R64DLL R64RC	R64CAPI R64SignalWait(R64 Board, PR64SIGNAL pSignal, BFU32 TimeOut, PBFU32 pNumInts);
R64DLL R64RC	R64CAPI R64SignalNextWait(R64 Board, PR64SIGNAL pSignal, BFU32 TimeOut);
R64DLL R64RC	R64CAPI R64SignalCancel(R64 Board, PR64SIGNAL pSignal);
R64DLL R64RC	R64CAPI R64SignalQueueSize(R64 Board, PR64SIGNAL pSignal, PBFU32 pNumInts);
R64DLL R64RC	R64CAPI R64SignalQueueClear(R64 Board, PR64SIGNAL pSignal);
R64DLL R64RC	R64CAPI R64SignalFree(R64 Board, PR64SIGNAL pSignal);

// Quad Table
R64DLL R64RC	R64CAPI R64QTabCreate(R64 Board,PR64CAM pCam,PBFVOID pDest,BFU32 BufferSize,BFS32 Stride,VQTabHeadPtr pVirtQTabHead,BFU32 DestType,BFU32 Options);
R64DLL R64RC	R64CAPI	R64QTabFree(R64 Board,VQTabHeadPtr pVirtQTabHead);


// Mid Level Control

R64DLL R64RC	R64CAPI R64ConAqMode(R64 Board,BFU32 DestType);
R64DLL R64RC	R64CAPI R64LastLine(R64 Board,PBFU32 pCurLine);

// Miscellaneous

R64DLL R64RC	R64CAPI R64Shutdown(R64 Board);  

// Version Control

R64DLL R64RC	R64CAPI R64DVersion(PBFU32 pMajorVeraion,PBFU32 pMinorVersion);

#endif // !defined(KernelOS)

// Data Control

R64DLL R64RC	R64CAPI R64ConFreqSet(R64 Board, BFU8 Freq); 
R64DLL R64RC	R64CAPI R64ConGPOutSet(R64 Board, BFU32 GPout, BFU32 Level); 
R64DLL R64RC	R64CAPI R64ConSwTrig(R64 Board, BFU32 AssertType); 

// Mid Level Control Functions

R64DLL R64RC	R64CAPI R64ConAqCommand(R64 Board,BFU32 Command);
R64DLL R64RC	R64CAPI R64ConAqStatus(R64 Board,PBFU32 pStatus);
R64DLL R64RC	R64CAPI R64ConInt(R64 Board,BFU32 IntType,BFU32 Action);
R64DLL R64RC	R64CAPI R64DMAProgress(R64 Board, RQTabHeadPtr pRelQTabHead, PBFU32 pBytesAqed);
R64DLL R64RC	R64CAPI R64ConDMACommand(R64 Board, BFU32 Command, BFU32 Mode);
R64DLL R64RC	R64CAPI R64ConVTrigModeSet(R64 Board, BFU32 TrigMode, BFU32 TrigSelect, BFU32 TrigPolarity);
R64DLL R64RC	R64CAPI R64ConVTrigModeGet(R64 Board, PBFU32 TrigMode, PBFU32 TrigSelect, PBFU32 TrigPolarity);
R64DLL R64RC	R64CAPI R64ConHTrigModeSet(R64 Board, BFU32 EncMode, BFU32 EncPolarity, BFU32 EncSelect);
R64DLL R64RC	R64CAPI R64ConHTrigModeGet(R64 Board, PBFU32 EncMode, PBFU32 EncPolarity, PBFU32 EncSelect);
R64DLL R64RC	R64CAPI R64ConSwTrigStat(R64 Board, PBFU32 Status );
R64DLL R64RC	R64CAPI R64ConHwTrigStat(R64 Board, PBFU32 Status);
R64DLL R64RC	R64CAPI R64ConExTrigStatus(R64 Board, PBFU32 Mode);
R64DLL R64RC	R64CAPI R64ConExTrigConnect(R64 Board, BFU32 Mode);
R64DLL R64RC	R64CAPI R64ConCTabReset(R64 Board);
R64DLL R64RC	R64CAPI R64ConIntModeSet(R64 Board, BFU32 Mode);
R64DLL R64RC	R64CAPI R64ConIntModeGet(R64 Board, PBFU32 Mode);
R64DLL R64RC	R64CAPI R64ConGPOutGet(R64 Board, PBFU32 Value);
R64DLL R64RC	R64CAPI R64LutPoke(R64 Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 Value);
R64DLL BFU32	R64CAPI R64LutPeek(R64 Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr);
R64DLL R64RC	R64CAPI R64ConExposureControlSet(Bd Board, BFDOUBLE ExposurePeriod, BFDOUBLE LineFramePeriod, BFU32 TriggerMode, BFBOOL AssertedHigh, BFU32 OutputSignal);
R64DLL R64RC	R64CAPI R64ConExposureControlGet(Bd Board, PBFDOUBLE pExposurePeriod, PBFDOUBLE pLineFramePeriod, PBFU32 pTriggerMode, PBFBOOL pAssertedHigh, PBFU32 pOutputSignal);
R64DLL R64RC	R64CAPI R64EncoderDividerSet(Bd Board, BFDOUBLE ScaleFactor, BFBOOL ForceDC, BFBOOL OpenLoop, BFU32 ClockSelect);
R64DLL R64RC	R64CAPI R64EncoderDividerGet(Bd Board, PBFDOUBLE pScaleFactor, PBFBOOL pForceDC, PBFBOOL pOpenLoop, PBFU32 pClockSelect);

// Control Tables

R64DLL BFU16	R64CAPI R64CTabPeek(R64 Board, BFU32 Index, BFU16 Mask);
R64DLL R64RC	R64CAPI R64CTabPoke(R64 Board, BFU32 Index, BFU16 Mask, BFU16 Value);
R64DLL R64RC	R64CAPI R64CTabRead(R64 Board, BFU32 Index, BFU32 NumEntries, BFU16 Mask, PBFVOID pDest);
R64DLL R64RC	R64CAPI R64CTabWrite(R64 Board, BFU32 Index, BFU32 NumEntries, BFU16 Mask, PBFVOID pSource);
R64DLL R64RC	R64CAPI R64CTabFill(R64 Board, BFU32 Index, BFU32 NumEntries, BFU16 Mask, BFU16 Value);
R64DLL R64RC	R64CAPI R64CTabRamp(R64 Board, BFU32 StartIndex, BFU32 EndIndex, BFU32 StartVal, BFU32 EndVal, BFU16 Mask);

// Quad Tables

R64DLL R64RC	R64CAPI R64QTabEngage(Bd Board, RQTabHeadPtr pRelQTabHead);
R64DLL R64RC	R64CAPI R64QTabChainLink(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 NumInChain);
R64DLL R64RC	R64CAPI R64QTabChainBreak(Bd Board, RQTabHeadPtrPtr ChainArray);
R64DLL R64RC	R64CAPI R64QTabChainEngage(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 FrameNum);
R64DLL R64RC	R64CAPI R64QTabChainProgress(Bd Board, RQTabHeadPtrPtr ChainArray, PBFU32 pFrameNum, PBFU32 pLineNum);

R64DLL R64RC	R64CAPI R64ChainSIPEnable(Bd Board, RQTabHeadPtrPtr ChainArray);
R64DLL R64RC	R64CAPI R64ChainSIPDisable(Bd Board, RQTabHeadPtrPtr ChainArray);

// DPM

R64DLL BFU32	R64CAPI R64DPMPeek(R64 Board, BFU32 Offset);
R64DLL R64RC	R64CAPI R64DPMPoke(R64 Board, BFU32 Offset, BFU32 Value);
R64DLL R64RC	R64CAPI R64DPMRead(R64 Board, BFU32 Offset, BFU32 NumEntries, PBFVOID pDest);
R64DLL R64RC	R64CAPI R64DPMWrite(R64 Board, BFU32 Offset, BFU32 NumEntries, PBFVOID pSource);
R64DLL R64RC	R64CAPI R64DPMFill(R64 Board, BFU32 Offset, BFU32 NumEntries, BFU32 Value);
R64DLL R64RC	R64CAPI R64DPMRamp(R64 Board, BFU32 StartOffset, BFU32 EndOffset, BFU32 StartVal, BFU32 EndVal);
R64DLL R64RC	R64CAPI R64DPMReadDMA(R64 Board, BFU32 Offset, BFU32 NumEntries, PBFVOID pDest);


// alternative spellings

#define R64ConCtabReset		R64ConCTabReset

#ifdef __cplusplus
}
#endif

#endif


