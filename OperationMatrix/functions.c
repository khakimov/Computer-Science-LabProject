#include "header.h"

int intestazione()
{
   int scelta;

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
   while(scanf("%d",&scelta)==0)
   {
     cleanBuffer();
     intestazione();
   }
   cleanBuffer();
   return scelta;
}

void free_matrix( float **mat, int n )
{
    int i;

    for ( i = 0; i < n; i++ )
        free(mat[i]);
    free(mat);
}

int inizializzazione(string a)
{
  int val;
  printf("Inserisci %s matrice: ",a);

  while(scanf("%d",&val)==0)
  {
     cleanBuffer();
     printf("\n**Il numero di %s e' errato**",a);
     printf("\nInserisci %s matrice: ",a);
  }


  return val;


}
float ** inserisciMatrice(int r, int c)
{
    float **array;
    int i,j;
    string buffer;
    float *line;

    array = (float**)malloc(r*sizeof(float*));
    for ( i = 0; i < r; i++ )
        array[i] = (float*)malloc( c * sizeof(float));

    if(array==NULL)
       printf("\n**Memoria Esaurita**");
    printf("\n---Inserisci la matrice---\n");
    cleanBuffer();
    for(i=0;i<r;i++)
    {
        printf("Riga %d: (%d elementi) : ",i+1,c);
        fgets(buffer, MAXLEN, stdin);
        chomp(buffer);
        line = leggi_riga(buffer,c);
        memcpy(array[i], line, sizeof(line)*c);

    }


    controllaMatrice(array, r,c);



    return array;
}
void stampa(float **array,int r,int c,string a)
{
  int i,j;
  printf("\n---Matrice %s---\n",a);
  for(i=0;i < r; printf("\n"),i++)
       for(j=0;j<c;j++)printf("%.3f ",array[i][j]);


}

float ** trasposta(float **matx,int r, int c)
{
  int i,j;
  float **matx_t;

  matx_t = (float**)malloc( c * sizeof(float*));
  for ( i = 0; i < c; i++ )
  {
    matx_t[i] = (float*)malloc( r * sizeof(float));
    if ( !matx_t[i] )
        printf("ERRORE MEMORIA!!!\n");
  }

  for ( i=0; i < c; i++ )
    for ( j = 0; j < r; j++ )
        matx_t[i][j] = matx[j][i];

  return matx_t;

}

float *leggi_riga( string s, int n )
{

    int i = 0;
    float *line;
    int res;
    int n_char;
    string buffer;

    line = (float*)malloc( n * sizeof(float));

    while( i < n ) {
        if ( sscanf(s,"%f%n ", &line[i], &n_char) ) {
            i++, s += n_char;
        } else {
            printf("Valore inserito errato!!\nReinserisci riga : ");
            fgets(s, MAXLEN, stdin);
            chomp(s);

        }
    }
    return line;
}

void cleanBuffer()
{
    while ( getchar() != '\n');
}

void salvaValore( float *f )
{
    int res;

    do
    {
        res = scanf("%f", f);
        if ( res == 0 )
        {
            printf("ERRORE: valore errato!!\n");
            printf("Reinserisci il valore : ");
        }
    }while ( res == 0);

}
void controllaMatrice( float **mat, int r, int c)
{
    int i,j;

    for ( i = 0; i < r; i++ )
        for ( j = 0; j < c; j++ )
            if( isalpha(mat[i][j]) && !isdigit(mat[i][j]) && mat[i][j] > FLT_MAX )
            {
                printf("ERRORE: valore errato!!\nReinserisci il valore : ");
                salvaValore(&mat[i][j]);
            }
}


float **sommaMatrici( float **m, int r, int c, float **n )
{
    float **mpn;
    int i, j;

    mpn = (float**)malloc( r * sizeof(float*));
    if ( !mpn )
        printf("ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for ( i = 0; i < r; i++ )
    {
        mpn[i] = (float*)malloc( c * sizeof(float));
        if ( !mpn[i] )
            printf("ERRORE : MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
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
        printf("ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for ( i = 0; i < r; i++ )
    {
        ma[i] = (float*)malloc( c * sizeof(float));
        if ( !ma[i] )
            printf("ERRORE : MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }

    printf("Inserisci valore scalare : ");
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
       printf("ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for(i=0;i<r;i++)
    {
       md[i]=(float*)malloc(c*sizeof(float));
       if(!md[i])
          printf("ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
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
       printf("ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");

    for(i=0;i<r;i++)
    {
       MpvN[i]=(float*)calloc(c,sizeof(float));
       if(!MpvN[i])
          printf("ERRORE: MEMORIA NON ALLOCATA CORRETTAMENTE!!\n");
    }

    /*
     USANDO CALLOC RISPARMI COMPLETAMENTE QUESTO CICLO!
     for(i=0;i<r;i++)
       for(j=0;j<c;j++)
           MpvN[i][j]=0;
    */
    for(i=0;i<r;i++)
       for(j=0;j<c;j++)
          for(k=0;k<c;k++)
             MpvN[i][j]+=m[i][k]*n[k][j];

    return MpvN;
}
