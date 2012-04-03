/* <------------- Preprocessor useful declaration -------------> */
#ifndef _OPMATRIX_H
#define _OPMATRIX_H

/* <------------- Header file declaration ---------------------> */
#include "ReadWriteFoo.h"


/* <------------- Functions' prototype declaration -------------- > */

matrice* initElenco( void );
matrice *reallocMat( matrice *, int );
int overwriteMatrix( matrice *, int );
int intestazione();
matrice inserisciMatrice( int );
void stampaMatrice(matrice *, int );
void free_matrix( matrice *);
void salvaValore( float *);
void cleanBuffer();
matrice trasposta(matrice *, int);
matrice sommaMatrici( matrice *, int);
matrice prodScalareMatrice( matrice *, int);
matrice diffMatrice( matrice *, int);
matrice prodvetMatrice(matrice *, int);
void initDim( matrice *, matrice );
void allocMatrix( matrice * );
int checkDim( matrice, matrice );
int checkRowCol( matrice , matrice );
void sceltaMatrici(int *, int *, int);
int leggiIntero();
void controllaDati( matrice *, int , char  , int *, int *);
matrice *cercaMatrice (matrice *, int );
matrice* allocMatrice ();


/* < -------------------------------------------------------------------- > */

#endif
