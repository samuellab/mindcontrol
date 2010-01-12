/***************************************************************************
*
* CiApi.h
*
* Generic camera interface API
* 
* Function prototypes
*
* Copyright (C) 1998 by BitFlow, Inc.  All Rights Reserved.
*
* 04/21/98	rjd		created
* 06/02/99  sms		Added additional functions
*
***************************************************************************/

#if !defined(__CIAPI__)
    #define __CICIAPI__

#include "BFApi.h"
#include "BFDef.h"

#include "R2Type.h"
#include "R2Board.h"
#include "RvBoard.h"

#include "CiDef.h"

#ifdef __cplusplus
extern "C" {
#endif

// System Open and Initialization

BFDLL BFRC		BFCAPI CiSysBrdEnum(BFU32 Type, PBFU32 Number);
BFDLL BFRC		BFCAPI CiSysBrdFind(BFU32 Type, BFU32 Number, PCiENTRY pEntry);
BFDLL BFRC		BFCAPI CiSysBoardFindSWConnector(BFU32 Type, BFU32 Switch, BFU32 Connector, PCiENTRY pEntry);
BFDLL BFRC		BFCAPI CiBrdOpen(PCiENTRY pEntry, Bd *pBoard, BFU32 Mode);
BFDLL BFRC		BFCAPI CiBrdOpenCam(PCiENTRY pEntry, Bd *pBoard, BFU32 Mode, PBFCHAR ForceCamFile);
BFDLL BFRC		BFCAPI CiBrdCamSel(Bd Board, BFU32 CamIndex, BFU32 Mode);
BFDLL BFRC		BFCAPI CiBrdCamGetCur(Bd Board, PBFCNF *pCam);
BFDLL BFRC		BFCAPI CiBrdCamSetCur(Bd Board, PBFCNF pCam, BFU32 Mode);
BFDLL BFRC		BFCAPI CiBrdInquire(Bd Board, BFU32 Member, PBFU32 pVal);
BFDLL BFRC		BFCAPI CiBrdClose(Bd Board);
BFDLL BFRC		BFCAPI CiBrdAqTimeoutSet(Bd Board, BFU32 Timeout);
BFDLL BFU32		BFCAPI CiBrdType(Bd Board);
BFDLL BFRC		BFCAPI CiBrdAqSigSetCur(Bd Board, PBFVOID pAqSig, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiBrdAqSigGetCur(Bd Board, PBFVOID pAqSig, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiBrdCamGetFileName(Bd Board, BFU32 Num, PBFCHAR CamName);

// Acquisition

BFDLL BFRC		BFCAPI CiAqSetup(Bd Board, PBFVOID pDest,BFU32  DestSize,BFS32 Stride,BFU32 DestType,BFU32 LutBank,BFU32 LutMode,BFU8 QuadBank,BFBOOL FirstBank,BFU32 QTabMode,BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqCommand(Bd Board,BFU32 Command,BFU32 Mode,BFU8 QuadBank,BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqCleanUp(Bd Board,BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqWaitDone(Bd Board,BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqNextBankSet(Bd Board,BFU8 QuadBank,BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqBankSet(Bd Board,BFU8 QuadBank,BFU32 AqEngine);
BFDLL BFRC  	BFCAPI CiAqOverflowCheck(Bd Board, PBFBOOL pStatus);
BFDLL BFRC		BFCAPI CiShutdown(Bd Board, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqWaitActive(Bd Board, BFU32 AqEngine, BFU32 Timeout);
BFDLL BFRC		BFCAPI CiAqLastLine(Bd Board, PBFU32 pCurLine, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqFrameSize(Bd Board, BFU32 XSize, BFU32 YSize, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqReengage(Bd Board, BFU8 QuadBank, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqROISet(Bd Board, BFU32 XOffset, BFU32 YOffset, BFU32 XSize, BFU32 YSize, BFU32 AqEngine);

// two board functions

BFDLL BFRC		BFCAPI CiAqSetup2Brds(Bd Board1, Bd Board2, PBFVOID pDest, BFU32 DestSize, BFS32 Stride, BFU32 DestType, BFU32 LutBank, BFU32 LutMode, BFU8 QuadBank, BFBOOL FirstBank, BFU32 QTabMode, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiAqCleanUp2Brds(Bd Board1, Bd Board2, BFU32 AqEngine);

// Camera Configuration

BFDLL BFRC		BFCAPI  CiCamOpen(Bd Board, PCHAR CamName, PBFCNF *pCam);
BFDLL BFRC		BFCAPI  CiCamInquire(Bd Board,PBFCNF pCam, BFU32 Member, PBFU32 pVal);
BFDLL BFRC		BFCAPI  CiCamClose(Bd Board, PBFCNF pCam);
BFDLL BFRC		BFCAPI  CiCamAqTimeoutSet(Bd Board, PBFCNF pCam, BFU32 Timeout);
BFDLL BFRC		BFCAPI  CiCamInqTaps(Bd Board, PBFU32 pTaps);

// Interrupt Signals

BFDLL BFRC		BFCAPI CiSignalCreate(Bd Board,BFU32  Type, PCiSIGNAL pSignal);
BFDLL BFRC		BFCAPI CiSignalWait(Bd Board,PCiSIGNAL pSignal, BFU32  TimeOut, PBFU32  pNumInts);
BFDLL BFRC		BFCAPI CiSignalNextWait(Bd Board,PCiSIGNAL pSignal, BFU32  TimeOut);
BFDLL BFRC		BFCAPI CiSignalCancel(Bd Board,PCiSIGNAL pSignal);
BFDLL BFRC		BFCAPI CiSignalQueueSize(Bd Board,PCiSIGNAL pSignal,PBFU32  pNumInts);
BFDLL BFRC		BFCAPI CiSignalQueueClear(Bd Board,PCiSIGNAL pSignal);
BFDLL BFRC		BFCAPI CiSignalFree(Bd Board,PCiSIGNAL pSignal);

// Control Table functions

BFDLL BFU32	BFCAPI CiCTabPeek(Bd Board, BFU32 Index, BFU16 Mask);
BFDLL BFRC	BFCAPI CiCTabPoke(Bd Board, BFU32 Index, BFU16 Mask, BFU16 Value);
BFDLL BFRC	BFCAPI CiCTabRead(Bd Board, BFU32 Index, BFU32 NumEntries, BFU16 Mask, PBFVOID pDest);
BFDLL BFRC	BFCAPI CiCTabWrite(Bd Board, BFU32 Index, BFU32 NumEntries, BFU16 Mask, PBFVOID pSource);
BFDLL BFRC	BFCAPI CiCTabFill(Bd Board, BFU32 Index, BFU32 NumEntries, BFU16 Mask, BFU16 Value);
BFDLL BFRC	BFCAPI CiCTabRamp(Bd Board, BFU32 StartIndex, BFU32 EndIndex, BFU32 StartVal, BFU32 EndVal, BFU16 Mask);
BFDLL BFU32 BFCAPI CiCTabVSize(Bd Board);
BFDLL BFU32 BFCAPI CiCTabHSize(Bd Board);

// Con functions

BFDLL BFRC		BFCAPI CiConAqStatus(Bd Board, PBFU32 pStatus, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiConInt(Bd Board, BFU32 IntType, BFU32 Action);
BFDLL BFRC		BFCAPI CiConAqCommand(Bd Board, BFU32 Command, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiConExTrigConnect(Bd Board, BFU32 CiTrig, BFU32 Mode);
BFDLL BFRC		BFCAPI CiConExTrigStatus(Bd Board, BFU32 CiTrig, PBFU32 Mode);
BFDLL BFRC		BFCAPI CiConVTrigModeGet(Bd Board, PBFU32 TrigMode, PBFU32 TrigAssignments, PBFU32 TrigAPolarity, PBFU32 TrigBPolarity);
BFDLL BFRC		BFCAPI CiConVTrigModeSet(Bd Board, BFU32 TrigMode, BFU32 TrigAssignments, BFU32 TrigAPolarity, BFU32 TrigBPolarity);
BFDLL BFRC		BFCAPI CiConHTrigModeSet(Bd Board, BFU32 EncMode, BFU32 EncPolarity, BFU32 EncSelect);
BFDLL BFRC		BFCAPI CiConHTrigModeGet(Bd Board,PBFU32 EncMode, PBFU32 EncPolarity, PBFU32 EncSelect);
BFDLL BFRC		BFCAPI CiConSwTrig(Bd Board, BFU32 Triggers, BFU32 AssertType);
BFDLL BFRC		BFCAPI CiConAqMode(Bd Board,BFU32 DestType);
BFDLL BFRC		BFCAPI CiConDMACommand(Bd Board, BFU32 Command, BFU32 Mode, BFU8 Bank, BFU32 DMAChannel);
BFDLL BFRC		BFCAPI CiConSwTrigStat(Bd Board, BFU32 CiTrig, PBFU32 Status);
BFDLL BFRC		BFCAPI CiConHwTrigStat(Bd Board, BFU32 CiTrig, PBFU32 Status);
BFDLL BFRC		BFCAPI CiConFIFOReset(Bd Board);
BFDLL BFRC		BFCAPI CiConCTabReset(Bd Board);
BFDLL BFRC		BFCAPI CiConGetFrameCount(Bd Board, PBFU32 FrameCount, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiConIntModeSet(Bd Board, BFU32 Mode);
BFDLL BFRC		BFCAPI CiConIntModeGet(Bd Board, PBFU32 Mode);
BFDLL BFRC		BFCAPI CiConExposureControlSet(Bd Board, BFDOUBLE ExposurePeriod, BFDOUBLE LineFramePeriod, BFU32 TriggerMode, BFBOOL AssertedHigh, BFU32 OutputSignal);
BFDLL BFRC		BFCAPI CiConExposureControlGet(Bd Board, PBFDOUBLE pExposurePeriod, PBFDOUBLE pLineFramePeriod, PBFU32 pTriggerMode, PBFBOOL pAssertedHigh, PBFU32 pOutputSignal);
BFDLL BFRC		BFCAPI CiEncoderDividerSet(Bd Board, BFDOUBLE ScaleFactor, BFBOOL ForceDC, BFBOOL OpenLoop, BFU32 ClockSelect);
BFDLL BFRC		BFCAPI CiEncoderDividerGet(Bd Board, PBFDOUBLE pScaleFactor, PBFBOOL pForceDC, PBFBOOL pOpenLoop, PBFU32 pClockSelect);

// Quad Table Functions

BFDLL BFRC		BFCAPI CiPhysQTabCreate(Bd Board, RQTabHeadPtr pRelQTabHead, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiPhysQTabFree(Bd Board, RQTabHeadPtr pRelQTabHead);
BFDLL BFRC		BFCAPI CiPhysQTabWrite(Bd Board, RQTabHeadPtr pRelQTabHead, BFU32 Offset);
BFDLL BFRC		BFCAPI CiPhysWriteFirstQTabs(Bd Board,RQTabHeadPtr pRelQTabFirst,RQTabHeadPtr pRelQTabSecond,BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiPhysQTabEngage(Bd Board, RQTabHeadPtr pRelQTabHead);
BFDLL BFRC		BFCAPI CiRelQTabCreate(Bd Board, PBFCNF pCam, PBFVOID pDest, BFU32 BufferSize, BFS32 Stride, RQTabHeadPtr pRelQTabHead, BFU32 DestType, BFU32 LutBank, BFU32 LutType, BFU32 Options, BFU32 AqEngine);
BFDLL BFRC		BFCAPI CiRelQTabFree(Bd Board, RQTabHeadPtr pRelQTabHead);
BFDLL BFRC		BFCAPI CiPhysQTabChainLink(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 NumInChain);
BFDLL BFRC		BFCAPI CiPhysQTabChainBreak(Bd Board, RQTabHeadPtrPtr ChainArray);
BFDLL BFRC		BFCAPI CiPhysQTabChainEngage(Bd Board, RQTabHeadPtrPtr ChainArray, BFU32 NumInChain);
BFDLL BFRC		BFCAPI CiPhysQTabChainProgress(Bd Board, RQTabHeadPtrPtr ChainArray, PBFU32 pFrameNum, PBFU32 pLineNum);
BFDLL BFRC		BFCAPI CiQTabFill(Bd Board, BFU8 Bank, BFU32 Index, BFU32 NumEntries, BFU32 Value);
BFDLL BFRC		BFCAPI CiQTabRead(Bd Board, BFU8 Bank, BFU32 Index, BFU32 NumEntries, PBFVOID pDest);
BFDLL BFRC		BFCAPI CiQTabWrite(Bd Board, BFU8 Bank, BFU32 Index, BFU32 NumEntries, PBFVOID pSource);
BFDLL BFRC		BFCAPI CiQTabRamp(Bd Board, BFU8 Bank, BFU32 StartIndex, BFU32 EndIndex, BFU32 StartVal, BFU32 EndVal);
BFDLL BFRC		BFCAPI CiChainSIPEnable(Bd Board, RQTabHeadPtrPtr ChainArray);
BFDLL BFRC		BFCAPI CiChainSIPDisable(Bd Board, RQTabHeadPtrPtr ChainArray);

// Register Index Access

BFDLL BFRC		BFCAPI CiRegIndxRMW(Bd Board, BFU32 RegIndx, BFU32 RegValue, BFU32 RegMask);
BFDLL BFBOOL	BFCAPI CiRegIndxSupported(Bd Board, BFU32 RegIndx);
BFDLL BFRC		BFCAPI CiRegIndxName(Bd Board, BFU32 RegIndx, PBFCHAR pRegName, BFU32 Size);
BFDLL BFRC		BFCAPI CiRegIndxFlags(Bd Board, BFU32 RegIndx, PBFU32 FlagsPtr);
BFDLL BFRC		BFCAPI CiRegIndxShift(Bd Board, BFU32 RegId, PBFU32 ShiftPtr);
BFDLL BFRC		BFCAPI CiRegIndxMask(Bd Board, BFU32 RegIndx, PBFU32 MaskPtr);
BFDLL BFRC		BFCAPI CiRegIndxObjectId(Bd Board, BFU32 RegIndx, PBFU32 ObjectIdPtr);
BFDLL BFRC		BFCAPI CiRegIndxPoke(Bd Board, BFU32 RegIndx, BFU32 Val);
BFDLL BFU32		BFCAPI CiRegIndxPeek(Bd Board, BFU32 RegIndx);

// GPOUT access

BFDLL BFRC      BFCAPI CiRegGPOutSet(Bd Board, BFU32 Mask, BFU32 Value);
BFDLL BFRC		BFCAPI CiRegGPOutGet(Bd Board, PBFU32 Value);

// LUTs

BFDLL BFU32		BFCAPI CiLutPeek(Bd Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr) ;
BFDLL BFRC		BFCAPI CiLutPoke(Bd Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 Value) ;
BFDLL BFRC		BFCAPI CiLutRead(Bd Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 NumEntries, PBFVOID pDest);
BFDLL BFRC		BFCAPI CiLutWrite(Bd Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr,BFU32 NumEntries, PBFVOID pSource);
BFDLL BFRC		BFCAPI CiLutFill(Bd Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 Addr, BFU32 NumEntries, BFU32 Val);
BFDLL BFRC		BFCAPI CiLutRamp(Bd Board, BFU8 Mode, BFU8 Bank, BFU8 Lane, BFU32 StartAddr,BFU32 EndAddr, BFU32 StartVal, BFU32 EndVal);
BFDLL BFRC		BFCAPI CiLutSetMask(Bd Board, BFU32 BitDepth, PBFU8 LutMode);
BFDLL BFRC		BFCAPI CiLutMax(Bd Board,CiLutModePtr LutSizePtr);

// Versions

BFDLL BFRC		BFCAPI CiDVersion(PBFU32 pMajorVersion, PBFU32 pMinorVersion);

// Alternate spellings.

#define CiShutDown	CiShutdown
#define Qtab		QTab
#define CiConCtabReset	CiConCTabReset

#ifdef __cplusplus
}
#endif

#endif // __CICIAPI__
