/***************************************************************************
*
* BFInfo.h
*
* Kernel mode driver for Windows NT.  
* Device driver structure, not seen by user mode
*
* Copyright (C) 1996 by BitFlow, Inc.  All Rights Reserved.
*
* 03/06/96	rjd		created
*
***************************************************************************/

#if !defined(__BFINFO__)
#define __BFINFO__

#include "BFSystem.h"
#include "BFType.h"
#include "BFDef.h"
#include "BFTabError.h"
#include "BFTabConfig.h"
#include "BFTabRegister.h"
#include "BFOSInfo.h"


#if defined(KernelOS)
	#include "BFBoardMapKrn.h"
	#include "BFTabRegisterPrv.h"
	#include "BFTabErrorPrv.h"
	#include "BFTabDispatchPrv.h"
	#include "BFErrorKrn.h"
	#include "BFUtilitiesBth.h"
#endif

#if !defined(KernelOS)

	// Force these types to work at user level.

	typedef BFU32   KMUTEX;
	typedef PBFVOID PDEVICE_OBJECT, PKINTERRUPT, PADAPTER_OBJECT, PFILE_OBJECT;

#endif

#if defined(_DEBUG)
	#define TRACK_SIZES		8192	// If memory tracking is enabled track all allocations up to this size.
#endif

// Board numbers used to open the BitFlow driver without an associated board.
//
// These must be enumerated to match the pseudo control device install order in BFDriverControl.

#define BFDriverOnly		0
#define R2DriverOnly		1
#define R2CLDriverOnly		2
#define RvDriverOnly		3
#define R64DriverOnly		4
#define AltaDriverOnly		5
#define AltaCODriverOnly	6

// Registry key paths.

#ifdef LINX_BUILD_TARGET

#define BFK_BITFLOW			"System\\CurrentControlSet\\Services\\LinX"
#define BFK_ROOT			"System\\CurrentControlSet\\Services\\LinX\\LinX"
#define BFK_ERRORLOG		"System\\CurrentControlSet\\Services\\EventLog\\System\\LinX"
#define BFK_FAMILY			"LinX"
#define BFK_EVENT_ENTRY		"%SystemRoot%\\System32\\Drivers\\Linx.sys"
#define BFK_DRIVER_HANDLE	"\\\\.\\LinX"
#define BFK_DRIVER_ENTRY	"LinX"

#else

#define BFK_BITFLOW			"System\\CurrentControlSet\\Services\\BitFlow"
#define BFK_ROOT			"System\\CurrentControlSet\\Services\\BitFlow\\BitFlow"
#define BFK_ERRORLOG		"System\\CurrentControlSet\\Services\\EventLog\\System\\BitFlow"
#define BFK_FAMILY			"BitFlow"
#define BFK_EVENT_ENTRY		"%SystemRoot%\\System32\\Drivers\\BitFlow.sys"
#define BFK_DRIVER_HANDLE	"\\\\.\\BitFlow"
#define BFK_DRIVER_ENTRY	"BitFlow"

#endif

#define BFK_DEVICE			"BFDev"
#define BFK_BOARD			"BoardParam"
#define BFK_FLASH			"Flash"
#define BFK_BOARD_NUMBER	"BoardNumber"
#define BFK_DEVICENAME		"DeviceFileName"
#define BFK_MOVED_FROM		"MovedFrom"
#define BFK_DIRNAME			"BFConfigDir"
#define BFK_CAMLIST			"BFCamList"
#define BFK_DMATIMEOUT		"DMATimeout"
#define BFK_DMALATENCY		"DMAMasterLatency"
#define BFK_OTHERLAT		"OtherDMALatency"	    // latency for other bus mastering devices
#define BFK_VGAADDR			"VGABaseAddress"	    // latency for other bus mastering devices
#define BFK_NOSNOOPSET		"NoSnoopSet"
#define BFK_DATE_TIME		"CfgDateTime"
#define BFK_DEVICE_ID		"CfgDeviceId"
#define BFK_INFO_HI			"CfgInfoHi"
#define BFK_INFO_LO			"CfgInfoLo"
#define BFK_REVISION		"CfgRevision"
#define BFK_SUBSYS_ID		"CfgSubSystemId"
#define BFK_SUBVEND_ID		"CfgSubVendorId"
#define BFK_SWITCH			"CfgSwitch"
#define BFK_VENDOR_ID		"CfgVendorId"
#define BFK_OVERRIDE		"Override"
#define BFK_BUS				"CfgDeviceBus"
#define BFK_SLOT			"CfgDeviceSlot"
#define BFK_FUNCTION		"CfgDeviceFunction"
#define BFK_MASTER_BOARD	"MasterBoardNum"
#define BFK_FLASHMEM_SERIAL	"CfgFMSerial"
#define BFK_FLASHMEM_REV	"CfgFMRevision"
#define BFK_FLASHMEM_DATE	"CfgFMDate"
#define BFK_FLASHMEM_IPL	"CfgFMIPLevel"


#define BFK_FLASH_DELAY		"BFFlashDelay"			// Flash download delay. 
#define BFK_FLASH_ADJ_PCNT	"BFFlashAdjustPercent"  // Delay safety adjustment amount.
#define BFK_FLASH_DLY_TEST	"BFFlashDelayTest"      // If non-zero, calculate download delay during next download.
#define BFK_FLASH_ERR_TEST	"BFFlashErrorTest"      // If non-zero, calculate download delay after download errors.
#define BFK_FLASH_ERR_HITS	"BFFlashErrorHits"      // Number of times download failed and delay was reset.

// Magic numbers.

#define DRIVER_INFO_MAGIC	0x16180339				// Hexified golden ratio digits.
#define INFO_KRN_MAGIC		0x31415926				// You should recognize it!
#define INFO_USR_MAGIC		0x14142136				// Square root of 2.
#define QUAD_TABLE_MAGIC	0x27182818				// e!
#define BAD_LUCK_MAGIC		0x13131313				// Magic number for dead structures.

// Driver callback function states for driver/device startup/cleanup functions.

typedef enum _DrvStates
{
	DrvSetup,										// Perform standard setup actions.
	DrvClean,										// Perform standard cleanup actions.
	DrvSetupPseudo,									// Perform standard pseudo device setup.
	DrvSetupPseudoCL,								// Perform CameraLink pseudo device setup.
	DrvSetupPseudoAnalog,							// Perform Analog pseudo device setup.
	DrvSetupPseudoAnalogCo							// Perform Analog Composite pseudo device setup.
} DrvStates;

// Driver initialization states.

typedef enum _DriverInitStates
{
	DriverInitBuild = 0,							// Build the driver data structures.
	DriverInitStart,								// Start the driver.
	DriverInitEnd									// End of driver states.
} DriverInitStates;

// Board delayed flash status states
typedef enum _DelayedFlashState
{
	DelayedFlashBooting,							// Start State, system is booting, board is not flashed
	DelayedFlashDownloaded,							// Board has been downloaded but not flashed
	DelayedFlashFlashed								// Boad has been downloaded
} DelayedFlashState;
// Driver State Record

typedef struct _StateTableRec		*StateTablePtr, *pStateTable;
typedef struct _StateTableRec
{
	DriverStates		State;						// Driver state.
	PBFCHAR				Name;						// Driver state name.
} StateTableRec;

// QTab Hash Table definitions.

#if defined(KernelOS)

#define QTAB_HASH_MASK		BitMask(13, 0)			// Hash mask used to convert Physical QTab Id to hash table key.
#define	QTAB_HASH_SIZE		(QTAB_HASH_MASK + 1)	// Number of entries in the Physical QTab hash table.
	
#endif

// QTab bank sizes, small bank is when board is in two bank mode, big when it is in single bank mode.

#define MAX_PQTAB_SMALL_BANK				4096
#define MAX_PQTAB_BIG_BANK					8192
#define MAX_PQTAB_SIZE						0x8000

// QTab local address tag bits.

