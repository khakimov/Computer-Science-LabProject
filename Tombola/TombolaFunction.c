/*
 * TombolaFunction.c
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ & Nazar Chekalin
 */
#include "CardManager.h"
#include "TombolaFunction.h"

/* Stampa il layout del menuì principale */
void stampaMenu( void )
{
       int locX = 10, locY = 10;

       clrscr();
       stampaFile("tombola.txt");
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
        gotoxy(7, 10);
        printf("->");
        nascondiCursore();


}
/*Nasconde il cursore nella schermata  */
void nascondiCursore( void )
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = FALSE;

    SetConsoleCursorInfo(hOut, &ConCurInf);
}


/* mostra il cursore nella schermata */
void mostraCursore( void )
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = TRUE;

    SetConsoleCursorInfo(hOut, &ConCurInf);
}


/*
    ///////////////////////////////////////
    // Funzione: liberaMemoria() /////////
    /////////////////////////////////////
    Provvede a deallocare tutta la memoria
    che è stata allocata mediante chiamate a
    malloc().

*/
void liberaMemoria( ListaGiocatori *listag, Tombolone *t, Estrazione *estr )
{
    int i,j;
    Giocatore *gioc_corr = NULL, *temp_gioc = NULL;
    Cartella *cart_corr = NULL, *temp_cart = NULL;

    /*
        Libera memoria assegnata al tombolone.

    */
    if ( t->cart_tomb != NULL )
    {

        for ( i = 0; i < leggiRigheTombolone(t); i++ )
            free( *(t->cart_tomb+i));
        free(t->cart_tomb);
    }
    /*
        Libera la memoria assegnata al vettore presente in Estrazione.

    */
    if ( leggiVettoreNumeri(estr) != NULL )
        free(leggiVettoreNumeri(estr));

    /*
        Delloca ogni singolo nodo che rappresenta un giocatore,
        e per ogni singolo giocatore, provvede a deallocare memoria
        per ogni singolo nodo Cartella.
    */
    if ( leggiPrimoGioc(listag) != NULL )
    {

        /*
            Per ogni giocatore della lista, salva il nodo corrente in un nodo
            temporaneo, scorri di un elemento la lista salvando il giocatore successivo
            a quello temporaneo e provvedi a deallocare il nodo temporaneo.

        */
        for ( i = 0, gioc_corr = leggiPrimoGioc(listag);
                i < leggiTotG(listag);
                i++ )
        {

            for ( j = 0, cart_corr = leggiCartella(gioc_corr);
                    j < leggiNumCartelleGioc(gioc_corr);
                    j++ )
            {

                temp_cart = cart_corr;
                cart_corr = leggiSuccC(cart_corr);
                free(temp_cart);

            }

            temp_gioc = gioc_corr;
            gioc_corr = leggiSuccG(gioc_corr);
            free(temp_gioc);


        }
    }
}



/*
    Funzione che provvede ad inizializzare nuovamente
    il file topten.txt nel caso questo fosse stato
    eliminato o fosse stato cancellato il suo contenuto.

*/
void ricreaTopten( FILE *top_file )
{
    int cont_gioc;
    char buffer[30];
    int tot = 200;


    /* Ora provvedo a riaprirlo in modalità scrittura per poterlo ricreare correttamente */

    /* Controlla eventuale impossibilità nel creare il file */
    if (  ( top_file = fopen("topten.txt", "w") ) == NULL )
    {
        perror("ERRORE CREAZIONE FILE TOPTEN.txt ::> ");
        getch();
        exit(-1);

    }
    else
    {
        /* File creato correttamente, ora provvedo a rimpinguarlo dei vari giocatori vincenti */
        for ( cont_gioc = 1; cont_gioc <= 10; cont_gioc++, tot -= 20 )
        {
            snprintf(buffer, 30, "Gioc%d %d\n", cont_gioc, tot );
            fprintf(top_file, "%s", buffer);
            strcpy(buffer, "\0");
        }


        fclose(top_file);


    }


}


/*
    Legge dal file topten.txt tutti i dati relativi
    alla topten e li salva correttamente nella lista
    di tipo Topten  passata come parametro.

*/
void leggiTopten( Topten *list )
{
    int cont_gioc;
    Topten *curr_top; /* Nodo topten attuale */
    FILE *top_file;
    char buffer[30]; /* Stringa contenente il nome del giocatore appena letto dal file*/
    int punt;/* valore intero che rappresenta il punteggio del giocare corrente */
    int file_creato = 0;

    if ( ( top_file = fopen("topten.txt", "r") ) == NULL )
    {
        fprintf(stderr,"\nFILE TOPTEN.txt NON PRESENTE\n");
        printf("Il File verra' ricreato, premere un tasto per continuare...");
        getch();
        clrscr();
        stampaFile("topten.txt");
        ricreaTopten( top_file );
        file_creato = 1;

    }

    else
    {

        if ( file_creato == 0 )
        {
            /*
                Posiziono il File Pointer alla fine del file in modo da
                poter correttamente richiamare la funzione ftell
                per poter conoscere la dimensione del file.
            */
            fseek( top_file, 0, SEEK_END);


            /* Il file topten.txt risulta essere vuoto, qualcosa non va. Ricrealo */
            if ( ftell(top_file) == 0 )
            {

                printf("IL FILE TOPTEN.txt E' VUOTO, LO RICREO!\n");
                getch();
                clrscr();
                stampaFile("topten.txt");

                ricreaTopten(top_file);


            }
        }
    }

    /*
        Lo riapro in modalità lettura in modo tale che si possa nuovamente
        utilizzare la topten in modo corretto.
    */

    if ( ( top_file = fopen("topten.txt", "r") )  == NULL )
    {
        perror("ERRORE APERTURA FILE TOPTEN.txt ::> ");
        getch();
        exit(-1);
    }
    else
    {


        curr_top = list;

        for ( curr_top = list, cont_gioc = 0;
            !feof(top_file) && cont_gioc < 10;
            cont_gioc++, curr_top = allocTopten() )
        {
            fscanf(top_file, "%s %d\n", buffer, &punt);
            scriviNomeTopTen(curr_top, buffer);
            scriviPunteggioTopTen(curr_top, punt);
            curr_top->next_top = initTopten();


            if ( cont_gioc > 0 )
                aggTopten(list, curr_top);

        }


    fclose(top_file);

    }
}


/*
    Funzione che gestisce l'intera elaborazione
    relativa all'inserimento dei giocatori in topten
    o alla stampa delle classifica.

*/
void topten( ListaGiocatori *listag )
{
    Giocatore *max_gioc, /* Giocatore con punteggio più alto*/
              *gioc_corr; /* Giocatore correntemente referenziato */
    Topten toplist, /* Lista di tipo Topten adoperata per tener traccia di tutti i giocatori */
            *nuovo_gioc; /* Nuovo elemento Topten da aggiungere eventualmente alla lista */

    stampaFile("topten.txt");

    /*
        Se la lista di giocatori è piena, ha senso valutare chi è il giocatore che
        merita di entrare in topten.
    */
    if ( listag != NULL )
    {
        /*
            Scorro la lista di giocatori alla ricerca del giocatore
            che ha totalizzato il punteggio più alto.

        */
        for ( max_gioc = leggiPrimoGioc(listag),gioc_corr = leggiPrimoGioc(listag);
            isSetGiocatore(gioc_corr);
            gioc_corr = leggiSuccG(gioc_corr) )
        {
            if ( leggiCashGiocatore(gioc_corr ) > leggiCashGiocatore(max_gioc ) )
                max_gioc = gioc_corr;
        }

        /* Leggo al topten attualmente salvata sul file */
        leggiTopten(&toplist);

        /*
            Con controllaTopten() verifico che il giocatore attualmente
            con punteggio maggiore meriti di entrare in topten e se così
            fosse la funzione ritornerebbe un valore diverso da NULL che
            rappresenta il nuovo elemento di tipo Topten
            correttamente inizializzato.
        */
        if ( ( nuovo_gioc = controllaTopten(&toplist, max_gioc) ) != NULL )
        {
            insOrdTopten(&toplist, nuovo_gioc);
            clrscr();
            stampaFile("topten.txt");
            stampaTopTen(&toplist);
            stampaTopTenSuFile( &toplist );
            gotoxy(30,80);
            printf("\nPremi un tasto qualsiasi per uscire!");
            getch();
        }
    }
    else
    {
        /*
            Se la lista di giocatori non è inizializzata allora è necessario
            unicamente stampare a video la topten.
        */
        leggiTopten(&toplist);
        stampaTopTen(&toplist);
        gotoxy(30,80);
        printf("\nPremi un tasto qualsiasi per uscire!");
        getch();
    }

    /*
        In ogni caso, dopo aver creato la lista di nodi di tipo Topten è necessario
        deallocarli chiamando la funzione liberaTopten().
    */
    liberaTopten(&toplist);

}

