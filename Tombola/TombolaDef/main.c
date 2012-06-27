/*
 ============================================================================
 Name        : main.c
 Author      : Alessandro Suglia & Nazar Chekalin
 Version     :
 Copyright   :
 Description : Game of Tombola
 ============================================================================
 */

#include "TombolaFunction.h"

int main(void)
{
    Tombolone t;
    ListaGiocatori list;
    ListaPremi lista_premi;
    Estrazione estr;
    Impostazioni imp;
    Giocatore new_g;

    system("COLOR 3F");

    estr.num_gen = 0;
    estr.tot = 0;
    estr.total_number = 90;
    estr.numbers = NULL;

    new_g.cart_g = initCartella();
    new_g.cash = 200;
    new_g.id = 1;
    new_g.next_g = initListaG();
    new_g.num_cartelle = 2;


    addGiocatore( leggiPrimoGioc(&list), &new_g );

    //createCartelle(leggiPrimoGioc(&list), &estr);
    /*
    printCartelle( leggiPrimoGioc(&list));
    */

	return EXIT_SUCCESS;
}
