/*
 * ErrorManager.h
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ
 */

#ifndef ERRORMANAGER_H_
#define ERRORMANAGER_H_

#include <stdio.h>
#include <string.h>

/*
 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ----------------------------------------------------------
  		      VALORI DI RITORNO IN CASO DI ERRORE
  -----------------------------------------------------------
	ENOTF – nessun errore rilevato nel corso dell’esecuzione ( 1 )
	ERNUM – errore lettura campo intero della struttura Cell ( -1 )
	EWNUM – errore scrittura campo intero della struttura Cell (-2)
	ERCHEK – errore lettura campo boolean della struttura Cell (-3)
	ENLPL – errore lista giocatori vuota ( -4 )
 	ENLCART – errore lista cartelle vuota ( -5 )
	ENUMCART – errore scrittura campo numero cartella della struttura Giocatore ( -6 )
	ENUMP – errore scrittura numero di giocatori totali ( -8)
	ERTOMB – errore scrittura righe del Tombolone ( -9)
	ECTOMB - errore scrittura colonne del Tombolone ( -10 )
	ENUMT - errore scrittura numeri del Tombolone ( -11 )
	EIMPD -  errore scrittura numero di elementi del tombolone ( -12 )
	EIP - errore modifica numero di giocatori delle Impostazioni ( -13 )
	ECASH - errore modifica campo cash della struttura Giocatore ( -14 )

  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */

#define ENOTF 1
#define ERNUM -1
#define EWNUM -2
#define ERCHEK -3
#define ELPL -4
#define ELCART -5
#define ENUMCART -6
#define ENUMP -7
#define ERTOMB -8
#define ECTOMB -9
#define ENUMT -10
#define EDIMT -11
#define EIMPD -12
#define EIP -13
#define ECASH -14

/*
 * variabile globale che rappresenta l'errore attualmente riscontrato.
 *
 * */
int tomb_err;

/*
    Controlla appositamente l'errore attualmente
    commesso e provvede a stampare a video un opportuno
    messaggio d'errore.
*/
void tombola_error( char * );
/*
    Garantisce la modifica della variabile globale
*/
void set_error( int );
/*
    Ritorna il corrente valore d'errore riscontrato
    contenuto nella variabile globale tomb_err.
*/
int get_curr_error( void );



#endif /* ERRORMANAGER_H_ */
