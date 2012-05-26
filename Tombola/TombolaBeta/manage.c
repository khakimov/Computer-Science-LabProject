#include "manage.h"

ListPrize premi = { { "Ambo", 5, NO, 0}, { "Terno", 10, NO, 0}, { "Quaterna", 20, NO, 0}, { "Cinquina", 30, NO, 0 }, { "Bingo", 50, NO, 0} };
Tombolone tomb;

void banner( void )
{
    printf("%s\n%s\n%s",
           "**************************************************",
           "************** INIZIA IL GIOCO *******************",
           "**************************************************"

           );
}

void initTombolone( Tombolone tomb )
{
    int row_tomb, col_tomb;
    int i, j;
    int k = 0;
    int k1 = 0;

    for ( row_tomb = 0; row_tomb < TR; row_tomb++ )
    {

          for ( i = 0; i < 3; i++ )
            {
                for ( j = 0; j < 5; j++ )
                {
                    tomb[row_tomb][0][i][j].num = j + 1 + ( k * 10);
                    tomb[row_tomb][0][i][j].check = NO;

                }
                k++;
            }

    }
    k = 0;
    for ( row_tomb = 0; row_tomb < TR; row_tomb++ )
    {

            for ( i = 0; i < 3; i++ )
            {
                for ( j = 0, k1 = 5; j < 5; j++, k1++ )
                {
                    tomb[row_tomb][1][i][j].num = k1 + 1 + ( k * 10);
                    tomb[row_tomb][1][i][j].check = NO;

                }
                k++;
            }




    }




}
void printTombolone( Tombolone tomb )
{
   int row_tomb, col_tomb;
    int i, j;
    int posX = 0, posY = 0;
    int tempX = 0, tempY = 0;

    for ( row_tomb = 0; row_tomb < TR;  row_tomb++)
    {

       for ( i = 0; i < 3; i++ )
        {
            for ( j = 0; j < 5;j++)
            {
                printf("| %2d | ", tomb[row_tomb][0][i][j].num);

            }
            gotoxy(posX,++posY);


        }
        gotoxy(posX, ++posY);


    }
    posX = 40;
    posY = 0;
    gotoxy(posX, posY);
    for ( row_tomb = 0; row_tomb < TR;  row_tomb++)
    {

       for ( i = 0; i < 3; i++ )
        {
            for ( j = 0; j < 5;j++)
            {
                printf("| %2d | ", tomb[row_tomb][1][i][j].num);

            }
            gotoxy(posX,++posY);


        }
        gotoxy(posX, ++posY);


    }
    printf("\n");


}

void gotoxy(int x, int y)
{
	COORD CursorPos = {x, y};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, CursorPos);
}

/* ---------------------------------------------------------------------------------        */
void fill_cells( Card tab )
{

	int i, j;
	int start, end;
	int num_col, num_row;
	int flag = 0;
	int tot = 0;

	for ( i = 0; i < CTC; i++ )
	{
        for ( j = 0; j < 3; j++ )
		{


		switch ( i )
            {

                case 0 :
                    start = 1; end = start + 9;
                break;
                case 1 :
                    start = 10; end = start + 9;
                break;
                case 2:
                    start = 20; end = start + 9;
                break;
                case 3:
                    start = 30; end = start + 9;
                break;
                case 4:
                    start = 40; end = start + 9;
                break;
                case 5:
                    start = 50; end = start + 9;
                break;
                case 6:
                    start = 60; end = start + 9;
                break;
                case 7:
                    start = 70; end = start + 9;
                break;
                case 8 :
                    start = 80; end = 90;

                break;

            }

            tab[j][i].num = rand_num(start, end);
			tab[j][i].check = NO;
		}


	}

    num_col = 3;
    num_row = 9;
    while ( tot != 15 )
    {
        printf("tot = %d\n", tot);

        for ( j = 0; j < 9 && num_row >= 5; j++ )
        {

            for ( i = 0; i < 3 && num_col >= 1; i++ )
            {
                flag = rand_num(0,2);

                if ( flag == 0 )
                {
                    tab[j][i].num = 0;
                    tab[j][i].check = NO;
                    tot++;
                    num_col--;
                    num_row--;


                }

            }
            num_col = 3;

        }

        num_row = 9;
        num_col = 3;
  }


}



void printNumbers( int num[], int n )
{
	int i;

	for ( i = 0; i < n; i++ )
		printf("%d ", num[i]);
	printf("\n");
}

