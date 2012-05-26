#include <stdio.h>
#include <windows.h>

#define TR 3
#define TC 2


typedef enum { NO, O } is_out;

typedef struct
{
    int num;
    is_out check;

}Cell;
typedef Cell Cart_Tomb[3][5];
typedef Cart_Tomb Tombolone[TR][TC];



void initTombolone( Tombolone );
void printTombolone( Tombolone );
void gotoxy(int x, int y);
int main()
{
    int i;
    Tombolone tomb;
    int posX = 0, posY = 0;

    initTombolone(tomb);
    printTombolone(tomb);

    return 0;

}

void initTombolone( Tombolone tomb )
{
    int row_tomb, col_tomb;
    int i, j;
    int k = 0;
    int k1 = 0;

    for ( row_tomb = 0; row_tomb < TR; row_tomb++ )
    {

          for ( i = 0; i < 3; i++ )
            {
                for ( j = 0; j < 5; j++ )
                {
                    tomb[row_tomb][0][i][j].num = j + 1 + ( k * 10);
                    tomb[row_tomb][0][i][j].check = NO;

                }
                k++;
            }

    }
    k = 0;
    for ( row_tomb = 0; row_tomb < TR; row_tomb++ )
    {

            for ( i = 0; i < 3; i++ )
            {
                for ( j = 0, k1 = 5; j < 5; j++, k1++ )
                {
                    tomb[row_tomb][1][i][j].num = k1 + 1 + ( k * 10);
                    tomb[row_tomb][1][i][j].check = NO;

                }
                k++;
            }




    }




}
void printTombolone( Tombolone tomb )
{
   int row_tomb, col_tomb;
    int i, j;
    int posX = 0, posY = 0;
    int tempX = 0, tempY = 0;

    for ( row_tomb = 0; row_tomb < TR;  row_tomb++)
    {

       for ( i = 0; i < 3; i++ )
        {
            for ( j = 0; j < 5;j++)
            {
                printf("| %2d | ", tomb[row_tomb][0][i][j].num);

            }
            gotoxy(posX,++posY);


        }
        gotoxy(posX, ++posY);


    }
    posX = 40;
    posY = 0;
    gotoxy(posX, posY);
    for ( row_tomb = 0; row_tomb < TR;  row_tomb++)
    {

       for ( i = 0; i < 3; i++ )
        {
            for ( j = 0; j < 5;j++)
            {
                printf("| %2d | ", tomb[row_tomb][1][i][j].num);

            }
            gotoxy(posX,++posY);


        }
        gotoxy(posX, ++posY);


    }


}

void gotoxy(int x, int y)
{
	COORD CursorPos = {x, y};
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, CursorPos);
}
