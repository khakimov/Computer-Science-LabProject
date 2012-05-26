#ifndef __READWRITEFOO_H__
#define __READWRITEFOO_H__

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_LEN 512

/* Constants that represent the number of cartelle in a Tabellone */
#define TR 3
#define TC 2

/* Constant that represent the max num of row and col of the Tabellone */

#define MAXR 9
#define MAXC 10

/* ------------------------------------------------------------------- */

/* Constant that represent the max num of row and col of a single matrix of Cell type */
#define CTR 3
#define CTC 9

/* --------------------------------------------------------------------------------- */

/* Total number of elements that will be shuffled */
#define TOT_NUM 90

/* Total number of prize */
#define TOT_PRIZE 5

/* Enum variable which grant to understand if a specific number is out or not */
typedef enum { NO, O } is_out;

struct Prize
{
    char *name_prize;
    int prize;
    is_out checked;
    int winner_id;
};


typedef struct Prize ListPrize[TOT_PRIZE];

/* New data type which represent the specific cell in which there is a single number */
typedef struct
{
    int num;
    is_out check;

}Cell;

/* New data type which represent a specific tab */
typedef Cell Card[CTR][CTC];

/*
    New data structure which represent a single table with all the value
    that were contained in it( Cart_Tab cart ) and a specific ID ( int id ).
*/
typedef struct
{
    Card cart;
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

typedef Cell Cart_Tomb[3][5];
typedef Cart_Tomb Tombolone[TR][TC];



//void writeNumCard( Card, int, int, int );
void swapCell( Cell *c1, Cell *c2 );
void ord_row( Cell row[] );
int readNumber( Cartella *, int, int );
int readId( Player *, int );
void writeId( Player *, int, int );
void writeNumber( Player *, int, int, int, int );
int isChecked( struct Prize * );
int isGameFinished( struct Prize * );
void wait ( int );
int readNumberCartTab( Cart_Tomb , int, int );
void gotoxy(int , int );
void writeCheckCard( Cart_Tomb c, int i, int j, is_out flag );
void writeNumCard( Cart_Tomb c, int i, int j, int num );
void getNumCard( Cart_Tomb c, int i, int j, int num );
void getCheckCard( Cart_Tomb c, int i, int j, is_out );

#endif
