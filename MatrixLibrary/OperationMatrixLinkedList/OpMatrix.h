/* <------------- Preprocessor useful declaration -------------> */
#ifndef _OPMATRIX_H
#define _OPMATRIX_H

/* <------------- Header file declaration ---------------------> */
#include "ReadWriteFoo.h"


/* <------------- Functions' prototype declaration -------------- > */

void stampaMatrice( matrice * );
void trasposta( matrice *, matrice *);
void somma( matrice *, matrice *, matrice * );
void differenza( matrice *, matrice *, matrice * );
void scalare( matrice *, matrice *, float );
void prodotto( matrice *, matrice *, matrice * );

/* < -------------------------------------------------------------------- > */

#endif