#define BF_DMA_QUAD_LOCAL_FIF				(1<<0)
#define BF_DMA_QUAD_LOCAL_LIF				(1<<1)
#define BF_DMA_QUAD_LOCAL_ONCEONLY			(1<<2)

// QTab next quad address attribute bits.

#define BF_DMA_QUAD_ATTR_MASK				0xff800000
#define BF_DMA_QUAD_NEXT_MASK				0x0000000f
#define BF_DMA_QUAD_NEXT_HOST				(1<<0)
#define BF_DMA_QUAD_NEXT_EOC				(1<<1)
#define BF_DMA_QUAD_NEXT_INT				(1<<2)
#define BF_DMA_QUAD_NEXT_WRITE				(1<<3)

// QTAB attributes

#define BF_DMA_QUAD_LOCAL_EOX			(1UL<<23)
#define BF_DMA_QUAD_LOCAL_BANK			(1UL<<24)
#define BF_DMA_QUAD_LOCAL_BYPASS		(1UL<<25)
#define BF_DMA_QUAD_LOCAL_BY8			(1UL<<26)
#define BF_DMA_QUAD_LOCAL_MCHSEL0		(1UL<<27)
#define BF_DMA_QUAD_LOCAL_MCHSEL1		(1UL<<28)
#define BF_DMA_QUAD_LOCAL_FLUSH			(1UL<<29)

// FIFO locations on the R3/R3
#define BF_R2_QTAB_FIFO_ADDR			0x1f0000
#define BF_R2_CL_QTAB_FIFO_ADDR			0xC0000


// QTab flush quad size.

#define FLUSH_QUAD_SIZE						0x24

// QTab byte alignment sizes.

#define PLX_QUAD_ALIGNMENT					4		// PLX quads must be on four byte boundaries.
#define QL_QUAD_ALIGNMENT					8		// QuickLogic quads must be on eight byte boundaries.

// Unadvertised modes.

#define BF_UNADDMODE_NOCOMBINEQUADS			0x0001
#define BF_UNADDMODE_HOSTVGAGARBAGE			0x0002
#define BF_UNADDMODE_FASTQTABDOWNLOAD		0x0004

// Maximum garbage memory to allocate.

#define GARBAGECANSIZE						8192

// Serial port buffer size

#define BFSerialPortBufSize					32768	// 32K

// Structure for IRP used to communicate interrupt status.

typedef struct _INTINFOIRP				*PINTINFOIRP;
typedef struct _INTINFOIRP
{
	BFU32 IntCount[BFIntCount];
	BFU32 IntDiff[BFIntCount];
	BFU32 FirstTime;
} INTINFOIRP;

// PCI DMA write commands.

typedef enum _PciWriteCommands
{
	PciRead				= 0x6,
	PciWrite			= 0x7,
	PciReadMultiple		= 0xc,
	PciReadLine			= 0xe,
	PciWriteInvalidate	= 0xf
} PciWriteCommands;

// DMA engines

typedef enum _DMAEngines
{
	BF_DMA_PLDA,
	BF_DMA_QL,
	BF_DMA_PLX
} DMAEngines;

//
// Quad Modifiers Structure
//
// This structure encapsulates board specific differences between physical quad 
// types to facilitate physical quad construction using generic BFQTab functions.
//

typedef struct _BFModsRec				*BFModsPtr;
typedef struct _BFModsRec
{
	BFU32				Engine;				// Acquire engine.
	BFU32				Channel;			// DMA channel number.
	BFU32				NumFields;			// Number of interlaced fields.
	BFU32				NumChannels;		// Number of DMA channels.
	BFU32				DMAEngine;			// type of DMA engine (PLX, QL, PLDA)
	BFBOOL				HostQuads;			// Set True if host quads are enabled.
	BFBOOL				SixtyFourBitQuads;			// Set True if 64 bit quads are enabled (QL or PLDA).
	BFBOOL				PLDAQuads;			// Set True if PLDA quads are built
	BFBOOL				TwoInOne;			// Set True if two in one channel DMA is enabled. 
	BFBOOL				FFAInline;			// Set True if inline FFA tables are required.
	BFBOOL				FieldEOC;			// EOC required at end of each field.
	BFU32				FirstFieldNumber;	// Set to the field number that always arrives first.
	BFU32				AttrShiftCount0;	// Attribute shift count zero.
	BFU32				AttrShiftMask0;		// Attribute shift count zero mask.
	BFU32				StartAddress;		// On-board quad start address.
	BFU32				ControlAddress;		// Control quad address. 
	BFU32				FirstInFieldBit;	// First in field tag bit.
	BFU32				LastInFieldBit;		// Last in field tag bit.
	BFU32				OnceOnlyBit;		// Only execute this quad once.
	BFU32				EngineKBit;			// Acquire engine K selection bit.
	BFU32				FlushBit;			// Quad flush bit.
	BFU32				FlushQuadSize;		// FLush quad size
	BFU32				LutBankMask;		// Mask to strip out lut bank number.
	BFU32				LutBankOne;			// Lut bank one set bits.
	BFU32				EOXBit;				// EOX bit.
	BFU32				RegOddQuadStart;	// Register where first odd field quad start number is written.
	BFU32				RegPCIAddress;		// Register where destination address is written.
	BFU32				RegLocalAddress;	// Register where source address is written.
	BFU32				RegTransferSize;	// Register where transfer size is written.
	BFU32				RegNextQuad;		// Register where start address is written.
	BFU32				RegDMADone;			// Register bit used to indicate DMA done.
	BFU32				HostBit;			// Set for host QTABs
	BFU32				DMAWrite;			// Set for DMA write to host
	BFU32				IntBit;				// Set for interrupt on quad
	BFU32				LocalAddress;		// Local address of FIFO
	BFU32				BypassBit;			// Set to Bypass LUT
	BFU32				By8Bit;				// set to put LUTs in By 8 mode
	BFU32				FIFOFChan0Bit;		// First bit of FIFO select bit
	BFU32				FIFOFChan1Bit;		// Second bit of FIFO select bit
	BFU32				UsingVQTabs;		// Flag to indicate the VQTabs were built
} BFModsRec;

// Serial port read data structure

typedef struct _BFSerialPort			*BFSerialPortPtr;
typedef struct _BFSerialPort
{
	BFU32		IndxInUART;
	BFU32		IndxInUser;
	BFU8		InBuffer[BFSerialPortBufSize];		// In from camera buffer
} BFSerialPort;

// Structure name and size structure.

typedef struct _MaybeRec *MaybePtr;
typedef struct _MaybeRec
{
	BFU32		Size;		// Structure size.
	PBFCHAR		Name;		// Structure name.
	MaybePtr	Next;		// Next strucure.
} MaybeRec;

// Flash source file info record.

typedef struct _SRC_InfoRec
{
    struct _SRC_InfoRec *Next;                      // Next file in source file list.
	BFU32				Family;						// Device family for this flash file.
    BFU32               FlashId;                    // Flash file Id.
	BFCHAR	            Name[MAX_STRING];		    // Flash gate array source file name.
    BFCHAR              Comment[MAX_STRING];        // Source file description.
    BFBOOL              Present;                    // File is out there.
} SRC_InfoRec, *SRC_InfoPtr;

// Flash gate array bits.

