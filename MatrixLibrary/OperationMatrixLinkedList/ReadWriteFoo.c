#include "ReadWriteFoo.h"


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
void scriviRighe( matrice *m, int row )
{
    m->righe = row;

}

/*
    Function that correctly takes from the
    stdin the row's value inserted by the user
    and stores it into the colomn field of the
    structure m.

*/
void scriviColonne( matrice *m, int col )
{
    m->colonne = col;
}


/*
    Functions that returns a specific element
    stored in the i,j position of the considered
    matrix.
*/
float leggiElemento( matrice *m, int i, int j )
{
      int pos = ( i * leggiColonne(m) + j );
      List *node = getNode(m->mat, pos);

      return node->val;

}

/*
    Functons that simply set in the i,j position
    of the matrix, a value specified as a parameter n
    of the function.
*/
void scriviElemento( matrice *m, int i, int j, float n )
{
     m->mat = setTail( m->mat, n);
}

void creaMatrice( matrice *m, int row, int col )
{
    scriviRighe(m,row);
    scriviColonne(m,col);

    m->mat = SetNull();

}
List *nextNode (List *node)
{
     return node->next;
}
List* SetNull( void )
{
    return NULL;
}
int isSet(List *node)
{
    return ( node ) ? 1 : 0;
}

List * getNode( List *list, int pos )
{

   if ( isSet(list) && pos == 0 )
      return list;
   else
      return getNode(nextNode(list),pos-1);


}

List *setTail( List *list, float n )
{
     List* curr;

     if ( !isSet( list ) )
     {
           curr = (List*)malloc( sizeof(List));
           if( !isSet(curr) )
           {
                fprintf(stderr, "ERROR ALLOCATION OF MEMORY!!\n");
                exit(-1);
           }
           curr->val = n;
           curr->next = SetNull();
           return curr;

     }
     else
     {
         list->next = setTail( nextNode(list), n );
         return list;

     }

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
