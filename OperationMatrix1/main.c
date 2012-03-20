/*
    ****************************************
    ****************************************
    ********    MATRIX OPERATION ***********
    ****************************************
    ****************************************

    @authors : Alessandro Suglia & Nazar Chekalin


*/
#if defined _WIN32
#define wait() getch()
#elif defined __unix__
#define wait() getchar()
#endif

#include "header.h"

int main()
{

  matrix m = { NULL, 0, 0, FALSE}; /* First matrix */
  matrix n = { NULL, 0, 0, FALSE }; /* Secondo matrix */
  matrix matx_tm = { NULL, 0, 0, FALSE }; /* M's transposed matrix */
  matrix matx_tn = { NULL, 0, 0, FALSE }; /* N's transposed matrix */

  int scelta=1;
  int res;
  matrix mpn = { NULL, 0, 0, FALSE }; /* Matrix resulting from the sum of the M matrix and the N matrix */
  matrix md = { NULL, 0, 0, FALSE };  /* Matrix resulting from the difference between the two matrix */
  matrix mam = { NULL, 0, 0, FALSE }; /* Matrix create for the scalar product of each M's value and a scalar value */
  matrix man = { NULL, 0, 0, FALSE }; /* Matrix create for the scalar product of each N's value and a scalar value */
  matrix MpvN = { NULL, 0, 0, FALSE }; /* Vectorial product between the two matrix */
  char matchoice; /* variable used in order to get the choice inserted by the user */


  while(scelta)
  {
      scelta=intestazione();

      switch(scelta)
	  {
        case 1:
	  /* Matrici entrambe non ancora inizializzate */
         checkStatus(&m, &n);

	     if(  selectMatrix(m,n) == MN )
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
           m = inserisciMatrice("\n----Matrice M----\n");

		   printFile(m, "M");
		   stampa(m,"M");
		   wait();
		}

        else
		{
            n = inserisciMatrice("\n----Matrice N----\n");

            stampa(n, "N");
            wait();
	    }
      }
	  else
          if ( selectMatrix(m,n) == M ) /* M not initialized, create it! */
		  {
                m = inserisciMatrice("\n----Matrice M----\n");

                printFile(m, "M");
                stampa(m,"M");
                wait();
		  }
		else
		  if ( selectMatrix(m,n) == N ) /* N not initialized, create it */
		    {
                n = inserisciMatrice("\n----Matrice N----\n");
                stampa(n, "N");
                wait();

		    }

		  else /* They're already initialzed, nothing to be done */
		    {
		      printf("Le Matrici sono già state inizializzate");
		      wait();
		    }
	  break;

        case 2:
        checkStatus(&m, &n);

	  if( useMatrix(m,n) == MN) /* Both correctly create, now can I do something with them */
      {

	      do
		  {
		     printf("\nScegli su quale matrice operare ( M/N ) ");
		     res = scanf("%c",&matchoice);
		     cleanBuffer();

		  }while( (matchoice!='m' && matchoice != 'M') && ( matchoice != 'N' && matchoice!='n' ) && res == 1 );

	      if(matchoice=='m' || matchoice=='M')
		  {

		    if( matx_tm.status == FALSE )
		      matx_tm=trasposta( m );

            stampa(matx_tm,"Trasposta M");
            wait();
		   }
	      else
		  {
		    if( matx_tn.status == FALSE )
		      matx_tn=trasposta(n);

		    stampa(matx_tn,"Trasposta N");
		    wait();
		  }
     }
	 else
	 {
	     checkStatus(&m, &n);
        if(m.status == TRUE) /* It's defined only m, so make the trasposition with it */
		{
		  if( matx_tm.status == FALSE )
		    matx_tm=trasposta(m);

		  stampa(matx_tm,"Trasposta M");
		  wait();
		}
	    else if( n.status == TRUE) /* It's defined only n, so make the trasposition with it */
		{
		  if(matx_tn.status == FALSE )
		    matx_tn=trasposta(n);

		  stampa(matx_tn,"Trasposta N");
		  wait();
		}
	    else
		{
		  fprintf(stderr,"\nERROR: LE MATRICI NON SONO INIZIALIZZATE!!!");
		  wait();
		}
	 }
	 break;

     case 3:
      checkStatus(&m, &n);
	  if  ( (m.row != n.row || m.col != n.col) || ( m.status == FALSE && n.status == FALSE )) /* The matrixs must have the same dimensions to make the sum */
      {
	     fprintf(stderr,"Attenzione!!! Matrici NULLE oppure di dimensioni DIFFERENTI!\nReinserisci le matrici!!\n");
	      if ( m.status == TRUE )
            free_matrix(m);
	      if ( n.status == TRUE )
            free_matrix(n);
	      m.matx=NULL;
	      n.matx=NULL;
	      m.row = m.col = n.col = n.row = 0;
	      wait();
     }
	 else
     {
	   if( mpn.status == FALSE)
         mpn = sommaMatrici( m, n);

	   stampa( mpn, "Somma M+N");
	   wait();
     }
     break;

     case 4:
	  checkStatus(&m, &n);
	  if  ( (m.row != n.row || m.col != n.col) || ( m.status == FALSE && n.status == FALSE ) ) /* The matrixs must have the same dimensions */
      {
	      fprintf(stderr,"Attenzione!!! Matrici NULLE oppure di dimensioni DIFFERENTI!\nReinserisci le matrici!!\n");
	      if ( m.status == TRUE )
		    free_matrix(m);
	      if ( n.status == TRUE )
	         free_matrix(n);

          m.matx=NULL;
	      n.matx=NULL;
	      m.row = m.col = n.col = n.row = 0;
	      wait();
      }
	  else
      {
	      if(md.status == FALSE )
             md=diffMatrice(m, n);

	      stampa(md, "Differenza M-N");
	      wait();
      }
      break;

      case 5:
        checkStatus(&m, &n);


        if( useMatrix(m,n) == MN )
	    {
	       do
		   {
		      printf("\nScegli matrice sulla quale operare ( M/N ) ");
		      res = scanf("%c",&matchoice);

		      cleanBuffer();

           }while( (matchoice!='m' && matchoice != 'M') && ( matchoice != 'N' && matchoice!='n' ) && res == 1 );

	      if(matchoice=='m' || matchoice=='M')
		  {

		     if( mam.status == FALSE )
		       mam=prodScalareMatrice(m);

		     stampa(mam,"Prodotto Scalare M");
		     cleanBuffer();
		  }
	      else
		  {

		     if( man.status == FALSE )
               man=prodScalareMatrice(n);

             stampa(man,"Prodotto Scalare N");
		     wait();

		  }
	    }
	  else
        if( useMatrix(m,n) == M )
	    {
            if( mam.status==FALSE)
                mam=prodScalareMatrice(m);

            stampa(mam,"Prodotto Scalare M");
            wait();

        }
	    else if( useMatrix(m, n) == N )
	    {
            if( man.status == FALSE)
                man=prodScalareMatrice(n);

            stampa(man,"Prodotto Scalare N");
            wait();

	    }
	    else
	    {
            fprintf(stderr,"\nERROR: LE MATRICI NON SONO INIZIALIZZATE!!!");
            wait();
	    }
	  break;

	case 6:
	  checkStatus(&m, &n);
	  if ( ( m.col == n.row) && ( useMatrix(m,n) == MN ) )
	  {
	      if( MpvN.status == FALSE)
		    MpvN=prodvetMatrice(m,n);

	      stampa(MpvN,"Prodotto Vettoriale MxN");
	      wait();
      }
	  else
	  {
	      fprintf(stderr,"%s\n%s\n",
                  "Attenzione!!! Matrici NULLE oppure di dimensioni INCOMPATIBILI!",
                  "Premi 7 per reinizializzare e poi reinserisci le matrici premendo 1!");
	      n.col = m.col = m.row = n.row = 0;
	      wait();
	  }
	  break;

	case 7 :
	  printf("Matrici Inizializzate nuovamente!\nScegli 1 e ricomincia\n");
	   n.col = m.col = m.row = n.row = 0;
	  /* Reinitialization of all the pointer used into all the program */
      m.matx = NULL;
	  n.matx = NULL;
	  matx_tm.matx = NULL;
	  matx_tn.matx = NULL;
	  mpn.matx = NULL;
	  md.matx = NULL;
	  mam.matx = NULL;
	  man.matx = NULL;
	  MpvN.matx = NULL;
	  wait();
	break;


   case 0:
	  if( m.status == TRUE )
	    free_matrix( m );
	  if( n.status == TRUE )
	    free_matrix( n );

	  if( matx_tm.status == TRUE )
	    free_matrix(matx_tm);
	  if( matx_tn.status == TRUE )
	    free_matrix( matx_tn );
	  if( mpn.status == TRUE )
	    free_matrix( mpn );
	  if( md.status == TRUE )
	    free_matrix( md );
	  if( mam.status == TRUE )
	    free_matrix( mam );
	  if( man.status == TRUE )
	    free_matrix( man );
	  if( MpvN.status == TRUE )
	    free_matrix(MpvN);


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

