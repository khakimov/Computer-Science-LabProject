/* <------------- Preprocessor useful declaration -------------> */
#ifndef _HEADER_H
#define _HEADER_H

/* <------------- Header file declaration ---------------------> */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <ctype.h>

/* <------------- Macro and costant definition ----------------- > */
#define chomp(x) x[strlen(x)-1] = '\0'

#define MAXR 100
#define MAXC 100
#define FILENAME "result.txt"
#define MAXLEN 512
#define LARGEST 100000000

typedef enum { FALSE, TRUE }boolean;

typedef enum { NOTMN,M, N, MN }selected;

typedef char string[MAXLEN-1];

typedef struct
{
  float **matx;
  int row;
  int col;
  boolean status;

}matrix;



/* <------------- Functions' prototype declaration -------------- > */

selected selectMatrix( matrix, matrix );
void checkStatus( matrix *, matrix *);
int intestazione();
int inizializzazione(string);
matrix inserisciMatrice();
void stampa(matrix, string);
matrix trasposta(matrix);
void free_matrix( matrix );
void salvaValore( float *);
void cleanLine( float *, int, int );
void cleanBuffer();
float *leggi_riga( string, int );
matrix sommaMatrici( matrix, matrix );
matrix prodScalareMatrice( matrix );
matrix diffMatrice( matrix, matrix );
matrix prodvetMatrice(matrix, matrix );
void printFile( matrix, string );
void initDim( matrix *, matrix );

/* < -------------------------------------------------------------------- > */

#endif
