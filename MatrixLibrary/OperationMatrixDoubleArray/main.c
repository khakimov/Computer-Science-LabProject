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
	matrice m2;
    matrice m3;

	creaMatrice(&m1, 2, 2);

	scriviElemento(&m1, 0,0,1);

	scriviElemento(&m1, 0,1,2);
    creaMatrice(&m2, 2, 2);
	trasposta(&m2, &m1);
	stampaMatrice(&m2);
	mat_error("\n");

	scriviElemento(&m1, 1,0,3);

	scriviElemento(&m1, 1, 1,4);
    mat_error("");

    stampaMatrice(&m1);


    return EXIT_SUCCESS;

}

