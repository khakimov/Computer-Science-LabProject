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
     int num;
     boolean Flag;
     int i;
     int cont = 1;

     Giocatori.num_player = imp->num_tot_player;
     Giocatori.list_g = initListaG();
     Giocatori.list_g = allocGiocatore();
     punt_g = Giocatori.list_g;
     punt_g->id = cont++;
     punt_g->num_cartelle = imp->max_cartelle;

     i = imp->num_tot_player;
     while ( --i )
     {
      punt_g->next_g = allocGiocatore();
      punt_g = getNextG( punt_g );
     }


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

     getcwd(cwd, sizeof(cwd));

     char *filename = malloc( (  strlen(cwd)+ strlen("\\data\\") + strlen(file) ) * sizeof(char));


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
    Cartella *curr_cart = getCartella(p);
    int i = 0;

    curr_cart = initCartella();

    while( i < getNumCartelleGioc(p) )
    {

        addCartella( curr_cart, genCartella(estr) );
        setIdCartella(curr_cart, id_cart++);
        curr_cart = getNextC(curr_cart);
        i++;
    }

}

void addGiocatore(Giocatore *g,Giocatore *gcomodo)
{
     if(!isSetGiocatore(g->next_g))
     {
       g->next_g = allocGiocatore();
       g = getNextG(g);
       memcpy(g,gcomodo, sizeof(Giocatore));
     }
      else addGiocatore(getNextG(g),gcomodo);

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

int leggiVincitorePremio( Premio *p )
{
    return p->winner_id;
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

void scriviVincitaPremio( Premio *p, int tot_premio )
{
    p->tot_cash = tot_premio;
}


/*
    FUNZIONI DI STAMPA DELLE STRUTTURE DATI


*/

void printTombolone( Tombolone *tomb )
{
   int row_tomb, col_tomb;
    int i, j;
    int posX = 0, posY = 0;
    int tempX = 0, tempY = 0;

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



