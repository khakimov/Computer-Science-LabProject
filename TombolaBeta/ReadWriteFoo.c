#include "ReadWriteFoo.h"

int readNumber( Cartella *cartella, int i, int j )
{
    return cartella->cart[i][j].num;
}

int readId( Player *p, int cont_c )
{
    return p->cartelle[cont_c].id;
}

void writeId( Player *p, int cont_c, int id )
{
    p->cartelle[cont_c].id = id;
}

void writeNumber( Player *p, int cont_c, int i, int j, int num )
{
    p->cartelle[cont_c].cart[i][j].num = num;
}

int isChecked( struct Prize *prize )
{
    return ( prize->checked == O ) ? 1 : 0;
}


int isGameFinished( struct Prize *prizes )
{
    return ( isChecked( &(prizes[TOT_PRIZE-1] ) ) ) ? 1 : 0;
}

void swapCell( Cell *c1, Cell *c2 )
{
    Cell temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

void ord_row( Cell row[] )
{
    int i = 0, j;
    int ordinato = 1;

    while( ordinato != 0 && i < CTC-1 )
    {
        ordinato = 0;
        for ( j = CTC-1; j >= i+1; j-- )
            if ( row[j].num < row[j-1].num )
            {
                swapCell(&row[j], &row[j-1]);
                ordinato = 1;

            }
        i++;
    }
}

void wait ( int seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}
