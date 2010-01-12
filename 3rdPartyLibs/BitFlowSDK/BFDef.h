//
// Creation:    BFDef.h
// Created:     August 21, 1997
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// BitFlow Public Definitions
//
// History:
//  Note: Andy Commented out some things that the compiler doesn't like. Search for andy within the file.
// 08/21/97     rbs     Created file.
//

#if !defined(__BFDEF__)
#define __BFDEF__

#include "BFSystem.h"
#include "BFType.h"
#include "BFBoard.h"
#include "BFTabConfig.h"
#include "BFTabRegister.h"
#include "BFTabError.h"
#include "BFVersion.h"

// Source And Destination Address Types

typedef enum _AddrType
{
	AddrTypeBoard = 0,			// Image data transfers from or to a board.
	AddrTypeVirtual,			// Image data transfers from or to virtual memory.
	AddrTypePhsyical,			// Image data transfers from or to physical memory.
	AddrTypes					// Total number of address types.		
} AddrType;	

// Acquire Engines

typedef enum _AqEngine
{
	AqEngJ = 0,
	AqEngK,
	AqEngL,
	AqEngM
} AqEngine;

// Data Fifos

typedef enum _BFFifo
{
	BFFifoA = 0,
	BFFifoB,
	BFFifoC,
	BFFifoD
} BFFifo;

// DMA Channels

typedef enum _DMAChannel
{
	DMAChannel0 = 0,
	DMAChannel1,
	DMAChannel2,
	DMAChannel3
} DMAChannelT; /** changed the type name to have a T on the end so that it compiles. **/

// LUT Mode Types

typedef enum _BFLutMode
{
    BFLut8Bit = 0, 
    BFLut12Bit,
    BFLut16Bit,
	BFLutSkip
} BFLutMode, *BFLutModePtr;

// LUT Bank Types

typedef enum _BFLutBank
{
    BFLutBank0 = 0,
    BFLutBank1,
	BFLutBank2,
	BFLutBank3,
	BFLutBypass
} BFLutBank, *BFLutBankPtr;

// LUT Lane Types

typedef enum _BFLutLane
{
    BFLutLane0      = 0x01,
    BFLutLane1      = 0x02,
    BFLutLane2      = 0x04,
    BFLutLane3      = 0x08,
    BFLutTwoLanes   = 0x03,
    BFLutFourLanes  = 0x0f
} BFLutLane, *BFLutLanePtr;

// QTab on-board banks.

typedef enum _BFQTabBank
{
    BFQTabBank0 = 0,
    BFQTabBank1,
    BFQTabBank2,
    BFQTabBank3
} BFQTabBank, *BFQTabBankPtr;

// Software Trigger Selectors

typedef enum _BFTrigSelect
{
    BFTrigA = 1,									// Select trigger A.
    BFTrigB = 2										// Select trigger B. 
} BFTrigSelect, *BFTrigSelectPtr;

// Formats

typedef enum _BFForm
{
	BFFormNI = 1, // NOTE: this needs to be 1 to match configuration files
	BFFormInterlaced
} BFForm, *BFFormPtr;

// Options for BFVQtabCreat

typedef enum _BFVQTABOptions
{
	BFOptNone = 0,
	BFOptPhysicalMemory = 1
} BFVQTABOptions, *BFVQTABOptionsPtr;

// Structured used to report board found in system.

typedef struct _BFENTRY
{
	BFCHAR	Name[MAX_STRING];
	BFU32	Number;
	BFU32	Index;
	BFBOOL	Pseudo;
	BFU32	Bus;
	BFU32	Slot;
	BFU32	Family; // only used by CiFunctions
} BFENTRY, *PBFENTRY;

// Error Dialog Responses

#define ABORT				0x0001
#define NEXT_ERROR			0x0002
#define IGNORE_ERROR		0x0003
#define TURN_ERROR_OFF 		0x0100

// Bit Field Descriptor Flags

