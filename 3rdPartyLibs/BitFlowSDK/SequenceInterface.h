#pragma once
#include "BufferInterface.h"
#include "BiApi.h"

/**
 * SequenceInterface class.\n
 * The SequenceInterface class provides the ability to acquire a 
 * sequence of images using a BitFlow interface board.
 */

class BFDLL SequenceInterface : public BufferInterface
{
public:
	// create instance
	SequenceInterface();

	// create instance and open board
	SequenceInterface(BFU32 brdNumber); 
	
	// create instance and open and setup board.
	SequenceInterface(BFU32 brdNumber, BFU32 numBuffers, BFU32 options);

	// create instance, open and setup the board with the buffers aligned
	// on a specified alignment boundary.
	SequenceInterface(BFU32 brdNumber, BFU32 numBuffers, BFU32 options, BFSIZET alignment);
	
	~SequenceInterface(void);
		
	// Sets up the board for sequence acquisition.
	void setup(BFU32 numBuffers, BFU32 options);

	// Sets up the board for sequence acquisition aligning each buffer
	// on a specified alignment boundary.
	void setup(BFU32 numBuffers, BFU32 options, BFSIZET alignment);
 
	// Sets up the board for sequence acquisition.
	void setup(PBFU32 *pMemArray, BFU32 numBuffers, BFU32 options);
	
	// Frees resources allocated by setup.
	void cleanup(); 
	
	// Change default acquisition settings.
	void setSettings(BFU32 startFrame, BFU32 numFrames, BFU32 skipFrames);
	
	// Wait for sequence to be acquired. 
	BFU32 seqWaitDone(BFU32 timeout); 
	
	// Issue sequence commands.
	void seqControl(BFU32 command, BFU32 options);
	
	// Wait for error.
	BFU32 seqErrorWait(); 
	
	// Returns error from error stack.
	BFU32 getSeqError(); 
	
	// Returns the current frame being acquired.
	BFU32 getCurFrameAcquired(); 
	
	// Returns when a frame has been DMAed into memory.
	BFU32 waitDoneFrame(BFU32 timeout); 
	
	// Returns info about a buffer.
	BiSeqInfo getBufferInfo(BFU32 bufferNumber); 
	
	// Clears buffer information for all buffers.
	void clearBufferInfo(); 

};

/** 
 * @example BiSimplePlusPlus.cpp
 * This is an example of how to use the SequenceInterface class.
 */
