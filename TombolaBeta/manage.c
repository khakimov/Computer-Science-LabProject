#include "manage.h"


void fill_cells( Cart_Tab tab )
{
    for ( i = 0; i < CTR; i++ )
        for ( j = 0; j < CTC; j++ )
        {
           tab[i][j].num = rand_num();
           tab[i][j].check = NO;

        }
}

int rand_num( void )
{

    const int tot_num = 90;
    static int numbers[tot_num];
    int i = 0;
    int n_rand;

    srand(time(NULL));

    x = 1 + rand() % tot_num;

    if ( n_rand > 1 )
        for ( i = 0; i < tot_num-1; i++ )
        {
            int n_rand =  1 + rand() % tot_num;
            int temp = numbers[i];
            numbers[i] = numbers[n_rand];
            numbers[n_rand] = temp;

        }
    else
    {
       for ( i = 0; i < tot_num; i++ )
            numbers[i] = i+1;
        for ( i = 0; i < tot_num-1; i++ )
        {
            int n_rand =  1 + rand() % tot_num;
            int temp = numbers[i];
            numbers[i] = numbers[n_rand];
            numbers[n_rand] = temp;

        }
    }

    return numbers[n_rand];
}

