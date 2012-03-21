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
     printf("----------OPERAZIONI MATRICI----------\nPowered by A. Suglia & N. Chekalin\n\n%s%s%s%s%s%s%s%s%s%s\n",
          "-----------------MENU'----------------\n\n",
          "1 - Inserire Matrice \n",
          "2 - Stampa Matrice \n",
          "3 - Sovrascrivi\n",
          "4 - Matrice Trasposta\n",
          "5 - Somma Matrici\n",
          "6 - Differenza Matrici\n",
          "7 - Prodotto Scalare Matrici\n",
          "8 - Prodotto Vettoriale Matrici\n",
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

int checkRowCol( matrice m , matrice n)
{
    return ( leggiColonne(m) == leggiRighe(n) ) ? 1 : 0;
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
    for ( j = 0; j < leggiColonne(mat_t); j++ )
        scriviElemento(&mat_t,i,j,leggiValore(mat,j,i));



  return mat_t;

}


matrice sommaMatrici( matrice *elenco, int cont)
{
    matrice mpn;
    int i, j;
    int scelta1,scelta2;

    controllaDati( elenco, cont, 'S' , &scelta1, &scelta2);
    initDim( &mpn, elenco[scelta1]);
    allocMatrix(&mpn);

    for ( i = 0; i < leggiRighe(mpn); i++ )
        for ( j = 0; j < leggiColonne(mpn); j++ )
            scriviElemento( &mpn,i, j, leggiValore(elenco[scelta1], i, j) + leggiValore(elenco[scelta2], i, j));


    return mpn;
}

matrice prodScalareMatrice( matrice *m, int cont )
{
    matrice ma;
    float a;
    int i, j;
    int scelta;
    
    do
     {
          printf("Inserisci l'ID della matrice sulla quale operare: ");
          scelta = leggiIntero();
          if(scelta < 0 || scelta >= cont)
             printf("Matrice non esistente!\n");
             
     }while( scelta < 0 || scelta >= cont );
     
    initDim( &ma, m[scelta]);

    allocMatrix(&ma);

    printf("Inserisci valore scalare di tipo reale : ");
    salvaValore(&a);

    for( i = 0; i < leggiRighe(ma); i++ )
        for ( j = 0; j < leggiColonne(ma); j++ )
            scriviElemento(&ma,i,j, a * leggiValore(m[scelta],i,j));


    return ma;
}

matrice diffMatrice( matrice *elenco, int cont)
{
    matrice md;
    int i,j;
    int scelta1,scelta2;

    controllaDati( elenco, cont, 'D' , &scelta1, &scelta2);
    initDim( &md, elenco[scelta1]);

    allocMatrix(&md);

    for( i=0; i < leggiRighe(md);i++)
       for(j=0; j < leggiColonne(md); j++)
           scriviElemento( &md, i, j, leggiValore(elenco[scelta1],i,j)- leggiValore(elenco[scelta2], i,j));


    return md;

}

matrice prodvetMatrice( matrice *elenco, int cont)
{
    matrice MpvN;
    int i,j,k;
    int scelta1,scelta2;

    controllaDati( elenco, cont, 'P' , &scelta1, &scelta2);
    
    
    MpvN.righe = leggiRighe(elenco[scelta1]);
    MpvN.colonne = leggiColonne(elenco[scelta2]);

    allocMatrix(&MpvN);

    for(i=0;i< leggiRighe(MpvN);i++)
       for(j=0;j< leggiColonne(MpvN);j++)
          for(k=0;k< leggiColonne(elenco[scelta1]);k++)
            scriviElemento( &MpvN, i, j, leggiValore(MpvN,i,j) + leggiValore(elenco[scelta1],i,k)* leggiValore(elenco[scelta2],k,j) );



    return MpvN;
}

void sceltaMatrici(matrice *m, int *scelta1, int *scelta2, int cont)
{
    do
     {
          printf("Indicare l'ID della matrice n.1: ");
          *scelta1 = leggiIntero();
          if(*scelta1 < 0 || *scelta1 >= cont)
             printf("Matrice non esistente!\n");
     }while( *scelta1 < 0 || *scelta1 >= cont );
     
    do
     {
          printf("Indicare l'ID della matrice n.2: ");
          *scelta2 = leggiIntero();
          if( *scelta2 < 0 || *scelta2 >= cont )
             printf("Matrice non esistente!\n");
             
                     
     }while( (*scelta2 < 0 || *scelta2 >= cont) );
}

int leggiIntero()
{
    int res;
    int intero;
    do
    {
        res = scanf("%d",&intero);
        scanf("%*[^\n]");
        if( res == 0) 
          printf("\nAssegnazione valore errata, reinserisci: ");
          
    }while ( res == 0 );
    
    return intero;
} 
  
void controllaDati( matrice *elenco, int n, char opt, int *scelta1, int *scelta2 )
{
    int res;

    switch ( opt )
    {

     case 'S' : case 'D' :
        do
        {

            sceltaMatrici(elenco,scelta1, scelta2, n);
            res = checkDim( elenco[*scelta1], elenco[*scelta2] );
            if ( res == 0 )
                fprintf(stderr,"Reinserisci le matrici!\nLE MATRICI DEVONO NECESSARIAMENTE AVERE LE STESSE DIMENSIONI!\n");

        }while( res == 0 || ( checkDim(elenco[*scelta1], elenco[*scelta2])) == 0 );
    break;
    case 'P':
        do
        {

            sceltaMatrici(elenco,scelta1, scelta2, n);
            res = checkDim( elenco[*scelta1], elenco[*scelta2] );
            if ( res == 0 )
                fprintf(stderr,"Reinserisci le matrici!\nLE MATRICI DEVONO NECESSARIAMENTE AVERE LE STESSE DIMENSIONI!\n");

        }while( res == 0 || ( checkRowCol(elenco[*scelta1],elenco[*scelta2]) == 0));

    break;
    }
}
