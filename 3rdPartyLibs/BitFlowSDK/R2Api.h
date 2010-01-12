/***************************************************************************
*
* R2Api.h
*
* Header file for New R2 Kernel driver API for Windows NT.
* This should/will be the only interface to the kernel for both R2 
* and BF libraries. This eventually should be in its own DLL.
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* 03/06/96	rjd		created
*
***************************************************************************/

#ifndef __R2API__
#define __R2API__

#include "BFDef.h"
#include "R2Type.h"
#include "R2Def.h"
#include "R2Board.h"
#include "R2TabError.h"
#include "R2Config.h"
#include "R2CLConfig.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(KernelOS)

// System Open and Initialization
	
R2DLL R2RC	R2CAPI R2SysBoardFindByNum(BFU32 Number, PR2ENTRY pEntry);
R2DLL R2RC	R2CAPI R2BrdOpen(PR2ENTRY pEntry,RdRn *pBoard, BFU32 Mode);
R2DLL R2RC	R2CAPI R2BrdOpenCam(PR2ENTRY pEntry, RdRn *pBoard, BFU32 Mode, PBFCHAR ForceCamFile);
R2DLL R2RC	R2CAPI R2BrdCamSel(RdRn Board, BFU32 CamIndex, BFU32 Mode);
R2DLL R2RC	R2CAPI R2BrdCamSetCur(RdRn pBoard, PR2CAM pCam, BFU32 Mode);
R2DLL R2RC	R2CAPI R2BrdInquire(RdRn Board, BFU32 Member, PBFU32 pVal);
R2DLL R2RC	R2CAPI R2BrdClose(RdRn Board);
R2DLL R2RC	R2CAPI R2BrdAqTimeoutSet(RdRn Board, BFU32 Timeout);
R2DLL R2RC	R2CAPI R2BrdAqSigGetCur(RdRn Board, PBFVOID *pAqSig);
R2DLL R2RC	R2CAPI R2BrdAqSigSetCur(RdRn pBoard, PBFVOID pAqSig);
R2DLL R2RC	R2CAPI R2BrdQTabGetCur(RdRn Board, PBFVOID *pQuad, BFU32 QuadBank);
R2DLL R2RC	R2CAPI R2BrdQTabSetCur(RdRn pBoard, PBFVOID pQuad, BFU32 QuadBank);

R2DLL R2RC	R2CAPI R2BrdCamGetCur(RdRn Board, PR2CAM *pCam);
R2DLL R2RC	R2CAPI R2BrdCamGetFileName(RdRn Board, BFU32 Num, PBFCHAR CamName);

R2DLL R2RC	R2CAPI R2DrvOpen(RdRn *pBoard, BFBOOL CameraLink);
R2DLL R2RC	R2CAPI R2DrvClose(RdRn Board);

// Acquisition

R2DLL R2RC	R2CAPI R2AqSetup(RdRn Board, PBFVOID pDest, BFU32 DestSize, BFS32 Stride,BFU32 DestType,BFU32 LutBank,BFU32 LutMode,BFU8 QuadBank,BFBOOL FirstBank);
R2DLL R2RC	R2CAPI R2AqCommand(RdRn Board,BFU32 Command, BFU32 Mode,BFU8 QuadBank);
R2DLL R2RC	R2CAPI R2AqCleanUp(RdRn Board);
R2DLL R2RC	R2CAPI R2AqWaitDone(RdRn Board);
R2DLL R2RC	R2CAPI R2AqNextBankSet(RdRn Board,BFU8 QuadBank);
R2DLL R2RC	R2CAPI R2AqReengage(RdRn Board,BFU8 QuadBank);

R2DLL R2RC	R2CAPI R2AqFrameSize(RdRn Board,BFU32 XSize,BFU32 YSize);
R2DLL R2RC	R2CAPI R2AqROISet(RdRn Board, BFU32 XSize, BFU32 YSize, BFU32 XOffset, BFU32 YOffset);


// Camera Configuration

R2DLL R2RC	R2CAPI R2CamOpen(RdRn Board, PBFCHAR CamName, PR2CAM *pCam);
R2DLL R2RC	R2CAPI R2CamInquire(RdRn Board,PR2CAM pCam,BFU32 Member, PBFU32 pVal);
R2DLL R2RC	R2CAPI R2CamClose(RdRn Board, PR2CAM pCam);
R2DLL R2RC	R2CAPI R2CamAqTimeoutSet(RdRn Board,PR2CAM pCam, BFU32 Timeout);

