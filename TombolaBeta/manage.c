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

void print_cartelle( Player *p )
{
    int i, j;
    int cont_c; /* Counter uses in order to loop throught the cartelle hold by a single player*/


    for( cont_c = 0; cont_c < p->n_cart; cont_c++ )
    {
        printf("\tCARTELLA N %d\n", p->cartelle[cont_c].id);

        for ( i = 0; i < CTR; printf("\n"), i++ )
            for ( j = 0; j < CTC; j++ )
                printf("%d ", p->cartelle[cont_c].cart[i][j].num);
    }

}

/*
    Function : fill_numbers()
    Parameters :
    - int num[] integer array which will contains all the value from 1 to 90
    - int n array's length

*/

void fill_numbers ( int num[], int n )
{
    int i;

    for ( i = 0; i < n; num[i] = i+1, i++ );
}

/*
    Function: rand_num()
    Returns :
    int : a random number generate using shuffling

    rand_num() uses a static array in order to
    shuffle all the ninety value that was contained in it
    using the modern implementation of Durstenfeld of the
    Fisher-Yaste's shuffling algorithm.

    if the source was not initialized than
        initialize it with value that go from 1 to 90

    for i from 1 to n − 1 do
      j ← random integer with 0 ≤ j ≤ i
      a[i] ← a[j]
      a[j] ← source[i]

*/
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

/*
    Function : get_row_col()
    Parameters:
    - int num : specific number that was extracted
    - int *r : pointer to the location in which there is the row number
    - int *c : pointer to the location in which there is the colomn number

    It splits the number in order to retrieve from the its first digit, the
    row's number and from its second digit the colomn's number.

*/
void get_row_col( int num, int *r, int *c )
{
    *r = num / 10 - 1;
    *c = num % 10 - 1;
}
/*
   It reads from the stdin an integer that respects the
   restrictions connected to the float data type.
*/

/* Useful function used in order to remove some useless characters present in the buffer */
void cleanBuffer()
{
    while ( getchar() != '\n');
}

int readInteger( void )
{
    int res;
    int intero;
    do
    {
        res = scanf("%d",&intero);
        scanf("%*[^\n]");
        if( res == 0)
          printf("\nAssegnazione valore errata, reinserisci: ");

    }while ( res == 0 );

    return intero;
}
/*
    Returns a correctly allocated pointer to a region
    of memory of n Cartella data structures.

*/
Cartella *createCartelle( Player *p )
{
    int i;

    p->cartelle = ( (Cartella*)malloc( p->n_cart * sizeof(Cartella)));
    if ( !p->cartelle )
    {
        fprintf(stderr, "ERRORE ALLOCAZIONE MEMORIA!\n");
        exit(-1);
    }

    for ( i = 0; i < p->n_cart; i++ )
    {
        fill_cells( p->cartelle[i].cart );
        p->cartelle[i].id = rand_num();
    }
    return p->cartelle;
}

Player *initListPlayer( ListPlayer *players )
{
    return ((Player*)malloc( players->n_player * sizeof(Player)));
}

void initGame( ListPlayer *players )
{

    int i;
    char buffer[MAX_LEN-1];

    printf("STAI INIZIANDO IL GIOCO CON QUANTI GIOCATORI?\n( RICORDA, DEVONO ESSERCENE ALMENO 2!! )\n");
    players->n_player = readInteger();
    cleanBuffer();
    players->list_player = initListPlayer( players);

    for( i = 0; i < players->n_player; i++ )
    {
        getName( &(players->list_player[i]));
        printf("PLAYER %d : %s", i+1, players->list_player[i].name_player);
        printf("Quante Cartelle desideri?\nN.Cartelle : ");
        players->list_player[i].n_cart = readInteger();
        players->list_player[i].cartelle = createCartelle( &(players->list_player[i]));
        print_cartelle( &(players->list_player[i]) );
        cleanBuffer();

    }

}

char *getName( Player *play )
{
    printf("INSERISCI IL TUO NOME :\n");

    play->name_player = malloc( MAX_LEN * sizeof(char));

    if ( !play->name_player )
    {
        printf("ERRORE ALLOCAZIONE MEMORIA!\n");
        exit(-1);
    }
    fgets( play->name_player, MAX_LEN, stdin);

    return play->name_player;
}
