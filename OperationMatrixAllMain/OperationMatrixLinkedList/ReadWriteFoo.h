#ifndef _READWRITEFOO_H
#define _READWRITEFOO_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>

#define MAXR 100
#define MAXC 100
#define MAXM 50

#define val_access( i, n, j) ( i * n + j )


/*
#if defined _WIN32
#define wait() getch()
#elif defined __unix__
#define wait() getchar()
#endif
*/

#define wait() { clock_t end_wait = clock() + 2 * CLOCKS_PER_SEC; while( clock() < end_wait ); }

struct Node
{
    float val;
    struct Node *next;

};

typedef struct Node List;



struct Matrice
{
  List* mat;
  int righe;
  int colonne;
  int id;
  struct Matrice *next;


};
typedef struct Matrice matrice;


int leggiRighe( matrice *);
int leggiColonne( matrice * );
float leggiElemento( matrice *, int, int);
void scriviRighe( matrice *, int );
void scriviColonne( matrice *, int );
void scriviElemento( matrice *, float );
void scriviId( matrice *, int );
int leggiId( matrice * );
void creaMatrice( matrice *, int, int );

#endif
