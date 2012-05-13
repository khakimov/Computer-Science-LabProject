#include "manage.h"

/*
    *******************************************************
    *******************************************************
    *********************** TODO **************************
    *******************************************************

    GESTIRE APPROPRIATAMENTE LA STRUTTURA DATI SOPRA RIPORTATA
    IN MODO TALE DA ESSERE IN GRADO DI INIZIALIZZARLA E DI
    STAMPARLA CORRETTAMENTE. ( SOPRATTUTTO PER L'INZIALIZZAZIONE
    E' ALQUANTO SCOMODO AVERE UN TOMBOLONE INIZIALIZZATO A MANO!! )

    VEDI PROBLEMA 1 E PROBLEMA 2
    File -> manage.c
*/

int main()
{
	Cartella cart1;
	int i, j;

	fill_cells(cart1.cart);

	printf("\tCARTELLA \n");

	for ( i = 0; i < CTR; printf("\n"), i++ )
		for ( j = 0; j < CTC; j++ )
			printf("| %2d | ", readNumber( &cart1, i, j ));




    system("PAUSE");
    return EXIT_SUCCESS;

}
