#include "header.h"

int main()
{
  float **m=NULL;
  float **n=NULL;
  float **matx_t;
  int r,c, r1, c1;
  int scelta=1;
  float **mpn;
  float **md;
  float **ma;
  float **MpvN;


  while(scelta)
  {
    scelta=intestazione();
    switch(scelta)
    {
        case 1:
            if(!m)
            {

                r=inizializzazione("righe");
                c=inizializzazione("colonne");
                m = inserisciMatrice(r,c);
                stampa(m,r,c,"M");
                getch();
            }
            else
                 if(!n)
                 {

                    r1 = inizializzazione("righe");
                    c1 = inizializzazione("colonne");
                    n = inserisciMatrice(r1,c1);
                    stampa(n, r1, c1, "N");
                    getch();
                 }
                else
                {
                    printf("Le Matrici sono già state inizializzate");
                    getch();
                }
        break;

        case 2:
           matx_t=trasposta(m,r,c);
           stampa(matx_t,c,r,"Trasposta M");
           free_matrix(matx_t,r);
           getch();
        break;

        case 3:
            if  ( r != r1 && c != c1 )
            {
                printf("ReInserisci le matrici!!\nDevono avere la stessa dimensione!");

                if ( m )
                    free_matrix(m, c);
                if ( n )
                    free_matrix(n, c1);
                r = c = c1 = r1 = 0;
                getch();
            }
            else
            {
                mpn = sommaMatrici( m, r, c, n);
                stampa( mpn, r, c, "Somma M+N");
                free_matrix(mpn, c);
                getch();
            }
        break;

        case 4:
            if  ( r != r1 && c != c1 )
            {
                printf("ReInserisci le matrici!!\nDevono avere la stessa dimensione!");
                  if ( m )
                    free_matrix(m, c);
                if ( n )
                    free_matrix(n, c1);

                r = c = c1 = r1 = 0;
                getch();
            }
            else
            {
                md=diffMatrice(m, r, c, n);
                stampa(md, r, c, "Differenza M-N");
                free_matrix(md, c);
                getch();
            }
        break;

        case 5:
           ma=prodScalareMatrice(m,r,c);
           stampa(ma,r,c,"Prodotto Scalare M");
           free_matrix(ma, c);
           getch();
        break;

        case 6:
           if ( c == r1 )
           {
            MpvN=prodvetMatrice(m,r,c1,n);
            stampa(MpvN,r,c,"Prodotto Vettoriale MxN");
            free_matrix(MpvN, c1);
            getch();
           }
           else
            {
                printf("Le colonne di m devono essere uguale a quelle di n per poter fare il prodotto vettoriale!\nReinserisci una delle due matrici!\n");
                r = c = r = r1 = 0;
                getch();
            }
        break;

        case 7 :
                printf("Matrici Inizializzate nuovamente!\nScegli 1 e ricomincia\n");
                r = c = r = r1 = 0;
                getch();
        break;

        case 0:

            free_matrix( m, c);
            free_matrix(n, c1);
            scelta=0;
        break;
        default :
            printf("Scelta immessa non valida!");
            intestazione();
        }
    }


  system("PAUSE");
  return 0;







}

