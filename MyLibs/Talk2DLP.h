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
 * T2DLP.h
 *
 *  Created on: Jul 3, 2009
 *      Author: Andy
 */

#ifndef TALK2DLP_H_
#define TALK2DLP_H_

long T2DLP_on(); //returns the ID of the DMD
int T2DLP_off(long alpid); //takes an ID of the DMD
int T2DLP_SendFrame(unsigned char *image, long alpid);
unsigned char *SampleImages( unsigned long nSizeX, unsigned long nSizeY );


/*
 * Clear the DLP mirrors
 */
int T2DLP_clear(long myDLP);

#define	T2DLP_HAPPY	 	0
#define	T2DLP_SAD		-1


/*Hard Code in the dimensions.
 *  We are Using ALPB_DMDTYPE_XGA_055X
 *  Which is XGA .55 Type X
 *  1024 by 768 mirrors
 */
#define NSIZEX 1024
#define NSIZEY 768

#endif /* TALK2DLP_H_ */
