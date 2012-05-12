#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <windows.h>

void printFile( char * );
void menu();
void carica();
void nuova();
void impostazioni();
void topten();
void istruzioni();
void uscita();
void ResizeWindows();

int main()
{
    int scelta = 1;


    ResizeWindows();

    SetConsoleTitle("IL GIOCO DELLA TOMBOLA - Created by Alessandro Suglia & Nazar Chekalin");

   system("COLOR 3F");

   while ( scelta != 0 )
   {
      menu();
      scanf("%d", &scelta);

      switch( scelta )
      {
        case 1 : nuova();
        break;
        case 2 : carica();
        break;
        case 3 : impostazioni();
        break;
        case 4 : topten();
        break;
        case 5 : istruzioni();
        break;
        case 0 : uscita();
        break;

        default : printf("INCORRECT OPTION\n");



      }

   }
   getch();


}


void ResizeWindows( void )
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsole,&info);

    SMALL_RECT size = {0, 0, info.dwMaximumWindowSize.X-1, info.dwMaximumWindowSize.Y-20};

    SetConsoleWindowInfo( hConsole, TRUE, &size);
}
void menu()
{

     printFile("tombola.txt");
     printf("%s\n%s\n%s\n%s\n%s\n%s\n%s",
            "1 - NUOVA PARTITA",
            "2 - CARICA PARTITA",
            "3 - IMPOSTAZIONI",
            "4 - TOP TEN",
            "5 - ISTRUZIONI",
            "0 - ESCI",
            "SCELTA : "
            );



}

void printFile( char *filename )
{
     FILE *fp;
     int tot_char = 0;
     char c;

     clrscr();
     system("COLOR 3F");
     if ( ( fp = fopen(filename, "r")) == NULL )
        exit(-1);

    while ( ( c = fgetc(fp) ) != EOF  && tot_char < 1805 )
    {

       printf("%c", c);
       tot_char++;


    }
    /*if ( tot_char == 737 )
        printf("\nPremi INVIO per visualizzare l'altra pagina, ESC per menu' principale\n");
    printf("\n");
    getch(); */
     fclose(fp);
}
void impostazioni()
{
  printFile("impostazioni.txt");
  getch();


}

void uscita()
{
   printFile("uscita.txt");

}
void carica()
{
     printFile("carica.txt");
    printf("%s\n%s\n%s\n",
           "---------------------------",
           "      PARTITE SALVATE ",
           "---------------------------"
           );
   printf("%s\n%s\n%s\n%s\n%s\n%s\n",
          "1 - gino",
          "2 - tonio",
          "3 - natale2011",
          "4 - prova11",
          "5 - tombola1",
          "6 - maner");

   printf("Quale salvataggio intendi caricare ? \n");
   printf("Partita 1 scelta : gino\tCaricamento in corso . . .\n");
   getch();
}


void topten()
{
     printFile("topten.txt");

    printf("POS.\t   NAME\t\t  TOT GAINED\n\n");
    textcolor(4);
    printf("1st\t%10s\t\t%4d\n\n","Alessandro", 577);
    textcolor(2);
    printf("2nd\t%10s\t\t%4d\n\n", "Nazario",550);
    textcolor(5);
    printf("3rd\t%10s\t\t%4d\n\n", "Daniele",490);
    textcolor(6);
    printf("4th\t%10s\t\t%4d\n\n","Anna", 485);

    printf("5th\t%10s\t\t%4d\n\n", "Tonio", 478);
    printf("6th\t%10s\t\t%4d\n\n", "Pino",450);
    printf("7th\t%10s\t\t%4d\n\n", "Gianvito", 449);
    printf("8th\t%10s\t\t%4d\n\n", "Raffaele",447);
    printf("9th\t%10s\t\t%4d\n\n", "Paolo",420);
    printf("10th\t%10s\t\t%4d\n\n","Filippo", 300);
    getch();


}

void istruzioni()
{
    printFile("istruzioni.txt");
    printf("\nPremi INVIO per visualizzare l'altra pagina, ESC per menu' principale\n");
    getch();



}

void nuova()
{
    int scelta;
    int flag = 0;
    printFile("nuova.txt");


    while ( scelta != 4)
    {
          scanf("%d",&scelta);
    switch(scelta)
    {
      case 1: if(!flag)
              {
                printFile("cartelle.txt");
                flag = 1;
              }
                else printFile("cartelle2.txt");

      break;
      case 2: printFile("giocatore2.txt");
      break;
      case 3: printFile("mex.txt");
      break;
      case 4: printFile("abbandona.txt");
      break;
    }
    }
     getch();

}
