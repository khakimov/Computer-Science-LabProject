/*
 * TombolaFunction.c
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ & Nazar Chekalin
 */
#include "CardManager.h"
#include "TombolaFunction.h"

void getTopten( Topten *list )
{
    int cont_gioc;
    Topten *curr_top; /* Nodo topten attuale */
    FILE *top_file;
    char buffer[30]; /* Stringa contenente il nome del giocatore appena letto dal file*/
    int punt;/* valore intero che rappresenta il punteggio del giocare corrente */

    if ( ( top_file = fopen("topten.txt", "r") ) == NULL )
    {
        perror("ERROR FILE ::>  topten2");
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
                addTopten(list, curr_top);

        }


    }

    fclose(top_file);

}

void topten( ListaGiocatori *listag )
{
    Giocatore *max_gioc, *curr_gioc;
    Topten toplist, *new_gioc;

    printFile("topten.txt");

    for ( max_gioc = leggiPrimoGioc(listag),curr_gioc = leggiPrimoGioc(listag);
          isSetGiocatore(curr_gioc);
          curr_gioc = getNextG(curr_gioc) )
    {
      if ( getCashGiocatore(curr_gioc ) > getCashGiocatore(max_gioc ) )
          max_gioc = curr_gioc;
    }


    getTopten(&toplist);

    if ( ( new_gioc = checkTopten(&toplist, max_gioc) ) != NULL )
    {
        insOrdTopten(&toplist, new_gioc);
        clrscr();
        printFile("topten.txt");
        printTopTen(&toplist);
    }

}
int GiocaPartita ( ListaGiocatori *listag, Impostazioni *imp, Estrazione *estr, Tombolone *tomb)
{
    int num_estr = 0;
    int car;
    int exit  = 0;
    int x = 1;

    /*
        E' necessario controllare e differenziare il caso in cui si sta iniziando una nuova parita
        nella quale è necessario inizializzare la struttura, e il caso in cui si sta riprendendo la partita
        e in quel caso, non bisogna toccare nulla!
    */
    scriviNumGen(estr, leggiDimImpostazioni(imp));
    if ( leggiTotNumeri(estr) == leggiDimImpostazioni(imp)  )
    {

        initEstrazione ( estr, imp );

        scriviTotNumEstratti(estr, 0);
    }


    clrscr();
    printTombolone(tomb);
    gotoxy(x,33);
    printf("INIVIO/SPAZIO - Estrai Numero     ESC - Esci     s - Salva Partita");
    gotoxy(1,13);

    while( !finePartita() && num_estr != -1  && exit != 1 )
    {
        if( leggiTotNumEstratti(estr) != 0 && leggiTotNumEstratti(estr) % 10 == 0)
        {
         clrscr();
         printTombolone(tomb);
         gotoxy(1,13);
         printf("NUMERO ESTRATTO : %3d ", num_estr);
         gotoxy(x,33);
         printf("INIVIO/SPAZIO - Estrai Numero     ESC - Esci     s - Salva Partita");
         gotoxy(1,13);
        }
        switch( ( car = getch() ) )
        {
            case 13 :
                num_estr = estraiNumero(estr);
                clrscr();
                printTombolone(tomb);
                gotoxy(1,13);
                printf("NUMERO ESTRATTO : %3d ", num_estr);
                gotoxy(x,33);
                printf("INIVIO/SPAZIO - Estrai Numero     ESC - Esci     s - Salva Partita");
                gotoxy(1,13);
                controllaNumero(listag, tomb, num_estr);
                clrscr();
                printTombolone(tomb);
                gotoxy(1,13);
                printf("NUMERO ESTRATTO : %3d ", num_estr);
                gotoxy(x,33);
                printf("INIVIO/SPAZIO - Estrai Numero     ESC - Esci     s - Salva Partita");
                gotoxy(1,13);
                if( leggiTotNumEstratti(estr) >= 2)
                    checkPrize(listag,tomb);

            break;

            case SAVE_KEY:
                salvaPartita(listag, tomb, premi, estr, imp);
            break;

            case ESC_KEY:
                exit = 1;
            break;
        }
    }

    if ( finePartita() )
    {
        clrscr();
        printFile("tombola.txt");
        printf("PUNTEGGI PARTITA CORRENTE \nGIOCATORE\t\tPUNTEGGIO\n");
        printClassifica(listag);
        getch();
        topten(listag);
    }



    return 0;
}

