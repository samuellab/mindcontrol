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
 * version.h
 *
 *  Created on: Nov 23, 2009
 *      Author: Andy
 */


/*
 * When I complie the MindControl code by invoking make,
 * make will auto generate the corresponding version.c file to include
 * the most recent Git Version control hash and timestamp.
 *
 * It does this by calling git and awk from within make. The file here is simply a header to let the rest of
 * the software know about those variables.
 *
 * In this way, the software can write out its git version information when it outputs data.
 * This turns out to be extremely useful.
 *
 */

#ifndef VERSION_H_
#define VERSION_H_

extern const char * build_git_time;
extern const char * build_git_sha;


#endif /* VERSION_H_ */
