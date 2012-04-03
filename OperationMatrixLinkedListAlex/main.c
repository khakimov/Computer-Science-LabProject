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
  matrice *elenco = NULL;//initElenco();
  matrice *curr;
  matrice *succ;
  int cont = 0;
  int scelta=1;
  int pos = 0;


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
                    elenco = allocMatrice();
                    *elenco = inserisciMatrice(0);
                    elenco -> next = NULL;
                    cont++;
                }
                else
                {


                if ( cont > 0 && cont <= MAXM )
                {
                    curr = cercaMatrice(elenco, cont-1);
                    curr -> next = allocMatrice();
                }

                if ( cont >= MAXM)
                {
                    printf("E' stato superato il limite di matrici previsto!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                      curr = cercaMatrice(elenco, pos);
                      succ = curr -> next;
                      *curr = inserisciMatrice(pos);
                      curr -> next = succ;
                    }

                }
                else
                {

                    curr = cercaMatrice(elenco, cont-1);
                    curr = curr -> next;
                    *curr = inserisciMatrice(cont);
                    curr -> next = NULL;
                    cont++;
                }
                }

	  break;

      case 2:

           if( cont > 0 )
           {
            stampaMatrice(elenco, cont);
            wait();
            }
             else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }

      break;

     case 3:

            pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                      curr = cercaMatrice(elenco, pos);
                      succ = curr -> next;
                      *curr = inserisciMatrice(pos);
                      curr -> next = succ;
                    }
            wait();
      break;

     case 4:

          if( cont > 0 && cont <= MAXM )
           {

            curr = cercaMatrice(elenco, cont-1);
            curr -> next = allocMatrice();
            curr = curr -> next;
            *curr = trasposta(elenco, cont);
            curr -> next = NULL;
            cont++;


           }
           else
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

                }
           else

             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }


      break;

      case 5:

           if( cont > 0 && cont <= MAXM )
           {
             curr = cercaMatrice(elenco, cont-1);
             curr -> next = allocMatrice();

             *curr -> next = sommaMatrici(elenco, cont);
             cont++;


           }
           else
             if ( cont >= MAXM )
             {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos =overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                        curr = cercaMatrice(elenco, pos);
                        *curr -> next = sommaMatrici(elenco, cont);
                        curr = curr -> next;
                        curr -> next = NULL;
                    }
                }
           else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }


	  break;

	case 6:

	       if( cont > 0 && cont <= MAXM )
           {
                curr = cercaMatrice(elenco, cont-1);
                curr -> next = allocMatrice();

                *curr -> next = diffMatrice(elenco, cont);
                cont++;

            }
            else
                if ( cont >= MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                        curr = cercaMatrice(elenco, pos);
                        *curr -> next = diffMatrice(elenco, cont);
                        curr = curr -> next;
                        curr -> next = NULL;
                    }
                }
            else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }

	  break;

	case 7 :

	       if( cont > 0 && cont <= MAXM)
           {
                curr = cercaMatrice(elenco, cont-1);
                curr -> next = allocMatrice();

                *curr -> next = prodScalareMatrice( elenco, cont);
                cont++;


            }
            else
                if ( cont >= MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                        curr = cercaMatrice(elenco, pos);
                        *curr -> next = prodScalareMatrice( elenco, cont);
                        curr = curr -> next;
                        curr -> next = NULL;
                    }
                }
            else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }
	break;

	case 8 :

           if( cont > 0 && cont <= MAXM)
           {
                curr = cercaMatrice(elenco, cont-1);
                curr -> next = allocMatrice();

                *curr -> next = prodvetMatrice(elenco, cont );
                cont++;


            }

            else
                if ( cont >= MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                    {
                        curr = cercaMatrice(elenco, pos);
                        *curr -> next = prodvetMatrice(elenco, cont );
                        curr = curr -> next;
                        curr -> next = NULL;
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
        free_matrix( elenco );

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

