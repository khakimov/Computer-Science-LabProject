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
#include "CardManager.h"
#include "conio2.h"



int main(void)
{
    Tombolone t;
    ListaGiocatori list;
    ListaPremi lista_premi;
    Estrazione estr;
    Impostazioni imp;

    
    textcolor(15);
    srand(time(NULL));
    
    imp.max_cartelle = 6;
    imp.num_tot_player = 6;
    imp.dim_tombolone = 90;
    imp.audiov = T;
    imp.audionum = F;
    
    //nuova_partita(&imp);
    impostazioni_gioco(&imp);
    getch();
	return EXIT_SUCCESS;
}