typedef enum _BFD
{
    BFD_RO      = 1,        						// Read only bit field.
    BFD_WO      = 2,        						// Write only bit field.
    BFD_SH      = 4,        						// Shadowed write only bit field.
    BFD_IN      = 8,        						// Reads may be inconsistent with last write.
    BFD_US      = 16,       						// Unsafe to manipulate without forethought.
    BFD_IAP     = 32,       						// Indirect address/port register.
	BFD_NORMW	= 64,								// Disable read during a read-modify-write (hack for autoincrementing registers).

    BFD_NSET    = 128,								// Narrow memory object (bit field within a 32 bit register).
    BFD_WSET    = 256,								// Wide memory object (32 bit register).
    BFD_LSET    = 512								// Large memory object (large chunk of mapped memory).
} BFD;


#define BFD_MODES       (BFD_RO | BFD_WO | BFD_SH | BFD_IN | BFD_US | BFD_IAP | BFD_NORMW)
#define BFD_SIZES       (BFD_NSET | BFD_WSET | BFD_LSET)

#define BFQTabChanMax			4					// Maximum number of QTab DMA channels supported by driver software.
#define BFQTabBankMax			4					// Maximum number of QTab banks supported by the driver software.
#define BFQTabFieldMax			4					// Maximum number of QTab fields supported by the driver software.
#define BFQTabEngineMax			4					// Maximum number of QTab acquire engines supported by the driver software.

// Quad table modes.

typedef enum _QuadModes
{
	BFQTabModeBoard = 0,
	BFQTabModeHost
} QuadModes;

// Non-error return values from signal wait functions.

#define BF_SIGNAL_TIMEOUT	0x00010000
#define BF_SIGNAL_CANCEL	0x00010001 

// signal used for communicated interrupt events
typedef struct _BFSIGNAL 
{
	HANDLE	SemHandle;
	BFU32   IntType;
	BFU32   NewInts;
	BFU32	Status;
} BFSIGNAL, *PBFSIGNAL;

typedef enum _SigStat
{
	SigUp = 0,
	SigCancelled
} SigStat;

// Flash file information record.

typedef struct _BFFlashRec
{
    struct _BFFlashRec      *Next;                  // Link to next flash file record or BFNULL.
    BFBOOL                  Active;                 // Flash file is active in the registry when true. 
	BFU32					Family;					// Flash family.
	BFU32					Bytes;					// Flash file default number of data bytes.
    BFUPTR                   FileId;					// Flash file identification number (BitSet).
    BFU32                   FlashId;                // Flash type identification number.
	BFU32					PPC;					// Flash pixels per clock.
	BFCHAR					Root[MIN_STRING];		// Flash root name.
	BFCHAR					Folder[MIN_STRING];		// Flash folder name.
	BFCHAR	                Name[MAX_STRING];	    // Flash file name.
    BFCHAR                  Comment[MAX_STRING];    // Flash file description.
} BFFlashRec, *BFFlashPtr, **BFFlashTab;

// Flash options record.

typedef struct _BFFlashOpsRec
{
    BFS32   FlashDelay;                             // Download delay.
    BFS32   AdjustPercent;                          // Download delay safety adjustment value.
    BFBOOL  DelayTest;                              // Delay test and set at next download flag.
    BFBOOL  ErrorTest;                              // Delay test and set after download failure flag.
} BFFlashOpsRec, *BFFlashOpsPtr;

// Device information record.

typedef struct _BFDeviceRec
{
    struct _BFDeviceRec	*Next;						// Link to the next device record or BFNULL.
	Bd					KernelId;					// Kernel Board Id if known or BFNULL.
	VFORec				VFO;						// VFO record for this device.
} BFDeviceRec, *BFDevicePtr;

// Registry Enumeration State Record For BFRegistry EnumKey functions.

typedef struct _BFEnumStateRec
{
	HANDLE	hKey;									// Parent key handle (set this to BFNULL before first call).
	BFU32	Index;									// After each call, this will be set to the current sub-key index.
} BFEnumStateRec, *BFEnumStatePtr;

// Horizontal And Vertical Control Table Masks

typedef enum _BFCTabControl
{
    BFCTab		= 0xffff,
    BFHCTab		= 0x00ff,
    BFVCTab		= 0xff00,
    BFHCTab0	= 0x0001,
    BFHCTab1	= 0x0002,
    BFHCTab2	= 0x0004,
    BFHCTab3	= 0x0008,
    BFHCTab4	= 0x0010,
    BFHCTab5	= 0x0020,
    BFHCTab6	= 0x0040,
    BFHCTab7	= 0x0080,
    BFVCTab0	= 0x0100,
    BFVCTab1	= 0x0200, 
    BFVCTab2	= 0x0400, 
    BFVCTab3	= 0x0800, 
    BFVCTab4	= 0x1000, 
    BFVCTab5	= 0x2000, 
    BFVCTab6	= 0x4000, 
    BFVCTab7	= 0x8000 
} BFCTabControl, *BFCTabControlPtr;

