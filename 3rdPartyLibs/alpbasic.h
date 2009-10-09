//  *************************************************************************
//  *                                                                       *
//  *   Project:      ALP basic	  (ALP basic DLL)							*
//  *   Filename:     alpbasic.h : Header File 								*
//  *                                                                       *
//  *************************************************************************
//  *                                                                       *
//  *   © 2004-2008 ViALUX GmbH. All rights reserved.                       *
//  *                                                                       *
//  *************************************************************************
//  *                                                                       *
//  *   Version:        2                                                   *
//  *                                                                       *
//  *************************************************************************
//
#ifndef ALPBASIC_API
#define ALPBASIC_ATTR
#define ALPBASIC_API extern "C" __declspec(dllimport)
#endif

#ifndef _ALPBASIC_H__INCLUDED
#define _ALPBASIC_H__INCLUDED

/******************************************************************/
/** Constants *****************************************************/
/******************************************************************/

enum ALPB_RETURNCODES {
	ALPB_SUCCESS		= 0,
	ALPB_SUCC_PARTIAL	= 1,
	ALPB_ERROR			= 0x80000000,	// generic error, e.g. "not implemented"; should never be returned to user
	ALPB_ERR_NOT_FOUND	= 0x80000001,	// DevAlloc: serial number not found
	ALPB_ERR_DUPLICATE	= 0x80000002,	// DevAlloc: device already allocated
	ALPB_ERR_INIT		= 0x80000003,	// DevAlloc: initialization error
	ALPB_ERR_RESET		= 0x80000004,	// DevAlloc: init. error, maybe due to reset switch
	ALPB_ERR_HDEVICE	= 0x80000005,
	ALPB_ERR_DISCONNECT	= 0x80000006,
	ALPB_ERR_CONNECTION	= 0x80000007,	// connection error occurred, but device is (maybe) re-connected
	ALPB_ERR_MT			= 0x80000008,
	ALPB_ERR_HALT		= 0x80000009,
	ALPB_ERR_MEM		= 0x8000000A,
	ALPB_ERR_MEM_I		= 0x8000000B,
	ALPB_ERR_PARAM		= 0x8000000C,
	ALPB_ERR_DONGLE		= 0x8000000D,
};

enum ALPB_DLL_CONTROLTYPES {
	ALPB_DLL_TIMEOUT		= 0,
	ALPB_DLL_VERSION		= 1,
	ALPB_DLL_DEV_VERSIONS	= 2,
};

enum ALPB_DEV_CONTROLTYPES {
	ALPB_DEV_HALT			= 0,
	ALPB_DEV_DRIVER_VER		= 1,
	ALPB_DEV_FIRMWARE_DATE	= 2,
	ALPB_DEV_CONFIG_DATE	= 3,
	ALPB_DEV_SERIAL			= 4,
	ALPB_DEV_DMDTYPE		= 5,
	ALPB_DEV_VERSION		= 6,
	ALPB_DEV_DDC_VERSION	= 7,
	ALPB_DEV_SWITCHES		= 8,
	ALPB_DEV_DDC_SIGNALS	= 9,
};

enum ALPB_DMDTYPES {
	ALPB_DMDTYPE_INVALID	= 0,
	ALPB_DMDTYPE_XGA		= 1,
	ALPB_DMDTYPE_SXGA_PLUS	= 2,
	ALPB_DMDTYPE_1080P_095A	= 3,	// (1080P 0.95" Type A),
	ALPB_DMDTYPE_XGA_07A	= 4,	// (XGA .7" Type A), 
	ALPB_DMDTYPE_XGA_055A	= 5,	// (XGA .55" Type A), 
	ALPB_DMDTYPE_XGA_055X	= 6,	// (XGA .55" Type X),
};

enum ALPB_RESETTYPES {
	ALPB_RESET_SINGLE		= 0,
	ALPB_RESET_PAIR			= 1,
	ALPB_RESET_QUAD			= 2,
	ALPB_RESET_GLOBAL		= 4,
};

enum ALPB_SPECIAL_VALUES {
	ALPB_INFINITE = 0xFFFFFFFF,
};


/******************************************************************/
/** Types *********************************************************/
/******************************************************************/

typedef long ALPB_HDEVICE;

struct ALPB_VERSION {
	short	Version1;
	short	Version2;
	short	Version3;
	short	Build;
};
struct ALPB_DATE {
	short	Year;		// year AD
	short	Month;		// month: 1..12
	short	Day;		// day of month: 1..31
};




/******************************************************************/
/** Function prototypes *******************************************/
/******************************************************************/

