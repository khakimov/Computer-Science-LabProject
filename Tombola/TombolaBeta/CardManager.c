#include "CardManager.h"


void card_generator( Card card )
{
    int vet[3];
    int i,j,z,x;
    int error = 1;
    int cont = 1;
    int dark[3][4];
    static int tot = 0;
    static int num_gen = 3;

   for( j=0; j<9; j++)
   {
    for (i=0; i<3; i++)
      {

          if( j==0) vet[i] = rand_num (1,9);
          else if ( j==8 )  vet[i] = rand_num ( 79,90 );
               else vet[i] = rand_num(0,9)+j*10;
      }
    bubble_sort(vet,3);
    for(i=0;i<3;i++) card[i][j].num=vet[i];
   }

   for(i=0;i<3;i++)
    for(j=0;j<9;j++) card[i][j].check=1;

   while(error)
  {
    error = dark_generator( dark, tot, num_gen );
    if(error)
     cont++;

  }

  z=0;
  for(i=0;i<3;i++)
  {
    for(j=0;j<9;j++)
    {
       for(x=0;x<4;x++)
        if(j==dark[z][x]) card[i][j].check=0;
    }
    z++;
  }






}


/*
    Function : fill_numbers()
    Parameters :
    - int num[] integer array which will contains all the value from 1 to 90
    - int n array's length

*/

void fill_numbers ( int num[], int min, int max )
{
    int i;
    int k;

    for ( i = 0, k = min; i < (max-min)+1; num[i] = k, i++, k++ );


}

/*
    Function: rand_num()
    Returns :
    a random number generate using shuffling

    rand_num() uses a static array in order to
    shuffle all the ninety value that was contained in it
    using the modern implementation of Durstenfeld of the
    Fisher-Yaste's shuffling algorithm.


*/int rand_num( int min, int max)
{
    static int numbers[TOT_NUM];
    int rand_number;
    static int tot = 0;
    static int num_gen = 3;

    if ( tot == 0 || tot >= num_gen )
    {
    	tot = 0;
    	fill_numbers(numbers, min, max);
    	shuffle(numbers, (max-min)+1);
    	rand_number = numbers[tot++];

    }
    else
    	rand_number = numbers[tot++];

    return rand_number;
}

int dark_generator ( int dark[3][4], int tot, int num_gen )
{
  int error = 0;
  int cont = 0;
  int comodo = 0;

  int i,j;
  int vet[3][4];

  num_gen = 4;
  tot = 0;


  for ( i=0; i<3; i++)
  {
   for ( j=0; j<4; j++)
    vet[i][j] = rand_num (0,8);
   bubble_sort(vet[i],4);

   if ( vet[i][0] >= 4 || vet[i][3] <= 4 )error = 1;

   for ( j=0; j<4 ; j++)
      if((vet[i][j+1]-vet[i][j])>=5)error = 1;

   }

   while(comodo<9)
   {
    for ( i=0; i<3; i++)
     for ( j=0; j<4; j++)
        if(vet[i][j]==comodo) cont++;

    if(cont==0 || cont>=3)
    {
      error = 1;
      comodo=9;
    }
    else
    {
         cont = 0;
         comodo++;
    }

  }


  memcpy(dark,vet,sizeof(int)*12);

  return error;

}

void shuffle( int numbers[], int n )
{
    int i = 0;
    int n_rand;
    int temp;



    for( i = n-1; i > 0; i-- )
    {
        n_rand = rand() % n;
        temp = numbers[i];
        numbers[i] = numbers[n_rand];
        numbers[n_rand] = temp;
    }
}

void bubble_sort( int *vet, int n)
{
     int scambio = 1,i,comodo;

     while( scambio )
     {
      scambio = 0;
      for (i = 0; i < n-1; i++)
       if( vet[i] > vet[i+1])
        {
          comodo = vet[i];
          vet[i]=vet[i+1];
          vet[i+1]=comodo;
          scambio = 1;
        }
     }



}
void wait ( float seconds )
{
  clock_t endwait;
  endwait = clock () + seconds * CLOCKS_PER_SEC ;
  while (clock() < endwait) {}
}