// so super maximums for arrays, these are max acress all products

#define BF_MAX_CTAB_COLS 16
#define BF_MAX_MAXE 50



// link list of handles to open cameras
typedef struct _OPENCAMLIST
{
	PBFCNF OpenCam;
	BFU32  Index;
	struct _OPENCAMLIST *Next;
} OPENCAMLIST, *POPENCAMLIST;

// Locked memory descriptor.

#ifdef _WIN64
#define BF_MDL_SEG_SIZE		0x01800000												// Maximum locked segment size.
#else
#define BF_MDL_SEG_SIZE		0x03000000												// Maximum locked segment size.
#endif

typedef struct _BFMdlRec
{
	struct _BFMdlRec		*NextMdl;				// Pointer to next locked memory descriptor.
	struct _BFMdlRec		*LastMdl;				// Pointer to last locked memory descriptor.

	struct _BFMdlRec		*NextSeg;				// Pointer to next locked memory segment.

	BFUPTR					FileId;					// File id number that is unique for each open. 
	BFU32					LockCount;				// Number of times this region has been locked.
	BFUPTR					FullSize;				// Full size of the region in bytes. 
	BFSIZET					MdlSize;				// Number of Mdl bytes required to track this region.

	PBFU8					Start;					// Start address of this locked memory segment.
	PBFU8					End;					// End address of this locked memory segment.
	BFUPTR					Size;					// Size of this locked memory segment.
	PBFVOID					pMdl;					// Pointer to system structure for this locked memory segment.
} BFMdlRec, *BFMdlPtr;

// Structure for getting total interrupt counts.

typedef struct _INTCOUNT
{
	BFU32 IntCount[BFIntCount];
} INTCOUNT, *PINTCOUNT;

// Structure for getting interrupt time stamps.

typedef struct _INTSTAMP
{
	BFStampRec IntStamp[BFIntCount];
} INTSTAMP, *PINTSTAMP;

// Structure for getting interrupt time stamps min delta

typedef struct _INTMIN
{
	BFStampRec IntMin[BFIntCount];
} INTMIN, *PINTMIN;

// Structure for getting interrupt time stamps max delta

typedef struct _INTMAX
{
	BFStampRec IntMax[BFIntCount];
} INTMAX, *PINTMAX;

// Structure for getting interrupt time stamps sum

typedef struct _INTSUM
{
	BFStampRec IntSum[BFIntCount];
} INTSUM, *PINTSUM;

// defines to help decode QTAB model parameters
// VAL1 = CONTINUOUS | REPEAT | PRE/POST/NORMAL | MIRROR | RUNX8 | CHAN | RUN

#define BFENT_QMOD_RUN_M			0x0000ffff		// Length of run (in pixels!)
#define BFENT_QMOD_RUN_S			0
#define BFENT_QMOD_CHAN_M 			0x00070000		// Channel for quad to use
#define BFENT_QMOD_CHAN_S 			16
#define BFENT_QMOD_RUNX8_M 			0x00080000		// if set, multiply RUN by 8 to get actual run
#define BFENT_QMOD_RUNX8_S 			19
#define BFENT_QMOD_MIRROR_M			0x00100000		// Is this a mirror channel
#define BFENT_QMOD_MIRROR_S			20
#define BFENT_QMOD_TYPE_M			0x00600000		// Pre/post/normal/invert
#define BFENT_QMOD_TYPE_S			21
#define BFENT_QMOD_CONTINUOUS_M		0x00800000		// Is this a mirror channel in continous mode
#define BFENT_QMOD_CONTINUOUS_S		23
#define BFENT_QMOD_REPEAT_M			0xFF000000		// Number of times to repeat pre/post	// depreciated
#define BFENT_QMOD_REPEAT_S			24														// depreciated

// VAL2 = YOFFS | XOFFS

