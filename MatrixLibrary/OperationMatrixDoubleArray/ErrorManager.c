
#include "ErrorManager.h"

int mat_err;
const char *mat_err_list[] =
	{
		"The inserted matrix was not initialized\n",
		"The first parameter matrix is not initialized\n",
		"The second parameter matrix is not initialized\n",
		"The matrix's row number is incorrect\n",
		"The matrix's col number is incorrect\n",
		"The selected matrices are not equal, it's impossible to do SUM operation\n",
		"The selected matrices are not equal, it's impossible to do DIFFERENCE operation\n",
		"The selected matrix has not the correct dimension in order to do the TRANSPOSITION\n",
		"The selected matrices haven't the correct dimensions. THE FIRST MATRIX's COLUMNS MUST BE EQUAL TO THE SECOND MATRIX's ROW to do the product\n",
		"The position that you've specified could not be located in the matrix\n",
		"Error in reading from file\n",
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
    case EMPAR1 :
         pos = 1;
    break;
    case EMPAR2 :
         pos = 2;
    break;
	case EMROW :
		pos = 3;
		break;
	case EMCOL:
		pos = 4;
		break;
	case EMSUM :
		pos = 5;
		break;
	case EMDIFF :
			pos = 6;
			break;
	case EMTRASP :
			pos = 7;
		break;
	case EMPROD:
		pos = 8;
		break;
	case EMCOORD:
		pos = 9;
		break;
	case EMFNR :
			pos  = 10;
		break;

	case EMNOTF :
		pos  = 11;
		break;

	}

	/* Print on the standard error file stream the error found */
	if ( !str )
	   str = "";
    fprintf(stdout, "ERROR >> %s %s\n", mat_err_list[pos], str);

	/* Replace the current error that was current managed to the standard value */
    mat_err = EMNOTF;

}

void set_error( int curr_err )
{
	mat_err = curr_err;

}

int get_curr_error( void )
{
	return mat_err;
}
