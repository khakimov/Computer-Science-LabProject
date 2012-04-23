/*
    ****************************************
    ****************************************
    ********    MATRIX OPERATION ***********
    ****************************************
    ****************************************

    @authors : Alessandro Suglia & Nazar Chekalin


*/

#if defined _WIN32
#define pause() getch()
#elif defined __unix__
#define pause() getchar()
#endif

#include "OpMatrix.h"


int main()
{
  matrice *elenco = NULL;

  int cont = 0;
  int scelta=1;
  int res;
  int ris;
  int r, c;
  float x;
  int i, j;
  int scelta1 = 0,scelta2 = 0;

  elenco = (matrice*)malloc( 1 * sizeof(matrice));
  if ( elenco == NULL )
  {
      fprintf(stderr,"ERRORE ALLOCAZIONE DINAMICA DELLA MEMORIA\n");
      wait();
      exit(-1);
  }
  while(scelta)
  {
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
         printf("----------OPERAZIONI MATRICI----------\nPowered by A. Suglia & N. Chekalin\n\n%s%s%s%s%s%s%s%s%s\n",
                "-----------------MENU'----------------\n\n",
                "1 - Inserire Matrice \n",
                "2 - Stampa Matrice \n",
                "3 - Matrice Trasposta\n",
                "4 - Somma Matrici\n",
                "5 - Differenza Matrici\n",
                "6 - Prodotto Scalare Matrici\n",
                "7 - Prodotto Vettoriale Matrici\n",
                "0 - Esci\n\n");
        printf("Scelta operazione -> ");
        ris=scanf("%d",&scelta);
        scanf("%*[^\n]");

        }while(ris==0);

        switch(scelta)
        {
            case 1:

                if ( cont > 0  )
                {
                    elenco = (matrice*)realloc( elenco, (cont+1) * sizeof(matrice));
                    if ( elenco == NULL )
                    {
                       fprintf(stderr,"ERRORE ALLOCAZIONE MEMORIA!\n");
                       wait();
                       exit(-1);
                    }
                }

                    printf("INSERIMENTO MATRICE\nLa nuova matrice avra' come ID %d\nID UNIVOCAMENTE ASSEGNEGNATO REGISTRATO\n", cont);

                    scriviId(&elenco[cont], cont);

                    /* Gets row and colomn of the matrix */
                    do
                    {
                        printf("\nInserisci righe matrice: ");

                        res = scanf("%d",&r);
                        scanf("%*[^\n]");

                        if(res==0)
                            fprintf(stderr,"\n**Assegnazione valore errata!**\n\n");
                        else if( r < 1 || r > MAXR)
                            fprintf(stderr,"\n**Il numero di righe e' errato (1< r < %d)**\n\n",MAXR);

                    }while(res == 0 || ( r < 1 || r > MAXR));

                    scanf("%*[^\n]");
                    do
                    {
                        printf("\nInserisci colonne matrice: ");
                        res = scanf("%d",&c);
                        scanf("%*[^\n]");
                        if(res==0)
                            fprintf(stderr,"\n**Assegnazione valore errata!**\n\n");
                        else if( c < 1 || c > MAXR)
                            fprintf(stderr,"\n**Il numero di colonne e' errato (1< c < %d)**\n\n",MAXC);

                    }while(res == 0 || c < 1 || c > MAXR );

                    scanf("%*[^\n]");

                    creaMatrice( &elenco[cont], r, c );
                    printf("\n\nInserisci elementi della matrice\n");

                    for ( i = 0; i < leggiRighe(&elenco[cont]); i++ )
                    {

                        for ( j = 0; j < leggiColonne(&elenco[cont]); j++ )
                        {
                            do
                            {
                                printf("m[%d][%d] = ", i, j);
                                res = scanf("%f", &x);
                                scanf("%*[^\n]");
                                if ( res == 0 || x > FLT_MAX )
                                printf("Valore inserito non corretto!!Sono ammessi solo valori reali!\n");

                            }while( res == 0 || x > FLT_MAX );

                            scriviElemento(&elenco[cont], i, j, x);

                        }
                    }

                    cont++;


	  break;

      case 2:
            /* Print to video the value of the selected matrix */
           if( cont > 0 )
           {
            printf("MATRICI TOTALI DISPONIBILI = %d\n\n", cont);
            do
            {
              printf("Indicare l'ID della matrice sulla quale si intende operare: ");
               do
               {
                 res = scanf("%d",&scelta1);
                 scanf("%*[^\n]");
                 if( res == 0)
                   printf("\nAssegnazione valore errata, reinserisci: ");

               }while ( res == 0 );
               if(scelta1 < 0 || scelta1 >= cont)
                  printf("Matrice non esistente!\n");

            }while( scelta1 < 0 || scelta1 >= cont );
            if ( leggiRighe(&elenco[scelta1]) == 0 )
               printf("Matrice non inizializzata!!\n");
            else
                stampaMatrice(&elenco[scelta1]);

            wait();
            }
             else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }

      break;

     case 3:
            /* Create the transposition of the selected matrix */
          if( cont > 0  )
           {
            /* Adds a new element to the list of matrix array */
            elenco = (matrice*)realloc( elenco, (cont+1) * sizeof(matrice));
            if ( elenco == NULL )
            {
             fprintf(stderr,"ERRORE ALLOCAZIONE MEMORIA!\n");
             wait();
             exit(-1);
            }
            do
            {
              printf("Indicare l'ID della matrice sulla quale si intende operare: ");
               do
               {
                 res = scanf("%d",&scelta1);
                 scanf("%*[^\n]");
                 if( res == 0)
                   printf("\nAssegnazione valore errata, reinserisci: ");

               }while ( res == 0 );
               if(scelta1 < 0 || scelta1 >= cont)
                  printf("Matrice non esistente!\n");

            }while( scelta1 < 0 || scelta1 >= cont );

            scriviId(&elenco[cont], cont);
            creaMatrice( &elenco[cont], leggiColonne(&elenco[scelta1]), leggiRighe(&elenco[scelta1]));
            trasposta( &elenco[cont], &elenco[scelta1] );
            cont++;


           }

           else

             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }


      break;

      case 4:
      /* Creates a matrix which is the sum of two selected matrixs */
           if( cont > 0  )
           {

            do
            {
              printf("Indicare l'ID della matrice 1 sulla quale si intende operare: ");
               do
               {
                 res = scanf("%d",&scelta1);
                 scanf("%*[^\n]");
                 if( res == 0)
                   printf("\nAssegnazione valore errata, reinserisci: ");

               }while ( res == 0 );
               if(scelta1 < 0 || scelta1 >= cont)
                  printf("Matrice non esistente!\n");

            }while( scelta1 < 0 || scelta1 >= cont );



              do
              {
                 printf("Indicare l'ID della matrice 2 sulla quale si intende operare: ");
                 do
                 {
                  res = scanf("%d",&scelta2);
                  scanf("%*[^\n]");
                  if( res == 0)
                   printf("\nAssegnazione valore errata, reinserisci: ");

                   }while ( res == 0 );
                   if(scelta2 < 0 || scelta2 >= cont)
                      printf("Matrice non esistente!\n");

                }while( scelta2 < 0 || scelta2 >= cont );

              if ( leggiRighe(&elenco[scelta1]) == leggiRighe(&elenco[scelta2]) &&
                   leggiColonne(&elenco[scelta1]) == leggiColonne(&elenco[scelta2]) )
              {
                   elenco = (matrice*)realloc( elenco, (cont+1) * sizeof(matrice));
                   if ( elenco == NULL )
                   {
                     fprintf(stderr,"ERRORE ALLOCAZIONE MEMORIA!\n");
                     wait();
                     exit(-1);
                   }
                   scriviId(&elenco[cont], cont );
                   creaMatrice( &elenco[cont], leggiRighe(&elenco[scelta1] ), leggiColonne(&elenco[scelta1]) );
                   somma( &elenco[cont], &elenco[scelta1], &elenco[scelta2]);
                   cont++;

              }
              else
                  fprintf(stderr,"Reinserisci le matrici!\nLE MATRICI DEVONO NECESSARIAMENTE AVERE LE STESSE DIMENSIONI!\n");
           }

           else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }


	  break;

	case 5:
            /* Creates a matrix which is the difference between two selected matrix */
	       if( cont > 0 )
           {

            do
            {
              printf("Indicare l'ID della matrice 1 sulla quale si intende operare: ");
               do
               {
                 res = scanf("%d",&scelta1);
                 scanf("%*[^\n]");
                 if( res == 0)
                   printf("\nAssegnazione valore errata, reinserisci: ");

               }while ( res == 0 );
               if(scelta1 < 0 || scelta1 >= cont)
                  printf("Matrice non esistente!\n");

            }while( scelta1 < 0 || scelta1 >= cont );


              do
              {
                 printf("Indicare l'ID della matrice 2 sulla quale si intende operare: ");
                 do
                 {
                  res = scanf("%d",&scelta2);
                  scanf("%*[^\n]");
                  if( res == 0)
                   printf("\nAssegnazione valore errata, reinserisci: ");

                   }while ( res == 0 );
                   if(scelta1 < 0 || scelta2 >= cont)
                      printf("Matrice non esistente!\n");

                }while( scelta2 < 0 || scelta2 >= cont );

              if ( leggiRighe(&elenco[scelta1]) == leggiRighe(&elenco[scelta2]) &&
                   leggiColonne(&elenco[scelta1]) == leggiColonne(&elenco[scelta2]) )
              {
                   elenco = (matrice*)realloc( elenco, (cont+1) * sizeof(matrice));
                   if ( elenco == NULL )
                   {
                     fprintf(stderr,"ERRORE ALLOCAZIONE MEMORIA!\n");
                     wait();
                     exit(-1);
                   }
                   scriviId(&elenco[cont], cont );
                   creaMatrice( &elenco[cont], leggiRighe(&elenco[scelta1] ), leggiColonne(&elenco[scelta1]) );
                   differenza( &elenco[cont], &elenco[scelta1], &elenco[scelta2]);
                   cont++;

              }
              else
                  fprintf(stderr,"Reinserisci le matrici!\nLE MATRICI DEVONO NECESSARIAMENTE AVERE LE STESSE DIMENSIONI!\n");
           }

           else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }

	  break;

	case 6 :
            /* Creates a matrix whose values are the former matrix's values moltiplicated by the float value specified by the user*/
	       if( cont > 0 )
           {
             elenco = (matrice*)realloc( elenco, (cont+1) * sizeof(matrice));
            if ( elenco == NULL )
            {
             fprintf(stderr,"ERRORE ALLOCAZIONE MEMORIA!\n");
             wait();
             exit(-1);
            }

            do
            {
              printf("Indicare l'ID della matrice sulla quale si intende operare: ");
               do
               {
                 res = scanf("%d",&scelta1);
                 scanf("%*[^\n]");
                 if( res == 0)
                   printf("\nAssegnazione valore errata, reinserisci: ");

               }while ( res == 0 );
               if(scelta1 < 0 || scelta1 >= cont)
                  printf("Matrice non esistente!\n");

            }while( scelta1 < 0 || scelta1 >= cont );
             /* Gets the float value from stdin */
              printf("Inserisci valore scalare per il quale moltiplicare la matrice : ");
            do
             {

              res = scanf("%f", &x);
              scanf("%*[^\n]");
              if ( res == 0 || x > FLT_MAX )
              printf("Valore inserito non corretto!!Sono ammessi solo valori reali!\n");

              }while( res == 0 || x > FLT_MAX );

            elenco = (matrice*)realloc( elenco, (cont+1) * sizeof(matrice));
            if ( elenco == NULL )
            {
             fprintf(stderr,"ERRORE ALLOCAZIONE MEMORIA!\n");
             wait();
             exit(-1);
            }

            scriviId(&elenco[cont], cont );
            creaMatrice( &elenco[cont], leggiRighe(&elenco[scelta1] ), leggiColonne(&elenco[scelta1]) );
            scalare(&elenco[cont],&elenco[scelta1], x);
            cont++;


            }

            else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }
	break;

	case 7 :
            /* Creates a matrix which is the result of the vectorial product between two selected matrix */
           if( cont > 0 )
           {
            do
            {
              printf("Indicare l'ID della matrice 1 sulla quale si intende operare: ");
               do
               {
                 res = scanf("%d",&scelta1);
                 scanf("%*[^\n]");
                 if( res == 0)
                   printf("\nAssegnazione valore errata, reinserisci: ");

               }while ( res == 0 );
               if(scelta1 < 0 || scelta1 >= cont)
                  printf("Matrice non esistente!\n");

            }while( scelta1 < 0 || scelta1 >= cont );


              do
              {
                 printf("Indicare l'ID della matrice 2 sulla quale si intende operare: ");
                 do
                 {
                  res = scanf("%d",&scelta2);
                  scanf("%*[^\n]");
                  if( res == 0)
                   printf("\nAssegnazione valore errata, reinserisci: ");

                   }while ( res == 0 );
                   if(scelta2 < 0 || scelta2 >= cont)
                      printf("Matrice non esistente!\n");

                }while( scelta2 < 0 || scelta2 >= cont );

              if ( leggiColonne(&elenco[scelta1]) == leggiRighe(&elenco[scelta2]) )
              {
                   elenco = (matrice*)realloc( elenco, (cont+1) * sizeof(matrice));
                   if ( elenco == NULL )
                   {
                     fprintf(stderr,"ERRORE ALLOCAZIONE MEMORIA!\n");
                     wait();
                     exit(-1);
                   }
                   scriviId(&elenco[cont], cont );
                   creaMatrice( &elenco[cont], leggiRighe(&elenco[scelta1] ), leggiColonne(&elenco[scelta2]) );
                   prodotto( &elenco[cont], &elenco[scelta1], &elenco[scelta2]);
                   cont++;

              }
              else
              {
                fprintf(stderr,"Reinserisci le matrici!\nLE MATRICI DEVONO NECESSARIAMENTE AVERE LE STESSE DIMENSIONI!\n");
                wait();
              }
           }

           else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }

	  break;

    case 0:


	  scelta=0;
	  if(elenco)
        free( elenco );

    break;

    default :
	  printf("Scelta immessa non valida!");
	  wait();
    }
 }



  #if defined _WIN32
         system("PAUSE");
  #endif

  return 0;

}