#define BFENT_QMOD_XOFFS_M			0x0000ffff		// x offset to next run (in pixels)
#define BFENT_QMOD_XOFFS_S			0          
#define BFENT_QMOD_YOFFS_M			0xffff0000		// y offset to next run (in pixels)
#define BFENT_QMOD_YOFFS_S			16  
        
// qtab model paramter types

#define QTAB_PARAM_NORMAL			0
#define QTAB_PARAM_PRE				1		// depreceated
#define QTAB_PARAM_POST				2		// depreceated
#define QTAB_PARAM_INVERTED			3

// list(s) sizes

#define BFENT_QMOD_MAXE			10
#define BFCNF_AFE_COMMAND_MAXE	250

// Transfer progress record.

typedef struct _BFProgressRec
{
	BFU32		Frame;								// Current frame number.
	BFU32		Field;								// Current field number.
	BFU32		BytesIntoField;						// Number of bytes into the current field.
	BFU32		BytesIntoFrame;						// Number of bytes into the current frame.
	BFU32		BytesIntoSequence;					// Number of bytes into the current sequence.
} BFProgressRec, *BFProgressPtr;

// Performance test results record.

typedef struct _BFSpeedsUsrRec
{
	BFU32		WidePeeksPerSec;					// Full register peek rate.
	BFU32		ThinPeeksPerSec;					// Bit field peek rate.
	BFU32		WidePokesPerSec;					// Full register poke rate.
	BFU32		ThinPokesPerSec;					// Bit field poke rate.
	BFU32		Integer32MultipliesPerSec;			// 32 bit integer multiply rate.
	BFU32		Integer64MultipliesPerSec;			// 64 bit integer multiply rate.
	BFU32		Integer32DivisionsPerSec;			// 32 bit integer division rate.
	BFU32		Integer64DivisionsPerSec;			// 64 bit integer division rate.
	BFU32		Integer32ShiftsPerSec;				// 32 bit integer shift rate.
	BFU32		Integer64ShiftsPerSec;				// 64 bit integer shift rate.
	BFU32		BFmallocBFfreePerSec;				// BFmalloc/BFfree rate.
	BFU32		BFmemcpyBytesPerSec;				// BFmemcpy byte copy rate.
	BFU32		BFmemmoveBytesPerSec;				// BFmemmove byte move rate.
	BFU32		BFInteger32BytesPerSec;				// 32 bit integer copy rate.
	BFU32		FloatMultipliesPerSec;				// Floating multiply rate.
	BFU32		DoubleMultipliesPerSec;				// Double multiply rate.
} BFSpeedsUsrRec, *BFSpeedsUsrPtr;

typedef struct _BFSpeedsKrnRec
{
	BFU32		WidePeeksPerSec;					// Full register peek rate.
	BFU32		ThinPeeksPerSec;					// Bit field peek rate.
	BFU32		WidePokesPerSec;					// Full register poke rate.
	BFU32		ThinPokesPerSec;					// Bit field poke rate.
	BFU32		Integer32MultipliesPerSec;			// 32 bit integer multiply rate.
	BFU32		Integer64MultipliesPerSec;			// 64 bit integer multiply rate.
	BFU32		Integer32DivisionsPerSec;			// 32 bit integer division rate.
	BFU32		Integer64DivisionsPerSec;			// 64 bit integer division rate.
	BFU32		Integer32ShiftsPerSec;				// 32 bit integer shift rate.
	BFU32		Integer64ShiftsPerSec;				// 64 bit integer shift rate.
	BFU32		BFmallocBFfreePerSec;				// BFmalloc/BFfree rate.
	BFU32		BFmemcpyBytesPerSec;				// BFmemcpy byte copy rate.
	BFU32		BFmemmoveBytesPerSec;				// BFmemmove byte move rate.
	BFU32		BFInteger32BytesPerSec;				// 32 bit integer copy rate.
} BFSpeedsKrnRec, *BFSpeedsKrnPtr;

// Error Monitor Information Record

typedef struct _BFErrorInfoRec
{
	BFRC		RC;									// Error code.
	ErrorMesBuf	Message;							// Error message.
	BFCHAR		DeviceName[20];						// Board's device name.
} BFErrorInfoRec, *BFErrorInfoPtr;

// BrdOpenDialog Flags

