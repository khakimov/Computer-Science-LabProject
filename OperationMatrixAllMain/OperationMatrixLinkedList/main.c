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
  matrice *curr,*curr2,*curr3;
  matrice *succ;
  int cont = 0;
  int scelta=1;
  int pos = 0;
  int res;
  int intero;
  int trovato = 0;


  while(scelta)
  {
      scelta=intestazione();

      switch(scelta)
	  {
        case 1:

                /*
                if ( cont > 0 && cont <= MAXM )
                    elenco = reallocMat( elenco,cont+1 );
                if( cont > MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                        elenco[pos] = inserisciMatrice(pos);
                }
                else
                {
                    elenco[cont] = inserisciMatrice(cont);
                    cont++;
                }
                */
                if( !elenco )
                {
                    elenco = (matrice*)malloc(sizeof(matrice));
                    *elenco = creaMatrice(0);
                    elenco -> next = NULL;
                    cont++;
                }
                else
                {


                if ( cont > 0 /*&& cont <= MAXM*/ )
                {
                    curr2 = elenco; 
                     while (curr2 && !trovato)
                     {
                      if (curr2 -> id == intero) trovato = 1;
                      else curr2 = curr2 -> next;
                      }
                    curr2 -> next = (matrice*)malloc(sizeof(matrice));
                }

                /*if ( cont >= MAXM)
                {
                    printf("E' stato superato il limite di matrici previsto!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                      curr = cercaMatrice(elenco, pos);
                      succ = curr -> next;
                      *curr = creaMatrice(pos);
                      curr -> next = succ;
                    }

                }
                else
                {

                    curr = cercaMatrice(elenco, cont-1);
                    curr = curr -> next;
                    *curr = creaMatrice(cont);
                    curr -> next = NULL;
                    cont++;
                }*/
                }

	  break;

      case 2:

           if( cont > 0 )
           {
            do
            {
             printf("Indicare l'ID della matrice sulla quale si intende operare: ");
             do
             {
               res = scanf("%d",&intero);
               scanf("%*[^\n]");
               if( res == 0)
               printf("\nAssegnazione valore errata, reinserisci: ");

             }while ( res == 0 );
             if(intero < 0 || intero >= cont)
                       printf("Matrice non esistente!\n");
             
            }while( intero < 0 || intero >= cont );
            
            curr2 = elenco; 
            while (curr2 && !trovato)
            {
             if (curr2 -> id == intero) trovato = 1;
             else curr2 = curr2 -> next;
             }
             
            stampaMatrice(curr2, cont);
            wait();
            }
             else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }

      break;

    /* case 3:

            pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                      curr = cercaMatrice(elenco, pos);
                      succ = curr -> next;
                      *curr = creaMatrice(pos);
                      curr -> next = succ;
                    }
            wait();
      break;*/

     case 4:

          if( cont > 0 /*&& cont <= MAXM*/ )
           {

            curr = elenco; 
            while (curr -> next)
            {
               curr = curr -> next;
              }
            curr -> next = (matrice*)malloc(sizeof(matrice));
            curr = curr -> next;
            
            do
            {
             printf("Indicare l'ID della matrice sulla quale si intende operare: ");
             do
             {
               res = scanf("%d",&intero);
               scanf("%*[^\n]");
               if( res == 0)
               printf("\nAssegnazione valore errata, reinserisci: ");

             }while ( res == 0 );
             if(intero < 0 || intero >= cont)
                       printf("Matrice non esistente!\n");
             
            }while( intero < 0 || intero >= cont );
            
            curr2 = elenco; 
            while (curr2 && !trovato)
            {
             if (curr2 -> id == intero) trovato = 1;
             else curr2 = curr2 -> next;
             }
             
            *curr = trasposta(curr2, cont);
            curr -> next = NULL;
            cont++;


           }
          /* else
              if ( cont >= MAXM )
              {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                        curr = cercaMatrice(elenco, pos);
                        curr = curr -> next;
                        *curr = trasposta( elenco, cont );
                        curr -> next = NULL;
                    }

                }*/
           else

             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }


      break;

      case 5:

           if( cont > 0 /*&& cont <= MAXM*/ )
           {
             curr = elenco; 
             while (curr -> next)
            {
               curr = curr -> next;
              }
             curr -> next = (matrice*)malloc(sizeof(matrice));
            do
            {
             printf("Indicare l'ID della matrice 1 sulla quale si intende operare: ");
             do
             {
               res = scanf("%d",&intero);
               scanf("%*[^\n]");
               if( res == 0)
               printf("\nAssegnazione valore errata, reinserisci: ");

             }while ( res == 0 );
             if(intero < 0 || intero >= cont)
                       printf("Matrice non esistente!\n");
             
            }while( intero < 0 || intero >= cont );
            
            curr2 = elenco; 
            while (curr2 && !trovato)
            {
             if (curr2 -> id == intero) trovato = 1;
             else curr2 = curr2 -> next;
             }
             do
            {
             printf("Indicare l'ID della matrice 2 sulla quale si intende operare: ");
             do
             {
               res = scanf("%d",&intero);
               scanf("%*[^\n]");
               if( res == 0)
               printf("\nAssegnazione valore errata, reinserisci: ");

             }while ( res == 0 );
             if(intero < 0 || intero >= cont)
                       printf("Matrice non esistente!\n");
             
            }while( intero < 0 || intero >= cont );
            
            curr3 = elenco; 
            while (curr3 && !trovato)
            {
             if (curr3 -> id == intero) trovato = 1;
             else curr3 = curr3 -> next;
             }
             *curr -> next = somma(curr2,curr3, cont);
             cont++;


           }
           /*else
             if ( cont >= MAXM )
             {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos =overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                        curr = cercaMatrice(elenco, pos);
                        *curr -> next = somma(elenco, cont);
                        curr = curr -> next;
                        curr -> next = NULL;
                    }
                }*/
           else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }


	  break;

	case 6:

	       if( cont > 0 /*&& cont <= MAXM*/ )
           {
             curr = elenco; 
             while (curr -> next)
            {
               curr = curr -> next;
              }
             curr -> next = (matrice*)malloc(sizeof(matrice));
            do
            {
             printf("Indicare l'ID della matrice 1 sulla quale si intende operare: ");
             do
             {
               res = scanf("%d",&intero);
               scanf("%*[^\n]");
               if( res == 0)
               printf("\nAssegnazione valore errata, reinserisci: ");

             }while ( res == 0 );
             if(intero < 0 || intero >= cont)
                       printf("Matrice non esistente!\n");
             
            }while( intero < 0 || intero >= cont );
            
            curr2 = elenco; 
            while (curr2 && !trovato)
            {
             if (curr2 -> id == intero) trovato = 1;
             else curr2 = curr2 -> next;
             }
             do
            {
             printf("Indicare l'ID della matrice 2 sulla quale si intende operare: ");
             do
             {
               res = scanf("%d",&intero);
               scanf("%*[^\n]");
               if( res == 0)
               printf("\nAssegnazione valore errata, reinserisci: ");

             }while ( res == 0 );
             if(intero < 0 || intero >= cont)
                       printf("Matrice non esistente!\n");
             
            }while( intero < 0 || intero >= cont );
            
            curr3 = elenco; 
            while (curr3 && !trovato)
            {
             if (curr3 -> id == intero) trovato = 1;
             else curr3 = curr3 -> next;
             }
             *curr -> next = differenza(curr2,curr3, cont);
             cont++;


           }
            /*else
                if ( cont >= MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                        curr = cercaMatrice(elenco, pos);
                        *curr -> next = differenza(elenco, cont);
                        curr = curr -> next;
                        curr -> next = NULL;
                    }
                }*/
            else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }

	  break;

	case 7 :

	       if( cont > 0 /*&& cont <= MAXM*/ )
           {
             curr = elenco; 
             while (curr -> next)
            {
               curr = curr -> next;
              }
             curr -> next = (matrice*)malloc(sizeof(matrice));
            do
            {
             printf("Indicare l'ID della matrice sulla quale si intende operare: ");
             do
             {
               res = scanf("%d",&intero);
               scanf("%*[^\n]");
               if( res == 0)
               printf("\nAssegnazione valore errata, reinserisci: ");

             }while ( res == 0 );
             if(intero < 0 || intero >= cont)
                       printf("Matrice non esistente!\n");
             
            }while( intero < 0 || intero >= cont );
            
            curr2 = elenco; 
            while (curr2 && !trovato)
            {
             if (curr2 -> id == intero) trovato = 1;
             else curr2 = curr2 -> next;
             }
            
             *curr -> next = scalare(curr2, cont);
             cont++;


           }
           /* else
                if ( cont >= MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                        curr = cercaMatrice(elenco, pos);
                        *curr -> next = scalare( elenco, cont);
                        curr = curr -> next;
                        curr -> next = NULL;
                    }
                }*/
            else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }
	break;

	case 8 :

           if( cont > 0 /*&& cont <= MAXM*/ )
           {
             curr = elenco; 
             while (curr -> next)
            {
               curr = curr -> next;
              }
             curr -> next = (matrice*)malloc(sizeof(matrice));
            do
            {
             printf("Indicare l'ID della matrice 1 sulla quale si intende operare: ");
             do
             {
               res = scanf("%d",&intero);
               scanf("%*[^\n]");
               if( res == 0)
               printf("\nAssegnazione valore errata, reinserisci: ");

             }while ( res == 0 );
             if(intero < 0 || intero >= cont)
                       printf("Matrice non esistente!\n");
             
            }while( intero < 0 || intero >= cont );
            
            curr2 = elenco; 
            while (curr2 && !trovato)
            {
             if (curr2 -> id == intero) trovato = 1;
             else curr2 = curr2 -> next;
             }
             do
            {
             printf("Indicare l'ID della matrice 2 sulla quale si intende operare: ");
             do
             {
               res = scanf("%d",&intero);
               scanf("%*[^\n]");
               if( res == 0)
               printf("\nAssegnazione valore errata, reinserisci: ");

             }while ( res == 0 );
             if(intero < 0 || intero >= cont)
                       printf("Matrice non esistente!\n");
             
            }while( intero < 0 || intero >= cont );
            
            curr3 = elenco; 
            while (curr3 && !trovato)
            {
             if (curr3 -> id == intero) trovato = 1;
             else curr3 = curr3 -> next;
             }
             *curr -> next = prodotto(curr2,curr3, cont);
             cont++;


           }

            /*else
                if ( cont >= MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                        curr = cercaMatrice(elenco, pos);
                        *curr -> next = prodotto(elenco, cont );
                        curr = curr -> next;
                        curr -> next = NULL;
                    }
                }*/
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

