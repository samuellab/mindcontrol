/*
 * calibrateStage.c
 *
 *  Created on: Feb 22, 2010
 *      Author: Andy
 */

#include <windows.h>
#include <stdio.h>
#include "MyLibs/Talk2Stage.h"

int main() {
	HANDLE hUSB= InitializeUsbStage();
	if (hUSB==NULL) {
		printf("No stage found. Goodbye!\n");
		return 0;
	}


	int input;


	printf("Uses number pad arrow keys. Hit <enter> to invoke.\n Hit 5 <enter> to stop. Hit 0 <enter> to quit.\n");

	int speed=500;

	while(1){
	  scanf("%d",&input);
	  if (input <10 && input >0){

		  steerStageFromNumberPad(hUSB,speed,input);
	  } else {
		  break;
	  }
	}
		Sleep(1000);
		printf("GoodBye!");
}
