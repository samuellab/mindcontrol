/***************************************************************************
*
* BFIODef.h
*
* BFDiskIO API
* 
* Types and defines for BFIO library
*
* Copyright (C) 2002 by BitFlow, Inc.  All Rights Reserved.
*
* 10/22/2002	sms		created
*
***************************************************************************/

#if !defined(__BFIODEF__)
    #define __BFIODEF__

#ifdef __cplusplus
extern "C" {
#endif

// Error Codes
typedef struct _BFIOErrors
{
	int		ErrorCode;
	char	FailureDescription[256];

}BFIOErrors;

extern BFIOErrors BFIOErrorTable[];

typedef enum _DiskIOErr
{
	BF_ER_START = 7000,

	BF_CANCEL,				// The cancel button was pressed
	BF_ER_AVI_WRITE_SINGLE,	// Use BFIOWriteMultiple to write an AVI file.
	BF_ER_AVI_READ_SINGLE,  // Use BFIOReadMultiple to read an AVI file.
	BF_ER_FILE_NAME,		// No file name given
	BF_ER_BUF_POINTER,		// Invalid buffer pointer
	BF_ER_NUM_BUFFERS,		// Invalid number of buffers
	BF_ER_XSIZE,			// Invalid XSize, not greater than zero
	BF_ER_YSIZE,			// Inavlid YSize, not greater than zero
	BF_ER_BITDEPTH_UNKNOWN, // Bit depth must be 8, 10, 12, 14, 16, 24 or 32
	BF_ER_BITDEPTH_SWAPRGB,	// Invalid bit depth for swap rgb option
	BF_ER_PACK24_BITDEPTH,	// Must start with 32 bit data to use the 32TO24BIT option
	BF_ER_CAD6_OPTION,		// The CAD6 option must be used with no other options.
	BF_ER_BMP_BIT_DEPTH,	// Invalid bit depth for bmp
	BF_ER_BMP_OPEN_FILE,	// Failed opening bmp file
	BF_ER_BMP_FILE_HEADER,	// Failed writing bmp header to file
	BF_ER_BMP_DATA_WRITE,	// Failed writing image data to bmp file
	BF_ER_BMP_DATA_READ,	// Failed reading image data from bmp file.
	BF_ER_OPEN_FILE,		// Could not open file from open dialog
	BF_ER_DATA_READ,		// Error reading header from file in open dialog
	BF_ER_LOW_MEM,			// Failed allocating memory.
	BF_ER_TIF_TAG,			// Tif tag not supported
	BF_ER_TIF_BIT_DEPTH,	// Invalid tif bit depth
	BF_ER_TIF_OPEN_FILE,	// Failed opening tif file
	BF_ER_TIF_FILE_HEADER,	// Failed writing tif header to file
	BF_ER_TIF_DATA_WRITE,	// Failed writing image data to tif file
	BF_ER_TIF_DATA_READ,	// Failed reading image data from tif file.
	BF_ER_RAW_OPEN_FILE,	// Failed opening raw file
	BF_ER_RAW_DATA_WRITE,	// Failed writing image data to raw file
	BF_ER_RAW_DATA_READ,	// Failed reading image data from raw  file.
	BF_ER_AVI_BIT_DEPTH,	// Invalid bit depth for avi
	BF_ER_AVI_OPEN_FILE,	// Failed opening avi file
	BF_ER_AVI_DATA_WRITE,	// Failed writing image data to the avi stream
	BF_ER_AVI_DATA_READ,	// Failed reading image data from avi file.
	BF_ER_CREATE_STREAM,	// Error creating AVI stream.
	BF_ER_SAVE_OPTIONS,		// Error with dialog box save options
	BF_ER_COMPRESS_STREAM,	// Error with compressing the stream.
	BF_ER_AVI_HEADER,		// Error putting AVI header in the stream.
	BF_ER_FILE_FORMAT,		// Invalid file format. Please use bmp, tiff, raw or avi 
	BF_ER_NUMBER_OF_FRAMES,	// Number of frames asked for exceeds the number of frames the AVI file
	BF_ER_NO_DECOMPRESS,	// Decompressing image to dimensions outside of maximum limit.
	BF_ER_RAW_READ_PARAMS,	// Can not read image info such as XSize, YSize or bit depth from raw data
	BF_ER_RAW_OPEN_TEXTFILE,// Failed to open the text file to write raw image file information.
	BF_ER_RAW_TEXT_WRITE,	// Failed to write the data to the raw text file.
	BF_ER_FILE_EXISTS,		// The file exists and the OVERWRITEFILE option is not being used.

	BF_ER_END
	
}DiskIOErr;

// Write option defines
#define CAD6			1
#define SWAPRGB			2
#define PACK32TO24BIT	4
#define BOTTOM_UP		8
#define OVERWRITEFILE	16

#ifdef __cplusplus
}
#endif

#endif /* __BFIODEF__ */