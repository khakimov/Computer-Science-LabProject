#ifndef _READWRITEFOO_H
#define _READWRITEFOO_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define MAXR 100
#define MAXC 100
#define MAXM 50

#define MAT_FILENAME "matrix.txt"

typedef struct node
{
    float val;
    struct node *nextCol;
    struct node *nextRow;

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
void leggiMatriceDaFile( FILE *, matrice * );
void stampaMatriceSuFile( FILE *, matrice * );
List *nextRow (List *);
List *nextCol (List *);
List *SetNull( void );
int isSet(List *);
List *getNode( List *, int , int );
List *setTail( List *, int, int, float );

#endif
