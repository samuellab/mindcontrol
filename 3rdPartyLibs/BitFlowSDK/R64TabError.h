//
// Creation:    R64TabError.h
// Created:     May 6, 2002
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2002 by BitFlow, Inc.  All Rights Reserved.
//
// R64 Error Handler Definitions
//
// History:
//
// 05/06/02     rbs     Created file.
//

#if !defined(__R64TABERROR__)
#define __R64TABERROR__

#include "R64Type.h"
#include "BFTabError.h"
#include "BFTabConfig.h"

//
// R64 Error Return Codes
//

#define R64_ERROR_ZERO (FF_R64 << BF_ERROR_FAMILY_SHIFT)

typedef enum _R64RC_Enum
{
    R64_OK = 0,					    // Operation succeeded.
	R64_ERROR_START = R64_ERROR_ZERO,
    R64_BAD_NEWS,					// Operation failed.
    R64_BAD_HCTAB_ADDR,				// HCTab address error.
    R64_BAD_VCTAB_ADDR,				// VCTab address error.
    R64_CTAB_PEEK_BAD,				// CTabPeek error.
    R64_CTAB_POKE_BAD,				// CTabPoke error.
    R64_CTAB_READ_BAD,				// CTabRead error.
    R64_CTAB_WRITE_BAD,				// CTabWrite error.
    R64_CTAB_FILL_BAD,				// CTabFill error.
    R64_CTAB_RAMP_BAD,				// CTabRamp error.
    R64_BAD_DPM_ADDR,               // DPM address error.
    R64_DPM_PEEK_BAD,               // DPMPeek error.
    R64_DPM_POKE_BAD,               // DPMPoke error.
    R64_DPM_READ_BAD,               // DPMRead error.
    R64_DPM_WRITE_BAD,              // DPMWrite error.
    R64_DPM_FILL_BAD,               // DPMFill error.
    R64_DPM_RAMP_BAD,               // DPMRamp error.
	R64_DPM_READ_DMA_BAD,			// DPMReadDMA error.
    R64_BAD_FREQ,					// Illegal clock frequency.
    R64_CON_FREQ_BAD,				// ConFreq error.
    R64_BAD_GPOUT,					// Illegal GPOut value.
    R64_CON_GPOUT_BAD,				// ConGPOut error.
	R64_BAD_CON_PARAM,				// Bad parameter to control functions.
	R64_BAD_TRIGAQ,					// Illegal TrigAq setting. 
    R64_CON_TRIG_AQ_BAD,			// ConTrigAq error.
    R64_BAD_VSTOP,					// Illegal VMode selection. 
    R64_BAD_HSTOP,					// Illegal HMode selection. 
    R64_CON_VMODE_BAD,				// ConVMode error.
    R64_CON_HMODE_BAD,				// ConHMode error.
	R64_AQSETUP_FAIL,				// AqSetup failed.
	R64_BAD_STOP,				    // Error stopping DMA and/or acquistion.
	R64_AQ_NOT_SETUP,			    // Board not setup for acquistion.
	R64_BAD_AQ_CMD,				    // Board not ready for Aq command issued.
	R64_AQSTRT_TIMEOUT,			    // Timeout waiting for acquisition to start.
	R64_AQEND_TIMEOUT,			    // Timeout waiting for acquisition to end.
	R64_BAD_WAIT,				    // Cannot wait for acquire to end when board is in this state.
	R64_BAD_CNF,					// Error extracting information from camera configuration.
	R64_BAD_FRM_SIZE,				// Invalid frame size, too big or small
	R64_HCTAB_X16,					// Pixel clock divided by 16 is not supported by R64AqFrameSize
	R64_BAD_VCTAB,					// Couldn't find a valid VStart segment 0
	R64_BAD_HCTAB,					// Couldn't find a valid HStart segment 0 or 1 and/or HStop
	R64_CAM_SUPPORT,				// Cam file is not supported for changing of the frame size
	R64_BAD_INQ_PARAM,			    // Bad parameter to inquire function.
    R64_BAD_STRUCT,				    // Error in size of camera strucuture.
	R64_BAD_CNF_FILE,			    // Error reading configuration file.
	R64_INCOMP,					    // This configuration file is incompatible with this board.
	R64_BAD_CNFG,				    // Error getting item from configuration structure
    R64_NO_CNFDIR_REG_KEY,			// Cnf Dir path key missing.
	R64_BAD_PATH,				    // Error building file path.
	R64_UNKOWN_REV,					// Board/camera revision unkown
	R64_BRD_NOT_COMP,				// Camera file not compatible with this model board.
	R64_UNKOWN_COMP,				// Camera file compatibility is unkown.
	R64_TIMEOUT,					// Timeout wait for command.
	R64_CTAB_PEEK_ERR,				// R64CTabPeek Error
	R64_CTAB_READ_ERR,				// R64CTabRead Error
	R64_CTAB_WRITE_ERR,				// R64CTabWrite Error
	R64_CTAB_POKE_ERR,				// R64CTabPoke Error
	R64_CTAB_FILL_ERR,				// R64CTabFill Error
	R64_CTAB_RAMP_ERR,				// R64CTabRamp Error
	R64_DPM_PEEK_ERR,				// R64DPMPeek Error
	R64_DPM_READ_ERR,				// R64DPMRead Error
	R64_DPM_WRITE_ERR,				// R64DPMWrite Error
	R64_DPM_POKE_ERR,				// R64DPMPoke Error
	R64_DPM_FILL_ERR,				// R64DPMFill Error
	R64_DPM_RAMP_ERR,				// R64DPMRamp Error
	R64_DPM_READ_DMA_ERR,			// R64DPMReadDMA Error
	R64_BAD_IRP_STOP,			    // Error canceling interrupt signalling IRPs.
	R64_BAD_AQ_STOP,				// Timeout waiting for acquisition to stop.
	R64_BAD_FIFO_RESET,				// Could not reset FIFO overflow.
	R64_BAD_ROI,					// Error calculating QTAB for ROI.
	R64_BAD_MODEL,				    // Error building QTAB from model parameters.
	R64_DMA_ACTIVE_ERR,				// R64DMAActive Error
	R64_DMA_START_ERR,				// R64DMAStart Error
	R64_DMA_STOP_ERR,				// R64DMAStop Error
	R64_DMA_ACTIVE,					// DMA is already active.
	R64_DMA_START_BAD,				// DMAStart error.
	R64_DMA_START_TIMEOUT,			// DMA start timeout.
	R64_DMA_STOP_BAD,				// DMAStop error.
	R64_DMA_STOP_TIMEOUT,			// DMA stop timeout.
	R64_DMA_STUCK,					// R64 DMA engine hung.
	R64_DMA_START_NULL,				// Quad start address BFNULL.
	R64_BAD_FIRMWARE,				// Error downloading camera file requested firmware.
	R64_BAD_DISP_BIT_DEPTH,			// This pixel depth not support for display.
	R64_SLAVE_FW_MISMATCH,			// Requested slave firmware does not match master's firmware.
	R64_RLE_TOO_SMALL,				// The CTab change requested will not fit in the RLE CTab.
	R64_NOT_RLE_BOARD,				// RLE CTab Command issued to a non-RLE board.
	R64_RLE_NO_SUPPORT,				// Function not supported on RLE boards.
	R64_NTG_NOT_SUPPORTED,			// Board does not support NTG
	R64_NTG_EXP_OUT_OF_RANGE,		// NTG parameters are out of range of NTG
	R64_NTG_EXP_GT_LF,				// The exposure period is longer than the line/frame period
	R64_NTG_UNKNOWN_MODE,			// NTG Trigger mode is unknown
	R64_ENCDIV_NOT_SUPPORTED,		// Board does not support the encoder divider
	R64_ENCDIV_OUT_OF_RANGE,		// The request encoder divider scale factor is too big
	R64_ENCDIV_UNKNOWN_CLK,			// The request clock frequency is not supported the encoder divder

    R64_ERROR_END
} R64RC_Enum;

// Message truncation point:    _______12345678901234567890123456______________________________          


#define R64_ERROR_ENTRIES	(R64_ERROR_END - R64_ERROR_START) 

#endif

