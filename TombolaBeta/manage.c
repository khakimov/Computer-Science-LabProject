#include "manage.h"


void fill_cells( Cart_Tab tab )
{
    int i, j;

    for ( i = 0; i < CTR; i++ )
        for ( j = 0; j < CTC; j++ )
        {
           tab[i][j].num = rand_num();
           tab[i][j].check = NO;

        }
}
void print_cells( Cart_Tab cartella )
{
    int i, j;
    for ( i = 0; i < CTR; printf("\n"), i++ )
        for ( j = 0; j < CTC; j++ )
            printf("%d ", cartella[i][j].num);


}

void fill_numbers ( int num[], int n )
{
    int i;

    for ( i = 0; i < n; num[i] = i+1, i++ );
}

int rand_num( void )
{

    static int numbers[TOT_NUM];
    int i = 0;
    int n_rand;
    int temp;

    srand(time(NULL));

    if ( numbers[0] == 0 )
        fill_numbers(numbers, TOT_NUM);

    for( i = TOT_NUM-1; i > 0; i-- )
    {
        n_rand = 1 +  rand() % i;
        temp = numbers[i];
        numbers[i] = numbers[n_rand];
        numbers[n_rand] = temp;
    }


    return numbers[1+ rand() % TOT_NUM];
}

void get_row_col( int num, int *r, int *c )
{
    *r = num / 10 - 1;
    *c = num % 10 - 1;
}

Cartella *createCartelle( Cartella *listCartelle, int n )
{
    return malloc( n * sizeof(Cartella));
}
