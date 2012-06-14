/*
 * CardManager.h
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ
 */

#ifndef CARDMANAGER_H_
#define CARDMANAGER_H_

/* Tipo di dato enumerativo che indica se uno specifico numero è uscito o meno
 *
 * Nella generazione dei numeri viene adoperato anche il valore EXIST, per poter
 * gestire il caso in cui un valore è stato già precedentemente settato o meno,
 * in modo tale da poter garantire una corretta elaborazione di quella che è la fase
 * di generazione dei numeri casuali che andranno a comporre le cartelle.
 *
 *  */
typedef enum { FALSE, TRUE, EXIST }flag;
typedef enum { FALSE, TRUE, }boolean;

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


typedef struct giocatore
{
	struct giocatore *next_g; /* riferimento prossimo giocatore */
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

typedef struct lista_giocatori
{
	Giocatore *list_g; // elenco di giocatori
	int num_player; // numero giocatori dell’elenco
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
	Cart_Tomb ** tomb; /* insieme di cartelle che costituiscono il tombolone */
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

typedef struct impostazioni
{
	int num_tot_player; /* numero totale di giocatori impostati */
	int  dim_tombolone; /* valore numerico che rappresenta i numeri presenti nel tombolone */
	int max_cartelle; /* numero Massimo di cartelle che un giocatore può scegliere */
	char mod_game; /* modalità di gioco scelta dall’utente */
	boolean audiov; /* audio per vittoria di un premio */
	boolean audionum; /* audio estrazione di un numero */
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
	char *nome_premio; // nome del premio corrente
	int tot_cash;// totale vincita del premio
	int winner_id; // id del vincitore di quell premio
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

typedef Premio ListaPremi[5];  // insieme di premi presenti nel gioco

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
typedef struct
{
 char *nome; // Nome giocatore della topten
 int punteggio; // punteggio collezionato
}Topten;

/*
 * Salvataggio - Struttura necesaria
 * per contenere tutti i dati di gioco
 * che devon esser salvati.
 *
 */
typedef struct
{
	Tombolone t;
	ListaGiocatori lista;
	ListaPremi lista_premi;
	int *numbers;
	int tot_num;
Impostazioni imp;

}Salvataggio;




#endif /* CARDMANAGER_H_ */
