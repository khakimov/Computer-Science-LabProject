#include "OpMatrix.h"
#include "ReadWriteFoo.h"

/* Prints to video the values present in the matrix passed as a parameter */
void stampaMatrice( matrice *m )
{
  int i,j;


  if ( leggiRighe(m) == 0 )
     printf("Matrice non inizializzata!!\n");
  else
  {
      printf("\t ----- Matrice %d ---- \n", leggiId(m));
      for(i = 0; i < leggiRighe(m); printf("\n"),i++)
        for(j=0;j < leggiColonne(m);j++)
            printf("%15.3f ",leggiElemento(m, i, j));
  }

}

/*
    Function which make the transposition operation of a
    matrix passed as a parameter.
    It returns a double pointer which points to the current location
    in which the new trasposed matrix will be.
*/
matrice* trasposta( matrice *mt, matrice *m )
{
    int i, j;

   for ( i=0; i < leggiRighe(mt); i++ )
    for ( j = 0; j < leggiColonne(mt); j++ )
        scriviElemento(mt,leggiElemento(m,j,i));



  return mt;

}


matrice* somma( matrice *sum_mat, matrice *m, matrice *n )
{
    int i, j;

    for ( i = 0; i < leggiRighe(sum_mat); i++ )
        for ( j = 0; j < leggiColonne(sum_mat); j++ )
            scriviElemento( sum_mat, leggiElemento(m, i, j) + leggiElemento(n, i, j));


    return sum_mat;
}

matrice* scalare( matrice *ma, matrice *m, float a )
{
    int i, j;

    for( i = 0; i < leggiRighe(ma); i++ )
        for ( j = 0; j < leggiColonne(ma); j++ )
            scriviElemento(ma, a * leggiElemento(m,i,j));

    return ma;
}

matrice* differenza( matrice *diff_mat, matrice *m, matrice *n )
{
    int i, j;

    for( i=0; i < leggiRighe(diff_mat);i++)
       for(j=0; j < leggiColonne(diff_mat); j++)
           scriviElemento( diff_mat,leggiElemento(m,i,j)- leggiElemento(n, i,j));


    return diff_mat;

}

/*
    Function : prodvetMatrice()
    parameters :
        matrice *elenco, Pointer to struct matrice which represents a list of matrix
        int cont, integer variable which holds the current number of matrix saved into the list
    Returns:
        The resulting matrix which represents the vectorial product.


*/

matrice* prodotto( matrice *mp, matrice *m, matrice *n )
{
    int i, j, k;
    int tot = 0;

    for(i=0;i< leggiRighe(mp);i++)
       for(j=0;j< leggiColonne(mp);j++)
       {
         for(k=0;k< leggiColonne(m);k++)
            tot += leggiElemento(m,i,k)* leggiElemento(n,k,j);
         scriviElemento( mp, tot );
       }


    return mp;
}

