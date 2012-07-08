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

#include <direct.h>
#include <dirent.h>
#include <unistd.h>
#include <windows.h>

#define chomp( buffer ) buffer[strlen(buffer)-1] = '\0';

void liberaMemoria( ListaGiocatori *listag, Tombolone *t, Estrazione *estr );
void getTopten( Topten *list );
void play_sound( int );
void printClassifica( ListaGiocatori * );
void bgcolor( int );
int controllaEstensione( char * );
int prelevaDatiDaFile( FILE *fp, ListaGiocatori *list, Tombolone *t, Estrazione *estr, Impostazioni *imp );
int leggiFileDatiGiocatori( FILE *fp, ListaGiocatori *list );
int finePartita( void );
void istruzioni();
void uscita();
int GiocaPartita ( ListaGiocatori *listag, Impostazioni *imp, Estrazione *estr, Tombolone *tomb);
void topten( ListaGiocatori *listag );
void initEstrazione ( Estrazione *, Impostazioni * );
void initGiocatore(Giocatore *, Impostazioni *, int *);
Topten *initTopten( void );
void caricaPartita( void );
void salvaPartita( ListaGiocatori *, Tombolone *, Estrazione *, Impostazioni * );
int leggiFileSalvataggio( char *nuovo_file );
void nuova_partita( Impostazioni * );
void impostazioni_gioco (Impostazioni * );
void Stampaimpostazioni ( Impostazioni *, int);
void printFile( char *filename );
void createCartelle( Giocatore *p, Estrazione *estr );
Cartella *getCartella(Giocatore *);
int getIdGiocatore(Giocatore *);
Giocatore *initListaG();
Giocatore *allocGiocatore();
Giocatore *leggiPrimoGioc( ListaGiocatori *list );
void addGiocatore(Giocatore *, Giocatore *);
Giocatore *getNextG(Giocatore *g);
Giocatore *delGiocatore(Giocatore *, int);
int setNumCartelleGioc(Giocatore *,int);
int getNumCartelleGioc(Giocatore *);
int setCashGiocatore( Giocatore *g, int cash );
int getCashGiocatore( Giocatore *g );
Giocatore *getNodoG(Giocatore *, int);
int setTotG(ListaGiocatori *, int);
int getTotG(ListaGiocatori *);
int isSetGiocatore (Giocatore *);
int leggiTotGiocImpostazioni( Impostazioni * );
int leggiDimImpostazioni( Impostazioni * );
int leggiNumCartelleImpostazioni( Impostazioni * );
Boolean leggiAudiovImpostazioni( Impostazioni * );
Boolean leggiAudioNumImpostazioni( Impostazioni * );
int scriviTotGiocImpostazioni( Impostazioni *, int );
int scriviDimImpostazioni( Impostazioni *, int );
int scriviNumCartelleImpostazioni ( Impostazioni *, int );
void scriviAudioVImpostazioni( Impostazioni *, Boolean);
void scriviAudioNumImpostazioni( Impostazioni *, Boolean );
void initTombolone( Tombolone *tomb, int dim );
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
void scriviNomeTopTen ( Topten *, char * );
void scriviPunteggioTopTen( Topten *, int );
char *leggiNomePremio ( Premio * );
int leggiVincitaPremio( Premio * );
int leggiVincitorePremio( Premio * );
Boolean leggiUscitoPremio( Premio * );
void scriviUscitoPremio( Premio *, Boolean );
void scriviNomePremio( Premio *, char * );
void scriviVincitorePremio( Premio *, int  );
void scriviIdSchedaPremio( Premio *, int );
int leggiIdSchedaPremio( Premio *);
void scriviVincitaPremio( Premio *, int );
void printCartelle( Giocatore *, Estrazione * );
void printTombolone( Tombolone *, int  );
void printTopTen( Topten *toplist );
void printCelle( Card cart , int , int, int );
void printPrize( int, Giocatore *, int );
void checkPrize( ListaGiocatori *, Tombolone *, Estrazione * );
int estraiNumero( Estrazione * );

/* Accesso alla struttura Estrazione */
void initVettoreNumeri( Estrazione * );
int leggiNumGen( Estrazione * );
int scriviNumGen( Estrazione *, int );
int leggiTotNumEstratti( Estrazione * );
int scriviTotNumEstratti( Estrazione *, int );
int leggiTotNumeri( Estrazione * );
int scriviTotNumeri( Estrazione *, int );
int *getVettoreNumeri( Estrazione * );
void setVettoreNumeri( Estrazione *, int dim );

/* Accesso alla struttura Topten */
Topten* getNextTop( Topten *top );
int isSetTopten( Topten *top );
Topten *allocTopten( void );
void addTopten( Topten *top, Topten *new_gioc );
void insOrdTopten( Topten *top, Topten *new_gioc );
Topten *checkTopten( Topten *top, Giocatore *new_gioc );
Topten *initTopten( void );



#endif /* TOMBOLAFUNCTION_H_ */
