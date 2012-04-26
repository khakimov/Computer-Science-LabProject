#include "OpMatrix.h"

int main()
{
    matrice m1;
    
    creaMatrice(&m1, 2, 2);
    scriviElemento( &m1, 0,0, 2);
    scriviElemento(&m1, 0,1, 3);
    scriviElemento(&m1, 1, 0, 58);
    scriviElemento(&m1, 1, 1, 23);
    
    printf("MATRICE \n");
    stampaMatrice(&m1);
    
       
    system("PAUSE");
    return EXIT_SUCCESS;    
}
