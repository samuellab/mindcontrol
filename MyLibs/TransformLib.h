/*
 * TransformLib.h
 *
 *  Created on: Oct 15, 2009
 *      Author: andy
 *
 *      The Transformation Library is the library that deals with transforming between
 *      the camera, OpenCV and the DLP. This was formerly called CalibLib because all of the
 *      calibration functions are handled in this library.
 *
 *      The idea is Calibration Library can include both the Talk2Camera and Talk2DLP libraries.
 *
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

int LoadCalibFromFile(CalibData* Calib, char * filename);
