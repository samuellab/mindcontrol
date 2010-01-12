#pragma once
#include "BiApi.h"

/*! \mainpage Buffer Interface Class Library
 *
 * \section intro_sec Overview
 *
 * The Buffer Interface Class Library provides a C++ wrapper around the
 * BitFlow's C based BufIn API for sequence and circular image acquisition.
 * There are several advantages to using the Buffer Interface class library
 * over the BufIn API. Some of the advantages are:\n
 *	1. Fewer method/function calls to accomplish sequence or circular capture.\n
 *	2. No need to call cleanup methods/functions.\n
 *	3. Fewer method/function parameters.\n
 *	4. Improved error handling by throwing exceptions.\n
 *
 * This document provides class informatation on the sequence and circular
 * acquistion classes, along with examples of how to use the classes to
 * acquire from Bitflow's extensive line of framegrabbers.
 */

/**
 * BufferInterface class.\n
 * The BufferInterface class provides the common functionality
 * that the Sequence and Circular Interface classes use.
 */

class BFDLL BufferInterface
{
public:
	BufferInterface(void);
	~BufferInterface(void);

	// Opens board for acquisition.
	void open(BFU32 brdNumber);

	// Opens board for acquisition with specified options
	void open(BFU32 brdNumber, BFU32 options);

	// Opens board for acquisition and loads the camera file given.
	void open(BFU32 brdNumber, PBFCHAR camFileName);
	
	// Closes board resources.
	void close(); 
	
	/**
	 * Returns the board handle. This will be useful when using other
	 * BitFlow APIs.
	 * @return Returns the board handle.
	 */
	Bd getBoardHandle() { return m_hBoard; }

	// Returns a pointer to the array of pointers to the buffers.
	PBFU32* getBufferArrayPointers(); 
	
	// Returns information about the board and camera file.
	BFU32 getBrdInfo(BFU32 brdInqVar); 
	
	// Returns the number of frames that have been captured.
	BFU32 getNumFramesCaptured();
	
	// Returns the number of frames that where missed during acquisition.
	BFU32 getNumFramesMissed();
	
	// If returns TRUE <=> a start command has been issued.
	BFBOOL getStartAcqFlag();
	
	// If returns TRUE <=> a stop command has been issued.
	BFBOOL getStopAcqFlag();
	
	// If returns TRUE <=> an abort command has been issued.
	BFBOOL getAbortAcqFlag();
	
	// If returns TRUE <=> a pause command has been issued.
	BFBOOL getPauseAcqFlag();
	
	// If returns TRUE <=> instance cleanup has occured.
	BFBOOL getCleanupAcqFlag();

	// Returns the major version of the Bi API.
	BFU32 getMajorVersion();
	
	// Returns the minor version of the Bi API.
	BFU32 getMinorVersion();

	// Sets the hardware trigger mode
	void setTriggerMode(BFU32 triggerMode, BFU32 trigPolarity); 
	
	// Returns the current hardware trigger mode of the board.
	BFU32 getTriggerMode(); 
	
	// Returns the current hardware trigger polarity.
	BFU32 getTriggerPolarity(); 
	
	// Issues a software trigger.
	void issueSoftwareTrigger(BFU32 trigMode); 
	
	// Displays dialog describing error
	BFU32 showError(BFU32 errorNum); 

	// Write a single buffer to disk.
	void writeBuffer(PBFCHAR fileName, BFSIZET fileNameSize, BFU32 bufferNumber, BFU32 options);

	// Write a sequence of buffers to disk. 
	void writeSeqBuffer(PBFCHAR fileName, BFSIZET fileNameSize, BFU32 firstBufNumber, BFU32 numBufs, 
		BFU32 Options);

	// read a sequence of files into memory.
	void readSeqFile(PBFCHAR fileName, BFU32 firstBufNumber, BFU32 numBufs); 

	// Clears all buffers memory
	void clearBuffers();

	// Returns the error test for a specific error number
	void getErrorText(BFU32 errorNumber, PBFCHAR errorText, PBFU32 errorTextSize);

	// Returns the number of buffers software is behind the hardware DMA engine.
	BFU32 getBufferQueueSize();
	
	// Set Buffer acquisition timeout.
	void setTimeout( BFU32 TimeoutValue );

	// Loads a camera file for the board to use.
	void loadCamFile(PBFCHAR camFileName);

	// Unloads a camera file loaded by the loadCamFile method.
	void unloadCamFile();

	// Returns if the board is open or not
	BFBOOL isBoardOpen() {return isOpen;}

	// Returns if the board is setup or not
	BFBOOL isBoardSetup() {return isSetup;}

protected:
	/** Handle to the opened board */
	Bd m_hBoard;
	
	/** Bi info structure */		
	BIBA m_BufferArray;	

	/** A pointer to a loaded camera file */
	PBFCNF m_pCam;

	BFBOOL isMemAssigned;
	BFBOOL isMemAllocated;
	BFBOOL isSetup;
	BFBOOL isOpen;

};


/**
 * Bitflow exception class to be throw on errors.
 */
class BFDLL BFException
{
public:
	BFException(){errorNum = 0;}
	BFException(BFU32 error) {errorNum = error;}
	~BFException(){};

	/**
     * Pops up a dialog displaying a text description of the error that
	 * was thrown.
	 *
	 * @return Returns one of the following:\n
     *  BI_OK - The user clicked on the ok button on the dialog.\n
     *  BI_CANCEL - The user clicked on the cancel button on the dialog.
     */
	BFU32 showErrorMsg() { return(BiErrorShow(0, errorNum)); }

	// Returns an text based message of an error that has occured.
	BFU32 getErrorText(PBFCHAR ErrorText, PBFU32 ErrorTextSize);

	/**
	 * Returns the error number of the error that occured.
	 */
	BFU32 getErrorNumber() {return errorNum;}

private:
	BFU32 errorNum;

};