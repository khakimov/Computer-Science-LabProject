#ifndef __MANAGE_H__
#define __MANAGE_H__

#include "ReadWriteFoo.h"
#include "CardManager.h"

extern Tombolone tomb;
extern ListPrize premi;


int extractNumber( void );
int playGame( ListPlayer *);
void print_cells( Cartella * );
Cartella *createCartelle( Player * );
void print_cartelle( Player * );
void initGame( ListPlayer *);
int readInteger( void );
Player *initListPlayer( ListPlayer *);
char *getName( Player *);
void cleanBuffer( void );
void initTombolone( Tombolone );
void printTombolone( Tombolone );
void banner( void );
void checkValue( ListPlayer *, int );
void setValue( Cartella *, int );
void checkPrize( ListPlayer *);
void printPrize( int, Player *, int );
int checkCartella( Cartella *, int  );

void printCartTab( Cart_Tomb );
int checkCartTomb( Cart_Tomb, int );
void setValueTab( Cart_Tomb, int );
void printNumbers( int [], int );

#endif
