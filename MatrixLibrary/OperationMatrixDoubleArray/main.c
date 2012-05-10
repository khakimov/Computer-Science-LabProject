/*
    ****************************************
    ****************************************
    ********    MATRIX OPERATION ***********
    ****************************************
    ****************************************

    @authors : Alessandro Suglia & Nazar Chekalin

*/


#include "OpMatrix.h"

/* < --------------- Constant definition ------------------------> */
#define MAX 20 /* Total number of matrix */

/* < --------------------- main function ------------------------> */
int main()
{

   matrice m1; /* First matrix variable */
   matrice m2; /* Second matrix variable */
   matrice prod, /* Matrix product */
   	   	   risultati[MAX],  /* An array of matrix type variable will be used temporarily to hold all the result matrix*/
   	   	   trasp; /* Matrix which will hold the transposed matrix */
   FILE *mat_file; /* Pointer to a textual file */
   FILE *mat_file2; /* Pointer to a binary file */
   int i, /* Used in order to loop through the array of result matrixs */
   	   n_mat; /* Result matrix's number */

    if ( ( mat_file = fopen("matrix.txt", "r") ) != NULL )
        leggiMatriceDaFile(mat_file, &m1);
    else
       	{
       		perror("ERROR ::>> ");
       		getchar();
       		exit(-1);

       	}

    creaMatrice(&m2, 3, 2);
    scriviElemento( &m2, 0,0, 2);
    scriviElemento(&m2, 0,1,3);
    scriviElemento(&m2, 1, 0, 5);
    scriviElemento(&m2, 1,1,5);
    scriviElemento(&m2, 2, 0, 4);
    scriviElemento(&m2, 2,1,1);

    printf("\nMATRICE 1\n");
    stampaMatrice(&m1);


    printf("MATRICE 2 \n");
    stampaMatrice(&m2);

    printf("MATRICE PRODOTTO \n");
    creaMatrice(&prod, leggiRighe(&m1), leggiColonne(&m2));
    prodotto(&prod, &m1, &m2);
    stampaMatrice(&prod);

    if ( ( mat_file2 = fopen("result_matrix", "ab+")) != NULL )
        stampaMatriceSuFileBinario(mat_file2, &prod);
    else
    	{
    		perror("ERROR ::>> ");
    		getchar();
    		exit(-1);

    	}

    creaMatrice(&trasp, leggiColonne(&m1), leggiRighe(&m1));
    trasposta(&trasp, &m1);

    printf("TRASPOSTA : \n");
    stampaMatrice(&trasp);
    stampaMatriceSuFileBinario(mat_file2, &trasp);

    fseek(mat_file2,0,SEEK_SET);

    n_mat = leggiMatriciRisultato(mat_file2, risultati);

    printf("MATRICI LETTE DA FILE BINARIO\n");
    printf("TOTALE MATRICI %d\n", n_mat);

    for ( i = 0; i < n_mat; printf("\n"),i++ )
    	stampaMatrice(&risultati[i]);

    fclose(mat_file);
    fclose(mat_file2);
    system("PAUSE");

    return EXIT_SUCCESS;

}

