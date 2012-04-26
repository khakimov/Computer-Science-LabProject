#ifndef _READWRITEFOO_H
#define _READWRITEFOO_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAXR 100
#define MAXC 100
#define MAXM 50

typedef struct node
{
    float val;
    struct node *next;

}Node;

typedef Node List;



typedef struct Matrice
{
  List* mat;
  int righe;
  int colonne;
  struct Matrice *next;


}matrice;


int leggiRighe( matrice *);
int leggiColonne( matrice * );
float leggiElemento(matrice *, int, int );
void scriviRighe( matrice *, int );
void scriviColonne( matrice *, int );
void scriviElemento( matrice *, int, int, float );
void creaMatrice( matrice *, int, int );
List *nextNode (List *);
List *SetNull( void );
int isSet(List *);
List *getNode( List *, int );
List *setTail( List *, float );

#endif
