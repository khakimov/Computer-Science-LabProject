#include "header.h"

/* Useful funtion used to get the option choosen by the user from the command line and print the menu */
int intestazione()
{
   int scelta;
   int ris;


   do
   {
     system("cls");
     printf("---OPERAZIONI MATRICI---\nPowered by A. Suglia & N. Chekalin\n\n%s%s%s%s%s%s%s%s\n",
          "1 - Inserire Matrice \n",
          "2 - Trasposta Matrice \n",
          "3 - Somma Matrici\n",
          "4 - Differenza Matrici\n",
          "5 - Prodotto Scalare Matrici\n",
          "6 - Prodotto Vettoriale Matrici\n",
          "7 - Inserisci nuove matrici\n",
          "0 - Esci\n\n");
     printf("Scelta-> ");
     ris=scanf("%d",&scelta);
     cleanBuffer();

   }while(ris==0);


   return scelta;
}

/* Deallocate memory dinamically from the specific double pointer passed to the function */
void free_matrix( float **mat, int n )
{
    int i;

    for ( i = 0; i < n; i++ )
        free(mat[i]);
    free(mat);
}

/* It gets the value of a specific integer data that could be the row number or the column number */
int inizializzazione(string a)
{
  int val;
  int ris;


  do
  {
     printf("Inserisci %s matrice: ",a);
     ris=scanf("%d",&val);
     scanf("%[^\n]");
     if(ris==0)
        fprintf(stderr,"\n**Assegnazione valore errata!**\n\n",a);
        else if(val<1 || val>MAXR) fprintf(stderr,"\n**Il numero di %s e' errato (1< %s <100)**\n\n",a,a);

  }while(ris == 0 || (val<1 || val>MAXR));



  return val;


}

/*
    Function that receives the number of colomn and the number of row of the matrix,
    and create it asking to the user to fill it inserting each row.
*/
float ** inserisciMatrice(int r, int c)
{
    float **array;
    int i,j;
    string buffer; /* Temporary buffer needed to get the line inserted by the user*/
    float *line; /* It was used to save the values inserted by the user */

    /* Dynamic allocation of a matrix of (r,c) */
    array = (float**)malloc(r*sizeof(float*));
     if(array==NULL)
       fprintf(stderr,"\n**Memoria Esaurita**");

    for ( i = 0; i < r; i++ )
    {
        array[i] = (float*)malloc( c * sizeof(float));
        if( array[i] == NULL)
            printf("\n**Memoria Esaurita**");
    }

    printf("\n---Inserisci la matrice---\n%s\n",
           "INSERISCI GLI ELEMENTI DI UNA RIGA SEPARANDOLI CON UNO SPAZIO!");
    for(i=0;i<r;i++)
    {
        printf("\nRiga %d: (%d elementi) : ",i+1,c);
        fgets(buffer, MAXLEN, stdin);
        chomp(buffer);

        if(strlen(buffer)!=0)
        {
            line = leggi_riga(buffer,c);
            memcpy(array[i], line, sizeof(line)*c);
        }
         else
         {
             fprintf(stderr,"\nATTENZIONE RIGA VUOTA! VALORI AZZERATI\n");
             memset(array[i], 0, c);
         }

    }

    return array;
}

/* Prints to video the values present in the matrix passed as a parameter */
void stampa(float **array,int r,int c,string a)
{
  int i,j;
  printf("\n---Matrice %s---\n",a);
  for(i=0;i < r; printf("\n"),i++)
       for(j=0;j<c;j++)
            printf("%.3f ",array[i][j]);


}

/*
    Function which make the transposition operation of a
    matrix passed as a parameter.
    It returns a double pointer which points to the current location
    in which the new trasposed matrix will be.
*/
float ** trasposta(float **matx,int r, int c)
{
  int i,j;
  float **matx_t;

  matx_t = (float**)malloc( c * sizeof(float*));
  if ( matx_t == NULL )
    printf("ERRORE: MEMORIA INSUFFICIENTE!\n");

  for ( i = 0; i < c; i++ )
  {
    matx_t[i] = (float*)malloc( r * sizeof(float));
    if ( !matx_t[i] )
        fprintf(stderr,"ERRORE MEMORIA!!!\n");
  }

  for ( i=0; i < c; i++ )
    for ( j = 0; j < r; j++ )
        matx_t[i][j] = matx[j][i];

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
            if ( line[i] > LARGEST )
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
            for(i=0;i<n;i++) line[i]=0;
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


float **sommaMatrici( float **m, int r, int c, float **n )
{
    float **mpn;
    int i, j;

    mpn = (float**)malloc( r * sizeof(float*));
    if ( !mpn )
        fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for ( i = 0; i < r; i++ )
    {
        mpn[i] = (float*)malloc( c * sizeof(float));
        if ( !mpn[i] )
            fprintf(stderr,"ERRORE : MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }

    for ( i = 0; i < r; i++ )
        for ( j = 0; j < c; j++ )
            mpn[i][j] = m[i][j] + n[i][j];

    return mpn;
}

float **prodScalareMatrice( float **m, int r, int c )
{
    float **ma;
    float a;
    int i, j;

    ma = (float**)malloc( r * sizeof(float*));
    if ( !ma )
        fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for ( i = 0; i < r; i++ )
    {
        ma[i] = (float*)malloc( c * sizeof(float));
        if ( !ma[i] )
            fprintf(stderr,"ERRORE : MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }

    printf("Inserisci valore scalare di tipo reale : ");
    salvaValore(&a);
    for( i = 0; i < r; i++ )
        for ( j = 0; j < c; j++ )
            ma[i][j] = a*m[i][j];

    return ma;
}
float **diffMatrice(float **m, int r, int c, float **n)
{
    float **md;
    int i,j;

    md=(float**)malloc(r*sizeof(float*));
    if(!md)
       fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for(i=0;i<r;i++)
    {
       md[i]=(float*)malloc(c*sizeof(float));
       if(!md[i])
          fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }

    for(i=0;i<r;i++)
       for(j=0;j<c;j++)
           md[i][j]=m[i][j]-n[i][j];

    return md;

}
float **prodvetMatrice(float **m,int r, int c, float **n)
{
    float **MpvN;
    int i,j,k;

    MpvN=(float**)calloc(r,sizeof(float*));
    if(!MpvN)
       fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for(i=0;i<r;i++)
    {
       MpvN[i]=(float*)calloc(c,sizeof(float));
       if(!MpvN[i])
          fprintf(stderr,"ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }


    for(i=0;i<r;i++)
       for(j=0;j<c;j++)
          for(k=0;k<c;k++)
             MpvN[i][j]+=m[i][k]*n[k][j];

    return MpvN;
}

void printFile( float **mat, int r, int c, string type )
{
    int i,j;
    FILE *fp;

    if ( ( fp = fopen(FILENAME,"w") ) == NULL )
    {
        perror("ERROR:> ");
        getch();
        exit(-1);
    }

    fprintf(fp,"Matrice %s\n", type);
    for ( i = 0; i < r; fprintf(fp,"\n"),i++ )
        for ( j = 0; j < c; j++ )
            fprintf(fp,"%.3f ", mat[i][j]);



    fclose(fp);
}
