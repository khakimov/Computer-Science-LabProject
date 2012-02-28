#include "verbale.h"


int carica_esami( ESAME e[] )
{
    int i;
    int n;
    
    printf("Inserisci il numero di esami da registrare : \n");
    scanf("%d", &n);
    clear_buffer();
    printf("\nInserisci %d esami ",n);
    for ( i = 0; i < n; ++i  )
    {
        printf("\nInserisci nome esame :");    
        gets(e[i].nome_esame);
        printf("\nInserisci voto : ");
        scanf("%d", &e[i].voto);
        clear_buffer();
    }    
    
    return n;
}
void visualizza_esami( ESAME e[], int n )
{
    int i;
    
    printf("ESAME\tVOTO\n");
    for ( i = 0; i < n; i++ ) 
        printf("%10s\t%d\n",e[i].nome_esame, e[i].voto);    
    
}

void stampa_verbale( ESAME e[], int n)
{
    int i;
    FILE *fp;
    
    if( ( fp = fopen("verbale.txt", "w") ) == NULL )     
        {
            printf("ERRORE APERTURA DEL FILE!!\n");
            exit(-1);    
            
        }
    for ( i = 0; i < n; i++ ) 
        fprintf(fp, "%10s\t%d\n", e[i].nome_esame, e[i].voto);
        
    fclose(fp);
}
void scambia( ESAME *a, ESAME *b ) 
{
    ESAME temp = *a;
    *a = *b;
    *b = temp;    
    
}
void clear_buffer()
{
  char c;
  
  while ( c != '\n' ) 
        scanf("%c", &c);
     
}

/* Ordina gli esami adoperando l'algoritmo di insertion sort */
void ord_esami( ESAME e[], int n )
{
    int i, j = 0;
    ESAME min;
    int p = 0;
   
    
    for ( i = 1; i < n; i++ ) 
        {
            
            if ( e[i].voto < e[p].voto )
                scambia(&e[i], &e[p]);
             
            
        }
        
    for ( i = 2; i < n; i++ ) 
        {
            j = i; 
            min = e[j];
            
                      
            while ( min.voto < e[j-1].voto  )
                {
                     
                    e[j] = e[j-1];
                    j--;    
                    
                }    
            e[j] = min;
            
            
        }
    
    
}
