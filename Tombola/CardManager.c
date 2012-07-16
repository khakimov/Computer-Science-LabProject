/*
 * CardManager.c
 *
 *  Created on: 14/giu/2012
 *
 */
 #include "CardManager.h"
 #include "TombolaFunction.h"


/*
    Ritorna un puntatore a Cartella
    settato  a NULL.

*/
Cartella *initCartella( void )
{
     return NULL;
}

/*
    Ritorna il campo id della struttura Cartella.

*/

int leggiIdCartella(Cartella *c)
{
    int errore = ENOTF;

     if ( !isSetCartella(c) )
        errore = EIDCART;

     return ( errore == EIDCART) ? EIDCART : c->id;
}

/*
    Controlla se la lista di cartelle e' piena o meno.
    Se è piena ritorna 1 altrimenti setta la varibile
    globale tomb_err con ELCART( Errore Lista Cartelle )
    ritornando 0.
*/
int isSetCartella( Cartella *cart )
{
    return ( cart ) ? 1 : 0;
}

/*
    Provvede ad impostare con il valore presente
    in id, il campo id della struttura Cartella
    denotata da c.

*/
int scriviIdCartella(Cartella *c, int id)
{
    int errore = ENOTF;

    if(!isSetCartella(c))
        errore = ELCART;
    else
        if ( id < 0 || id > MAX_NUM_ID )
            errore = EIDCART;
    else
         c->id = id;

    return errore;
}

/*
    Ritorna campo della struttura cartella che identifica il nodo
    successivo a quello passato come parametro.
*/
Cartella *leggiSuccC(Cartella *c)
{
     return c->next_cart;
}

/* Alloca memoria per un nuovo nodo di tipo Cartella */
Cartella *allocCartella()
{
     return malloc(sizeof(Cartella));
}

/* Inserisce in coda il nodo passato per parametro */
void aggCartella(Cartella *c, Cartella *comodo)
{
     if(!isSetCartella( leggiSuccC(c)))
       c->next_cart = comodo;
     else aggCartella(leggiSuccC(c),comodo);
}

/* Legge dal file di testo le coordinate delle caselle da oscurare */
void leggiSchemi( Cartella vett[] )
{
    FILE *fp;
    int posRighe, posCol, num_cart = 0;
    int cont = 1;
    int i, j;
    int c;


    /* apre il file dalla dir e nome specificate, in caso di fallimento restituisce un errore */
    if ( ( fp = fopen("schemi\\schema.txt", "r") ) == NULL )
    {
        fprintf(stderr,"FILE NOT FOUND!\n");
        getch();
        exit(-1);

    }



    /*
        Prima di acquisire i valori da settare ad EXIST
        e che rappresenteranno i numeri presenti nella cartella
        provvedo ad inizializzare ogni singola Cella della cartella
        con il valore FALSE.
    */
    for ( cont = 0; cont < 24; cont ++)
    {
        for ( i = 0; i < CARTR; i++ )
        {
            for ( j = 0; j < CARTC; j++ )
            {
                scriviCheckedCard( vett[cont].cart, i, j, FALSE);
            }
        }
    }

    /*

        A tal punto provvedo a leggere i valori di righe e colonne
        che rappresenteranno le coordinate delle celle da settare ad
        EXIST e da considerare nel processo di generazione delle cartelle.

    */

    cont = 1;
    while( ( c = fgetc(fp ) ) != EOF )
    {
        while ( c != '\n' && c != EOF)
        {

            if ( isdigit( c ) && cont == 1 )
            {
                posRighe = c-48;
                cont++;
            }
            else
                if ( isdigit(c) && cont == 2 )
                {
                    posCol = c-48;
                    cont = 1;


                    scriviCheckedCard(vett[num_cart].cart, posRighe, posCol, EXIST );
                }

            c = fgetc(fp);

        }


        vett[num_cart].next_cart = NULL;
        num_cart++;


    }

    fclose(fp);
}

/* Imposta in base alle coordinate della casella il numero opportuno
   al fine di riempiera la scheda con le giuste numerazioni */
