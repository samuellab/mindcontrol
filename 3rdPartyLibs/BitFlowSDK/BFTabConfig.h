//
// Creation:    BFTabConfig.h
// Created:     October 21, 1998
// Creator:     Bob Sheff
//
// Copyright (C) 1993-94 by BitFlow, Inc.  All Rights Reserved.
//
// BitFlow Device Configuration Definitons
//
// History:
//
// 10/21/98     rbs     Created file.
//

#if !defined(__BFTABCONFIG__)
#define __BFTABCONFIG__

#include "BFType.h"

// Maximum device specific option record size in bytes.

#define	MAX_OPS_SIZE	100

#define VFF_UNKNOWN		0x00000001				// Flag bit that indicates and unknown Vendor and Family.
#define VFF_EVERYTHING	0xffffffff				// All 32 flag bits turned on.
#define VFF_IGNORE		0x00000000				// All zero means ignore the test (test always results in match). 

// Vendor Flags

typedef enum _VF
{
	VF_UNKNOWN		= VFF_UNKNOWN,				// Unknown device.
    VF_EMPTYSLOT	= 0x00000002,				// Empty slot.
    VF_INTEL		= 0x00000004,				// Intel device.
    VF_PLX			= 0x00000008,				// PLX device.
	VF_BITFLOW		= 0x00000010				// BitFlow device.
} VF;

#define VF_NOT_BITFLOW	(VFF_EVERYTHING ^ VF_BITFLOW ^ VF_EMPTYSLOT)

// Family Flags for Bitflow Devices

typedef enum _FF_BITFLOW_DEVICES
{
	FF_BITFLOW_UNKNOWN	= VFF_UNKNOWN,			// Unknown family.
	FF_DRIVER			= 0x00000002,			// Driver open, board closed.
	FF_BITFLOW			= 0x00000004,			// BitFlow family.
    FF_ROADRUNNER		= 0x00000010,			// RoadRunner family. 
	FF_RAVEN			= 0x00000020,			// Raven family.
#ifdef BUILD_TARGET_LINX
	FF_R64				= 0x00000080,			// Ginga family
#else
	FF_R64				= 0x00000040,			// R64 family.
#endif
	FF_STANDARD			= 0x00010000,			// Standard version of the root family.
	FF_CAMERALINK		= 0x00020000,			// Special CamerLink version of the root family.
	FF_ANALOG			= 0x00040000,			// Special Analog version of the root family.
	FF_COMPOSITE		= 0x00080000			// Special Composite version of the root family.
} FF_BITFLOW_DEVICES;

#define FF_LO16					0x0000ffff		// Low 16 bits.
#define FF_HI16					0xffff0000		// Hi 16 bits.
#define	FF_MODS					FF_HI16			// Modification bits.

#define FF_BITFLOW_SUPPORTS		(FF_ROADRUNNER | FF_RAVEN | FF_R64)
#define FF_BITFLOW_MODERN		(FF_ROADRUNNER | FF_RAVEN | FF_R64)
#define FF_R2_RV				(FF_ROADRUNNER | FF_RAVEN)
#define FF_ROADRUNNER_CL		(FF_ROADRUNNER | FF_CAMERALINK)
#define FF_R64_ALTA				(FF_R64 | FF_ANALOG)
#define FF_R64_ALTA_CO			(FF_R64 | FF_ANALOG | FF_COMPOSITE)
#define FF_BITFLOW_DRIVER		(FF_BITFLOW | FF_DRIVER)
#define FF_ROADRUNNER_DRIVER	(FF_ROADRUNNER | FF_DRIVER)
#define FF_ROADRUNNER_CL_DRIVER	(FF_ROADRUNNER_CL | FF_DRIVER)
#define FF_RAVEN_DRIVER			(FF_RAVEN | FF_DRIVER)
#define FF_R64_DRIVER			(FF_R64 | FF_DRIVER)

// Enumerated type version of the main flags to make debugging easier.

typedef enum _BF_Families
{
	FF_BitFlowUnknown		=	FF_BITFLOW_UNKNOWN,
	FF_BitFlowDriver		=	FF_BITFLOW_DRIVER,
	FF_RoadRunner			=	FF_ROADRUNNER,
	FF_RoadRunnerCL			=	FF_ROADRUNNER_CL,
	FF_Raven				=	FF_RAVEN,
	FF_RoadRunner64			=	FF_R64,
	FF_RoadRunnerDriver		=	FF_ROADRUNNER_DRIVER,
	FF_RoadRunnerCLDriver	=	FF_ROADRUNNER_CL_DRIVER,
	FF_RavenDriver			=	FF_RAVEN_DRIVER,
	FF_RoadRunner64Driver	=	FF_R64_DRIVER
} BF_Families;

// Macros to separate the root family bits from the modification bits.

#define FBits(Family)			(Family & ~FF_MODS)
#define MBits(Family)			(Family & FF_MODS)

// temporary INFOLO flags for development

typedef enum _KBN_DEV_BRDS
{
	KBN_PLDA_ENGINE = 0x1
} KBN_DEV_BRDS;

// Modern Device IDs

#define BF_PCI_R64				0x2000			// R64 Device ID
#define BF_PCI_KBN				0x3000			// Karbon Device ID
#define BF_PCI_NEO				0x4000			// Neon Device ID
#define BF_PCI_ALT_AN			0x5000			// Alta-AN Device ID
#define BF_PCI_ALT_CO			0x6000			// Alta-CO Device ID

