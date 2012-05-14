/*
 * ErrorManager.c
 *
 *  Created on: 14/mag/2012
 *      Author: AlexZ
 */

#include "ErrorManager.h"

int mat_err;
const char *mat_err_list[] =
	{
		"The inserted matrix was not initialized\n",
		"The matrix's row number is incorrect\n"
		"The matrix's col number is incorrect\n",
		"The selected matrices are not equal, it's impossible this operation\n",
		"The selected matrices haven't the correct dimensions. THE FIRST MATRIX's COLUMNS MUST BE EQUAL TO THE SECOND MATRIX's ROW\n",
		"The position that you've specified could not be located in the matrix\n",
		"CORRECT.\n"

	};

void mat_error( char *str )
{
	int curr_error = mat_err;
	int pos;

	switch( curr_error )
	{
	case EMNI :
			pos = 0;
		break;
	case EMROW :
		pos = 1;
		break;
	case EMCOL:
		pos = 2;
		break;
	case EMATNEQ :
		pos = 3;
		break;
	case EMATPROD:
		pos = 4;
		break;
	case EMCOORD:
		pos = 5;
		break;
	case EMNOTF :
		pos  = 6;
		break;

	}

	/* Print on the standard error file stream the error found */
	fprintf(stdout, "ERROR >> %s %s\n", mat_err_list[pos], str);

	/* Replace the current error that was current managed to the standard value */


}

void set_error( int curr_err )
{
	mat_err = curr_err;

}

int get_curr_error( void )
{
	return mat_err;
}