typedef struct _BitSetRec
{
    struct _BitSetRec   *Next;		                // Next gate array bit set.

	PBFVOID				Pack;                       // First packed bit list record points to PackIt record start.
	BFCHAR				Root[MIN_STRING];			// Flash file root name.
	BFCHAR				Name[MAX_STRING];			// Flash file full name (without extension).
	SRC_InfoPtr			Info;                       // Each custom bit list record points to a file information record.
	BFBOOL				Standard:1;					// True for standard flash bit data.
	BFBOOL				Custom:1;					// True for custom flash bit data.
	BFBOOL				Tag:1;						// True for a custom flash comment tag.
	BFU32				Family;						// Flash device family.
    BFU32               FlashId;                    // Flash file Id.
    PBFU8		        BitData;	                // Gate array bit data.
    BFU32		        BitCount;	                // Gate array bit count.
	
	// Parsed header information taken from the 
	// original source file.

	PBFCHAR				HeaderPtr;					// Header pointer.
	BFU32				HeaderCnt;					// Header byte count.

	PBFCHAR				FileFormatPtr;				// Flash file format pointer.
	BFU32				FileFormatCnt;				// Flash file format byte count.
	BFU32				FileFormat;					// Flash file format.
	PBFCHAR				SourcePtr;					// Source file name pointer.
	BFU32				SourceCnt;					// Source file name byte count.
	PBFCHAR				RevisionPtr;				// File revision pointer.
	BFU32				RevisionCnt;				// File revision byte count.
	BFU32				RevisionMajor;				// File revision major.
	BFU32				RevisionMinorNum;			// File revision minor numerator.
	BFU32				RevisionMinorDen;			// File revision minor denominator.
	PBFCHAR				DatePtr;					// Compile date pointer.
	BFU32				DateCnt;					// Compile date byte count.
	PBFCHAR				FileSizePtr;				// File size pointer.
	BFU32				FileSizeCnt;				// File size byte count.
	BFU32				FileSize;					// File size in gate array bytes.
	PBFCHAR				HardwareRevPtr;				// Hardware revision pointer.
	BFU32				HardwareRevCnt;				// Hardware revision byte count.
	BFU32				HardwareRevMajor;			// Hardware revision major.
	BFU32				HardwareRevMinorNum;		// Hardware revision minor numerator.
	BFU32				HardwareRevMinorDen;		// Hardware revision minor denominator.
	PBFCHAR				ProductPtr;					// Product name pointer.
	BFU32				ProductCnt;					// Product name byte count.
	PBFCHAR				PPCPtr;						// Pixels per clock pointer.
	BFU32				PPCCnt;						// Pixels per clock byte count.
	BFU32				PPC;						// Pixels per clock.
	PBFCHAR				LoadTagPtr;					// Flash load tag pointer.
	BFU32				LoadTagCnt;					// Flash load tag byte count.
	BFU32				LoadTag;					// Flash load tag.
	PBFCHAR				SelectorPtr;				// Selector pointer.
	BFU32				SelectorCnt;				// Selector byte count.
	PBFCHAR				SelectorCustomPtr;			// Custom selector pointer.
	BFU32				SelectorCustomCnt;			// Custom selector byte count.
	PBFCHAR				DataStartPtr;				// Data CRC start pointer.
	BFU32				DataStartCnt;				// Data CRC start count.
	PBFCHAR				DataEndPtr;					// Data CRC end pointer.
	BFU32				DataEndCnt;					// Data CRC end count.
	PBFCHAR				HeadStartPtr;				// Header CRC start pointer.
	BFU32				HeadStartCnt;				// Header CRC start count.
	PBFCHAR				HeadEndPtr;					// Header CRC end pointer.
	BFU32				HeadEndCnt;					// Header CRC end count.
	PBFCHAR				DataCRCPtr;					// Flash data CRC pointer.
	BFU32				DataCRCCnt;					// Flash data CRC byte count.
	BFU32				DataCRC;					// Flash data CRC.
	PBFCHAR				CRCPtr;						// Flash file combined CRC pointer.
	BFU32				CRCCnt;						// Flash file combined CRC byte count.
	BFU32				CRC;						// Flash file combined CRC.
	PBFCHAR				F1HeadCRCPtr;				// Flash format 1 header CRC pointer.
	BFU32				F1HeadCRCCnt;				// Flash format 1 header CRC byte count.
	BFU32				F1HeadCRC;					// Flash format 1 header CRC.
	PBFCHAR				F1DataCRCPtr;				// Flash format 1 data CRC pointer.
	BFU32				F1DataCRCCnt;				// Flash format 1 data CRC byte count.
	BFU32				F1DataCRC;					// Flash format 1 data CRC.
} BitSetRec, *BitSetPtr;


// The following section is for user level only definitions.

#if !defined(KernelOS)

    // Interrupt event thread states.

    typedef enum _BFIntThreadState
    {
        BFIntThreadStarting,                // Interrupt event notification thread has been requested to start.
        BFIntThreadStarted,                 // Interrupt event notification thread has begun. 
        BFIntThreadWaiting,                 // Interrupt event notification thread is waiting for interrupts.
        BFIntThreadRunning,                 // Interrupt event notification thread is processing interrupts.
        BFIntThreadStopping,                // Interrupt event notification thread has been requested to stop.
        BFIntThreadStopped                  // Interrupt event notification thread has stopped. 
    } BFIntThreadState;

    // link list to hold signals

    typedef struct _BFSIGNALLIST		*PBFSIGNALLIST;
    typedef struct _BFSIGNALLIST
    {
	    PBFSIGNAL		Signal;
	    PBFSIGNALLIST	Next;

    } BFSIGNALLIST;

	// Function type for a board specific interrupt enable/disable function.

	typedef BFBOOL (*PBFINTENABLE)(Bd Board, BFU32 Type, BFBOOL Enable);	

    // BitFlow Driver's user level device information record.

	typedef struct _BFInfoUsr			*BFInfoUsrPtr, *pBFInfoUsr;
    typedef struct _BFInfoUsr
    {
        BFU32				Magic;						// Set to INFO_USR_MAGIC when DeviceHandle is good.
		HANDLE				DeviceHandle;				// User level driver handle.
		PBFVOID				pXXInfoUsr;					// Device specific user level information pointer.
		OSInfoUsrPtr		pOSInfoUsr;					// Device specific user level OS specific information pointer.
		BFU32				Status;						// Board status.
	    PBFSIGNALLIST		gSignalHead[BFIntCount];	// list of signal for board, needs to be initialize;
	    HANDLE				hSignalMutex;				// Handle of mutex used to protect interrupt signal linked list
		BFU32				DmaTimeout;					// Timeout length for DMA operations.
		BFU32				OldQTabMode;				// set to use old QTAB mode (only works on R3/R3)


		// Interrupt stuff.
		
		HANDLE				IntThread;					// Handle to interrupt notification thread.
	    HANDLE				IntEvent;					// Handle to event is for asyn IO in interrupt thread.
	    BFIntThreadState	IntThreadState;				// Current execution state of interrupt notification thread.
        BFBOOL				IntThreadStopRequest;		// Set True to tell interrupt notification thread to die.
	    PBFINTENABLE		BoardIntEnable;				// Board specific interrupt enable/disable function.
		PBFU32				IntEnableCount;				// Count number of signals created, disable interrupt when last signal is freed.
		HANDLE				hIntCountMap;				// handle to shared memory used to store IntEnableCount

		// Interrupt GPOUT jitter diagnostics.

		BFU32				IntGPOUT;					// GPOUT line settings for interrupt diagnostic tracing.
		BFU8				IntGPOUTService;			// GPOUT line for interrupt service routine tracing.
		BFU8				IntGPOUTDPC;				// GPOUT line for interrupt DPC routine tracing.
		BFU8				IntGPOUTSignal;				// GPOUT line for interrupt signal routine tracing.
		BFU8				IntGPOUTQueue;				// GPOUT line for interrupt queue routine tracing.

		BFU32				IntJitterGPOUT;				// GPOUT line settings for jitter detection signalling.
		BFU8				IntJitterGPOUTService;		// Jitter detection GPOUT line for service interrupts.
		BFU8				IntJitterGPOUTDPC;			// Jitter detection GPOUT line for DPC interrupts.
		BFU8				IntJitterGPOUTSignal;		// Jitter detection GPOUT line for signal interrupts.
		BFU8				IntJitterGPOUTQueue;		// Jitter detection GPOUT line for queue interrupts.

		BFU32				IntJitterThresh;			// Jitter detection thresholds.
		BFU8				IntJitterThreshService;		// Jitter threshold for service interrupts.
		BFU8				IntJitterThreshDPC;			// Jitter threshold for DPC interrupts.
		BFU8				IntJitterThreshSignal;		// Jitter threshold for signal interrupts.
		BFU8				IntJitterThreshQueue;		// Jitter threshold for queue interrupts.

		BFU64				IntJitterStampSignal;		// Time stamp of last signal interrupt.
		BFU64				IntJitterDeltaSignal;		// Latency in microseconds before last signal interrupt.

		BFU64				IntJitterStampQueue;		// Time stamp of last queue interrupt.
		BFU64				IntJitterDeltaQueue;		// Latency in microseconds before last queue interrupt.

		// Device Configuration Information

		VFOPtr				pVFO;						// Vendor, Family and Options record. 

        // Registry key names.

        BFCHAR				DeviceName[20];				// Board's device name.

        BFCHAR				DriverKey[80];				// Driver registry key (BitFlow).
		BFCHAR				FamilyKey[100];				// Family registry key (BitFlow\<family>).
        BFCHAR				BoardKey[120];				// Device registry key (BitFlow\<family>\BoardParam#).
        BFCHAR				FlashKey[140];				// Flash registry key (BitFlow\<family>\BoardParam#\Flash).

        // Translation table to convert a register number to a BitField register Id.
    
        BFU16				*RegToId;					// Convert a sequential register number to a BitFieldId number.
        BFU16				RegCount;					// Number of registers in RegToId table.

		// Camera file stuff.
		
		PBFCNF				pCurCam;					// Current camera.
		POPENCAMLIST		pOpenCamList;				// Open camera files.

		// Interrupt Stuff

		HANDLE				hSerialMap;					// handle to shared memory used to store serial port buffer points
		BFSerialPortPtr		pBFSerialPort;				// serial port circular buffer

		// Host copy of RLE CTabs Stuff (only on RLE CTabs boards)

		HANDLE				hHostCTabMap;				// handle to shared memory used to store host CTAbs for RLE boards
		PBFU8				pVRLECTab;					// Vertical host copy of CTabs for RLE boards
		PBFU8				pHRLECTab;					// Vertical host copy of CTabs for RLE boards

		// translation table for configuration tokens

		PBFU32				pTransTable;

    } BFInfoUsr;

    // Useful macros to get things out of the device info block.

	#define GetBFInfo(BoardId)			(BoardId != BFNULL && ((pBFInfoUsr)BoardId)->Magic == INFO_USR_MAGIC ? (pBFInfoUsr)BoardId : BFNULL)
	#define GetOSInfo(BoardId)			(BoardId != BFNULL && ((pBFInfoUsr)BoardId)->Magic == INFO_USR_MAGIC ? ((pBFInfoUsr)BoardId)->pOSInfoUsr : BFNULL)
	#define GetVFO(BoardId)				(BoardId != BFNULL && ((pBFInfoUsr)BoardId)->Magic == INFO_USR_MAGIC ? ((pBFInfoUsr)BoardId)->pVFO : BFNULL)