void printClassifica( ListaGiocatori *listag )
{
    int *punt_gioc = malloc( getTotG(listag) * sizeof(int) ) ;
    int *id_gioc = malloc( getTotG(listag) * sizeof(int));
    int i;
    int comodo_punt, comodo_id, scambio;
    Giocatore *curr_gioc;

    for ( curr_gioc = leggiPrimoGioc(listag), i = 0;
         isSetGiocatore(curr_gioc);
         curr_gioc = getNextG(curr_gioc), i++ )
    {
         punt_gioc[i] = getCashGiocatore(curr_gioc);
         id_gioc[i] = getIdGiocatore(curr_gioc);
    }

    while( scambio )
     {
      scambio = 0;
      for (i = 0; i < getTotG(listag)-1; i++)
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
    //printFile("tombola.txt");

    for ( i = 0; i < getTotG(listag); i++ )
    {
        switch ( i+1 )
        {
            case 1 : textcolor(28); break;
            case 2: textcolor(30); break;
            case 3 : textcolor(26); break;
            default : textcolor(63); break;
        }
        printf("Giocatore %d\t\t%4d\n", id_gioc[i], punt_gioc[i]);
    }
    free(punt_gioc);
    free(id_gioc);



}
int finePartita( void )
{
    int stato = 0;

    if( leggiUscitoPremio( &premi[TOT_PRIZE-1] ) == T )
        stato = 1;

    return stato;
}

void nuova_partita( Impostazioni *imp )
{
     ListaGiocatori lista;
     lista.list_g = initListaG();
     Giocatore *temp = NULL;
     int choice = 0;
     int i = 0;
     int flag = 0;
     int cont_id = 0;
     Estrazione estr;
     Tombolone tomb;


     if ( leggiDimImpostazioni(imp) < 0 || leggiNumCartelleImpostazioni(imp) > 1000 || leggiTotGiocImpostazioni(imp) > 1000 )
     {
        printf("Il gioco è stato avviato senza aver selezionato le impostazioni!\nIl gioco verrà avviato con le impostazioni di default!\n");
        scriviNumCartelleImpostazioni(imp,6);
        scriviTotGiocImpostazioni( imp,6);
        scriviDimImpostazioni( imp, 90);
        scriviAudioVImpostazioni( imp, T);
        scriviAudioNumImpostazioni( imp, F);

     }

     initEstrazione(&estr, imp);
     initTombolone(&tomb, leggiDimImpostazioni(imp));

    lista.list_g = allocGiocatore();
    setTotG(&lista, leggiTotGiocImpostazioni(imp));

    for ( temp = lista.list_g; i < getTotG(&lista) && !flag; i++, temp = allocGiocatore() )
    {
        clrscr();
        printFile("nuova.txt");
        printf("\nNUMERO GIOCATORI : %d", getTotG(&lista));
        printf("\nNUMERO CARTELLE : %d", leggiNumCartelleImpostazioni(imp));
        printf("\nDIMENSIONI TOMBOLONE : %d\n", leggiDimImpostazioni(imp));

        initGiocatore(temp, imp, &cont_id);
        createCartelle(temp, &estr);
        if( i > 0)
         addGiocatore(lista.list_g, temp);

        if( getIdGiocatore(temp) == 6)
            {
             do
             {
               clrscr();
               printFile("nuova.txt");
               printf("\nNUMERO GIOCATORI : %d", getTotG(&lista));
               printf("\nNUMERO CARTELLE : %d", leggiNumCartelleImpostazioni(imp));
               printf("\nDIMENSIONI TOMBOLONE : %d\n", leggiDimImpostazioni(imp));
               printf("\n\nOPZIONI UTENTE - Giocatore %d\n\n%s\n%s\n%s\n",
                        getIdGiocatore(temp),
                        "1) Visualizza Cartelle",
                        "2) Inizia il Gioco",
                        "3) Vai ad Impostazioni");
               printf("\nOpzione Digitata: ");
               scanf("%d", &choice);
               switch( choice )
               {
                case 1 : printCartelle( temp ); break;
                case 3 :
                    printf("ATTENZIONE SI STA PASSANDO ALLA SEZIONE IMPOSTAZIONI!\n");
                    impostazioni_gioco(imp);
                    flag = 1;
                break;

               }
             }
             while (choice == 1);
            }
        else
         do
         {
             clrscr();
             printFile("nuova.txt");
             printf("\nNUMERO GIOCATORI : %d", getTotG(&lista));
             printf("\nNUMERO CARTELLE : %d", leggiNumCartelleImpostazioni(imp));
             printf("\nDIMENSIONI TOMBOLONE : %d\n", leggiDimImpostazioni(imp));
             printf("\n\nOPZIONI UTENTE - Giocatore %d\n\n%s\n%s\n%s\n",
                getIdGiocatore(temp),
                "1) Visualizza Cartelle",
                "2) Passa al prossimo giocatore",
                "3) Vai ad Impostazioni");
            printf("\nOpzione Digitata: ");
                scanf("%d", &choice);
            switch( choice )
            {
                case 1 : printCartelle( temp ); break;
                case 3 :
                    printf("ATTENZIONE SI STA PASSANDO ALLA SEZIONE IMPOSTAZIONI!\n");
                    impostazioni_gioco(imp);
                    flag = 1;
                break;

            }
         }while( choice == 1);




    }
    if (!flag) GiocaPartita(&lista, imp, &estr, &tomb);
    gotoxy(1,25);

    /*for ( i = 1; i <= getTotG(&lista); i++ )
        delGiocatore(&lista, i);*/
}

void initEstrazione ( Estrazione *estr , Impostazioni *imp)
{
     scriviNumGen(estr, 0);
     scriviTotNumEstratti( estr, 0);
     initVettoreNumeri(estr);
     scriviTotNumeri(estr, leggiDimImpostazioni(imp));
}
void initGiocatore(Giocatore *gcomodo, Impostazioni *imp, int *cont)
{
     gcomodo->id = (*cont)+=1;
     gcomodo->num_cartelle = imp->max_cartelle;
     gcomodo->cash = 0;
     gcomodo->next_g = NULL;
     gcomodo->cart_g = NULL;



}
void bgcolor( int color )
{

    int num = 1;
    textcolor(color);
    gotoxy(1,1);

    while ((num++)<6001)
    printf(" ");
    gotoxy(1,1);

}
void impostazioni_gioco (Impostazioni *imp )
{
    char comando;
    int posizione = 1;
    int random = rand()%2;
    textcolor(58+random);

    clrscr();


    printFile("impostazioni.txt");
    textcolor(63);
    /* Inizializza la struttura Impostazioni */
    if ( leggiDimImpostazioni(imp) < 0 )
    {
        scriviNumCartelleImpostazioni(imp,6);
        scriviTotGiocImpostazioni( imp,6);
        scriviDimImpostazioni( imp, 90);
        scriviAudioVImpostazioni( imp, T);
        scriviAudioNumImpostazioni( imp, F);
    }
    Stampaimpostazioni(imp, posizione );

    while ((comando=(int)getch()) != 27)
    {
          if ( (int)comando == 72 || (int)comando == 8 )
          {
               if ( posizione - 1 < 1 )
               {
                    posizione = 5;
                    Stampaimpostazioni(imp, posizione);
               }
               else
               {
                    posizione--;
                    Stampaimpostazioni(imp,posizione);
               }
          }
          if ( (int)comando == 80 || (int)comando == 2 )
          {
               if ( posizione + 1 > 5 )
               {
                    posizione = 1;
                    Stampaimpostazioni(imp, posizione);
               }
               else
               {
                    posizione++;
                    Stampaimpostazioni(imp,posizione);
               }
          }
          if ( (int)comando == 75 || (int)comando == 77 )
          {
               switch( posizione )
               {
                       case 1:
                              if( (int)comando == 77 )
                              {
                                  if( leggiTotGiocImpostazioni(imp) + 1 > MAXG )
                                  {
                                      scriviTotGiocImpostazioni(imp, 2);
                                      Stampaimpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      scriviTotGiocImpostazioni(imp, leggiTotGiocImpostazioni(imp) + 1 );
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              if( (int)comando == 75 )
                              {
                                  if( leggiTotGiocImpostazioni(imp) - 1 < 2 )
                                  {
                                      scriviTotGiocImpostazioni(imp, MAXG );
                                      Stampaimpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      scriviTotGiocImpostazioni(imp, leggiTotGiocImpostazioni(imp) - 1 );
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 2:
                              if( (int)comando == 77 )
                              {
                                  if( leggiNumCartelleImpostazioni(imp) + 1 > MAXC )
                                  {
                                      scriviNumCartelleImpostazioni(imp,1);
                                      Stampaimpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      scriviNumCartelleImpostazioni(imp, leggiNumCartelleImpostazioni(imp) + 1);
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              if( (int)comando == 75 )
                              {
                                  if( leggiNumCartelleImpostazioni(imp) - 1 < 1 )
                                  {
                                      scriviNumCartelleImpostazioni(imp,MAXC);
                                      Stampaimpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      scriviNumCartelleImpostazioni(imp, leggiNumCartelleImpostazioni(imp) - 1);
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 3:
                              if( (int)comando == 77 )
                              {
                                  scriviDimImpostazioni( imp, leggiDimImpostazioni(imp) + 90);
                                  Stampaimpostazioni(imp,posizione);
                              }
                              if( (int)comando == 75 )
                              {
                                  if( leggiDimImpostazioni(imp) - 90 >= 90)
                                  {
                                      scriviDimImpostazioni(imp, leggiDimImpostazioni(imp) - 90);
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 4:
                              if( (int)comando == 75 || (int)comando == 77)
                              {
                                  if( leggiAudiovImpostazioni(imp) == T)
                                  {
                                     scriviAudioVImpostazioni(imp,F);
                                     Stampaimpostazioni(imp,posizione);
                                  }
                                  else
                                  {
                                      scriviAudioVImpostazioni(imp, T);
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 5:
                              if( (int)comando == 75 || (int)comando == 77)
                              {
                                  if(leggiAudioNumImpostazioni(imp) == T)
                                  {
                                     scriviAudioNumImpostazioni(imp, F);
                                     Stampaimpostazioni(imp,posizione);
                                  }
                                  else
                                  {
                                      scriviAudioNumImpostazioni(imp, T);
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              break;
               }
          }
    }


}

void Stampaimpostazioni ( Impostazioni *imp, int posizione)
{
    int pos = 8;
    int color = 62;

    gotoxy( 1, 6);
    printf("----------------------GAMEPLAY--------------------");
    gotoxy( 5, pos );
    printf("Numero Giocatori [Min 2]");
    gotoxy( 42, pos++ );
    printf(" %c %3d %3c  ", 17, imp->num_tot_player, 16);
    gotoxy( 5, pos );
    printf("Cartelle per Giocatore [Min 1/Max 6]");
    gotoxy( 42, pos++ );
    printf(" %c %3d %3c  ", 17, imp->max_cartelle, 16);
    gotoxy( 5, pos );
    printf("Dimensione Tombolone [Min 90]");
    gotoxy( 42, pos++ );
    printf(" %c %3d %3c  ", 17, imp->dim_tombolone, 16);
    gotoxy( 1, 12);
    printf("------------------------SOUND---------------------");
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
    gotoxy( 1, 25);
    printf("ESC - Esci");
    switch( posizione )
    {
      case 1 :
              gotoxy( 5, posizione + 7);
              textcolor(color);
              printf("Numero Giocatori [Min 2]");
              gotoxy(42, posizione + 7);
              printf(" %c %3d %3c  ", 17, imp->num_tot_player, 16);
              textcolor(color+1);
              break;
      case 2 :
              gotoxy( 5, posizione + 7);
              textcolor(color);
              printf("Cartelle per Giocatore [Min 1/Max 6]");
              gotoxy(42, posizione + 7);
              printf(" %c %3d %3c  ", 17, imp->max_cartelle, 16);
              textcolor(color+1);
              break;
      case 3 :
              gotoxy( 5, posizione + 7);
              textcolor(color);
              printf("Dimensione Tombolone [Min 90]");
              gotoxy(42,posizione +7 );
              printf(" %c %3d %3c  ", 17, imp->dim_tombolone, 16);
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

void addGiocatore(Giocatore *g,Giocatore *gcomodo)
{
     if(!isSetGiocatore(g->next_g))
     {
       g->next_g = allocGiocatore();
       g = getNextG(g);
       *g = *gcomodo;
     }
      else addGiocatore(getNextG(g),gcomodo);

}
void salvaPartita( ListaGiocatori *list, Tombolone *t, ListaPremi p, Estrazione *estr, Impostazioni *imp )
{
    DIR *dir_fp;
    struct dirent *ent;
    FILE *fp;
    char buffer[100];
    char filename[MAX_PATH];
    char dir_name[MAX_PATH];
    char *dir_principale;

    /* Prelevo la homepath del sistema corrente */



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
        printf("DIRECTORY NON TROVATA, LA STO CREANDO");
       if ( _mkdir(dir_name) )
       {
            printf("\nDIR CREATA!\n");
            if ( ( dir_fp = opendir(dir_name) ) == NULL ) printf("\n\n\nNON CREATA!");

       }


    }
  else
    {
        printFile("salva.txt");
        while ( getchar() != '\n' );
        printf("Inserisci nome file da salvare ( MAX 6 caratteri ) : ");
        fgets( buffer, 10, stdin);
        chomp(buffer);

        /*filename = malloc( ( 1 + strlen(dir_name) + strlen(buffer) + strlen(".sav") ) );
        if ( !filename )
        {
            perror("MALLOC ERROR ::> ");
            getch();
            exit(-1);
        }

        strcpy(filename, dir_name);
        strcat(filename, "\\");
        strcat(filename, buffer);
        strcat(filename, ".sav");

        */

        if ( !snprintf( filename, MAX_PATH, "%s\\%s.sav", dir_name, buffer) )
        {
            perror("ERRORE CREAZIONE NOME FILE ::> ");
            getch();
            exit(-1);
        }

        if ( ( fp = fopen(filename,"wb")) == NULL )
        {
            perror("ERROR FILE ::> ");
            getchar();
            exit(-1);
        }
        else
        {
            Giocatore *curr_gioc;
            Cartella *curr_cart;
            int i, row_tomb, col_tomb;

            printf("Salvataggio %s in corso....", filename);
            /* Salvataggio struttura ListaGiocatore */

            fwrite( list, sizeof(ListaGiocatori), 1, fp );
            for ( curr_gioc = leggiPrimoGioc(list); isSetGiocatore(curr_gioc); curr_gioc = getNextG(curr_gioc) )
            {
                fwrite(curr_gioc, sizeof(Giocatore), 1, fp);

                for ( curr_cart = getCartella(curr_gioc); isSetCartella(curr_cart); curr_cart = getNextC(curr_cart) )
                    fwrite( curr_cart, sizeof(Cartella), 1, fp);
            }


            /* Salvataggio struttura Impostazioni */
            fwrite(imp, sizeof(Impostazioni), 1, fp);

            /* Salvataggio ListaPremi */
            /*for ( i = 0; i < TOT_PRIZE; fwrite( &p[i], sizeof(Premio), 1, fp ),i++ );*/
            fwrite( p, sizeof(Premio), TOT_PRIZE, fp);

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

void caricaPartita( void )
{
    ListaGiocatori list;
    Tombolone t;
    ListaPremi p;
    Estrazione estr;
    Impostazioni imp;
    DIR *dir_fp;
    struct dirent *ent = malloc( sizeof(struct dirent));;
    FILE *fp;
    char **file_names;
    int num_files;
    int i = 0;
    char dir_name[MAX_PATH];
    char *dir_principale;

    int choice;

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
       perror("ERROR ::  ");
       getchar();
       exit(-1);

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
        printFile("carica.txt");
        printf("SALVATAGGI ATTUALMENTE CARICATI \n");

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


                printf("%d) %s\n", num_files, *(file_names+i));

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

        /* SE I = 0 , NESSUN FILE SARA' STATO TROVATO! */
        if ( i == 0)
        {
            printf(" NESSUN FILE DI SALVATAGGIO TROVATO!!\nSTO USCENDO!\n");

        }
        else
        {


            do
            {
                printf("Scelta salvataggio : ");
                scanf("%d", &choice);
                if ( choice < 0 || choice > num_files )
                    printf("ERRORE SCELTA!ATTENZIONE NUMERO SALVATAGGIO NON VALIDO!\n");
            }
            while( choice <= 0 || choice > num_files );

            printf("Salvataggio selezionato %s\n", *(file_names+(choice-1)));
            /*
                Compongo il pathname del salvataggio selezionato
            */

            if ( !snprintf(dir_name, MAX_PATH, "%s\\%s", dir_name, *(file_names+(choice-1)) ) )
            {
                perror("ERRORE CREAZIONE NOME FILE ::> ");
                getch();
                exit(-1);
            }

            if ( ( fp = fopen(dir_name,"rb") ) == NULL )
            {
                perror("FILE ERROR ::>  ");
                getch();
                exit(-1);
            }
            else
            {

                Giocatore *curr_gioc = NULL;
                Cartella *curr_cart = NULL;
                int i, j, row_tomb, col_tomb;

                printf("Caricamento %s in corso....", dir_name);
                /* Lettura struttura ListaGiocatore */
                fread(&list, sizeof(ListaGiocatori), 1, fp );

                list.list_g = initListaG();


                for ( curr_gioc = allocGiocatore(), i = 0; i < getTotG(&list); i++, curr_gioc = allocGiocatore() )
                {
                    fread( curr_gioc, sizeof(Giocatore), 1, fp);
                    curr_gioc->next_g = initListaG();
                    curr_gioc->cart_g = initCartella();

                    for ( curr_cart = allocCartella(), j = 0; j < getNumCartelleGioc(curr_gioc); curr_cart = allocCartella(), j++ )
                    {
                        fread(curr_cart, sizeof(Cartella), 1, fp);
                        curr_cart->next_cart = initCartella();

                        if ( j == 0 )
                            curr_gioc->cart_g = curr_cart;
                        else
                            addCartella(curr_gioc->cart_g, curr_cart);
                    }

                    if ( i == 0 )
                        list.list_g = curr_gioc;
                    else
                        addGiocatore(list.list_g, curr_gioc);
                }

                /* Caricamento struttura Impostazioni */
                fread( &imp, sizeof(Impostazioni), 1, fp);

                /* Caricamento ListaPremi */
                fread( p, sizeof(Premio), TOT_PRIZE, fp );
                /*
                for ( i = 0; i < TOT_PRIZE; fread( &p[i], sizeof(Premio), 1, fp ),i++ );*/

                /* Caricamento struttura Estrazione */
                fread( &estr, sizeof(Estrazione), 1, fp );

                estr.numbers = malloc( leggiTotNumeri(&estr) * sizeof(int));
                fread( estr.numbers, sizeof(int), leggiTotNumeri(&estr), fp);


                /* Caricamento struttura Tombolone */
                fread( &t, sizeof(Tombolone), 1, fp);

                t.cart_tomb = (Cart_Tomb**)malloc( leggiRigheTombolone(&t) * sizeof(Cart_Tomb*));
                if ( !t.cart_tomb )
                {
                    perror("MALLOC ERROR ::> ");
                    getch();
                    exit(-1);

                }

                for ( i = 0; i < leggiRigheTombolone(&t); i++ )
                {
                    *(t.cart_tomb+i) = (Cart_Tomb*)malloc( leggiColTombolone(&t) * sizeof(Cart_Tomb));
                    if ( !( *(t.cart_tomb+i ) ) )
                    {
                        perror("MALLOC ERROR ::> ");
                        getch();
                        exit(-1);

                    }
                }

                for ( row_tomb = 0; row_tomb < leggiRigheTombolone(&t); row_tomb++ )
                    for ( col_tomb = 0; col_tomb < leggiColTombolone(&t); col_tomb++ )
                        fread( &t.cart_tomb[row_tomb][col_tomb], sizeof(Cart_Tomb), 1, fp );

                printf("CARICAMENTO COMPLETATO!!\n");

                clrscr();

                GiocaPartita(&list, &imp, &estr, &t);
            }
    }

    /*
        Dealloca memoria per l'array di stringhe adoperato
        per salvare i nomi dei file.
    */
   if ( num_files > 1 )
    {
        for ( i = 0; i < num_files; i++ )
        free(file_names[i]);
    }
    free(file_names);

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
    printFile("uscita.txt");


}

void istruzioni()
{
    printFile("istruzioni.txt");


}



Cartella *getCartella(Giocatore *g)
{
    return g->cart_g;
}

int getIdGiocatore(Giocatore *g)
{
    return g->id;
}

int getCashGiocatore( Giocatore *g )
{
    return g->cash;
}

int getNumCartelleGioc( Giocatore *g )
{
    return g->num_cartelle;
}
int setNumCartelleGioc(Giocatore *g, int numc)
{
    int segnale = 0;

    if(numc < 1 || numc > 6)
     set_error(ENUMCART);
     else
      g->num_cartelle = numc;

    if ( get_curr_error() == ENOTF )
     segnale = 1;

    return segnale;
}

int setCashGiocatore( Giocatore *g, int cash )
{
    if ( !isSetGiocatore(g) )
        set_error(ELPL);
    else
        if ( cash < 0 )
            set_error(ECASH);
    else
        g->cash = cash;

    return get_curr_error();
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

void createCartelle( Giocatore *p, Estrazione *estr )
{
    int i = 0;
    //Puntatore alla testa della lista di cartelle
    Cartella *curr_cart = NULL;

    //Inizializzio il puntatore di testa delle cartelle
    p->cart_g = genCartella(estr);
    curr_cart = p->cart_g;

    while( i < getNumCartelleGioc(p)-1 )
    {

        addCartella( p->cart_g, genCartella(estr) );
        curr_cart = curr_cart->next_cart;
        i++;
    }

}

Giocatore *getNextG(Giocatore *g)
{
    return g->next_g;
}

Giocatore *delGiocatore (Giocatore *g, int id)
{
     Giocatore *gcomodo;

     if(isSetGiocatore(g))
     {
        if( getIdGiocatore(g) == id)
        {
           gcomodo = g;
           g = getNextG(g);
           free(gcomodo);

           return g;
        }
         else g->next_g = delGiocatore(getNextG(g), id);
     }
      else return g;

    return g;
}


Giocatore *getNodoG(Giocatore *g, int pos)
{
    if(isSetGiocatore(g) && pos == 1)
        return g;
    else
        getNodoG(getNextG(g), pos - 1);
}

int setTotG(ListaGiocatori *g,int numg)
{
    int segnale = 0;

    if ( !isSetGiocatore(g->list_g) || numg < 1 )
     set_error(ENUMP);
     else g->num_player = numg;

    if ( get_curr_error() == ENOTF ) segnale = 1;

    return segnale;
}

int getTotG(ListaGiocatori *g)
{
    return g->num_player;
}

int isSetGiocatore(Giocatore *g)
{
    int controllo = 0;

    if(!g)
        set_error(ELPL);
    else
        controllo = 1;

    return controllo;
}

int leggiTotGiocImpostazioni( Impostazioni *imp )
{
    return imp->num_tot_player;
}

int leggiDimImpostazioni( Impostazioni *imp )
{
    return imp->dim_tombolone;

}

int leggiNumCartelleImpostazioni( Impostazioni *imp )
{
    return imp->max_cartelle;

}

int leggiAudiovImpostazioni( Impostazioni *imp )
{
    return imp->audiov;
}

int leggiAudioNumImpostazioni( Impostazioni *imp )
{
    return imp->audionum;
}


int scriviTotGiocImpostazioni( Impostazioni *imp, int numgioc )
{
    int state;

    if ( numgioc < 0 )
    {
        set_error(EIP);
        state = EIP;
    }
    else
        imp->num_tot_player = numgioc;


    return state;

}


int scriviDimImpostazioni( Impostazioni *imp, int dim )
{
    int state = ENOTF;
    int mod = 0;

    if ( dim < 0 )
    {
        set_error(EIMPD );
        state = EIMPD;
    }
    else
        if ( ( mod = dim % 90 ) != 0 )
            dim = 90 * ( mod + 1);

    imp->dim_tombolone = dim;

    return state;
}

int scriviNumCartelleImpostazioni ( Impostazioni *imp, int numcart )
{
    int state = ENOTF;

    if ( numcart < 1 || numcart > 6 )
    {
        set_error(ENUMCART);
        state = ENUMCART;
    }
    else
        imp->max_cartelle = numcart;

    return state;
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

void initTombolone( Tombolone *tomb, int dim )
{
    int row_tomb;
    int i, j;
    int k = 0;
    int k1 = 0;

    /*
        Dovendo avere necessariamente delle cartelle del tombolone che hanno un numero di elementi
        multiplo di 90( 90 compreso ) ed essendo il numero di elementi di una singola cartella pari a 30,
        le dimensioni del tombolone saranno pari alla dimensione diviso 30 che rappresenterà il numero di righe
        e le colonne saranno fisse a 2
    */

    scriviColTombolone(tomb, 2);
    scriviRigheTombolone(tomb, dim / 30);
    tomb->cart_tomb = (Cart_Tomb**)malloc( leggiRigheTombolone(tomb) * sizeof(Cart_Tomb* ) );
    if ( !tomb->cart_tomb )
    {
        perror("MALLOC ERRROR ::> ");
        getch();
        exit(-1);

    }
    for ( i = 0; i < leggiRigheTombolone(tomb); i++ )
    {
        *(tomb->cart_tomb+i) = malloc( leggiColTombolone(tomb) * sizeof(Cart_Tomb));
        if ( !(*(tomb->cart_tomb + i ) ) )
        {
            perror("MALLOC ERROR ::> ");
            getch();
            exit(-1);
        }
    }
    for ( row_tomb = 0; row_tomb < leggiRigheTombolone(tomb); row_tomb++ )
    {

          for ( i = 0; i < CTOMBR; i++ )
            {
                for ( j = 0; j < CTOMBC; j++ )
                {
                    scriviNumTombolone(tomb->cart_tomb[row_tomb][0],i,j,  j + 1 + ( k * 10) );
                    scriviNumFlagTombolone(tomb->cart_tomb[row_tomb][0], i,j, EXIST);

                }
                k++;
            }

    }
    k = 0;
    for ( row_tomb = 0; row_tomb < leggiRigheTombolone(tomb); row_tomb++ )
    {

            for ( i = 0; i < 3; i++ )
            {
                for ( j = 0, k1 = 5; j < 5; j++, k1++ )
                {
                    scriviNumTombolone(tomb->cart_tomb[row_tomb][1], i,j, k1 + 1 + ( k * 10) );
                    scriviNumFlagTombolone(tomb->cart_tomb[row_tomb][1],i,j,EXIST);

                }
                k++;
            }




    }




}


int scriviNumTombolone( Cart_Tomb cart_tomb, int i, int j, int num )
{
    int state = ENOTF;

    if ( ( i < 0 || i > CTOMBR) && ( j < 0 || j > CTOMBC) )
    {
        set_error(ENUMT);
        state = ENUMT;
    }
    else
        cart_tomb[i][j].num = num;

    if ( get_curr_error() != ENOTF )
        state = get_curr_error();

    return state;
}

int leggiNumTombolone( Cart_Tomb cart_tomb,  int i, int j )
{
    int num;

    if ( ( i < 0 || i > CTOMBR) && ( j < 0 || j > CTOMBC) )
    {
        set_error(ENUMT);
        num = -1;
    }
    else
        num = cart_tomb[i][j].num;

    return num;

}

int scriviNumFlagTombolone( Cart_Tomb cart_tomb,  int i, int j, flag f )
{
    int state = ENOTF;

    if ( ( i < 0 || i > CTOMBR) && ( j < 0 || j > CTOMBC) )
    {
        set_error(ENUMT);
        state = ENUMT;
    }
    else
        cart_tomb[i][j].checked = f;

    return state;
}

int leggiNumFlagTombolone( Cart_Tomb cart_tomb, int i, int j )
{
    if ( ( i < 0 || i > CTOMBR) && ( j < 0 || j > CTOMBC) )
        set_error(ENUMT);
    else
        return cart_tomb[i][j].checked;
}

int scriviRigheTombolone(Tombolone *tomb, int righe )
{
    int state = ENOTF;

    if ( righe < 0 || righe > 20 )
    {
        set_error(ERTOMB);
        state = ERTOMB;
    }
    else
        tomb->row = righe;

    return state;

}

int leggiRigheTombolone( Tombolone *tomb )
{
    return tomb->row;
}

int scriviColTombolone( Tombolone *tomb, int col )
{
    int state = ENOTF;

    if ( col < 0 || col > 20 )
    {
        set_error(ECTOMB);
        state = get_curr_error();
    }
    else
        tomb->col = col;

    return state;
}

int leggiColTombolone( Tombolone *tomb )
{
    return tomb->col;
}


char *leggiNomeTopTen( Topten *t )
{
    return t->nome;
}

int leggiPuntTopTen( Topten *t )
{
    return t->punteggio;
}

void scriviNomeTopTen ( Topten *t, char *nome )
{
    t->nome = malloc( ( strlen(nome)+ 1 ) * sizeof(char));
    if ( !t->nome )
    {
        fprintf(stderr, "MALLOC ERROR!EXIT\n");
        exit(-1);
    }
    else
        strcpy( t->nome, nome);
}

void scriviPunteggioTopTen( Topten *t, int punt )
{
    t->punteggio = punt;
}

char *leggiNomePremio ( Premio *p )
{
    return p->nome_premio;
}

int leggiVincitaPremio( Premio *p )
{
    return p->tot_cash;

}

void scriviNomePremio( Premio *p, char *nome )
{

    p->nome_premio = malloc(  (strlen(nome) + 1 ) * sizeof(char ));
    if ( !p->nome_premio )
    {
        fprintf(stderr, "MALLOC ERROR!!EXIT!\n");
        exit(-1);
    }
    else
        strcpy( p->nome_premio, nome);
}
void scriviVincitorePremio( Premio *p, int id )
{
    p->winner_id = id;
}

int leggiVincitorePremio( Premio *p )
{
    return p->winner_id;
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



void printCelle( Card cart, int x, int y )
{
    int i, j;

    int color = 62;

    textcolor(color);
    gotoxy(x,y);

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
                    //scriviCheckedCard(cart,i,j,FALSE);
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




  textcolor(color+1);

}

void printCartelle( Giocatore *p )
{
    Cartella *curr_cart = getCartella(p);
    clrscr();
    int x = 1, y = 1;
    int cont = 1;

    while( isSetCartella( curr_cart ) )
    {
        gotoxy(x,y);
        printCelle( curr_cart->cart ,x,y);
        y += 10;
        if((cont++) == 3)
        {
            x = 60;
            y = 1;
            cont = 0;
        }

        getch();
        curr_cart = getNextC(curr_cart);
    }
    x = 1;
    gotoxy(x,++y);
}

void printPrize( int curr_prize, Giocatore *win_player, int cont_c )
{
    int x = 1, y = 14;
    gotoxy(x,y++);
    /* If it not specified the player, the croupier has won */
    if ( !win_player )
        printf("\nIl Croupier ha fatto %s e ha vinto %d\n",
                leggiNomePremio(&premi[curr_prize]),
                leggiVincitaPremio(&premi[curr_prize]) );
    /* In  the other case, A specific player has won so I print all the information */
    else
    {
        scriviVincitorePremio( &premi[curr_prize], getIdGiocatore( win_player) );
        scriviIdSchedaPremio(&premi[curr_prize], cont_c);
        printf("\nGiocatore %d - ha fatto %s e ha vinto %d con la cartella %d\n",
                leggiVincitorePremio( &premi[curr_prize]),
                leggiNomePremio(&premi[curr_prize]),
                leggiVincitaPremio(&premi[curr_prize]), leggiIdSchedaPremio(&premi[curr_prize]) );
        setCashGiocatore(win_player, getCashGiocatore(win_player) + leggiVincitaPremio(&premi[curr_prize]));

    }

    scriviUscitoPremio( &premi[curr_prize], T);


}



void checkPrize( ListaGiocatori *list, Tombolone *tomb )
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
    Giocatore *curr_gioc;
    Cartella *curr_cart;


    for( i = 0; i < TOT_PRIZE && premi[i].checked == TRUE; i++ )
        ;
    /* ASSERTION : the actual i value represent the position in which there is the prize that will be analyzed */
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

        /* Check Tombolone */
        for( i = 0; i < leggiRigheTombolone(tomb); i++ )
            for ( j = 0; j < leggiColTombolone(tomb); j++ )
                if ( controllaCartTomb( tomb->cart_tomb[i][j], in_a_row) == in_a_row )
                    printPrize( curr_prize,NULL, 0 );




        for( curr_gioc = leggiPrimoGioc(list); isSetGiocatore(curr_gioc);  curr_gioc = getNextG(curr_gioc) )
            for ( curr_cart = getCartella(curr_gioc); isSetCartella(curr_cart); curr_cart = getNextC(curr_cart) )
                if ( controllaCartella( curr_cart, in_a_row) == in_a_row )
                {
                    printPrize( curr_prize, curr_gioc, getIdCartella(curr_cart) );
                    printCelle( curr_cart->cart, 20, 20);
                    getch();
                }



    }
    else
    {

        /* Check BINGO prize for the Tombolone */
        for ( i = 0; i < leggiRigheTombolone(tomb); i++ )
            for ( j = 0; j < leggiColTombolone(tomb); j++ )
                if ( controllaCartTomb( tomb->cart_tomb[i][j], in_a_row) == in_a_row )
                    printPrize( curr_prize, NULL, 0 );



        for( curr_gioc = leggiPrimoGioc(list); isSetGiocatore(curr_gioc);  curr_gioc = getNextG(curr_gioc) )
            for ( curr_cart = getCartella(curr_gioc); isSetCartella(curr_cart); curr_cart = getNextC(curr_cart) )
                if ( controllaCartella( curr_cart, in_a_row) == in_a_row )
                {
                    printPrize( curr_prize, curr_gioc, getIdCartella(curr_cart) );
                    printCelle( curr_cart->cart, 20, 20);
                    getch();
                }


    }

}

int estraiNumero( Estrazione *estr )
{
    int rand_number;

    if ( !getVettoreNumeri(estr) )
    {
        estr->numbers = (int*)malloc( leggiTotNumeri(estr) * sizeof(int));
        if ( !getVettoreNumeri(estr))
        {
            perror("MALLOC ERROR ::>> ");
            exit(-1);
        }
    }

    /*if(leggiTotNumEstratti(estr) < leggiNumGen(estr) )
    {
    */
    if ( leggiTotNumEstratti(estr) == 0 )
    {
        scriviTotNumEstratti( estr, 0);
        fill_numbers(getVettoreNumeri(estr), 1, leggiTotNumeri(estr));
        shuffle( getVettoreNumeri(estr), leggiTotNumeri(estr) );
        rand_number = estr->numbers[estr->tot_numeri_estr++];

    }
    else
        rand_number = estr->numbers[estr->tot_numeri_estr++];



    return rand_number;
   /* }
    else
    {
        /*printf("Numeri estr %d, Numeri totali %d",leggiTotNumEstratti(estr), leggiNumGen(estr));
        getch();
        return -1;
    } */
}

int leggiTotNumEstratti( Estrazione *estr )
{
    return estr->tot_numeri_estr;
}

int scriviTotNumEstratti( Estrazione *estr, int tot )
{
    int stato = 1;

    if ( tot < 0 )
    {
        set_error(ENUMESTR);
        stato = 0;
    }
    else
        estr->tot_numeri_estr = tot;

    return stato;
}

int leggiTotNumeri( Estrazione *estr )
{
    return estr->tot_numeri;
}

int scriviTotNumeri( Estrazione *estr, int dim  )
{
    int stato = 1;

    if ( dim < 0 )
    {
        set_error(EDIMT);
        stato = 0;
    }
    else
        estr->tot_numeri = dim;

    return stato;
}

int *getVettoreNumeri( Estrazione *estr )
{
    return estr->numbers;
}

void setVettoreNumeri( Estrazione *estr, int dim )
{
    int stato = 1;
    if ( dim < 0 )
    {
        set_error(EDIMVET);
        stato = 0;
    }
    else
    {
        estr->numbers = (int*)malloc( leggiTotNumeri(estr) * sizeof(int));
        if ( !estr->numbers )
        {
            perror("MALLOC ERROR ::>> ");
            exit(-1);
        }
    }


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
    int stato = 1;

    if ( num_gen < 0 )
    {
       stato = 0;
       set_error(ENUMGEN);
    }
    else
        estr->num_gen = num_gen;

    return stato;
}

void printTombolone( Tombolone *tomb )
{
   int row_tomb;
    int i, j;
    int posX = 1, posY = 1;
    int num_pagine_tot = leggiRigheTombolone(tomb) / 3;
    int num_pagine_curr = 0;
    int cont = 0;
    int key;

   while( num_pagine_curr++ < num_pagine_tot )
    {
        clrscr();
        system("COLOR 3F");

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
                printf("|%4d | ", leggiNumTombolone(tomb->cart_tomb[row_tomb][1],i,j) ) ;
                textcolor(63);

            }
            gotoxy(posX,++posY);


        }
        gotoxy(posX, ++posY);


    }
    printf("\n");
    cont += 3;
    if ( leggiRigheTombolone(tomb) > 3 )
    {

        printf("Premi un tasto per visualizzare l'altra parte del tombolone o per uscire\n");
        while ( ( key = getch() ) != 13 && key != 27 )
            /* non fa nulla */;

        switch( key )
        {
            case 13 : break;
            case 27 : num_pagine_curr = num_pagine_tot; break;

        }
    }
    posX = 1;
    posY = 1;


    }
}

void printFile( char *file )
{
     FILE *fp;
     int tot_char = 0;
     char c;
     char filename[MAX_PATH];
     int key;

    /*
     filename = malloc( ( strlen("data\\") + strlen(file) ) + 1);

    strcpy(filename, "data\\");
    strcat(filename, file);
    */

    if ( !snprintf(filename, MAX_PATH, "data\\%s", file) )
    {
        perror("ERRORE CREAZIONE DEL PATHNAME ::> ");
        getch();
        exit(-1);
    }
    clrscr();
     system("COLOR 3F");



     if ( ( fp = fopen(filename, "r") ) == NULL )
     {
        perror("ERROR FILE ::> ");
        getch();

        exit(-1);


     }
     else
     {


        while( ( c = fgetc(fp) ) != EOF )
        {
            if( tot_char > 1135 )
            {

                printf("\nPREMI SPAZIO PER ANDARE ALLA PAGINA SUCCESSIVA O ESC PER USCIRE ");
                while( ( ( key = getch() ) != 13 ) && ( key != 27 ) )
                    /* non fa nulla*/;

                if ( key == 13 )
                {
                    clrscr();
                    system("COLOR 3F");
                    tot_char=0;

                }
                else if ( key == 27 )
                    break;



                }

                printf("%c", c);
                tot_char++;
        }


     }


    fclose(fp);

}

Topten *initTopten( void )
{
    return NULL;
}
Topten* getNextTop( Topten *top )
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

void addTopten( Topten *top, Topten *new_gioc )
{

    if ( !isSetTopten(getNextTop(top) ) )
    {

        top->next_top = allocTopten();
        top = getNextTop(top);
        *top = *new_gioc;
    }
    else
        addTopten( getNextTop(top), new_gioc);

}

void insOrdTopten( Topten *top, Topten *new_gioc )
{
    Topten *prec_gioc = top, *curr_gioc;



    if ( /*!isSetTopten( getNextTop(curr_gioc ) ) ||*/ leggiPuntTopTen(top) < leggiPuntTopTen(new_gioc) )
    {
        curr_gioc = allocTopten();
        *curr_gioc = *top;
        new_gioc->next_top = curr_gioc;
        *top = *new_gioc;

    }
    else
    {
        curr_gioc = top;
        prec_gioc = top;
        while ( isSetTopten(curr_gioc ) && leggiPuntTopTen(new_gioc) < leggiPuntTopTen(curr_gioc ) )
        {
            prec_gioc = curr_gioc;
            curr_gioc = getNextTop(curr_gioc);

        }

        prec_gioc->next_top = new_gioc;
        new_gioc->next_top = curr_gioc;

    }
}

Topten *checkTopten( Topten *top, Giocatore *new_gioc )
{
    Topten *curr_gioc, *new_top = allocTopten();
    int flag = 0;
    char buffer[50];


    for ( curr_gioc = top; isSetTopten(curr_gioc) && flag == 0; curr_gioc = getNextTop(curr_gioc) )
        if ( leggiPuntTopTen(curr_gioc) < getCashGiocatore(new_gioc) )
        {
            while( getchar() != '\n');
            printf("Nuovo record.\nInserisci Nickname per entrare nella topten ( MAX 6 caratteri ) : ");
            fgets(buffer,8, stdin);
            chomp(buffer);
            /* crea nuova struttura di tipo topten per effettuare l'inserimento nella lista*/
            scriviNomeTopTen(new_top, buffer);
            scriviPunteggioTopTen(new_top, getCashGiocatore(new_gioc) );
            new_top->next_top = initTopten();
            flag = 1;
        }

    return new_top;

}


void printTopTen( Topten *toplist )
{
    Topten *curr_top;
    int cont_gioc;
    FILE *top_file;

    /*while ( i++ < 90 )
    {
        textcolor(i);
        printf("PROVA %d", i);
        getch();
    }*/

    if ( ( top_file = fopen("topten.txt", "w") ) == NULL )
    {
        perror("ERROR FILE ::> ");
        getch();
        exit(-1);
    }

    printf("POS\t NOME GIOCATORE\t TOT. PUNTEGGIO \n");


    for ( curr_top = toplist, cont_gioc = 1;
        isSetTopten(curr_top) && cont_gioc <= 10;
         curr_top = getNextTop(curr_top), cont_gioc++ )
    {
        switch ( cont_gioc )
        {
            case 1 : textcolor(28); break;
            case 2: textcolor(30); break;
            case 3 : textcolor(26); break;
            default : textcolor(63); break;
        }

        printf("%d)\t\t%6s\t\t  %4d\n", cont_gioc, leggiNomeTopTen(curr_top), leggiPuntTopTen(curr_top));
        fprintf(top_file, "%s %d\n", leggiNomeTopTen(curr_top), leggiPuntTopTen(curr_top));
    }

    fclose(top_file);



}


