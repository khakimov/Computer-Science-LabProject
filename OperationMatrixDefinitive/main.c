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

#include "header.h"


int main()
{
  matrice *elenco = initElenco();
  matrice matx_t;
  matrice matx_s;
  
  int cont_t = 0;
  int cont = 0;
  int scelta=1;
  int res;
  int matchoice = 0; /* variable used in order to get the choice inserted by the user */
  int scelta1,scelta2;


  while(scelta)
  {
      scelta=intestazione();

      switch(scelta)
	  {
        case 1:
             
               if ( cont > 0 )
                elenco = reallocMat( elenco,cont+1 );
                
               printf("Inserisci matrice - ID %d\nID UNIVOCAMENTE ASSEGNEGNATO REGISTRALO\n", cont);
               elenco[cont] = inserisciMatrice(cont);
               cont++;
             
	  break;
	        
      case 2:
           do
            {
               printf("%s%s %d\n",
                   "Inserisci l'ID della matrice della quale si intende visualizzare i valori\n",
                   "MATRICI CARICATE", cont);
               res = scanf("%d", &matchoice);
               scanf("%*[^\n]");
               if ( res == 0 ) 
                  printf("Valore inserito errato, riprovare!\n");
               else
                   if ( matchoice < 0 || matchoice > cont )
                      printf("Valore inserito non fa riferimento a matrici inizializzate!!\n");                 
                   
            }while( res == 0 || matchoice > cont);
            
            stampaMatrice(elenco[matchoice], matchoice);  
            wait();
            
      break;

     case 3:
      //overwrite this dick stupid duck
      break;
     
     case 4:
          do
          {
             printf("%s%s %d\n",
                    "Inserisci l'ID della matrice sulla quale si intende operare la TRASPOSTA\n",
                    "MATRICI CARICATE", cont);
             res = scanf("%d", &matchoice);  
             scanf("%*[^\n]");
             if ( res == 0 )
                printf("ID inserito errato, riprovare!\n");
             else 
                if (matchoice < 0 || matchoice > cont)
                   printf("ID inserito non fa riferimento a matrici inizializzate!\n");
             }while ( res == 0 || matchoice > cont);
             
          matx_t = trasposta(elenco[matchoice]);
          stampaMatrice(matx_t, matchoice);  
          wait();  
                              
      
      break; 

      case 5:
           sceltaMatrici(elenco,&scelta1, &scelta2, cont);
           sommaMatrici(elenco[scelta1],elenco[scelta2]);
           stampaMatrice(matx_s, 0);
        
	  break;

	case 6:
	  
	  break;

	case 7 :
	  
	break;

	case 8 :
	  
	break;
	
	case 9 :
	  
	break;

   case 0:
	  

	  scelta=0;

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

