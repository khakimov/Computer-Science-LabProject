/*
 ============================================================================
 Name        : main.c
 Author      : Alessandro Suglia & Nazar Chekalin
 Version     :
 Copyright   :
 Description : Game of Tombola
 ============================================================================
 */

#include "TombolaFunction.h"


int main(void)
{
    /*Imposto i parametri per lo sfondo, grandezza finestra e titolo finestra */

    coloraSfondo(63);
    nascondiCursore();
    system( "mode con: cols=80 lines=40" );

    SetConsoleTitle("IL GIOCO DELLA TOMBOLA - Created by Alessandro Suglia & Nazar Chekalin");

    Impostazioni imp;


    srand(time(NULL));

    int cursX = 7, cursY = 10;
    int key;
    int scelta = 1;

    stampaMenu();

  /*  Ciclo per la gestione del cursore nel menu' e per
      la selezione dell'opzione scelta dal giocatore in base
      alle coordinate su schermo */

    while( scelta != 0 )
    {


        key = getch();

        switch ( key )
        {
            case 72 :
                gotoxy(cursX, cursY);
                printf("  ");
                if ( cursY < 12 )
                    cursY  = 34;

                gotoxy(cursX, cursY-=4);
                printf("->");

            break;
            case 80 :
                gotoxy(cursX, cursY);
                printf("  ");
                if ( cursY > 26 )
                    cursY = 6;

                gotoxy(cursX, cursY+=4);
                printf("->");

            break;
            case '\r':
                    switch ( cursY )
                        {
                            case NEW_GAME : nuovaPartita(&imp); cursX = 7; cursY = 10; stampaMenu();
                            break;

                            case LOAD : mostraCursore(); caricaPartita(); cursX = 7; cursY = 10;  stampaMenu();
                            break;

                            case SETTINGS :  impostazioniGioco(&imp); cursX = 7; cursY = 10;  stampaMenu();
                            break;

                            case TOP :  topten(NULL); cursX = 7; cursY = 10;  stampaMenu();
                            break;

                            case ISTR :  istruzioni(); cursX = 7; cursY = 10;  stampaMenu();
                            break;

                            case EXIT : uscita(); scelta = 0;
                            break;
                        }


            break;

        }


    }

    return EXIT_SUCCESS;
}