typedef enum _BOD_OPTIONS
{
	BOD_NONE				= 0x00000000,				// No restrictions
	BOD_HIDEJUSTOPEN		= 0x00000001,				// Hide just open button
	BOD_CLONLY				= 0x00000002,				// Only show CL boards.
	BOD_HIDEOPENINIT		= 0x00000004,				// Gude open init button
	BOD_BRD_NUM_NON_FAMILY	= 0x00000008,				// the return number family independent
} BOD_OPTIONS;

// BitFlow Quad Definitions

typedef void						*****PQNumPtr, ******PPQNumPtr;

// Legacy (Relative) Quad Definitions

// Legacy (Relative) Quad

typedef	struct _RQTabRec			*RQTabPtr, QTAB, *PQTAB;
typedef	struct _RQTabRec
{
	BFUPTR PCIAddress;	//64BITMOD
	BFU32 LocalAddress;
	BFU32 TransferSize;
	BFU32 NextQuad;
} RQTabRec;

// Physical Quad Definitions
// These are mainly used in the kernel, but we need
// the structures at both level so we can pass them
// back and forth

// PLX Physical Quad

typedef	union _PLXQTabRec			*PLXQTabPtr;
typedef	union _PLXQTabRec
{
	struct
	{
		BFU32 PCIAddress;
		BFU32 LocalAddress;
		BFU32 TransferSize;
		BFU32 NextQuad;
	};

	struct
	{
		BFU64 PCIAddress;
		BFU32 TransferSize;
		BFU32 VTapInfo;
	} Big;
} PLXQTabRec;

// QuickLogic Physical Quad

typedef	struct _QLQTabRec			*QLQTabPtr;
typedef	struct _QLQTabRec
{
	BFU32 PCIAddressLo;
	BFU32 PCIAddressHi;
	BFU32 UserLo;
	BFU32 UserHi;
	BFU32 TransferCommand;
	BFU32 TransferCount;
	BFU32 NextQuadLo;
	BFU32 NextQuadHi;
} QLQTabRec;

// PLDA Physical Quad

typedef	struct _PLDAQTabRec			*PLDAQTabPtr;
typedef	struct _PLDAQTabRec
{
	BFU32 PCIAddressLo;
	BFU32 PCIAddressHi;
	BFU32 TransferCount;
	BFU32 NextQuadLo;
	BFU32 NextQuadHi;	
	BFU32 Dum0; // NEEDSWORK, these are here to pad quad out so it is exactly 8 words
	BFU32 Dum2;
	BFU32 Dum3;
} PLDAQTabRec;

typedef enum _QuadType
{
	QuadTypePLX,
	QuadTypeQL,
	QuadTypePLDA,
} QuadType;

// Virtual Quad Definitions

// Virtual Quad

typedef	struct _VQTabRec			*VQTabPtr;
typedef	struct _VQTabRec
{
	BFUPTR		pSource;							// Source data address.
	BFUPTR		pDestination;						// Destination data address.
	BFU32		Size;								// Transfer size in bytes.
	AddrType	SrcType;							// Source data address type.
	AddrType	DstType;							// Destination data address type.
	BFBOOL		FieldStart:1;						// First quad in a field.
	BFBOOL		FieldEnd:1;							// Last quad in a field.
	BFBOOL		Margin:1;							// Margin quad (executed only once after an engage).
	BFBOOL		Garbage:1;							// Garbage quad (data is sent to a garbage can).
	BFBOOL		Mutant:1;							// Special non-image data quad. Data is embedded in target buffer.
	BFBOOL		ToBoard:1;							// Quad is directing data from the host to the board.
	BFBOOL		Force32:1;							// Force 32 bit PCI accesses.
	AqEngine	Engine;								// Acquire engine.
	BFFifo		Fifo;								// Data fifo.
	DMAChannelT	DMAChannel;							// DMA channel.
	BFLutMode	LutMode;							// Lut mode.
	BFLutBank	LutBank;							// Lut bank.
	BFU32		VTap;								// Virtual tap number.
} VQTabRec;

// Virtual Quad Header

