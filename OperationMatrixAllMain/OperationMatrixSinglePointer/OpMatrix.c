#include "OpMatrix.h"
#include "ReadWriteFoo.h"

/*
    Function that receives the number of colomn and the number of row of the matrix,
    and create it asking to the user to fill it inserting each row.
*/

void creaMatrice( matrice *m, int row, int col )
{
    scriviRighe(m, row);
    scriviColonne( m, col );

    m->mat = (float*)malloc( leggiRighe(m) * leggiColonne(m) * sizeof(float));
    if ( !m->mat )
    {
        fprintf(stderr,"ERRORE ALLOCAZIONE DINAMICA DELLA MEMORIA!!\n");
        wait();
        exit(-1);
    }
}


/* Prints to video the values present in the matrix passed as a parameter */
void stampaMatrice( matrice *mat )
{
  int i,j;

  if ( leggiRighe(mat) == 0 )
     printf("Matrice non inizializzata!!\n");
  else
  {
      printf("\t ----- Matrice %d ---- \n", mat->id);
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
void trasposta( matrice *dest, matrice *src )
{
  int i,j;

  for ( i=0; i < leggiRighe(dest); i++ )
    for ( j = 0; j < leggiColonne(dest); j++ )
        scriviElemento(dest,i,j,leggiElemento(src,j,i));

}


void somma( matrice *dest, matrice *src1, matrice *src2)
{

    int i, j;

    for ( i = 0; i < leggiRighe(dest); i++ )
        for ( j = 0; j < leggiColonne(dest); j++ )
            scriviElemento( dest,i, j, leggiElemento(src1, i, j) + leggiElemento(src2, i, j));


}

void scalare( matrice *dest, matrice *src, float a )
{

    int i, j;

    for( i = 0; i < leggiRighe(dest); i++ )
        for ( j = 0; j < leggiColonne(dest); j++ )
            scriviElemento(dest,i,j, a * leggiElemento(src,i,j));


}

void differenza( matrice *dest, matrice *src1, matrice *src2 )
{
    int i,j;

    for( i=0; i < leggiRighe(dest);i++)
       for(j=0; j < leggiColonne(dest); j++)
           scriviElemento( dest, i, j, leggiElemento(src1,i,j)- leggiElemento(src2, i,j));

}

void prodotto( matrice *dest, matrice *src1, matrice *src2)
{

    int i,j,k;

    for(i=0;i< leggiRighe(dest);i++)
       for(j=0;j< leggiColonne(dest);j++)
          for(k=0;k< leggiColonne(src1);k++)
            scriviElemento( dest, i, j, leggiElemento(dest,i,j) + leggiElemento(src1,i,k)* leggiElemento(src2,k,j) );

}

