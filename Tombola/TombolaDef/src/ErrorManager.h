/*
 * ErrorManager.h
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ
 */

#ifndef ERRORMANAGER_H_
#define ERRORMANAGER_H_


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
	EMOD – errore scrittura modalità di gioco ( -7)
	ENUMP – errore scrittura numero di giocatori totali ( -8)
	ERTOMB – errore scrittura righe del Tombolone ( -9)
	EDIMT -  errore scrittura numero di elementi del tombolone ( -10)

  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */

#define ENOTF 1
#define ERNUM -1
#define EWNUM -2
#define ERCHEK -3
#define ENLPL -4
#define ENLCART -5
#define ENUMCART -6
#define EMOD -7
#define ENUMP -8
#define ERTOMB -9
#define EDIMT -10

/*
 * variabile globale che rappresenta l'errore attualmente riscontrato.
 *
 * */
int tomb_err;

void tombola_error( char * );
void set_error( int );
int get_error( void );



#endif /* ERRORMANAGER_H_ */