typedef struct _VQTabHeadRec		*VQTabHeadPtr, **VQTabHeadPtrPtr,*RQTabHeadPtr, **RQTabHeadPtrPtr,RQTabHeadRec, QTABHEAD, *PQTABHEAD, **PPQTABHEAD; 
typedef struct _VQTabHeadRec
{
	BFU32		NumEntries;							// number of QUADs
	BFU32		Size;								// actual size of the QUAD table (in bytes)
	PBFVOID		BufferBaseAddress;					// pointer to the base address of the destination buffer
	BFU32		BufferSize;							// actual size is of the desitnation buffer
	VQTabPtr	VQuads;								// pointer to virtual quads
	RQTabPtr	RQuads;								// pointer to relative quads
    PQNumPtr	PhysQTabNum;						// associated physical QTAB number
	BFU32		Engine;								// Acquire engine quad was built for.
	BFU32		Channel;							// DMA channel quad was built for.
	BFU32		Bank;								// Bank quad was written to.
	BFU32		BankCount;							// Total bank count when quad was written.
	BFU32		BankSize;							// Maximum bank size when quad was written.
	BFU32		DestType;
	BFU32		VTapInterleave;						// Virtual tap quads must be split and interleaved.
	BFU32		VTapCount;							// Virtual tap count. 
	BFU32		LineCount;							// Number of transfer lines.
} VQTabHeadRec;

// Quad information record.

typedef struct _BFQuadInfoRec	*BFQuadInfoPtr;
typedef struct _BFQuadInfoRec
{
	BFBOOL		Found:1;							// Set True if the quad was found and loaded.
	BFBOOL		HostQuads:1;						// Set True if this quad is host based.
	BFBOOL		InChain:1;							// True if this quad is in a chained quad table. 
	BFBOOL		Written:1;							// True if this quad is written.
	BFBOOL		Overwritten:1;						// True if this quad was overwritten by another quad on the board.
	BFBOOL		Engaged:1;							// True if this quad is engaged.
	BFBOOL		Enabled:1;							// True if this quad is enabled.
	BFU32		Engine;								// Acquire engine.
	BFU32		Channel;							// DMA channel number.
	BFU32		FrameNum;							// Frame number at this point in a chained quad table. 
	BFU32		Entries;							// Number of quad tables in the quad set that contains this quad.
	BFUPTR		TotalQTableBytes;					// Number of quad table bytes in the quad set that contains this quad.
	BFUPTR		TotalTargetBytes;					// Number of destination bytes locked down by the quad set that contains this quad.
	BFSIZET		QTableBytes;						// Number of quad table bytes used by this quad table.
	BFUPTR		TargetBytes;						// Number of destination bytes locked down by this quad table.
	BFUPTR		DMABytes;							// Number of DMA bytes covered by this quad table.
	BFUPTR		TotalDMABytes;						// Number of DMA bytes covered by this quad set that contains this quad table.
	BFU32		Bank;								// This quad's bank number if written to a board.
	BFU32		BankCount;							// This quad's number of banks if written to a board.
	BFU32		BankSize;							// This quad's maximum bank size if written to a board.
	BFU32		NumQuads;							// Number of quads in this quad's quad table.
	BFU32		FieldCount;							// Number of fields in this quad's quad table.
	BFU32		FieldFirst;							// First field of frame.
	BFU32		FieldNum;							// This quad's field number. 
	PQNumPtr	PhysQTabNum;						// This quad's quad table number.
	BFUPTR		HashAddress;						// This quad's hash address.
	BFU32		PhysAddressHi;						// High 32 bits of this quad's physical address.
	BFU32		PhysAddressLo;						// Low 32 bits of this quad's physical address.
//	RQTabRec	Quad;								// The quad. 
	PLXQTabRec	PLXQuad;							// PLX Physical quad
	QLQTabRec	QLQuad;								// QL Physical quad
	PLDAQTabRec	PLDAQuad;							// PLDA Physical quad
} BFQuadInfoRec;

// LRET structures and enums

// LRET output options
typedef enum _OutputRoute
{
	CT0,
	CT1,
	CT2,
	CC1,
	CC2,
	CC3,
	CC4,
} SyncRoute;

// LRET modes
typedef enum _LRETMode
{
	MaxExp,
	ProgrammedExp,
	PulseWidth,
	TwoSignal,
} LRETMode;

// LRET proirities
typedef enum _LRETPriority
{
	Exact,
	ExposurePriority,
	LineRatePriority,
	DontCare,
} LRETPriority;

