#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>

#define chomp(x) x[strlen(x)-1] = '\0'

#define MAXR 100
#define MAXC 100

#define MAXLEN 512
typedef char string[MAXLEN];

int intestazione();
int inizializzazione(string);
float ** inserisciMatrice(int,int);
void stampa(float **,int ,int, string);
float ** trasposta(float **,int, int);
void free_matrix( float **, int );
void salvaValore( float *);
void controllaMatrice( float **, int , int );
void cleanBuffer();
float *leggi_riga( string, int );
float **sommaMatrici( float **, int, int, float ** );
float **prodScalareMatrice( float **, int, int );
float **diffMatrice(float **, int , int , float **);
float **prodvetMatrice(float **,int , int , float **);
#endif
