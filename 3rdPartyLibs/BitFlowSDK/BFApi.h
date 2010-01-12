//
// Creation:    BFApi.h 
// Created:     July 18, 1997
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved. 
//
// Description:
//
// BitFlow API Generic Board Access Functions    
//
// History:
//
// 07/18/97     rbs     Added BFLane<things>.
// 

#if !defined(__BFAPI__)
#define __BFAPI__

#include "BFDef.h"
#include "BFTabRegister.h"
#include "BFTabError.h"
#include "BFEntTrans.h"
#include "BFRunTimeBth.h"

#ifdef __cplusplus
extern "C" {
#endif

// Register Access

BFDLL BFU32			BFCAPI BFRegPeek(Bd Board, BFU32 RegId);
BFDLL BFU32			BFCAPI BFRegPeekWait(Bd Board, BFU32 RegId, BFU32 WaitValue, BFU32 WaitMilliseconds);
BFDLL BFRC			BFCAPI BFRegPoke(Bd Board, BFU32 RegId, BFU32 RegValue);
BFDLL BFRC			BFCAPI BFRegRMW(Bd Board, BFU32 RegId, BFU32 RegValue, BFU32 RegMask);
BFDLL BFRC			BFCAPI BFRegName(Bd Board, BFU32 RegId, PBFCHAR pRegName, BFU32 Size); 
BFDLL BFRC			BFCAPI BFRegFlags(Bd Board, BFU32 RegId, PBFU32 FlagsPtr);  
BFDLL BFRC			BFCAPI BFRegShift(Bd Board, BFU32 RegId, PBFU32 ShiftPtr);
BFDLL BFRC			BFCAPI BFRegMask(Bd Board, BFU32 RegId, PBFU32 MaskPtr);
BFDLL BFRC			BFCAPI BFRegObjectId(Bd Board, BFU32, PBFU32 ObjectIdPtr);
BFDLL BFBOOL		BFCAPI BFRegSupported(Bd Board, BFU32 RegId);

// Error Handling

BFDLL BFRC			BFCAPI BFErrorEnableEvent(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorDisableEvent(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorEnableDebugger(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorDisableDebugger(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorEnableDialog(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorDisableDialog(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorEnableFile(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorDisableFile(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorEnableMonitor(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorDisableMonitor(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorEnableBreakUser(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorDisableBreakUser(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorEnableAll(Bd Board, BFU32 Filter);
BFDLL BFRC			BFCAPI BFErrorDisableAll(Bd Board, BFU32 Filter);

BFDLL BFRC			BFCAPI BFErrorDefaults(Bd Board);

BFDLL BFRC			BFCAPI BFErrorShow(Bd Board);
BFDLL BFRC			BFCAPI BFErrorCheck(Bd Board);
BFDLL BFRC			BFCAPI BFErrorClearAll(Bd Board);
BFDLL BFRC			BFCAPI BFErrorGetLast(Bd Board, PBFU32 pLastError); 
BFDLL BFRC			BFCAPI BFErrorClearLast(Bd Board); 
BFDLL BFRC			BFCAPI BFErrorGetMes(Bd Board, BFRC ErrorRC, PBFCHAR Message, BFU32 MessageBufSize);

// Error and About Dialogs

BFDLL BFBOOL		BFCAPI DoErrorDialog(BFS32 ErrorCode, PBFCHAR ErrorSource, BFU32 ErrorLine, PBFCHAR ErrorMess, PBFU32 pDisposition);
BFDLL BFBOOL		BFCAPI DoAboutDialog(PBFCHAR AppName, PBFCHAR Purpose);
BFDLL BFRC			BFCAPI BFErVersion(PBFU32 pMajorVersion, PBFU32 pMinorVersion);

// QTAB Functions

BFDLL BFRC			BFCAPI BFQTabModeRequest(Bd Board, BFU32 ModeRequested, PBFU32 pModeImplemented);
BFDLL BFRC			BFCAPI BFChainSIPEnable(Bd Board, PQNumPtr PhysQTabNum);
BFDLL BFRC			BFCAPI BFChainSIPDisable(Bd Board, PQNumPtr PhysQTabNum);

// Structures

BFDLL BFRC			BFCAPI BFStructItemGet(Bd Board, PBFCNF pBase, BFU32  ID, BFU32 Indx, PBFVOID pVal1, PBFVOID pVal2, PBFU32 pDisp, BFSIZET DestSize, PBFSIZET pASize);
BFDLL BFRC			BFCAPI BFStructItemSet(Bd Board, PBFCNF pBase, BFU32  ID, BFU32 Indx, PBFVOID pVal1, PBFVOID pVal2, BFSIZET SourceSize);
BFDLL BFU32			BFCAPI BFGetID(Bd Board,BFU32 GenericID);


// Timing

BFDLL BFTickPtr		BFCAPI BFTick(BFTickPtr TickPtr);
BFDLL BFU32			BFCAPI BFTickRate(void);
BFDLL BFU32			BFCAPI BFTickDelta(BFTickPtr t0, BFTickPtr t1);
BFDLL BFU32			BFCAPI BFStampRate(Bd Board);
BFDLL BFU32			BFCAPI BFStampDelta(Bd Board, BFStampPtr t0, BFStampPtr t1);
BFDLL BFU32			BFCAPI BFCurrentTimeGet(Bd Board, PBFTimeStruct Time);
BFDLL BFU32			BFCAPI BFTimeStructInit(Bd Board, PBFTimeStruct Time);
BFDLL BFU32			BFCAPI BFHiResTimeStampInit(PBFTime pStartTime);
BFDLL BFU32			BFCAPI BFHiResTimeStamp(BFTime StartTime, PBFTime pCurTime);

// Interrupts

BFDLL BFRC			BFCAPI BFInterruptGetCounters(Bd Board, PINTCOUNT pCounters);
BFDLL BFRC			BFCAPI BFInterruptGetStamps(Bd Board, PINTSTAMP pStamps, PINTCOUNT pCounters);
BFDLL BFRC			BFCAPI BFInterruptGetStampsEx(Bd Board, PINTSTAMP pStamps, PINTCOUNT pCounters, PINTMIN pMin, PINTMAX pMax, PINTSUM pSum);
BFDLL BFRC			BFCAPI BFInterruptEnableStamps(Bd Board);
BFDLL BFRC			BFCAPI BFInterruptDisableStamps(Bd Board);
BFDLL BFRC			BFCAPI BFSerIntHandlerEnable(Bd Board);
BFDLL BFRC			BFCAPI BFSerIntHandlerDisable(Bd Board);

// Version Control Functions

BFDLL BFRC			BFCAPI BFDVersion(PBFU32 pMajorVersion, PBFU32 pMinorVersion);
BFDLL BFRC			BFCAPI BFDriverVersion(PBFU32 pMajorVersion, PBFU32 pMinorVersion);
BFDLL BFRC			BFCAPI BFBuildNumber(PBFU32 pBuildNumber);


// Board Functions

BFDLL BFRC			BFCAPI BFDrvReady(BFU32 TimeoutSeconds);

// Board flavor functions

BFDLL BFBOOL		BFCAPI BFIsR2(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsRv(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsR64(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsR64Board(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsCL(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsR3(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsPMC(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsPLDA(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsKbn(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsKbn4(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsKbn2(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsKbnBase(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsKbnFull(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsNeon(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsNeonBase(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsAlta(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsAltaAN(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsAltaCO(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsAlta1(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsAlta2(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsAlta4(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsMaster(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsSlave(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsEncDiv(Bd Board);
BFDLL BFBOOL		BFCAPI BFIsNTG(Bd Board);

// Serial communication funcctions

BFDLL BFU32			BFCAPI BFSetBaudRegisters(Bd hBoard, BFU32 BaudRate);
BFDLL BFU32			BFCAPI BFGetBoardXTL(Bd hBoard);
BFDLL BFU32			BFCAPI BFUARTInit(Bd hBoard);
BFDLL BFU32			BFCAPI BFGetRegistersBaud(Bd hBoard, PBFU32 pBaudRate);
BFDLL BFRC			BFCAPI BFGetNumCLBrds(PBFU32 pNumCLBrds);

// Timers

BFDLL BFU64			BFCAPI BFClock(void);
BFDLL BFU32			BFCAPI BFClockRate(void);
BFDLL BFU32			BFCAPI BFClockDelta(BFU64 t0, BFU64 t1);
BFDLL void			BFCAPI BFClockWait(BFU32 Milliseconds);						


// misc

BFDLL BFRC			BFCAPI BFGetBoardStrings(Bd hBoard, PBFCHAR pModelSt, BFU32 ModelStLen, PBFCHAR pFamilySt, BFU32 FamilyStLen, PBFU32 pFamilyIndex, PBFU32 pCiFamily);
BFDLL BFRC			BFCAPI BFGetBoardStringsVFO(VFOPtr pVFO, PBFCHAR pModelSt, BFU32 ModelStLen, PBFCHAR pFamilySt, BFU32 FamilyStLen, PBFU32 pFamilyIndex, PBFU32 pCiFamily);
BFDLL BFRC			BFCAPI BFGetBoardStringsPCIInfo(BFU32 DeviceId, BFU32 Revision, BFU32 InfoHi, BFU32 InfoLo, BFU32 SubVendorId, PBFCHAR pModelSt, BFU32 ModelStLen, PBFCHAR pFamilySt, BFU32 FamilyStLen, PBFU32 pFamilyIndex, PBFU32 pCiFamily);
BFDLL void			BFCAPI BFOutputDebugString(PBFCHAR OutputString);
BFDLL BFRC			BFCAPI BFGetCurrentFimwareName(Bd Board, PBFCHAR FWRoot, PBFCHAR FWFileName, BFU32 FWFileNameSize);
BFDLL BFRC			BFCAPI BFGetBuildTarget(PBFU32 pTarget);
BFDLL void			BFCAPI BFReadSerialNumber(Bd Board, PBFU32 pSerialNumber);


// Alternate spellings.

#define Qtab		QTab
#define BFIsRev3	BFIsR3

#ifdef __cplusplus
}
#endif

#endif

