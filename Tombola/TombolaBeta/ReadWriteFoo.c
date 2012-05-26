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

void writeNumCard( Cart_Tomb c, int i, int j, int num )
{
    c[i][j].num = num;
    c[i][j].check = NO;
}
void writeCheckCard( Cart_Tomb c, int i, int j, is_out flag )
{
    c[i][j].check = flag;
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


int readNumberCartTab( Cart_Tomb cart, int i, int j )
{
    return cart[i][j].num;


}