void printCartTab( Cart_Tomb cartella )
{
    int i,j;

    for ( i = 0; i < CTR; printf("\n"), i++ )
        for ( j = 0; j < CTC; j++ )
            printf("| %2d | ", cartella[i][j].num);
}

void print_cartelle( Player *p )
{
    int i, j;
    int cont_c; /* Counter uses in order to loop throught the cartelle hold by a single player*/


    for( cont_c = 0; cont_c < p->n_cart; cont_c++ )
    {
        printf("\tCARTELLA N %d\n", readId(p, cont_c));

        for ( i = 0; i < CTR; printf("\n"), i++ )
            for ( j = 0; j < CTC; j++ )
                printf("%d ", readNumber( (&p->cartelle[cont_c]), i, j));




    }

}

/*
    Function : fill_numbers()
    Parameters :
    - int num[] integer array which will contains all the value from 1 to 90
    - int n array's length

*/

void fill_numbers ( int num[], int min, int max )
{
    int i;
    int k;

    for ( i = 0; i < 90; i++ )
        num[i] = 0;

    for ( i = 0, k = min; i < max-min; num[i] = k, i++, k++ );

}

/*
    Function: rand_num()
    Returns :
    a random number generate using shuffling

    rand_num() uses a static array in order to
    shuffle all the ninety value that was contained in it
    using the modern implementation of Durstenfeld of the
    Fisher-Yaste's shuffling algorithm.


*/
int rand_num( int min, int max )
{
    static int numbers[TOT_NUM];
    int rand_number;
    static int tot = 0;


    if ( tot == 0 || tot >= 3 )
    {
    	tot = 0;
    	fill_numbers(numbers, min, max);
    	shuffle(numbers, max-min);
    	rand_number = numbers[tot++];

    }
    else
    	rand_number = numbers[tot++];
    printf("TOTALE PRELEVATI %d\n", tot);
    //printNumbers(numbers, max-min);

    return rand_number;
}



