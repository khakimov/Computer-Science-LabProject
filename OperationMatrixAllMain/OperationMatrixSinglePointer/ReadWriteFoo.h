#ifndef _READWRITEFOO_H
#define _READWRITEFOO_H

#include <stdlib.h>
#include <stdio.h>

#define MAXR 100
#define MAXC 100
#define MAXM 50

#if defined _WIN32
#define wait() getch()
#elif defined __unix__
#define wait() getchar()
#endif

typedef struct
{
  float *mat;
  int righe;
  int colonne;

}matrice;



int leggiRighe( matrice * );
int leggiColonne( matrice *);
float leggiElemento( matrice *, int, int );
void scriviRighe( matrice *, int );
void scriviColonne( matrice *, int );
void scriviElemento( matrice *, int, int, float );
void creaMatrice( matrice *, int, int );

#endif
