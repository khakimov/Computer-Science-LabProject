#include "OpMatrix.h"
#include "ReadWriteFoo.h"

/* Prints to video the values present in the matrix passed as a parameter */
void stampaMatrice( matrice *mat )
{
  int i,j;

  if ( leggiRighe(mat) == 0 )
     printf("Matrice non inizializzata!!\n");
  else
  {
      printf("\t ----- Matrice %d ---- \n", leggiId(mat));
      for(i = 0; i < leggiRighe(mat); printf("\n"),i++)
        for(j=0;j < leggiColonne(mat);j++)
            printf("%15.3f ",leggiElemento(mat, i, j));
  }

}

/*
    Function which make the transposition operation of a
    matrix passed as a parameter.
    It returns a double pointer which points to the current location
    in which the new trasposed matrix will be.
*/
void trasposta( matrice *mt, matrice *m )
{
  int i,j;

  for ( i=0; i < leggiRighe(mt); i++ )
    for ( j = 0; j < leggiColonne(mt); j++ )
        scriviElemento(mt,i,j,leggiElemento(m,j,i));

}


void somma( matrice *sum_mat, matrice *m, matrice *n)
{

    int i, j;

    for ( i = 0; i < leggiRighe(sum_mat); i++ )
        for ( j = 0; j < leggiColonne(sum_mat); j++ )
            scriviElemento( sum_mat,i, j, leggiElemento(m, i, j) + leggiElemento(n, i, j));


}

void scalare( matrice *ma, matrice *m, float a )
{

    int i, j;

    for( i = 0; i < leggiRighe(ma); i++ )
        for ( j = 0; j < leggiColonne(ma); j++ )
            scriviElemento(ma,i,j, a * leggiElemento(m,i,j));


}

void differenza( matrice *diff_mat, matrice *m, matrice *n )
{
    int i,j;

    for( i=0; i < leggiRighe(diff_mat);i++)
       for(j=0; j < leggiColonne(diff_mat); j++)
           scriviElemento( diff_mat, i, j, leggiElemento(m,i,j)- leggiElemento(n, i,j));

}

void prodotto( matrice *prod_mat, matrice *m, matrice *n)
{

    int i,j,k;

    for(i=0;i< leggiRighe(prod_mat);i++)
       for(j=0;j< leggiColonne(prod_mat);j++)
          for(k=0;k< leggiColonne(m);k++)
            scriviElemento( prod_mat, i, j, leggiElemento(prod_mat,i,j) + leggiElemento(m,i,k)* leggiElemento(n,k,j) );

}

