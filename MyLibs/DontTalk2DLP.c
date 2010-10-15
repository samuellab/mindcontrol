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
 * DontTalk2DLP.c
 *
 *  Created on: Dec 17, 2009
 *      Author: Andy
 */
#include <assert.h>
#include <stdio.h>
#include <Talk2DLP.h>

/**
 *
 * This library is a bit of a hack.
 *
 * The idea is that sometimes we want to compile libraries like experiment.c
 * that access hardware specific functionality such as functions in:
 * Talk2DLP.c
 *
 * Anyway. The point is that I would like to be able to occasionally include libraries
 * that call functions in these libraries, even though I don't actually
 * ever use these functions at runtime.
 *
 * So to avoid linker errors I am writing this DontTalk2DLP.c
 * which basically redefines all of the hardware specific functions.
 */




void T2DLP_errormsg(){
	printf("\n\nERROR.\n");
	printf("It appears as though a DLP-specific function was called.\n");
	printf("This software was compiled without DLP-specific libraries.\n");
	printf("Try running the software in DLP simulation mode with the -s switch.\n\n");
}


long T2DLP_on(){
	T2DLP_errormsg();
	assert(0);

	return 0;
}
int T2DLP_off(long alpid)
{
	T2DLP_errormsg();
	assert(0);
	return 0;
}//takes an ID of the DMD

int T2DLP_SendFrame(unsigned char *image, long alpid){
	T2DLP_errormsg();
	assert(0);
	return 0;
}

unsigned char *SampleImages( unsigned long nSizeX, unsigned long nSizeY ){
	T2DLP_errormsg();
	assert(0);
	return NULL;
}


/*
 * Clear the DLP mirrors
 */
int T2DLP_clear(long myDLP){
	T2DLP_errormsg();
	assert(0);
	return 0;
}
