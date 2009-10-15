/*
 * CalibLib.h
 *
 *  Created on: Oct 15, 2009
 *      Author: andy
 */


/*
 * This structure contains information about calibrating the DLP to the CCD
 *
 */
typedef struct CalibDataStruct{
	int* CCD2DLPLookUp;
	CvSize SizeOfDLP;
	CvSize SizeOfCCD;

} CalibData;



/*
 * Create and allocate memory for the CalibData structure
 *
 * Currently SizeOfCCD is stored but not really used
 *
 */
void CreateCalibData( CalibData* Calib,CvSize SizeOfDLP, CvSize SizeOfCCD);

/*
 * Deallocate memory for CalibData object
 */
void DestroyCalibData(CalibData* Calib);




/*
 * Read In Calibration Frome File
 *
 * Returns 1 if open failed.
 * Returns -1 if open succesfully but read fails.
 */

int ReadCalibFromFile(CalibData* Calib, char * filename);
