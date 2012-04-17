#include "ReadWriteFoo.h"


void creaMatrice( matrice *m, int row, int col )
{
    int i;

    scriviRighe(m, row);
    scriviColonne( m, col );

    /* Dynamic allocation of a matrix of (r,c) */
    m->mat = (float**)malloc(leggiRighe(m)*sizeof(float*));
     if( m->mat == NULL )
     {
        fprintf(stderr,"\n**ERRORE ALLOCAZIONE MEMORIA**");
        wait();
        exit(-1);
     }
    for ( i = 0; i < leggiRighe(m); i++ )
    {
        m->mat[i] = (float*)malloc( leggiColonne(m) * sizeof(float));
        if( m->mat[i] == NULL)
            printf("\n**ERRORE ALLOCAZIONE MEMORIA**");
    }

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

void scriviId( matrice *m, int id_num )
{
    m->id = id_num;

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
