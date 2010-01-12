//
// Creation:    BFOSInfoNT.h
// Created:     June 10, 2004
// Creator:     Bob Sheff
//
// Copyright (C) 1993-2004 by BitFlow, Inc.  All Rights Reserved.
//
// Description:
//
// BitFlow driver Windows NT operating system specific driver information structure.
//
// History:
//
// 06/10/04     rbs     Created file.
//

#if !defined(__BFOSINFONT__)
#define __BFOSINFONT__

#if defined(KernelNT)

	//
	// Windows NT Kernel Level System Specific Driver Info
	//
		 
	typedef struct _OSDriverInfoKrn		*OSDriverInfoKrnPtr, *pOSDriverInfoKrn;
	typedef struct _OSDriverInfoKrn
	{
		PDRIVER_OBJECT		pDriverObject;				// Kernel level driver object.
		PUNICODE_STRING		pDriverClass;				// BitFlow driver's class name.
		PUNICODE_STRING		pKernelException;			// BitFlow driver's kernel exception error message.
	    KMUTEX				DriverMutex;				// Mutex to protect DriverInfo access assinged level 2.
		PDEVICE_OBJECT		pLastDevice;				// Last device object handled by the driver.
		BFU32				LastDeviceBus;				// Bus number of the last device handled by the driver.
		BFU32				LastDeviceSlot;				// Slot number of the last device handled by the driver.
		BFU32				LastDeviceFunction;			// Function number of the last device handled by the driver.
	} OSDriverInfoKrn;

	//
	// Windows NT Kernel Level System Specific Device Info
	//

	typedef struct _OSInfoKrn			*OSInfoKrnPtr, *pOSInfoKrn;
    typedef struct _OSInfoKrn
    {
		BFBOOL				Stacked;					// Set True if the BitFlow device is in a driver stack.
		PUNICODE_STRING		pDevicePath;				// BitFlow device's registry path.
        PDEVICE_OBJECT		pDeviceObject;				// BitFlow device's device object.
        PDEVICE_OBJECT		pLowerObject;				// Device directly below the BitFlow device in a stacked driver.
        PDEVICE_OBJECT		pStackObject;				// Device somewhere below the BitFlow device in a stacked driver.
		LIST_ENTRY			WaitingListHead;			// Head of uncompleted irp queue.
	    KMUTEX				DeviceMutex;				// Device access mutex level 1 used to serialize device requests.
        KSPIN_LOCK			QueueSpin;					// Wait queue spin lock.
        KSPIN_LOCK			IntSpin;					// Interrupt queue spin lock.
		BFBOOL				ResourcesAllocated;			// Set True if resources were allocated by the driver (not pnp).
		PFILE_OBJECT		pFileObjectActive;			// File object that is active.
		PFILE_OBJECT		pFileObjectEngage;			// File object that was active during last engage.
		PFILE_OBJECT		pFileObjectUARTMutex;		// File object that was set the UART mutex.
		
		// DMA Adapter
		PDEVICE_OBJECT		PhysicalDeviceObject;		// The physical device object for the device requesting the DMA adapter structure.
		PDMA_ADAPTER		DMAAdapter;					// DMA adapter object
		BFU32				NumberOfMapRegisters;
		
		PDMA_ADAPTER		QuadAdapter;
		BFU32				MaxQuadMapRegisters;	
		PMDL				pQuadMDL;
		

		// Resource lists.

		PCM_RESOURCE_LIST	RRList;						// Raw resource list.
		PCM_RESOURCE_LIST	TRList;						// Translated resource list.

	    // IRQ requirements. 

        PKINTERRUPT			InterruptObject;			// Interrupt object.

		BFBOOL				RIrqGood;					// Translated interrupt values are good.
		BFU32				RIrqMode;					// Raw interrupt mode.				
	    BFU32				RIrqLevel;					// Raw interrupt level.
	    BFU32				RIrqVector;					// Raw interrupt vector.
		BFUPTR				RIrqAffinity;				// Raw interrupt affinity.

		BFBOOL				TIrqGood;					// Translated interrupt values are good.
		BFU32				TIrqMode;					// Translated interrupt mode.				
	    BFU32				TIrqLevel;					// Translated interrupt level.
	    BFU32				TIrqVector;					// Translated interrupt vector.
		BFUPTR				TIrqAffinity;				// Translated interrupt affinity.

		// Current Irp information. 

        PIRP				CurrentIrp;					// Irp that is being processed now.
		BFU32				IrpMajorFunction;			// Current Irp's Major Function code.
		BFU32				IrpMinorFunction;			// Current Irp's Minor Function code.
		BFU32				IrpIoControlCode;			// Current Irp's DeviceIoControl code.
		PBFVOID				IrpBuffer;					// Current Irp's buffer pointer.
		BFU32				IrpInLength;				// Current Irp's input buffer size.
		BFU32				IrpOutLength;				// Current Irp's output buffer size.
		BFBOOL				IrpNeedComplete;			// Current Irp's completion needs.
		BFU32				IrpStatus;					// Current Irp's completion status.
	} OSInfoKrn;

#endif

#if defined(UserNT)		 

	//
	// Windows NT User Level System Specific Driver Info
	//
		 
	typedef struct _OSDriverInfoUsr		*OSDriverInfoUsrPtr, *pOSDriverInfoUsr;
	typedef struct _OSDriverInfoUsr
	{
		BFU32				UserStuff;
	} OSDriverInfoUsr;

	//
	// Windows NT User Level System Specific Device Info
	//

	typedef struct _OSInfoUsr			*OSInfoUsrPtr, *pOSInfoUsr;
    typedef struct _OSInfoUsr
    {
        BFU32				UserStuff;
    } OSInfoUsr;

#endif

#endif





