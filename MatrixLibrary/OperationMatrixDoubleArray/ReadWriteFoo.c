#include "ReadWriteFoo.h"

/*
    Function that receives the number of colomn and the number of row of the matrix,
    and create it asking to the user to fill it inserting each row.
*/

void creaMatrice( matrice *m, int row, int col )
{
    scriviRighe(m, row);
    scriviColonne( m, col );
}

/*
    Functions that returns
    the number of row of the matrix
    taking it from the field of the structure
*/
int leggiRighe( matrice *m )
{
  return m->righe;

}

/*
    Functions that returns
    the number of colomn of the matrix
    taking it from the field of the structure
*/

int leggiColonne( matrice *m )
{
  return m->colonne;

}

/*
    Function that correctly takes from the
    stdin the row's value inserted by the user
    and stores it into the colomn field of the
    structure m.

*/
void scriviRighe( matrice *m, int n_righe )
{


  m->righe = n_righe;
}

/*
    Function that correctly takes from the
    stdin the row's value inserted by the user
    and stores it into the colomn field of the
    structure m.

*/
void scriviColonne( matrice *m, int n_colonne )
{

  m->colonne = n_colonne;

}


/*
    Functions that returns a specific element
    stored in the i,j position of the considered
    matrix.
*/
float leggiElemento( matrice *m, int i, int j )
{
  return m->mat[i][j];

}

/*
    Functons that simply set in the i,j position
    of the matrix, a value specified as a parameter n
    of the function.
*/
void scriviElemento( matrice *m, int i, int j, float n )
{
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
    creaMatrice(m, row, col);

    for ( i = 0; i < row; i++ )
    {
        for ( j = 0; j < col; j++ )
        {
            fscanf(mat_file,"%f ", &x);
            scriviElemento( m, i, j, x);
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
void leggiMatriceDaFileBinario( FILE *mat_file, matrice *m )
{
	fread( m, sizeof(matrice), 1, mat_file);

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

	while( !feof(mat_file))
		leggiMatriceDaFileBinario(mat_file, &elenco[i++]);

	return i-1;
}
