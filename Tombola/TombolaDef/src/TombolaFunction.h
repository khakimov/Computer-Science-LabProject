/*
 * TombolaFunction.h
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ
 */

#ifndef TOMBOLAFUNCTION_H_
#define TOMBOLAFUNCTION_H_

#include "ErrorManager.h"
#include "CardManager.h"


void nuova_partita( Impostazioni *imp );
Cartella *getCartella(Giocatore *);
int getIdGiocatore(Giocatore *);
Giocatore *initListaG();
Giocatore *allocGiocatore();
Giocatore *leggiPrimoGioc( ListaGiocatori *list );
void addGiocatore(Giocatore *, Giocatore *);
Giocatore *getNextG(Giocatore *g);
Giocatore *delGiocatore(Giocatore *, int);
int setNumCartelle(Giocatore *,int);
int getNumCartelle(Giocatore *);
Giocatore *getNodoG(Giocatore *, int);
int setTotG(ListaGiocatori *, int);
int getTotG(ListaGiocatori *);
int isSetGiocatore (Giocatore *);
int leggiTotGiocImpostazioni( Impostazioni * );
int leggiDimImpostazioni( Impostazioni * );
int leggiNumCartelleImpostazioni( Impostazioni * );
int leggiAudiovImpostazioni( Impostazioni * );
int leggiAudioNumImpostazioni( Impostazioni * );
int scriviTotGiocImpostazioni( Impostazioni *, int );
int scriviDimImpostazioni( Impostazioni *, int );
int scriviNumCartelleImpostazioni ( Impostazioni *, int );
void scriviAudioVImpostazioni( Impostazioni *, boolean);
void scriviAudioNumImpostazioni( Impostazioni *, boolean );
int scriviNumTombolone( Cart_Tomb, int, int, int );
int leggiNumTombolone( Cart_Tomb,  int, int );
int scriviNumFlagTombolone( Cart_Tomb,  int, int, flag );
int leggiNumFlagTombolone( Cart_Tomb, int, int);
int scriviRigheTombolone(Tombolone *, int );
int leggiRigheTombolone( Tombolone * );
int scriviColTombolone( Tombolone *, int );
int leggiColTombolone( Tombolone * );
char *leggiNomeTopTen( Topten * );
int leggiPuntTopTen( Topten * );
void scriviNomeTopTen ( Topten *t, char *nome );
void scriviPunteggioTopTen( Topten *t, int punt );
char *leggiNomePremio ( Premio *p );
int leggiVincitaPremio( Premio *p );
int leggiVincitorePremio( Premio *p );
void scriviNomePremio( Premio *p, char *nome );
void scriviVincitorePremio( Premio *p, int id );
void scriviVincitaPremio( Premio *p, int tot_premio );


#endif /* TOMBOLAFUNCTION_H_ */
