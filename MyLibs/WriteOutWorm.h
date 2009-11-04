/*
 * WriteOutWorm.h
 *
 *  Created on: Nov 3, 2009
 *      Author: Andy
 */

#ifndef WRITEOUTWORM_H_
#define WRITEOUTWORM_H_


typedef struct SaveWormFrameStruct{
	/** Current Frame **/
	int FrameId;
	int CamFrameId;

	/** Frame to Frame Temporal Analysis**/
	int TemporalOn;
	int MaxLocationChange;
	int MaxPerimChange;

	/** Display Stuff**/
	int DispRate;
	int Display;

	/** Illumination Parameters **/
	int SegStart;
	int SegStop;

} SaveWormFrame;



#endif /* WRITEOUTWORM_H_ */
