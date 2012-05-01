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

void leggiMatriceDaFile( FILE *mat_file, matrice *m )
{
    int row, col;
    int i = 0, j = 0;
    float x;
    static fpos_t current_position;



    if (  ( mat_file = fopen(MAT_FILENAME, "r") ) == NULL )
    {
        fprintf(stderr, "ERROR WHILE READING FROM FILE %s\n", MAT_FILENAME);
        exit(-1);

    }
    else
    {
        if ( current_position )
            fsetpos(mat_file, &current_position);

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

        fgetpos(mat_file, &current_position);

    }

    fclose(mat_file);
}

void stampaMatriceSuFile( FILE *mat_file, matrice *m )
{
    int i, j;

    if ( ( mat_file = fopen( MAT_FILENAME, "a")) == NULL )
    {
        fprintf(stderr,"ERROR WHILE OPENING FILE %s\n", MAT_FILENAME);
        exit(-1);

    }
    else
    {
        fprintf(mat_file,"%d %d\n", leggiRighe(m), leggiColonne(m));

        for ( i = 0; i < leggiRighe(m); i++ )
            for ( j = 0; j < leggiColonne(m); j++ )
                fprintf(mat_file, "%f ", leggiElemento(m, i, j));

        fprintf(mat_file, "\n");

    }

    fclose(mat_file);
}



