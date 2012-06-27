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

void addGiocatore(Giocatore *g,Giocatore *gcomodo)
{

     if(!isSetGiocatore(g))
     {
           g = allocGiocatore();
           g->next_g = initListaG();
           g = gcomodo;
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

int setNumCartelle(Giocatore *g, int numc)
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

int getNumCartelle(Giocatore *g)
{
    return g->num_cartelle;
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

