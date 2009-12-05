//Standard C headers
#include <stdio.h>
#include <ctime>
#include <time.h>
#include <conio.h>
#include <math.h>

//C++ header
#include <iostream>
#include <limits>

using namespace std;

//OpenCV Headers
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>



//Andy's Headers
#include "MyLibs/IllumWormProtocol.h"
#include "MyLibs/version.h"

int main(){

	printf("Hello World\n");

	Protocol* myP=CreateProtocolObject();

	myP->Description="A test protocol.";
	myP->Filename="protocol.yaml";
	myP->GridSize=cvSize(2,99);
	/** Create the Steps Object and Load it into the Protocol **/
	myP->Steps=CreateStepsObject(myP->memory);


	/** Create an Illumination Montage**/
	CvSeq* FirstIllum=CreateIlluminationMontage(myP->memory);
	CvSeq* SecondIllum=CreateIlluminationMontage(myP->memory);
	CvSeq* ThirdIllum=CreateIlluminationMontage(myP->memory);


	/** Create Some Polygons **/
	WormPolygon* Head = CreateWormPolygon(myP->memory,myP->GridSize);
	WormPolygon* Left = CreateWormPolygon(myP->memory,myP->GridSize);
	WormPolygon* Right = CreateWormPolygon(myP->memory,myP->GridSize);
	WormPolygon* Tail = CreateWormPolygon(myP->memory,myP->GridSize);

	//(length along centerline,radius from centerline)
	cvSeqPush(Head->Points,&cvPoint(0,0));
	cvSeqPush(Head->Points,&cvPoint(2,0));
	cvSeqPush(Head->Points,&cvPoint(2,20));
	cvSeqPush(Head->Points,&cvPoint(0,20));

	cvSeqPush(Left->Points,&cvPoint(0,30));
	cvSeqPush(Left->Points,&cvPoint(1,30));
	cvSeqPush(Left->Points,&cvPoint(1,70));
	cvSeqPush(Left->Points,&cvPoint(0,70));

	cvSeqPush(Right->Points,&cvPoint(1,30));
	cvSeqPush(Right->Points,&cvPoint(2,30));
	cvSeqPush(Right->Points,&cvPoint(2,70));
	cvSeqPush(Right->Points,&cvPoint(1,70));

	cvSeqPush(Tail->Points,&cvPoint(0,80));
	cvSeqPush(Tail->Points,&cvPoint(1,80));
	cvSeqPush(Tail->Points,&cvPoint(1,99));
	cvSeqPush(Tail->Points,&cvPoint(0,99));


	/** Let's load up the illumination montages with polygons**/
//	cvSeqPush(FirstIllum,&Head);
	cvSeqPush(FirstIllum,&Tail);
	cvSeqPush(FirstIllum,&Left);
	cvSeqPush(FirstIllum,&Right);

	printf("FirstIllum->total=%d\n",FirstIllum->total);

	cvSeqPush(SecondIllum,&Head);
	cvSeqPush(SecondIllum,&Right);


	cvSeqPush(ThirdIllum,&Tail);
	cvSeqPush(ThirdIllum,&Left);

	/** Let's Load the montages into a series of steps **/
	cvSeqPush(myP->Steps,&FirstIllum);
	cvSeqPush(myP->Steps,&SecondIllum);
	cvSeqPush(myP->Steps,&ThirdIllum);

	WriteProtocolToYAML(myP);


	return 0;
}