void impostaValori( Cartella vett[], Estrazione *estr )
{
    int i, j;
    int cont;
    int decina = leggiTotNumeri(estr) / 90;



	/* Per ogni colonna della cartella */
    for ( j = 0; j < CARTC; j++ )
    {
        if ( j == 8 )
        {
            scriviTotNumEstratti(estr, 0);
            scriviNumGen(estr, 11 );
        }

        else
         if ( j == 0 )
         {
            scriviTotNumEstratti(estr, 0);
            scriviNumGen(estr, 9 );
         }
         else
         {
            scriviTotNumEstratti(estr, 0);
            scriviNumGen(estr, 10 );
         }

		/* Per ogni singola nuova cartella */
        for( cont = 0; cont < 24; cont++)
        {
           /* per ogni riga della cartella */
            for ( i = 0; i < CARTR; i++)
            {
                /* verifica che il campo non sia oscurato in base agli schemi della scheda */
                if ( leggiCheckedCard( vett[cont].cart, i, j ) == EXIST )
                {
                    /* verifica la grandezza del campo della tombola, in caso del campo maggiore di 90, la decina ha un valore superiore ad 1 */
                    if ( decina > 1)
                    {
                        switch( j )
                        {
                            case 0 : scriviNumeroCard( vett[cont].cart, i, j, numCasuale(1,((decina)*10)+9,estr)); break;
                            case 8 : scriviNumeroCard( vett[cont].cart, i, j, numCasuale(0,(decina*10),estr)+10*(decina)*j); break;
                            default : scriviNumeroCard( vett[cont].cart, i, j, numCasuale(1,((decina)*10)+9,estr)+10*(decina)*j); break;

                        }
                    }
                    else
                    {
                        switch( j )
                        {
                            case 0 : scriviNumeroCard( vett[cont].cart, i, j, numCasuale(1,9,estr)); break;
                            case 8 : scriviNumeroCard( vett[cont].cart, i, j, numCasuale( 80,90,estr )); break;
                            default : scriviNumeroCard( vett[cont].cart, i, j, numCasuale(0,9,estr)+j*10); break;
                        }
                    }

                }

            }

            ordinaCelle( vett[cont].cart, j);


        }
    }

}

/* genera la cartella della tombola */
Cartella *genCartella( Estrazione *estr )
{
    static int num_cart = 0;

    static Cartella vettCartelle[24];
    Cartella *comodo = allocCartella();


    /*
        Se il numero totale delle cartelle utilizzate è zero
        oppure si è nella situazione iniziale del gioco nella quale
        bisogna inizializzare tutte le strutture
        allora provvedi a generare gli schemi delle cartelle.
    */
    if ( num_cart == 0 || leggiTotNumEstratti(estr) == 0 )
    {
        leggiSchemi( vettCartelle);
        impostaValori(vettCartelle, estr);

    }


    *comodo = vettCartelle[num_cart];

    if ( num_cart == 23 )
        num_cart = 0;
    else
        num_cart++;


    return comodo;

}

/*
    Riempie il vettore num con valori interi che vanno da min a max.
*/
void riempiNumeri( int num[], int min, int max )
{
    int i;
    int k;

    for ( i = 0, k = min; i < (max-min)+1; num[i] = k, i++, k++ );




}
/* genera un numero casuale nel dominio assegnato in ingresso */
int numCasuale( int min, int max, Estrazione *estr)
{
    int rand_number;
    /* se il vettore dei numeri da estrarre casualmente è vuoto allora questo viene inizializzato */
    if ( !leggiVettoreNumeri(estr) )
        allocVettoreNumeri(estr, leggiTotNumeri(estr));
   /* se il numero degli elementi da estrarre è pari a zero oppure ha superato il numero di generazioni
      viene re-inizializzato nuovamente, in caso contrario viene estratto un numero casuale*/
    if ( leggiTotNumEstratti(estr) == 0 || leggiTotNumEstratti(estr) >= leggiNumGen(estr) )
    {
    	scriviTotNumEstratti(estr, 0);
    	riempiNumeri( leggiVettoreNumeri(estr), min, max);
    	mischiaNumeri(leggiVettoreNumeri(estr), (max-min)+1);

    	rand_number = estr->numbers[estr->tot_numeri_estr++];

    }
    else
    	rand_number = estr->numbers[estr->tot_numeri_estr++];

    return rand_number;
}


