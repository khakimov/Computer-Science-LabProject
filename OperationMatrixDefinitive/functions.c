#include "header.h"
#include "ReadWriteFoo.h"

/* Useful funtion used to get the option choosen by the user from the command line and print the menu */
int intestazione()
{
   int scelta;
   int ris;


   do
   {
     /*
       Macro preprocessor used in order to
       check the system on which the program was executed
     */
     #if defined _WIN32
            system("cls");
     #elif  defined __unix__
            system("clear");
     #endif
     printf("----------OPERAZIONI MATRICI----------\nPowered by A. Suglia & N. Chekalin\n\n%s%s%s%s%s%s%s%s%s%s%s\n",
          "-----------------MENU'----------------\n\n",
          "1 - Inserire Matrice \n",
          "2 - Stampa Matrice \n",
          "3 - Sovrascrivi\n",
          "4 - Matrice Trasposta\n",
          "5 - Somma Matrici\n",
          "6 - Differenza Matrici\n",
          "7 - Prodotto Scalare Matrici\n",
          "8 - Prodotto Vettoriale Matrici\n",
          "9 - Inserisci nuove matrici\n",
          "0 - Esci\n\n");
     printf("Scelta operazione -> ");
     ris=scanf("%d",&scelta);
     cleanBuffer();

   }while(ris==0);


   return scelta;
}

/*
    Functiont that takes as its parameter a pointer
    to a structure of type "matrice", in which there is
    a field that represents a bidimensional array which need
    to be dinamically allocated.

*/
void allocMatrix( matrice *m )
{

    int i;

    /* Dynamic allocation of a matrix of (r,c) */
    m->mat = (float**)malloc(leggiRighe(*m)*sizeof(float*));
     if( m->mat == NULL)
       fprintf(stderr,"\n**Memoria Esaurita**");

    for ( i = 0; i < leggiRighe(*m); i++ )
    {
        m->mat[i] = (float*)malloc( leggiColonne(*m) * sizeof(float));
        if( m->mat[i] == NULL)
            printf("\n**Memoria Esaurita**");
    }


}

/*
    Function that takes as parameters the
    pointer to a structure of type "matrice"
    and an integer variable which represents
    the number of matrix actually contained into the list
    of matrix.
    It returns a pointer to the new resized list of matrix.

*/
matrice *reallocMat( matrice *m, int n )
{
  matrice *new_mat;

  /* Create a new memory location for the next matrix that was declared*/
  new_mat = (matrice*)realloc( m, (n+1) * sizeof(matrice));
  if ( new_mat == NULL )
  {
      fprintf(stderr,"ERRORE ALLOCAZIONE MEMORIA!\n");
      wait();
      exit(-1);
  }

  return new_mat;
}

/*
    Function that simply initializes
    the array of matrix returning a pointer
    to this array properly dinamically allocated
    using malloc() function.

*/
matrice* initElenco( void )
{
  matrice *arr;

  arr = (matrice*)malloc( 1 * sizeof(matrice));
  if ( arr == NULL )
  {
      fprintf(stderr,"Errore allocazione dinamica della memoria!\n");
      wait();
      exit(-1);
  }

  return arr;

}

void overwriteMatrix( matrice *m, int n )
{
     int matchoice;



}


/* Deallocate memory dinamically from the specific double pointer passed to the function */
void free_matrix( matrice m )
{
    int i;

    for ( i = 0; i < leggiRighe(m); i++ )
        free(m.mat[i]);
    free(m.mat);


}

int checkDim( matrice m, matrice n )
{
    return ( leggiRighe(m) == leggiRighe(n) && leggiColonne(m) == leggiColonne(n) ) ? 1 : 0;
}

int checkRowCol( matrice m )
{
    return ( ( leggiRighe(m) != 0 ) && ( leggiColonne(m) != 0 ) ) ? 1 : 0;
}

void initDim( matrice *dest, matrice src )
{
  dest->righe = src.righe;
  dest->colonne = src.colonne;

}
/* Useful function used in order to remove some useless characters present in the buffer */
void cleanBuffer()
{
    while ( getchar() != '\n');
}

