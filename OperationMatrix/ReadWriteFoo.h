#ifndef _READWRITEFOO_H
#define _READWRITEFOO_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAXR 100
#define MAXC 100
#define MAXM 2

#if defined _WIN32
#define wait() getch()
#elif defined __unix__
#define wait() getchar()
#endif

typedef struct
{
  float **mat;
  int righe;
  int colonne;
  int id;


}matrice;


int leggiRighe( matrice * );
int leggiColonne( matrice *);
void scriviValore( matrice *, int, int );
float leggiValore( matrice *, int, int );
void scriviRighe( matrice * );
void scriviColonne( matrice * );
void scriviElemento( matrice *, int, int, float );

#endif
