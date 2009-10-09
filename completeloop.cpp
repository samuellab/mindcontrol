/* completeloop.cpp
 * This is a file that tests the complete loop, it
 * formerly display.cpp
 * Reads in video from a file or video from a USB camera.
 * Conducts image processing.
 * Displays result on screen.
 * Hopefully soon it will also send to DLP.
 * \
 *  Created on: Jun 22, 2009
 *      Author: Andy
 */

#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include "MyLibs/Talk2DLP.h"
#include "MyLibs/AndysOpenCVLib.h"
/*extern "C" {
   // Get declaration for f(int i, char c, float x)
   #include "../AndysOpenCVLib/AndysOpenCVLib.h"
 }*/

#define ONSCREEN 1

int			g_slider_position	=0;
CvCapture*	g_capture			=NULL;



/*
 * This function takes an integer describing the position of the Trackbar and then sets the movie to that positoin.
 */
void onTrackbarSlide(int pos) {
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}



/**
 * takes a pointer to two, similarly formatted IplImages and performs arbitrary image processing
 *
 */
int   ImageProcess(IplImage* image, IplImage* dest){
	//cvSmooth( image, dest, CV_GAUSSIAN, 5, 5);
	int ThreshValue=75;
	cvThreshold( image, dest, ThreshValue,
	                  128, CV_THRESH_BINARY);

	return 0;
}





int main( int argc, char** argv ) {
	printf("Using static linking now.");
	//turn on the DLP
	long myalpid;
	myalpid=T2DLP_on(); //Turn the DLP on



    //Timing tools for framerate
	clock_t start,finish;
	double time; //timer for computing frames per second
	int fcounter; //frame counter for computing frames per second

	//Timing tools for
	clock_t startconversion, stopconversion;
	double avgconversiontime;
	avgconversiontime=0;
	int loopcounter;


	//Create our windows.

	cvNamedWindow( "Example3", CV_WINDOW_AUTOSIZE );
	cvNamedWindow( "Example3-out", CV_WINDOW_AUTOSIZE );


	bool LIVEFLAG=0;
	if( argc==1) {
		g_capture=cvCreateCameraCapture(0);
		LIVEFLAG=1;
	}else{
	g_capture = cvCreateFileCapture( argv[1] ); // Capture the movie
		LIVEFLAG=0; //No camera
		// Let's find the total number of frames and setup the trackbar
		int frames = (int) cvGetCaptureProperty( g_capture, CV_CAP_PROP_FRAME_COUNT); //find the number of frames
		if( frames != 0){
		cvCreateTrackbar(
				"Position",
				"Example3",
				&g_slider_position,frames,
				onTrackbarSlide
				);
		}
	}

	//Initilize memory for the various images.
	IplImage* frame; //The frame from the camera
	frame=cvCreateImage(  //Create a three channel image
			cvSize(NSIZEX, NSIZEY),
			IPL_DEPTH_8U,
			3
			);

	IplImage* dest; // The output of the image processing
	dest=cvCreateImage(  //Create a triple channel image
				cvSize(NSIZEX, NSIZEY),
				IPL_DEPTH_8U,
				3
				);
	IplImage* singlechannelimage; //intermediary to be converted to char
	singlechannelimage=cvCreateImage(  //Create a single channel image
			cvSize(NSIZEX, NSIZEY),
			IPL_DEPTH_8U,
			1
			);
	unsigned char *image2DLP;//the actual image sent to the DLP


	// Prepare our Counters
	fcounter=0; //set fcounter to zero
	loopcounter=0; //counts the total number of frames (Does not get reset)
	start = clock(); //Start clock timer


	while(1){
		fcounter++;
		loopcounter++;

		printf(".");
		frame=cvQueryFrame( g_capture );
		if (LIVEFLAG==0){
		//Andy's code to query the location in frames
		int currentposition;
		currentposition= (int) cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES);
		cvSetTrackbarPos( "Position", "Example3", currentposition);
		//End andy's code to query frame location
		}

		if( !frame ) break;
		printf("o");

		//Show the first image
		if(ONSCREEN){
		cvShowImage( "Example3", frame );
		}


		//Do image processing
		ImageProcess(frame,dest);


		cvConvertImage( //Convert to single channel image of the correct size
				dest,
				singlechannelimage,
				CV_CVTIMG_FLIP //This Flips the image. Its useful when the projector is upside down. Set this to zero for right-side up.
				);
		if(ONSCREEN){
			cvShowImage( "Example3-out",singlechannelimage ); //display the image
		}


		// Super ghetto For loop to get each point and put it in an unsigned character array
		startconversion=clock(); //start the conversion timer

		copyIplImageToCharArray(singlechannelimage, &image2DLP);



		stopconversion=clock();
		//Calculate a running average
		avgconversiontime=(avgconversiontime*(double(loopcounter)-1)+(double(stopconversion)-double(startconversion))/CLOCKS_PER_SEC)/double(loopcounter);
		if (loopcounter%50==0){
			printf("\n\n%f seconds per conversion on average.\n", avgconversiontime);
		}


		//ACtually send the character array to the dLP.
		int ret;
		ret= T2DLP_SendFrame( (unsigned char *) image2DLP,myalpid);



		//Wait for the user to hit escape key
		char c= cvWaitKey(2); // Waiting 2ms


		//finish clock timer
		finish = clock();
		time = (double(finish)-double(start))/CLOCKS_PER_SEC;
		if (  time >= 1.0){
			printf("%f fps\n", fcounter/time);
			start=clock();
			fcounter=0;
		}

		if( c==27 ) break;
	}


	printf("\nreleasing..");
	//Release the second image
	cvReleaseImage( &dest);
	cvReleaseImage(&singlechannelimage);
	cvReleaseCapture( &g_capture );
	cvDestroyWindow( "Example3" );

	/////////////TURN THE DLP OFF!!
	return T2DLP_off(myalpid);
	////////////
	return 0;
}
