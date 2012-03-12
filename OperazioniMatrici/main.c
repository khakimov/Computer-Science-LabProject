/*
    ****************************************
    ****************************************
    ********    MATRIX OPERATION ***********
    ****************************************
    ****************************************

    @authors : Alessandro Suglia & Nazar Chekalin
    @date : 15:23 PM 10/03/2012

*/


#include "header.h"

int main()
{

  float **m=NULL;
  float **n=NULL;
  float **matx_tm=NULL;
  float **matx_tn=NULL;
  int r,c, r1, c1;
  int scelta=1;
  int res;
  float **mpn=NULL;
  float **md=NULL;
  float **mam=NULL;
  float **man=NULL;
  float **MpvN=NULL;
  char matchoice;


  while(scelta)
  {
    scelta=intestazione();
    switch(scelta)
    {
        case 1:
            /* Matrici entrambe non ancora inizializzate */
            if(!m && !n)
            {

                do
                {
                  printf("\nScegli quale matrice inserire ( M/N ) : ");
                  res = scanf("%c",&matchoice);
                  cleanBuffer();

                }
                  while( (matchoice!='m' && matchoice != 'M') && ( matchoice != 'N' && matchoice!='n' ) && res == 1 );

                if(matchoice=='m' || matchoice=='M')
                {

                   r=inizializzazione("righe");
                   c=inizializzazione("colonne");
                   cleanBuffer();
                   m = inserisciMatrice(r,c);
                   printFile(m, r, c, "M");
                   stampa(m,r,c,"M");
                   getch();
                 }

                else
                {
                    r1 = inizializzazione("righe");
                    c1 = inizializzazione("colonne");
                    cleanBuffer();
                    n = inserisciMatrice(r1,c1);
                    stampa(n, r1, c1, "N");
                    getch();
                 }
             }
             else
                if ( !m ) /* M not initialized, create it! */
                {
                    r=inizializzazione("righe");
                   c=inizializzazione("colonne");
                   cleanBuffer();
                   m = inserisciMatrice(r,c);
                   stampa(m,r,c,"M");
                   getch();

                }
            else
                if ( !n ) /* N not initialized, create it */
                 {
                    r1 = inizializzazione("righe");
                    c1 = inizializzazione("colonne");
                    cleanBuffer();
                    n = inserisciMatrice(r1,c1);
                    stampa(n, r1, c1, "N");
                    getch();
                 }

            else /* They're already initialzed, nothing to be done */

            {
                printf("Le Matrici sono già state inizializzate");
                getch();
             }
        break;

        case 2:

        if(m && n) /* Both correctly create, now can I do something with them */
        {

           do
            {
                printf("\nScegli su quale matrice operare ( M/N ) ");
                res = scanf("%c",&matchoice);
                cleanBuffer();

            }while( (matchoice!='m' && matchoice != 'M') && ( matchoice != 'N' && matchoice!='n' ) && res == 1 );

           if(matchoice=='m' || matchoice=='M')
           {
             if(matx_tm==NULL)
               matx_tm=trasposta(m,r,c);

               stampa(matx_tm,c,r,"Trasposta M");
               getch();
           }
             else
             {
               if(matx_tn==NULL)
                  matx_tn=trasposta(n,r1,c1);

               stampa(matx_tn,c1,r1,"Trasposta N");
               getch();
             }
        }
         else
         {
              if(m) /* It's defined only m, so make the trasposition with it */
              {
                   if(matx_tm==NULL)
                      matx_tm=trasposta(m,r,c);

                   stampa(matx_tm,c,r,"Trasposta M");
                   getch();
               }
                else if(n) /* It's defined only n, so make the trasposition with it */
                     {
                      if(matx_tn==NULL)
                         matx_tn=trasposta(n,r1,c1);

                      stampa(matx_tn,c1,r1,"Trasposta N");
                      getch();
                      }
                       else
                       {
                            printf("\nERROR: LE MATRICI NON SONO INIZIALIZZATE!!!");
                            getch();
                       }
          }
        break;

        case 3:
            if  ( (r != r1 && c != c1) || (!m && !n)) /* The matrixs must have the same dimensions to make the sum */
            {
                printf("Matrici nulle oppure di dimensioni differenti!!!");
                if ( m )
                    free_matrix(m, c);
                if ( n )
                    free_matrix(n, c1);
                m=NULL;
                n=NULL;
                r = c = c1 = r1 = 0;
                getch();
            }
            else
            {
                if(mpn==NULL)
                   mpn = sommaMatrici( m, r, c, n);

                stampa( mpn, r, c, "Somma M+N");
                getch();
            }
        break;

        case 4:
            if  ( (r != r1 && c != c1) || (!m && !n)) /* The matrixs must have the same dimensions */
            {
                printf("Matrici nulle oppure di dimensioni differenti!!!");
                  if ( m )
                    free_matrix(m, c);
                if ( n )
                    free_matrix(n, c1);
                m=NULL;
                n=NULL;
                r = c = c1 = r1 = 0;
                getch();
            }
            else
            {
                if(md==NULL)
                   md=diffMatrice(m, r, c, n);

                stampa(md, r, c, "Differenza M-N");
                getch();
            }
        break;

        case 5:

        if(m && n)
        {
           do
           {
                printf("\nScegli matrice sulla quale operare ( M/N ) ");
                res = scanf("%c",&matchoice);
                cleanBuffer();

          }while( (matchoice!='m' && matchoice != 'M') && ( matchoice != 'N' && matchoice!='n' ) && res == 1 );

           if(matchoice=='m' || matchoice=='M')
           {
                if(mam==NULL)
                    mam=prodScalareMatrice(m,r,c);

                stampa(mam,r,c,"Prodotto Scalare M");
                getch();
           }
            else
            {
                if(man==NULL)
                    man=prodScalareMatrice(n,r1,c1);

                stampa(man,r1,c1,"Prodotto Scalare N");
                getch();

            }
        }
        else
         {
              printf("\nERROR: LE MATRICI NON SONO INIZIALIZZATE!!!");
              getch();
         }
        break;

        case 6:
           if ( (c == r1) && (m && n) )
           {
                if(MpvN==NULL)
                    MpvN=prodvetMatrice(m,r,c1,n);

                stampa(MpvN,r,c,"Prodotto Vettoriale MxN");
                getch();
           }
           else
            {
                printf("Colonne diverse tra M e N, oppure Matrici Nulle!!!\n");
                r = c = r = r1 = 0;
                getch();
            }
        break;

        case 7 :
                printf("Matrici Inizializzate nuovamente!\nScegli 1 e ricomincia\n");
                r = c = r = r1 = 0;
                m=NULL;
                n=NULL;
                matx_tm=NULL;
                matx_tn=NULL;
                mpn=NULL;
                md=NULL;
                mam=NULL;
                man=NULL;
                MpvN=NULL;
                getch();
        break;


        case 0:
            if(m)
               free_matrix(m, c);
            if(n)
               free_matrix(n, c1);

            if(matx_tm)
               free_matrix(matx_tm,r);
            if(matx_tn)
               free_matrix(matx_tn,r1);
            if(mpn)
               free_matrix(mpn, c);
            if(md)
               free_matrix(md, c);
            if(mam)
               free_matrix(mam, c);
            if(man)
               free_matrix(man, c1);
            if(MpvN)
               free_matrix(MpvN, c1);


            scelta=0;

        break;
        default :
            printf("Scelta immessa non valida!");
            getch();
        }
    }


  system("PAUSE");
  return 0;







}