// Interrupt Signals

R2DLL R2RC	R2CAPI R2SignalCreate(RdRn Board,BFU32 Type, PR2SIGNAL pSignal);
R2DLL R2RC	R2CAPI R2SignalWait(RdRn Board,PR2SIGNAL pSignal, BFU32 TimeOut, PBFU32 pNumInts);
R2DLL R2RC	R2CAPI R2SignalNextWait(RdRn Board,PR2SIGNAL pSignal, BFU32 TimeOut);
R2DLL R2RC	R2CAPI R2SignalCancel(RdRn Board,PR2SIGNAL pSignal);
R2DLL R2RC	R2CAPI R2SignalQueueSize(RdRn Board,PR2SIGNAL pSignal,PBFU32 pNumInts);
R2DLL R2RC	R2CAPI R2SignalQueueClear(RdRn Board,PR2SIGNAL pSignal);
R2DLL R2RC	R2CAPI R2SignalFree(RdRn Board,PR2SIGNAL pSignal);

// Quad Table Functions

R2DLL R2RC	R2CAPI R2PhysQTabWrite(RdRn Board, RQTabHeadPtr pRelQTabHead, BFU32 Offset);
R2DLL R2RC	R2CAPI R2RelQTabCreate(RdRn Board, PR2CAM pCam, PBFVOID pDest, BFU32 BufferSize, BFS32 Stride, RQTabHeadPtr pRelQTabHead, BFU32 DestType, BFU32 LutBank, BFU32 LutMode, BFU32 Options);
R2DLL R2RC	R2CAPI R2RelQTabFree(RdRn Board, RQTabHeadPtr pRelQTabHead);
R2DLL R2RC	R2CAPI R2RelDisplayQTabCreate(RdRn Board, PR2CAM pCam, PBFVOID pDest, BFU32 BufferSize, BFS32 Stride, RQTabHeadPtr pRelQTabHead, BFU32 DestType, BFU32 LutBank, BFU32 LutMode, BFU32 Options, BFU32 SrcX, BFU32 SrcY, BFU32 SrcDX, BFU32 SrcDY, BFU32 DestX, BFU32 DestY);
R2DLL R2RC	R2CAPI R2QTabCreate(RdRn Board, PR2CAM pCam, PBFVOID pDest, BFU32 BufferSize, BFS32 Stride, VQTabHeadPtr pVirtQTabHead, BFU32 DestType, BFU32 LutBank, BFU32 LutMode, BFU32 Options);
R2DLL R2RC	R2CAPI R2QTabFree(RdRn Board, RQTabHeadPtr pRelQTabHead);

R2DLL R2RC	R2CAPI R2RelQTabCreateRoi(RdRn Board, PR2CAM pCam, PBFVOID pDest, BFU32  BufferSize,BFS32 Stride, RQTabHeadPtr pRelQTabHead, BFU32 DestType, BFU32 LutBank, BFU32 LutMode, BFU32 Options, BFU32 DestX, BFU32 DestY, BFU32 DestDx, BFU32 DestDy);

// Mid Level Control Functions

R2DLL R2RC	R2CAPI R2ConAqMode(RdRn Board,BFU32 DestType);
R2DLL R2RC  R2CAPI R2LastLine(RdRn Board,PBFU32 pCurLine);
R2DLL R2RC	R2CAPI R2ConHwTrigStat(RdRn Board, BFU32 BFTrig, PBFU32 Status);
R2DLL R2RC	R2CAPI R2ConSwTrigStat(RdRn Board, BFU32 BFTrig, PBFU32 Status );
R2DLL R2RC	R2CAPI R2ConVTrigModeSet(RdRn Board,BFU32 TrigMode,BFU32 TrigPolarity);
R2DLL R2RC	R2CAPI R2ConVTrigModeGet(RdRn Board,PBFU32 TrigMode,PBFU32 TrigPolarity);
R2DLL R2RC	R2CAPI R2ConHTrigModeSet(RdRn Board, BFU32 EncMode, BFU32 EncPolarity, BFU32 EncSelect);
R2DLL R2RC	R2CAPI R2ConHTrigModeGet(RdRn Board, PBFU32 EncMode, PBFU32 EncPolarity, PBFU32 EncSelect);
R2DLL R2RC	R2CAPI R2ConExTrigStatus(RdRn Board, PBFU32 Mode);
R2DLL R2RC	R2CAPI R2ConExTrigConnect(RdRn Board, BFU32 Mode);
R2DLL R2RC	R2CAPI R2ConFIFOReset(RdRn Board);
R2DLL R2RC	R2CAPI R2ConCTabReset(RdRn Board);

