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

void nascondiCursore( void );
void mostraCursore( void);
void stampaMenu( void );
void liberaMemoria( ListaGiocatori *, Tombolone *, Estrazione * );
void liberaTopten( Topten * );
void leggiTopten( Topten * );
void ricreaTopten( FILE * );
void riprodSuono( int );
void stampaClassifica( ListaGiocatori * );
void coloraSfondo( int );
int controllaEstensione( char * );
int controllaNomeFile( char * );
int prelevaDatiDaFile( FILE *, ListaGiocatori *, Tombolone *, Estrazione *, Impostazioni *, ListaPremi );
int leggiFileDatiGiocatori( FILE *, ListaGiocatori * );
int finePartita( ListaPremi );
void istruzioni( void );
void uscita( void );
void giocaPartita ( ListaGiocatori *, Impostazioni *, Estrazione *, Tombolone *, ListaPremi );
void topten( ListaGiocatori * );
void initImpostazioni (Impostazioni *);
void initEstrazione ( Estrazione *, Impostazioni * );
void initGiocatore(Giocatore *, Impostazioni *, int *);
Topten *initTopten( void );
void caricaPartita( void );
void salvaPartita( ListaGiocatori *, Tombolone *, Estrazione *, Impostazioni *, ListaPremi );
int leggiFileSalvataggio( char *nuovo_file );
void nuovaPartita( Impostazioni * );
void impostazioniGioco (Impostazioni * );
void stampaImpostazioni ( Impostazioni *, int);
void stampaFile( char *filename );
void creaCartelle( Giocatore *, Estrazione * );
Cartella *leggiCartella(Giocatore *);
int leggiIdGiocatore(Giocatore *);
int scriviIdGiocatore( Giocatore * , int );
Giocatore *initListaG( void );
Giocatore *allocGiocatore( void );
Giocatore *leggiPrimoGioc( ListaGiocatori * );
void aggGiocatore(Giocatore *, Giocatore *);
Giocatore *leggiSuccG(Giocatore *);
int scriviNumCartelleGioc(Giocatore *,int);
int leggiNumCartelleGioc(Giocatore *);
int scriviCashGiocatore( Giocatore *, int );
int leggiCashGiocatore( Giocatore * );
Giocatore *leggiNodoG(Giocatore *, int);
int scriviTotG(ListaGiocatori *, int);
int leggiTotG(ListaGiocatori *);
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
int initTombolone( Tombolone *, int );
int scriviNumTombolone( Cart_Tomb, int, int, int );
int leggiNumTombolone( Cart_Tomb,  int, int );
int scriviNumFlagTombolone( Cart_Tomb,  int, int, flag );
int leggiNumFlagTombolone( Cart_Tomb, int, int);
int scriviRigheTombolone(Tombolone *, int );
int leggiRigheTombolone( Tombolone * );
int scriviColTombolone( Tombolone *, int );
int leggiColTombolone( Tombolone * );
void initPremio( ListaPremi, int, int );
char *leggiNomePremio ( Premio * );
int leggiVincitaPremio( Premio * );
int leggiVincitorePremio( Premio * );
Boolean leggiUscitoPremio( Premio * );
void scriviUscitoPremio( Premio *, Boolean );
int scriviNomePremio( Premio *, char * );
void scriviVincitorePremio( Premio *, int  );
void scriviIdSchedaPremio( Premio *, int );
int leggiIdSchedaPremio( Premio *);
void scriviVincitaPremio( Premio *, int );
void stampaCartelle( Giocatore *, Estrazione * );
void stampaTombolone( Tombolone *, int  );
void stampaTopTen( Topten *);
void stampaTopTenSuFile( Topten * );
void stampaCelle( Card cart , int , int, int );
void stampaPremio( ListaPremi, int, Giocatore *, int );
void controllaPremio( ListaGiocatori *, Tombolone *, Estrazione *, ListaPremi );
int estraiNumero( Estrazione * );

/* Accesso alla struttura Estrazione */
void initVettoreNumeri( Estrazione * );
int leggiNumGen( Estrazione * );
int scriviNumGen( Estrazione *, int );
int leggiTotNumEstratti( Estrazione * );
int scriviTotNumEstratti( Estrazione *, int );
int leggiTotNumeri( Estrazione * );
int scriviTotNumeri( Estrazione *, int );
int *leggiVettoreNumeri( Estrazione * );
int allocVettoreNumeri( Estrazione *, int );

/* Accesso alla struttura Topten */
Topten* leggiSuccTop( Topten * );
int isSetTopten( Topten * );
Topten *allocTopten( void );
void aggTopten( Topten *, Topten * );
void insOrdTopten( Topten *, Topten * );
Topten *controllaTopten( Topten *, Giocatore * );
Topten *initTopten( void );
int leggiPuntTopTen( Topten * );
int scriviNomeTopTen ( Topten *, char * );
char *leggiNomeTopTen( Topten * );
int scriviPunteggioTopTen( Topten *, int );


#endif /* TOMBOLAFUNCTION_H_ */
