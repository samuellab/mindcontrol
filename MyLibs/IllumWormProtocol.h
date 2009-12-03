/*
 * IllumWormProtocol.h
 *
 *  Created on: Nov 11, 2009
 *      Author: Andy
 */

#ifndef ILLUMWORMPROTOCOL_H_
#define ILLUMWORMPROTOCOL_H_


typedef struct ProtocolStruct{
	CvSize GridSize;
	Char* ProtocolFilename;
	Char* ProtocolDescription;
	CvSeq Steps;
	CvMemStorage* memory;

}Protocol;











#endif /* ILLUMWORMPROTOCOL_H_ */
