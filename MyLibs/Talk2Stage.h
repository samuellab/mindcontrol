
/*
 * Copyright 2010 Andrew Leifer et al <leifer@fas.harvard.edu>
 * This file is part of MindControl.
 *
 * MindControl is free software: you can redistribute it and/or modify
 * it under the terms of the GNU  General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MindControl is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MindControl. If not, see <http://www.gnu.org/licenses/>.
 *
 * For the most up to date version of this software, see:
 * http://github.com/samuellab/mindcontrol
 *
 *
 *
 * NOTE: If you use any portion of this code in your research, kindly cite:
 * Leifer, A.M., Fang-Yen, C., Gershow, M., Alkema, M., and Samuel A. D.T.,
 * 	"Optogenetic manipulation of neural activity with high spatial resolution in
 *	freely moving Caenorhabditis elegans," Nature Methods, Submitted (2010).
 */

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
