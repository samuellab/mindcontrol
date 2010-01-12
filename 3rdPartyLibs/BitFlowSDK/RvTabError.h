//
// Creation:    RvTabError.h
// Created:     March 25, 1996
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights ReseRVed.
//
// Raven Error Handler Definitions
//
// History:
//
// 03/25/96     rbs     Created file.
//

#if !defined(__RVTABERROR__)
#define __RVTABERROR__

#include "RvType.h"
#include "BFTabError.h"
#include "BFTabConfig.h"

//
// Raven Error Return Codes
//

#define RV_ERROR_ZERO (FF_RAVEN << BF_ERROR_FAMILY_SHIFT)

typedef enum _RVRC_Enum
{
    RV_OK = 0,					    // Operation succeeded.
	RV_ERROR_START = RV_ERROR_ZERO,
    RV_BAD_NEWS,					// Operation failed.
    RV_BAD_BASE,				    // Bad base address.
    RV_BAD_TABLES,				    // BitField and Object tables unchecked (board not open).
    RV_BAD_BIT_ID,                  // BitField Id out of range. 
    RV_BAD_POKE,                    // Illegal poke request (like poking to a large object). 
    RV_BAD_PEEK,                    // Illegal peek request (like peeking at a large object).
    RV_BAD_MODE,                    // Illegal LUT mode.
    RV_BAD_BANK,                    // Illegal LUT bank.
    RV_BAD_LANE,                    // Illegal LUT lane.
    RV_BAD_LUT_ADDR,                // Illegal LUT address. 
    RV_TOO_MANY_LANES,              // Too many lanes for requested operation. 
	RV_NO_DRIVER,				    // Driver not connected.
	RV_THREAD_FAIL_OLD,			    // Failed to create interrupt signalling thread.
	RV_BAD_EVENT_OLD,			    // Error associated with an operating system event.
	RV_BAD_IOCTL,				    // Unsuccessfull status returned from driver function.
	RV_BAD_DATA_SIZE,			    // Size of data returned from driver is incorrect.
	RV_BAD_DEVICE,				    // No device in this slot/bus.
	RV_BAD_SEMAPHORE_OLD,		    // Error creating or using semaphore.
	RV_BAD_SIGNAL_OLD,			    // Interrupt signal unkown.
	RV_WAIT_FAILED_OLD,			    // Wait for object failed.
	RV_BAD_CNF_PTR,				    // Invalid configuration pointer.
	RV_BAD_CNF_PARAM,			    // Bad parameter to structure function.
	RV_BAD_CNF_SIZE,			    // Structure not big enough to accomadate operation.
	RV_BAD_HEADER,				    // Binary configuration header is incorrect
	RV_BAD_SIG,					    // Bad binary configuration signature
	RV_BAD_ENDIAN,				    // Unknown endian model
	RV_BAD_FORMREV,				    // Incorrect binary configuration format revision
	RV_BAD_BINSIZE,				    // Size of binary configuration is incorrect
	RV_BAD_CRC,					    // CRC of binary data is incorrect
	RV_BAD_BINR,				    // Error extracting item from binary data
	RV_BAD_BINW,				    // Error inserting item into binary data
	RV_BAD_CNFA,				    // Error adding item to configuration structure
	RV_BAD_CNFG,				    // Error getting item from configuration structure
	RV_ITEM_TYPE,				    // Unknown configuration structure type
	RV_ITEM_SIZE,				    // Out of buffer space reading/writing configuration item
	RV_BAD_TXTW,				    // Error writing text version of configuration data
	RV_BAD_TXTR,				    // Error reading text version of configuration data
	RV_BAD_KEY,					    // Unkown or unexpected key while parsing text configuration
	RV_BAD_FIELDS,				    // Number of fields on line is incorrect.
	RV_UNEXPECTED_OEF,			    // Reached end of buffer before correct data was extracted.
	RV_LINE_LENGTH,				    // Text line too long.
	RV_BAD_CHAR,				    // Input buffer contains invalid characters
	RV_BAD_LINE,				    // Text line is incorrect.
	RV_BAD_CNF_FILE,			    // Error reading configuration file.
	RV_REG_ERROR,				    // Error communicating with registry.
	RV_BAD_STOP,				    // Error stopping DMA and/or acquistion.
	RV_BAD_IRP_STOP,			    // Error canceling interrupt signalling IRPs.
	RV_INCOMP,					    // This configuration file is incompatible with this board.
    RV_BAD_STRUCT,				    // Error in size of camera strucuture.
    RV_NO_CNFDIR_REG_KEY,           // Cnf Dir path key missing.
	RV_BAD_PATH,				    // Error building file path.
	RV_BAD_CNF,					    // Error extracting information from camera configuration.
	RV_BAD_MODEL,				    // Error building QTAB from model parameters.
	RV_BAD_CON_PARAM,			    // Bad parameter to control functions.
	RV_BAD_DMA_SETUP,			    // Board has not been setup for this DMA command.
	RV_TIMEOUT,					    // Timeout wait for command.
    RV_QTAB_PEEK_BAD,               // QTabPeek error.
    RV_QTAB_POKE_BAD,               // QTabPoke error.
    RV_QTAB_READ_BAD,               // QTabRead error.
    RV_QTAB_WRITE_BAD,              // QTabWrite error.
    RV_QTAB_FILL_BAD,               // QTabFill error.
    RV_QTAB_RAMP_BAD,               // QTabFill error.
    RV_CON_QTAB_BANK_BAD,           // ConQTabBank error.
    RV_CHAN_MUX_BAD,                // ConChanMux error.
    RV_TAP_MIRROR_BAD,              // ConTapMirror error.
    RV_NO_BIG_LUTS,                 // 16-bit LUT unavailable.
    RV_BAD_QTAB_BANK,               // Illegal QTab bank.
    RV_BAD_FREQ,                    // Illegal clock frequency.
    RV_BAD_GPOUT,                   // Illegal GPOut value.
    RV_BAD_TRIGAQ,                  // Illegal TrigAq setting. 
	RV_AQSETUP_FAIL,			    // RVAqSetup failed.
	RV_AQ_NOT_SETUP,			    // Board not setup for acquistion.
	RV_BAD_AQ_CMD,				    // Board not ready for Aq command issued.
	RV_AQEND_TIMEOUT,			    // Timeout waiting for acquisition to end.
	RV_BAD_WAIT,				    // Cannot wait for acquire to end when board is in this state.
    RV_BAD_TRIG_SEL,                // Illegal trigger selection.
    RV_BAD_VSTOP,                   // Illegal VMode selection. 
    RV_BAD_HSTOP,                   // Illegal HMode selection. 
    RV_BAD_CHANNEL,                 // Illegal channel selection. 
    RV_BAD_TAP_PACK,                // Illegal tap packing mode. 
    RV_BAD_MIRROR,                  // Illegal tap mirror mode. 
	RV_ALLOCATE_MDL,			    // Error allocating MDL for host buffer.
	RV_BAD_LOCK,				    // Error locking memory pages.
	RV_BAD_PQTAB_BUILD,			    // Error building phys QTab.
    RV_LUT_PEEK_BAD,                // LutPeek error.
    RV_LUT_POKE_BAD,                // LutPoke error.
    RV_LUT_READ_BAD,                // LutRead error.
    RV_LUT_WRITE_BAD,               // LutWrite error.
    RV_LUT_FILL_BAD,                // LutFill error.
    RV_LUT_RAMP_BAD,                // LutRamp error.
    RV_REG_PEEK_BAD,                // RegPeek error.
    RV_REG_POKE_BAD,                // RegPoke error.
	RV_AQSTRT_TIMEOUT,			    // Timeout waiting for acquisition to start.
    RV_BAD_HCTAB_ADDR,              // RVHCTab address error.
    RV_BAD_VCTAB_ADDR,              // RVVCTab address error.
    RV_BAD_QTAB_ADDR,               // QTab address error.
	RV_BAD_INQ_PARAM,			    // Bad parameter to inquire function.
	RV_UNKOWN_MODEL,				// Board model unkown.
	RV_UNKOWN_REV,					// Board/camera revision unkown
	RV_BRD_NOT_COMP,				// Camera file not compatible with this model board.
	RV_UNKOWN_COMP,					// Camera file compatibility is unkown.
	RV_BAD_DMA0_STOP,				// Timeout waiting for DMA channel 0 to stop.
	RV_BAD_DMA1_STOP,				// Timeout waiting for DMA channel 1 to stop.
	RV_BAD_AQ_STOP,					// Timeout waiting for acquisition to stop.
	RV_BAD_FIFO_RESET,				// Could not reset FIFO overflow.
	RV_BAD_CNF_SET,					// Error in StructItemSet.
	RV_BAD_INDEX,					// Bad index parameter.
	RV_BAD_TYPE,					// Configuration entry map contains unkown type.
	RV_BAD_CNF_ADD,					// Error in StructItemAdd.
	RV_BAD_CNF_ADDBL,				// Error in StructItemAddBlank.
	RV_BAD_CNF_GET,					// Error in StructItemGet.
	RV_BAD_ID_EMPTY,				// This configuration slot is empty.
	RV_BAD_ITEM_ID,					// ID of Item is not in configuration structure.
	RV_BAD_ITEM_INDEX,				// Index exceeds maximum allocate for list type configuration item.
	RV_DEST_TO_SMALL,				// Destination is to small to accept data.
	RV_ID_INUSE,					// This configuration ID is already in use.
    RV_BAD_SW_TRIG,                 // Illegal trigger selection.
	RV_BAD_CMD_LATCH,				// Command to board did not latch.
	RV_BAD_ROI,						// Error calculating QTAB for ROI.
	RV_CAM_BAD_CAM_TYPE,			// Current camera is not a line scan camera
	RV_CAM_NO_CONTROL,				// Camera control not supported for current camera
	RV_CAM_BAD_HWIN,				// The horizontal active window for the current camera does not make sense
	RV_CAM_BAD_FREQ,				// The pixel clock frequency is invalid
	RV_CAM_BAD_EXP,					// The desired exposure is not possible
	RV_CAM_BAD_RATE,				// The desired line rate is not possible
	RV_CAM_BAD_PRIORITY,			// the priority parameter is not valid
	RV_CAM_NOT_EXACT,				// Both the exact rate and exposure cannot be acheived
	RV_CAM_BAD_RESET,				// the CTAB's horizontal reset does not make sense
	RV_CAM_BAD_EXPSR,		        // the exposure period cannot be calculated
	RV_BROKEN_FLUSH,				// Flush quad spans page boundary.
    RV_THREAD_GOING,                // The interrupt notification thread is already running.
    RV_THREAD_NOT_GOING,            // The interrupt notification thread is not running.
    RV_THREAD_NOT_DYING,            // The interrupt notification thread is not dying.
	RV_CON_ENG_BAD,					// Unkown acquisition engine
	RV_CON_DMA_CHAN_BAD,			// Unkown DMA channel 
	RV_CON_QTAB_MODE_BAD,			// Unkown QTAB mode
	RV_LUT_READ_ERR,				// RvLutRead Error
	RV_LUT_WRITE_ERR,				// RvLutWrite Error
	RV_QTAB_READ_ERR,				// RvQTabRead Error
	RV_QTAB_WRITE_ERR,				// RvQTabWrite Error
	RV_LUT_PEEK_ERR,				// RvLutPeek Error
	RV_LUT_POKE_ERR,				// RvLutPoke Error
	RV_LUT_FILL_ERR,				// RvLutFill Error
	RV_LUT_RAMP_ERR,				// RvLutRamp Error
	RV_QTAB_PEEK_ERR,				// RvQTabPeek Error
	RV_QTAB_POKE_ERR,				// RvQTabPoke Error
	RV_QTAB_FILL_ERR,				// RvQTabFill Error
	RV_QTAB_RAMP_ERR,				// RvQTabRamp Error
	RV_BAD_FRM_SIZE,				// Invalid frame size, too big or small
	RV_CAM_SUPPORT,					// Cam file is not supported for changing of the frame size
	RV_CON_GPOUT_BAD,				// ConGPOut error.
    RV_ERROR_END

} RVRC_Enum;

// Message truncation point:    _______12345678901234567890123456______________________________          

#define RV_ERROR_ENTRIES	(RV_ERROR_END - RV_ERROR_START) 

#endif

