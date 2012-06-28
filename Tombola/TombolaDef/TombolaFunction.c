/*
 * TombolaFunction.c
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ & Nazar Chekalin
 */
#include "CardManager.h"
#include "TombolaFunction.h"

void nuova_partita( Impostazioni *imp )
{
     ListaGiocatori Giocatori;
     Giocatore *punt_g = initListaG();
     Giocatore *gcomodo;
     int num;
     boolean Flag;
     int i = 0,j = 0;
     int cont = 1;
     Estrazione estr;
     Cartella *c;

     initEstrazione ( &estr , imp);

     Giocatori.num_player = imp->num_tot_player;
     Giocatori.list_g = initListaG();
     Giocatori.list_g = allocGiocatore();
     gcomodo = allocGiocatore();
     punt_g = Giocatori.list_g;


     initGiocatore(gcomodo,imp,&cont);
     gcomodo->cart_g = genCartella(&estr);

     *punt_g = *gcomodo;
     i = imp->num_tot_player;
     j = imp->max_cartelle;

     while ( --i )
     {
       while ( --j )
       {
         c = genCartella(&estr);
         addCartella(punt_g->cart_g, c);

       }
       gcomodo->id = cont++;
       addGiocatore(punt_g,gcomodo);


     }


}
void initEstrazione ( Estrazione *estr , Impostazioni *imp)
{
     scriviNumGen(estr, 0);
     scriviTotNumEstratti( estr, 0);
     initVettoreNumeri(estr);
     scriviTotNumeri(estr, imp->dim_tombolone);
}
void initGiocatore(Giocatore *gcomodo, Impostazioni *imp, int *cont)
{
     gcomodo->id = *cont++;
     gcomodo->num_cartelle = imp->max_cartelle;
     gcomodo->cash = 0;
     gcomodo->next_g = NULL;
     gcomodo->cart_g = NULL;


}

