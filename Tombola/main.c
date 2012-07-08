/*
 ============================================================================
 Name        : main.c
 Author      : Alessandro Suglia & Nazar Chekalin
 Version     :
 Copyright   :
 Description : Game of Tombola
 ============================================================================
 */

/*
    AGGIORNAMENTI

    La funzione caricaPartita() è stata divisa in più funzioni per poter
    garantire una più facile lettura del codice ed inoltre una notevole
    facilità di gestione dello stesso.
    Controllo errori in fase di caricamento e controllo che il file non sia
    vuoto.
    Controllo sulla dimensione del tombolone ed in caso tale dimensione sia
    incoretta viene prevista una gestione dello stesso garantendo la continuazione
    del gioco.

*/
#include "TombolaFunction.h"

void ResizeWindows( void );

int main(void)
{
    bgcolor(63);
    system( "mode con: cols=80 lines=40" );


    Impostazioni imp;

    set_error(ENOTF);
    srand(time(NULL));


    int cont = 0;
    int locX = 10, locY = 10;
    int cursX = 7, cursY = 10;
    int key;
    int scelta = 1;




    while( scelta != 0 )
    {
        clrscr();
        locX = 10, locY = 10;
        printFile("tombola.txt");
        gotoxy(locX, locY);
        printf("NUOVA PARTITA");
        gotoxy(locX, locY+=4);
        printf("CARICA PARTITA");
        gotoxy(locX, locY+=4);
        printf("IMPOSTAZIONI");
        gotoxy(locX, locY+=4);
        printf("TOP TEN");
        gotoxy(locX, locY+=4);
        printf("ISTRUZIONI");
        gotoxy(locX, locY+=4);
        printf("USCITA");
        gotoxy(cursX, cursY);
        printf("->");
        gotoxy(cursX, cursY);

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
                            case NEW_GAME : nuova_partita(&imp);
                            break;

                            case LOAD : caricaPartita();
                            break;

                            case SETTINGS : impostazioni_gioco(&imp);
                            break;

                            case TOP : topten(NULL);
                            break;

                            case ISTR : istruzioni();
                            break;

                            case EXIT : uscita(); scelta = 0;
                            break;
                        }


            break;

        }


    }


   /* int i = 0;
    while (++i)
    {

    textcolor(i);
    printf("PROVA %d  ", i);
    getch();
    }

    //printFile("tombola.txt");
    nuova_partita(&imp);
    caricaPartita();
    //impostazioni_gioco(&imp);
    /*initEstrazione(&estr, &imp);
    list.list_g = allocGiocatore();
    initGiocatore(list.list_g, &imp, &cont);
    createCartelle ( list.list_g, &estr);
    printCartelle(list.list_g);*/
    /*initTombolone(&t, 270);
    printTombolone(&t);*/



	return EXIT_SUCCESS;
}