// Family Flags for Intel Devices

typedef enum _FF_INTEL
{
	FF_INTEL_UNKNOWN	= VFF_UNKNOWN,
	FF_INTEL_430VX		= 0x00000002,
	FF_INTEL_430FX		= 0x00000004,
	FF_INTEL_430HX		= 0x00000008,
	FF_INTEL_440FX		= 0x00000010
} MF_INTEL;

#define FF_INTEL_430_ALL		(FF_INTEL_430VX | FF_INTEL_430FX | FF_INTEL_430HX)

// PCI configuration space Vendor, Device and SubVendor IDs.

// Extraction Masks

#define VID_MASK				0xffff			// All vendor ID bits.
#define DID_MASK				0xffff			// All device ID bits.
#define SID_MASK				0xffff			// All sub-vendor ID bits.

#define DID_BF_MASK				0xf000			// Device Id bits used to identify BitFlow families.

// Vendor IDs

#define BF_PCI_VEN_ID			0x118d			// BitFlow vendor ID.
#define	PLX_PCI_VEN_ID			0x10b5			// PLX vendor ID.
#define INTEL_PCI_VEN_ID		0x8086			// Intel vendor ID.

// Device IDs

// Intel PCI ChipsSet Families

#define BF_PCI_INTEL_430VX		0x7030
#define BF_PCI_INTEL_430FX		0x122d
#define BF_PCI_INTEL_430HX		0x1250
#define BF_PCI_INTEL_440FX		0x1237
#define BF_PCI_INTEL_LANAI_1	0x0340
#define BF_PCI_INTEL_LANAI_2	0x0341

#if !defined(KernelOS)

#define PCI_INVALID_VENDORID	0xFFFF
#define PCI_MAX_DEVICES			32

#endif

#define PCI_MAX_FUNCTIONS		4

// Driver & Device States

typedef enum _DriverStates
{
	DriverInstalling = 0,							// The driver is installing.
	DriverInstalled,								// The driver is installed.
	DriverRemoving,									// The driver is removing.
	DriverRemoved,									// The driver is removed.
	DriverUndefined,								// The driver state is undefined.

	DeviceInstalling,								// The device is installing.
	DeviceInstalled,								// The device is installed.
	DeviceStarting,									// The device is starting.
	DeviceStarted,									// The device is started.
	DeviceStopping,									// The device is stopping.
	DeviceStopped,									// The device is stopped.
	DeviceRemoving,									// The device is removing.
	DeviceRemoved,									// The device is removed.
	DeviceUndefined									// The device state is undefined.
} DriverStates;

// VFO Parse States

typedef enum _ParseOpsStates
{
	ParseOpsUndefined = 0,	// Bug catcher state.
	ParseOpsRegistry,		// Parse missing board based on BoardParam registry settings.
	ParseOpsConfig,			// Parse raw configuration data.
	ParseOpsMapped,			// Parse a mapped board.
	ParseOpsFlashed			// Parse a flashed board.
} ParseOpsStates;

// Vendor, Family and Options Information Record.

typedef struct _VFORec
{
	BFCHAR			Name[20];					// The device name if the device is a started BitFlow device.
	BFBOOL			Registered;					// True if the device is a BitFlow device registered in the registry.
	BFU32			Switch;						// BitFlow device hardware Id switch setting.
	BFU32			Number;						// Enumerated board number if the device is a started BitFlow device.
	BFU32			Index;						// The BoardParam registry index if the device is a BitFlow device.
	BFU32			Order;						// EnumerateByLookup BusSlot override order number.
	BFBOOL			Pseudo;						// True if the device is a pseudo BitFlow device.
	BFBOOL			Live;						// True if the device is a started BitFlow device.
	DriverStates	State;						// This device's current driver state.
	BFBOOL			CameraLink;					// True for a CameraLink BitFlow device.
	BFBOOL			PMC;						// True for a PMC BitFlow device.
	BFBOOL			PLDAEngine;					// Set to true if the board has a PLDA Engine

	BFU32			Vendor;						// Vendor Id.
	BF_Families		Family;						// Family Id. 

	BFU32			BusType;					// Bus type. 		
	BFU32			Bus;						// Bus number.
	BFU32			Slot;						// Slot number. 
	BFU32			Function;					// Function number.

	BFU32			VendorId;					// PCI VendorId.
	BFU32			DeviceId;					// PCI DeviceId.
	BFU32			SubVendorId;				// PCI SubVendorId.
	BFU32			SubSystemId;				// PCI SubSystemId.
	BFU32			Revision;					// PCI Revision Id.

	BFU32			InfoHi;						// High order information bits.
	BFU32			InfoLo;						// Low order information bits.

	BFU32			RegFilter;					// Filter bits for register operations.
	BFU32			FlashFilter;				// Filter bits for flash download.

	BFBOOL			Overridden;					// If True, the PCI Board Ids are overridden by registry entries.

	ParseOpsStates	LastParse;					// Last parse state.

	BFU32	OpSpace[(MAX_OPS_SIZE + 3) / 4];	// Storage space for family specific options forced to 32 bit alignment. 
} VFORec, *VFOPtr, *pVFO;

#endif