/*
    Mediante i dati passati come parametri alla funzione è possibile
    dare inizio ad una nuova partita della tombola.
    Tutti i parametri risultano ovviamente essere inizializzati poichè
    la chiamata a nuova partita viene effettuata o

*/
void giocaPartita ( ListaGiocatori *listag, Impostazioni *imp, Estrazione *estr, Tombolone *tomb, ListaPremi premi )
{
    int num_estr = 0; /* numero attualmente estratto */
    int car; /* Variabile che registra il carattere letto da tastiera */
    int exit  = 0; /* Flag che determinata se si deve o meno uscire dalla partita */
    int x = 1; /* Coordinata necessaria per la visualizzazione corretta delle informazioni su schermo*/
    int pag = 0; /* Necessaria per poter correttamente visualizzare il tombolone */
    int n_premio = 0; /* Posizione che identifica il premio attualmente analizzato */


    /* Controllo se vi sono premi vinti da una partita precedente (Nel caso in cui Gioca Partita viene richiamata
       a causa di una partita caricata) */
    for ( n_premio = 0; n_premio < TOT_PRIZE && leggiUscitoPremio(&premi[n_premio]) == T; n_premio++ )
        /* NON FA NULLA! */ ;
        /* ASSERZIONE : All'uscita dal ciclo n_premio individuerà la posizione del premio corrente*/



    clrscr();
    stampaTombolone(tomb, pag);
    gotoxy(x,33);
    printf("INVIO - Estrai Numero  %c/%c - Scorri Tombolone  s - Salva Partita  ESC - Esci",17,16);
    gotoxy(1,13);

    while( !finePartita(premi) && num_estr != -1  && exit != 1 )
    {


        if( leggiTotNumEstratti(estr) != 0 && leggiTotNumEstratti(estr) % 10 == 0 && num_estr != 0 )
        {
         clrscr();
         stampaTombolone(tomb, pag);
         gotoxy(1,13);
         printf("NUMERO ESTRATTO : %3d ", num_estr);
         gotoxy(x,33);
         printf("INVIO - Estrai Numero  %c/%c - Scorri Tombolone  s - Salva Partita  ESC - Esci",17,16);
         gotoxy(1,13);
        }

        /* Controlla il comando inserito dall'utente */
        switch( car = getch() )
        {
            case ENTER_KEY :
                num_estr = estraiNumero(estr);


                clrscr();
                stampaTombolone(tomb, pag);
                gotoxy(1,13);
                printf("NUMERO ESTRATTO : %3d ", num_estr);
                gotoxy(x,33);
                printf("INVIO - Estrai Numero  %c/%c - Scorri Tombolone  s - Salva Partita  ESC - Esci",17,16);
                gotoxy(1,13);
                controllaNumero(listag, tomb, num_estr);
                clrscr();
                stampaTombolone(tomb, pag);
                gotoxy(1,13);
                printf("NUMERO ESTRATTO : %3d ", num_estr);
                gotoxy(x,33);
                printf("INVIO - Estrai Numero  %c/%c - Scorri Tombolone  s - Salva Partita  ESC - Esci",17,16);
                gotoxy(1,13);

                /* Se vi sono più due o più numeri estratti allora controlla i premi */
                if( leggiTotNumEstratti(estr) >= 2)
                 controllaPremio(listag,tomb, estr, premi);

                    /* Se è uscito un premio e l'audio è attivo allora riproduci il suono vittoria */
                    if ( leggiUscitoPremio( &premi[n_premio] ) == T && leggiAudiovImpostazioni(imp) == T )
                    {

                        riprodSuono(0);
                        n_premio ++;

                    }
                    else
                      if ( leggiAudioNumImpostazioni(imp) == T ) /* Se il suono è attiva ma non vi sono premi riproduci il suono dell'estrazione */
                      {

                        if(num_estr > 90)
                         riprodSuono(91);
                        else
                         riprodSuono(num_estr);

                      }






            break;

            case SAVE_KEY:
                salvaPartita(listag, tomb, estr, imp, premi);
                wait(1);
                clrscr();
                stampaTombolone(tomb, pag);
                /* se viene eseguito il salvataggio prima di estrarre i numeri questo è pari a 0
                   di conseguenza si evita di stampare la scritta dell'estrazione */
                if ( num_estr != 0)
                {
                  gotoxy(1,13);
                  printf("NUMERO ESTRATTO : %3d ", num_estr);
                }

                gotoxy(x,33);
                printf("INVIO - Estrai Numero  %c/%c - Scorri Tombolone  s - Salva Partita  ESC - Esci",17,16);
                gotoxy(1,13);
            break;

            case RIGHT_KEY:
                if( pag == ( leggiRigheTombolone(tomb)  - 3) ) /* verifica se la pagina corrente sia pari al numero di pagine totali */
                    pag = 0; /* si riparta dalla prima pagina */
                else
                    pag += 3; /* passa alla pagina successiva */

                clrscr();
                stampaTombolone(tomb, pag);
                gotoxy(x,33);
                printf("INVIO - Estrai Numero  %c/%c - Scorri Tombolone  s - Salva Partita  ESC - Esci",17,16);
                gotoxy(1,13);

            break;

            case LEFT_KEY:
                if( pag == 0 ) /* se la pagina corrente è pari alla prima pagina */
                    pag =( leggiRigheTombolone(tomb) - 3 ); /* passa all'ultima pagina */
                else
                    pag -= 3; /* passa alla pagine precedente */

                clrscr();
                stampaTombolone(tomb, pag);
                gotoxy(x,33);
                printf("INVIO - Estrai Numero  %c/%c - Scorri Tombolone  s - Salva Partita  ESC - Esci",17,16);
                gotoxy(1,13);

            break;

            case ESC_KEY:
            {
                printf("SI STA ABBANDONANDO LA PARTITA CORRENTE...\n");
                wait(2);
                exit = 1;
            }
            break;
        }
    }

    /*
        Se effettivamente è finita la partita e non vi è stata
        alcuna uscita preventiva dalla partita allora provveded a
        verificare i premi dei giocatori della partita corrente.
    */
    if ( finePartita(premi) )
    {
        clrscr();
        stampaFile("tombola.txt");
        printf("PUNTEGGI PARTITA CORRENTE \nGIOCATORE\t\tPUNTEGGIO\n");
        stampaClassifica(listag);
        topten(listag);


    }


}

/*
    La funzione riproduce mediante la funzione della libreria Windows.h
    PlaySound() un suono specifico per ogni numero estratto.

*/
void riprodSuono( int num_estratto )
{
    char file_audio[MAX_PATH]; /* Variabile che conterrà il percorso del file audio da riprodurre */

    /*
        Se c'è stato un errore nella conversione e nell'esecuzione della snprintf,
        viene ritornato un valore negativo.
    */


    if ( snprintf(file_audio, MAX_PATH,  "sound\\%d.wav", num_estratto) < 0 )
    {
        perror("ERRORE SNPRINTF ::> ");
        getch();
        exit(-1);
    }
   else
    {
        /*
            Riproduce il file specificato dalla stringa file_audio
            in modo asincrono rispetto all'applicazione.
        */
        PlaySound (NULL, 0, 0);
        if ( !PlaySound(file_audio, NULL, SND_ASYNC) )


        {
            perror("PLAY SOUND ERROR ::> ");
            getch();
            exit(-1);
        }


    }
}


/*
    Stampa a video la classifica dei giocatori che
    hanno appena terminato una partita.

*/
void stampaClassifica( ListaGiocatori *listag )
{
    int *punt_gioc = malloc( leggiTotG(listag) * sizeof(int) ) ;
    int *id_gioc = malloc( leggiTotG(listag) * sizeof(int));
    int i;
    int car;
    int comodo_punt, comodo_id, scambio;
    Giocatore *gioc_corr;

    if ( leggiTotG(listag) > 10 )
    {
        car = getch();
        if ( car == 224 )
            car = getch();
    }

    /* scorre la lista dei giocatori e preleva le informazioni relative al punteggio ed id */
    for ( gioc_corr = leggiPrimoGioc(listag), i = 0;
         isSetGiocatore(gioc_corr);
         gioc_corr = leggiSuccG(gioc_corr), i++ )
    {
         punt_gioc[i] = leggiCashGiocatore(gioc_corr);
         id_gioc[i] = leggiIdGiocatore(gioc_corr);
    }
    /* ordina la classifica */
    while( scambio )
     {
      scambio = 0;
      for (i = 0; i < leggiTotG(listag)-1; i++)
       if( punt_gioc[i] < punt_gioc[i+1])
        {
          comodo_punt = punt_gioc[i];
          punt_gioc[i]= punt_gioc[i+1];
          punt_gioc[i+1]=comodo_punt;
          comodo_id = id_gioc[i];
          id_gioc[i]= id_gioc[i+1];
          id_gioc[i+1]=comodo_id;
          scambio = 1;
        }
     }

    /* stampa la classifica */
    for ( i = 0; i < leggiTotG(listag) && car != ESC_KEY; i++ )
    {
        switch ( i+1 )
        {
            case 1 : textcolor(28); break;
            case 2: textcolor(30); break;
            case 3 : textcolor(26); break;
            default : textcolor(63); break;
        }
        if( i && (i % 10)==0 && leggiTotG(listag) > 10)
        {
            printf("\n\nPremere un tasto per la pagina successiva");
            car = getch();
            clrscr();

            if(car != ESC_KEY)
            {
               stampaFile("tombola.txt");
               printf("PUNTEGGI PARTITA CORRENTE \nGIOCATORE\t\tPUNTEGGIO\n");
               printf("Giocatore %d\t\t%4d\n", id_gioc[i], punt_gioc[i]);
            }


        }
        else
        {
            printf("Giocatore %d\t\t%4d\n", id_gioc[i], punt_gioc[i]);
            if ( i == leggiTotG(listag)-1 )
            {
                printf("\n\nPremi un tasto per continuare...");
                getch();
            }

        }

    }
    free(punt_gioc);
    free(id_gioc);



}

/*
    Controlla se il premio in posizione 4
    del vettore( TOMBOLA ) è uscita o meno
    in modo tale da segnalare la fine della partita.

*/
int finePartita( ListaPremi premi )
{
    int stato = 0;

    if( leggiUscitoPremio( &premi[TOT_PRIZE-1] ) == T )
        stato = 1;

    return stato;
}

/* Inizializza le impostazio di gioco ai valore di default */
void initImpostazioni (Impostazioni *imp)
{
    scriviNumCartelleImpostazioni(imp,6);
    scriviTotGiocImpostazioni( imp,6);
    scriviDimImpostazioni( imp, 90);
    scriviAudioVImpostazioni( imp, F);
    scriviAudioNumImpostazioni( imp, F);
}

/*
    Funzione che provvede a dare inizio ad una nuova partita
    inizializzando anche tutte le strutture dati coinvolte nel gioco
    sulla base di quelle che sono le impostazioni scelte dall'utente.

*/
void nuovaPartita( Impostazioni *imp )
{
     ListaGiocatori lista;
     lista.list_g = initListaG();

    ListaPremi premi = { { "Ambo", 0, 0, F, 0 }, { "Terno", 0, 0, F, 0 }, { "Quaterna", 0, 0, F,0 },
                    { "Cinquina", 0, 0, F, 0 }, { "Bingo", 0, 0, F, 0 } };


     Giocatore *temp = NULL;
     int choice = 0;
     int i = 0;
     int flag_uscita = 0;
     int flag_menu = 0;
     int cont_id = 0;
     int cart_id = 1;
     Estrazione estr;
     Tombolone tomb;
     Cartella *cart_corr = NULL;

    /*
        Se nel caso in cui la partita venga avviata senza aver impostato le impostazioni( la struttura impostazioni potrebbe
        risultare non inizializzata ) viene notificato all'utente questa situazione e garantisce che la struttura venga
        inizializzata correttamente con quelle che sono le impostazioni di default.

    */

     if ( leggiDimImpostazioni(imp) < 0 || leggiNumCartelleImpostazioni(imp) > 1000 || leggiTotGiocImpostazioni(imp) > 10000 )
     {
        clrscr();
        stampaFile("nuova.txt");
        printf("\nIl gioco e' stato avviato senza aver selezionato le impostazioni!\nIl gioco verra' avviato con le impostazioni di default!\nPremere un tasto per continuare...\n");
        getch();
        initImpostazioni ( imp );
     }

     initEstrazione(&estr, imp);


    /*
        Se non è stata allocata memoria per il tombolone,
        vuol dire che è stato rilevato un eccesso nelle dimensioni
        dello stesso
    */
     if ( initTombolone(&tomb, leggiDimImpostazioni(imp)) == EITOMB )
     {
         flag_uscita = 1;
         clrscr();
         tombolaErrore( EITOMB, "Per prevenire ulteriori danni si sta uscendo dalla partita in corso!" );
         getch();
     }
    /* viene inizializzata la lista dei giocatori */
    lista.list_g = allocGiocatore();
    scriviTotG(&lista, leggiTotGiocImpostazioni(imp));

    /* Riempie la lista dei giocatori associando ad ognuno le cartelle della tombola */
    for ( temp = lista.list_g; i < leggiTotG(&lista) && !flag_uscita; i++, temp = allocGiocatore() )
    {

        initGiocatore(temp, imp, &cont_id);
        creaCartelle(temp, &estr);

        for ( cart_corr = leggiCartella(temp); isSetCartella(cart_corr); cart_id++, cart_corr = leggiSuccC(cart_corr ) )
            scriviIdCartella( cart_corr, cart_id);
        if( i > 0)
         aggGiocatore(lista.list_g, temp);



     if(!flag_menu)
     {


        /* Se l'id del giocatore indica l'ultima giocatore della lista
           allora stampa un menu' adatto altrimenti stampa il menu'
           del giocatore qualunque */
        if( leggiIdGiocatore(temp) == leggiTotGiocImpostazioni(imp))
        {
             do
             {

                    clrscr();
                    stampaFile("nuova.txt");
                    printf("\nNUMERO GIOCATORI : %d", leggiTotG(&lista));
                    printf("\nNUMERO CARTELLE : %d", leggiNumCartelleImpostazioni(imp));
                    printf("\nDIMENSIONI TOMBOLONE : %d\n", leggiDimImpostazioni(imp));
                    printf("\n\nOPZIONI UTENTE - Giocatore %d\n\n%s\n%s\n%s\n",
                            leggiIdGiocatore(temp),
                            "1) Visualizza Cartelle",
                            "2) Inizia il Gioco",
                            "3) Vai ad Impostazioni");
                    gotoxy(1,38);
                    printf("ESC - Esci");
                    gotoxy(1,18);


                switch( choice = getch() )
                {
                    case '1' : stampaCartelle( temp, &estr ); break;
                    case '2' : break;
                    case '3' :
                        printf("\nATTENZIONE SI STA PASSANDO ALLA SEZIONE IMPOSTAZIONI!\n");
                        wait(2);
                        impostazioniGioco(imp);
                        flag_uscita = 1;
                        break;
                    case ESC_KEY:
                        printf("ATTENZIONE SI STA PER ABBANDONARE LA PARTITA !");
                        wait(2);
                        flag_uscita = 1;
                        break;
                    default : printf("\n\nATTENZIONE TASTO NON VALIDO!\n"); wait(2); break;

                }
              } while (choice != '2' && !flag_uscita);
        }
        else
        {
            do
            {

                    clrscr();
                    stampaFile("nuova.txt");
                    printf("\nNUMERO GIOCATORI : %d", leggiTotG(&lista));
                    printf("\nNUMERO CARTELLE : %d", leggiNumCartelleImpostazioni(imp));
                    printf("\nDIMENSIONI TOMBOLONE : %d\n", leggiDimImpostazioni(imp));
                    printf("\n\nOPZIONI UTENTE - Giocatore %d\n\n%s\n%s\n%s\n%s\n",
                            leggiIdGiocatore(temp),
                            "1) Visualizza Cartelle",
                            "2) Inizia il Gioco",
                            "3) Vai ad Impostazioni",
                            "4) Passa al giocatore successivo");
                    gotoxy(1,38);
                    printf("ESC - Esci");
                    gotoxy(1,18);


                switch( choice = getch() )
                {
                    case '1' : stampaCartelle( temp, &estr ); break;
                    case '2' : flag_uscita = 1;
                               flag_menu = 1;
                               break;
                    case '3' :
                        printf("ATTENZIONE SI STA PASSANDO ALLA SEZIONE IMPOSTAZIONI!\n");
                        wait(2);
                        impostazioniGioco(imp);
                        flag_uscita = 1;
                    break;
                    case '4' : break;
                    case ESC_KEY:
                        printf("ATTENZIONE SI STA PER ABBANDONARE LA PARTITA !");
                        wait(1);
                        flag_uscita = 1;
                        break;
                    default : printf("\n\nATTENZIONE, TASTO NON VALIDO!!\n"); getch();break;

                }
            }while (choice != '4' && !flag_uscita );
        }
     }
      if(flag_menu)
        flag_uscita = 0;

    }



    if (!flag_uscita)
    {
        initEstrazione(&estr, imp);
        scriviNumGen(&estr, leggiDimImpostazioni(imp));
        initPremio(premi, leggiTotGiocImpostazioni(imp), leggiNumCartelleImpostazioni(imp));
        giocaPartita(&lista, imp, &estr, &tomb, premi);
         /*
            Terminata la partita è necessario provvedere alla deallocazione
            dell'ingente quantità di memoria che è stata messa a disposizione
            per poter garantire l'esecuzione.
        */
        liberaMemoria( &lista, &tomb, &estr);
    }

    gotoxy(1,25);





}

