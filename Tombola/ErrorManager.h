/*
 * ErrorManager.h
 *
 *  Created on: 14/giu/2012
 *
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
	ERNUM – errore lettura campo intero della struttura Cella
	EWNUM – errore scrittura campo intero della struttura Cella
	ERCHEK – errore lettura campo boolean della struttura Cella
	ENLPL – errore lista giocatori vuota
 	ENLCART – errore lista cartelle vuota
	ENUMCART – errore scrittura campo numero cartella della struttura Giocatore
	ENUMP – errore scrittura numero di giocatori totali
	ERTOMB – errore scrittura righe del Tombolone
	ECTOMB - errore scrittura colonne del Tombolone
	ENUMT - errore scrittura numeri del Tombolone
	EIMPD -  errore scrittura numero di elementi del tombolone
	EIP - errore modifica numero di giocatori delle Impostazioni
	ECASH - errore modifica campo cash della struttura Giocatore
	ENUMESTR - errore accesso al campo totale numeri estratti della struttura Estrazione
	EDIMVET - errore accesso al campo dimensione del vettore della struttura Estrazione
	ENUMGEN - errore accesso al campo numeri generati della struttura Estrazione
	EVET - errore nella modifica del vettore di numeri della struttura Estrazione
	EITOMB - errore inizializzazione del tombolone

  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */
#define EIDCART -1 /* Errore Letture dell'id della cartella */
#define ENUMCARD -2 /* Errore nella lettura di un numero della cartella */
#define ERCHEK -3 /* Errore nella lettura del campo checked di una elemento della cartella*/
#define ERIDG -4 /* Errore nella lettura dell'id del giocatore */
#define ERCASHG -5 /* Errore nella lettura del totale vinto dal giocatore */
#define ERNUMCART -6 /* Errore nella lettura del numero di cartelle del giocatore */
#define ERITOTG -7 /* Errore nella lettura del numero totale dei giocatori (Impostazioni )*/
#define ERIDIMT -8 /* Errore nella lettura del numero totale di elementi del tombolone ( Impostazioni )*/
#define ERINUMC -9 /* Errore nella lettura del numero di cartelle di ogni giocatore  */
#define ERNUMT -10 /* Errore nella lettura dei valori del tombolone */


enum{ ENOTF, EWNUM, ENCHEK, ELG, ELCART, EIDG, ETOTG, ECASHG, ENUMCART, ERTOMB,
     ECTOMB, ENUMT, EI, EIDIMT, EINUMG, EINUMCART, ETOTESTR, ENUMESTR, EVET, ENUMGEN,
     EITOMB, ENOMTOP, EPUNTOP, ENOMPR, EVINPR, ENOMSAVE };

/*
    Controlla appositamente l'errore attualmente
    commesso e provvede a stampare a video un opportuno
    messaggio d'errore.
*/
void tombolaErrore( int, char * );



#endif /* ERRORMANAGER_H_ */
