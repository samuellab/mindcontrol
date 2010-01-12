//
// Creation:    BFTabError.h
// Created:     March 15, 1996
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// BitFlow Error Definitions
//
// History:
//
// 03/15/96     rbs     Created file.
//

#if !defined(__BFTABERROR__)
#define __BFTABERROR__

#include "BFTabConfig.h"

#define BF_ERROR_FAMILY_SHIFT	10	// Family flag shift count for board specific errors tables.

//
// Driver Error Return Codes
//

#define BF_ERROR_ZERO (FF_BITFLOW << BF_ERROR_FAMILY_SHIFT)

typedef enum _BFRC_Enum
{
    BF_OK = 0,							// Operation succeeded.
	BF_ERROR_START = BF_ERROR_ZERO,
    BF_WHERE_AM_I,						// Set by WhereAmI to force a file & line message.
    BF_SHOW_ME_DEC,						// Display a message and decimal value.
    BF_SHOW_ME_HEX,						// Display a message and hex value.
	BF_SHOW_ME_TEXT_INFO,				// Display a blue dot informational message. 
	BF_SHOW_ME_TEXT_WARN,				// Display a yellow dot warning message. 
	BF_SHOW_ME_TEXT_ERROR,				// Display a red dot error message. 
	BF_SHOW_ME_TEXT_MSGS,				// Display a message and show an msgs.mc error in the event viewer. 
    BF_RESERVED0,						// 
    BF_RESERVED1,						// 
    BF_RESERVED2,						// 
    BF_RESERVED3,						// 
    BF_RESERVED4,						// 
    BF_SPECIAL_PURPOSE,					// End of special purpose (non-error) error codes.
    BF_FAIL_OPEN,						// Unable to open driver.
    BF_CLOSED,							// Request failed because driver is closed.
    BF_FAIL_MAP,						// Unable to map memory object.
    BF_NOT_MAPPED,						// Request failed because ObjectId not mapped. 
    BF_TABLE_FULL,						// Unable to add memory object because table is full.
    BF_ID_OUT_OF_BOUNDS,				// Object Id is < 0 or >= MAX_MEM_OBJECTS. 
    BF_ID_TAKEN,						// Map request failed because ObjectId already taken. 
    BF_NT_DISPATCH,						// Error dispatching a command to the NT driver.
    BF_MEM_OUT_OF_BOUNDS,				// Read/Write memory block out of bounds. 
    BF_NO_CAN_PACK,						// Unable to pack small blocks into big blocks. 
    BF_NO_CAN_UNPACK,					// Unable to unpack big blocks into small blocks. 
    BF_NO_OBJ_MEM,						// Unable to allocate object table memory.
    BF_SET_REC,							// SetRec error while reconstructing PackIt arguments. 
    BF_BAD_ARGS,						// Illegal argument detected. 
    BF_LANE_PEEK_BAD,					// Lane peek error. 
    BF_NO_LANE_MEM,						// Couldn't allocate a lane record.
    BF_BAD_LANE_WIDTH,					// Unequal lane widths in a multi-lane write.
    BF_BAD_MASK,						// Multi-lane mask badly formed.
    BF_NULL_TABLE,						// Error table contains a BFNULL entry.
    BF_DUP_RECORD,						// Error table contains a duplicate entry.
    BF_ERR_INIT,						// Error initializing error tables. 
    BF_BAD_ERROR_COUNT,					// Error table record count and RC count disagree.
    BF_BAD_PACK_ARGS,					// Illegal pack argument.
    BF_NO_TRACK_MEM,					// Unable to allocate argument packer tracking memory. 
    BF_EMPTY_PACK_TRACK,				// PackIt tracking list is empty.
    BF_NOT_PACKED,						// PackIt record not packed. 
    BF_PACK_INDEX_BAD,					// PackIt record index out of range.
    BF_PACK_SIZE_MISMATCH,				// GetRec record size mismatch.
    BF_NULL_POINTER,					// BFNULL pointer detected.
    BF_CRC_DISABLED,					// CRC checking disabled. 
    BF_BAD_TIME,						// Bad time for CRC check.
    BF_BAD_CRC,							// CRC check failed.
    BF_BAD_MAGIC,						// Bad magic number detected.
    BF_BAD_PACK_COUNT,					// PackIt count mismatch.
    BF_BAD_PACK_SIZE,					// PackIt size mismatch.
    BF_ALREADY_COMPRESSED,				// PackIt already compressed.
    BF_ALREADY_DECOMPRESSED,			// PackIt already decompressed.
    BF_ENCODE_BAD,						// PackIt compression failed.
    BF_DECODE_BAD,						// PackIt decompression failed.
    BF_NO_PACK_MEM,						// Unable to allocate PackIt memory.
    BF_LANE_POKE_BAD,					// Lane poke error.
    BF_NO_SUCH_ERR,						// No such error code.
    BF_NO_MEM,							// Out of memory.
    BF_ALLOCATE_MDL,					// MDL allocation error.
	BF_BAD_LOCK,						// MDL page lock error.
    BF_NULL_OBJ_TABLE,					// Unable to allocate memory object table. 
    BF_BAD_OBJ_TABLE,					// BFNULL record detected in BitField or Object table.
    BF_DUP_OBJ_RECORD,					// Duplicate record detected in BitField table. 
    BF_BAD_OBJ_SIZE,					// BitField table entry with improper size specification.
    BF_BAD_OBJ_ORDER,					// BitField table entry out of Wide-Large-Narrow sequence. 
    BF_OBJ_TAB_BAD,						// Object or BitField table is bad.
    BF_MAP_FAILED,						// BF_Map error.
    BF_BAD_TABLES,						// BitField and Object tables unchecked (board not open).
    BF_BAD_BIT_ID,						// BitField Id out of range. 
    BF_BAD_POKE,						// Illegal poke request (like poking to a large object). 
    BF_BAD_PEEK,						// Illegal peek request (like peeking at a large object).
    BF_REG_PEEK_BAD,					// RegPeek error.
    BF_REG_POKE_BAD,					// RegPoke error.
    BF_MAP_GAP,							// Unmapped object in memory object table.
    BF_REG_BAD_BOARD,					// BFRegistry bad Board Id.
    BF_DSP_NULL_TABLE,					// Dispatch table contains a BFNULL entry.
    BF_DSP_DUP_RECORD,					// Dispatch table contains a duplicate entry.
    BF_DSP_INIT,						// Error initializing dispatch tables. 
    BF_DSP_TABLE_SIZE,					// Dispatch table size doesn't match dispatch table entry count.
    BF_NULL_GET_INFO_INFO,				// BFNULL BF_GetInfo Info pointer.
    BF_GET_INFO_BOARD,					// BFGetInfo bad Board Id.
    BF_GET_INFO_TYPE,					// BFGetInfo bad Type Id.
    BF_SET_INFO_BOARD,					// BFSetInfo bad Board Id.
    BF_SET_INFO_TYPE,					// BFSetInfo bad Type Id.
    BF_SET_INFO_MEM,					// BFSetInfo out of memory.
    BF_BAD_NEWS,						// Operation failed.
    BF_BAD_DEVICE_INFO,					// Unitialized kernel device info record.
    BF_BAD_BOARD_ID,					// Unitialized board Id.
    BF_BAD_ERROR_HANDLER,				// Undefined error handler type.
    BF_ERR_ENABLE_EVENT_BAD,			// BFErrorEnableEvent failed.
    BF_ERR_DISABLE_EVENT_BAD,			// BFErrorDisableEvent failed.
    BF_ERR_ENABLE_DEBUGGER_BAD,			// BFErrorEnableDebugger failed.
    BF_ERR_DISABLE_DEBUGGER_BAD,		// BFErrorDisableDebugger failed.
    BF_ERR_ENABLE_DIALOG_BAD,			// BFErrorEnableDialog failed.
    BF_ERR_DISABLE_DIALOG_BAD,			// BFErrorDisableDialog failed.
    BF_ERR_ENABLE_FILE_BAD,				// BFErrorEnableFile failed.
    BF_ERR_DISABLE_FILE_BAD,			// BFErrorDisableFile failed.
    BF_ERR_ENABLE_MONITOR_BAD,			// BFErrorEnableMonitor failed.
    BF_ERR_DISABLE_MONITOR_BAD,			// BFErrorDisableMonitor failed.
    BF_ERR_ENABLE_BREAK_USER_BAD,		// BFErrorEnableBreakUser failed.
    BF_ERR_DISABLE_BREAK_USER_BAD,		// BFErrorDisableBreakUser failed.
    BF_ERR_ENABLE_BREAK_KERNEL_BAD,		// BFErrorEnableBreakKernel failed.
    BF_ERR_DISABLE_BREAK_KERNEL_BAD,	// BFErrorDisableBreakKernel failed.
    BF_ERR_ENABLE_ALL_BAD,				// BFErrorEnableAll failed.
    BF_ERR_DISABLE_ALL_BAD,				// BFErrorDisableAll failed.
	BF_BAD_CNF_PTR,						// Invalid configuration pointer.
	BF_BAD_CNF_PARAM,					// Bad parameter to structure function.
	BF_BAD_CNF_SIZE,					// Structure not big enough to accomadate operation.
	BF_BAD_HEADER,						// Binary configuration header is incorrect
	BF_BAD_SIG,							// Bad binary configuration signature
	BF_BAD_ENDIAN,						// Unknown endian model
	BF_BAD_FORMREV,						// Incorrect binary configuration format revision
	BF_BAD_BINSIZE,						// Size of binary configuration is incorrect
	BF_BAD_CNF_CRC,						// CRC of binary data is incorrect
	BF_BAD_BINR,						// Error extracting item from binary data
	BF_BAD_BINW,						// Error inserting item into binary data
	BF_BAD_CNFA,						// Error adding item to configuration structure
	BF_BAD_CNFG,						// Error getting item from configuration structure
	BF_ITEM_TYPE,						// Unknown configuration structure type
	BF_ITEM_SIZE,						// Out of buffer space reading/writing configuration item
	BF_BAD_TXTW,						// Error writing text version of configuration data
	BF_BAD_TXTR,						// Error reading text version of configuration data
	BF_BAD_KEY,							// Unkown or unexpected key while parsing text configuration
	BF_BAD_FIELDS,						// Number of fields on line is incorrect.
	BF_UNEXPECTED_OEF,					// Reached end of buffer before correct data was extracted.
	BF_LINE_LENGTH,						// Text line too long.
	BF_BAD_CHAR,						// Input buffer contains invalid characters
	BF_BAD_LINE,						// Text line is incorrect.
	BF_BAD_CNF_FILE,					// Error reading configuration file.
	BF_BAD_CNF_SET,						// Error in StructItemSet.
	BF_BAD_INDEX,						// Bad index parameter.
	BF_BAD_TYPE,						// Configuration entry map contains unkown type.
	BF_BAD_CNF_ADD,						// Error in StructItemAdd.
	BF_BAD_CNF_ADDBL,					// Error in StructItemAddBlank.
	BF_BAD_CNF_GET,						// Error in StructItemGet.
	BF_BAD_ID_EMPTY,					// This configuration slot is empty.
	BF_BAD_ITEM_ID,						// ID of Item is not in configuration structure.
	BF_BAD_ITEM_INDEX,					// Index exceeds maximum allocate for list type configuration item.
	BF_DEST_TO_SMALL,					// Destination is to small to accept data.
	BF_ID_INUSE,						// This configuration ID is already in use.
	BF_BAD_ALLOC,						// Cannot allocate memory for structure.
	BF_BAD_SEMAPHORE,					// Error creating or using semaphore.
	BF_BAD_SIGNAL,						// Interrupt signal unkown.
	BF_WAIT_FAILED,						// Wait for object failed.
    BF_THREAD_GOING,					// The interrupt notification thread is already running.
    BF_THREAD_NOT_GOING,				// The interrupt notification thread is not running.
    BF_THREAD_NOT_DYING,				// The interrupt notification thread is not dying.
	BF_BAD_EVENT,						// Error associated with an operating system event.
	BF_THREAD_FAIL,						// Failed to create interrupt signalling thread.
	BF_NO_DEVICE,						// No device at given PCI address
    BF_NO_FPG_LIST_RAW_MEM,				// Flash file list allocation error.
    BF_FPG_LIST_FILE_READ,				// Flash file list (BitFlow.txt) read error.
    BF_NO_FLASH_RAW_MEM,				// Flash allocation error.
    BF_NO_FLASH_REG_KEY,				// Flash path key missing.
    BF_FPG_OPEN,						// Flash file open error. 
    BF_FPG_FILE_READ,					// Flash file read error.
    BF_FPG_SIZE_WRONG,					// Flash file size error.
    BF_FPG_CREATE,						// Flash file create error. 
    BF_FPG_FILE_WRITE,					// Flash file write error.
    BF_FPG_BAD_READ,					// Flash FSH file load error.
    BF_FPG_BAD_WRITE,					// Flash BitFlow.gat create error.
    BF_BAD_BIT_BUCKET,					// Flash download allocation error. 
    BF_GATE_RESET,						// Flash gate reset failed.
    BF_GATE_ENABLE,						// Flash download enable failed. 
    BF_BIT_WRITE_BAD,					// Flash bit write failed.
	BF_DWNLDR_WRITE_TIMEOUT,			// Timeout waiting for downloader to write block.
    BF_BAD_CONFIG,						// Flash configuration failed. 
	BF_DWNLDR_NOT_IDLE,					// Downloader not in idle state
    BF_BAD_CONFIG_PLL,					// PLL Flash configuration failed. 
    BF_BAD_CONFIG_MUX,					// MUX Flash configuration failed. 
    BF_BAD_CONFIG_CCU,					// CCU Flash configuration failed. 
    BF_BAD_CONFIG_LBC,					// LBC Flash configuration failed. 
    BF_BAD_GATE_READ,					// Flash read error.
    BF_BAD_DOWNLOAD,					// Flash download failed.
    BF_BAD_MOD_FAM,						// Unsupported Register.
    BF_NO_REG_ID_MEM,					// RegToId allocation error.
    BF_BAD_OBJ_MEM,						// Object table allocation error.
    BF_BAD_OBJ_ENTRY,					// Object record index error.
    BF_BAD_BFT_MEM,						// BitField table allocation error.
    BF_BAD_BFT_ENTRY,					// BitField record index error.
    BF_BAD_MATCH,						// BitField object match error.
    BF_BAD_R2_OPTION,					// Illegal RoadRunner Option.
    BF_BAD_R2_MODEL,					// Illegal RoadRunner Model.
    BF_BAD_RV_OPTION,					// Illegal Raven Option.
    BF_BAD_RV_MODEL,					// Illegal Raven Model.
    BF_BAD_BF_FAMILY,					// Illegal BitFlow Family.
    BF_BAD_MAP_INIT,					// Board Map initialization error.
    BF_BAD_FLASH_CUSTOM,				// Illegal Custom Flash Name.
	BF_BAD_PQTAB_BUILD,					// Could not build physical QTab.
	BF_BAD_PTAB,						// Physical QTAB number is bad.
	BF_BAD_ERROR_INIT,					// Error table initialization error. 
	BF_BAD_REGISTER,					// Unsupported register.
    BF_BAD_DISPATCH_COUNT,				// Dispatch table record count and entry count disagree.
	BF_BAD_DISPATCH_INIT,				// Dispatch table initialization error. 
    BF_NO_FLASH_CUSTOM,					// Custom flash file missing.
	BF_GET_COUNTERS,					// BFInterruptGetCounters bad Board Id.
    BF_NO_FLASH_STANDARD,				// Standard flash file missing.
	BF_ALREADY_OPEN_PROC,				// Board already opened in this process.
	BF_ALREADY_OPEN_SYS,				// Board already open by another process.
	BF_ALREADY_OPEN_INIT,				// Board is already opened and will not be initialized.
	BF_ALREADY_OPEN_EXEC_ME,			// Board is already opened and cannot be opened in exclusive mode.
	BF_ALREADY_OPEN_EXEC_YOU,			// Board is already opened in exclusive mode and will not be opened.
	BF_BAD_MUTEX,						// Bad Interrupt Signal Mutex.
	BF_BAD_CAM,							// Can't initialize for camera.
	BF_BAD_INIT,						// Couldn't initiaze board.
	BF_BAD_CAM_INDEX,					// Bad camera index.
	BF_PQTAB_MISMATCH,					// Relative QTAB points outside of destination buffer.
	BF_PQTAB_TO_SMALL,					// Not enough phys QTAB entries allocated.
	BF_NOT_YET,							// Feature not implemented.
	BF_BOARD_CLOSED,					// Board closed.
	BF_BAD_FIT,							// Physical QTAB bigger than board's QTAB bank(s).
    BF_BAD_DISPATCH_RANGE,				// Dispatch table overlap error.
	BF_BAD_CAM_LIST,					// No camera list.
	BF_QUAD_NOT_WRITTEN,				// Quad not written.
	BF_BAD_CHAIN,						// QTab not in QTab chain.
	BF_BAD_FRAME,						// Frame not in QTab chain.
	BF_BAD_QTWRITE,						// Can't write chained quad.
	BF_NOT_CHAIN,						// Chain size must be > 0.
	BF_QUAD_GOING,						// DMA active during engage.
	BF_QUAD_OVERWRITTEN,				// Quad overwritten.
	BF_LOST_QUADS,						// Lost PhysQTabs released.
	BF_BAD_BIG,							// Bad BigLock Id.
	BF_BIG_RANGE,						// Address out of big range.
	BF_BAD_UNLOCK_ALL,					// BigUnlockAll failed.
	BF_BAD_UNLOCK_MINE,					// BigUnlockMine failed.
	BF_LOST_LOCKS,						// Lost memory locks unlocked.
	BF_GET_STAMPS,						// BFInterruptGetStamps bad Board Id.
	BF_STAMPS_OFF,						// Time stamping is disabled.
	BF_PHYS_QTAB_ENGAGE_ERR,			// BFPhysQTabEngage Error
	BF_GET_REG_TO_ID_ERR,				// BFGetRegToId Error
	BF_DO_NOTHING_ERR,					// BFDoNothing Error
	BF_GET_INFO_ERR,					// BFGetInfo Error
	BF_SET_INFO_ERR,					// BFSetInfo Error
	BF_SET_UART_MUTEX_ERR,				// BFSetUARTMutex Error
	BF_RESET_UART_MUTEX_ERR,			// BFResetUARTMutex Error
	BF_DRIVER_VERSION_ERR,				// BFDriverVersion Error
	BF_PARSE_CFG_OPS_ERR,				// BFParseCfgOps Error
	BF_WRITE_CFG_BUS_ERR,				// BFWriteCfgBus Error
	BF_READ_CFG_BUS_ERR,				// BFReadCfgBus Error
	BF_GET_CFG_BUS_VENDOR_ERR,			// BFGetCfgBusVendor Error
	BF_GET_CFG_BUS_DEVICE_ERR,			// BFGetCfgBusDevice Error
	BF_GET_CFG_BUS_SUBVENDOR_ERR,		// BFGetCfgBusSubVendor Error
	BF_GET_CFG_BUS_SUBSYSTEM_ERR,		// BFGetCfgBusSubSystem Error
	BF_GET_CFG_BUS_VFO_ERR,				// BFGetCfgBusVFO Error
	BF_READ_CFG_BOARD_ERR,				// BFReadCfgBoard Error
	BF_READ_CFG_ALL_ERR,				// Failure saving one board's Config space
	BF_WRITE_CFG_BOARD_ERR,				// BFWriteCfgBoard Error
	BF_WRITE_CFG_ALL_ERR,				// Failure restoring one board's Config space
	BF_GET_CFG_BOARD_VENDOR_ERR,		// BFGetCfgBoardVendor Error
	BF_GET_CFG_BOARD_DEVICE_ERR,		// BFGetCfgBoardDevice Error
	BF_GET_CFG_BOARD_SUBVENDOR_ERR,		// BFGetCfgBoardSubVendor Error
	BF_GET_CFG_BOARD_SUBSYSTEM_ERR,		// BFGetCfgBoardSubSystem Error
	BF_GET_CFG_BOARD_VFO_ERR,			// BFGetCfgBoardVFO Error
	BF_GET_CFG_DEVICES_ERR,				// BFGetCfgDevices Error
	BF_GET_FAMILY_DEVICES_ERR,			// BFGetFamilyDevices Error
	BF_PCI_CFG_SAVE_ERR,				// BFPCICfgSave Error,
	BF_PCI_CFG_SAVE_ERR_ALL,			// BFPCICfgSaveAll Error,
	BF_PCI_CFG_RESTORE_ERR,				// BFPCICfgRestore Error,
	BF_PCI_CFG_RESTORE_ERR_ALL,			// BFPCICfgRestoreAll Error,
	BF_REG_TRACE_ERR,					// BFRegTrace Error
	BF_TIME_TRACE_ERR,					// BFTimeTrace Error
	BF_TIME_DUMP_ERR,					// BFTimeDump Error
	BF_CALL_TRACE_ERR,					// BFCallTrace Error
	BF_ERROR_SUBMIT_ERR,				// BF_ErrorSubmit Error
	BF_ERROR_CHECK_ERR,					// BFErrorCheck Error
	BF_ERROR_FETCH_ERR,					// BF_ErrorFetch Error
	BF_ERROR_CLEAR_ERR,					// BF_ErrorClear Error
	BF_ERROR_DEPTH_ERR,					// BF_ErrorDepth Error
	BF_ERROR_GET_MES_ERR,				// BF_ErrorGetMes Error
	BF_ERROR_GET_LAST_ERR,				// BFErrorGetLast Error
	BF_ERROR_CLEAR_LAST_ERR,			// BFErrorClearLast Error
	BF_ERROR_SET_ALL_ERR,				// BFErrorSetAll Error
	BF_ERROR_FILE_ALL_ERR,				// BFErrorFileAll Error
	BF_ERROR_MONITOR_CONNECT_ERR,		// BFErrorMonitorConnect Error
	BF_ERROR_MONITOR_WAIT_ERR,			// BFErrorMonitorWait Error
	BF_ERROR_MONITOR_DISCONNECT_ERR,	// BFErrorMonitorDisconnect Error
	BF_ERROR_ENABLE_ALL_ERR,			// BFErrorEnableAll Error
	BF_ERROR_DISABLE_ALL_ERR,			// BFErrorDisableAll Error
	BF_ERROR_ENABLE_EVENT_ERR,			// BFErrorEnableEvent Error
	BF_ERROR_DISABLE_EVENT_ERR,			// BFErrorDisableEvent Error
	BF_ERROR_ENABLE_DEBUGGER_ERR,		// BFErrorEnableDebugger Error
	BF_ERROR_DISABLE_DEBUGGER_ERR,		// BFErrorDisableDebugger Error
	BF_ERROR_ENABLE_DIALOG_ERR,			// BFErrorEnableDialog Error
	BF_ERROR_DISABLE_DIALOG_ERR,		// BFErrorDisableDialog Error
	BF_ERROR_ENABLE_FILE_ERR,			// BFErrorEnableFile Error
	BF_ERROR_DISABLE_FILE_ERR,			// BFErrorDisableFile Error
	BF_ERROR_ENABLE_MONITOR_ERR,		// BFErrorEnableMonitor Error
	BF_ERROR_DISABLE_MONITOR_ERR,		// BFErrorDisableMonitor Error
	BF_ERROR_ENABLE_BREAK_USER_ERR,		// BFErrorEnableBreakUser Error
	BF_ERROR_DISABLE_BREAK_USER_ERR,	// BFErrorDisableBreakUser Error
	BF_ERROR_ENABLE_BREAK_KERNEL_ERR,	// BFErrorEnableBreakKernel Error
	BF_ERROR_DISABLE_BREAK_KERNEL_ERR,	// BFErrorDisableBreakKernel Error
	BF_FLASH_CREATE_SET_ERR,			// BFFlashCreateSet Error
	BF_FLASH_VALIDATE_ERR,				// BFFlashValidate Error
	BF_FLASH_DOWNLOAD_ERR,				// BFFlashDownload Error
	BF_FLASH_DOWN_TEST_ERR,				// BFFlashDownTest Error
	BF_FLASH_DELAYED_FLASH_ERR,			// BFFlashDelayedFlash Error
	BF_FLASH_GET_SET_ERR,				// BFFlashGetSet Error
	BF_FLASH_SET_SET_ERR,				// BFFlashSetSet Error
	BF_INTERRUPT_GET_COUNTERS_ERR,		// BFInterruptGetCounters Error
	BF_INTERRUPT_GET_STAMPS_ERR,		// BFInterruptGetStamps Error
	BF_INTERRUPT_ENABLE_STAMPS_ERR,		// BFInterruptEnableStamps Error
	BF_INTERRUPT_DISABLE_STAMPS_ERR,	// BFInterruptDisableStamps Error
	BF_INTERRUPT_SIMULATE_ERR,			// BFInterruptSimulate Error
	BF_SER_INT_ENABLE_ERR,				// BFSerIntHandlerEnable Error
	BF_SER_INT_DISABLE_ERR,				// BFSerIntHandlerDisable Error
	BF_SER_INT_GET_IN_BUF_ERR,			// BFSerIntGetInBuf Error
	BF_BIG_LOCK_ERR,					// BFBigLock Error
	BF_BIG_UNLOCK_ERR,					// BFBigUnlock Error
	BF_BIG_UNLOCK_ALL_ERR,				// BFBigUnlockAll Error
	BF_BIG_UNLOCK_MINE_ERR,				// BFBigUnlockMine Error
	BF_BIG_FLUSH_ERR,					// BFBigFlush Error
	BF_BIG_PHYS_SEG_ERR,				// BFBigPhysSeg Error
	BF_PEEK_ERR,						// BF_Peek Error
	BF_POKE_ERR,						// BF_Poke Error
	BF_RMW_ERR,							// BF_RMW Error
	BF_READ_ERR,						// BF_Read Error
	BF_WRITE_ERR,						// BF_Write Error
	BF_MASK_FILL_ERR,					// BF_MaskFill Error
	BF_MASK_READ_ERR,					// BF_MaskRead Error
	BF_MASK_WRITE_ERR,					// BF_MaskWrite Error
	BF_LANE_READ_ERR,					// BFLaneRead Error
	BF_LANE_WRITE_ERR,					// BFLaneWrite Error
	BF_LANE_PEEK_ERR,					// BFLanePeek Error
	BF_LANE_POKE_ERR,					// BFLanePoke Error
	BF_PHYS_QTAB_WRITE_PART_ERR,		// BFPhysQTabWritePart Error
	BF_PHYS_QTAB_CHAIN_BREAK_ERR,		// BFPhysQTabChainBreak Error
	BF_PHYS_QTAB_GET_ABS_QUAD_ERR,		// BFPhysQTabGetAbsQuad Error
	BF_PHYS_QTAB_GET_REL_QUAD_ERR,		// BFPhysQTabGetRelQuad Error
	BF_PHYS_QTAB_FREE_ALL_ERR,			// BFPhysQTabFreeAll Error
	BF_QTAB_PROGRESS_ERR,				// BFQTabProgress Error
	BF_QTAB_MODE_REQUEST_ERR,			// BFQTabModeRequest Error
	BF_REG_SUPPORTED_ERR,				// BFRegSupported Error
	BF_REG_FLAGS_ERR,					// BFRegFlags Error
	BF_REG_SHIFT_ERR,					// BFRegShift Error
	BF_REG_MASK_ERR,					// BFRegMask Error
	BF_REG_OBJECT_ID_ERR,				// BFRegObjectId Error
	BF_REG_PEEK_ERR,					// BFRegPeek Error
	BF_REG_POKE_ERR,					// BFRegPoke Error
	BF_REG_RMW_ERR,						// BFRegRMW Error
	BF_SIGNALLING_CLEAR_ERR,			// BFSignallingClear Error
	BF_SPEEDS_ERR,						// BFSpeeds Error
	BF_FINE_ERR,						// BFFine Error
	BF_FINE_RATE_ERR,					// BFFineRate Error
	BF_PHYS_QTAB_CREATE_ERR,			// BFPhysQTabCreate Error
	BF_PHYS_QTAB_CHAIN_LINK_ERR,		// BFPhysQTabChainLink Error
	BF_PHYS_QTAB_FREE_ERR,				// BFPhysQTabFree Error
	BF_DISP_QTAB_CREATE_ERR,			// BFPhysQTabCreate Error
	BF_REG_NAME_ERR,					// BFRegName Error
	BF_SIGNAL_ANY_INT_ERR,				// BF_SignalAnyInt Error
	BF_GET_CFG_BUS_CONFIG_ERR,			// BFGetCfgBusConfig Error
	BF_GET_CFG_BOARD_CONFIG_ERR,		// BFGetCfgBoardConfig Error
	BF_SPEED_LIMIT,						// Error speed limit exceeded.
	BF_UPDATE_BOARD_VFO_ERR,			// BFUpdateBoardVFO Error
	BF_ERR_MON_FULL,					// Error monitor full.
	BF_BAD_FILTER,						// Register filter not set.
	BF_CHAIN_SIP_ENABLE_ERR,			// BFChainSIPEnable Error
	BF_CHAIN_SIP_DISABLE_ERR,			// BFChainSIPDisable Error
	BF_CHANGE_FACE_ERR,					// BFChangeFace Error
	BF_VID_NUKED,						// Vendor Id Nuked
	BF_WRONG_CAM,						// Wrong camera configuration file type.
	BF_DISABLED,						// Board disabled.
	BF_BAD_REG,							// Board register test error.
	BF_PHYS_QTAB_CHAIN_ENABLE_ERR,		// BFPhysQTabChainEnable Error
	BF_PHYS_QTAB_CHAIN_DISABLE_ERR,		// BFPhysQTabChainDisable Error
	BF_HAVE_HASH,						// Hash already allocated.
	BF_CANT_HASH,						// Can't allocate hash.
	BF_HASH_STUFFED,					// Hash table full.
	BF_NOT_IN_HASH,						// Not in hash table.
	BF_BAD_HASH_ADDR,					// Bad physical quad number.
	BF_GATE_STATUS,						// Flash status error.
	BF_GATE_DONE,						// Flash done error.
	BF_BAD_MODEL,						// Error building QTAB from model parameters
	BF_BAD_ROI,							// Error calculating QTAB for ROI
	BF_BAD_CON_PARAM,					// Bad parameter to control functions
	BF_BAD_CNF,							// Error extracting information from camera configuration
	BF_PQTAB_CREATE_ERR,				// BFPQTabCreate Error
	BF_BAD_FLASH_RQST,					// The requested flash does not exist.
	BF_BAD_FLASH_INFO,					// Error geting flash information.
	BF_BAD_FLASH_GET,					// Reguested flash is not available or not compatible with this board.
	BF_BAD_FLASH_DNLD,					// Error downloading new flash.
	BF_BAD_FLASH_TAG,					// Flash tag mismatch.
	BF_FREE_ERR,						// Error freeing memory.
	BF_HIGH_RES_TIMER_ERR,				// Error with high resolution timer. May not be supported on this computer.		
	BF_NOT_SUPPORTED,					// Feature not supported.
	BF_INQ_UNKNOWN_VAL,					// Board returning value that is not understood
	BF_REGISTRY_READ_ERROR,				// Error reading value from registry
	BF_AFE_TIMEOUT,						// Timeout accessing AFE
	BF_REGISTRY_ERROR,					// Error parsing registry entries
	BF_CFG_SPACE_TIMEOUT,				// Time out waiting to read/write PCI configure space
	BF_FLASH_MEM_TIMEOUT,				// Time out waiting for flash memory operation to complete
	BF_ERROR_END
} BFRC_Enum;

