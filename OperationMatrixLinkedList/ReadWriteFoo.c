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
void scriviRighe( matrice *m )
{
     int res;
  do
  {
     printf("\nInserisci righe matrice: ");
     res=scanf("%d",&m->righe);
     scanf("%*[^\n]");
     if(res==0)
        fprintf(stderr,"\n**Assegnazione valore errata!**\n\n");
        else if( m->righe < 1 || m->righe > MAXR) fprintf(stderr,"\n**Il numero di righe e' errato (1< r < %d)**\n\n",MAXR);

  }while(res == 0 || ( m->righe < 1 || m->righe > MAXR));

  scanf("%*[^\n]");

}

/*
    Function that correctly takes from the
    stdin the row's value inserted by the user
    and stores it into the colomn field of the
    structure m.

*/
void scriviColonne( matrice *m )
{
  int res;

   do
  {
     printf("\nInserisci colonne matrice: ");
     res=scanf("%d",&m->colonne);
     scanf("%*[^\n]");
     if(res==0)
        fprintf(stderr,"\n**Assegnazione valore errata!**\n\n");
        else if( m->righe < 1 || m->colonne > MAXR) fprintf(stderr,"\n**Il numero di colonne e' errato (1< c < %d)**\n\n",MAXC);

  }while(res == 0 || ( m->colonne < 1 || m->colonne > MAXR));

  scanf("%*[^\n]");

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
float leggiValore( matrice *m, int i, int j )
{
  List* curr = NULL;
  int cont = 0;


  curr = m->mat;
  printf("STO LEGGENDO!!\n");

  while ( cont < val_access(i, leggiColonne(m), j ) )
    {
        curr = curr->next;
        cont++;
    }

    /* Localized correct value when we exit from the while statement */
    /* Take it and take away */

    return curr->val;
}

/*
    Functons that simply set in the i,j position
    of the matrix, a value specified as a parameter n
    of the function.
*/
void scriviElemento( matrice *m, int i, int j, float n )
{
    List* curr = NULL;

    if ( !(m->mat) )
    {
        m->mat = (List*)malloc(sizeof(List));
        if ( !m->mat )
            printf("ERROR OCCURED!!\n");
        else
        {
            m->mat->val = n;
            m->mat->next = NULL;
        }
    }
    else
    {
        curr = m->mat;

        while( curr )
            curr = curr->next;

        curr = (List *)malloc( sizeof(List ));

        curr->val = n;
        curr->next = NULL;
    }

}