void shuffle( int numbers[], int n )
{
    int i = 0;
    int n_rand;
    int temp;

    srand(time(NULL));


    for( i = n-1; i > 0; i-- )
    {
        n_rand = rand() % i;
        temp = numbers[i];
        numbers[i] = numbers[n_rand];
        numbers[n_rand] = temp;
    }
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

/*
    Returns a correctly allocated pointer to a region
    of memory of n Cartella data structures.

*/
Cartella *createCartelle( Player *p )
{
    int i;
    static int id_cart = 10;

    p->cartelle = ( (Cartella*)malloc( p->n_cart * sizeof(Cartella)));
    if ( !p->cartelle )
    {
        fprintf(stderr, "ERRORE ALLOCAZIONE MEMORIA!\n");
        exit(-1);
    }

    for ( i = 0; i < p->n_cart; i++ )
    {
        fill_cells( p->cartelle[i].cart );
        writeId(p, i, id_cart++);
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
void checkValue( ListPlayer *list, int num )
{
    int cont_c;
    int cont_player;
    int i, j;

    for(  cont_player = 0; cont_player < list->n_player; cont_player++ )
    {
        for ( cont_c = 0; cont_c < list->list_player[cont_player].n_cart; cont_c++ )
            setValue( &(list->list_player[cont_player].cartelle[cont_c]), num );
    }

    for ( i = 0; i < TR; i++ )
        for ( j = 0; j < TC; j++ )
            setValueTab( tomb[i][j], num );


}
void setValueTab( Cart_Tomb cart_tab , int num )
{
    int i, j;

    for( i = 0; i < CTR; i++ )
        for( j = 0; j < CTC; j++ )
            if ( cart_tab[i][j].num  == num )
                cart_tab[i][j].check = O;
}
void setValue( Cartella *cartella, int num )
{
    int i, j;

    for( i = 0; i < CTR; i++ )
        for( j = 0; j < CTC; j++ )
            if ( readNumber( cartella, i, j )  == num )
                cartella->cart[i][j].check = O;
}

void printPrize( int curr_prize, Player *win_player, int cont_c )
{
    /* If it not specified the player, the croupier has won */
    if ( !win_player )
        printf("Il Croupier ha fatto %s e ha vinto %d\n",
                premi[curr_prize].name_prize,
                premi[curr_prize].prize );
    /* In  the other case, A specific player has won so I print all the information */
    else
    {
        premi[curr_prize].winner_id = win_player->cartelle[cont_c].id;
        printf("%s ha fatto %s e ha vinto %d con la cartella %d\n",
                win_player->name_player, premi[curr_prize].name_prize,
                premi[curr_prize].prize, premi[curr_prize].winner_id );
    }
    premi[curr_prize].checked = O;
}

int checkCartella( Cartella *cartella, int in_a_row )
{
    int win = 1;
    int i,j;


    if ( in_a_row == 10 )
    {
        win = 10;
        for ( i = 0; i < CTR && win != 0; i++ )
            for ( j = 0; j < CTC && win != 0; j++ )
                if ( cartella->cart[i][j].check != O )
                    win = 0;

    }
    else
    {
        for( i = 0; i < CTR; i++ )
            for ( j = 0; j < CTC && win <= in_a_row; j++ )
                if ( cartella->cart[i][j].check == O )
                    win++;
    }

    return win;

}

int checkCartTomb( Cart_Tomb cart_tab, int in_a_row )
{
    int win = 0;
    int i,j;


    if ( in_a_row == 10 )
    {
        win = 10;
        for ( i = 0; i < 3 && win != 0; i++ )
            for ( j = 0; j < 5 && win != 0; j++ )
                if ( cart_tab[i][j].check != O )
                    win = 0;

    }
    else
    {

        for( i = 0; i < 3; i++ )
        {

           for ( j = 0; j < 5 && win < in_a_row; j++ )
                if ( cart_tab[i][j].check == O )
                    win++;
        }
    }

    return win;
}
void checkPrize( ListPlayer *list )
{
    /*
        PRIZE LIST:
        AMBO - 2
        TERNO - 3
        QUATERNA - 4
        CINQUINA - 5
        BINGO(TOMBOLA) - 10

        CARATTERI DI RIFERIMENTO
        A - Ambo
        T - Terno
        Q - Quaterna
        C - cinquina
        B - Bingo o Tombola

 */

    int i, j;
    int in_a_row = 0; /* number of element that will be in a row in order to gain the prize */
    int curr_prize = 0; /* hold the position in the array prize which represent the current prize that will be checked */
    int cont_c; /* hold the number of cartelle examined */

    for( i = 0; i < TOT_PRIZE && premi[i].checked == O; i++ )
        ;
    /* ASSERTION : the actual i value represent the position in which there is the prize that will be analyzed */
    curr_prize = i;

    switch( premi[i].name_prize[0] )
        {
            case 'A' : in_a_row = 2; break;
            case 'T' : in_a_row = 3; break;
            case 'Q' : in_a_row = 4; break;
            case 'B' : in_a_row = 10; break;
        }

    if ( in_a_row != 10 )
    {

        /* Check Tombolone */
        for( i = 0; i < TR; i++ )
            for ( j = 0; j < TC; j++ )
                if ( checkCartTomb( tomb[i][j], in_a_row) == in_a_row )
                    printPrize( curr_prize,NULL, 0 );




        for( i = 0; i < list->n_player; i++ )
            for ( cont_c = 0; cont_c < list->list_player[i].n_cart; cont_c++ )
                if ( checkCartella( &(list->list_player[i].cartelle[cont_c]), in_a_row) == in_a_row )
                    printPrize( curr_prize, &(list->list_player[i]), cont_c );




    }
    else
    {

        /* Check BINGO prize for the Tombolone */
        for ( i = 0; i < TR; i++ )
            for ( j = 0; j < TC; j++ )
                if ( checkCartTomb( tomb[i][j], in_a_row) == in_a_row )
                    printPrize( curr_prize, NULL, 0 );



        for ( i = 0; i < list->n_player; i++ )
            for ( cont_c = 0; cont_c < list->list_player[i].n_cart; cont_c++ )
                if ( checkCartella( &(list->list_player[i].cartelle[cont_c]), in_a_row) == in_a_row )
                    printPrize( curr_prize, &(list->list_player[i]), cont_c );



    }

}

int playGame( ListPlayer *list_player )
{
    int cont = 0;

    banner();


    while( isGameFinished(premi) != 1 && cont < TOT_NUM )
    {
        int estracted = rand_num(1,90);
        cont++;
        printf("\nESTRATTO NUMERO");
        /*wait(5);*/
        printf(" %d\n", estracted);

        checkValue( list_player, estracted);

        if ( cont >= 2 )
        {
            checkPrize( list_player );
        }
    }
    return 0;
}
