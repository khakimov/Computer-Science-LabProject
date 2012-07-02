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
    TODO LIST
    - Risolvere problema del carica partita.
    provvedere a reallocare tutte le varie strutture dati appropriatamente.
    - Risolvere problema della PrintFile. FILE TOMBOLA.TXT NON FUNZIONANTE.
    - Aggiornare la funzione genCartella() garantendo la sua correttezza anche
    con un tombolone avente dimensione maggiore di 90.

    Aggiornamenti
    Gestione della topten completamente funzionante con stampa della classifica
    della partita attuale


*/
#include "TombolaFunction.h"

int main(void)
{
    bgcolor(63);
    system( "mode con: cols=120 lines=33" );

    Tombolone t;
    ListaGiocatori list;
    ListaPremi lista_premi;
    Estrazione estr;
    Impostazioni imp;


    scriviNumCartelleImpostazioni(&imp,6);
    scriviTotGiocImpostazioni( &imp,6);
    scriviDimImpostazioni( &imp, 90);
    scriviAudioVImpostazioni( &imp, T);
    scriviAudioNumImpostazioni( &imp, F);
   /* int cont = 0;
    int locX = 10, locY = 10;
    int cursX = 7, cursY = 10;
    int key;
    int scelta = 1;


    srand(time(NULL));


    gotoxy(locX, locY);
    printf("NUOVA PARTITA");
    gotoxy(locX, locY+=4);
    printf("CARICA PARTITA");
    gotoxy(locX, locY+=4);
    printf("IMPOSTAZIONI");
    gotoxy(locX, locY+=4);
    printf("TOT TEN");
    gotoxy(locX, locY+=4);
    printf("ISTRUZIONI");
    gotoxy(locX, locY+=4);
    printf("USCITA");
    gotoxy(cursX, cursY);
    printf("->");
    gotoxy(cursX, cursY);


    while( 1 )
    {


        key = getch();

        switch ( key )
        {
            case 'H' :
                gotoxy(cursX, cursY);
                printf("  ");
                if ( cursY < 12 )
                    cursY  = 34;

                gotoxy(cursX, cursY-=4);
                printf("->");

            break;
            case 'P' :
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


    /*int i = 0;
    while (++i)
    {

    textcolor(i);
    printf("PROVA %d  ", i);
    getch();
    }*/

    //printFile("impostazioni.txt");
    //nuova_partita(&imp);
    caricaPartita( );
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
