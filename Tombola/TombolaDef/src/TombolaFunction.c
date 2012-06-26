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

