#include "header.h"

void cleanLine( float *line, int start, int end )
{
 int i;

 for( i = start; i < end; line[i] = 0,i++ );


}


/* Useful funtion used to get the option choosen by the user from the command line and print the menu */
int intestazione()
{
   int scelta;
   int ris;


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
          "2 - Trasposta Matrice \n",
          "3 - Somma Matrici\n",
          "4 - Differenza Matrici\n",
          "5 - Prodotto Scalare Matrici\n",
          "6 - Prodotto Vettoriale Matrici\n",
          "7 - Inserisci nuove matrici\n",
          "0 - Esci\n\n");
     printf("Scelta operazione -> ");
     ris=scanf("%d",&scelta);
     cleanBuffer();

   }while(ris==0);


   return scelta;
}

/* Deallocate memory dinamically from the specific double pointer passed to the function */
void free_matrix( matrix m )
{
    int i;

    for ( i = 0; i < m.row; i++ )
        free(m.matx[i]);
    free(m.matx);
}

void checkStatus( matrix *m, matrix *n )
{
    if( m->matx == NULL && n->matx == NULL )
        m->status = FALSE, n->status = FALSE;
    else
    {
        if ( m->matx == NULL )
            m->status = FALSE;
        else
            m->status = TRUE;

        if ( n->matx == NULL )
            n->status = FALSE;
          else
            n->status = TRUE;
    }

}

selected selectMatrix( matrix m, matrix n )
{
    if ( m.status == FALSE && n.status == FALSE )
        return MN;
    else
        if ( m.status == FALSE )
            return M;
    else
        if ( n.status == FALSE )
            return N;
    else
        return NOTMN;
}

void initDim( matrix *dest, matrix src )
{
  dest->row = src.row;
  dest->col = src.col;

}
/* It gets the value of a specific integer data that could be the row number or the column number */
int inizializzazione(string a)
{
  int val;
  int ris;
  string buffer;


  do
  {
     printf("Inserisci %s matrice: ",a);
     ris=scanf("%d",&val);
     scanf("%[^\n]", buffer);
     if(ris==0)
        fprintf(stderr,"\n**Assegnazione valore errata!**\n\n",a);
        else if(val<1 || val>MAXR) fprintf(stderr,"\n**Il numero di %s e' errato (1< %s <100)**\n\n",a,a);

  }while(ris == 0 || (val<1 || val>MAXR));

  scanf("%[^\n]", buffer);
  return val;


}

/*
    Function that receives the number of colomn and the number of row of the matrix,
    and create it asking to the user to fill it inserting each row.
*/
matrix inserisciMatrice( string title )
{
    matrix array;
    int i;
    string buffer; /* Temporary buffer needed to get the line inserted by the user*/
    float *line; /* It was used to save the values inserted by the user */

    printf("%s", title);
    array.row = inizializzazione("righe");
    array.col = inizializzazione("colonne");


    cleanBuffer();

    /* Dynamic allocation of a matrix of (r,c) */
    array.matx = (float**)malloc(array.row*sizeof(float*));
     if(array.matx == NULL)
       fprintf(stderr,"\n**Memoria Esaurita**");

    for ( i = 0; i < array.row; i++ )
    {
        array.matx[i] = (float*)malloc( array.col * sizeof(float));
        if( array.matx[i] == NULL)
            printf("\n**Memoria Esaurita**");
    }

    printf("\n---Inserisci la matrice---\n%s\n",
           "INSERISCI GLI ELEMENTI DI UNA RIGA SEPARANDOLI CON UNO SPAZIO!");
    for(i=0;i< array.row;i++)
    {
        printf("\nRiga %d: (%d elementi) : ",i+1,array.col);
        fgets(buffer, MAXLEN, stdin);
        chomp(buffer);

        if(strlen(buffer)!=0)
        {
            line = leggi_riga(buffer,array.col);
            memcpy(array.matx[i], line, sizeof(float)*array.col);
        }
         else
         {
             fprintf(stderr,"\nATTENZIONE RIGA VUOTA! VALORI AZZERATI\n");
             cleanLine(array.matx[i], 0, array.col);
         }

    }

    array.status = TRUE;
    return array;
}

/* Prints to video the values present in the matrix passed as a parameter */
void stampa( matrix mat,string a)
{
  int i,j;
  printf("\n\t\t ---  Matrice %s  ---\n",a);
  for(i=0;i < mat.row; printf("\n"),i++)
       for(j=0;j< mat.col;j++)
            printf("%15.3f ",mat.matx[i][j]);


}

/*
    Function which make the transposition operation of a
    matrix passed as a parameter.
    It returns a double pointer which points to the current location
    in which the new trasposed matrix will be.
*/
matrix trasposta( matrix mat )
{
  int i,j;
  matrix matx_t;

  matx_t.row = mat.col;
  matx_t.col = mat.row;

  matx_t.matx = (float**)malloc( matx_t.row * sizeof(float*));
  if ( matx_t.matx == NULL )
    printf("ERRORE: MEMORIA INSUFFICIENTE!\n");

  for ( i = 0; i < matx_t.row; i++ )
  {
    matx_t.matx[i] = (float*)malloc( matx_t.col * sizeof(float));
    if ( !matx_t.matx[i] )
        fprintf(stderr,"ERRORE MEMORIA!!!\n");
  }

  for ( i=0; i < matx_t.row; i++ )
    for ( j = 0; j < matx_t.col; j++ )
        matx_t.matx[i][j] = mat.matx[j][i];

   matx_t.status = TRUE;

  return matx_t;

}

