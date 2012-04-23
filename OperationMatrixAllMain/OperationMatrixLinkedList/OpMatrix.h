/* <------------- Preprocessor useful declaration -------------> */
#ifndef _OPMATRIX_H
#define _OPMATRIX_H

/* <------------- Header file declaration ---------------------> */
#include "ReadWriteFoo.h"


/* <------------- Functions' prototype declaration -------------- > */

void stampaMatrice( matrice * );
matrice *trasposta( matrice *, matrice *);
matrice *somma( matrice *, matrice *, matrice * );
matrice *differenza( matrice *, matrice *, matrice * );
matrice *scalare( matrice *, matrice *, float );
matrice *prodotto( matrice *, matrice *, matrice * );

/* < -------------------------------------------------------------------- > */

#endif
