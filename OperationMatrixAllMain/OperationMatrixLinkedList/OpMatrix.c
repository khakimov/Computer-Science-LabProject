#include "OpMatrix.h"
#include "ReadWriteFoo.h"

/* Useful funtion used to get the option choosen by the user from the command line and print the menu */
int intestazione()
{
  int scelta; /* Holds the choice made by the user when was asked to him which operation will do */
  int ris; /* Represents the return value of the scanf() that was checked out in order to manage some possible errors */


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
   overwriteMatrix function which grants to the user
   to overwrite unneeded matrix saved in memory in oreder
   to save some other when the memory was full.

   Parameters:
   matrice m* : Pointers to a struct of type matrice
   int n : represents the number of matrix saved in memory until now

   Returns :
   an integer value which represents the location in
   which was present the matrix that will be 
   overwritten.
*/
/*int overwriteMatrix( matrice *m, int n )
{
  int matchoice; // A specific integer value that represent the id of the matrix 
  char choice; // Hold the value of the user's choice needed to ask to him if he wants to continue 


     printf("----- SOVRASCRITTURA --------\n\n");


     if ( n <= 0 )
        printf("%s\n%s\n",
               "L'operazione di sovrascrittura non e' possibile!",
               "NESSUNA MATRICE DISPONIBILE, PREMI 1 NEL MENU PER INSERIRLE!");
    else
    {
       printf("Sara' possibile inserire l'ID della matrice che si vuole sovrascrivere!!\n\n");
       sceltaMatrici(&matchoice, NULL, n);
        printf("%s %d\n",
               "Si sta per sovrascrivere la matrice con ID", matchoice);

        do
        {

            printf("Si intende continuare? s/n\nSCELTA : ");
            scanf("\n%c", &choice);

            if( choice != 'n' && choice != 's' )
            {
                printf("Scelta non consentita!!\n");
                scanf("%*[^\n]");


            }
        }while ( ( choice != 'n' && choice != 's' ) );

        if( choice == 's' )
            return matchoice;
        else
        {
           printf("La matrice con ID %d non e' stata sovrascritta!!", matchoice);
           return -1;
        }

    }

}*/


/* Deallocate memory  */
/*void free_matrix( matrice *elenco )
{

    free(elenco);


}
*/
/*
    Simple function used in order to check the correcteness of the dimension of the matrix
    that are involved into operation like the sum and the difference, in which the fundamental
    requirement is that the matrix MUST have the same dimensions.
*/
/*int checkDim( matrice *m, matrice *n )
{
    return ( leggiRighe(m) == leggiRighe(n) && leggiColonne(m) == leggiColonne(n) ) ? 1 : 0;
}
*/
/*
    Function that check if the m's colomns and the n'rows are equal
    in order to grant the possibility to make the vectorial product
    between the selected matrixs.

*/
/*int checkRowCol( matrice *m , matrice *n)
{
    return ( leggiColonne(m) == leggiRighe(n) ) ? 1 : 0;
}

void initDim( matrice *dest, matrice *src )
{
  dest->righe = leggiRighe(src);
  dest->colonne = leggiColonne(src);

}*/
/* Useful function used in order to remove some useless characters present in the buffer */
void cleanBuffer()
{
    while ( getchar() != '\n');
}

/*
    Function that makes some specific control on a float value inserted,
    and only if it is correct, it stores it in a specific location pointed by f.
*/
/*void salvaValore( float *f )
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
*/

/*
    Function that receives the number of colomn and the number of row of the matrix,
    and create it asking to the user to fill it inserting each row.
*/
matrice creaMatrice( int id )
{
    matrice array;
    array.mat = NULL;

    int i,j;

    printf("INSERIMENTO MATRICE\nLa nuova matrice avra' come ID %d\nID UNIVOCAMENTE ASSEGNEGNATO REGISTRATO\n", id);
    scriviRighe(&array);
    scriviColonne(&array);

    array.id = id;


    cleanBuffer();

    /*allocMatrix(&array);
    */

    printf("\n\nInserisci elementi della matrice\n");
    for ( i = 0; i < leggiRighe(&array); i++ )
        for ( j = 0; j < leggiColonne(&array); j++ )
             scriviElemento(&array, i, j, scriviValore(i, j) );

    return array;
}

/* Prints to video the values present in the matrix passed as a parameter */
void stampaMatrice( matrice *elenco, int cont )
{
  int i,j;
  int matchoice;
  matrice *curr;

    printf("MATRICI TOTALI DISPONIBILI = %d\n\n", cont);

  if ( leggiRighe(curr) == 0 )
     printf("Matrice non inizializzata!!\n");
  else
  {
      printf("\t ----- Matrice %d ---- \n", curr -> id);
      for(i = 0; i < leggiRighe(curr); printf("\n"),i++)
        for(j=0;j < leggiColonne(curr);j++)
            printf("%15.3f ",leggiValore(curr, i, j));
  }

}

/*
    Function which make the transposition operation of a
    matrix passed as a parameter.
    It returns a double pointer which points to the current location
    in which the new trasposed matrix will be.
*/
matrice trasposta( matrice *elenco, int cont )
{
  int i,j;
  matrice mat_t;

  int matchoice;
  matrice *curr;
  

  //sceltaMatrici(&matchoice, NULL, cont);
  //curr = cercaMatrice(elenco, matchoice);
  curr = elenco;


  mat_t.mat = NULL;
  mat_t.id = cont;
  mat_t.righe = leggiColonne(curr);
  mat_t.colonne = leggiRighe(curr);



  for ( i=0; i < leggiRighe(&mat_t); i++ )
    for ( j = 0; j < leggiColonne(&mat_t); j++ )
        scriviElemento(&mat_t,i,j,leggiValore(curr,j,i));



  return mat_t;

}


matrice somma( matrice *curr,matrice *curr2, int cont)
{
    matrice mpn;
    int i, j;

    mpn.mat = NULL;
    initDim( &mpn, curr);

    mpn.id = cont;

    for ( i = 0; i < leggiRighe(&mpn); i++ )
        for ( j = 0; j < leggiColonne(&mpn); j++ )
            scriviElemento( &mpn,i, j, leggiValore(curr, i, j) + leggiValore(curr2, i, j));


    return mpn;
}

matrice scalare( matrice *m, int cont )
{
    matrice ma;
    float a;
    int i, j;
    int scelta;
    matrice *curr;

    ma.mat = NULL;
    initDim( &ma, curr);


    ma.id = cont;

    printf("Inserisci valore scalare di tipo reale : ");
    salvaValore(&a);

    for( i = 0; i < leggiRighe(&ma); i++ )
        for ( j = 0; j < leggiColonne(&ma); j++ )
            scriviElemento(&ma,i,j, a * leggiValore(curr,i,j));

    return ma;
}

matrice differenza( matrice *curr,matrice *curr2, int cont)
{
    matrice md;
    int i,j;

    md.mat = NULL;
    initDim( &md, curr);

    /*allocMatrix(&md);*/

    md.id = cont;

    for( i=0; i < leggiRighe(&md);i++)
       for(j=0; j < leggiColonne(&md); j++)
           scriviElemento( &md, i, j, leggiValore(curr,i,j)- leggiValore(curr2, i,j));


    return md;

}

matrice prodotto( matrice *curr,matrice *curr2, int cont)
{
    matrice MpvN;
    int i,j,k;
    float tot = 0;

    MpvN.mat = NULL;
    MpvN.righe = leggiRighe(curr);
    MpvN.colonne = leggiColonne(curr2);
    MpvN.id = cont;


    for(i=0;i< leggiRighe(&MpvN);i++)
       for(j=0;j< leggiColonne(&MpvN);j++)
       {
         for(k=0;k< leggiColonne(curr);k++)
            tot += leggiValore(curr,i,k)* leggiValore(curr2,k,j);
         scriviElemento( &MpvN, i, j, tot );
       }


    return MpvN;
}

/*void sceltaMatrici(int *scelta1, int *scelta2, int cont)
{
    do
     {
          printf("Indicare l'ID della matrice sulla quale si intende operare: ");
          *scelta1 = leggiIntero();
          if(*scelta1 < 0 || *scelta1 >= cont)
             printf("Matrice non esistente!\n");
     }while( *scelta1 < 0 || *scelta1 >= cont );

    if(scelta2!=NULL)
    {
     do
     {
          printf("Indicare l'ID della matrice successiva: ");
          *scelta2 = leggiIntero();
          if( *scelta2 < 0 || *scelta2 >= cont )
             printf("Matrice non esistente!\n");


      }while( (*scelta2 < 0 || *scelta2 >= cont) );
     }
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

            sceltaMatrici(scelta1, scelta2, n);
            res = checkDim( cercaMatrice(elenco, *scelta1), cercaMatrice(elenco, *scelta2) );
            if ( res == 0 )
                fprintf(stderr,"Reinserisci le matrici!\nLE MATRICI DEVONO NECESSARIAMENTE AVERE LE STESSE DIMENSIONI!\n");

        }while( res == 0 || ( cercaMatrice(elenco, *scelta1), cercaMatrice(elenco, *scelta2)) == 0 );
    break;
    case 'P':
        do
        {

            sceltaMatrici(scelta1, scelta2, n);
            res = checkRowCol( cercaMatrice(elenco, *scelta1), cercaMatrice(elenco, *scelta2));
            if ( res == 0 )
                fprintf(stderr,"Reinserisci le matrici!\n%s\n",
                        "ATTENZIONE: IL NUMERO DI COLONNE DELLA SECONDA MATRICE DEVE ESSERE UGUALE A QUELLO DELLE COLONNE!!");

        }while( res == 0 || ( checkRowCol(cercaMatrice(elenco, *scelta1), cercaMatrice(elenco, *scelta2)) == 0));

    break;
    }
}
matrice *cercaMatrice (matrice *elenco, int pos)
{
    matrice *curr;
    int trovato = 0;

    curr = elenco;

    while (curr && !trovato)
    {
       if (curr -> id == pos) trovato = 1;
           else curr = curr -> next;
    }
    return curr;
}
matrice* allocMatrice ()
{
   return (matrice*)malloc(sizeof(matrice));
}
*/
