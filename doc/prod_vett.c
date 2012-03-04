/* <------ Header file definition --------------> */
#include <stdio.h>
/* <------ Useful constant definition ----------> */
#define MAXR 1
#define MAXC 30

/* Simple typedef instruction in order to simplify the use of the matrix*/
typedef int vet[MAXC];
typedef vet mat_row[MAXR];

typedef int vet_c[MAXR];
typedef vet_c mat_col[MAXC];

/* <------------ main function ---------------- >*/
int main()
{
    int n = 3;
    int i, j;
    mat_row a = { { 1, 3, 4} }; /* Initialization of the row matrix */
    mat_col b = { { 3}, {4}, {5} }; /* Initialization of the colomn matrix */

    mat_riga c;

    /* Simple iteration which grants the effective vectorial product between the two matrix*/
    for( i = 0; i < n; i++ )
        c[i][0] = a[0][i] * b[i][0];
    

    for( i = 0; i < n; i++ )
        printf("c[%d][0] = %d\n", i, c[i][0]);

    return 0;

}
