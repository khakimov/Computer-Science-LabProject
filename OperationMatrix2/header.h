/* <------------- Preprocessor useful declaration -------------> */
#ifndef _HEADER_H
#define _HEADER_H

/* <------------- Header file declaration ---------------------> */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "ReadWriteFoo.h"


/* <------------- Functions' prototype declaration -------------- > */

matrice* initElenco( void );
matrice *reallocMat( matrice *, int );
void overwriteMatrix( matrice *, int );
int intestazione();
matrice inserisciMatrice( int );
void stampaMatrice(matrice, int );
void free_matrix( matrice );
void salvaValore( float *);
void cleanBuffer();
matrice trasposta(matrice);
matrice sommaMatrici( matrice *, int);
matrice prodScalareMatrice( matrice *, int);
matrice diffMatrice( matrice *, int);
matrice prodvetMatrice(matrice *, int);
void initDim( matrice *, matrice );
void allocMatrix( matrice * );
int checkDim( matrice, matrice );
int checkRowCol( matrice , matrice );
void sceltaMatrici(matrice *, int *, int *, int);
int leggiIntero();
void controllaDati( matrice *, int , char  , int *, int *);


/* < -------------------------------------------------------------------- > */

#endif
