/*
 * Copyright 2011 Andrew Leifer <leifer@fas.harvard.edu>
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
 * Leifer, A.M., Fang-Yen, C., Gershow, M., Alkema, M. J., and Samuel A. D.T.,
 * 	"Optogenetic manipulation of neural activity  in freely moving
 *   Caenorhabditis elegans," Nature Methods, in press, (2011).
 */


/*
 * Talk2Laser.h
 *
 *  Created on: Jan 5, 2011
 *      Author: andy
 *
 *      This library allows the MindControl software to get information about the state of the lasers.
 *      There are functions to get the power levels of the blue and green laser, and to
 *      determine which lasers are on.
 *
 *      Note that this header library abstracts away how the information is obtained.
 *      At the moment, the plan is for the C code to talk to Labview code that controls the laser.
 *      Later on this could change.
 *
 */

#ifndef TALK2LASER_H_
#define TALK2LASER_H_



/*
 * Is the software available to control the laser?
 * (Under the current implementation, the laser software runs
 * in Labview, so this function checks to see if that software is running)
 *
 */
int IsLaserSoftwareAvailable()



/*
 *  Find out what the current laser power is for the blue laser.
 *  Note that this is in arbitrary units. A calibration curve is required.
 *
 */
int GetBlueLaserPower();

/*
 *  Find out what the current laser power is for the green laser.
 *  Note that this is in arbitrary units. A calibration curve is required.
 *
 */
int GetGreenLaserPower();



#endif /* TALK2LASER_H_ */
