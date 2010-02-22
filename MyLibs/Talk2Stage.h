/*
 * Talk2Stage.h
 *
 *  Created on: Feb 22, 2010
 *      Author: Andy
 */

#ifndef TALK2STAGE_H_
#define TALK2STAGE_H_

#include <windows.h>

/*
 * Initializes the USB stage;
 */
HANDLE InitializeUsbStage();


/*
 * Set the velocity of the stage
 *
 */
int spinStage(HANDLE s, int xspeed,int yspeed);


int haltStage(HANDLE s);

int moveStageRel(HANDLE s, int xpos, int ypos);

/*
 * Set's the stage current location to be zero zero.
 */
int zeroStage(HANDLE s);

/*
 * Note this takes a really long time.
 */
int centerStage(HANDLE s);

/*
 *
 *  Given a number on the number pad, this steers the stage.
 *  1-9 is  direction.
 *  5 is halt.
 *
 */
void steerStageFromNumberPad(HANDLE s, int speed, int input);
#endif /* TALK2STAGE_H_ */
