/*
 * CardManager.h
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ
 */

#ifndef CARDMANAGER_H_
#define CARDMANAGER_H_


#include "ErrorManager.h"
#ifndef _STDIO_H_
#include <stdio.h>
#endif

#ifndef _STDLIB_H_
#include <stdlib.h>
#endif

#include <time.h>
#include <conio2.h>

#define SAVE_KEY 's'
#define ESC_KEY 27

#define TOT_PRIZE 5
#define CARTC 9
#define CARTR 3

#define CTOMBR 3
#define CTOMBC 5

#define MAXG 6
#define MAXC 6

#define NEW_GAME 10
#define LOAD 14
#define SETTINGS 18
#define TOP 22
#define ISTR 26
#define EXIT 30
/* Tipo di dato enumerativo che indica se uno specifico numero è uscito o meno
 *
 * Nella generazione dei numeri viene adoperato anche il valore EXIST, per poter
 * gestire il caso in cui un valore è stato già precedentemente settato o meno,
 * in modo tale da poter garantire una corretta elaborazione di quella che è la fase
 * di generazione dei numeri casuali che andranno a comporre le cartelle.
 *
 *  */
typedef enum { FALSE, TRUE, EXIST }flag;
typedef enum { F, T }Boolean;


/* Struttura che rappresenta una cella della cartella della tombola
 * avente come campi un numero intero che rappresenta il numero della cella
 * e un flag che indica se il numero è uscito o meno.
 * (
 * */
typedef struct
{
	int num;
	flag checked;

}Cella;


/*
	Card – array bidimensionale di tipo Cella che rappresenta propriamente una cartella

*/
typedef Cella Card[3][9];

/*
 * 	Cartella – record contenente un campo di tipo Card e
 *
 * un campo intero che indica il numero della cartella  alla quale
 *
 * si sta facendo riferimento e un puntatore alla cartella successiva.
*/

typedef struct cartella
{
	Card cart; /* cartella con la quale giocare */
	int id; /* id della cartella */
	struct cartella *next_cart; /* indirizzo cartella successiva */
}Cartella;

/*
 * Giocatore – struttura contenente un puntatore ad una struttura di tipo Cartella che
 *
 *  rappresenta le cartelle  possedute dal giocatore, un intero che rappresenta il numero di
 *
 *  cartelle possedute e una seconda variabile  intera che rappresenta
 *
 *  l’attuale somma di denaro vinta dal giocatore.

*/


typedef struct Giocatore
{
	struct Giocatore *next_g; /* riferimento prossimo giocatore */
	Cartella *cart_g; /* elenco di cartelle possedute dal giocatore */
	int num_cartelle;	/* numero di cartelle facenti parte dell’elenco */
	int cash; /* montepremi vinto dall’utente */
	int id; /* id corrispondente all’utente */
}Giocatore;

/*
*	ListaGiocatori – struttura dati concatenata che contiene un puntatore
*	ad una struttura di tipo Giocatore  che rappresenta il prossimo
*	giocatore nella lista e un campo di tipo intero che rappresenta
*	il numero totale  di giocatori attualmente in gioco.
*/

typedef struct Lista_giocatori
{
	Giocatore *list_g; /* elenco di giocatori */
	int num_player; /* numero giocatori dell’elenco */
}ListaGiocatori;
/*
 *	Tabellone – Tipo di dato che rappresenta
 *	un doppio puntatore a Card che concretamente
 *	rappresenta il  tombolone di gioco
 *	( allocato dinamicamente in base all’opzione dell’utente ).
 *
 *
 *
 */

typedef Cella Cart_Tomb[3][5];

typedef struct
{
	Cart_Tomb **cart_tomb; /* insieme di cartelle che costituiscono il tombolone */
	int row; /* numero di righe di tale tombolone */
	int col; /* numero di colonne del tombolone */
}Tombolone;

