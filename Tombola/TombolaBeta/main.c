#include "manage.h"

int main()
{
   ListPlayer list;

   initGame(&list);

    while( playGame( &list) )
        ;

    system("PAUSE");
    return EXIT_SUCCESS;

}