// further specify function arguments (pointers): IN, OUT, or INOUT
#ifndef OUT
#define OUT
#endif

#ifndef IN
#define IN
#endif

#ifndef INOUT
#define INOUT
#endif


// return SUCCESS, ERR_MT, ERR_MEM, or ERR_PARAM
ALPBASIC_API long ALPBASIC_ATTR Alp3bDllControl(long ControlType, IN void *pValue);
ALPBASIC_API long ALPBASIC_ATTR AlpbDllControl(long ControlType, IN void *pValue);

// return SUCCESS, ERR_MT, ERR_MEM, or ERR_PARAM
ALPBASIC_API long ALPBASIC_ATTR Alp3bDllInquire(long QueryType, OUT void *pValue);
ALPBASIC_API long ALPBASIC_ATTR AlpbDllInquire(long QueryType, OUT void *pValue);

// return SUCCESS, SUCC_PARTIAL, ERR_MEM, or ERR_PARAM
ALPBASIC_API long ALPBASIC_ATTR Alp3bDllGetResultText(long RetVal, INOUT long *pSize, OUT char *pStr);
ALPBASIC_API long ALPBASIC_ATTR AlpbDllGetResultText(long RetVal, INOUT long *pSize, OUT char *pStr);

// return SUCCESS, ERR_INIT, ERR_INIT_DUP, ERR_MT, or ERR_MEM
ALPBASIC_API long ALPBASIC_ATTR Alp3bDevAlloc(unsigned long nSerial, OUT ALPB_HDEVICE *hDevice);
ALPBASIC_API long ALPBASIC_ATTR AlpbDevAlloc(unsigned long nSerial, OUT ALPB_HDEVICE *hDevice);

// return SUCCESS, ERR_HDEVICE, ERR_DISCONNECT, ERR_CONNECTION, ERR_MT, ERR_MEM, or ERR_PARAM
ALPBASIC_API long ALPBASIC_ATTR Alp3bDevControl(ALPB_HDEVICE hDevice, long ControlType, IN void *pValue);
ALPBASIC_API long ALPBASIC_ATTR AlpbDevControl(ALPB_HDEVICE hDevice, long ControlType, IN void *pValue);

// return SUCCESS, ERR_HDEVICE, ERR_DISCONNECT, ERR_CONNECTION, ERR_MT, ERR_MEM, or ERR_PARAM
ALPBASIC_API long ALPBASIC_ATTR Alp3bDevInquire(ALPB_HDEVICE hDevice, long QueryType, OUT void *pValue);
ALPBASIC_API long ALPBASIC_ATTR AlpbDevInquire(ALPB_HDEVICE hDevice, long QueryType, OUT void *pValue);

// return SUCCESS, ERR_HDEVICE, or ERR_MT
ALPBASIC_API long ALPBASIC_ATTR Alp3bDevFree(ALPB_HDEVICE hDevice);
ALPBASIC_API long ALPBASIC_ATTR AlpbDevFree(ALPB_HDEVICE hDevice);

// return SUCCESS, ERR_HDEVICE, ERR_DISCONNECT, ERR_CONNECTION, ERR_MT, ERR_HALT, ERR_MEM, or ERR_PARAM
ALPBASIC_API long ALPBASIC_ATTR Alp3bDevLoadRows(ALPB_HDEVICE hDevice, IN unsigned char *pImage, long FirstRow, long LastRow);
ALPBASIC_API long ALPBASIC_ATTR AlpbDevLoadRows(ALPB_HDEVICE hDevice, IN unsigned char *pImage, long FirstRow, long LastRow);

// return SUCCESS, ERR_HDEVICE, ERR_DISCONNECT, ERR_CONNECTION, ERR_MT, ERR_HALT, or ERR_PARAM
ALPBASIC_API long ALPBASIC_ATTR Alp3bDevClear(ALPB_HDEVICE hDevice, long FirstBlock, long LastBlock);
ALPBASIC_API long ALPBASIC_ATTR AlpbDevClear(ALPB_HDEVICE hDevice, long FirstBlock, long LastBlock);

// return SUCCESS, ERR_HDEVICE, ERR_DISCONNECT, ERR_CONNECTION, ERR_MT, ERR_HALT, or ERR_PARAM
ALPBASIC_API long ALPBASIC_ATTR Alp3bDevReset(ALPB_HDEVICE hDevice, long ResetType, long ResetAddr);
ALPBASIC_API long ALPBASIC_ATTR AlpbDevReset(ALPB_HDEVICE hDevice, long ResetType, long ResetAddr);

#endif // _ALPBASIC_H__INCLUDED