/*
 * Impostazioni – Record contenente una
 * serie di campi per poter raggruppare
 * le opzioni scelte dal giocatore,
 * rappresentate tutte da valori interi precisamente:
 *
 */

typedef struct Impostazioni
{
	int num_tot_player; /* numero totale di giocatori impostati */
	int dim_tombolone; /* valore numerico che rappresenta i numeri presenti nel tombolone */
	int max_cartelle; /* numero Massimo di cartelle che un giocatore può scegliere */
	Boolean audiov; /* audio per vittoria di un premio */
	Boolean audionum; /* audio estrazione di un numero */
}Impostazioni;

/* Premi – Struttura che rappresenta un premio
 *
 * che un giocatore ha la possibilità di vincere
 * durante il gioco e  contiene un intero che
 * rappresenta la vincita relativa a quel premio,
 *
 * un campo che indica il nome del  premio, una
 * variabile booleana che indica se tale premio è stato vinto o meno
 * e una variabile intera che  rappresenta il numero del
 * giocatore che ha vinto quel premio.
 *
 *
 *
 */

typedef struct premio
{
	char *nome_premio; /* nome del premio */
	int tot_cash;/* Totale vincita premio */
	int winner_id; /* Id del premio vincitore */
	Boolean checked; /* Flag che notifica se un premio è stato vinto o meno */
    int id_scheda; /* numero della scheda vincente */
}Premio;


/*
 * Lista dei 5 premi che è possibile vincere.
 * AMBO - posizione 0
 * TERNO  - posizione 1
 * QUATERNO -posizione 2
 * QUINTINA  - posizione 3
 * TOMBOLA - posizione 4
 *
 *
 */

typedef Premio ListaPremi[TOT_PRIZE];  /* insieme di premi presenti nel gioco */

/*
 *
 * Struttura necessaria per contenere
 *
 *  i giocatori che hanno vinto maggiormente
 *  durante il corso del gioco.
 *
 *
 *
 *   */
typedef struct topten
{
    char *nome; /* Nome del giocatore in topten */
    int punteggio; /* punteggio totalizzato dal giocatore */
    struct topten *next_top; /* puntatore al prossimo elemento della topten */
}Topten;

typedef struct
{
    int num_gen; /* Numeri attualmente generati*/
    int tot_numeri_estr; /* Totale numeri estratti dall'inzio del gioco */
    int *numbers; /* Vettore di interi contenente i numeri da estrarre */
    int tot_numeri; /* Totale numeri da gestire */
}Estrazione;

/* Variabile globale che contiene i premi a disposizione dei giocatori */
extern ListaPremi premi;

void impValore(Cartella *, int );
int ctrlValore(Giocatore *,Tombolone *, int);
Cartella *genCartella (Estrazione *);
Cartella *getCartList( Cartella *, int );
Cartella *allocCartella( void );
int genBlind( int blind[][4] ,Estrazione *);
void wait(float);
void bubble_sort(int *,int);
void shuffle(int numbers[], int);
int rand_num(int, int, Estrazione *);
void fill_numbers(int num[], int ,int);
Cartella *getNextC(Cartella *);
void setIdCartella (Cartella *,int);
int getIdCartella (Cartella *);
Cartella* initCartella ();
int leggiNumeroCard( Card, int, int );
int scriviNumeroCard( Card, int, int, int );
flag leggiCheckedCard( Card, int, int );
int scriviCheckedCard( Card, int , int, flag);
int isSetCartella( Cartella * );
void controllaNumero( ListaGiocatori *list, Tombolone *t, int num );
void segnaNumeroUscitoTomb( Cart_Tomb cart_tab , int num );
void segnaNumeroUscito( Card cartella, int num );
void addCartella(Cartella *, Cartella *);
int controllaCartTomb( Cart_Tomb cart_tab, int in_a_row );
int controllaCartella( Cartella *cartella, int in_a_row );


#endif /* CARDMANAGER_H_ */