/*
    Function that makes some specific control on a float value inserted,
    and only if it is correct, it stores it in a specific location pointed by f.
*/
void salvaValore( float *f )
{
    int res;

    do
    {
        res = scanf("%f", f);
        if ( res == 0 )
        {
            fprintf(stderr,"ERRORE: valore errato!!\n%s",
                   "Reinserisci il valore : ");
        }
        scanf("%*[^\n]");
    }while ( res == 0);


}


/*
    Function that receives the number of colomn and the number of row of the matrix,
    and create it asking to the user to fill it inserting each row.
*/
matrice inserisciMatrice( int id )
{
    matrice array;
    int i,j;

    scriviRighe(&array);
    scriviColonne(&array);

    array.id = id;


    cleanBuffer();

    allocMatrix(&array);

    printf("Inserisci elementi della matrice\n");
    for ( i = 0; i < leggiRighe(array); i++ )
        for ( j = 0; j < leggiColonne(array); j++ )
            scriviValore(&array, i, j);

    return array;
}

/* Prints to video the values present in the matrix passed as a parameter */
void stampaMatrice( matrice mat, int id )
{
  int i,j;


  if ( mat.righe == 0 )
     printf("Matrice non inizializzata!!\n");
  else
  {
      printf(" ----- Matrice %d ---- \n", id);
      for(i = 0; i < leggiRighe(mat); printf("\n"),i++)
        for(j=0;j < leggiColonne(mat);j++)
            printf("%15.3f ",leggiValore(mat, i, j));
  }

}

/*
    Function which make the transposition operation of a
    matrix passed as a parameter.
    It returns a double pointer which points to the current location
    in which the new trasposed matrix will be.
*/
matrice trasposta( matrice mat )
{
  int i,j;
  matrice mat_t;

  mat_t.righe = leggiColonne(mat);
  mat_t.colonne = leggiRighe(mat);

  allocMatrix(&mat_t);

  for ( i=0; i < leggiRighe(mat_t); i++ )
    for ( j = 0; j < leggiRighe(mat_t); j++ )
        scriviElemento(&mat_t,i,j,leggiValore(mat,j,i));



  return mat_t;

}


matrice sommaMatrici( matrice m, matrice n )
{
    matrice mpn;
    int i, j;

    initDim( &mpn, m);

    allocMatrix(&mpn);

    for ( i = 0; i < leggiRighe(mpn); i++ )
        for ( j = 0; j < leggiColonne(mpn); j++ )
            scriviElemento( &mpn,i, j, leggiValore(m, i, j) + leggiValore(n, i, j));


    return mpn;
}

matrice prodScalareMatrice( matrice m )
{
    matrice ma;
    float a;
    int i, j;

    initDim( &ma, m);

    allocMatrix(&ma);

    printf("Inserisci valore scalare di tipo reale : ");
    salvaValore(&a);

    for( i = 0; i < leggiRighe(ma); i++ )
        for ( j = 0; j < leggiRighe(ma); j++ )
            scriviElemento(&ma,i,j, a * leggiValore(m,i,j));


    return ma;
}

matrice diffMatrice( matrice m, matrice n )
{
    matrice md;
    int i,j;

    initDim( &md, m);

    allocMatrix(&md);

    for( i=0; i < leggiRighe(md);i++)
       for(j=0; j < leggiColonne(md); j++)
           scriviElemento( &md, i, j, leggiValore(m,i,j)- leggiValore(n, i,j));


    return md;

}

matrice prodvetMatrice( matrice m, matrice n )
{
    matrice MpvN;
    int i,j,k;

    MpvN.righe = leggiRighe(m);
    MpvN.colonne = leggiColonne(n);

    allocMatrix(&MpvN);

    for(i=0;i< leggiRighe(MpvN);i++)
       for(j=0;j< leggiColonne(MpvN);j++)
          for(k=0;k< leggiColonne(m);k++)
            scriviElemento( &MpvN, i, j, leggiValore(MpvN,i,j) + leggiValore(m,i,k)* leggiValore(n,k,j) );



    return MpvN;
}

