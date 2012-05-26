#ifndef __MANAGE_H__
#define __MANAGE_H__

#include "ReadWriteFoo.h"
extern Tombolone tomb;
extern ListPrize premi;

int playGame( ListPlayer *);
void fill_cells( Cart_Tab );
int rand_num( int, int );
void fill_numbers ( int [], int, int );
void print_cells( Cartella * );
void get_row_col( int, int *, int * );
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
void shuffle( int [], int );
void printCartTab( Cart_Tomb );
int checkCartTomb( Cart_Tomb, int );
void setValueTab( Cart_Tomb, int );
void printNumbers( int [], int );

#endif