/* mischia in maniera pseudo-casuale i numeri di un vettore */
void mischiaNumeri( int numbers[], int n )
{
    int i = 0;
    int n_rand;
    int temp;

    for( i = n-1; i > 0; i-- )
    {
        n_rand = rand() % n;
        temp = numbers[i];
        numbers[i] = numbers[n_rand];
        numbers[n_rand] = temp;
    }
}

void ordinaCelle( Card vet, int n)
{
    int comodo;

    /*
        Ordinamento dei vari elementi delle colonne della cartella
        che risultano essere settati ad EXIST, ossia tutti valori che devono
        essere presi in considerazione durante la generazione della cartella.

    */

    /*
    ------------------------------------------------------------------------
    -----------      CONTROLLI SUL VALORE DEGLI ELEMENTI         -----------
    ------------------------------------------------------------------------

    */

    if ( leggiCheckedCard( vet , 0, n ) == EXIST && leggiCheckedCard( vet , 1, n ) == EXIST )
    {
        /*  <<<<<<<<<< Se si considera l'elemento della prima riga e quello della seconda >>>>>>>>>>*/
        if ( leggiNumeroCard ( vet, 0, n) > leggiNumeroCard ( vet, 1, n))
        {
            comodo = leggiNumeroCard( vet, 0, n);
            scriviNumeroCard(vet, 0,n, leggiNumeroCard( vet , 1, n ));
            scriviNumeroCard(vet, 1,n, comodo);
        }

    }
    else
     if ( leggiCheckedCard( vet , 0, n ) == EXIST && leggiCheckedCard( vet , 2, n ) == EXIST )
     {

        if ( leggiNumeroCard ( vet, 0, n) > leggiNumeroCard ( vet, 2, n))
        {
            comodo = leggiNumeroCard( vet, 0, n);
            scriviNumeroCard(vet, 0,n, leggiNumeroCard( vet , 2, n ));
            scriviNumeroCard(vet, 2,n, comodo);
        }

     }
     else
      if ( leggiCheckedCard( vet , 1, n ) == EXIST && leggiCheckedCard( vet , 2, n ) == EXIST )
      {
        if ( leggiNumeroCard ( vet, 1, n) > leggiNumeroCard ( vet, 2, n))
        {
            comodo = leggiNumeroCard( vet, 1, n);
            scriviNumeroCard(vet, 1,n, leggiNumeroCard( vet , 2, n ));
            scriviNumeroCard(vet, 2,n, comodo);
        }

      }


}


