/***************************************************************************
*
* BiError.h
*
* BufIn API
* 
* Types and defines for error processing
*
* Copyright (C) 1999 by BitFlow, Inc.  All Rights Reserved.
*
* 07/29/99	sms		created
*
***************************************************************************/



typedef enum _BIRC_Enum
{
	BI_OK = 0,						// Everything is good 

	// BiBrdOpen 
	BI_ERROR_BOARD_NOT_FOUND,		// Boards are in the host, but not the number that was specified 
	BI_ERROR_UNKNOWN_TYPE,			// Board UNKNOWN, not a RoadRunner or Raven 
	BI_ERROR_SYSTEM,				// Error talking to registry 
	BI_ERROR_OPENING,				// Could not open board 

	// BiBrdInquire() 
	BI_ERROR_BAD_BOARDPTR_INQ,		// Not passing a RoadRunner or Raven to function 
	BI_ERROR_UNKNOWN_PARAMETER,		// Parameter being passed is unknown 

	// BiBrdClose() 
	BI_ERROR_NOCLOSE,				// Could not close board 

	// BiBufferAllocCam() & AlignedCam() 
	BI_ERROR_CAM_NO_MEM_AVAIL,		// Lack of memory for allocation 
	BI_ERROR_CAM_FRAMESIZE,			// Inquire of frame size failed. 
	BI_ERROR_CAM_STACK_MEM,			// Not enough memory for error stack 
	BI_ERROR_CAM_BUFFERS_NUM,		// There must be at least two buffers to allocate 
	BI_ERROR_CAM_PIXDEPTH,			// Pixel depth not supported 
	BI_ERROR_CAM_UNKNOWN,			// Undefined error 

	// BiBufferAlloc() & Aligned()
	BI_ERROR_NO_MEM_AVAIL,			// Lack of memory for allocation 
	BI_ERROR_FRAMESIZE,				// Inquire of frame size failed. 
	BI_ERROR_STACK_MEM,				// Not enough memory for error stack 
	BI_ERROR_BUFFERS_NUM,			// There must be at least two buffers to allocate 
	BI_ERROR_PIXDEPTH,				// Pixel depth not supported 

	// BiBufferAssign() 
	BI_ERROR_MEM_SIZE,				// There is not enough memory allocated for current frame size 
	BI_ERROR_ASSIGN_PIXDEPTH,		// Pixel depth not supported 
	BI_ERROR_NO_MEM_POINT,			// Memory could not be allocated for BufIn's array of pointers 

	// BiBufferFree()
	BI_ERROR_MEM_UNASSIGN,			// Please use BiBufferUnassign to free memory.
	BI_ERROR_MEM_ALLOC_TYPE,		// Unable to determine how buffers were allocated. Buffers still allocated.

	// BiBufferUnassign()
	BI_ERROR_MEM_FREE,				// Please use BiBufferFree to free memory.

	// BiSeqAqSetup( ) 
	BI_ERROR_LUT_MASK,				// Error in masking LUT 
	BI_ERROR_QTABARRAY_MEM,			// Not enough memory for QtabArray 
	BI_ERROR_REL_QTAB,				// Couldn't create all relative QTABs 
	BI_ERROR_PHYS_QTAB,				// Couldn't create all physical QTABs 
	BI_ERROR_CREATE_CTAB_SIG,		// Couldn't create CTAB signal 
	BI_ERROR_CREATE_THREAD,			// Couldn't create worker thread 
	BI_ERROR_SIGCREATE_EX,			// Couldn't create exception signal 
	BI_ERROR_SIGCREATE_OVF,			// Couldn't create overflow signal 
	BI_ERROR_SIGCREATE_QUAD,		// Couldn't create Quad Done signal 
	BI_ERROR_SIGCREATE_STARTSTOP,	// Couldn't create start stop signal 
	BI_ERROR_CREATE_ERRORTHREAD,	// Couldn't create error thread 
	BI_ERROR_ENGINEK,				// DMA engine K is currently not supported 
	BI_ERROR_P_QTABARRAY_MEM,		// Couldn't allocated memory for array of pointers to  qtabs 
	BI_ERROR_CHAIN_LINK,			// Failure linking physical qtabs together 
	BI_ERROR_QTABHOST_SKIPFRAME,	// Skip frames is currently not supported for host qtabs 
	BI_ERROR_HOST_MODE,				// Board is currently setup for qtabs on the board 
	BI_ERROR_SEQINFO_MEM,			// Not enough memory for sequence info	
	BI_ERROR_SEQARRAY_MEM,			// Not enough memory for sequence buffer info array

	// BiSeqCleanUp( ) 
	BI_ERROR_SIGCANCEL_QUAD,		// Problem cancelling quad done signal 
	BI_ERROR_SIGFREE_QUAD,			// Problem freeing Quad done signal 
	BI_ERROR_SIGCANCEL_STARTSTOP,	// Problem cancelling start/stop signal 
	BI_ERROR_SIGFREE_STARTSTOP,		// Problem freeing start/stop signal 
	BI_ERROR_SIGCANCEL_EX,			// Problem cancelling exception signal 
	BI_ERROR_SIGFREE_EX,			// Problem freeing exception signal 
	BI_ERROR_SIGCANCEL_OVF,			// Problem cancelling overflow signal 
	BI_ERROR_SIGFREE_OVF,			// Problem freeing overflow siganl 
	BI_ERROR_PHYSQTAB_FREE,			// Problem freeing qhysical qtabs 
	BI_ERROR_RELQTAB_FREE,			// Problem freeing relative qtabs 
	BI_ERROR_AQ_CLEANUP,			// CiAqCleanUp returned a failure 

	// BiCircCleanUp( ) 
	BI_ERROR_CIR_SIGCANCEL_QUAD,		// Problem cancelling quad done signal 
	BI_ERROR_CIR_SIGFREE_QUAD,			// Problem freeing Quad done signal 
	BI_ERROR_CIR_SIGCANCEL_STARTSTOP,	// Problem cancelling start/stop signal 
	BI_ERROR_CIR_SIGFREE_STARTSTOP,		// Problem freeing start/stop signal 
	BI_ERROR_CIR_SIGCANCEL_EX,			// Problem cancelling exception signal 
	BI_ERROR_CIR_SIGFREE_EX,			// Problem freeing exception signal 
	BI_ERROR_CIR_SIGCANCEL_OVF,			// Problem cancelling overflow signal 
	BI_ERROR_CIR_SIGFREE_OVF,			// Problem freeing overflow siganl 
	BI_ERROR_CIR_PHYSQTAB_FREE,			// Problem freeing qhysical qtabs 
	BI_ERROR_CIR_RELQTAB_FREE,			// Problem freeing relative qtabs 
	BI_ERROR_CIR_AQ_CLEANUP,			// CiAqCleanUp returned a failure 

	// Qtab Host Worker Thread 
	BI_ERROR_HOST_CHAIN_ENGAGE,		// Failure engaging the chain of qtabs 
	BI_ERROR_HOST_GRAB_CMD,			// Error with the grab command 
	BI_ERROR_HOST_CLR_SIGQ,			// Couldn't clear signal queue 
	BI_ERROR_HOST_SIGNAL_TIMEOUT,	// Worker thread has timed out 
	BI_ERROR_HOST_SIGNAL_BAD,		// Bad signal or wait failed 
	BI_ERROR_HOST_MISSED_FRAMES,	// Missed to many frames 
	BI_ERROR_HOST_SHUTDOWN,			// CiShutdown failed 
	BI_ERROR_SEQ_SIP_ENABLE,		// Error enabling start/stop interrupt processing 
	BI_ERROR_SEQ_SIP_DISABLE,		// Error Disabling start/stop interrupt processing 
	BI_ERROR_HOST_AQ_FREEZE,		// Timed out waiting for acquisition to freeze. 
	BI_ERROR_HOST_TRIGSTAT,			// Timed out waiting for trigger to go low, in order to resume from a pause 
	BI_ERROR_HOST_AQ_GRAB,			// Timed out waiting for acquisition to start. 
	BI_ERROR_HOST_DMA_START,		// Error starting the DMA engine 
	BI_ERROR_ACTIVE_TIMEOUT,		// Timed out waiting for the active region of the image.
	BI_ERROR_BUFFER_INDEX,			// The buffer index was incremented beyond the buffer range.

	// BiTrigModeGet( ) 
	BI_ERROR_BOARDPTR_TRIG_GET,		// Bad board pointer 

	// BiTrigModeSet( ) 
	BI_ERROR_UNKNOWN_TRIG_SET,		// Unknown parameter 
	BI_ERROR_BOARDPTR_TRIG_SET,		// Bad board pointer 
	BI_ERROR_BAD_BOARD_PARA,		// Bad parameter for this specific board 

	// BiTrigForce( ) 
	BI_ERROR_UNKNOWN_MODE,			// Unknown Trig mode 
	BI_ERROR_BRD_TRIG_FORCE,		// Bad board pointer 

	// BiSeqWaitDone() 
	BI_ERROR_WAIT_TIMEOUT,			// Timed out while waiting for sequence acquistion 
	BI_ERROR_WAIT_FAILED,			// WaitForSingleObject failed 

	// BiSeqWaitFrameDone 
	BI_ERROR_FRAME_TIMEOUT,			// Timed out while waiting for a frame 
	BI_ERROR_FRAME_FAILED,			// Function failed 

	// BiSeqParameters() 
	BI_ERROR_START_INVALID,			// Start frame is greater than number of buffers allocated 
	BI_ERROR_TOMANY_FRAMES,			// Number of frames to collect is greater then buffers allocated 
	BI_ERROR_START_COMBO,			// Start frame + number of frames is greater than buffers allocated 
	BI_ERROR_NUM_FRAMES,			// Number of frames must be at least 2 

	// BiSeqControl() 
	BI_ERROR_CNTL_UNKNOWN,			// Unknown parameter being passed to function 
	BI_ERROR_START_TIMEOUT,			// Timed out waiting for the start command 
	BI_ERROR_STOP_TIMEOUT,			// Timed out waiting for the stop command 
	BI_ERROR_PAUSE_TIMEOUT,			// Timed out waiting for the pause command 
	BI_ERROR_RESUME_TIMEOUT,		// Timed out waiting for the resume command 
	BI_ERROR_ABORT_TIMEOUT,			// Timed out waiting for the abort command 
	BI_ERROR_CICONAQCMD_FREEZE,		// Error issuing an acquistion freeze with the CiConAqCommand function.
	BI_ERROR_CICONAQSTATUS,			// Error retrieving acquistion status with the CiConAqStatus function.
	BI_ERROR_INVALIDAQSTATUS,		// The acquistion status was invalid.
	BI_ERROR_INVALID_CMD_SEQ,		// An invalid sequence of commands to control acquisition was used.
	BI_ERROR_CICONAQCMD_ABORT,		// Error issuing an acquistion abort with the CiConAqCommand function.

	// BiSeqBufferStatus
	BI_ERROR_BUF_STAT,				// must call BiSeqAqSetup before BiSeqBufferStatus.

	// Internal Errors  
	BI_ERROR_STACK_FULL,			// Error Stack full 
	BI_ERROR_OVERFLOW,				// FIFO overflow occured 
	BI_ERROR_HWEXCEPTION,			// Hardware exeption occured 
	BI_ERROR_MUL_OBJ_WAIT,			// WaitMultipleObjects function failed 
	BI_ERROR_INTERNAL_ERROR,		// Error occured in the thread 
	BI_ERROR_RESETAQ,				// The Reset Acquisition function failed to reset 

	
	// BiSeqErrorWait() 
	BI_ERROR_ACQUISITION,			// An acquisition error has happened 
	
	// BiCirErrorWait() 
	BI_ERROR_CIR_ACQUISITION,		// An circular acquisition error has happened 

	// BiDiskBufWrite() 
	BI_ERROR_UNKNOWN_FILETYPE,		// The file type to save as is unknown 
	BI_ERROR_FIRSTBUF_INVALID,		// The first buffer is larger that the number of buffers. 
	BI_ERROR_NUMBUFS_ZERO,			// The number of buffers must be at least 1. 
	BI_ERROR_TOO_MANY_BUFFERS,		// Asking for more buffer to save then allocated. 
	BI_ERROR_OPEN_BMP_FILE,			// File for BMP could not be created 
	BI_ERROR_BITMAP_HEADER,			// Error writing BMP header to file 
	BI_ERROR_BMP_DATA_WRITE,		// Error writing BMP data to file 
	BI_ERROR_OPEN_AVI_FILE,			// Error opening AVI File 
	BI_ERROR_CREATE_STREAM,			// Error creating stream 
	BI_ERROR_SAVE_OPTIONS,			// Error with dialog box save options 
	BI_ERROR_COMPRESS_STREAM,		// Error with compressing the stream 
	BI_ERROR_AVI_HEADER,			// Error putting AVI header in the stream 
	BI_ERROR_WRITING_AVI_DATA,		// Error writing the AVI stream 
	BI_ERROR_OPEN_RAW_FILE,			// Error opening the RAW file 
	BI_ERROR_RAW_DATA_WRITE,		// Error writing RAW data to file 
	BI_ERROR_OPEN_TIFF_FILE,		// Error opening TIFF file 
	BI_ERROR_WRITING_TIFF_HEADER,	// Error writing TIFF header 
	BI_ERROR_WRITING_TIFF_DATA,		// Error writing TIFF data 
	BI_ERROR_SWAPRGB,				// The SwapRGB option can only be used with color data 
	BI_ERROR_PACK24BIT,				// Image data must be 32 bit in order to pack it into 24 bit 
	BI_ERROR_BUF_POINTER,			// Invalid buffer pointer.
	BI_ERROR_FILE_XSIZE,			// Invalid XSize. The XSize must be greater than zero.
	BI_ERROR_FILE_YSIZE,			// Inavlid YSize. The YSize must be greater than zero.	
	BI_ERROR_WRITE_BITDEPTH,		// Unknown bit depth. The bit depth must be 8, 10, 12, 14, 16, 24 or 32.
	BI_ERROR_WRITE_BMP_BITDEPTH,	// Invalid bit depth for bmp. BMP supports 8, 24 and 32 bit pixel depths.
	BI_ERROR_WRITE_TIF_BITDEPTH,	// Invalid tif bit depth. The bit depth must be 8, 10, 12, 14, 16, 24 or 32.
	BI_ERROR_WRITE_AVI_BITDEPTH,	// Invalid bit depth for avi. AVI supports 8, 24 and 32 bit pixel depths.
	BI_ERROR_FILE_CAD6_OPTION,		// The CAD6 option must be used with no other options.
	BI_ERROR_WRITE_LOW_MEM,			// Failed allocating memory. Free resources and try again.
	BI_ERROR_OPEN_TEXTFILE,			// Failed opening text file to write raw image info. 
	BI_ERROR_RAW_TEXT_WRITE,		// Failed writing raw image info to text file. 
	BI_ERROR_UNKNOWN_WRITE,			// Unknown error returned from BiDiskBufWrite. 
	BI_ERROR_FILE_EXISTS,			// Saving a file that already exists without the overwrite option.

	// BiDiskBufRead() 
	BI_ERROR_NUMBUFS,				// Bad value of NumBufs, must be greater than zero 
	BI_ERROR_BUFFER_SIZE_SMALL,		// Image size is larger that the buffer size being copied to 
	BI_ERROR_FILE_OPEN_READ,		// Error opening file for reading 
	BI_ERROR_FILE_READ,				// Error reading file 
	BI_ERROR_FILETYPE_READ_IO,		// Unknown File type. File type must be raw,bmp,tif, or avi 
	BI_ERROR_MEM_TEMP_BUF_READ_IO,	// Error allocating memory for temporary BMP buffer 
	BI_ERROR_INVALID_NAME,			// The file name given is invalid, to few characters 
	BI_ERROR_PIXDEPTH_READ,			// Pixel depth not supported 
	BI_ERROR_DISK_PARAM_READ,		// Error returned by BiDiskParamRead function 
	BI_ERROR_NUMBER_OF_FRAMES,		// Number of frames in AVI file exceeds number of buffer asked for 
	BI_ERROR_NO_DECOMPRESS,			// Decompressing image to dimensions outside of maximum limit 
	BI_ERROR_READ_BUF_POINTER,		// Invalid buffer pointer.
	BI_ERROR_READ_XSIZE,			// Invalid XSize. The XSize must be greater than zero.
	BI_ERROR_READ_YSIZE,			// Inavlid YSize. The YSize must be greater than zero. 
	BI_ERROR_RAW_READ,				// Reading a raw image file is not supported.
	BI_ERROR_UNKNOWN_READ,			// Unknown error returned from BiDiskBufRead. 

	// BiDiskParamRead() 
	BI_ERROR_FILETYPE_PARAM,		// Unknown file type. File type must be raw,bmp,tif, or avi 
	BI_ERROR_MEM_TEMP_BUF_PARAM,	// Error creating temporary buffer 
	BI_ERROR_FILE_OPEN_PARAM,		// Error opening file 
	BI_ERROR_READFILE_PARAM,		// Error reading in file data 	
	BI_ERROR_RAW_READ_PARAMS,		// Reading raw file parameters is not possible.
	BI_ERROR_UNKNOWN_PARAM,			// Unknown error returned from BiDiskParamRead. 

	// BiCircAqSetup() 
	BI_ERROR_CIR_ENGINEK,			// DMA engine K is currently not supported 
	BI_ERROR_CIR_FIRMWARE,			// Please download host qtab firmware to use circular buffers 
	BI_ERROR_CIR_LUT_MASK,			// Error in masking LUT 
	BI_ERROR_CIR_QTABARRAY_MEM,		// Lack of Memory for Qtab Array Allocation 
	BI_ERROR_CIR_P_QTABARRAY_MEM,	// Lack of Memory for array of host qtab pointers allocation 
	BI_ERROR_CIR_REL_QTAB,			// Error Creating any/all Relative QTABs. 
	BI_ERROR_CIR_PHYS_QTAB,			// Error Creating any/all Physical QTABs. 
	BI_ERROR_CIR_CHAIN_LINK,		// Failure linking physical qtabs together 
	BI_ERROR_CIR_CREATE_THREAD,		// Unable to create circular buffer worker thread 
	BI_ERROR_CIR_SIG_OVF,			// Unable to create signal for overflow 
	BI_ERROR_CIR_SIG_EX,			// Unable to create signal for exceptions 
	BI_ERROR_CIR_SIG_QUAD,			// Unable to create signal for Quad done 
	BI_ERROR_CIR_SIG_STARTSTOP,		// Unable to create signal for start/stop 
	BI_ERROR_CIR_SIG_ERRORTHREAD,	// Unable to create internal error thread 
	BI_ERROR_CIR_BUF_STAT,			// Lack of memory to create buffer status array 
	BI_ERROR_CIR_BUF_QUEUE,			// Lack of memory to create circular buffer queue 
	BI_ERROR_CIR_ERROR_MODE,		// An invalid error mode was used.

	// Circular Worker Thread 
	BI_ERROR_CIR_SHUTDOWN,			// CiShutdown failed 
	BI_ERROR_CIR_CHAIN_ENGAGE,		// Failure engaging the chain of qtabs 
	BI_ERROR_CIR_GRAB_CMD,			// Error with the grab command 
	BI_ERROR_CIR_CLR_SIGQ,			// Couldn't clear signal queue 
	BI_ERROR_CIR_SIGNAL_TIMEOUT,	// Worker thread has timed out 
	BI_ERROR_CIR_SIGNAL_BAD,		// Bad signal or wait failed 
	BI_ERROR_CIR_MISSED_FRAMES,		// Missed to many frames 
	BI_ERROR_AVAL_BUFFER,			// There are no buffers available for data 
	BI_ERROR_STAT_CHECK,			// An error occured when checking buffer availability 
	BI_ERROR_CIR_SIP_ENABLE,		// Error enabling start/stop interrupt processing 
	BI_ERROR_CIR_SIP_DISABLE,		// Error Disabling start/stop interrupt processing 
	BI_ERROR_CIR_AQ_FREEZE,			// Timed out waiting for acquisition to freeze. 
	BI_ERROR_CIR_TRIGSTAT,			// Timed out waiting for trigger to go low, in order to resume from a pause 
	BI_ERROR_CIR_AQ_GRAB,			// Timed out waiting for acquisition to start. 
	BI_ERROR_CIR_DMA_START,			// Error starting the DMA engine 
	BI_ERROR_OVERWRITE,				// Buffers have been overwritten.
	BI_ERROR_THREAD_MUTEX_TIMEOUT,  // Timed out waiting for the buffer status mutex.
	BI_ERROR_THREAD_MUTEX_ABANDONED,// The buffer status mutex was not released properly.


	// BiCirControl() 
	BI_ERROR_CIR_CNTL_UNKNOWN,		// Unknown parameter being passed to function 
	BI_ERROR_CIR_RESUME_P,			// Can only resume after the acquisition has been running and paused 
	BI_ERROR_CIR_PAUSE,				// Issued a pause after a stop or abort command 
	BI_ERROR_CIR_RESUME,			// Issued a resume after a stop or abort command 
	BI_ERROR_CIR_PAUSE_START,		// Issued a start after a pause command 
	BI_ERROR_CIR_START_TIMEOUT,		// Timed out waiting for the start command 
	BI_ERROR_CIR_STOP_TIMEOUT,		// Timed out waiting for the stop command 
	BI_ERROR_CIR_PAUSE_TIMEOUT,		// Timed out waiting for the pause command 
	BI_ERROR_CIR_RESUME_TIMEOUT,	// Timed out waiting for the resume command 
	BI_ERROR_CIR_ABORT_TIMEOUT,		// Timed out waiting for the abort command 
	BI_ERROR_CIR_CICONAQCMD_FREEZE,	// Error issuing an acquistion freeze with the CiConAqCommand function.
	BI_ERROR_CIR_CICONAQSTATUS,		// Error retrieving acquistion status with the CiConAqStatus function.
	BI_ERROR_CIR_INVALIDAQSTATUS,	// The acquistion status was invalid.
	BI_ERROR_CIR_INVALID_CMD_SEQ,	// An invalid sequence of commands to control acquisition was used.
	BI_ERROR_CIR_CICONAQCMD_ABORT,	// Error issuing an acquistion abort with the CiConAqCommand function.
									

	// BiCirWaitDoneFrame() 
	BI_ERROR_CIR_WAIT_TIMEOUT,		// Timed out while waiting for sequence acquistion 
	BI_ERROR_CIR_WAIT_FAILED,		// WaitForSingleObject failed 
	BI_ERROR_QEMPTY,				// Nothing is in the circular buffer queue 
	BI_ERROR_FRAME_MUTEX_TIMEOUT,	// Timed out waiting for the buffer status mutex.
	BI_ERROR_FRAME_MUTEX_ABANDONED, // The buffer status mutex was not released properly.

	// BiCirStatusSet() 
	BI_ERROR_MARK_STAT,				// Tryed to change to a status other than AVAILABLE and HOLD 
	BI_ERROR_MARK_HOLD,				// Was unable to mark the buffer to hold.
	BI_ERROR_CHAIN_DISABLE,			// Driver error holding buffer.
	BI_ERROR_CHAIN_ENABLE,			// Driver error making buffer available.
	BI_ERROR_AVAIL_QUEUE_FULL,		// Available queue was full.
	BI_ERROR_ON_AVAIL_QUEUE,		// Unable to change buffer status, because the buffer is on the available queue.
	BI_ERROR_STATUS_STATE,			// Unknown status state
	BI_ERROR_BUFFER_RANGE,			// Could not adjust the buffer range. Too many buffers are being held.
	BI_ERROR_STATUS_MUTEX_TIMEOUT,	// Timed out waiting for the buffer status mutex.
	BI_ERROR_STATUS_MUTEX_ABANDONED,// The buffer status mutex was not released properly.
	BI_ERROR_RAVEN_HOLD,			// Holding buffers with the Raven is not supported.

	// BiCirBufferStatusSet()
	BI_ERROR_CIR_BAD_BUFFER_NUM,	// Invalid buffer number was passed into the function.

	// BiCirBufferStatusGet()
	BI_ERROR_CIR_BUFFER_NUM,		// Invalid buffer number was passed into the function.


	// BiErrorTextGet()
	BI_ERROR_BUFFER_TOO_SMALL,		// The buffer was not large enough to hold the error message.
	BI_ERROR_ERR_NOT_FOUND,			// Could not find error number.
	BI_ERROR_NULL_TEXT_PTR,			// Invalid pointer to text buffer.

	// BiErrorShow
	BI_ERROR_INVALID_ERR_NUM,		// Unknown error number. Could not find error message for the error number passed into function.

	// BiInternalTimeoutSet
	BI_ERROR_TIMEOUT_SET,			// An error occured trying to set the internal timeout.

	// Errors used by the sequence and circular classes
	BI_ERROR_SETUP_TWICE,			// Setup has been called twice without a call to cleanup.
	BI_ERROR_CALL_SETUP,			// Setup must be called before using this method
	BI_ERROR_ALREADY_SETUP,			// This method must be called before setup is called.

	// BiCamOpen
	BI_ERROR_CAM_OPEN,				// Error opening the specified camera file.

	// BiCamClose
	BI_ERROR_CAM_CLOSE,				// Error closing the specified camera file.

	// BiCamSel
	BI_ERROR_CAM_SEL,				// Error selecting camera file.

	// BiCamGetCur
	BI_ERROR_GET_CUR,				// Error returning the current camera file.

	// BiCamSetCur
	BI_ERROR_CAM_SET_CUR,			// Error setting current camera file.

	// BiCamGetFileName
	BI_ERROR_CAM_FILENAME,			// Error returning the camera file name.

	// Keep this as the last error
	BI_ERROR_END,
	

	// WARNINGS  
	BI_WARNINGS = 0x10000,			// BufIn warning will be returns above 0x10000 
	BI_AQ_ABORTED,					// BiSeqWaitDone returning acquisition was aborted 
	BI_AQ_STOPPED,					// BiSeqWaitDone returning acquisition was stopped 
	BI_CLEANUP,						// BiSeqWaitError return for clean up bumping semaphore 
	BI_CIR_STOPPED,					// BiCirWaitNext - Circular acquisition was stopped. 
	BI_CIR_ABORTED,					// BiCirWaitNext - Circular acquisition was aborted. 
	BI_CIR_CLEANUP,					// BiAqCleanUp killed BiCirWaitError function 
	BI_CANCEL_FRAME_DONE,			// BiSeqWaitFrameDone was bumped by BiAqCleanup  
	BI_FRAME_STOP,					// BiSeqWaitFrameDone was bumped by stop 
	BI_FRAME_ABORT,					// BiSeqWaitFrameDone was bumped by abort 
	BI_CANCEL_CIR_FRAME_DONE,		// BiCirWaitDoneFrame returned because cleanup was called.
	BI_WARNINGS_END,

}BIRC_Enum;

