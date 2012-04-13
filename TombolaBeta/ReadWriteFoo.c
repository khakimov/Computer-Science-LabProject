#include "ReadWriteFoo.h"

int readNumber( Player *p, int cont_c, int i, int j )
{
    return p->cartelle[cont_c].cart[i][j].num;
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

int isChecked( Prize *prize )
{
    return ( prize.checked == O ) ? 1 : 0;
}
