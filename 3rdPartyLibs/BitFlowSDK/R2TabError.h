//
// Creation:    R2TabError.h
// Created:     March 25, 1996
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// RoadRunner Error Handler Definitions
//
// History:
//
// 03/25/96     rbs     Created file.
//

#if !defined(__R2TABERROR__)
#define __R2TABERROR__

#include "R2Type.h"
#include "BFTabError.h"
#include "BFTabConfig.h"

//
// RoadRunner Error Return Codes
//

#define R2_ERROR_ZERO (FF_ROADRUNNER << BF_ERROR_FAMILY_SHIFT)

typedef enum _R2RC_Enum
{
    R2_OK = 0,					    // Operation succeeded.
	R2_ERROR_START = R2_ERROR_ZERO,
    R2_BAD_NEWS,					// Operation failed.
    R2_BAD_BASE,				    // Bad base address.
    R2_BAD_TABLES,				    // BitField and Object tables unchecked (board not open).
    R2_BAD_BIT_ID,                  // BitField Id out of range. 
    R2_BAD_POKE,                    // Illegal poke request (like poking to a large object). 
    R2_BAD_PEEK,                    // Illegal peek request (like peeking at a large object).
    R2_BAD_MODE,                    // Illegal LUT mode.
    R2_BAD_BANK,                    // Illegal LUT bank.
    R2_BAD_LANE,                    // Illegal LUT lane.
    R2_BAD_LUT_ADDR,                // Illegal LUT address. 
    R2_TOO_MANY_LANES,              // Too many lanes for requested operation. 
	R2_NO_DRIVER,				    // Driver not connected.
	R2_THREAD_FAIL_OLD,			    // Failed to create interrupt signalling thread.
	R2_BAD_EVENT_OLD,			    // Error associated with an operating system event.
	R2_BAD_IOCTL,				    // Unsuccessfull status returned from driver function.
	R2_BAD_DATA_SIZE,			    // Size of data returned from driver is incorrect.
	R2_BAD_DEVICE,				    // No device in this slot/bus.
	R2_BAD_SEMAPHORE_OLD,		    // Error creating or using semaphore. (MOVED TO BF)
	R2_BAD_SIGNAL_OLD,				// Interrupt signal unkown. (MOVED TO BF)
	R2_WAIT_FAILED_OLD,			    // Wait for object failed.  (MOVED TO BF)
	R2_BAD_CNF_PTR,				    // Invalid configuration pointer.
	R2_BAD_CNF_PARAM,			    // Bad parameter to structure function.
	R2_BAD_CNF_SIZE,			    // Structure not big enough to accomadate operation.
	R2_BAD_HEADER,				    // Binary configuration header is incorrect
	R2_BAD_SIG,					    // Bad binary configuration signature
	R2_BAD_ENDIAN,				    // Unknown endian model
	R2_BAD_FORMREV,				    // Incorrect binary configuration format revision
	R2_BAD_BINSIZE,				    // Size of binary configuration is incorrect
	R2_BAD_CRC,					    // CRC of binary data is incorrect
	R2_BAD_BINR,				    // Error extracting item from binary data
	R2_BAD_BINW,				    // Error inserting item into binary data
	R2_BAD_CNFA,				    // Error adding item to configuration structure
	R2_BAD_CNFG,				    // Error getting item from configuration structure
	R2_ITEM_TYPE,				    // Unknown configuration structure type
	R2_ITEM_SIZE,				    // Out of buffer space reading/writing configuration item
	R2_BAD_TXTW,				    // Error writing text version of configuration data
	R2_BAD_TXTR,				    // Error reading text version of configuration data
	R2_BAD_KEY,					    // Unkown or unexpected key while parsing text configuration
	R2_BAD_FIELDS,				    // Number of fields on line is incorrect.
	R2_UNEXPECTED_OEF,			    // Reached end of buffer before correct data was extracted.
	R2_LINE_LENGTH,				    // Text line too long.
	R2_BAD_CHAR,				    // Input buffer contains invalid characters
	R2_BAD_LINE,				    // Text line is incorrect.
	R2_BAD_CNF_FILE,			    // Error reading configuration file.
	R2_REG_ERROR,				    // Error communicating with registry.
	R2_BAD_STOP,				    // Error stopping DMA and/or acquistion.
	R2_BAD_IRP_STOP,			    // Error canceling interrupt signalling IRPs.
	R2_INCOMP,					    // This configuration file is incompatible with this board.
    R2_BAD_STRUCT,				    // Error in size of camera strucuture.
    R2_NO_CNFDIR_REG_KEY,           // Cnf Dir path key missing.
	R2_BAD_PATH,				    // Error building file path.
	R2_BAD_CNF,					    // Error extracting information from camera configuration.
	R2_BAD_MODEL,				    // Error building QTAB from model parameters.
	R2_BAD_CON_PARAM,			    // Bad parameter to control functions.
	R2_BAD_DMA_SETUP,			    // Board has not been setup for this DMA command.
	R2_TIMEOUT,					    // Timeout wait for command.
    R2_CTAB_PEEK_BAD,               // CTabPeek error.
    R2_CTAB_POKE_BAD,               // CTabPoke error.
    R2_CTAB_READ_BAD,               // CTabRead error.
    R2_CTAB_WRITE_BAD,              // CTabWrite error.
    R2_CTAB_FILL_BAD,               // CTabFill error.
    R2_CTAB_RAMP_BAD,               // CTabRamp error.
    R2_QTAB_PEEK_BAD,               // QTabPeek error.
    R2_QTAB_POKE_BAD,               // QTabPoke error.
    R2_QTAB_READ_BAD,               // QTabRead error.
    R2_QTAB_WRITE_BAD,              // QTabWrite error.
    R2_QTAB_FILL_BAD,               // QTabFill error.
    R2_QTAB_RAMP_BAD,               // QTabFill error.
    R2_CON_QTAB_BANK_BAD,           // ConQTabBank error.
    R2_CON_FREQ_BAD,                // ConFreq error.
    R2_CON_GPOUT_BAD,               // ConGPOut error.
    R2_CON_SW_TRIG_BAD,             // ConSwTrig error.
    R2_CON_TRIG_AQ_BAD,             // ConTrigAq error.
    R2_CON_TRIG_SEL_BAD,            // ConTrigSel error.
    R2_CON_VMODE_BAD,               // ConVMode error.
    R2_CON_HMODE_BAD,               // ConHMode error.
    R2_CHAN_MUX_BAD,                // ConChanMux error.
    R2_TAP_MIRROR_BAD,              // ConTapMirror error.
    R2_NO_BIG_LUTS,                 // 16-bit LUT unavailable.
    R2_BAD_QTAB_BANK,               // Illegal QTab bank.
    R2_BAD_FREQ,                    // Illegal clock frequency.
    R2_BAD_GPOUT,                   // Illegal GPOut value.
    R2_BAD_TRIGAQ,                  // Illegal TrigAq setting. 
	R2_AQSETUP_FAIL,			    // R2AqSetup failed.
	R2_AQ_NOT_SETUP,			    // Board not setup for acquistion.
	R2_BAD_AQ_CMD,				    // Board not ready for Aq command issued.
	R2_AQEND_TIMEOUT,			    // Timeout waiting for acquisition to end.
	R2_BAD_WAIT,				    // Cannot wait for acquire to end when board is in this state.
    R2_BAD_TRIG_SEL,                // Illegal trigger selection.
    R2_BAD_VSTOP,                   // Illegal VMode selection. 
    R2_BAD_HSTOP,                   // Illegal HMode selection. 
    R2_BAD_CHANNEL,                 // Illegal channel selection. 
    R2_BAD_TAP_PACK,                // Illegal tap packing mode. 
    R2_BAD_MIRROR,                  // Illegal tap mirror mode. 
	R2_ALLOCATE_MDL,			    // Error allocating MDL for host buffer.
	R2_BAD_LOCK,				    // Error locking memory pages.
	R2_BAD_PQTAB_BUILD,			    // Error building phys QTab.
    R2_LUT_PEEK_BAD,                // LutPeek error.
    R2_LUT_POKE_BAD,                // LutPoke error.
    R2_LUT_READ_BAD,                // LutRead error.
    R2_LUT_WRITE_BAD,               // LutWrite error.
    R2_LUT_FILL_BAD,                // LutFill error.
    R2_LUT_RAMP_BAD,                // LutRamp error.
    R2_REG_PEEK_BAD,                // RegPeek error.
    R2_REG_POKE_BAD,                // RegPoke error.
	R2_AQSTRT_TIMEOUT,			    // Timeout waiting for acquisition to start.
    R2_BAD_HCTAB_ADDR,              // R2HCTab address error.
    R2_BAD_VCTAB_ADDR,              // R2VCTab address error.
    R2_BAD_QTAB_ADDR,               // QTab address error.
	R2_BAD_INQ_PARAM,			    // Bad parameter to inquire function.
	R2_UNKOWN_MODEL,				// Board model unkown.
	R2_UNKOWN_REV,					// Board/camera revision unkown
	R2_BRD_NOT_COMP,				// Camera file not compatible with this model board.
	R2_UNKOWN_COMP,					// Camera file compatibility is unkown.
	R2_BAD_DMA0_STOP,				// Timeout waiting for DMA channel 0 to stop.
	R2_BAD_DMA1_STOP,				// Timeout waiting for DMA channel 1 to stop.
	R2_BAD_AQ_STOP,					// Timeout waiting for acquisition to stop.
	R2_BAD_FIFO_RESET,				// Could not reset FIFO overflow.
	R2_BAD_FIFO_PGRM,				// Could not program FIFOs
	R2_BAD_CNF_SET,					// Error in StructItemSet.
	R2_BAD_INDEX,					// Bad index parameter.
	R2_BAD_TYPE,					// Configuration entry map contains unkown type.
	R2_BAD_CNF_ADD,					// Error in StructItemAdd.
	R2_BAD_CNF_ADDBL,				// Error in StructItemAddBlank.
	R2_BAD_CNF_GET,					// Error in StructItemGet.
	R2_BAD_ID_EMPTY,				// This configuration slot is empty.
	R2_BAD_ITEM_ID,					// ID of Item is not in configuration structure.
	R2_BAD_ITEM_INDEX,				// Index exceeds maximum allocate for list type configuration item.
	R2_DEST_TO_SMALL,				// Destination is to small to accept data.
	R2_ID_INUSE,					// This configuration ID is already in use.
    R2_BAD_SW_TRIG,                 // Illegal trigger selection.
	R2_BAD_CMD_LATCH,				// Command to board did not latch.
	R2_BAD_ROI,						// Error calculating QTAB for ROI.
	R2_CAM_BAD_CAM_TYPE,			// Current camera is not a line scan camera
	R2_CAM_NO_CONTROL,				// Camera control not supported for current camera
	R2_CAM_BAD_HWIN,				// The horizontal active window for the current camera does not make sense
	R2_CAM_BAD_FREQ,				// The pixel clock frequency is invalid
	R2_CAM_BAD_EXP,					// The desired exposure is not possible
	R2_CAM_BAD_RATE,				// The desired line rate is not possible
	R2_CAM_BAD_PRIORITY,			// the priority parameter is not valid
	R2_CAM_NOT_EXACT,				// Both the exact rate and exposure cannot be acheived
	R2_CAM_BAD_RESET,				// the CTAB's horizontal reset does not make sense
	R2_CAM_BAD_EXPSR,		        // the exposure period cannot be calculated
	R2_BROKEN_FLUSH,				// Flush quad spans page boundary.
    R2_THREAD_GOING,                // The interrupt notification thread is already running.
    R2_THREAD_NOT_GOING,            // The interrupt notification thread is not running.
    R2_THREAD_NOT_DYING,            // The interrupt notification thread is not dying.
	R2_CTAB_PEEK_ERR,				// R2CTabPeek Error
	R2_CTAB_READ_ERR,				// R2CTabRead Error
	R2_CTAB_WRITE_ERR,				// R2CTabWrite Error
	R2_LUT_READ_ERR,				// R2LutRead Error
	R2_LUT_WRITE_ERR,				// R2LutWrite Error
	R2_QTAB_READ_ERR,				// R2QTabRead Error
	R2_QTAB_WRITE_ERR,				// R2QTabWrite Error
	R2_CTAB_POKE_ERR,				// R2CTabPoke Error
	R2_CTAB_FILL_ERR,				// R2CTabFill Error
	R2_CTAB_RAMP_ERR,				// R2CTabRamp Error
	R2_CON_QTAB_BANK_ERR,			// R2ConQTabBank Error
	R2_CON_FREQ_ERR,				// R2ConFreq Error
	R2_CON_GPOUT_ERR,				// R2ConGPOut Error
	R2_CON_SW_TRIG_ERR,				// R2ConSwTrig Error
	R2_CON_TRIG_AQ_ERR,				// R2ConTrigAq Error
	R2_CON_TRIG_SEL_ERR,			// R2ConTrigSel Error
	R2_CON_VMODE_ERR,				// R2ConVMode Error
	R2_CON_HMODE_ERR,				// R2ConHMode Error
	R2_CON_CHAN_MUX_ERR,			// R2ConChanMux Error
	R2_CON_TAP_MIRROR_ERR,			// R2ConTapMirror Error
	R2_LUT_PEEK_ERR,				// R2LutPeek Error
	R2_LUT_POKE_ERR,				// R2LutPoke Error
	R2_LUT_FILL_ERR,				// R2LutFill Error
	R2_LUT_RAMP_ERR,				// R2LutRamp Error
	R2_LUT_MAX_ERR,					// R2LutMax Error
	R2_QTAB_PEEK_ERR,				// R2QTabPeek Error
	R2_QTAB_POKE_ERR,				// R2QTabPoke Error
	R2_QTAB_FILL_ERR,				// R2QTabFill Error
	R2_QTAB_RAMP_ERR,				// R2QTabRamp Error
	R2_BAD_FRM_SIZE,				// Invalid frame size, too big or small
	R2_CAM_SUPPORT,					// Cam file is not supported for changing of the frame size
	R2_BAD_TAPS,					// Number of taps couldn't be determined or is invalid
	R2_HCTAB_X16,					// Pixel clock divided by 16 is not supported by R2AqFrameSize
	R2_BAD_VCTAB,					// Couldn't find a valid VStart segment 0
	R2_BAD_HCTAB,					// Couldn't find a valid HStart segment 0 or 1 and/or HStop
    R2_ERROR_END

} R2RC_Enum;

// Message truncation point:    _______12345678901234567890123456______________________________          


#define R2_ERROR_ENTRIES	(R2_ERROR_END - R2_ERROR_START) 

#endif

