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
            stampaMatrice(elenco, cont, 0);  
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
          
            elenco = reallocMat(elenco, cont+1);  
            elenco[cont] = trasposta(elenco, cont);
            stampaMatrice(elenco, cont, 1); 
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
             stampaMatrice(elenco, cont, 1);
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
            stampaMatrice(elenco, cont, 1);
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
            stampaMatrice(elenco, cont, 1);
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
               stampaMatrice(elenco, cont, 1);
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