/*
    Simple function used to parse the string
    read from the stdin, in which there will be
    the value that must be put in the matrix.
    It returns a float pointer which points to the
    current location in which there is an array of float
    that contains the number present in the row.
*/
float *leggi_riga( string s, int n )
{

    int i = 0;
    float *line;
    int n_char;


    line = (float*)malloc( n * sizeof(float));
    if ( !line )
        printf("ERRORE : MEMORIA INSUFFICIENTE!!\n");

    /* Loop until the number of element of the row was filled*/
    while( i < n )
    {
        /* If the sscanf() correctly parse the string, go ahead in it of n_char location of memory */
        if ( sscanf(s,"%f%n ", &line[i], &n_char) ) {
            if ( line[i] > LARGEST)
            {
                fprintf(stderr, "%s\n%s\n",
                       "E' stato inserito un valore che supera il massimo consentito oppure un valore nullo",
                       "Reinserisci il valore : ");
                salvaValore(&line[i]);
                cleanBuffer();
            }


            i++, s += n_char;


        } else
        {
            /* Some wrong values are present in the line, insert it again*/
            fprintf(stderr,"Valore inserito errato!!\nReinserisci riga : ");

            fgets(s, MAXLEN, stdin);
            chomp(s);
            cleanLine(line,0,n);
            i=0;

        }
    }
    return line;
}

/* Useful function used in order to remove some useless characters present in the buffer */
void cleanBuffer()
{
    while ( getchar() != '\n');
}

/*
    Function that makes some specific control on a float value inserted,
    and only if it is correct, it stores it in a specific location pointed by f.
*/
void salvaValore( float *f )
{
    int res;

    do
    {
        res = scanf("%f", f);
        if ( res == 0 )
        {
            fprintf(stderr,"ERRORE: valore errato!!\n%s",
                   "Reinserisci il valore : ");
        }
    }while ( res == 0);


}


matrix sommaMatrici( matrix m, matrix n )
{
    matrix mpn;
    int i, j;

    initDim( &mpn, m);

    mpn.matx = (float**)malloc( mpn.row * sizeof(float*));
    if ( !mpn.matx )
        fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for ( i = 0; i < mpn.row; i++ )
    {
      mpn.matx[i] = (float*)malloc( mpn.col * sizeof(float));
        if ( !mpn.matx[i] )
            fprintf(stderr,"ERRORE : MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }

    for ( i = 0; i < mpn.row; i++ )
        for ( j = 0; j < mpn.col; j++ )
            mpn.matx[i][j] = m.matx[i][j] + n.matx[i][j];

    mpn.status = TRUE;
    return mpn;
}

matrix prodScalareMatrice( matrix m )
{
    matrix ma;
    float a;
    int i, j;

    initDim( &ma, m);

    ma.matx = (float**)malloc( ma.row * sizeof(float*));
    if ( !ma.matx )
        fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for ( i = 0; i < ma.row; i++ )
    {
        ma.matx[i] = (float*)malloc( ma.col * sizeof(float));
        if ( !ma.matx[i] )
            fprintf(stderr,"ERRORE : MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }

    printf("Inserisci valore scalare di tipo reale : ");
    salvaValore(&a);
    for( i = 0; i < ma.row; i++ )
        for ( j = 0; j < ma.col; j++ )
            ma.matx[i][j] = a*m.matx[i][j];

    ma.status = TRUE;
    return ma;
}

matrix diffMatrice( matrix m, matrix n )
{
    matrix md;
    int i,j;

    initDim( &md, m);
    md.matx =(float**)malloc(md.row*sizeof(float*));
    if(!md.matx)
       fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for( i = 0; i < md.row; i++ )
    {
       md.matx[i]=(float*)malloc( md.col*sizeof(float));
       if(!md.matx[i])
          fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }

    for(i=0;i< md.row;i++)
       for(j=0;j< md.col; j++)
           md.matx[i][j]=m.matx[i][j]-n.matx[i][j];

    md.status = TRUE;
    return md;

}

matrix prodvetMatrice( matrix m, matrix n )
{
    matrix MpvN;
    int i,j,k;

    MpvN.row = m.row;
    MpvN.col = n.col;

    MpvN.matx=(float**)calloc( MpvN.row,sizeof(float*));
    if(!MpvN.matx)
       fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for(i=0;i< MpvN.row;i++)
    {
      MpvN.matx[i]=(float*)calloc( MpvN.col,sizeof(float));
       if(!MpvN.matx[i])
          fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }


    for(i=0;i< MpvN.row;i++)
       for(j=0;j< MpvN.col;j++)
          for(k=0;k< m.col;k++)
	    MpvN.matx[i][j]+=m.matx[i][k]*n.matx[k][j];


    MpvN.status = TRUE;
    return MpvN;
}

void printFile( matrix m, string type )
{
    int i,j;
    FILE *fp;

    if ( ( fp = fopen(FILENAME,"w") ) == NULL )
    {
        perror("ERROR:> ");
        getchar();
        exit(-1);
    }

    fprintf(fp,"Matrice %s\n", type);
    for ( i = 0; i < m.row; fprintf(fp,"\n"),i++ )
      for ( j = 0; j < m.col; j++ )
            fprintf(fp,"%.3f ", m.matx[i][j]);



    fclose(fp);
}
