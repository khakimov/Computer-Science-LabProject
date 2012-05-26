#ifndef __CARDGENERATOR_H__
#define __CARDGENERATOR_H__

#include "ReadWriteFoo.h"
#include <conio2.h>

void card_generator( Card card );
int dark_generator ( int dark[3][4], int tot, int num_gen );
int rand_num( int, int );
void fill_numbers ( int [], int, int );
void shuffle( int [], int );
void bubble_sort( int *vet, int n);
void wait ( float seconds );


#endif
