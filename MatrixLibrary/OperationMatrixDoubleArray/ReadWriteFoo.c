#include "ReadWriteFoo.h"

/*
    Function that receives the number of colomn and the number of row of the matrix,
    and create it asking to the user to fill it inserting each row.
*/

int creaMatrice( matrice *m, int row, int col )
{
    if ( ( row <= 0 || row > MAXR ) && ( col <= 0 || col > MAXC ) )
    	set_error(EMNI);
    else
    {

    	scriviRighe(m, row);
    	scriviColonne( m, col );
    }

    return ( get_curr_error() == EMNOTF ) ? 1 : 0;
}

/*
    Functions that returns
    the number of row of the matrix
    taking it from the field of the structure
*/
int leggiRighe( matrice *m )
{
  if ( m->righe <= 0 || m->righe > MAXR )
     set_error(EMNI);
  else
      return m->righe;


}

/*
    Functions that returns
    the number of colomn of the matrix
    taking it from the field of the structure
*/

int leggiColonne( matrice *m )
{
    if( m->colonne <= 0 || m->colonne > MAXC )
        set_error(EMNI);
    else
        return m->colonne;

}

/*
    Function that correctly takes from the
    stdin the row's value inserted by the user
    and stores it into the colomn field of the
    structure m.

*/
int scriviRighe( matrice *m, int n_righe )
{

	if ( n_righe <= 0 || n_righe > MAXR )
		set_error(EMROW);
	else
		m->righe = n_righe;

	return ( get_curr_error() == EMNOTF ) ? 1 : 0;
}

/*
    Function that correctly takes from the
    stdin the row's value inserted by the user
    and stores it into the colomn field of the
    structure m.

*/
int scriviColonne( matrice *m, int n_colonne )
{

	if ( n_colonne <= 0 || n_colonne > MAXC )
		set_error(EMCOL);
	else
		m->colonne = n_colonne;

	return ( get_curr_error() == EMNOTF ) ? 1 : 0;

}


/*
    Functions that returns a specific element
    stored in the i,j position of the considered
    matrix.
*/
float leggiElemento( matrice *m, int i, int j )
{
  if ( !matrixExist(m) )
	  set_error(EMNI);
  else
      if ( ( i < 0 || i > leggiRighe(m) ) || ( j < 0 || j > leggiColonne(m) ) )
    	  set_error(EMCOORD);
  else
       return m->mat[i][j];

}

/*
    Functons that simply set in the i,j position
    of the matrix, a value specified as a parameter n
    of the function.
*/
void scriviElemento( matrice *m, int i, int j, float n )
{
	if ( !matrixExist(m) )
		set_error(EMNI);

	else
      if ( ( i < 0 || i > leggiRighe(m) ) || ( j < 0 || j > leggiColonne(m) ) )
    	  set_error(EMCOORD);
      else
    	  m->mat[i][j] = n;


}

/*
 * 	Function : leggiMatriceDaFile()
 * 	@parameters :
 * 		- mat_file : pointer to the file( textual file ) from which will be read the matrix
 * 		- m : pointer to a matrix
 *
 *
 * */
void leggiMatriceDaFile( FILE *mat_file, matrice *m )
{
    int row, col;
    int i = 0, j = 0;
    float x;

    fscanf(mat_file,"%d %d\n", &row, &col );
    if ( !creaMatrice(m, row, col) )
    	set_error(EMFNR);
    else
    {

    	for ( i = 0; i < row; i++ )
    	{
    		for ( j = 0; j < col; j++ )
    		{
    			fscanf(mat_file,"%f ", &x);
    			scriviElemento( m, i, j, x);
    		}
    	}
    }

}

/*
 * 	Function : stampaMatriceSuFile()
 * 	@parameters :
 * 		- mat_file : pointer to the file( textual file ) in which will be written the matrix(m)
 * 		- m : pointer to a matrix
 *
 *
 * */
void stampaMatriceSuFile( FILE *mat_file, matrice *m )
{
    int i, j;

    fprintf(mat_file,"%d %d\n", leggiRighe(m), leggiColonne(m));
    for ( i = 0; i < leggiRighe(m); i++ )
        for ( j = 0; j < leggiColonne(m); j++ )
            fprintf(mat_file, "%f ", leggiElemento(m, i, j));

    fprintf(mat_file, "\n");

}

/*
 * 	Function : stampaMatriceSuFileBinario()
 * 	@parameters :
 * 		- mat_file : pointer to the file ( binary file ) in which will be written the matrix(m)
 * 		- m : pointer to a matrix
 *
 *
 * */

void stampaMatriceSuFileBinario( FILE *mat_file, matrice *m )
{

	fwrite( m, sizeof(matrice), 1, mat_file);


}


/*
 * 	Function : leggiMatriceDaFileBinario()
 * 	@parameters :
 * 		- mat_file : pointer to the file( binary file ) from which will be read the matrix
 * 		- m : pointer to a matrix
 *
 *
 * */
int leggiMatriceDaFileBinario( FILE *mat_file, matrice *m )
{
	if ( !fread( m, sizeof(matrice), 1, mat_file) )
		set_error(EMFNR);

	return ( get_curr_error() == EMNOTF ) ? 1 : 0;

}


/*
 * 	Function : leggiMatriciRisultato()
 * 	@parameters :
 * 		- mat_file : pointer to the file from which you will read the matrix
 * 		- elenco : array of matrix
 * 	@returns :
 * 		int - number of matrix that will be read from the mat_file
 *
 *
 * */
int leggiMatriciRisultato( FILE *mat_file, matrice elenco[] )
{
	int i = 0;

	while( !feof(mat_file) && get_curr_error() != EMFNR )
		if ( !leggiMatriceDaFileBinario(mat_file, &elenco[i++]) )
			set_error(EMFNR);

	return ( get_curr_error() == EMNOTF ) ? i-1 : -1;
}


/*
    Simple function used in order to check the correcteness of the dimension of the matrix
    that are involved into operation like the sum and the difference, in which the fundamental
    requirement is that the matrix MUST have the same dimensions.
*/
int checkDim( matrice *m, matrice *n )
{

    if ( leggiRighe(m) == leggiRighe(n) && leggiColonne(m) == leggiColonne(n) )
    	mat_err = EMNOTF;
    else
    	set_error(EMNEQ);

    return ( mat_err == EMNOTF ) ? 1 : 0;
}

/*
    Function that check if the m's colomns and the n'rows are equal
    in order to grant the possibility to make the vectorial product
    between the selected matrixs.

*/
int checkRowCol( matrice *m , matrice *n)
{
	if ( leggiColonne(m) == leggiRighe(n) )
	    	mat_err = EMNOTF;
	else
		set_error(EMPROD);

	return ( mat_err == EMNOTF ) ? 1 : 0;
}

int matrixExist( matrice *m )
{
	if ( ( leggiRighe(m) <= 0 || leggiRighe(m) > MAXR ) || (  leggiColonne(m) <= 0 || leggiColonne(m) > MAXC ) )
	   set_error(EMNI);
	else
		set_error(EMNOTF);

	return ( get_curr_error() == EMNOTF ) ? 1 : 0;

}
