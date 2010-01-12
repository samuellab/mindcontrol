/**************************************************************************
*
* BiDef.h
*
* BufIn API
* 
* Types and defines for Bi library
*
* Copyright (C) 1999 by BitFlow, Inc.  All Rights Reserved.
*
* 06/25/99	sms		created
*
**************************************************************************/

#include "BFDef.h"
#include "CiApi.h"
#include <time.h>
#include "BFIODef.h"

#if !defined(__BIDEF__)
    #define __BIDEF__


#define MINWRKSIZE  0x1000000
#define PAGE_SIZE	0x1000


/////////////////
// Board Types 
#define BiTypeR2					CISYS_TYPE_R2	// RoadRunner 
#define BiTypeRv					CISYS_TYPE_RV	// Raven 
#define BiTypeR64					CISYS_TYPE_R64  // R64 
#define BiTypeAny					0xFFFFFFFF		// First board seen in the system 

// return for BiErrorShow
#define BI_CANCEL					1


///////////////////////////////////
// Parameters for BiBrdInquire() 

// RoadRunner and Raven Parameters 
#define BiBrdInqModel					CiBrdInqModel					// Return Board Model 
#define BiBrdInqIDReg					CiBrdInqIDReg					// ID switch on the board 
// RoadRunner Parameters 
#define BiBrdInqSpeed					CiBrdInqSpeed					// Board receivers speed 
#define BiBrdInqLUT						CiBrdInqLUT						// type of LUT mounted to the board 
// Raven Parameters 
#define BiBrdInqScanType				CiBrdInqScanType				// Scan type 
#define BiBrdInqColorDecoder			CiBrdInqColorDecoder			// NTSC/PAL decoder 
#define BiBrdInqAnalogType				CiBrdInqAnalogType				// analog video input board 
#define BiBrdInqNumCams					CiBrdInqNumCams					// Number of cameras the board is setup for 

// RoadRunner and Raven Parameters 
#define BiCamInqXSize					CiCamInqXSize					// Width of image in pixels 
#define BiCamInqYSize0					CiCamInqYSize0					// Height of image in lines 
#define BiCamInqFormat					CiCamInqFormat					// Image format 
#define BiCamInqBitsPerPix				CiCamInqPixBitDepth				// Depth of pixel in bits, as acquired to host 
#define BiCamInqBytesPerPix				CiCamInqBytesPerPix				// Depth of pixel in bytes, as acquired to host 
#define BiCamInqAqTimeout				CiCamInqAqTimeout				// Number of mS to wait before Acq. command 
#define BiCamInqFrameSize0				CiCamInqFrameSize0				// Total size of image in bytes, as acq. to host 
#define BiCamInqFrameWidth				CiCamInqFrameWidth				// Width of image in bytes, as acq. to host 
#define BiCamInqBytesPerPixDisplay		CiCamInqBytesPerPixDisplay		// Depth of pixel in bytes, as acq. to display 
#define BiCamInqBitsPerPixDisplay		CiCamInqPixBitDepthDisplay		// Depth of pixel in bits, as acq. to display 
#define BiCamInqDisplayFrameSize0		CiCamInqDisplayFrameSize0		// Total size of image in bytes, as acq. to display 
#define BiCamInqDisplayFrameWidth		CiCamInqDisplayFrameWidth		// Width of image in bytes, as acq. to display 
// RoadRunner Parameters will give an error for Raven 
#define BiCamInqBitsPerSequence			CiCamInqBitsPerSequence			// Depth of multi-channel pixel in bits, as acq. to host 
#define BiCamInqBitsPerSequenceDisplay	CiCamInqBitsPerSequenceDisplay	// Depth of multi-channel pixel in bits, as acq. to display 
#define BiCamInqCamType					CiCamInqCamType					// Which camera type 
#define BiCamInqControlType				CiCamInqControlType				// Type of camera control accessible through API 
// Raven Parameters will give an error for RoadRunner 
#define BiCamInqYSize1					CiCamInqYSize1					// Camera 1 height of image in lines 
#define BiCamInqYSize2					CiCamInqYSize2					// Camera 2 height of image in lines 
#define BiCamInqYSize3					CiCamInqYSize3					// Camera 3 height of image in lines 
#define BiCamInqFrameSize1				CiCamInqFrameSize1				// Camera 1 total size of image in bytes, as acq. to host 
#define BiCamInqFrameSize2				CiCamInqFrameSize2				// Camera 2 total size of image in bytes, as acq. to host 
#define BiCamInqFrameSize3				CiCamInqFrameSize3				// Camera 3 total size of image in bytes, as acq. to host 



