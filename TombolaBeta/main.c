#include "manage.h"

int main()
{
    ListPlayer *players;

    initGame(players);

    initTombolone();
    printTombolone();


    while( playGame( players ) )
        ;

    return EXIT_SUCCESS;
}
