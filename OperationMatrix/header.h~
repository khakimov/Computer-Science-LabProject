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

typedef char string[MAXLEN];

/* <------------- Functions' prototype declaration -------------- > */
int intestazione();
int inizializzazione(string);
float ** inserisciMatrice(int,int);
void stampa(float **,int ,int, string);
float ** trasposta(float **,int, int);
void free_matrix( float **, int );
void salvaValore( float *);
void cleanLine( float *, int, int );
void cleanBuffer();
float *leggi_riga( string, int );
float **sommaMatrici( float **, int, int, float ** );
float **prodScalareMatrice( float **, int, int );
float **diffMatrice(float **, int , int , float **);
float **prodvetMatrice(float **,int , int , int,  float **);
void printFile( float **, int, int, string );

/* < -------------------------------------------------------------------- > */

#endif
