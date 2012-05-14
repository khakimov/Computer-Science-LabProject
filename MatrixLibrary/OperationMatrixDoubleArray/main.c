/*
    ****************************************
    ****************************************
    ********    MATRIX OPERATION ***********
    ****************************************
    ****************************************

    @authors : Alessandro Suglia & Nazar Chekalin

*/


#include "OpMatrix.h"



/* < --------------------- main function ------------------------> */
int main()
{
	matrice m1;

	creaMatrice(&m1, -2, 2);
	mat_error("Sei un coglione che cazzo inserisci valori negativi!?");
	stampaMatrice(&m1);


    return EXIT_SUCCESS;

}