/////////////////////////////////////////
// Parameters for Triggering Functions 

#define BiTrigFreeRun					CiTrigFreeRun
#define BiTrigContinuousData			CiTrigContinuousData
#define BiTrigOneShot					CiTrigOneShot
#define BiTrigOneShotJbyAandKbyB		20
#define BiTrigOneShotStartStop			21
#define BiTrigOneShotSSJbyAandKbyB		22
#define BiTrigOneShotStartAStopB		23
#define BiTrigAqCmd						CiTrigAqCmd
#define BiTrigAqCmdJbyAandKbyB			25
#define BiTrigAqCmdFreezeCmd			CiTrigAqCmdStartStop
#define BiTrigAqCmdFrzCmdJbyAandKFree	26
#define BiTrigOneShotSelfTrig			CiTrigOneShotSelfTriggered
#define BiTrigModeUnknown				CiTrigModeUnknown
#define BiTrigOneShotStartAStopALevel	CiTrigOneShotStartAStopALevel
#define BiTrigSnapQualified				BFTrigSnapQualified
#define BiTrigNTGOneShot				CiTrigNTGOneShot

// For Polarity 
#define BiTrigAssertedHigh				30
#define BiTrigAssertedLow				31
#define BiTrigAHighBLow					32
#define BiTrigALowBHigh					33

// For BiTrigForce 
#define BiTrigAssertTrigA				40
#define BiTrigAssertTrigB				41
#define BiTrigDeassertTrigA				42
#define BiTrigDeassertTrigB				43


//////////////////////////////////
// Compatibility for old defines

#define BIRC BFRC

//////////////////////////////////
// BiAqSetupSequence parameters 

// Options 
#define BiAqEngJ						4
#define BiAqEngK						8
#define NoResetOnError					16
#define AbortMissedFrame				32
#define DisableAqErrorSig				64
#define UseHighResTimer					128
#define InvertEvenFrames				256
#define InvertOddFrames					512
#define OnlyOddLines					1024
#define OnlyEvenLines					2048

// BiSeqControl and BiCirControl options 
#define BiWait							256
#define BiAsync							512


///////////////////
// Thread states 
#define NormalAbort		2               // thread has been killed by normal means. ex. all buffers are in 
#define ErrorAbort		3               // thread killed itself due to error 
#define SignalCancel	4



///////////////////////////////////////////
// BiSeqControl & BiCirControl parameters 
#define BISTART			0
#define BISTOP			1
#define BIPAUSE			2
#define BIRESUME		3
#define BIABORT			4



//////////////////////////
// BiDiskI/O paramenters
#define BIBMP			0
#define BITIF			1
#define BIAVI			2
#define BIRAW			3


////////////////////////////
// Options 
#define SwapRGB			SWAPRGB
#define Pack32to24Bit	PACK32TO24BIT
#define Cam_CAD6		CAD6



/////////////////////////////////
// Circular buffer error modes 
#define CirErStop		0
#define CirErLast		1
#define CirErNew		2
#define CirErIgnore		3

/////////////////////////////////
// How memory is allocated
#define BufferAlloc			0xf001
#define BufferAllocAligned	0xf002
#define BufferAssign		0xf003


////////////////////////////
// Curcular buffer status 
#define BIAVAILABLE		0
#define BIFRESH			1
#define BINEW			2
#define BIHOLD			3
#define BIQUEUED		4

#define AVAIL_Q_EMPTY		0xFFFFFFFF	// the available queue is empty

////////////////
// Structures 

// This structure is used by BiSeqBufferStatus to get infomation
// about the image in the sequence of buffers.
typedef struct _BiSeqInfo
{
	BFU32		 FrameCount;
	BFTimeStruct TimeStamp;
	BFTime		 HiResTimeStamp;
	BFU32		 NumLinesAcquired;

}BiSeqInfo, *PBiSeqInfo;


// This structure is used for the internal queue. BFQNodes
// are placed and removed from the queue.
typedef struct _QueueNode
{
	BFU32			Status;
	PBFU32			pBuffer;
	BFU32			FrameCount;
	BFTimeStruct	TimeStamp;
	BFTime			HiResTimeStamp;
	BFU32			BufferNumber;
	BFU32			NumLinesAcquired;
	BFU32			NumItemsOnQueue;
	struct _QueueNode *Next;

}BFQNode, *PBFQNode;