void impostazioni_gioco (Impostazioni *imp )
{
    char comando;
    char buffer[100];
    int posizione = 1;

    FILE *fp;

    fp = fopen("data/impostazioni.txt", "r");
    while ( fgets(buffer, sizeof(100),fp))
    printf("%s", buffer);

    fclose(fp);

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
                                  if( imp->num_tot_player + 1 > MAXG )
                                  {
                                      imp->num_tot_player = 1;
                                      Stampaimpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      imp->num_tot_player ++;
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              if( (int)comando == 75 )
                              {
                                  if( imp->num_tot_player - 1 < 1 )
                                  {
                                      imp->num_tot_player = MAXG;
                                      Stampaimpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      imp->num_tot_player --;
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 2:
                              if( (int)comando == 77 )
                              {
                                  if( imp->max_cartelle + 1 > MAXC )
                                  {
                                      imp->max_cartelle = 1;
                                      Stampaimpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      imp->max_cartelle ++;
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              if( (int)comando == 75 )
                              {
                                  if( imp->max_cartelle - 1 < 1 )
                                  {
                                      imp->max_cartelle = MAXC;
                                      Stampaimpostazioni(imp, posizione);
                                  }
                                  else
                                  {
                                      imp->max_cartelle --;
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 3:
                              if( (int)comando == 77 )
                              {
                                  imp->dim_tombolone += 90;
                                  Stampaimpostazioni(imp,posizione);
                              }
                              if( (int)comando == 75 )
                              {
                                  if( imp->dim_tombolone - 90 >= 90)
                                  {
                                      imp->dim_tombolone -= 90;
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 4:
                              if( (int)comando == 75 || (int)comando == 77)
                              {
                                  if(imp->audiov == T)
                                  {
                                     imp->audiov =F;
                                     Stampaimpostazioni(imp,posizione);
                                  }
                                  else
                                  {
                                      imp->audiov = T;
                                      Stampaimpostazioni(imp,posizione);
                                  }
                              }
                              break;
                       case 5:
                              if( (int)comando == 75 || (int)comando == 77)
                              {
                                  if(imp->audionum == T)
                                  {
                                     imp->audionum = F;
                                     Stampaimpostazioni(imp,posizione);
                                  }
                                  else
                                  {
                                      imp->audionum = T;
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

    gotoxy( 5, pos++ );
    printf("Numero Giocatori %10c %3d %3c  ", 17, imp->num_tot_player, 16);
    gotoxy( 5, pos++ );
    printf("Numero Cartelle  %10c %3d %3c  ", 17, imp->max_cartelle, 16);
    gotoxy( 5, pos++ );
    printf("Dimensioni Tombolone  %5c %3d %3c  ", 17, imp->dim_tombolone, 16);

    if (imp->audiov == T )
    {
      gotoxy( 5, pos++ );
      printf("Audio Vittoria  %3c %3s %3c  ", 17, "SI", 16);
    }
     else
     {
       gotoxy( 5, pos++ );
       printf("Audio Vittoria  %3c %3s %3c  ", 17, "NO", 16);
     }

    if (imp->audionum == T )
    {
      gotoxy( 5, pos++ );
      printf("Audio Estrazione  %3c %3s %3c  ", 17, "SI", 16);
    }
     else
     {
       gotoxy( 5, pos++ );
       printf("Audio Estrazione  %3c %3s %3c  ", 17, "NO", 16);
     }

    switch( posizione )
    {
      case 1 :
              gotoxy( 5, posizione + 7);
              textcolor(10);
              printf("Numero Giocatori %10c %3d %3c  ", 17, imp->num_tot_player, 16);
              textcolor(15);
              break;
      case 2 :
              gotoxy( 5, posizione + 7);
              textcolor(10);
              printf("Numero Cartelle  %10c %3d %3c  ", 17, imp->max_cartelle, 16);
              textcolor(15);
              break;
      case 3 :
              gotoxy( 5, posizione + 7);
              textcolor(10);
              printf("Dimensioni Tombolone  %5c %3d %3c  ", 17, imp->dim_tombolone, 16);
              textcolor(15);
              break;
      case 4 :
              gotoxy( 5, posizione + 7);
              textcolor(10);
              if (imp->audiov == T )
              {
               gotoxy( 5, posizione + 7);
               printf("Audio Vittoria  %3c %3s %3c  ", 17, "SI", 16);
              }
               else
               {
                gotoxy( 5, posizione + 7 );
                printf("Audio Vittoria  %3c %3s %3c  ", 17, "NO", 16);
               }
               textcolor(15);
              break;
      case 5 :
              gotoxy( 5, posizione + 7);
              textcolor(10);
              if (imp->audionum == T )
              {
               gotoxy( 5, posizione + 7);
               printf("Audio Estrazione  %3c %3s %3c  ", 17, "SI", 16);
              }
               else
               {
                gotoxy( 5, posizione + 7 );
                printf("Audio Estrazione  %3c %3s %3c  ", 17, "NO", 16);
               }
               textcolor(15);
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
void salvaPartita( ListaGiocatori *list, Tombolone *t, ListaPremi *p, Estrazione *estr, Impostazioni *imp )
{
    DIR *dir_fp;
    struct dirent *ent;
    Salvataggio save;
    FILE *fp;
    char buffer[100];
    char *filename;

    char *dir_name;

    char *s2;

    s2 = getenv("USERPROFILE");


    dir_name = (char*)malloc( ( 1+  strlen(s2) + strlen("\\TombolaSaveGame") ) * sizeof(char) );
    strcpy(dir_name, s2);

    strcat(dir_name, "\\TombolaSaveGame");



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
        printf("Inserisci nome file da salvare : ( MAX 6 caratteri ) \n");
        fgets( buffer, 6, stdin);
        save.imp = *imp;
        save.lista = *list;
        memcpy( save.lista_premi, p, TOT_PRIZE * sizeof(Premio));
        save.estr = *estr;

        filename = malloc( ( strlen(dir_name) + strlen(buffer) ) * sizeof(char ));

        strcpy(filename, dir_name);
        strcat(filename, "\\");
        buffer[strlen(buffer)-1] = '\0';
        strcat(filename, buffer);

        if ( ( fp = fopen(filename,"wb")) == NULL )
        {
            perror("ERROR FILE ::> ");
            getchar();
            exit(-1);
        }
        else
        {
            printf("Salvataggio %s in corso....", buffer);
            fwrite(&save, sizeof(Salvataggio), 1, fp);
        }

        closedir(dir_fp);
        fclose(fp);


    }
}

void caricaPartita( ListaGiocatori *list, Tombolone *t, ListaPremi *p, Estrazione *estr, Impostazioni *imp )
{
   DIR *dir_fp;
    struct dirent *ent;
    char **file_names;
    Salvataggio save;
    char buffer[100];

    char *dir_name;

    char *s2;

    s2 = getenv("USERPROFILE");


    dir_name = (char*)malloc( ( 1+  strlen(s2) + strlen("\\TombolaSaveGame") ) * sizeof(char) );
    strcpy(dir_name, s2);

    strcat(dir_name, "\\TombolaSaveGame");


    if ( ( dir_fp = opendir(dir_name) ) == NULL )
    {
       perror("ERROR ::  ");
       getchar();
       exit(-1);

    }
  else
    {
      file_names = (char**)malloc(sizeof(char*));

      while( ( ent = readdir(dir_fp) ) != NULL )
        {

          int len = strlen(ent->d_name);
          int i = 0;
          *(file_names+i) = malloc( len * sizeof(char));

            strcpy( *(file_names+i), ent->d_name);
            gotoxy(20,10);
             printf("FILE NAME %s\n", *(file_names+i));
             i++;
             file_names = realloc( file_names, i * sizeof(char*));


          if ( !file_names )
            {
              fprintf(stderr, "READING DIRECTORY OCCURRED AN ERROR!\n");
              exit(-1);

            }



        }
      closedir(dir_fp);
      free(file_names);

    }
}

void uscita()
{
    printFile("uscita.txt");


}

void istruzioni()
{
    printFile("istruzioni.txt");


}

void impostazioni( Impostazioni *imp )
{
    printFile("impostazioni.txt");
}

void printFile( char *file )
{
     FILE *fp;
     int tot_char = 0;
     char c;
     char cwd[300];
     char *filename;

     getcwd(cwd, sizeof(cwd));

     filename = malloc( (  strlen(cwd)+ strlen("\\data\\") + strlen(file) ) * sizeof(char));


     strcpy(filename, cwd);
     strcat(filename, "\\data\\");
     strcat(filename, file );

     printf("TEST %s", filename);
     getchar();


     clrscr();


     system("COLOR 3F");



     if ( ( fp = fopen(filename, "r")) == NULL )
     {
        perror("ERROR FILE ::> ");
        getchar();

        exit(-1);


     }




    while ( ( c = fgetc(fp) ) != EOF  && tot_char < 1280 )
    {

       printf("%c", c);
       tot_char++;


    }
    /*if ( tot_char == 737 )
        printf("\nPremi INVIO per visualizzare l'altra pagina, ESC per menu' principale\n");
    printf("\n");
    getch(); */
     fclose(fp);

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
    return (Giocatore*)malloc(sizeof(Giocatore));


}

void createCartelle( Giocatore *p, Estrazione *estr )
{
    static int id_cart = 10;
    int i = 1;
    //Puntatore alla testa della lista di cartelle
    Cartella *curr_cart = NULL;

    //Inizializzio il puntatore di testa delle cartelle
    p->cart_g = allocCartella();
    curr_cart = p->cart_g;

    while( i < getNumCartelleGioc(p) )
    {

        addCartella( curr_cart, genCartella(estr) );
        setIdCartella(curr_cart, id_cart++);
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
    return imp->num_tot_player;

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

void scriviAudioVImpostazioni( Impostazioni *imp, boolean flag )
{
    imp->audiov = flag;

}

void scriviAudioNumImpostazioni( Impostazioni *imp, boolean flag )
{
     imp->audiov = flag;

}

/* Funzioni di gestione del Tombolone */

void initTombolone( Tombolone *tomb, int dim )
{
    int row_tomb, col_tomb;
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

    for ( row_tomb = 0; row_tomb < leggiRigheTombolone(tomb); row_tomb++ )
    {

          for ( i = 0; i < CTOMBR; i++ )
            {
                for ( j = 0; j < CTOMBC; j++ )
                {
                    scriviNumTombolone(tomb->cart_tomb[row_tomb][0],i,j,  j + 1 + ( k * 10) );
                    scriviNumFlagTombolone(tomb->cart_tomb[row_tomb][0], i,j, FALSE);

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
                    scriviNumFlagTombolone(tomb->cart_tomb[row_tomb][1],i,j,FALSE);

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
        strncpy( t->nome, nome, 10);
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


boolean leggiUscitoPremio( Premio *p )
{
    return p->checked;
}

void scriviUscitoPremio( Premio *p, boolean f )
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



/*
    FUNZIONI DI STAMPA DELLE STRUTTURE DATI


*/

void printTombolone( Tombolone *tomb )
{
   int row_tomb, col_tomb;
    int i, j;
    int posX = 0, posY = 0;

    for ( row_tomb = 0; row_tomb < leggiRigheTombolone(tomb);  row_tomb++)
    {

       for ( i = 0; i < CTOMBR; i++ )
        {
            for ( j = 0; j < CTOMBC;j++)
            {
                printf("| %2d | ", leggiNumTombolone(tomb->cart_tomb[row_tomb][0], i, j ) );

            }
            gotoxy(posX,++posY);


        }
        gotoxy(posX, ++posY);


    }
    posX = 40;
    posY = 0;
    gotoxy(posX, posY);
    for ( row_tomb = 0; row_tomb < leggiRigheTombolone(tomb);  row_tomb++)
    {

       for ( i = 0; i < CTOMBR; i++ )
        {
            for ( j = 0; j < CTOMBC;j++)
            {
                printf("| %2d | ", leggiNumTombolone(tomb->cart_tomb[row_tomb][1],i,j) ) ;

            }
            gotoxy(posX,++posY);


        }
        gotoxy(posX, ++posY);


    }
    printf("\n");


}

void printCelle( Card cart )
{
    int i, j;

    for(j=0;j<CARTC;j++)
        printf("______");
        printf("\n\n");

        for(i=0;i<CARTR; i++)
        {
            for(j=0;j<CARTC;j++)
            {
                if( leggiCheckedCard(cart,i,j) == TRUE )
                {

                    textcolor(15);
                    printf("  %2d  ", leggiNumeroCard(cart,i,j));
                    scriviCheckedCard(cart,i,j,FALSE);
                }
                else
                {
                    printf("  ");
                    textcolor(204);
                    printf("  ");
                    textcolor(10);
                    printf("  ");
                }
            }
            printf("\n");
            for(j=0;j<CARTC;j++)
            {
                textcolor(15);
                printf("______");
            }
            printf("\n\n");
        }






}

void printCartelle( Giocatore *p )
{
    Cartella *curr_cart = getCartella(p);

    while( isSetCartella( curr_cart ) )
    {
        printCelle( curr_cart->cart );
        curr_cart = getNextC(curr_cart);
    }
}

void printPrize( int curr_prize, Giocatore *win_player, int cont_c )
{
    ListaPremi premi;
    /* If it not specified the player, the croupier has won */
    if ( !win_player )
        printf("Il Croupier ha fatto %s e ha vinto %d\n",
                premi[curr_prize].nome_premio,
                premi[curr_prize].tot_cash );
    /* In  the other case, A specific player has won so I print all the information */
    else
    {
        scriviVincitorePremio( &premi[curr_prize], getIdGiocatore( win_player) );
        printf("Giocatore %d ha fatto %s e ha vinto %d con la cartella %d\n",
                leggiVincitorePremio( &premi[curr_prize]), leggiNomePremio(&premi[curr_prize]),
                leggiVincitaPremio(&premi[curr_prize]), leggiIdSchedaPremio(&premi[curr_prize]) );
    }

    scriviUscitoPremio( &premi[curr_prize], TRUE);
}



void checkPrize( ListaGiocatori *list, ListaPremi premi, Tombolone *tomb )
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
    Giocatore *curr_gioc = leggiPrimoGioc(list);
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




        for( ; isSetGiocatore(curr_gioc);  curr_gioc = getNextG(curr_gioc) )
            for ( curr_cart = getCartella(curr_gioc); isSetCartella(curr_cart); curr_cart = getNextC(curr_cart) )
                if ( controllaCartella( curr_cart, in_a_row) == in_a_row )
                    printPrize( curr_prize, curr_gioc, getIdGiocatore(curr_gioc) );




    }
    else
    {

        /* Check BINGO prize for the Tombolone */
        for ( i = 0; i < leggiRigheTombolone(tomb); i++ )
            for ( j = 0; j < leggiColTombolone(tomb); j++ )
                if ( controllaCartTomb( tomb->cart_tomb[i][j], in_a_row) == in_a_row )
                    printPrize( curr_prize, NULL, 0 );



        for( ; isSetGiocatore(curr_gioc);  curr_gioc = getNextG(curr_gioc) )
            for ( curr_cart = getCartella(curr_gioc); isSetCartella(curr_cart); curr_cart = getNextC(curr_cart) )
                if ( controllaCartella( curr_cart, in_a_row) == in_a_row )
                    printPrize( curr_prize, curr_gioc, getIdGiocatore(curr_gioc) );



    }

}

int estraiNumero( Estrazione *estr )
{
    static int *numbers;
    static int tot_num = 0;
    int rand_number;

    if ( !getVettoreNumeri(estr) )
        setVettoreNumeri(estr, leggiTotNumeri(estr));




    if ( tot_num == 0 || tot_num >= TOT_NUM )
    {
        fill_numbers(numbers, 1, TOT_NUM);
        shuffle( numbers, TOT_NUM );
        rand_number = numbers[tot_num++];

    }
    else
        rand_number = numbers[tot_num++];

    return rand_number;
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

int *setVettoreNumeri( Estrazione *estr, int dim )
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