#endif          // User level definitions.

// The following section is for Kernel only definitions.

#if defined(KernelOS)

	// Function type for any function that takes the Board Id and returns an error.

	typedef BFRC	BFC		(*BFBoardFuncPtr)(Bd BoardId);

	// Function type for driver/device setup/clean functions.

	typedef BFRC	BFC		(*BFSetupFuncPtr)			(Bd BoardId, DrvStates State);

	// Function types for an interrupt detect and reset functions.

	typedef BFU32	BFC		(*IntDetectFuncPtr)			(Bd Board);
	typedef BFBOOL	BFC		(*IntResetFuncPtr)			(Bd Board, BFU32 Status);
	typedef void	BFC		(*IntUpdateFuncPtr)			(Bd Board, BFU32 Status, BFU64 Stamp);

    // Per process device information record.

    typedef struct _ProcessRec			*ProcessPtr;
    typedef struct _ProcessRec
    {
        ProcessPtr			Next;						// Pointer to next process record in the list.
        BFUPTR               Process;					// Process handle for process that has this device open.
        BFU32               DeviceOpensThisProcess;		// Number of device opens for this process.
    } ProcessRec;

    // Per handle device information record.

    typedef struct _FileHndRec			*FileHndPtr;
    typedef struct _FileHndRec
    {
        FileHndPtr			Next;						// Pointer to next file handle record in the list.
        PFILE_OBJECT        FileObject;					// File object for file handle that has this device open.
        BFBOOL              DeviceInitializedHandle;	// If True, this file handle initialized the device.
    } FileHndRec;

    // Interrupt status record used to hold queued interrupt status information.

    typedef struct _IntStatusRec		*IntStatusPtr;
    typedef struct _IntStatusRec
    {
        BFU32				Status;						// Interrupt status.
		BFU64				Stamp;						// Interrupt time stamp.
    } IntStatusRec;


	// Physical Quad Set and Quad Table Headers

	typedef struct _PQSetHeadRec		*PQSetHeadPtr;
	typedef struct _PQTabHeadRec		*PQTabHeadPtr, **PQTabHeadPtrPtr;

	// PQTab Table Header

	typedef struct _PQTabTableRec		*PQTabTablePtr;
	typedef struct _PQTabTableRec
	{
		PQTabHeadPtrPtr	Base;							// Table's base address.
		BFU32			Entries;						// Number of entries in the PQTab table.
		BFU32			Head;							// Index of first non-empty table entry.
		BFU32			Tail;							// Index of last non-empty table entry.
	} PQTabTableRec;

	// Physical Quad Set Header

	typedef struct _PQSetHeadRec
	{
		PQSetHeadPtr	NextPQSet;						// Pointer to the next quad table set header.
		PQSetHeadPtr	LastPQSet;						// Pointer to the last quad table set header.

		BFBOOL			Loose:1;						// True if this is a loose header.
		BFBOOL			Chain:1;						// True if this is a chain header.

		PQTabHeadPtr	List;							// First quad table in the quad table list.
		PQTabHeadPtr	Active;							// First active quad table in the quad table list.
		PQTabHeadPtr	Inactive;						// First inactive quad table in the quad table list.

		PQTabTableRec	Tab;							// Table of quad tables when Table is True.

		BFU32			PQSetTableCount;				// Number of quad tables in this physical quad set.
		BFUPTR			PQSetQTableBytes;				// Number of quad table bytes used by this physical quad set.
		BFUPTR			PQSetTargetBytes;				// Number of destination bytes targeted by this physical quad set.
		BFUPTR			PQSetDMABytes;					// Number of DMA bytes for this quad set
	} PQSetHeadRec;

	// Physical Quad Table Header

	typedef struct _PQTabHeadRec
	{
		BFU32			Magic;							// Magic number set when quad table is inserted into a quad list.
		BFUPTR			HashAddress;					// Hash address for this quad table.
		PQSetHeadPtr	PQSetHeader;					// Quad table set header. 
		BFUPTR			FileId;							// File id number that is unique for each open. 
		BFU32			FrameNum;						// Frame number for this quad table in a chain or frame table. 

		PQTabHeadPtr	HashNext;						// Next quad table in a hash quad table list.
		PQTabHeadPtr	HashLast;						// Last quad table in a hash quad table list.

		PQTabHeadPtr	ListNext;						// Next quad table in the quad table list.
		PQTabHeadPtr	ListLast;						// Last quad table in the quad table list.

		PQTabHeadPtr	ActiveNext;						// Next active quad table in the quad table list.
		PQTabHeadPtr	ActiveLast;						// Last active quad table in the quad table list.

		PQTabHeadPtr	InactiveNext;					// Next inactive quad table in the quad table list.
		PQTabHeadPtr	InactiveLast;					// Last inactive quad table in the quad table list.

		BFModsPtr		pMods;							// Board specific quad table modifiers.
		BFBOOL			Written:1;						// True if this quad table is written to a board.
		BFBOOL			Overwritten:1;					// True if this quad table has been overwritten.
		BFBOOL			Enabled:1;						// True if this quad table is enabled.
		BFSIZET			QTableBytes;					// Number of quad table bytes used by this quad table.
		BFUPTR			TargetBytes;					// Number of destination bytes targeted by this quad table.
		BFUPTR			DMABytes;						// Number of DMA bytes covered by this quad table.
		BFU32			Bank;							// Bank number.
		BFU32			BankCount;						// Number of banks.
		BFU32			BankSize;						// Current maximum bank size.
		BFU32			ActualNumEntries;				// Number of quads that are filled.
		BFU32			AllocatedEntries;				// Maximum number of quads allocated.
		BFMdlPtr		pBFMdl;							// Large buffer Mdl for user destination buffer in user space.
		PBFVOID			pQuadBuffer;					// Pointer to entire (unaligned) quad table buffer.
		PLXQTabPtr		pQuads;							// Physical quad table pointer.
		PBFVOID			pQLQuadsBuffer;						// Pointer to entire (unaligned) 64 bit quad table buffer.
		QLQTabPtr		pQLQuads;						// Physical 64 bit quad table pointer.
		PBFVOID			pPLDAQuadsBuffer;					// Pointer to entire (unaligned) PLDA 64 bit quad table buffer.
		PLDAQTabPtr		pPLDAQuads;						// PLDA Physical 64 bit quad table pointer.
		BFU32			Margin;							// start address for host based 32-bit QTABs
		BFU32			BigTotal;						// Total number of big quads allocated.
		BFU32			BigTaken;						// Total number of big quads used.
		BFU64			BigMargin;						// Address of the margin quad (tail tag quad that kicks things off).
		BFU64			BigFirst;						// Address of the first big quad (header tag quad).
		BFU64			pBigTrash;						// Garbage can address used to store tag quad trash bytes. 
		PBFVOID			Tracker;						// VTap tracking queues.
		BFU32			FieldCount;						// Number of fields.
		BFU32			FieldFirst;						// First field of frame.
		PLXQTabPtr		FieldMargin[BFQTabFieldMax];	// Pointers to each field margin descriptor.
		PLXQTabPtr		FieldStarts[BFQTabFieldMax];	// Pointers to each field start descriptor.
		PLXQTabPtr		FieldEnds[BFQTabFieldMax];		// Pointers to each field end descriptor.
		BFU32			FieldSizes[BFQTabFieldMax];		// Field size in bytes for each field.
		BFU32			FieldMarginPhys[BFQTabFieldMax];// Physical address of each field margin descriptor.
		BFU32			FieldStartsPhys[BFQTabFieldMax];// Physical address of each field start descriptor.
		PVOID			pQuadMapRegisterBase;			// Map registers used for MapTransfer
		PSCATTER_GATHER_LIST pScatterGatherList;
		PVOID			pNextQuadRegisterBase;
	} PQTabHeadRec;

	// Hash Table List Header

	typedef struct _HashListRec			*HashListPtr;
	typedef struct _HashListRec
	{
		PQTabHeadPtr	pHead;
		PQTabHeadPtr	pTail;
	} HashListRec;

	// BitFlow driver's kernel level file handle information.

	typedef struct _FHInfoKrnRec		*FHInfoKrnPtr;
    typedef struct _FHInfoKrnRec 
    {
        BFU32				Magic;						// Magic value set to INFO_KRN_MAGIC when block is good.
		FHInfoKrnPtr		Next;						// Pointer to next file handle information block.
		PBFVOID				FileId;						// File object that owns this information block.
	} FHInfoKrnRec;


	// BitFlow driver's kernel level driver information.
		 
	typedef struct _BFDriverInfoKrn		*BFDriverInfoKrnPtr, *pBFDriverInfoKrn;
	typedef struct _BFDriverInfoKrn
	{
		BFU32				Magic;						// Magic number that is set to DRIVER_INFO_MAGIC after allocation.
		StateTablePtr		pDriverState;				// Pointer to the current driver state.
		BFBOOL				LoadReinit;					// Set True to force loading of the driver reinitialization routine.
		DriverInitStates	InitState;					// The current driver reinitialization state.
		struct _BFInfoKrn	*pBFInfoHead;				// Head of the board specific information record list.
		struct _BFInfoKrn	*pBFInfoTail;				// Tail of the board specific information record list.
		OSDriverInfoKrnPtr	pOSDriverInfo;				// System specific driver information record. 
		BFU32				BoardCount;					// Number of BitFlow boards installed.
		DispatchTablePtr	DispatchTables;				// List of BitFlow dispatch tables.
		BFBOOL				FirstStart;					// Cleared to False just before the first device is started.

		// Driver level flags that are loaded from the
		// registry by BFDriverFlags during driver startup. 
		// These flags are stored in the registry at:
		//
		// HKEY_LOCAL_MACHINE\CurrentControlSet\Services\BitFlow

		BFBOOL				DriverTest;					// Set True to enable testing of new driver functions.
		BFBOOL				Reinitialize;				// Set True to enable driver reinitialization.
		BFBOOL				UseGat;						// Set True to enable old style flash download GAT file creation.
		BFBOOL				Verbose;					// Set True to enable verbose debug messages.
		BFBOOL				EnumerateByLookup;			// Set True to enable board enumeration lookup tables.
		BFBOOL				SmartInsert;				// Set True to enable smart registry device insertion.
		BFBOOL				SuperFineEnabled;			// Set True to enable super fine download delay timing.
		BFBOOL				HalGetSetAvoid;				// Set True to disable calls to HalGet & HalSet functions.
		BFBOOL				Legacy;						// Set True to enable the Plug'n'Play driver's legacy mode.
		BFBOOL				DelayedFlashAllowed;		// When True, delayed flashing is allowed

		BFBOOL				Stop00All;					// Set True to enable driver exit after driver builds BFDriverInfo.
		BFBOOL				Stop01Controls;				// Set True to enable driver exit after driver creates pseudo devices.
		BFBOOL				Stop02Devices;				// Set True to enable driver exit after driver creates real devices.
		BFBOOL				Stop03Flash;				// Set True to enable skipping flash downloads.
		BFBOOL				Stop04Interrupts;			// Set True to enable skipping interrupt connections.

		BFBOOL				DownloadInProgress;			// Set to true when any Karbon or Alta is being downloaded


		// Standard driver entry callbacks.

		BFSetupFuncPtr		BFDriverBuild;				// Allocate driver information structures.
		BFSetupFuncPtr		BFDriverSetup;				// Setup the driver.
		BFSetupFuncPtr		BFDriverControl;			// Create driver control devices.
		BFBoardFuncPtr		BFDriverUnload;				// Unload the driver.

		// Board specific driver entry eallbacks.

		BFSetupFuncPtr		OSDriverBuild;				// Allocate driver information structures.
		BFSetupFuncPtr		OSDriverSetup;				// Setup the driver.
		BFSetupFuncPtr		OSDriverControl;			// Create driver control devices.
		BFBoardFuncPtr		OSDriverUnload;				// Unload the driver.

		// Registry path string for each board family.

		PBFCHAR				BFRoot;						// Registry device path to BitFlow.
		PBFCHAR				R2Root;						// Registry device path to RoadRunner.
		PBFCHAR				R64Root;					// Registry device path to R64.
		PBFCHAR				RvRoot;						// Registry device path to Raven.

		// Global board count settings for each board family.

		BFBOOL				BFDoneCleaning;				// Set True after pseudo BitFlow device registry cleaning.
		BFU32				BFNumBoards;				// Number of pseudo BitFlow boards.

		BFU32				BFNumCLBoards;				// Number of CL boards 

		BFBOOL				R2DoneCleaning;				// Set True after RoadRunner device registry cleaning.
		BFU32				R2NumBoards;				// Number of RoadRunner boards.

		BFBOOL				R64DoneCleaning;			// Set True after R64 device registry cleaning.
		BFU32				R64NumBoards;				// Number of R64 boards.

		BFBOOL				RvDoneCleaning;				// Set True after Raven device registry cleaning.
		BFU32				RvNumBoards;				// Number of Raven boards.


		// Global registry flag load indicators and flags for each board family.

		BFBOOL				R2DoneFlags;				// Set True after RoadRunner registry flags are loaded.
		BFBOOL				R2Test;						// Set True to enable testing of new RoadRunner functions.
		BFBOOL				R2Stop00All;				// Set True to enable exit after driver builds R2Info.
		BFBOOL				R2MatchDeviceId;			// Set True to enable device id matching during insertion.
		BFBOOL				R2MatchSubVendorId;			// Set True to enable subvendor id matching during insertion.
		BFBOOL				R2MatchSubSystemId;			// Set True to enable subsystem id matching during insertion.
		BFBOOL				R2MatchRevision;			// Set True to enable revision matching during insertion.

		BFBOOL				R64DoneFlags;				// Set True after R64 registry flags are loaded.
		BFBOOL				R64Test;					// Set True to enable testing of new R64 functions.
		BFBOOL				R64Stop00All;				// Set True to enable exit after driver builds R64Info.
		BFBOOL				R64MatchDeviceId;			// Set True to enable device id matching during insertion.
		BFBOOL				R64MatchSubVendorId;		// Set True to enable subvendor id matching during insertion.
		BFBOOL				R64MatchSubSystemId;		// Set True to enable subsystem id matching during insertion.
		BFBOOL				R64MatchRevision;			// Set True to enable revision matching during insertion.
		BFBOOL				R64MatchInfoHi;				// Set True to enable InfoHi matching during insertion.
		BFBOOL				R64MatchInfoLo;				// Set True to enable InfoLo matching during insertion.
		BFU32				R64MatchInfoHiMask;			// Mask used when matching InfoHi
		BFU32				R64MatchInfoLoMask;			// Mask used when matching InfoLo

		BFBOOL				RvDoneFlags;				// Set True after Raven registry flags are loaded.
		BFBOOL				RvTest;						// Set True to enable testing of new Raven functions.
		BFBOOL				RvStop00All;				// Set True to enable exit after driver builds RvInfo.
		BFBOOL				RvMatchDeviceId;			// Set True to enable device id matching during insertion.
		BFBOOL				RvMatchSubVendorId;			// Set True to enable subvendor id matching during insertion.
		BFBOOL				RvMatchSubSystemId;			// Set True to enable subsystem id matching during insertion.
		BFBOOL				RvMatchRevision;			// Set True to enable revision matching during insertion.

		// Error EventViewer stall settings to control waits
		// for event records in order to get messages out to
		// the event viewer.

		BFU32				ErrRetries;					// Set to the number 1/10 second waits to do before giving up.
		BFU32				ErrStalls;					// Stall counter.
		BFU32				ErrGiveUps;					// Lost message counter.

		// Error monitor queue.

		BFErrMonClientPtr	ErrMonClients;				// Error monitor client list.
		BFU32				ErrMonCount;				// Number of errors in the error monitor queue.
		BFU32				ErrMonLimit;				// Maximum number of errors allowed in monitor queue.
		BFU32				ErrMonFirst;				// Number of the first error in the error monitor queue.
		BFU32				ErrMonLast;					// Number of the last error in the error monitor queue.
		BFErrMonPtr			ErrMonHead;					// Error monitor queue head.
		BFErrMonPtr			ErrMonTail;					// Error monitor queue tail. 

		// BFSuperFineWait timing constants.

		BFBOOL				TickStuffSet;				// Set True after the BFSuperFineWait constants are set.
		BFU32				TicksPerSecond;				// Number of fine grain clock ticks per second.
		BFU32				TicksPerClock;				// Number of fine grain clock ticks per clock (true clock granularity).
		BFU32				MicroPerClock;				// Number of microseconds per clock (true clock granularity in microseconds).
		BFU32				NanoPerClock;				// Number of nanoseconds per clock (true clock granularity in nanoseconds).
		BFU32				MicroDelayCount;			// Delay loop constant that should produce a one microsecond delay.

		// Memory leak detection stuff.

		#if defined(_DEBUG)

			BFBOOL				FindLeaks;				// Set True to enable leak detection.
			BFBOOL				WatchMem;				// Set True to trap specific sized allocations.
			BFU32				WatchSize;				// Memory allocation size to watch for when WatchMem is True.
			BFBOOL				LeakTest13;				// Set True to enable a 13 byte memory leak test.
			BFBOOL				StuckOn;				// Set True if leak detection is stuck on for safety.
			BFBOOL				LinkEm;					// Set True until SizeNames table is constructed.
			BFU32				GetCount;				// Number of small allocations.
			BFU32				BigGetCount;			// Number of large allocations (>= SIZES_TO_TRACK).
			BFU32				FreeCount;				// Number of small releases.
			BFU32				BigFreeCount;			// Number of big releases.
			BFU32				MultipleRelease;		// Number of multiple release errors detected.
			BFU32				DamagedHead;			// Number of damaged headers detected.
			BFU32				DamagedTail;			// Number of damaged tails detected.

			BFU32				SizeCount[TRACK_SIZES];	// Number of small allocations of specific sizes.
			MaybePtr			SizeNames[TRACK_SIZES];	// Names of structures of specific sizes.

		#endif

	} BFDriverInfoKrn;

	// BitFlow driver's kernel level device information record.

	typedef struct _BFInfoKrn			*BFInfoKrnPtr, *pBFInfoKrn;
    typedef struct _BFInfoKrn 
    {
        BFU32				Magic;						// Magic value set to INFO_KRN_MAGIC when record is good.
		StateTablePtr		pDeviceState;				// Pointer to the current device state.
		BFU32				Junky;						// Junk value that is free for debugging.
		BFInfoKrnPtr		pNext;						// Next record in the board specific information record list.
		BFInfoKrnPtr		pLast;						// Last record in the board specific information record list.
		BFDriverInfoKrnPtr	pBFDriverInfo;				// Link to driver information record. 
		OSDriverInfoKrnPtr	pOSDriverInfo;				// Link to system specific driver information record. 
	    PBFVOID				pXXInfoKrn;					// Device specific kernel level information pointer.
		OSInfoKrnPtr		pOSInfoKrn;					// Device specific kernel level OS specific information pointer.
		FHInfoKrnPtr		pFHInfoList;				// File handle information list.
		PBFCHAR				pFamily;					// Device family name.
		PBFCHAR				pDevice;					// Device name root.
		BFBOOL				PseudoDevice;				// Set True if this is a pseudo device.
		BFBOOL				HaveResources;				// Resources have been allocated to this device. 
	    BFBOOL				BoardMapped;				// Flag set when registers are mapped.
		BFBOOL				BoardFlashed;				// Flag set after flash is downloaded.
        BFBOOL				GoodToGo;					// Set True if all tables are good and the device is mapped.
		BFBOOL				RegTrace;					// When True, register peeks and pokes are dumped.
		BFBOOL				TimeTrace;					// When True, timing trace information is collected and can be dumped.
		BFBOOL				CallTrace;					// When True, driver calls are dumped.
		BFBOOL				DownloadFlash;				// When True, gate array flash will be downloaded during startup.
		BFBOOL				QuadStats;					// When True, quad statistics are dumped out.
		BFU32				VendorIdNukeCount;			// Number of times the Vendor Id was nuked.
		BFBOOL				DelayedFlash;				// When True, board will be downloaded but not flashed at startup
		BFU32				DelayedFlashedStatus;		// Flag that tells the delayed flash system the current status of the board
		PBFVOID				FlashCloseFunction;			// function flash the board if delayed flash is used

        // Registry key names.

        BFCHAR				DeviceName[20];				// Board's device name.
        BFCHAR				DriverKey[80];				// Driver key (BitFlow).
		BFCHAR				FamilyKey[100];				// Family key (BitFlow\<family>).
        BFCHAR				BoardKey[120];				// Device key (BitFlow\<family>\BoardParam#).
        BFCHAR				FlashKey[140];				// Flash key (BitFlow\<family>\BoardParam#\Flash).

		// Device Configuration Information

		VFOPtr				pVFO;						// Vendor, Family and Options record.
		BFCHAR				CfgSpace[256];				// Copy of the default configuration space

		// Pointers back to global settings for this board family.

		PBFBOOL				pDoneFlags;					// Set True after done reading family specific registry flags.
		PBFBOOL				pDoneCleaning;				// Set True after cleaning device registry for this board type.
		PBFU32				pNumBoards;					// Number of boards of this type.
		PBFBOOL				pMatchDeviceId;				// Set True to enable device id matching during insertion.
		PBFBOOL				pMatchSubVendorId;			// Set True to enable subvendor id matching during insertion.
		PBFBOOL				pMatchSubSystemId;			// Set True to enable subsystem id matching during insertion.
		PBFBOOL				pMatchRevision;				// Set True to enable revision matching during insertion.
		PBFBOOL				pMatchInfoHi;				// Set True to enable InfoHi matching during insertion.
		PBFBOOL				pMatchInfoLo;				// Set True to enable InfoLo matching during insertion.
		PBFU32				pMatchInfoHiMask;			// Bits used for comparing InfoHi 
		PBFU32				pMatchInfoLoMask;			// Bits used for comparing InfoLo

		// If any of these are True, some flags in the next section may be set after the board is mapped.

		BFBOOL				PLXOnBoard;					// Set True if board contains a PLX gate array.
		BFBOOL				QLOnBoard;					// Set True if board contains a QuickLogic gate array.

		// If the board supports any of the following items, these flags will be
		// set after the board is mapped (setting these requires register reads).

		BFBOOL				PLX9080;					// Set True if board contains a PLX-9080.
		BFBOOL				QuadsOnBoard;				// On board quads available.
		BFBOOL				QuadsOffBoard;				// Off board quads available.

		// Standard driver entry callbacks.

		BFSetupFuncPtr		BFBuild;					// Allocate BF structures for a new board.
		BFSetupFuncPtr		BFSetup;					// Setup a new board.
		BFSetupFuncPtr		BFDevice;					// Create device name.
		BFSetupFuncPtr		BFResources;				// Allocate driver resources.
		BFSetupFuncPtr		BFBoardMap;					// Map the BitFlow board.
		BFSetupFuncPtr		BFBoardFlash;				// Download flash to the BitFlow FPGA.
		BFSetupFuncPtr		BFBoardStart;				// Start the BitFlow board.

		BFBoardFuncPtr		BFPNP;						// Handle a Plug 'n' Play request.
		BFBoardFuncPtr		BFCreate;					// User level create device handle request.
		BFBoardFuncPtr		BFClose;					// Device handle closed and all pending Irps are complete.
		BFBoardFuncPtr		BFCleanup;					// Device handle closed and pending Irps need to be canceled.
		BFBoardFuncPtr		BFDeviceControl;			// Handle a user level DeviceIoControl request.

		// Board specific driver entry callbacks.

		BFSetupFuncPtr		XXBuild;					// Allocate XX structures for a new board.
		BFSetupFuncPtr		XXSetup;					// Setup a new board.
		BFSetupFuncPtr		XXDevice;					// Create device name.
		BFSetupFuncPtr		XXResources;				// Allocate driver resources.
		BFSetupFuncPtr		XXBoardMap;					// Map the BitFlow board.
		BFSetupFuncPtr		XXBoardFlash;				// Download flash to the BitFlow FPGA.
		BFSetupFuncPtr		XXBoardStart;				// Start the BitFlow board.

		BFBoardFuncPtr		XXPNP;						// Handle a Plug 'n' Play request.
		BFBoardFuncPtr		XXCreate;					// User level create device handle request.
		BFBoardFuncPtr		XXClose;					// Device handle closed and all pending Irps are complete.
		BFBoardFuncPtr		XXCleanup;					// Device handle closed and pending Irps need to be canceled.
		BFBoardFuncPtr		XXDeviceControl;			// Handle a user level DeviceIoControl request.

		// System specific driver entry callbacks.

		BFSetupFuncPtr		OSBuild;					// Allocate OS structures for a new board.
		BFSetupFuncPtr		OSSetup;					// Setup a new board.
		BFSetupFuncPtr		OSDevice;					// Create device name.
		BFSetupFuncPtr		OSResources;				// Allocate driver resources.
		BFSetupFuncPtr		OSBoardMap;					// Map the BitFlow board.
		BFSetupFuncPtr		OSBoardFlash;				// Download flash to the BitFlow FPGA.
		BFSetupFuncPtr		OSBoardStart;				// Start the BitFlow board.

		BFBoardFuncPtr		OSPNP;						// Handle a Plug 'n' Play request.
		BFBoardFuncPtr		OSCreate;					// User level create device handle request.
		BFBoardFuncPtr		OSClose;					// Device handle closed and all pending Irps are complete.
		BFBoardFuncPtr		OSCleanup;					// Device handle closed and pending Irps need to be canceled.
		BFBoardFuncPtr		OSDeviceControl;			// Handle a user level DeviceIoControl request.

        // Error tracking options.

        ErrOptPtr			ErrorEvent;
        ErrOptPtr			ErrorDebugger;
        ErrOptPtr			ErrorDialog;
        ErrOptPtr			ErrorFile;
		ErrOptPtr			ErrorMonitor;
        ErrOptPtr			ErrorBreakUser;
        ErrOptPtr			ErrorBreakKernel;

        // Error tracking list. 

        BFU32				TrackDepth;					// Track list depth. 
        BFU32				TrackEntries;				// Number of error records in tracking list.
        ErrTrackPtr			TrackHead;					// First record in error tracking list.

		// Error speed limiter.

		BFBOOL				ErrorTimeSpeeder;			// Set True when errors have passed the speed limit.
		BFU32				ErrorTimeErrors;			// Number of errors since ErrorTimeMark was reset.
		BFU64				ErrorTimeMark;				// The time when ErrorTimeErrors was reset.
		BFU32				ErrorTimeLimit;				// ErrorTimeMark reset interval in milliseconds.
		BFU32				ErrorTimeCount;				// Maximum number of error allowed during ErrorTimeLimit interval. 
		BFU32				ErrorTimeFilter;			// Type of errors that are speed limited. 

	    // Flag set when work need to be performed in DPC.

	    BFBOOL				DpcRequested;
	    BFBOOL				SignalWaiting;

		// DMA stuff. 

		BFBOOL				IntStampEnabled;			// Set True to enable interrupt time stamps. 
		BFU32				IntHooksEnabled;			// Set greater than one to enable interrupt hooks.
		BFU32				IntCounter;					// Counter for all interrupts (used to protect critical code).
		BFU32				IntBusy;					// Interrupt service routine busy flag.
		BFU32				IntInDPC;					// Set True while in a DPC routine.
		IntStatusRec		IntQueue[BFIntQueueCount];	// Interrupt status queue to hold interrupts in order.
		IntStatusPtr		IntStartPtr;				// Pointer to the start of IntQue. Used for wrap around.
		IntStatusPtr		IntEndPtr;					// Pointer to the end of IntQue. Used for wrap around.
		IntStatusPtr		IntPutPtr;					// First free status location in IntQue.
		IntStatusPtr		IntGetPtr;					// If GetPtr is not equal to PutPtr it points to a valid status.
		IntDetectFuncPtr	IntDetect;					// Interrupt detect function.
		IntResetFuncPtr		IntReset;					// Interrupt reset function.
		IntUpdateFuncPtr	IntUpdate;					// Update interrupt counters and time stamps function.
	    BFU32				IntCount[BFIntCount];		// Counter for number of interrupts that have come in.
		BFU64				IntStamp[BFIntCount];		// Interrupt time stamps.
		BFU32				IntHooks[BFIntCount];		// Interrupt hook counts.
		BFBOOL				IntAlive[BFIntCount];		// Interrupt hook enable flags. 
		BFBoardFuncPtr		IntFuncs[BFIntCount];		// Interrupt hook functions. 

		// IntStamp Statistics

		BFU64				IntStampMin[BFIntCount];	// Minimum time between two stamps.
		BFU64				IntStampMax[BFIntCount];	// Maximum time between two stamps.
		BFU64				IntStampSum[BFIntCount];	// Sum of differences between two time stamps.

		// Interrupt GPOUT jitter diagnostics.

		BFU32				IntGPOUT;					// GPOUT line settings for interrupt diagnostic tracing.
		BFU8				IntGPOUTService;			// GPOUT line for interrupt service routine tracing.
		BFU8				IntGPOUTDPC;				// GPOUT line for interrupt DPC routine tracing.
		BFU8				IntGPOUTSignal;				// GPOUT line for interrupt signal routine tracing.
		BFU8				IntGPOUTQueue;				// GPOUT line for interrupt queue routine tracing.

		BFU32				IntJitterGPOUT;				// GPOUT line settings for jitter detection signalling.
		BFU8				IntJitterGPOUTService;		// Jitter detection GPOUT line for service interrupts.
		BFU8				IntJitterGPOUTDPC;			// Jitter detection GPOUT line for DPC interrupts.
		BFU8				IntJitterGPOUTSignal;		// Jitter detection GPOUT line for signal interrupts.
		BFU8				IntJitterGPOUTQueue;		// Jitter detection GPOUT line for queue interrupts.

		BFU32				IntJitterThresh;			// Jitter detection thresholds.
		BFU8				IntJitterThreshService;		// Jitter threshold for service interrupts.
		BFU8				IntJitterThreshDPC;			// Jitter threshold for DPC interrupts.
		BFU8				IntJitterThreshSignal;		// Jitter threshold for signal interrupts.
		BFU8				IntJitterThreshQueue;		// Jitter threshold for queue interrupts.

		BFU64				IntJitterStampService;		// Time stamp of last service interrupt.
		BFU64				IntJitterDeltaService;		// Latency in microseconds before last service interrupt.

		BFU64				IntJitterStampDPC;			// Time stamp of last DPC interrupt.
		BFU64				IntJitterDeltaDPC;			// Latency in microseconds before last DPC interrupt.

		// Start-Stop interrupt processing stuff.

		BFU32				SIPEnable;					// SIP enable flag (inc/dec each time SIP is enabled/disabled).
		BFU32				SIPFrame;					// SIP frame count.
		PQSetHeadPtr		SIPChain;					// SIP quad chain header.
		BFU32				SIPFrameCount;				// Number of frames in SIP quad chain.
		PQNumPtr			SIPPhysQTabNum;				// Phys QTab number of quate use for sip

		// DPC timing statistics.
		//
		// Latency (SIPLat) is the time in microseconds 
		// between the SIP CTAB intterrupt and the start 
		// of the SIP DPC handler.
		//
		// DPC duration (SIPDPC) is the time in microseconds
		// between the start of the SIP DPC handler and 
		// the end of the SIP DPC handler.

		BFBOOL				SIPTiming;					// Set True to enable SIP DPC latency and duration timings.

		BFU32				SIPLatTotal;				// SIP DPC latency time accumulator in microseconds.
		BFU32				SIPLatMax;					// SIP DPC latency maximum in microseconds.
		BFU32				SIPLatMin;					// SIP DPC latency minimum in microseconds.

		BFU32				SIPDPCTotal;				// SIP DPC duration accumulator in microseconds.
		BFU32				SIPDPCMax;					// SIP DPC duration maximum in microseconds.
		BFU32				SIPDPCMin;					// SIP DPC duration minimum in microseconds.

		BFU32				SIPSamples;					// SIP latency and DPC duration sample count.

		// Each board needs its own garbage can (for throw away pixels).

	    PBFU8				pGarbageCanVirt; 
	    BFU64				pGarbageCanPhys;

	    BFU32				UnAdModes;					// Unadvertise behaviour modes from the registry.

        // Base address register table.

        MapObjRec			BAR[BaseRegCount];			// Large enough BAR table to hold the maximum possible number of BARs.

        // Table of mapped board registers and other memory regions.

        MemObjPtr			MemObjects;					// Memory object table.

        // Translation table to convert a register number to a BitField register Id.
    
        BFU16				*RegToId;					// Convert a sequential register number to a BitFieldId number.
        BFU16				RegCount;					// Number of registers in RegToId table.

        // Device open counts and flags.

        BFBOOL				DeviceInitialized;			// If True, the device was initialized by a currently open file handle.
        BFBOOL				DeviceOpensLocked;			// If True, only one open file handle is allowed.
        BFU32				DeviceOpensCount;			// Number of open file handles.
        ProcessPtr			DeviceOpensPerProcess;		// First record that stores number of opens for each process.
        FileHndPtr			DeviceFileHndContext;		// First record that stores context information for each file handle.

		// Physical quad table information.

		HashListPtr			PhysQTabHash;				// Hash table that contains all physical quad tables.
		BFU32				PhysQTabHashCount;			// Number of physical quad tables in the hash table.
		BFUPTR				PhysQTabHashAddress;		// Hash address of the last physical quad table inserted into the hash table.
		BFUPTR				PhysQTabHashMask;			// Hash table mask.
		BFU32				PhysQTabHashSize;			// Hash table size (number of entries).

		PQSetHeadPtr		PhysQSetList;				// List of physical quad sets.

		PQSetHeadPtr		PhysQSetEngaged;			// Pointer to the engaged physical quad set.
		PQTabHeadPtr		PhysQTabEngaged;			// Pointer to the engaged physical quad table.

		// List of large locked memory regions.

		BFMdlPtr			BigLockList;

		// Interrupt Stuff

		BFSerialPortPtr		pBFSerialPort;				// serial port circular buffer
    
	} BFInfoKrn;

    // Useful macros to get things out of the device info block.

	#define GetBFDriverInfo(BoardId)	(BoardId != BFNULL && ((pBFDriverInfoKrn)BoardId)->Magic == DRIVER_INFO_MAGIC ? (pBFDriverInfoKrn)BoardId : BoardId != BFNULL && ((pBFInfoKrn)BoardId)->Magic == INFO_KRN_MAGIC ? ((pBFInfoKrn)BoardId)->pBFDriverInfo : BFNULL)
	#define GetOSDriverInfo(BoardId)	(BoardId != BFNULL && ((pBFDriverInfoKrn)BoardId)->Magic == DRIVER_INFO_MAGIC ? ((pBFDriverInfoKrn)BoardId)->pOSDriverInfo : BoardId != BFNULL && ((pBFInfoKrn)BoardId)->Magic == INFO_KRN_MAGIC ? ((pBFInfoKrn)BoardId)->pOSDriverInfo : BFNULL)
	#define GetBFInfo(BoardId)			(BoardId != BFNULL && ((pBFInfoKrn)BoardId)->Magic == INFO_KRN_MAGIC ? (pBFInfoKrn)BoardId : BFNULL)
	#define GetOSInfo(BoardId)			(BoardId != BFNULL && ((pBFInfoKrn)BoardId)->Magic == INFO_KRN_MAGIC ? ((pBFInfoKrn)BoardId)->pOSInfoKrn : BFNULL)
	#define GetBFVTab(BoardId)			(BoardId != BFNULL && ((pBFInfoKrn)BoardId)->Magic == INFO_KRN_MAGIC ? ((pBFInfoKrn)BoardId)->MemObjects : BFNULL)
	#define GetVFO(BoardId)				(BoardId != BFNULL && ((pBFInfoKrn)BoardId)->Magic == INFO_KRN_MAGIC ? ((pBFInfoKrn)BoardId)->pVFO : BFNULL)

#endif          // Kernel level definitions.

#endif

