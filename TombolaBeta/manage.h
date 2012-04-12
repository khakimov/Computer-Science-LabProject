#ifndef __MANAGE_H__
#define __MANAGE_H__


#include <stdio.h>
#include <time.h>
#include stdlib.h>

/* Constant that represent the max num of row and col of the Tabellone */

#define MAXR 3
#define MAXC 2

/* ------------------------------------------------------------------- */

/* Constant that represent the max num of row and col of a single matrix of Cell type */
#define CTR 3
#define CTC 5

/* --------------------------------------------------------------------------------- */

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


/* A new type of matrix which represent the scheme thanks to we manage the game */
typedef Cart_tab Tabellone[MAXR][MAXC];

void fill_cells( Cart_Tab );
int rand_num( void );





#endif
