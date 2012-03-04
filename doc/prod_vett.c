#include <stdio.h>

#define MAXR 1
#define MAXC 30

typedef int vet[MAXC];
typedef vet mat_riga[MAXR];

typedef int vet_c[MAXR];
typedef vet_c mat_col[MAXC];

int main()
{
    int row = 3;
    int i, j;
    mat_riga a = { { 1, 3, 4} };
    mat_col b = { { 3}, {4}, {5} };

    mat_riga c;


    for( i = 0; i < row; i++ )
    {
        c[i][0] = a[0][i] * b[i][0];


    }

    for( i = 0; i < row; i++ )
        printf("c[%d][0] = %d\n", i, c[i][0]);

    return 0;

}
