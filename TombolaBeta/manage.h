#ifndef __MANAGE_H__
#define __MANAGE_H__

#include "ReadWriteFoo.h"


void fill_cells( Cart_Tab );
int rand_num( void );
void fill_numbers ( int [], int );
void print_cells( Cartella * );
void get_row_col( int, int *, int * );
Cartella *createCartelle( Player * );
void print_cartelle( Player * );
void initGame( ListPlayer *);
int readInteger( void );
Player *initListPlayer( ListPlayer *);
char *getName( Player *);
void cleanBuffer( void );

#endif
