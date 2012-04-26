#include "OpMatrix.h"

int main()
{
    matrice m1;
    matrice m2;
    matrice som;
    
    creaMatrice(&m1, 2, 2);
    scriviElemento( &m1, 0,0, 2);
    scriviElemento(&m1, 0,1, 3);
    scriviElemento(&m1, 1, 0, 58);
    scriviElemento(&m1, 1, 1, 23);
    
    creaMatrice(&m2, 2, 2);
    scriviElemento( &m2, 0,0, 21);
    scriviElemento(&m2, 0,1, 3);
    scriviElemento(&m2, 1, 0, 5);
    scriviElemento(&m2, 1, 1, 23);
    
    creaMatrice(&som, leggiRighe(&m1), leggiColonne(&m1));
    somma(&som, &m1, &m2);
    
    printf("MATRICE \n");
    stampaMatrice(&som);
    
    system("PAUSE");
    return EXIT_SUCCESS;    
}

