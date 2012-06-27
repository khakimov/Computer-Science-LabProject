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
    salvaPartita( &list, &t, &lista_premi, &estr, &imp );

	return EXIT_SUCCESS;
}
