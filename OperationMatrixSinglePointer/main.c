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
  matrice *elenco = initElenco();

  int cont = 0;
  int scelta = 1;
  int pos = 0;


  while(scelta)
  {
      scelta=intestazione();

      switch(scelta)
	  {
        case 1:

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

            pos = overwriteMatrix(elenco, cont );
            if ( pos != -1 )
                elenco[pos] = inserisciMatrice( pos );
            wait();
      break;

     case 4:

          if( cont > 0 && cont <= MAXM )
           {

            elenco = reallocMat(elenco, cont+1);
            elenco[cont] = trasposta(elenco, cont);
            cont++;


           }
           else
              if ( cont >= MAXM )
              {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                        elenco[pos] = trasposta( elenco, cont );
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
             elenco = reallocMat(elenco, cont+1);
             elenco[cont] = sommaMatrici(elenco, cont);
             cont++;


           }
           else
             if ( cont >= MAXM )
             {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos =overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                        elenco[pos] = sommaMatrici(elenco, cont );
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
                elenco = reallocMat(elenco, cont+1);
                elenco[cont] = diffMatrice(elenco, cont);
                cont++;


            }
            else
                if ( cont >= MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                        elenco[pos] = diffMatrice(elenco, cont );
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
	        elenco = reallocMat(elenco, cont+1);
            elenco[cont] = prodScalareMatrice(elenco, cont);
            cont++;


            }
            else
                if ( cont >= MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                        elenco[pos] = prodScalareMatrice( elenco, cont);
                }
            else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }
	break;

	case 8 :

           if( cont > 0 )
           {

               elenco = reallocMat(elenco, cont+1);
               elenco[cont] = prodvetMatrice(elenco, cont);
               cont++;


            }
            else
                if ( cont >= MAXM )
                {
                    printf("E' stato superato il limite massimo di matrici salvabili in memoria!!\n");
                    pos = overwriteMatrix(elenco, cont);
                    if ( pos != -1 )
                        elenco[pos] = prodvetMatrice(elenco, cont );
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

