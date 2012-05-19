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
	matrice trasp;

	/* Create m1 matrix */
	creaMatrice(&m1, 2, 2);
	scriviElemento(&m1, 0,0,1);
	scriviElemento(&m1, 0,1,2);

	printf("MATRICE M1 - PRIMA \n");
	stampaMatrice(&m1);

	/* Create m2 matrix */
	creaMatrice(&m2, 2, 2);
	somma(&m2, &m1, &m1);
	printf("MATRICE SOMMA M2 \n");
	stampaMatrice(&m2);
	mat_error("\n");

	/* Write another two element in the matrix */
	scriviElemento(&m1, 1,0,3);
	scriviElemento(&m1, 1, 1,4);

    mat_error("");

    printf("MATRICE M1 \n");
    stampaMatrice(&m1);

    creaMatrice(&trasp, 2, 2);
    trasposta(&trasp, &m1);
    mat_error("");
    printf("MATRICE TRASPOSTA \n");
    stampaMatrice(&trasp);


    mat_error("");


    return EXIT_SUCCESS;

}

