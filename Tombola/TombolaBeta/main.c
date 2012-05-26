#include "manage.h"

int main()
{
   ListPlayer list;
   srand(time(NULL));

   initGame(&list);

    while( playGame( &list) )
        ;

    system("PAUSE");
    return EXIT_SUCCESS;

}
