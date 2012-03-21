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
                
               printf("Inserisci matrice - ID %d\nID UNIVOCAMENTE ASSEGNEGNATO REGISTRATO\n", cont);
               elenco[cont] = inserisciMatrice(cont);
               cont++;
             
	  break;
	        
      case 2:
           
           if( cont > 0 )
           {
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
            }
             else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }     
            
      break;

     case 3:
      //overwrite 
      break;
     
     case 4:
          
          if( cont > 0 )
           {
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
          
          elenco = reallocMat(elenco, cont+1);  
          elenco[cont] = trasposta(elenco[matchoice]);
          stampaMatrice(elenco[cont], cont); 
          cont++; 
          wait();
           
           }else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }    
                              
      
      break; 

      case 5:
           
           if( cont > 0 )
           {
             elenco = reallocMat(elenco, cont+1);
             elenco[cont] = sommaMatrici(elenco, cont);
             stampaMatrice(elenco[cont], cont);
             cont++;
             wait();
             
           }else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             } 

        
	  break;

	case 6:
	       
	       if( cont > 0 )
           {
            elenco = reallocMat(elenco, cont+1);
            elenco[cont] = diffMatrice(elenco, cont);
            stampaMatrice(elenco[cont], cont);
            cont++;
            wait();
           
            }else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }
           
	  break;

	case 7 :
	  
	       if( cont > 0 )
           {
	        elenco = reallocMat(elenco, cont+1);
            elenco[cont] = prodScalareMatrice(elenco, cont);
            stampaMatrice(elenco[cont], cont);
            cont++;
            wait();
           
            }else
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
               stampaMatrice(elenco[cont], cont);
               cont++;
               wait();
           
            }else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }
	  
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

