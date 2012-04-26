/*
    ****************************************
    ****************************************
    ********    MATRIX OPERATION ***********
    ****************************************
    ****************************************

    @authors : Alessandro Suglia & Nazar Chekalin

    Simple program that uses Linked List in order to
    implement some important matrix operation like
    Vectorial Product, Scalar Product, Sum and difference
    between two matrix.

*/
#include "OpMatrix.h"


int main()
{
    
  matrice m1;
   matrice m2;
   matrice prod;
    
    creaMatrice(&m1, 2, 3);
    scriviElemento( &m1, 0,0, 1);
    scriviElemento(&m1, 0,1,3);
    scriviElemento(&m1, 0,2, 4);
    scriviElemento(&m1, 1, 0, 5);
    scriviElemento(&m1, 1,1,2);
    scriviElemento(&m1, 1, 2, 3);
    
    
    creaMatrice(&m2, 3, 2);
    scriviElemento( &m2, 0,0, 2);
    scriviElemento(&m2, 0,1,3);
    scriviElemento(&m2, 1, 0, 5);
    scriviElemento(&m2, 1,1,5);
    scriviElemento(&m2, 2, 0, 4);
    scriviElemento(&m2, 2,1,1);
    
    printf("MATRICE 1\n");
    stampaMatrice(&m1);
    printf("MATRICE 2 \n");
    stampaMatrice(&m2);
    
    printf("MATRICE PRODOTTO \n");
    creaMatrice(&prod, leggiRighe(&m1), leggiColonne(&m2));
    prodotto(&prod, &m1, &m2);
    stampaMatrice(&prod);
    
   
    system("PAUSE");
    return EXIT_SUCCESS; 

}

