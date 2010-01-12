#pragma once
#include "BufferInterface.h"
#include "BiApi.h"

/**
 * CircularInterface class.\n
 * The CircularInterface class provides the ability to acquire images
 * into a circular buffer using a BitFlow interface board.
 */

class BFDLL CircularInterface : public BufferInterface
{
public:
	// create instance
	CircularInterface();

	// create instance and open board.
	CircularInterface(BFU32 brdNumber);
	
	// create instance, open and setup board.
	CircularInterface(BFU32 brdNumber, BFU32 numBuffers, BFU32 errorMode,
		BFU32 options);

	// create instance, open and setup the board with the buffers aligned
	// on a specified alignment boundary.
	CircularInterface(BFU32 brdNumber, BFU32 numBuffers, BFU32 errorMode,
		BFU32 options, BFSIZET alignment);
	
	~CircularInterface(void);

	// Sets up the board for circular acquisition.
	void setup(BFU32 numBuffers, BFU32 errorMode, BFU32 options);

	// Sets up the board for circular acquisition aligning each buffer
	// on a specified alignment boundary.
	void setup(BFU32 numBuffers, BFU32 errorMode, BFU32 options, BFSIZET alignment);

	// Sets up the board for sequence acquisition.
	void setup(PBFU32 *pMemArray, BFU32 numBuffers, BFU32 errorMode, 
		BFU32 options); 

	// Frees resources allocated by setup.
	void cleanup(); 
	
	// Issue circular commands.
	void cirControl(BFU32 command, BFU32 options);
	
	// Wait for error.
	BFU32 cirErrorWait();

	// Returns error from the error stack
	BFRC getCirError();

	// Returns when a frame has been DMAed into memory.
	BFU32 waitDoneFrame(BFU32 timeout, PBiCirHandle CirHandle);

	// Set status of a buffer to BIAVAILABLE or BIHOLD
	BFU32 setBufferStatus(BiCirHandle cirHandle, BFU32 status);

	// Set status of a buffer to BIAVAILABLE or BIHOLD
	BFU32 setBufferStatus(BFU32 bufferNumber, BFU32 status);

	// Returns the status of a buffer
	BFU32 getBufferStatus(BiCirHandle cirHandle);

	// Returns the status of the buffer
	BFU32 getBufferStatus(BFU32 bufferNumber);

	// SMS - in the future
	//void setNextBufferForAcq(BFU32 bufferNumber);
	//void addAdditionalBuffers(BFU32 numBuffers);

};

/** 
 * @example CircClassExample.cpp
 * This is an example of how to use the CircularInterface class.
 */

/**
 * @example CircHoldSimple.cpp
 * This console application demonstrates the holding of buffers.
 */