// Message truncation point:        _______12345678901234567890123456______________________________          

#define BF_ERROR_ENTRIES	(BF_ERROR_END - BF_ERROR_START) 

//
// Error Types
//

typedef enum _ErrorType
{
    ErrorNone       = 0x00000000,               // No error messages.
    ErrorAll        = 0x7fff0000,               // All error messages.
    ErrorBug        = 0x00010000,               // Outright bug in the code that must be fixed.
    ErrorStop       = 0x00020000,               // Deep trouble, process cannot continue.
    ErrorWarn       = 0x00040000,               // Something is wrong but recovery is possible.
    ErrorInfo       = 0x00080000,               // Informational messages.
	ErrorPlace		= 0x00100000,				// BFErrorWhereAmI file and line number message.
	ErrorValue		= 0x00200000,				// BFErrorShowMe decimal or hex value message.
	ErrorText		= 0x00400000,				// BFErrorMessage text output.
	ErrorDrv		= 0x00800000				// Error returned after driver call.
} ErrorType;

typedef enum _ErrorMessageColor
{
    ErrorBlue,									// Blue dot informational error message.
	ErrorYellow,								// Yellow dot warning error message.
	ErrorRed									// Red dot error message.
} ErrorMessageColor;

typedef BFCHAR ErrorMesBuf[256], *ErrorMesPtr;	// Error message buffer.
typedef BFCHAR ErrorFileBuf[256], *ErrorFilePtr;// File name buffer.

#endif


