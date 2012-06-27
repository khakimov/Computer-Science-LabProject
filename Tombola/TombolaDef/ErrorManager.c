/*
 * ErrorManager.c
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ
 */


#include "ErrorManager.h"
/*
 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  ----------------------------------------------------------
  		      VALORI DI RITORNO IN CASO DI ERRORE
  -----------------------------------------------------------
	ENOTF – nessun errore rilevato nel corso dell’esecuzione ( 1 )
	ERNUM – errore lettura campo intero della struttura Cell ( -1 )
	EWNUM – errore scrittura campo intero della struttura Cell (-2)
	ENUMC - errore scrittura campo intero della struttura Giocatore (-3)
	ERCHEK – errore lettura campo boolean della struttura Cell (-3)
	ELPL – errore lista giocatori vuota ( -4 )
 	ELCART – errore lista cartelle vuota ( -5 )
	ENUMCART – errore scrittura campo numero cartella della struttura Giocatore ( -6 )
	ENUMP – errore scrittura numero di giocatori totali ( -8)
	ERTOMB – errore scrittura righe del Tombolone ( -9)
	ECTOMB - errore scrittura colonne del Tombolone ( -10 )
	ENUMT - errore scrittura numeri del Tombolone ( -11 )
	EDIMT -  errore scrittura numero di elementi del tombolone ( -12 )
	EIP - errore scrittura campo numero giocatori della struttura impostazioni ( -13 )

  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */


void tombola_error( char *mess )
{
    char *error_msg[] =
    {
        "Si sta facendo accesso ad un membro della struttura Cella non valido!!",
        "Tentativo di scrittura di un membro della struttura Cella non valido!!",
        "Tentativo di lettura di un membro della struttura Cella non valido!!",
        "La lista dei giocatori risulta essere vuota!!",
        "Lista cartelle vuota!!",
        "Errore nella lettura del campo intero della struttura Giocatore!!",
        "Errore nella modifica del numero di giocatori totali!!",
        "Errore nell'accesso alla righe della struttura Tombolone!!",
        "Errore nell'accesso alle colonne della struttura Tombolone!!",
        "Errore nell'accesso di un elemento del Tombolone!!",
        "Errore nell'impostazione delle dimensioni del tombolone!\nIl numero specificato deve essere un multiplo di 90!!",
    };
    int pos;

    switch( tomb_err )
    {
        case ERNUM : pos = 0; break;
        case EWNUM : pos = 1; break;
        case ERCHEK : pos = 2; break;
        case ELPL : pos = 3; break;
        case ELCART : pos = 4; break;
        case ENUMCART : pos = 5; break;
        case ENUMP : pos = 6; break;
        case ERTOMB : pos = 7; break;
        case ECTOMB : pos = 8; break;
        case ENUMT : pos = 9; break;
        case EDIMT : pos = 10; break;
    }

    if ( !mess )
        strcpy(mess, "\0");

    printf("TOMB ERROR : %s\n%s\n", error_msg[pos], mess);

    set_error(ENOTF);

}

void set_error( int err )
{
	tomb_err = err;

}

int get_curr_error( void )
{
	return tomb_err;

}