// misc
R2DLL R2RC	R2CAPI R2Shutdown(RdRn Board);
R2DLL R2RC	R2CAPI R2GetLinesPerVCount(RdRn Board,PBFU32 pLinesPerVCount);
  

// Version Control Functions

R2DLL R2RC	R2CAPI R2DVersion(PBFU32 pMajorVeraion,PBFU32 pMinorVersion);

// Alternate spellings.

#define R2ShutDown			R2Shutdown
#define Qtab				QTab
#define R2ConCtabReset		R2ConCTabReset


#endif // !defined(KernelOS)

// Data Control Functions

R2DLL R2RC	R2CAPI R2ConQTabBank(RdRn Board, BFU8 Bank); 
R2DLL R2RC	R2CAPI R2ConFreq(RdRn Board, BFU8 Freq); 
R2DLL R2RC	R2CAPI R2ConSwTrig(RdRn Board, BFU32 Triggers, BFU32 AssertType); 
R2DLL R2RC	R2CAPI R2ConTrigAqCmd(RdRn Board, BFU8 Mode); 
R2DLL R2RC	R2CAPI R2ConGPOutSet(RdRn Board, BFU32 Mask, BFU32 Value);
R2DLL R2RC	R2CAPI R2ConGPOutGet(RdRn Board, PBFU32 Value);

// Mid Level Control Functions

R2DLL R2RC	R2CAPI R2ConAqCommand(RdRn Board, BFU32 Command);
R2DLL R2RC	R2CAPI R2ConAqStatus(RdRn Board, PBFU32 pStatus);
R2DLL R2RC	R2CAPI R2ConInt(RdRn Board,BFU32 IntType,BFU32 Action);
R2DLL R2RC	R2CAPI R2DMAProgress(RdRn Board, RQTabHeadPtr pRelQTabHead, PBFU32 pBytesAqed);
R2DLL R2RC	R2CAPI R2ConDMACommand(RdRn Board, BFU32 Command,BFU32 Mode, BFU8 Bank);
R2DLL R2RC	R2CAPI R2ConDMATimeout(RdRn Board, BFU32 Timeout);

// Register Access

R2DLL BFU32	R2CAPI R2RegPeek(RdRn Board, BFU32 RegId);
R2DLL BFU32	R2CAPI R2RegPeekWait(RdRn Board, BFU32 RegId, BFU32 WaitValue, BFU32 WaitMilliseconds);
R2DLL R2RC	R2CAPI R2RegPoke(RdRn Board, BFU32 RegId, BFU32 RegValue);
R2DLL R2RC	R2CAPI R2RegRMW(RdRn Board, BFU32 RegId, BFU32 RegValue, BFU32 RegMask);
R2DLL R2RC	R2CAPI R2RegName(RdRn Board, BFU32 RegId, PBFCHAR pRegName, BFU32 Size); 
R2DLL R2RC	R2CAPI R2RegFlags(RdRn Board, BFU32 RegId, PBFU32 FlagsPtr);
R2DLL R2RC	R2CAPI R2RegShift(RdRn Board, BFU32 RegId, PBFU32 ShiftPtr);
R2DLL R2RC	R2CAPI R2RegMask(RdRn Board, BFU32 RegId, PBFU32 MaskPtr);
R2DLL R2RC	R2CAPI R2RegObjectId(RdRn Board, BFU32, PBFU32 ObjectIdPtr);

// Control Tables

R2DLL BFU16	R2CAPI R2CTabPeek(RdRn Board, BFU32 Index, BFU16 Mask);
R2DLL R2RC	R2CAPI R2CTabPoke(RdRn Board, BFU32 Index, BFU16 Mask, BFU16 Value);
R2DLL R2RC	R2CAPI R2CTabRead(RdRn Board, BFU32 Index, BFU32 NumEntries, BFU16 Mask, PBFVOID pDest);
R2DLL R2RC	R2CAPI R2CTabWrite(RdRn Board, BFU32 Index, BFU32 NumEntries, BFU16 Mask, PBFVOID pSource);
R2DLL R2RC	R2CAPI R2CTabFill(RdRn Board, BFU32 Index, BFU32 NumEntries, BFU16 Mask, BFU16 Value);
R2DLL R2RC	R2CAPI R2CTabRamp(RdRn Board, BFU32 StartIndex, BFU32 EndIndex, BFU32 StartVal, BFU32 EndVal, BFU16 Mask);

