#include "manage.h"

int main()
{

	int i, j;
    initTombolone(tomb);

    writeCheckCard( tomb[0][0], 1,0, O);
    writeCheckCard( tomb[0][0], 1,2, O);
    writeCheckCard( tomb[0][0], 1,5, O);
    writeCheckCard( tomb[0][0], 1,8, NO);

    if ( checkCartTomb( tomb[0][0], 4) == 4 )
        printPrize( 2, NULL, 0);



    system("PAUSE");
    return EXIT_SUCCESS;

}