// holds the camera specific parameters used by LRET
typedef struct _LRETParam
{
	BFDOUBLE PixClkFreq;			// Pixel clock frequency in MHz
	BFU32 Priority;					// In case of conflicting LRET, which input gets priority
	BFU32 SyncToLen;				// Number of pixels clocks between Sync assert and LEN back from the camera
	BFU32 SyncOutput;				// The board's output to route the sync signal to (OutputRoute)
	BFU32 ChargeOutput;				// The board's output to route the chage signal to (OutputRoute)
	BFU32 LRETMode;					// The exposure control mode  (LRETMode)
} LRETParam, *LRETParamPtr;

// holds the LRET information used to program the CTABs
typedef struct LRETCTabSet
{
	BFU32 HStart;					// Start of horizontal active window
	BFU32 HEnd;						// End of horizontal active window
	BFU32 HReset;					// Horizontal reset
	BFU32 SyncStart0;				// Start of first Sync pulse
	BFU32 SyncSize0;				// Size of first Sync pulse
	BFU32 SyncStart1;				// Start of second Sync pulse
	BFU32 SyncSize1;				// Size of second Sync pulse
	BFU32 ChargeStart;				// Start of Charge pulse
	BFU32 ChargeSize;				// Size of Charge pules
} LRETCTabSet, *LRETCTabSetPtr;


typedef struct _BFTimeStruct
{	
	BFU32		msec; // milliseconds 0..999
	BFU32		sec;  // seconds 0..59
	BFU32		min;  // minutes 0..59
	BFU32		hour; // 0..23
	BFU32		day;  // 1..31
	BFU32		yday; // 1..366
	BFU32		mon;  // 1..12
	BFU32		year; // 19xx

}BFTimeStruct, *PBFTimeStruct;


typedef struct _BFTime
{
	BFU32	usec;	// microseconds 0..999999
	BFU32	sec;	// seconds 0..59
	BFU32	min;	// minutes 0..59
	BFU32	hour;	// 0..23
	BFU64	highResCount;
	double	totalSec;

}BFTime, *PBFTime;


typedef enum _BFGPOutPin
{
    BFGPOut0	= 0x01,							// GPOut 0.
    BFGPOut1	= 0x02,							// GPOut 1.
    BFGPOut2	= 0x04,							// GPOut 2. 
    BFGPOut3	= 0x08,							// GPOut 3.
    BFGPOut4	= 0x10,							// GPOut 4.
    BFGPOut5	= 0x20,							// GPOut 5. 
    BFGPOut6	= 0x40,							// GPOut 6. 
	BFGPOut7	= 0x80,							// GPOut 7.
	BFGPOut8	= 0x100							// GPOut 8.
} BFGPOutPin, *BFGPOutPinPtr;


// Defines for DoBrdOpenDialog

#define BRD_DLG_OK				0x0000
#define BRD_DLG_NO_BOARDS		0x0001
#define BRD_DLG_USER_CANCEL		IDCANCEL	// this if for backwards compatibility, equals 2
#define BRD_DLG_MALLOC_ERROR	0x0003
#define BRD_DLG_DRIVER_ERROR	0x0004
#define	BRD_DLG_OTHER_ERROR		0x0005
#define BRD_DLG_ONLY_ONE		0xffff		// this is an internal only message

// Defines for DispSurfFormatBlit function

#define BFDISP_FORMAT_NORMAL	0
#define BFDISP_FORMAT_CAD6		1

// Some useful macros.

#define HiPart64(Num)		((BFU32)((BFU64)Num >> 32))
#define LoPart64(Num)		((BFU32)((BFU64)Num & 0x00000000ffffffff))

#define HiPart32(Num)		((BFU16)((BFU32)Num >> 16))
#define LoPart32(Num)		((BFU16)((BFU32)Num & 0x0000ffff))

// Constants

#define BF_FORMAT_REG_WILDCARD		0x1f
#define BF_WILDCARD_STRING			"Wildcard"

// Some sizes needed here for forward referencing

#define BFR64HCTABSIZE						(32 * 1024)			// Number of horizontal CTab entries in CTab table on R64 family.
#define BFR64VCTABSIZE						(128 * 1024)		// Number of vertical CTab entries in CTab table on R64 family.

// Build targets
#define BUILD_TARGET_BITFLOW	0
#define BUILD_TARGET_LINX		1

#endif

