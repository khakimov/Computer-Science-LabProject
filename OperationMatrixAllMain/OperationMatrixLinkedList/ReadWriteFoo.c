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
    Function that gets from the stdin the
    single element that will be put into
    a specific position of the matrix
    ( contained in the structure as a field )
    represented by the i,j integer variable.

*/
float scriviValore( int i, int j )
{
  int res;
  float x;

     do
     {
         printf("m[%d][%d] = ", i, j);
         res = scanf("%f", &x);
         scanf("%*[^\n]");
         if ( res == 0 || x > FLT_MAX )
            printf("Valore inserito non corretto!!Sono ammessi solo valori reali!\n");

     }while( res == 0 || x > FLT_MAX );

    return x;
}

/*
    Functions that returns a specific element
    stored in the i,j position of the considered
    matrix.
*/
float leggiElemento( matrice *m, int i, int j )
{
  List* curr;
  int cont = 0;
/*
  if ( !m->mat )
  {
    m->mat = allocMatrice();
    m->mat->val = 0;
    m->mat->next = NULL;
    curr = m->mat;
  }
  else
  { */
    curr = m->mat;

    while ( cont < val_access(i, leggiColonne(m), j) )
    {
      curr = curr->next;
      cont++;
    }

 /* }
    Localized correct value when we exit from the while statement
    Take it and take away */

    return curr->val;
}

/*
    Functons that simply set in the i,j position
    of the matrix, a value specified as a parameter n
    of the function.
*/
void scriviElemento( matrice *m, float n )
{
    List* curr = m->mat;

    if ( !m->mat )
    {

        m->mat = (List*)malloc(sizeof(List));
        if(!m->mat) printf("\nALLOCATION MEMORY ERROR in scriviElemento!");

        m-> mat -> val = n;
        m-> mat -> next = NULL;
    }
    else
    {

        while(curr->next)
            curr = curr->next;

        curr->next = (List*)malloc(sizeof(List));
        curr = curr->next;

        if(!curr) printf("\nALLOCATION MEMORY ERROR in scriviElemento!");

        curr->val = n;
        curr->next = NULL;
    }


}

void scriviId( matrice *m, int num_id )
{
    m->id = num_id;

}

int leggiId( matrice *m )
{
    return m->id;

}

void creaMatrice( matrice *m, int row, int col )
{
    scriviRighe(m,row);
    scriviColonne(m,col);

    m->mat = NULL;

}
