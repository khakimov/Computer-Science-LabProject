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

    system("COLOR 3F");

    estr.num_gen = 0;
    estr.tot = 0;
    estr.total_number = 90;
    estr.numbers = NULL;

    list.list_g = allocGiocatore();
    setTotG(&list, 1);
    setNumCartelleGioc(leggiPrimoGioc(&list), 2);


    createCartelle(leggiPrimoGioc(&list), &estr);
    /*
    printCartelle( leggiPrimoGioc(&list));
    */

	return EXIT_SUCCESS;
}
