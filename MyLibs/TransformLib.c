
//OpenCV Headers
#include <cxcore.h>
#include <highgui.h>
#include <cv.h>

#include <stdio.h>


#include "TransformLib.h"


/*
 * Create and allocate memory for the CalibData structure
 *
 * Currently SizeOfCCD is stored but not really used
 *
 */
CalibData* CreateCalibData( CvSize SizeOfDLP, CvSize SizeOfCCD){

	printf("Inside CreateCalibData()\nSizeOfDLP.height =%d,SizeOfDLP.width=%d\n",SizeOfDLP.height ,SizeOfDLP.width);
	CalibData* Calib=(CalibData*) malloc(sizeof(CalibData));
	Calib->CCD2DLPLookUp = (int *) malloc(2 * SizeOfDLP.height * SizeOfDLP.width* sizeof(int));
	Calib->SizeOfCCD=SizeOfCCD;
	Calib->SizeOfDLP=SizeOfDLP;
	return Calib;
}

/*
 * Deallocate memory for CalibData object
 */
void DestroyCalibData(CalibData* Calib){
	free(Calib->CCD2DLPLookUp);
	free(Calib);

}





/*
 * Read In Calibration Frome File
 *
 * Returns 1 if open failed.
 * Returns -1 if open succesfully but read fails.
 */

int LoadCalibFromFile(CalibData* Calib, char * filename){
	FILE *fp;
	int result;
	int FLAG=0;
	/*************** Read Calibration from File ****************/

	if ((fp = fopen(filename, "rb")) == NULL) {
		printf("Cannot open file.\n");
		FLAG=1;
	}
	result = 0;
	if (FLAG==0) result = fread(Calib->CCD2DLPLookUp, sizeof(int) * 2 * Calib->SizeOfDLP.height * Calib->SizeOfDLP.width , 1, fp);
	if (result != 1) {
		printf("Read error!\n");
	} else{
		printf("Read was successful.\n");
	}
	if (FLAG==0) fclose(fp);
	if (result ==0) FLAG=-1;
	return FLAG;
}