void wait ( float seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

/* ritorna la cartella con id pari alla posizione richiesta all'interno della lista */
Cartella *leggiCartLista(Cartella *c, int pos)
{
    while ( pos != leggiIdCartella(c) )
    c = leggiSuccC(c);

   return c;
}
/* legge il numero nella cartella in base alle coordinate della cella
   ritorna un errore se le coordinate non rispettano i vincoli della
   dimensione della cartella */
int leggiNumeroCard( Card cart, int i, int j )
{
    int errore = ENOTF;

    if ( ( i < 0 || i > CARTR ) && ( j < 0 || j > CARTC ) )
        errore = ENUMCARD;

    return ( errore == ENUMCARD ) ? errore : cart[i][j].num;
}
/* scrive il numero all'interno della cartella in base alle coordinate della cella
   ritorna un errore se le coordinate non rispettano i vincoli della
   dimensione della cartella */
int scriviNumeroCard( Card cart, int i, int j, int num  )
{
    int errore = ENOTF;

    if ( ( i < 0 || i > CARTR ) && ( j < 0 || j > CARTC ) && ( num < 0 ) )
        errore = EWNUM;
    else
        cart[i][j].num = num;

    return errore;

}

/* restituisce il valore della cella in base alle coordinate */
flag leggiCheckedCard( Card cart, int i, int j )
{
    int errore = ENOTF;

    if( ( i < 0 || i > CARTR ) || ( j < 0 || j > CARTC ) )
        errore = ERCHEK;

    return ( errore == ERCHEK ) ? errore : cart[i][j].checked;

}
/* scrive il valore di flag di una cella in base alla coordinate */
int scriviCheckedCard( Card cart, int i, int j, flag f )
{
   int errore = ENOTF;

   if( ( i < 0 || i > CARTR ) || ( j < 0 || j > CARTC ) )
        errore = ENCHEK;
    else
        cart[i][j].checked = f;

    return errore;
}
/* verifica che il numero è presente all'interno della lista dei giocatori per ogni cartella
   associata al giocatore e in quella del tombolone */
void controllaNumero( ListaGiocatori *list, Tombolone *t, int num )
{
    int i, j;
    Giocatore *curr_g = leggiPrimoGioc(list);
    Cartella *curr_card = leggiCartella(curr_g);

    for ( curr_g = leggiPrimoGioc(list); isSetGiocatore(curr_g); curr_g = leggiSuccG(curr_g) )
        for ( curr_card = leggiCartella(curr_g); isSetCartella(curr_card); curr_card = leggiSuccC(curr_card) )
            segnaNumeroUscito( curr_card->cart, num);

    for ( i = 0; i < leggiRigheTombolone(t); i++ )
        for ( j = 0; j < leggiColTombolone(t); j++ )
            segnaNumeroUscitoTomb( t->cart_tomb[i][j], num );


}
/*segna il numero uscito all'interno del tombolone */
void segnaNumeroUscitoTomb( Cart_Tomb cart_tab , int num )
{
    int i, j;

    for( i = 0; i < CTOMBR; i++ )
        for( j = 0; j < CTOMBC; j++ )
            if( ( leggiNumFlagTombolone( cart_tab, i, j ) == EXIST ) && ( leggiNumTombolone(cart_tab, i, j )  == num ) )
                scriviNumFlagTombolone( cart_tab, i, j,  TRUE);


}
/*segna il numero uscito all'interno della cartella del giocatore */
void segnaNumeroUscito( Card cartella, int num )
{
    int i, j;

    for( i = 0; i < CARTR; i++ )
        for( j = 0; j < CARTC; j++ )
            if ( ( leggiNumeroCard( cartella, i, j )  == num ) && ( leggiCheckedCard( cartella, i, j ) == EXIST ) )
                scriviCheckedCard(cartella, i, j, TRUE);


}
/* Controlla che il numero intero passato come parametro sia presente all'interno della cartella */
int controllaCartella( Cartella *cartella, int in_a_row )
{
    int num_usciti = 0;
    int i,j;


    if ( in_a_row == 10 )
    {
        num_usciti = 15;
        for ( i = 0; i < CARTR && num_usciti == 15; i++ )
            for ( j = 0; j < CARTC && num_usciti == 15; j++ )
                if ( leggiCheckedCard(cartella->cart,i,j) == EXIST )
                    num_usciti = 0;
       /* TUTTI I NUMERI SONO USCITI, SETTO LA TOMBOLA CON  DIECI*/
        if ( num_usciti == 15 )
            num_usciti = 10;

    }
    else
    {
       for ( i = 0; i < CARTR && num_usciti != in_a_row; i++ )
       {
            num_usciti = 0;

            for ( j = 0; j < CARTC && num_usciti != in_a_row; j++ )
                if ( leggiCheckedCard( cartella->cart, i, j ) == TRUE )
                    num_usciti++;

       }
    }


    return num_usciti;

}
/* Controlla che il numero intero passato come parametro sia presente all'interno della tombola */
int controllaCartTomb( Cart_Tomb cart_tab, int in_a_row )
{
    int num_usciti = 0;
    int i,j;


    if ( in_a_row == 10 )
    {
        num_usciti = 15;
        for ( i = 0; i < CTOMBR && num_usciti == 15; i++ )
            for ( j = 0; j < CTOMBC; j++ )
                if ( leggiNumFlagTombolone(cart_tab, i,j ) == EXIST )
                    num_usciti = 0;
        if ( num_usciti == 15 )
            num_usciti = 10;

    }
    else
    {

        for( i = 0; i < CTOMBR && num_usciti != in_a_row; i++ )
        {
            num_usciti = 0;

           for ( j = 0; j < CTOMBC && num_usciti != in_a_row; j++ )
           {

               if ( leggiNumFlagTombolone(cart_tab,i,j) == TRUE )
                    num_usciti++;

           }
        }
    }

    return num_usciti;
}

