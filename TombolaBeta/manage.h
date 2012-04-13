#ifndef __MANAGE_H__
#define __MANAGE_H__


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_LEN 512

/* Constant that represent the max num of row and col of the Tabellone */

#define MAXR 3
#define MAXC 2

/* ------------------------------------------------------------------- */

/* Constant that represent the max num of row and col of a single matrix of Cell type */
#define CTR 3
#define CTC 5

/* --------------------------------------------------------------------------------- */

/* Total number of elements that will be shuffled */
#define TOT_NUM 90

/* Enum variable which grant to understand if a specific number is out or not */
typedef enum { NO, O } is_out;

/* New data type which represent the specific cell in which there is a single number */
typedef struct
{
    int num;
    is_out check;

}Cell;

/* New data type which represent a specific tab */
typedef Cell Cart_Tab[CTR][CTC];

/*
    New data structure which represent a single table with all the value
    that were contained in it( Cart_Tab cart ) and a specific ID ( int id ).
*/
typedef struct
{
    Cart_Tab cart;
    int id;

}Cartella;

/*
    Player data structure which represent a specific player
    which have a n_cart number of tabels represented by the
    pointer to Cartella and a specific name of the player
    that will be associate when the game starts.
*/
typedef struct
{
    char *name_player;
    Cartella *cartelle;
    int n_cart;

}Player;

/*
    A list of all the player that are actually in game.
*/
typedef struct
{
    Player *list_player;
    int n_player;
}ListPlayer;


/* A new type of matrix which represent the scheme thanks to we manage the game */
//typedef Cart_tab Tabellone[MAXR][MAXC];

void fill_cells( Cart_Tab );
int rand_num( void );
void fill_numbers ( int [], int );
void print_cells( Cartella * );
void get_row_col( int, int *, int * );
Cartella *createCartelle( Player * );
void initGame( ListPlayer *);
int readInteger( void );
Player *initListPlayer( ListPlayer *players );
char *getName( Player *);
void cleanBuffer( void );

#endif