/* Inizializza la struttura estrazione */
void initEstrazione ( Estrazione *estr , Impostazioni *imp)
{
     scriviNumGen(estr, 0);
     scriviTotNumEstratti( estr, 0);
     initVettoreNumeri(estr);
     scriviTotNumeri(estr, leggiDimImpostazioni(imp));
}
/* Inizializza il gocatore singolo */
void initGiocatore(Giocatore *gcomodo, Impostazioni *imp, int *cont)
{
     gcomodo->id = (*cont)+=1;
     gcomodo->num_cartelle = imp->max_cartelle;
     gcomodo->cash = 0;
     gcomodo->next_g = NULL;
     gcomodo->cart_g = NULL;



}
/* La funzione prevede la colorazione dello sfondo della finestra */
void coloraSfondo( int color )
{

    int num = 1;
    textcolor(color);
    gotoxy(1,1);

    while ((num++)<6001)
    printf(" ");
    gotoxy(1,1);

}

/* Stampa le impostazioni di gioco e modifica i valori
   della struttura in base ai comando premuti dal giocatore */
void impostazioniGioco (Impostazioni *imp )
{
    char comando;
    int posizione = 1;
    static int flag_imp = 0;
    int random = rand()%2;
    textcolor(58+random);

    clrscr();


    stampaFile("impostazioni.txt");
    textcolor(63);
    /* Inizializza la struttura Impostazioni */
    if ( flag_imp == 0 )
    {
        initImpostazioni (imp);
        flag_imp = 1;
    }
    stampaImpostazioni(imp, posizione );

    while ((comando=(int)getch()) != 27)
    {
          if ( (int)comando == 72 || (int)comando == 8 )
          {
               if ( posizione - 1 < 1 )
               {
                    posizione = 5;
                    stampaImpostazioni(imp, posizione);
               }
               else
               {
                    posizione--;
                    stampaImpostazioni(imp,posizione);
               }
          }
          if ( (int)comando == 80 || (int)comando == 2 )
          {
               if ( posizione + 1 > 5 )
               {
                    posizione = 1;
                    stampaImpostazioni(imp, posizione);
               }
               else
               {
                    posizione++;
                    stampaImpostazioni(imp,posizione);
               }
          }
          if ( (int)comando == 75 || (int)comando == 77 )
          {
               switch( posizione )
               {
                       case 1:
                              if( (int)comando == 77 )
                              {
                                  scriviTotGiocImpostazioni(imp, leggiTotGiocImpostazioni(imp) + 1 );
                                  stampaImpostazioni(imp,posizione);

                              }
                              if( (int)comando == 75 )
                              {
                                  if( leggiTotGiocImpostazioni(imp) - 1 < 2 )
                                  {
                                      scriviTotGiocImpostazioni(imp, MAXG );
                                      stampaImpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      scriviTotGiocImpostazioni(imp, leggiTotGiocImpostazioni(imp) - 1 );
                                      stampaImpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 2:
                              if( (int)comando == 77 )
                              {
                                  if( leggiNumCartelleImpostazioni(imp) + 1 > MAXC )
                                  {
                                      scriviNumCartelleImpostazioni(imp,1);
                                      stampaImpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      scriviNumCartelleImpostazioni(imp, leggiNumCartelleImpostazioni(imp) + 1);
                                      stampaImpostazioni(imp,posizione);
                                  }
                              }
                              if( (int)comando == 75 )
                              {
                                  if( leggiNumCartelleImpostazioni(imp) - 1 < 1 )
                                  {
                                      scriviNumCartelleImpostazioni(imp,MAXC);
                                      stampaImpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      scriviNumCartelleImpostazioni(imp, leggiNumCartelleImpostazioni(imp) - 1);
                                      stampaImpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 3:
                              if( (int)comando == 77 )
                              {
                                  scriviDimImpostazioni( imp, leggiDimImpostazioni(imp) + 90);
                                  stampaImpostazioni(imp,posizione);
                              }
                              if( (int)comando == 75 )
                              {
                                  if( leggiDimImpostazioni(imp) - 90 >= 90)
                                  {
                                      scriviDimImpostazioni(imp, leggiDimImpostazioni(imp) - 90);
                                      stampaImpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 4:
                              if( (int)comando == 75 || (int)comando == 77)
                              {
                                  if( leggiAudiovImpostazioni(imp) == T)
                                  {
                                     scriviAudioVImpostazioni(imp,F);
                                     stampaImpostazioni(imp,posizione);
                                  }
                                  else
                                  {
                                      scriviAudioVImpostazioni(imp, T);
                                      stampaImpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 5:
                              if( (int)comando == 75 || (int)comando == 77)
                              {
                                  if(leggiAudioNumImpostazioni(imp) == T)
                                  {
                                     scriviAudioNumImpostazioni(imp, F);
                                     stampaImpostazioni(imp,posizione);
                                  }
                                  else
                                  {
                                      scriviAudioNumImpostazioni(imp, T);
                                      stampaImpostazioni(imp,posizione);
                                  }
                              }
                      break;
               }
          }
    }


}
/* Stampa a video le impostazioni di gioco */
void stampaImpostazioni ( Impostazioni *imp, int posizione)
{
    int pos = 8;
    int color = 62;

    gotoxy( 1, 6);
    printf("----------------------GAMEPLAY--------------------");
    gotoxy( 5, pos );
    printf("Numero Giocatori [Min 2]");
    gotoxy( 42, pos++ );
    printf(" %c %3d %3c  ", 17, leggiTotGiocImpostazioni(imp), 16);
    gotoxy( 5, pos );
    printf("Cartelle per Giocatore [Min 1/Max 6]");
    gotoxy( 42, pos++ );
    printf(" %c %3d %3c  ", 17, leggiNumCartelleImpostazioni(imp), 16);
    gotoxy( 5, pos );
    printf("Dimensione Tombolone [Min 90]");
    gotoxy( 42, pos++ );
    printf(" %c %3d %3c  ", 17, leggiDimImpostazioni(imp), 16);
    gotoxy( 1, 12);
    printf("------------------------AUDIO---------------------");
    gotoxy( 5, pos+3 );
    if (imp->audiov == T )
    {
      printf("Suoni Vittoria");
      gotoxy( 42, (pos++)+3 );
      printf(" %c %3s %3c  ", 17, "SI", 16);
    }
     else
     {
      printf("Suoni Vittoria");
      gotoxy( 42, (pos++)+3 );
      printf(" %c %3s %3c  ", 17, "NO", 16);
     }

    gotoxy( 5, pos+3 );
    if (imp->audionum == T )
    {
      printf("Suoni Estrazione");
      gotoxy(42, (pos++)+3);
      printf(" %c %3s %3c  ", 17, "SI", 16);
    }
     else
     {
      printf("Suoni Estrazione");
      gotoxy(42, (pos++)+3);
      printf(" %c %3s %3c  ", 17, "NO", 16);
     }
    gotoxy( 1, 17);
    printf("--------------------------------------------------");
    gotoxy( 1, 38);
    printf("ESC - Esci");
    switch( posizione )
    {
      case 1 :
              gotoxy( 5, posizione + 7);
              textcolor(color);
              printf("Numero Giocatori [Min 2]");
              gotoxy(42, posizione + 7);
              printf(" %c %3d %3c  ", 17, leggiTotGiocImpostazioni(imp), 16);
              textcolor(color+1);
              break;
      case 2 :
              gotoxy( 5, posizione + 7);
              textcolor(color);
              printf("Cartelle per Giocatore [Min 1/Max 6]");
              gotoxy(42, posizione + 7);
              printf(" %c %3d %3c  ", 17, leggiNumCartelleImpostazioni(imp), 16);
              textcolor(color+1);
              break;
      case 3 :
              gotoxy( 5, posizione + 7);
              textcolor(color);
              printf("Dimensione Tombolone [Min 90]");
              gotoxy(42,posizione +7 );
              printf(" %c %3d %3c  ", 17, leggiDimImpostazioni(imp), 16);
              textcolor(color+1);
              break;
      case 4 :
              gotoxy( 5, posizione + 10);
              textcolor(color);
              if (imp->audiov == T )
              {
               printf("Suoni Vittoria");
               gotoxy(42, posizione + 10);
               printf(" %c %3s %3c  ", 17, "SI", 16);
              }
               else
               {
                printf("Suoni Vittoria");
                gotoxy(42, posizione +10);
                printf(" %c %3s %3c  ", 17, "NO", 16);
               }
               textcolor(color+1);
              break;
      case 5 :
              gotoxy( 5, posizione + 10);
              textcolor(color);
              if (imp->audionum == T )
              {
               printf("Suoni Estrazione");
               gotoxy(42, posizione + 10);
               printf(" %c %3s %3c  ", 17, "SI", 16);
              }
               else
               {
                printf("Suoni Estrazione");
                gotoxy(42, posizione + 10);
                printf(" %c %3s %3c  ", 17, "NO", 16);
               }
               textcolor(color+1);
              break;
    }

}
/* Aggiungo un nodo giocatore in coda alla lista dei giocatori */
void aggGiocatore(Giocatore *g,Giocatore *gcomodo)
{
     if(!isSetGiocatore(g->next_g))
     {
       g->next_g = allocGiocatore();
       if ( !g->next_g )
       {
            clrscr();
            perror("ERRORE MALLOC ::> ");
            getch();
            exit(-1);
       }
       g = leggiSuccG(g);
       *g = *gcomodo;
     }
      else aggGiocatore(leggiSuccG(g),gcomodo);

}

int controllaNomeFile( char *nome_file )
{

    /*
        IL nome di un file in Windows accetta uno qualsiasi dei caratteri
        del formato standard Unicode, tralasciando quelli che sono i seguenti
        caratteri :

        < (less than)
        > (greater than)
        : (colon)
        " (double quote)
        / (forward slash)
        \ (backslash)
        | (vertical bar or pipe)
        ? (question mark)
        * (asterisk)


    */
    static char char_no_validi[] =
        {
            '<', '>', ':', '\"', '/', '\\', '|', '?', '*'

        };
    int errore = ENOTF;
    int tot_char = 9;
    int i = 0,j;

    /*
        Effettuo il controllo che all'interno del nome del file scelto non vi siano
        caratteri simili, altrimenti, segnalo un errore.

    */

    /* Se il nome del file è uguale alla parola vuota, c'è un errore! */
    if ( strcmp(nome_file, "\0") == 0 )
        errore = ENOMSAVE;
    else
    {
        for ( i = 0; i < strlen(nome_file) && errore == ENOTF; i++ )
            for ( j = 0; j < tot_char && errore == ENOTF; j++ )
                if ( nome_file[i] == char_no_validi[j] )
                    errore = ENOMSAVE;
    }

    return errore;
}

void salvaPartita( ListaGiocatori *list, Tombolone *t, Estrazione *estr, Impostazioni *imp, ListaPremi premi )
{
    DIR *dir_fp;
    struct dirent *ent;
    FILE *fp;
    char buffer[100];
    char filename[MAX_PATH];
    char dir_name[MAX_PATH];
    char *dir_principale;
    int errore = ENOTF;

    /* Prelevo la homepath del sistema corrente */



    stampaFile("salva.txt");

    if ( ( dir_principale = getenv("USERPROFILE") ) != NULL )
    {
        if ( ( strcpy( dir_principale,dir_principale) ) != NULL )
        {
            if ( !snprintf(dir_name, MAX_PATH, "%s\\TombolaSaveGame", dir_principale)  )
            {
                perror("ERRORE CREAZIONE PATHNAME :: > ");
                getch();
                exit(-1);
            }
        }
    }
    else
    {
        perror("ERROR GETENV ::> ");
        getch();
        exit(-1);
    }

    if ( ( dir_fp = opendir(dir_name) ) == NULL )
    {
       /*
        Se la directory non esiste
        allora viene appositamente creata

       */

        printf("\nDIRECTORY DI SALVATAGGIO NON TROVATA \n\n LA DIRECOTORY E' STATA CREATA NELLA CARTELLA PRINCIPALE DELL'UTENTE\n\n");
        wait(1);
       if ( _mkdir(dir_name) )
       {
            printf("\nDIR CREATA!\n\n");
            wait(1);
            if ( ( dir_fp = opendir(dir_name) ) == NULL )
            {
                printf("\n\n\nNON CREATA!\n\n");
                wait(1);
            }

       }


    }


    printf("\nIl nome del file da salvare verra' salvato con estensione '.sav'\nInserisci nome file da salvare ( MAX 6 caratteri ) : ");
    fgets( buffer, 8, stdin);
    chomp(buffer);
    while( getchar() != '\n');

    if ( ( errore = controllaNomeFile(buffer) ) == ENOMSAVE )
    {
        tombolaErrore( errore, "\nImpossibile proseguire nel salvataggio del file! \n\nPremi un tasto qualsiasi per uscire!");
        getch();
    }
    else
        if ( !snprintf( filename, MAX_PATH, "%s\\%s.sav", dir_name, buffer) || errore == ENOMSAVE )
        {
            clrscr();
            tombolaErrore( errore, "\nCrezione del pathname fallita!");
            getch();
            exit(-1);
        }
    else
    {

        if ( ( fp = fopen(filename,"wb")) == NULL )
        {
            perror("ERROR FILE ::> ");
            getchar();
            exit(-1);
        }
        else
        {
            Giocatore *gioc_corr;
            Cartella *cart_corr;
            int row_tomb, col_tomb;

            printf("\nSalvataggio %s in corso....", filename);

            /* Salvataggio struttura ListaGiocatore */

            fwrite( list, sizeof(ListaGiocatori), 1, fp );
            for ( gioc_corr = leggiPrimoGioc(list); isSetGiocatore(gioc_corr); gioc_corr = leggiSuccG(gioc_corr) )
            {
                fwrite(gioc_corr, sizeof(Giocatore), 1, fp);

                for ( cart_corr = leggiCartella(gioc_corr); isSetCartella(cart_corr); cart_corr = leggiSuccC(cart_corr) )
                    fwrite( cart_corr, sizeof(Cartella), 1, fp);
            }


            /* Salvataggio struttura Impostazioni */
            fwrite(imp, sizeof(Impostazioni), 1, fp);

            /* Salvataggio ListaPremi */
            fwrite( premi, sizeof(ListaPremi), 1, fp);

            /* Salvataggio struttura Estrazione */

            fwrite( estr, sizeof(Estrazione), 1, fp );

            fwrite(estr->numbers, sizeof(int), leggiTotNumeri(estr), fp);


            /* Salvataggio struttura Tombolone */
            fwrite(t, sizeof(Tombolone), 1, fp);

            for ( row_tomb = 0; row_tomb < leggiRigheTombolone(t); row_tomb++ )
                for ( col_tomb = 0; col_tomb < leggiColTombolone(t); col_tomb++ )
                    fwrite( &t->cart_tomb[row_tomb][col_tomb], sizeof(Cart_Tomb), 1, fp );


        }

        closedir(dir_fp);
        fclose(fp);
    }


}

int leggiFileSalvataggio( char *nuovo_file )
{
    int num_files;
    DIR *dir_fp;
    struct dirent *ent = malloc( sizeof(struct dirent));
    char **file_names;
    int i = 0;
    int res = 0;
    char dir_name[MAX_PATH];
    char *dir_principale;
    int status = 1;
    int choice;
    int flag_uscita = 1;
    int num_pagine, cont_pag;
    int j;
    int key;

    /*
        Controlla che la variabile d'ambiente USERPROFILE Sia settata
        e possa essere acquisita in modo corretto.
        Dopodichè provvede a generare il nome della directory
        nella quale salvare i vari file di salvataggio.

    */
   if ( ( dir_principale = getenv("USERPROFILE") ) != NULL )
    {
        if ( ( strcpy( dir_principale,dir_principale) ) != NULL )
        {
            if ( !snprintf(dir_name, MAX_PATH, "%s\\TombolaSaveGame", dir_principale)  )
            {
                fprintf(stderr,"ERRORE CREAZIONE PATHNAME  ");
                getch();
                exit(-1);
            }
        }
    }
    else
    {
        perror("ERROR GETENV ::> ");
        getch();
        exit(-1);
    }

    if ( ( dir_fp = opendir(dir_name) ) == NULL )
    {
       clrscr();
       stampaFile("carica.txt");
       fprintf( stderr, "\nCARTELLA DEI SALVATAGGI NON PRESENTE, PROVVEDERE A CREARLA SALVANDO UNA PARTITA ");
       getchar();
       status = 0;

    }
    else
    {

        file_names = (char**)malloc(sizeof(char*));
        if ( !file_names )
        {
            perror("MALLOC ERROR 1::> ");
            getch();
            exit(-1);
        }

        stampaFile("carica.txt");

        /*
            Usando la funzione readdir, scorro l'intera directory
            alla ricerca di quelli che sono i file di salvataggio
            che verranno mostrati all'utente.

        */
        num_files = 1;
        i = 0;

        while( ( ent = readdir(dir_fp) ) != NULL )
        {

            /* Controllo che il file abbia estensione .sav */
            if ( controllaEstensione(ent->d_name) )
            {

                *(file_names+i) = malloc( ent->d_namlen+1 );
                if ( !( file_names+i ) )
                {
                    perror("MALLOC ERROR 2::> ");
                    getch();
                    exit(-1);
                }

                strncpy( *(file_names+i), ent->d_name, ent->d_namlen+1);


                //printf("%d) %s\n", num_files, *(file_names+i));

                file_names = (char**)realloc( file_names, ++num_files * sizeof(char*));


                i++;
                if ( !file_names )
                {
                    perror("REALLOC ERROR 4::> ");
                    getch();
                    exit(-1);

                }


            }


        }


        /*
            SE I = 0 , NESSUN FILE SARA' STATO TROVATO!
            Setto lo status 0 per notificare l'errore.
        */
        if ( i == 0 )
        {
            printf(" NESSUN FILE DI SALVATAGGIO TROVATO!!\nSTO USCENDO!\n");
            wait(2);
            status = 0;

        }
        else

        {

            if ( ( num_files % 10 ) != 0 )
                num_pagine = num_files / 10 + 1;
            else
                num_pagine = num_files / 10;

            cont_pag = 1;
            num_files--;

            do
            {


                while( flag_uscita != 0 )
                {
                    clrscr();
                    stampaFile("carica.txt");
                    printf("---------------------------------\n%s\n%s\n",
                            "--------- PARTITE SALVATE -------",
                            "---------------------------------");
                    for ( j = (cont_pag-1) * 10; j < cont_pag * 10 && j < num_files; j++ )
                        printf("%d) %s\n", j+1, *(file_names+j) );


                    if ( num_pagine > 1 )
                    {
                        gotoxy(1, 38);
                        printf("Premi un qualunque tasto diverso dalle freccie per continuare!\n");
                        gotoxy( 1, 50);
                        printf("<- scrorri pagina a sinistra   -> scorri pagina a destra ");
                        gotoxy( 1, 20);
                        key = getch();
                        if ( key == 224 )
                            key = getch();
                        switch ( key )
                        {

                            case RIGHT_KEY :
                                if( cont_pag  < num_pagine )
                                    cont_pag++;
                            break;

                            case LEFT_KEY :
                                if ( cont_pag > 1 )
                                    cont_pag--;
                            break;

                            default : flag_uscita = 0; break;


                        }

                   }
                    else
                        flag_uscita = 0;


                }

            flag_uscita = 1;
            /*do
            {*/

            printf("\n\nPer caricare un file selezionare numero del salvataggio da caricare\n( Inserisci '0' per uscire )\nScelta del salvataggio : ");
            if ( ( res = scanf("%d", &choice) ) <= 0 )
            {
                fprintf(stderr,"ACCETTA UNICAMENTE DATI NUMERICI!!\n");
                while( getchar() != '\n' );
                getch();

            }
            else
               if ( choice < 0 || choice > num_files )
               {
                    fprintf(stderr, "SCELTA SELEZIONATA NON CONSENTITA!!\n");
                    while( getchar() != '\n' );
                    getch();

                }
            else
              if ( choice == 0 )
              {
                status = 0;
                flag_uscita = 0;
              }
              else
                flag_uscita = 0;

            //} while( ( choice < 0 || choice > num_files ) || ( res < 0 ) );

        }while( flag_uscita == 1 || ( choice < 0 || choice > num_files ) || ( res < 0 ) );


            /*
                Compongo il pathname del salvataggio selezionato
            */

        if ( status != 0 )
        {

            printf("Salvataggio selezionato %s\n", *(file_names+(choice-1)));
            if ( !snprintf(nuovo_file, MAX_PATH, "%s\\%s", dir_name, *(file_names+(choice-1)) ) )
            {
                perror("ERRORE CREAZIONE NOME FILE ::> ");
                getch();
                status = 0;
            }
        }
    }


    }


    return status;
}




int leggiFileDatiGiocatori( FILE *fp, ListaGiocatori *list )
{
    Giocatore *gioc_corr = NULL;
    Cartella *cart_corr = NULL;
    int error_flag = 1;
    int i, j;

    if ( fread(list, sizeof(ListaGiocatori), 1, fp ) != 0 )
    {

        list->list_g = initListaG();


        for ( gioc_corr = allocGiocatore(), i = 0; i < leggiTotG(list) && error_flag != 0; i++, gioc_corr = allocGiocatore() )
        {
            if ( fread( gioc_corr, sizeof(Giocatore), 1, fp) != 0 )
            {
                gioc_corr->next_g = initListaG();
                gioc_corr->cart_g = initCartella();

                for ( cart_corr = allocCartella(), j = 0; j < leggiNumCartelleGioc(gioc_corr) && error_flag != 0; cart_corr = allocCartella(), j++ )
                {
                    if ( fread(cart_corr, sizeof(Cartella), 1, fp) != 0 )
                    {

                        cart_corr->next_cart = initCartella();

                        if ( j == 0 )
                            gioc_corr->cart_g = cart_corr;
                        else
                            aggCartella(gioc_corr->cart_g, cart_corr);
                    }
                    else
                        error_flag = 0;
                }

                if ( i == 0 )
                    list->list_g = gioc_corr;
                else
                    aggGiocatore(list->list_g, gioc_corr);
            }
            else
                error_flag = 0;
        }
    }
    else
        error_flag = 0;

    return error_flag;

}
int prelevaDatiDaFile( FILE *fp, ListaGiocatori *list, Tombolone *t, Estrazione *estr, Impostazioni *imp, ListaPremi premi )
{

    int i, row_tomb, col_tomb;
    int error_flag = 1;

    /* Lettura struttura ListaGiocatore */

    if ( leggiFileDatiGiocatori( fp, list ) )
    {

        if ( ( fread( imp, sizeof(Impostazioni), 1, fp) != 0 ) && (fread( premi, sizeof(ListaPremi), 1, fp ) != 0 )
            && ( fread( estr, sizeof(Estrazione), 1, fp ) != 0 ) && error_flag != 0 )

        {
            estr->numbers = malloc( leggiTotNumeri(estr) * sizeof(int));

            if ( ( fread( estr->numbers, sizeof(int), leggiTotNumeri(estr), fp) != 0) && ( fread( t, sizeof(Tombolone), 1, fp) != 0 ) && error_flag != 0 )
            {
                    t->cart_tomb = malloc( leggiRigheTombolone(t) * sizeof(Cart_Tomb*));
                    if ( !t->cart_tomb )
                    {
                        perror("MALLOC ERROR ::> ");
                        getch();
                        exit(-1);

                    }

                    for ( i = 0; i < leggiRigheTombolone(t); i++ )
                    {
                        *(t->cart_tomb+i) = malloc( leggiColTombolone(t) * sizeof(Cart_Tomb));
                        if ( !( *(t->cart_tomb+i ) ) )
                        {
                            clrscr();
                            perror("MALLOC ERROR ::> ");
                            getch();
                            error_flag = 0;

                        }
                    }

                    for ( row_tomb = 0; row_tomb < leggiRigheTombolone(t) && error_flag != 0; row_tomb++ )
                        for ( col_tomb = 0; col_tomb < leggiColTombolone(t) && error_flag != 0; col_tomb++ )
                            error_flag = fread( &t->cart_tomb[row_tomb][col_tomb], sizeof(Cart_Tomb), 1, fp );
                }
                else
                    error_flag = 0;
        }
        else
            error_flag = 0;



    }
    else
        error_flag = 0;



    return error_flag;
}


void caricaPartita( void )
{
    ListaGiocatori list;
    Tombolone t;
    Estrazione estr;
    Impostazioni imp;
    ListaPremi premi;
    char nome_file_salvataggio[MAX_PATH];
    FILE *fp;


    if ( leggiFileSalvataggio(nome_file_salvataggio) != 0 )
    {

        if ( ( fp = fopen(nome_file_salvataggio,"rb") ) == NULL )
        {
            perror("FILE ERROR ::>  ");
            getch();
            exit(-1);
        }
        else
        {

            /* Controllo che il file che si sta cercando di aprire non sia vuoto! */
            fseek(fp, 0, SEEK_END);
            if ( ftell(fp) == 0 )
            {
                fprintf(stderr,"ERRORE APERTURA DEL FILE : Il file che si sta tentando di aprire è vuoto!\n");
                getch();
                fclose(fp);
            }
            else
            {
               /*
                  Dopo aver posizionato il file pointer alla fine del file per poter effettuare il controllo
                  lo riporto all'inizio del file in modo tale da poter garantire la corretta lettura dei dati.
               */
               fseek( fp, 0, SEEK_SET);
               printf("Caricamento %s in corso....", nome_file_salvataggio);

               if ( !prelevaDatiDaFile(fp, &list, &t, &estr, &imp, premi ) )
               {
                    clrscr();
                    printf("IL FILE POTREBBE ESSERE CORROTTO O POTREBBERO ESSERCI DATI NON LEGGIBILI!\nIMPOSSIBILE CARICARE FILE\nPremi Invio per continuare");
                    getch();
                    //liberaMemoria(&list, &t, &estr);

               }
               else
               {
                    printf("CARICAMENTO COMPLETATO! ");
                    giocaPartita(&list, &imp, &estr, &t, premi);
               }



            }

            fclose(fp);
        }
    }



}

int controllaEstensione( char *filename )
{
    char *temp = NULL;
    char *copy = NULL;
    int flag = 0;

    copy = malloc( ( strlen(filename) + 1) * sizeof(char));
    if ( !copy )
    {
        perror("MALLOC ERROR ::>> ");
        getch();
        exit(-1);
    }

    strcpy( copy, filename);
    temp = strtok(copy, ".");

    while( temp != NULL )
    {

        if ( strcmp(temp, "sav") == 0 )
            flag = 1;
        temp = strtok(NULL, ".");

    }

    free(copy);
    return flag;

}



void uscita()
{
    stampaFile("uscita.txt");
    wait(1);

}

void istruzioni()
{
    stampaFile("istruzioni.txt");


}



Cartella *leggiCartella(Giocatore *g)
{
    return g->cart_g;
}

int leggiIdGiocatore(Giocatore *g)
{
    int errore = ENOTF;

    if ( !isSetGiocatore(g) )
        errore = EIDG;

    return ( errore == EIDG ) ? errore : g->id;
}

int scriviIdGiocatore( Giocatore *g, int id )
{
    int errore = ENOTF;

    if ( !isSetGiocatore(g) )
        errore = ELG;
    else
        if ( id < 0 )
            errore = EIDG;
    else
        g->id = id;

    return errore;
}

int leggiCashGiocatore( Giocatore *g )
{
    int errore = ENOTF;

    if ( !isSetGiocatore(g ) )
        errore = ERCASHG;

    return (  errore == ERCASHG ) ? errore : g->cash;
}


int scriviCashGiocatore( Giocatore *g, int cash )
{
    int errore = ENOTF;

    if ( !isSetGiocatore(g) )
        errore = ELG;
    else
        if ( cash < 0 )
            errore = ECASHG;
    else
        g->cash = cash;

    return errore;
}

int leggiNumCartelleGioc( Giocatore *g )
{
    int errore = ENOTF;

    if ( !isSetGiocatore(g) )
        errore = ERNUMCART;


    return ( errore == ERNUMCART) ? errore : g->num_cartelle;
}
int scriviNumCartelleGioc(Giocatore *g, int numc)
{
    int errore = ENOTF;

    if(numc < 1 || numc > 6)
        errore = ENUMCART;
     else
        if ( !isSetGiocatore(g) )
            errore = ELG;
    else
      g->num_cartelle = numc;


    return errore;
}


Giocatore *leggiPrimoGioc( ListaGiocatori *list )
{
    return list->list_g;
}


Giocatore *initListaG()
{
    return NULL;
}

Giocatore *allocGiocatore()
{
    return malloc(sizeof(Giocatore));


}

void creaCartelle( Giocatore *p, Estrazione *estr )
{
    int i = 0;

    //Inizializzio il puntatore di testa delle cartelle

    p->cart_g = genCartella(estr);


    while( i < leggiNumCartelleGioc(p)-1 )
    {

        aggCartella( p->cart_g, genCartella(estr));

        i++;
    }

}

Giocatore *leggiSuccG(Giocatore *g)
{
    return g->next_g;
}

Giocatore *leggiNodoG(Giocatore *g, int pos)
{

    int posizione = 1;
    Giocatore * comodo = NULL;
    Giocatore * corrente = g;

    if ( isSetGiocatore(g) )
    {
        while ( pos != posizione )
        {
          posizione++;
          corrente = leggiSuccG(corrente);

        }

          comodo = corrente;

    }
    return comodo;
}

int scriviTotG(ListaGiocatori *g,int numg)
{
    int errore = ENOTF;

    if ( !isSetGiocatore(g->list_g) || numg < 1 )
        errore = ETOTG;
     else g->num_giocatori = numg;

   return errore;
}

int leggiTotG(ListaGiocatori *g)
{
    int errore = ENOTF;

    if ( !g )
        errore = ELG;


    return ( errore == ELG ) ? errore : g->num_giocatori;
}

int isSetGiocatore(Giocatore *g)
{

    /*
        Se il giocatore è diverso da NULL ritorna 1,
        altrimenti zero.
    */
    return ( g ) ? 1 : 0;
}

int leggiTotGiocImpostazioni( Impostazioni *imp )
{
    int errore = ENOTF;

    if ( !imp )
        errore = ERITOTG;

    return ( errore == ERITOTG) ? errore : imp->num_tot_giocatori;
}

int leggiDimImpostazioni( Impostazioni *imp )
{
    int errore = ENOTF;

    if ( !imp )
        errore = ERIDIMT;
    else
        if ( imp->dim_tombolone < 90 )
            errore = ERIDIMT;


    return ( errore == ERIDIMT ) ? errore : imp->dim_tombolone;

}

int leggiNumCartelleImpostazioni( Impostazioni *imp )
{
    int errore = ENOTF;

    if ( !imp )
        errore = ERINUMC;
    else
        if ( imp->max_cartelle < 1 || imp->max_cartelle > 6 )
            errore = ERINUMC;

    return ( errore == ERINUMC ) ? errore : imp->max_cartelle;

}

Boolean leggiAudiovImpostazioni( Impostazioni *imp )
{
    return imp->audiov;
}

Boolean leggiAudioNumImpostazioni( Impostazioni *imp )
{
    return imp->audionum;
}


int scriviTotGiocImpostazioni( Impostazioni *imp, int numgioc )
{
    int errore = ENOTF;

    if ( imp == NULL )
        errore = EI;
    else
        if ( numgioc < 2 )
            errore = EINUMG;
    else
        imp->num_tot_giocatori = numgioc;


    return errore;

}


int scriviDimImpostazioni( Impostazioni *imp, int dim )
{
    int errore = ENOTF;
    int mod = 0;

    if ( imp == NULL )
        errore = EI;
    else
        if ( dim < 90)
            errore = EIDIMT;
    else
        if ( ( mod = dim % 90 ) != 0 )
            dim = dim - mod;

    if ( errore == ENOTF )
        imp->dim_tombolone = dim;

    return errore;
}

int scriviNumCartelleImpostazioni ( Impostazioni *imp, int numcart )
{
    int errore = ENOTF;

    if ( imp == NULL )
        errore = EI;
    else
        if ( numcart < 1 || numcart > 6 )
            errore = EINUMCART;
    else
        imp->max_cartelle = numcart;

    return errore;
}

void scriviAudioVImpostazioni( Impostazioni *imp, Boolean flag )
{
    imp->audiov = flag;

}

void scriviAudioNumImpostazioni( Impostazioni *imp, Boolean flag )
{
     imp->audionum = flag;

}

/* Funzioni di gestione del Tombolone */

int initTombolone( Tombolone *tomb, int dim )
{
    int row_tomb; /* Contatore che tiene conto delle righe del tombolone */
    int i, j; /* Contatori che servono per scorrere le righe e le colonne delle singole cartelle del Tombolone. */
    int k = 0; /* Tiene conto */
    int k1 = 0;
    int error_flag = ENOTF;

    /*
        Dovendo avere necessariamente delle cartelle del tombolone che hanno un numero di elementi
        multiplo di 90( 90 compreso ) ed essendo il numero di elementi di una singola cartella pari a 30,
        le dimensioni del tombolone saranno pari alla dimensione diviso 30 che rappresenterà il numero di righe
        e le colonne saranno fisse a 2
    */

    scriviColTombolone(tomb, 2);
    error_flag = scriviRigheTombolone(tomb, dim / 30);

    if ( error_flag != ERTOMB )
    {
        /* <<<  Allocazione delle singole cartelle del tombolone >>>>>> */
        tomb->cart_tomb = malloc( leggiRigheTombolone(tomb) * sizeof(Cart_Tomb* ) );
        if ( !tomb->cart_tomb )
        {
            clrscr();
            perror("MALLOC ERRROR ::> ");
            error_flag = EITOMB;

        }
        if ( error_flag != EITOMB )
        {
            for ( i = 0; i < leggiRigheTombolone(tomb); i++ )
            {
                *(tomb->cart_tomb+i) = malloc( leggiColTombolone(tomb) * sizeof(Cart_Tomb));
                if ( !(*(tomb->cart_tomb + i ) ) )
                {
                    clrscr();
                    perror("MALLOC ERROR ::> ");
                    getch();
                    error_flag = EITOMB;
                }
            }
            if ( error_flag != EITOMB )
            {
                /* Crea la prima parte del tombolone inizializzato tutti i valori in modo corretto*/
                for ( row_tomb = 0; row_tomb < leggiRigheTombolone(tomb); row_tomb++ )
                {

                    for ( i = 0; i < CTOMBR; i++ )
                    {
                        for ( j = 0; j < CTOMBC; j++ )
                        {
                            /*
                                Nella prima parte del tombolone saranno presenti tutte le quintuple
                                che contengono numeri che vanno da 1 a 5, da 11 a 15, da 21 a 25,
                                da 31 a 35, da 41, 45 e così via quindi adopero tale formula per poter
                                inizializzare correttamente tali valori.

                            */
                            scriviNumTombolone(tomb->cart_tomb[row_tomb][0],i,j,  j + 1 + ( k * 10) );
                            scriviNumFlagTombolone(tomb->cart_tomb[row_tomb][0], i,j, EXIST);

                        }
                        k++;
                    }

                }

                k = 0;

                /* Provvede a creare la seconda parte del tombolone*/
                for ( row_tomb = 0; row_tomb < leggiRigheTombolone(tomb); row_tomb++ )
                {

                    for ( i = 0; i < CTOMBR; i++ )
                    {
                        for ( j = 0, k1 = 5; j < CTOMBC; j++, k1++ )
                        {
                            /*
                                Nella seconda parte del tombolone invece saranno presenti tutti i
                                valori che vanno da 6 a 10, da 16 a 20, da 26 a 30 e così via.
                                La formula adoperata tiene conto di un contatore opportuno per poter
                                far si che i valori vengano correttamente inizializzati.
                                E.G.
                                Il numero 16 viene generato grazie all'espressione
                                5 + 1 + ( 1 * 10 )
                                Il numero 17 viene generato grazie all'espressione
                                6 + 1 + ( 1* 10 )


                            */
                            scriviNumTombolone(tomb->cart_tomb[row_tomb][1], i,j, k1 + 1 + ( k * 10) );
                            scriviNumFlagTombolone(tomb->cart_tomb[row_tomb][1],i,j,EXIST);

                        }

                        k++;
                    }

                }
            }

        }

    }
    else /* C'è stato uno specifico errore nell'inizializzazione del tombolone. */
        error_flag = EITOMB;


    return error_flag;


}


int scriviNumTombolone( Cart_Tomb cart_tomb, int i, int j, int num )
{
    int errore = ENOTF;

    if ( ( i < 0 || i > CTOMBR) || ( j < 0 || j > CTOMBC) )
        errore = ENUMT;
    else
        cart_tomb[i][j].num = num;

    return errore;
}

int leggiNumTombolone( Cart_Tomb cart_tomb,  int i, int j )
{
    int errore = ENOTF;

    if ( ( i < 0 || i > CTOMBR) || ( j < 0 || j > CTOMBC) )
        errore = ERNUMT;


    return ( errore == ERNUMT ) ? errore : cart_tomb[i][j].num;

}

int scriviNumFlagTombolone( Cart_Tomb cart_tomb,  int i, int j, flag f )
{
    int errore = ENOTF;

    if ( ( i < 0 || i > CTOMBR) || ( j < 0 || j > CTOMBC) )
        errore = ENUMT;
    else
        cart_tomb[i][j].checked = f;

    return errore;
}

int leggiNumFlagTombolone( Cart_Tomb cart_tomb, int i, int j )
{
    int errore = ENOTF;

    if ( ( i < 0 || i > CTOMBR) || ( j < 0 || j > CTOMBC) )
        errore = ERNUMT;

    return ( errore == ERNUMT ) ? errore : cart_tomb[i][j].checked;
}

int scriviRigheTombolone(Tombolone *tomb, int righe )
{
    int errore = ENOTF;

    if ( righe < 0 || righe >= 18 )
        errore = ERTOMB;
    else
        tomb->righe = righe;

    return errore;

}

int leggiRigheTombolone( Tombolone *tomb )
{
    return tomb->righe;
}

int scriviColTombolone( Tombolone *tomb, int col )
{
    int errore = ENOTF;

    if ( col != 2 )
        errore = ECTOMB;
    else
        tomb->col = col;

    return errore;
}

int leggiColTombolone( Tombolone *tomb )
{
    return tomb->col;
}


char *leggiNomeTopTen( Topten *t )
{

    return ( !t ) ? NULL : t->nome;
}

int leggiPuntTopTen( Topten *t )
{
    return t->punteggio;
}

int scriviNomeTopTen ( Topten *t, char *nome )
{
    int errore = ENOTF;

    t->nome = malloc( ( strlen(nome)+ 1 ) * sizeof(char));
    if ( !t->nome )
    {
        errore = ENOMTOP;
    }
    else
        strcpy( t->nome, nome);

    return errore;
}

int scriviPunteggioTopTen( Topten *t, int punt )
{
    int errore = ENOTF;

    if ( punt < 0 )
        errore = EPUNTOP;
    else
        t->punteggio = punt;

    return errore;

}

char *leggiNomePremio ( Premio *p )
{
    return p->nome_premio;
}

int leggiVincitaPremio( Premio *p )
{
    return p->tot_cash;

}

int scriviNomePremio( Premio *p, char *nome )
{
    int errore = ENOTF;

    if ( strlen(nome) > 9 )
        errore = ENOMPR;
    else
        strcpy( p->nome_premio, nome);

    return errore;
}

void scriviVincitorePremio( Premio *p, int id )
{
    p->id_vincitore = id;
}

int leggiVincitorePremio( Premio *p )
{
    return p->id_vincitore;
}

void scriviVincitaPremio( Premio *p, int tot_premio )
{
    p->tot_cash = tot_premio;
}


Boolean leggiUscitoPremio( Premio *p )
{
    return p->checked;
}

void scriviUscitoPremio( Premio *p, Boolean f )
{

    p->checked = f;

}
void scriviIdSchedaPremio( Premio *p, int id_scheda )
{
    p->id_scheda = id_scheda;

}

int leggiIdSchedaPremio( Premio *p )
{
    return p->id_scheda;
}



void stampaCelle( Card cart, int x, int y, int dim )
{
    int i, j;

    int color = 62;

    textcolor(color);
    gotoxy(x,y);

    if( dim == 90)
    {
       for(j=0;j<CARTC;j++)
        printf("______");
        gotoxy(x,y+=2);

        for(i=0;i<CARTR; i++)
        {
            for(j=0;j<CARTC;j++)
            {
                if( leggiCheckedCard(cart,i,j) == EXIST )
                {

                    textcolor(color+1);
                    printf("  %2d  ", leggiNumeroCard(cart,i,j));

                }
                else
                 if (leggiCheckedCard(cart, i ,j) == TRUE)
                 {
                     textcolor(58);
                     printf("  %2d  ", leggiNumeroCard(cart,i,j));
                 }
                 else
                {
                    printf("  ");
                    textcolor(204);
                    printf("  ");
                    textcolor(color);
                    printf("  ");
                }
            }
            gotoxy(x,++y);
            for(j=0;j<CARTC;j++)
            {
                textcolor(color);
                printf("______");
            }
            gotoxy(x,y+=2);
        }

    }

    else
     if( dim < 1080)
     {
         for(j=0;j<CARTC;j++)
        printf("_______");
        gotoxy(x,y+=2);

        for(i=0;i<CARTR; i++)
        {
            for(j=0;j<CARTC;j++)
            {
                if( leggiCheckedCard(cart,i,j) == EXIST )
                {

                    textcolor(color+1);
                    printf("  %3d  ", leggiNumeroCard(cart,i,j));
                    //scriviCheckedCard(cart,i,j,FALSE);
                }
                else
                 if (leggiCheckedCard(cart, i ,j) == TRUE)
                 {
                     textcolor(58);
                     printf("  %3d  ", leggiNumeroCard(cart,i,j));
                 }
                 else
                {
                    printf("  ");
                    textcolor(204);
                    printf("   ");
                    textcolor(color);
                    printf("  ");
                }
            }
            gotoxy(x,++y);
            for(j=0;j<CARTC;j++)
            {
                textcolor(color);
                printf("_______");
            }
            gotoxy(x,y+=2);
        }

     }


  textcolor(color+1);

}
void stampaCartelle( Giocatore *p, Estrazione *estr )
{
    Cartella *cart_corr = leggiCartella(p);
    clrscr();
    int x = 1, y = 1;
    int cont = 1;
    int ncart = leggiNumCartelleGioc(p);
    int contpag = 1;

    gotoxy(x,y);

    if(ncart > 3)
        printf("Cartelle Giocatore %d - Pagina %d",leggiIdGiocatore(p), contpag);
    else
        printf("Cartelle Giocatore %d",leggiIdGiocatore(p));

    gotoxy( x, y += 1);
    while( isSetCartella( cart_corr ) )
    {

        printf("ID CARTELLA %d ", leggiIdCartella(cart_corr));
        gotoxy(x, y+=2);
        stampaCelle( cart_corr->cart ,x,y, leggiTotNumeri(estr));
        y += 10;
        if((cont++) == 3 && ncart > 3 )
        {
            x = 1;
            y = 1;
            cont = 0;
            printf("Premere un tasto qualsiasi per cambiare pagina");
            getch();
            clrscr();
            printf("Cartelle Giocatore %d - Pagina %d",leggiIdGiocatore(p), ++contpag);
            gotoxy( x, y += 1);
        }
        cart_corr = leggiSuccC(cart_corr);
    }
    x = 1;
    gotoxy(x,++y);
    printf("Premere un tasto qualsiasi per tornare alla partita");
    getch();
}


void stampaPremio( ListaPremi premi, int curr_prize, Giocatore *win_player, int cont_c )
{
    int x = 1, y = 14;
    gotoxy(x,y++);
    /* Se il giocatore non è specificato( win_player == NULL ), allora ha vinto il Croupier */
    if ( !win_player )
        printf("\nIl Croupier ha fatto %s e ha vinto %d\n",
                ( strcmp(leggiNomePremio(&premi[curr_prize] ), "Bingo" ) == 0 ) ? "Tombola" : leggiNomePremio(&premi[curr_prize]),
                leggiVincitaPremio(&premi[curr_prize]) );
    /* In caso contrario, avrà vinto un giocatore preciso e quindi provvedo a stampare tutte le informazioni relative*/
    else
    {
        scriviVincitorePremio( &premi[curr_prize], leggiIdGiocatore( win_player) );
        scriviIdSchedaPremio(&premi[curr_prize], cont_c);
        printf("\nGiocatore %d - ha fatto %s e ha vinto %d con la cartella %d\n",
                leggiVincitorePremio( &premi[curr_prize]),
                ( strcmp(leggiNomePremio(&premi[curr_prize] ), "Bingo" ) == 0 ) ? "Tombola" : leggiNomePremio(&premi[curr_prize]),
                leggiVincitaPremio(&premi[curr_prize]), leggiIdSchedaPremio(&premi[curr_prize]) );


    }

    /*scriviUscitoPremio( &premi[curr_prize], T);*/


}



void controllaPremio( ListaGiocatori *list, Tombolone *tomb, Estrazione *estr, ListaPremi premi )
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
    int in_a_row = 0; /* variabile intera che rappresenta i numeri che devono essere presenti in una riga per vincere il premio */
    int curr_prize = 0; /* posizione nell'array dei premi che determina il premio da controllare attualmente. */
    Giocatore *gioc_corr; /* Puntatore a giocare che garantisce l'accesso a tutti gli elementi della lista d giocatori*/
    Cartella *cart_corr; /* Puntatore a cartella che consente di scorrere la lista di cartelle */
    int *id_vincenti = NULL; /* Array necessario per poter gestire appropriatamente i giocatori che vincono il medesimo premio*/
    int cont_id = 0; /* contatore utilizzato per scorrere il vettore di id */
    int vincita = 0; /* Vincita di ogni singolo giocatore */
    int num_vincenti = 0; /* Numero effettivo di elementi presenti all'interno del vettore */
    int gioc_vince = 0; /* Stabilisce se il giocatore corrente ha vinto o meno con almeno una cartella */
    int vince_croupier = 0; /* Stabilisce se è stato il croupier ha vincere */


    for( i = 0; i < TOT_PRIZE && premi[i].checked == TRUE; i++ )
       /* NON FA NULLA*/ ;
    /* *************************************************************
        ASSERZIONE : il valore della variabile i all'uscita del for,
        rappresenterà la posizione nell'array nella quale sarà
        presente il premio da analizzare.
        ************************************************************
     */
    curr_prize = i;

    switch( premi[i].nome_premio[0] )
        {
            case 'A' : in_a_row = 2; break;
            case 'T' : in_a_row = 3; break;
            case 'Q' : in_a_row = 4; break;
            case 'C' : in_a_row = 5; break;
            case 'B' : in_a_row = 10; break;
        }

    if ( in_a_row != 10 )
    {

        /* <---------------- CONTROLLO VINCITORI PREMIO ATTUALE --------------------------->*/

        /* <<<<<<<<<<<<<<<<<<<<<<<<<< Controllo Tombolone >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> */
        for( i = 0; i < leggiRigheTombolone(tomb); i++ )
            for ( j = 0; j < leggiColTombolone(tomb); j++ )
                if ( controllaCartTomb( tomb->cart_tomb[i][j], in_a_row) == in_a_row )
                {
                    stampaPremio( premi, curr_prize,NULL, 0 );
                    vince_croupier = 1;
                    wait(2);
                    scriviUscitoPremio( &premi[curr_prize], T);
                }
        if ( vince_croupier != 1 )
        {



            /* <<<<<<<<<<<<<<<<<<<<<<< Controllo delle cartelle dei giocatori >>>>>>>>>>>>>>>>> */
            for( gioc_corr = leggiPrimoGioc(list); isSetGiocatore(gioc_corr);  gioc_corr = leggiSuccG(gioc_corr) )
            {

                for ( cart_corr = leggiCartella(gioc_corr); isSetCartella(cart_corr); cart_corr = leggiSuccC(cart_corr) )
                {
                    if ( controllaCartella( cart_corr, in_a_row) == in_a_row )
                    {
                        stampaPremio( premi, curr_prize, gioc_corr, leggiIdCartella(cart_corr) );
                        stampaCelle( cart_corr->cart, 1, 20, leggiTotNumeri(estr));
                        wait(2);
                        gioc_vince = 1;
                        scriviUscitoPremio( &premi[curr_prize], T);
                    }
                }


                if ( gioc_vince == 1 )
                {

                    if ( num_vincenti == 0 )
                    {
                        /*
                            Se num_vincenti è uguale a zero, questo è il primo
                            giocatore a vincere il premio, quindi è necessario
                            allocare memoria per il vettore degli id.
                            Poi si incrementa num_vincenti che rappresenterà
                            il primo giocatore vincente.


                        */
                        id_vincenti = malloc( sizeof(int) );
                        if ( !id_vincenti )
                        {
                            clrscr();
                            perror("MALLOC ERROR ::> ");
                            getch();
                            exit(-1);
                        }
                        num_vincenti++;
                        id_vincenti[cont_id++] = leggiIdGiocatore(gioc_corr);
                    }
                    else
                    {
                        /*
                            In tal caso vi è più di un giocatore che ha vinto
                            il premio corrente, quindi bisogna incrementare
                            di una unità la dimensione del vettore di id.

                        */
                        id_vincenti = realloc( id_vincenti,  ( ++num_vincenti )* sizeof(int));
                        if ( !id_vincenti )
                        {
                            clrscr();
                            perror("REALLOC ERROR ::> ");
                            getch();
                            exit(-1);
                        }

                        id_vincenti[cont_id++] = leggiIdGiocatore(gioc_corr);
                    }

                    gioc_vince = 0;
                }

            }
        }



    }
    else
    {

        /* <------------------------- Controllo Vincitori Tombola -------------------------------------->  */

        /* <<<<<<<<<<<<<<<<<<<<<<<<<<< Controllo del Tombolone >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
        for ( i = 0; i < leggiRigheTombolone(tomb); i++ )
            for ( j = 0; j < leggiColTombolone(tomb); j++ )
                if ( controllaCartTomb( tomb->cart_tomb[i][j], in_a_row) == in_a_row )
                {
                    stampaPremio( premi, curr_prize, NULL, 0 );
                    wait(2);
                    vince_croupier = 1;
                    scriviUscitoPremio( &premi[curr_prize], T);
                }

        /* <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/


        /* <<<<<<<<<<<<<<<<<<<<<<<<<< Controllo delle cartelle dei giocatori >>>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
        if ( vince_croupier != 1 )
        {

            for( gioc_corr = leggiPrimoGioc(list); isSetGiocatore(gioc_corr);  gioc_corr = leggiSuccG(gioc_corr) )
            {
                for ( cart_corr = leggiCartella(gioc_corr); isSetCartella(cart_corr); cart_corr = leggiSuccC(cart_corr) )
                {
                    if ( controllaCartella( cart_corr, in_a_row) == in_a_row )
                    {
                        stampaPremio( premi, curr_prize, gioc_corr, leggiIdCartella(cart_corr) );
                        stampaCelle( cart_corr->cart, 1, 20, leggiTotNumeri(estr));
                        wait(2);
                        gioc_vince = 1;
                        scriviUscitoPremio( &premi[curr_prize], T);
                    }
                }
                if ( gioc_vince == 1 )
                {

                    if ( num_vincenti == 0 )
                    {
                        /*
                            Se num_vincenti è uguale a zero, questo è il primo
                            giocatore a vincere il premio, quindi è necessario
                            allocare memoria per il vettore degli id.
                            Poi si incrementa num_vincenti che rappresenterà
                            il primo giocatore vincente.


                        */
                        id_vincenti = malloc( sizeof(int) );
                        if ( !id_vincenti )
                        {
                            clrscr();
                            perror("MALLOC ERROR ::> ");
                            getch();
                            exit(-1);
                        }
                        num_vincenti++;
                        id_vincenti[cont_id++] = leggiIdGiocatore(gioc_corr);
                    }
                    else
                    {
                        /*
                            In tal caso vi è più di un giocatore che ha vinto
                            il premio corrente, quindi bisogna incrementare
                            di una unità la dimensione del vettore di id.

                        */
                        id_vincenti = realloc( id_vincenti,  ( ++num_vincenti )* sizeof(int));
                        if ( !id_vincenti )
                        {
                            clrscr();
                            perror("REALLOC ERROR ::> ");
                            getch();
                            exit(-1);
                        }
                        id_vincenti[cont_id++] = leggiIdGiocatore(gioc_corr);
                    }

                    gioc_vince = 0;
                }

            }

        }

        /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
    }


    /* /////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////// FASE DI ASSEGNAZIONE DEI PREMI /////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////

    */

    /*
        Calcolo la vincita del singolo giocatore divendo la posta in palio del premio corrente
        per il numero di giocatori che hanno vinto il premio( indicato dalla variabile cont_id ).
    */
    if ( vince_croupier == 0 )
    {


        if( num_vincenti > 1 )
        {
            vincita = leggiVincitaPremio(&premi[curr_prize]) / num_vincenti;


            for ( cont_id = 0; cont_id < num_vincenti; cont_id++ )
            {
                gioc_corr = leggiNodoG( leggiPrimoGioc(list), id_vincenti[cont_id] );
                scriviCashGiocatore( gioc_corr, leggiCashGiocatore(gioc_corr) + vincita);

            }
        }
        else if ( num_vincenti == 1 )
        {
            /*
                Se num_vincenti è uguale ad 1, ha vinto unicamente un giocatore quindi l'intera posta in palio
                va assegnata a quest'ultimo.
            */
            vincita = leggiVincitaPremio(&premi[curr_prize]);
            gioc_corr = leggiNodoG( leggiPrimoGioc(list), id_vincenti[0]);
            scriviCashGiocatore(gioc_corr, leggiCashGiocatore(gioc_corr) + vincita);
        }

        free(id_vincenti);
    }
}

void initPremio( ListaPremi premi, int num_gioc, int num_cartelle )
{
    int i = 0;
    int vincita;

    for ( i = 0; i < TOT_PRIZE; i++ )
    {
        vincita = num_gioc * num_cartelle * ( i + 1);
        scriviVincitaPremio(&premi[i], vincita );
    }
}
int estraiNumero( Estrazione *estr )
{
    int rand_number;

    if ( !leggiVettoreNumeri(estr) )
    {
        estr->numbers = (int*)malloc( leggiTotNumeri(estr) * sizeof(int));
        if ( !leggiVettoreNumeri(estr))
        {
            clrscr();
            perror("MALLOC ERROR ::>> ");
            getch();
            exit(-1);
        }
    }

    if ( leggiTotNumEstratti(estr) == 0 )
    {
        scriviTotNumEstratti( estr, 0);
        riempiNumeri(leggiVettoreNumeri(estr), 1, leggiTotNumeri(estr));
        mischiaNumeri( leggiVettoreNumeri(estr), leggiTotNumeri(estr) );
        rand_number = estr->numbers[estr->tot_numeri_estr++];

    }
    else
        rand_number = estr->numbers[estr->tot_numeri_estr++];



    return rand_number;

}

int leggiTotNumEstratti( Estrazione *estr )
{
    return estr->tot_numeri_estr;
}

int scriviTotNumEstratti( Estrazione *estr, int tot )
{
    int errore = ENOTF;

    if ( tot < 0 )
        errore = ENUMESTR;
    else
        estr->tot_numeri_estr = tot;

    return errore;
}

int leggiTotNumeri( Estrazione *estr )
{
    return estr->tot_numeri;
}

int scriviTotNumeri( Estrazione *estr, int dim  )
{
    int errore = ENOTF;

    if ( dim < 0 )
        errore = ETOTESTR;
    else
        estr->tot_numeri = dim;

    return errore;
}

int *leggiVettoreNumeri( Estrazione *estr )
{
    return estr->numbers;
}

int allocVettoreNumeri( Estrazione *estr, int dim )
{
    int errore = ENOTF;
    if ( dim < 0 )
        errore = EVET;
    else
    {
        estr->numbers = (int*)malloc( leggiTotNumeri(estr) * sizeof(int));
        if ( !estr->numbers )
        {
            errore = EVET;
        }
    }


    return errore;

}

void initVettoreNumeri( Estrazione *estr )
{
    estr->numbers = NULL;
}


int leggiNumGen( Estrazione *estr )
{
    return estr->num_gen;
}

int scriviNumGen( Estrazione *estr, int num_gen )
{
    int errore = ENOTF;

    if ( num_gen < 0 )
        errore = ENUMGEN;
    else
        estr->num_gen = num_gen;

    return errore;
}

void stampaTombolone( Tombolone *tomb, int cont )
{
    int row_tomb;
    int i, j;
    int posX = 1, posY = 1;

    for ( row_tomb = cont; row_tomb < cont+3;  row_tomb++)
    {

       for ( i = 0; i < CTOMBR; i++ )
        {
            for ( j = 0; j < CTOMBC;j++)
            {
                if ( leggiNumFlagTombolone(tomb->cart_tomb[row_tomb][0], i, j ) == TRUE )
                    textcolor(58);

                printf("|%4d | ", leggiNumTombolone(tomb->cart_tomb[row_tomb][0], i, j ) );
                textcolor(63);


            }
            gotoxy(posX,++posY);


        }
        gotoxy(posX, ++posY);


    }

    posX = 40;
    posY = 1;
    gotoxy(posX, posY);
    for ( row_tomb = cont; row_tomb < cont+3;  row_tomb++)
    {

       for ( i = 0; i < CTOMBR; i++ )
        {
            for ( j = 0; j < CTOMBC;j++)
            {
                if ( leggiNumFlagTombolone(tomb->cart_tomb[row_tomb][1], i, j ) == TRUE )
                    textcolor(58);
                printf(" |%4d |", leggiNumTombolone(tomb->cart_tomb[row_tomb][1],i,j) ) ;
                textcolor(63);

            }
            gotoxy(posX,++posY);


        }
        gotoxy(posX, ++posY);


    }
    printf("\n");

}

void stampaFile( char *file )
{
     FILE *fp;
     int tot_char = 0;
     char c;
     char filename[MAX_PATH];
     int key = 0;


    if ( !snprintf(filename, MAX_PATH, "data\\%s", file) )
    {
        clrscr();
        perror("ERRORE CREAZIONE DEL PATHNAME ::> ");
        getch();
        exit(-1);
    }
    clrscr();
     system("COLOR 3F");



     if ( ( fp = fopen(filename, "r") ) == NULL )
     {
        clrscr();
        perror("ERROR FILE ::> ");
        getch();

        exit(-1);


     }
     else
     {
        int flag = 0;

        while( ( c = fgetc(fp) ) != EOF  && key != 27 )
        {
            if( tot_char > 1575 )
            {

                printf("\nPREMI INVIO PER ANDARE ALLA PAGINA SUCCESSIVA O ESC PER USCIRE ");
                while( ( ( key = getch() ) != 13 ) && ( key != 27 ) )
                    /* non fa nulla */;

                if ( key == ENTER_KEY )
                {
                    clrscr();
                    system("COLOR 3F");
                    tot_char=0;
                    flag = 1;


                }
                else if ( key == ESC_KEY )
                    break;



                }

                printf("%c", c);
                tot_char++;
        }

        if ( flag == 1 )
            getch();
     }



    fclose(fp);

}

Topten *initTopten( void )
{
    return NULL;
}
Topten* leggiSuccTop( Topten *top )
{

    return top->next_top;
}

int isSetTopten( Topten *top )
{
    return ( top ) ? 1 : 0;
}

Topten *allocTopten( void )
{
    return malloc( sizeof(Topten));
}

void aggTopten( Topten *top, Topten *nuovo_gioc )
{

    if ( !isSetTopten(leggiSuccTop(top) ) )
    {

        top->next_top = allocTopten();
        top = leggiSuccTop(top);
        *top = *nuovo_gioc;
    }
    else
        aggTopten( leggiSuccTop(top), nuovo_gioc);

}

void insOrdTopten( Topten *top, Topten *nuovo_gioc )
{
    Topten *prec_gioc = top, *gioc_corr;



    if ( leggiPuntTopTen(top) <= leggiPuntTopTen(nuovo_gioc) )
    {
        gioc_corr = allocTopten();
        *gioc_corr = *top;
        nuovo_gioc->next_top = gioc_corr;
        *top = *nuovo_gioc;

    }
    else
    {
        gioc_corr = top;
        prec_gioc = top;
        while ( isSetTopten(gioc_corr ) && leggiPuntTopTen(nuovo_gioc) <= leggiPuntTopTen(gioc_corr ) )
        {
            prec_gioc = gioc_corr;
            gioc_corr = leggiSuccTop(gioc_corr);

        }

        prec_gioc->next_top = nuovo_gioc;
        nuovo_gioc->next_top = gioc_corr;

    }
}

Topten *controllaTopten( Topten *top, Giocatore *nuovo_gioc )
{
    Topten *gioc_corr, *new_top = allocTopten();
    int flag = 0;
    char buffer[8];
    char *suppl = NULL;
    int res = 1;


    for ( gioc_corr = top; isSetTopten(gioc_corr) && flag == 0; gioc_corr = leggiSuccTop(gioc_corr) )
        if ( leggiPuntTopTen(gioc_corr) < leggiCashGiocatore(nuovo_gioc) )
        {

            do
            {
                printf("Nuovo record.\nInserisci Nickname per entrare nella topten ( MAX 6 caratteri ) : ");
                suppl = fgets(buffer,sizeof(buffer), stdin);

                if ( ( strcmp( buffer, "\n") == 0 ) || ( suppl == NULL ) ||  ( strcmp(buffer, "\r") == 0 ) )
                {
                    res = 0;
                    stampaFile("topten.txt");
                    fprintf(stderr, "SCELTA IMMESSA NON VALIDA. Inserisci 6 caratteri alfanumerici!\nPremi un tasto per continuare");
                    getch();
                    clrscr();
                    stampaFile("topten.txt");
                    //while( getchar() != '\n' );
                }
                else
                {
                    while( getchar() != '\n');
                    res = 1;
                }
            }while( res == 0 );

            chomp(buffer);
            /* crea nuova struttura di tipo topten per effettuare l'inserimento nella lista*/
            scriviNomeTopTen(new_top, buffer);
            scriviPunteggioTopTen(new_top, leggiCashGiocatore(nuovo_gioc) );
            new_top->next_top = initTopten();
            flag = 1;
        }

    return new_top;

}

void stampaTopTenSuFile( Topten *toplist )
{
    FILE *top_file;
    Topten *curr_top;
    int cont_gioc;

    if ( ( top_file = fopen("topten.txt", "w") ) == NULL )
    {
        clrscr();
        perror("ERROR FILE ::> ");
        getch();
        exit(-1);
    }

    for ( curr_top = toplist, cont_gioc = 1;
        isSetTopten(curr_top) && cont_gioc <= 10;
         curr_top = leggiSuccTop(curr_top), cont_gioc++ )
    {

        fprintf(top_file, "%s %d\n", leggiNomeTopTen(curr_top), leggiPuntTopTen(curr_top));
    }

    fclose(top_file);
}

void stampaTopTen( Topten *toplist )
{
    Topten *curr_top;
    int cont_gioc;

    if ( leggiPuntTopTen(toplist) == 0 )
    {
        printf("La topten risulta essere vuota!!\nE' stato manipolato il file!Ricreare il file topten.txt .\n");


    }
    else
    {
         printf("POS\t NOME GIOCATORE\t TOT. PUNTEGGIO \n");

        for ( curr_top = toplist, cont_gioc = 1;
            isSetTopten(curr_top) && cont_gioc <= 10;
            curr_top = leggiSuccTop(curr_top), cont_gioc++ )
        {
            switch ( cont_gioc )
            {
                case 1 : textcolor(12); break;
                case 2: textcolor(14); break;
                case 3 : textcolor(10); break;
                default : textcolor(15); break;
            }

            printf("%d)\t\t%6s\t\t  %4d\n\n", cont_gioc, leggiNomeTopTen(curr_top), leggiPuntTopTen(curr_top));

        }
   }

    textcolor(63);
    nascondiCursore();
    /*cont_gioc = 0;
    while( cont_gioc++ < 90 )
    {
        textcolor(cont_gioc);
        printf("PROVA %d", cont_gioc);
        getch();
    } */




}

void liberaTopten( Topten *top )
{
    Topten *gioc_temp = NULL;
    Topten *gioc_corr = NULL;

    for ( gioc_corr = leggiSuccTop(top); isSetTopten(gioc_corr);free(gioc_temp) )
    {
        gioc_temp = gioc_corr;
        gioc_corr = leggiSuccTop(gioc_corr);

    }

}