/////////////////////////////////////////////////////////////////////
// This sturcture is used as a parameter in BiCirWaitNext, BiCirMark, 
// BiCirStatus and BiCirSetNext, to pass info about the linked list.
 
typedef struct _BiCirHandle
{
	PBFU32			pBufData;			// A pointer to the image data buffer.
	BFU32			FrameCount;			// The frame count for a node in the link list.
	BFTimeStruct	TimeStamp;
	BFTime			HiResTimeStamp;		// The time stamp of the acquired image.
	BFU32			BufferNumber;		// The buffer number the image is in.
	BFU32			NumLinesAcquired;
	BFU32			NumItemsOnQueue;	// The number of frames that have not 
										// been remvoed from the buffer queue.
	PBFQNode		pNode;				// A pointer to the node in the linked list .
	
}BiCirHandle, *PBiCirHandle;


typedef struct _BFBUFARY
{
	// Set by BiAlloc() 
	BFU32			NumBuffers;					// The number of buffers that have been allocated by BiAlloc() 
	BFU32			BufferSize;					// The size of the each buffer that has be allocated 
	PBFU32			*BufferArry;				// An array of pointers pointing to each of the buffers 
	PBFU32			BufferMem;					// FrameSize * Number of buffers + Page size 

	// Set by SeqParameters() 
	BFU32			StartFrame;					// The first buffer to acquire into 
	BFU32			NumOfFrames;				// The number of frame to acquire 
	BFU32			SkipFrames;					// The number of frames to skip between captures 

	// Used by Circular 
	BFU32			CirErrorMode;				// CirErStop, CirErLast or CirErNew 
	PBFQNode		BufinQHead;					// Pointer to the first node in the bufin queue 
	PBFQNode		BufinQTail;					// Pointer to the last item in the bufin queue 
	PBFQNode		BufinQRetrieve;				// Points to the bufin node to be retrieved by BiCirWaitNext 
	PBFQNode		BufinQStore;				// Points to the next bufin node to stored data into 			
	BFU32			BufinQCount;				// Counts the number of items in the bufin queue
	BFBOOL			SIPEnabled;					// TRUE <=> SIP is enabled
	HANDLE			StatusSetMutex;				// Mutex to prevent multiple threads from entering the status set function.
	HANDLE			AvailQueueMutex;			// Mutex to prevent muiltiple access to the available queue
	HANDLE			BufferQueueMutex;			// Mutex around the get and set for the buffer queue
	HANDLE			BufferStatusMutex;			// Mutex to prevent muiltiple access to buffer status 
	HANDLE			ResetAcqMutex;				// Mutex to provide sycronization between commands and resetting acquistion on errors.
	PBFU32			HoldQueue;					// A queue of the buffers being held
	BFU32			HoldQStoreIndex;			// Index to store hold buffers
	BFU32			HoldQGetIndex;				// Index to retrieve hold buffers
	PBFU32			AvailableQueue;				// The queue of available buffers
	BFU32			AvailSIndex;				// Index to store available buffers
	BFU32			AvailRIndex;				// Index to retrieve available buffers
	BFU32			OverwriteFlag;				// Flag to indicate that buffers were overwritten in CirErIgnore mode.
	 
	// Used by Sequence and Circular 
	BFU32			FramesMissed;				// The number of frames missed during acquisition 
	BFU32			FramesCaptured;				// The number of frames acquired during acquisition 
	BFU32			AqSetupOptions;				// (BiAqEngJ,BiAqEngK),(CAM_CAD6),(IgnoreOverflows,AbortOnError,DisableAqErrorSig)
	BFU32			FrameCount;					// Counts frames including frames not completed because of overflow or HW ex.
	BFU32			NumLinesAcquired;			// The number of lines that werer acquired. Most times the ysize except for start/stop.
	BFU32			BufferIndex;				// The buffer currently being acquired into
	BFBOOL			IsResetting;				// TRUE <=> Resetting acquisition

	// Used by Sequence
	PBiSeqInfo		pSeqInfoMem;				// Pointer to the start of the block of memory used for buffer info.
	PBiSeqInfo*		SeqInfoArray;				// Pointer to the sequence buffer info array;

	// Info for worker threads 
	Bd				hBoard;						// Board handle 
	RQTabHeadPtr	QtabArray;					// The array of QTABs 
	RQTabHeadPtrPtr	QtabPtrArray;
	CiSIGNAL		Signal, StartStopSignal;	// Signals for end of quad 
	CiSIGNAL		ExceptionSignal;			// Signals hardware exceptions 
	CiSIGNAL		OverflowSignal;				// Signals FIFO Overflow 
	BFU32			PrevIntCount;				// Holds the previous interrupt count used in calculating missed frames in cicular mode.

	// Semaphore handles 
	HANDLE			NotifyAqStart;				// Semaphore to tell that Aq. has been started 

	// These handles are used to communicate with BiSeqWaitDone 
	HANDLE			BuffersFull;				// Semaphore to tell us when the seq. capture is complete 
	HANDLE			NotifyWaitDoneStop;			// Semaphore to tell that Aq. has been stopped 
	HANDLE			NotifyWaitDoneAbort;		// Semaphore to tell that Aq. has been aborted 
	HANDLE			WaitDoneArray[4];			// Waits for Abort, Stop, or Aq. complete in BiSeqWaitDone 
	HANDLE			ThreadError;				// Semaphore to tell when an error from any of the worker theads have occured 
	HANDLE			ErrorWaitArray[4];			// Waits for a thread error, overflow or HW exception in InternalErrorWaitThread 

	
	// These handle are used to communicate with BiSeqControl and BiCirControl 
	HANDLE			NotifyControlStop;			// Tells Bi*Control that acquisition has stopped 
	HANDLE			NotifyControlAbort;			// Tells Bi*Control that acquisition has aborted 
	HANDLE			NotifyControlResume;		// Tells Bi*Control that acquisition has resumed 
	HANDLE			NotifyControlPause;			// Tells Bi*Control that acquisition has paused 

	HANDLE			ErrorNotify;				// Notifies BiSeqErrorWait that an error has occured 
	HANDLE  		WorkerThreadHandle;			// Handle to the worker thread. 
	HANDLE			ErrorThreadHandle;			// Handle to the internal error thread.
	HANDLE			FrameDone;					// Semaphore to tell when a frame has been acquired 
	
	// Flags 
	BFBOOL			AqPause;					// Sequence Acquisition will pause when TRUE. 
	BFBOOL			AqStop;						// Flag to know that the acquisition was stopped 
	BFBOOL			AqAbort;					// Flag to know that the acquisition was aborted 
	BFBOOL			AqStart;					// Flag to know that the acquisition was started 
	BFU32			IsSeqBufStat;				// Flag to know when calling BiSeqBufferStatus if valid.
	BFBOOL			Cleanedup;					// Flag for SeqWaitError to exit function 
	BFBOOL			HaveSignal;					// Tells whether we created the signal 
	BFBOOL			HaveStartStopSignal;		// Tells whether were using start/stop or not 
	BFBOOL			HaveExceptionSignal;		// Tells whether we created the exception signal 
	BFBOOL			HaveOverflowSignal;			// Tells whether we created the overflow signal 
	BFBOOL			CirBuffers;					// True if using circular buffers 
	BFU32			MemoryAllocStatus;			// Status of buffer memory:
												//	BufferAlloc			<=> BiBufferAllocCam/BiBufferAlloc
												//	BufferAllocAligned	<=> BiBufferAllocAlignedCam
												//	BufferAssign		<=> BiBufferAssign

	// Error stack info 
	PBFU32			ErrorStack;					// Pointer to the current entry in the stack 
	PBFU32			StackTop;					// Top of the error stack 
	PBFU32			StackBot;					// Bottom of the error stack 

	// Handles to communicate with BiSeqWaitDoneFrame 
	HANDLE			FrameDoneArray[4];			// Waits for Abort, Stop, or Aq. complete in BiSeqWaitDoneFrame 
	HANDLE			FrameDoneStop;				// Let BiSeqWaitDoneFrame know that Aq. has been stopped 
	HANDLE			FrameDoneAbort;				// Let BiSeqWaitDoneFrame know that Aq. has been aborted 

	// For time stamping
	BFTime			InitTime;					// Initilized time for high res time stamp.
	BFBOOL			UsingHiResTimer;			// TRUE <=> Use high resolution timer


}BIBA, *PBIBA;


typedef struct _BiErrors
{
	int		ErrorCode;
	char	FuncName[128];
	char	FailureDescript[256];

}BiErrors;

#endif // __BIDEF__ 
