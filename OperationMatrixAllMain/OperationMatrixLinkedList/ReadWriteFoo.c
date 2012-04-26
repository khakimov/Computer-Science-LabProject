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