// Quad Tables

R2DLL R2RC	R2CAPI R2PhysQTabCreate(RdRn Board, RQTabHeadPtr pRelQTabHead);
R2DLL R2RC	R2CAPI R2PhysQTabEngage(Bd Board, RQTabHeadPtr pRelQTabHead);
R2DLL R2RC	R2CAPI R2PhysQTabChainLink(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 NumInChain);
R2DLL R2RC	R2CAPI R2PhysQTabChainBreak(Bd Board, RQTabHeadPtrPtr ChainArray);
R2DLL R2RC	R2CAPI R2PhysQTabChainEngage(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 FrameNum);
R2DLL R2RC	R2CAPI R2PhysQTabChainProgress(Bd Board, RQTabHeadPtrPtr ChainArray, PBFU32 pFrameNum, PBFU32 pLineNum);
R2DLL R2RC	R2CAPI R2PhysQTabFree(RdRn Board, RQTabHeadPtr pRelQTabHead);
R2DLL BFU32	R2CAPI R2QTabPeek(RdRn Board, BFU8 Bank, BFU32 Index);
R2DLL R2RC	R2CAPI R2QTabPoke(RdRn Board, BFU8 Bank, BFU32 Index, BFU32 Value);
R2DLL R2RC	R2CAPI R2QTabRead(RdRn Board, BFU8 Bank, BFU32 Index, BFU32 NumEntries, PBFVOID pDest);
R2DLL R2RC	R2CAPI R2QTabWrite(RdRn Board, BFU8 Bank, BFU32 Index, BFU32 NumEntries, PBFVOID pSource);
R2DLL R2RC	R2CAPI R2QTabFill(RdRn Board, BFU8 Bank, BFU32 Index, BFU32 NumEntries, BFU32 Value);
R2DLL R2RC	R2CAPI R2QTabRamp(RdRn Board, BFU8 Bank, BFU32 StartIndex, BFU32 EndIndex, BFU32 StartVal, BFU32 EndVal);

R2DLL R2RC	R2CAPI R2ChainSIPEnable(Bd Board, RQTabHeadPtrPtr ChainArray);
R2DLL R2RC	R2CAPI R2ChainSIPDisable(Bd Board, RQTabHeadPtrPtr ChainArray);

//  LUTS

R2DLL BFU32	R2CAPI R2LutPeek(RdRn Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr);
R2DLL R2RC	R2CAPI R2LutPoke(RdRn Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 Value);
R2DLL R2RC	R2CAPI R2LutRead(RdRn Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 NumEntries, PBFVOID pDest);
R2DLL R2RC	R2CAPI R2LutWrite(RdRn Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 NumEntries, PBFVOID pSource);
R2DLL R2RC	R2CAPI R2LutFill(RdRn Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 NumEntries, BFU32 Val);
R2DLL R2RC	R2CAPI R2LutRamp(RdRn Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 StartAddr, BFU32 EndAddr, BFU32 StartVal, BFU32 EndVal);
R2DLL R2RC	R2CAPI R2LutMax(RdRn Board, R2LutModePtr LutSizePtr);

// Error Handling

R2DLL R2RC	R2CAPI R2ErrorEnableEvent(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorDisableEvent(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorEnableDebugger(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorDisableDebugger(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorEnableDialog(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorDisableDialog(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorEnableFile(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorDisableFile(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorEnableMonitor(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorDisableMonitor(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorEnableBreakUser(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorDisableBreakUser(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorEnableAll(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorDisableAll(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorCheck(RdRn Board);
R2DLL R2RC	R2CAPI R2ErrorClearAll(RdRn Board);
R2DLL R2RC	R2CAPI R2ErrorClearLast(RdRn Board); 
R2DLL R2RC	R2CAPI R2ErrorDisableBreakKernel(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorEnableBreakKernel(RdRn Board, BFU32 Filter);
R2DLL R2RC	R2CAPI R2ErrorFileAll(RdRn Board);
R2DLL R2RC	R2CAPI R2ErrorGetLast(RdRn Board, PBFU32 pLastError); 
R2DLL R2RC	R2CAPI R2ErrorShow(RdRn Board); 


#ifdef __cplusplus
}
#endif

#endif // __R2API__
