/*
    ****************************************
    ****************************************
    ********    MATRIX OPERATION ***********
    ****************************************
    ****************************************

    @authors : Alessandro Suglia & Nazar Chekalin

    Simple program that uses Linked List in order to
    implement some important matrix operation like
    Vectorial Product, Scalar Product, Sum and difference
    between two matrix.

*/

#include "OpMatrix.h"


int main()
{
    matrice *elenco = NULL; /* List of all the matrix that will be used throught the program */
    matrice *curr; /* Pointer to the current matrix */
    matrice *sel_matrix1, *sel_matrix2;
    int cont = 0; /* Integer variable that save the number of matrix that was saved until a defined moment */
    int scelta=1; /* Integer variable that holds the choice inserted by the user */
    List *curr_mat = NULL;
    int res;
    int scelta1, scelta2;
    int row, col;
    float val;
    int ris;
    int i, j;

  while(scelta)
  {
      do
      {
     /*
       Macro preprocessor used in order to
       check the system on which the program was executed
     */
     #if defined _WIN32
            system("cls");
     #elif  defined __unix__
            system("clear");
     #endif
     printf("----------OPERAZIONI MATRICI----------\nPowered by A. Suglia & N. Chekalin\n\n%s%s%s%s%s%s%s%s%s\n",
          "-----------------MENU'----------------\n\n",
          "1 - Inserire Matrice \n",
          "2 - Stampa Matrice \n",
          "3 - Matrice Trasposta\n",
          "4 - Somma Matrici\n",
          "5 - Differenza Matrici\n",
          "6 - Prodotto Scalare Matrici\n",
          "7 - Prodotto Vettoriale Matrici\n",
          "0 - Esci\n\n");
     printf("Scelta operazione -> ");
     ris=scanf("%d",&scelta);
     scanf("%*[^\n]");

    }while(ris==0);

      switch(scelta)
	  {
        case 1:

               if( !elenco )
                {
                    elenco = malloc( sizeof(matrice));
                    if ( !elenco )
                    {
                        fprintf(stderr,"ALLOCATION OF MEMORY FAILED!\n");
                        exit(-1);
                    }

                    do
                    {
                        printf("\nInserisci righe matrice: ");
                        res=scanf("%d",&row);
                        scanf("%*[^\n]");

                        if(res==0)
                            fprintf(stderr,"\n**Assegnazione valore errata!**\n\n");

                        else if( row < 1 || row > MAXR)
                            fprintf(stderr,"\n**Il numero di righe e' errato (1< r < %d)**\n\n",MAXR);

                    } while(res == 0 || ( row < 1 || row > MAXR));

                    scanf("%*[^\n]");
                    do
                    {
                        printf("\nInserisci colonne matrice: ");
                        res=scanf("%d",&col);
                        scanf("%*[^\n]");

                        if(res==0)
                            fprintf(stderr,"\n**Assegnazione valore errata!**\n\n");

                        else if( col < 1 || col > MAXR)
                            fprintf(stderr,"\n**Il numero di righe e' errato (1< r < %d)**\n\n",MAXR);

                    } while(res == 0 || ( col < 1 || col > MAXR));

                    scanf("%*[^\n]");
                    creaMatrice(elenco, row, col);
                    scriviId(elenco, cont);

                    curr_mat = elenco->mat;

                    printf("\n\nInserisci elementi della matrice\n");
                    for ( i = 0; i < leggiRighe(elenco); i++ )
                        for ( j = 0; j < leggiColonne(elenco); j++ )
                        {
                            do
                            {
                                printf("m[%d][%d] = ", i, j);
                                res = scanf("%f", &val);
                                scanf("%*[^\n]");
                                if ( res == 0 || val > FLT_MAX )
                                    printf("Valore inserito non corretto!!Sono ammessi solo valori reali!\n");

                            }while( res == 0 || val > FLT_MAX );

                            scriviElemento(elenco, val);
                        }
                    elenco -> next = NULL;
                    cont++;
                }
                else
                {
                    curr = elenco;

                    while( curr->next != NULL )
                        curr = curr->next;
                    curr->next = malloc(sizeof(matrice));
                    if ( !curr->next )
                    {
                        fprintf(stderr, "ERROR IN ALLOCATION OF MEMORY!\n");
                        exit(-1);
                    }

                    curr = curr->next;

                    curr_mat = curr->mat;

                    do
                    {
                        printf("\nInserisci righe matrice: ");
                        res=scanf("%d",&row);
                        scanf("%*[^\n]");

                        if(res==0)
                            fprintf(stderr,"\n**Assegnazione valore errata!**\n\n");

                        else if( row < 1 || row > MAXR)
                            fprintf(stderr,"\n**Il numero di righe e' errato (1< r < %d)**\n\n",MAXR);

                    } while(res == 0 || ( row < 1 || row > MAXR));

                    scanf("%*[^\n]");
                    do
                    {
                        printf("\nInserisci colonne matrice: ");
                        res=scanf("%d",&col);
                        scanf("%*[^\n]");

                        if(res==0)
                            fprintf(stderr,"\n**Assegnazione valore errata!**\n\n");

                        else if( col < 1 || col > MAXR)
                            fprintf(stderr,"\n**Il numero di righe e' errato (1< r < %d)**\n\n",MAXR);

                    } while(res == 0 || ( col < 1 || col > MAXR));

                    scanf("%*[^\n]");
                    creaMatrice(curr, row, col);
                    scriviId(curr, cont);

                    printf("\n\nInserisci elementi della matrice\n");
                    for ( i = 0; i < leggiRighe(curr); i++ )
                        for ( j = 0; j < leggiColonne(curr); j++ )
                        {
                            do
                            {
                                printf("m[%d][%d] = ", i, j);
                                res = scanf("%f", &val);
                                scanf("%*[^\n]");
                                if ( res == 0 || val > FLT_MAX )
                                    printf("Valore inserito non corretto!!Sono ammessi solo valori reali!\n");

                            }while( res == 0 || val > FLT_MAX );

                            scriviElemento(curr, val);
                        }
                    elenco -> next = NULL;
                    cont++;


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
                        res = scanf("%d",&scelta1);
                        scanf("%*[^\n]");
                        if( res == 0)
                            printf("\nAssegnazione valore errata, reinserisci: ");

                    }while ( res == 0 );
                    if(scelta1 < 0 || scelta1 >= cont)
                        printf("Matrice non esistente!\n");
                }while( scelta1 < 0 || scelta1 >= cont );

                i = 1;
                curr = elenco;
                while( i++ <= scelta1 )
                    curr = curr->next;

                stampaMatrice( curr);
                wait();
            }
             else
             {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }

      break;

     case 3:

         if( cont > 0  )
              {
                    curr = elenco;
                    /* Loop throught the list and allocate memory for the next matrix that will be created */
                    while( curr->next != NULL )
                        curr = curr->next;

                    curr -> next = (matrice*)malloc( sizeof(matrice));
                    if ( !curr->next )
                    {
                        fprintf(stderr,"ALLOCATION OF MEMORY FAILED!\n");
                        exit(-1);

                    }
                    curr = curr -> next;

                    do
                    {
                        printf("Indicare l'ID della matrice sulla quale si intende operare: ");
                        do
                        {
                            res = scanf("%d",&scelta1);
                            scanf("%*[^\n]");
                            if( res == 0)
                                printf("\nAssegnazione valore errata, reinserisci: ");

                        }while ( res == 0 );

                        if(scelta1 < 0 || scelta1 >= cont)
                            printf("Matrice non esistente!\n");
                    }while( scelta1 < 0 || scelta1 >= cont );


                    sel_matrix1 = elenco;
                    i = 0;

                    while( i++ < scelta1 )
                        sel_matrix1 = sel_matrix1->next;


                    creaMatrice(curr, leggiColonne(sel_matrix1), leggiRighe(sel_matrix1));
                    scriviId(curr, cont);

                    trasposta( curr, sel_matrix1);
                    curr -> next = NULL;
                    cont++;
              }
              else
              {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
              }




      break;

      case 4:

              if( cont > 0  )
              {
                    do
                    {
                        printf("Indicare l'ID della matrice sulla quale si intende operare: ");
                        do
                        {
                            res = scanf("%d",&scelta1);
                            scanf("%*[^\n]");
                            if( res == 0)
                                printf("\nAssegnazione valore errata, reinserisci: ");

                        }while ( res == 0 );

                        if(scelta1 < 0 || scelta1 >= cont)
                            printf("Matrice non esistente!\n");
                    }while( scelta1 < 0 || scelta1 >= cont );


                    sel_matrix1 = elenco;
                    i = 0;

                    while( i++ < scelta1 )
                        sel_matrix1 = sel_matrix1->next;

                    do
                    {
                        printf("Indicare l'ID della matrice sulla quale si intende operare: ");
                        do
                        {
                            res = scanf("%d",&scelta2);
                            scanf("%*[^\n]");
                            if( res == 0)
                                printf("\nAssegnazione valore errata, reinserisci: ");

                        }while ( res == 0 );

                        if(scelta2 < 0 || scelta2 >= cont)
                            printf("Matrice non esistente!\n");
                    }while( scelta2 < 0 || scelta2 >= cont );


                    sel_matrix2 = elenco;
                    i = 0;

                    while( i++ < scelta2 )
                        sel_matrix2 = sel_matrix2->next;

                    if ( leggiRighe(sel_matrix1) == leggiRighe(sel_matrix2 ) &&
                         leggiColonne(sel_matrix2 ) == leggiColonne(sel_matrix2 ) )
                    {


                        curr = elenco;
                        /* Loop throught the list and allocate memory for the next matrix that will be created */
                        while( curr->next != NULL )
                            curr = curr->next;

                        curr -> next = (matrice*)malloc( sizeof(matrice));
                        if ( !curr->next )
                        {
                            fprintf(stderr,"ALLOCATION OF MEMORY FAILED!\n");
                            exit(-1);

                        }
                        curr = curr -> next;
                        creaMatrice(curr, leggiRighe(sel_matrix1), leggiColonne(sel_matrix1));
                        scriviId(curr, cont);

                        somma( curr, sel_matrix1, sel_matrix2);
                        curr -> next = NULL;
                        cont++;
                    }
                    else
                    {
                        fprintf(stderr, "%s\n%s\n",
                                "ATTENZIONE, LE MATRICI SELEZIONATE NON HANNO LE MEDESIME DIMENSIONI!",
                                "INSERIRE NUOVE MATRICI DAL MENU' OPPURE SCEGLIERE CON MAGGIOR CURA LE MATRICI GIA' INSERITE!!\n");

                    }


           }
           else

             {
                  fprintf(stderr,"NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }
	  break;

	case 5:

	       if( cont > 0  )
              {
                    do
                    {
                        printf("Indicare l'ID della matrice sulla quale si intende operare: ");
                        do
                        {
                            res = scanf("%d",&scelta1);
                            scanf("%*[^\n]");
                            if( res == 0)
                                printf("\nAssegnazione valore errata, reinserisci: ");

                        }while ( res == 0 );

                        if(scelta1 < 0 || scelta1 >= cont)
                            printf("Matrice non esistente!\n");
                    }while( scelta1 < 0 || scelta1 >= cont );


                    sel_matrix1 = elenco;
                    i = 0;

                    while( i++ < scelta1 )
                        sel_matrix1 = sel_matrix1->next;

                    do
                    {
                        printf("Indicare l'ID della matrice sulla quale si intende operare: ");
                        do
                        {
                            res = scanf("%d",&scelta2);
                            scanf("%*[^\n]");
                            if( res == 0)
                                printf("\nAssegnazione valore errata, reinserisci: ");

                        }while ( res == 0 );

                        if(scelta2 < 0 || scelta2 >= cont)
                            printf("Matrice non esistente!\n");
                    }while( scelta2 < 0 || scelta2 >= cont );


                    sel_matrix2 = elenco;
                    i = 0;

                    while( i++ < scelta2 )
                        sel_matrix2 = sel_matrix2->next;

                    if ( leggiRighe(sel_matrix1) == leggiRighe(sel_matrix2 ) &&
                         leggiColonne(sel_matrix2 ) == leggiColonne(sel_matrix2 ) )
                    {


                        curr = elenco;
                        /* Loop throught the list and allocate memory for the next matrix that will be created */
                        while( curr->next != NULL )
                            curr = curr->next;

                        curr -> next = (matrice*)malloc( sizeof(matrice));
                        if ( !curr->next )
                        {
                            fprintf(stderr,"ALLOCATION OF MEMORY FAILED!\n");
                            exit(-1);

                        }
                        curr = curr -> next;
                        creaMatrice(curr, leggiRighe(sel_matrix1), leggiColonne(sel_matrix1));
                        scriviId(curr, cont);

                        differenza( curr, sel_matrix1, sel_matrix2);
                        curr -> next = NULL;
                        cont++;
                    }
                    else
                    {
                        fprintf(stderr, "%s\n%s\n",
                                "ATTENZIONE, LE MATRICI SELEZIONATE NON HANNO LE MEDESIME DIMENSIONI!",
                                "INSERIRE NUOVE MATRICI DAL MENU' OPPURE SCEGLIERE CON MAGGIOR CURA LE MATRICI GIA' INSERITE!!\n");

                    }


           }
           else

             {
                  fprintf(stderr,"NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }

	  break;

	case 6 :

	        if( cont > 0  )
              {
                    curr = elenco;
                    /* Loop throught the list and allocate memory for the next matrix that will be created */
                    while( curr->next != NULL )
                        curr = curr->next;

                    curr -> next = (matrice*)malloc( sizeof(matrice));
                    if ( !curr->next )
                    {
                        fprintf(stderr,"ALLOCATION OF MEMORY FAILED!\n");
                        exit(-1);

                    }
                    curr = curr -> next;

                    do
                    {
                        printf("Indicare l'ID della matrice sulla quale si intende operare: ");
                        do
                        {
                            res = scanf("%d",&scelta1);
                            scanf("%*[^\n]");
                            if( res == 0)
                                printf("\nAssegnazione valore errata, reinserisci: ");

                        }while ( res == 0 );

                        if(scelta1 < 0 || scelta1 >= cont)
                            printf("Matrice non esistente!\n");
                    }while( scelta1 < 0 || scelta1 >= cont );


                    sel_matrix1 = elenco;
                    i = 0;

                    while( i++ < scelta1 )
                        sel_matrix1 = sel_matrix1->next;

                    do
                    {
                        res = scanf("%f", &val);
                        if ( res == 0 )
                        {
                            fprintf(stderr,"ERRORE: valore errato!!\n%s",
                                    "Reinserisci il valore : ");
                        }
                        scanf("%*[^\n]");

                    } while ( res == 0);

                    creaMatrice(curr, leggiRighe(sel_matrix1), leggiColonne(sel_matrix1));
                    scriviId(curr, cont);

                    scalare( curr, sel_matrix1, val);
                    curr -> next = NULL;
                    cont++;
              }
              else
              {
                  printf("NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
              }
	break;

	case 7 :

           if( cont > 0  )
              {
                    do
                    {
                        printf("Indicare l'ID della matrice sulla quale si intende operare: ");
                        do
                        {
                            res = scanf("%d",&scelta1);
                            scanf("%*[^\n]");
                            if( res == 0)
                                printf("\nAssegnazione valore errata, reinserisci: ");

                        }while ( res == 0 );

                        if(scelta1 < 0 || scelta1 >= cont)
                            printf("Matrice non esistente!\n");
                    }while( scelta1 < 0 || scelta1 >= cont );


                    sel_matrix1 = elenco;
                    i = 0;

                    while( i++ < scelta1 )
                        sel_matrix1 = sel_matrix1->next;

                    do
                    {
                        printf("Indicare l'ID della matrice sulla quale si intende operare: ");
                        do
                        {
                            res = scanf("%d",&scelta2);
                            scanf("%*[^\n]");
                            if( res == 0)
                                printf("\nAssegnazione valore errata, reinserisci: ");

                        }while ( res == 0 );

                        if(scelta2 < 0 || scelta2 >= cont)
                            printf("Matrice non esistente!\n");
                    }while( scelta2 < 0 || scelta2 >= cont );


                    sel_matrix2 = elenco;
                    i = 0;

                    while( i++ < scelta2 )
                        sel_matrix2 = sel_matrix2->next;

                    if ( leggiColonne(sel_matrix1) == leggiRighe(sel_matrix2) )
                    {


                        curr = elenco;
                        /* Loop throught the list and allocate memory for the next matrix that will be created */
                        while( curr->next != NULL )
                            curr = curr->next;

                        curr -> next = (matrice*)malloc( sizeof(matrice));
                        if ( !curr->next )
                        {
                            fprintf(stderr,"ALLOCATION OF MEMORY FAILED!\n");
                            exit(-1);

                        }
                        curr = curr -> next;
                        creaMatrice(curr, leggiRighe(sel_matrix1), leggiColonne(sel_matrix2));
                        scriviId(curr, cont);

                        prodotto( curr, sel_matrix1, sel_matrix2);
                        curr -> next = NULL;
                        cont++;
                    }
                    else
                    {
                        fprintf(stderr, "%s\n%s\n",
                                "ATTENZIONE, LE MATRICI SELEZIONATE NON HANNO LE MEDESIME DIMENSIONI!",
                                "INSERIRE NUOVE MATRICI DAL MENU' OPPURE SCEGLIERE CON MAGGIOR CURA LE MATRICI GIA' INSERITE!!\n");

                    }


           }
           else

             {
                  fprintf(stderr,"NESSUNA MATRICE INSERITA...OPERAZIONE NON VALIDA\nSELEZIONARE IL PUNTO 1 DEL MENU' PER UNA NUOVA INIZIALIZZAZIONE!\n");
                  wait();
             }


	break;

    case 0:


	  scelta=0;
	  if(elenco)
        free(elenco);

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

