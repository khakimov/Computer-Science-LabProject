/*
 * ErrorManager.c
 *
 *  Created on: 14/giu/2012
 *
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
	ENUMESTR - errore accesso al campo che identifica i numeri estratti della struttura Estrazione ( -15 )
    EDIMVET - errore accesso al campo che identfica la dimensione del vettore di numeri ( -16 )
    ENUMGEN - errore nell'accesso al campo che rappresenta il numero di elementi da generare (-17)
    EVET - errore nell'accesso al vettore di numeri (-18)


  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 */


void tombolaErrore( int tomb_err, char *mess )
{
    static char *error_msg[] =
    {
        [ENOTF] = "Nessun errore rilevato!!",
        [EWNUM] = "Tentativo di scrittura di un membro della struttura\nCella non valido!!",
        [ENCHEK] = "Errore nel tentativo d'accesso al membro boolean della\nstruttura Cella",
        [ELG] = "La lista dei giocatori risulta essere vuota o non inizializzata!!",
        [ELCART] = "Lista cartelle vuota o non inizializzata!!",
        [EIDG] = "Errore accesso al campo id della struttura Giocatore!!",
        [ETOTG] = "Errore accesso al campo che identifica\nil numero totale di giocatori!!",
        [ECASHG] = "Errore nell'accesso al campo che rappresenta il totale\nvinto dal Giocatore",
        [ENUMCART] = "Errre nell'accesso al campo della struttura\nGiocatore che rappresenta il numero di cartelle possedute",
        [ERTOMB] = "Errore nell'accesso alle righe della struttura Tombolone",
        [ECTOMB] = "Errore nell'accesso alle colonne della struttura Tombolone",
        [ENUMT] = "Errore nell'accesso ad un elemento del Tombolone!!",
        [EI] = "Errore nell'accesso alla struttura Impostazioni\n Struttura non inizializzata!",
        [EIDIMT]"Errore nell'impostazione delle dimensioni del tombolone!\nIl numero specificato deve essere un multiplo di 90!!",
        [EINUMG] = "Errore nell'impostazione del numero di giocatori delle Impostazioni",
        [EINUMCART] = "Errore nell'accesso al numero di cartelle delle impostazioni!",
        [ETOTESTR] = "Errore nell'accesso al totale dei numeri presenti nel tombolone della struttura Estrazione",
        [ENUMESTR] = "Errore nell'accesso al totale dei numeri estratti della struttura Estrazione",
        [EVET] = "Errore nell'accesso al vettore di numeri usati per l'estrazione",
        [ENUMGEN] = "Errore nell'accesso al totale di numeri da generare",
        [EITOMB] = "Impossibile inizializzare il tombolone.\nIl valore numerico scelto supera le possibilità della macchina stessa.",
        [ENOMTOP] = "Errore nell'accesso al nome del Giocatore in Topten",
        [EPUNTOP] = "Errore nell'accesso al punteggio del giocatore in Topten",
        [ENOMPR] = "Errore nell'accesso al nome del Premio",
        [EVINPR] = "Errore nell'accesso all'id del vincitore del premio",
        [ENOMSAVE] = "Il nome scelto per il file di salvataggio\n non risulta essere valido!",
        "Errore nella lettura dell'id della cartella",
        "Tentativo di lettura di un membro della struttura Cella non valido!!",
         "Errore nella lettura del campo checked della struttura Cella!",
         "Errore nella lettura dell'id del giocatore. Struttura non inizializzata!",
         "Errore nella lettura del numero di cartelle del giocatore!!",
         "Errore nella lettura del totale vinto dal giocatore!",
         "Errore nella lettura delle Impostazioni. Numero di giocatori non valido.",
         "Errore nella lettura delle Impostazioni. Numero di elementi del tombolone non valido",
         "Errore nella letture del campo 'Numero cartelle' della struttura\nImpostazioni",
         "Errore nella lettura di un numero del Tombolone"


    };


    switch( tomb_err )
    {

        case EIDCART : tomb_err = 26;  break;
        case ENUMCARD : tomb_err = 27; break;
        case ERCHEK : tomb_err = 28; break;
        case ERIDG : tomb_err = 29; break;
        case ERNUMCART : tomb_err = 30; break;
        case ERCASHG : tomb_err = 31; break;
        case ERITOTG : tomb_err = 32; break;
        case ERIDIMT : tomb_err = 33; break;
        case ERINUMC : tomb_err = 34; break;
        case ERNUMT : tomb_err = 35; break;

    }

    if ( !mess )
        strcpy(mess, "\0");

    fprintf(stderr,"TOMB ERROR: %s\n%s\n", error_msg[tomb_err], mess);



}

