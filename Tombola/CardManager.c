/*
 * CardManager.c
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ
 */
 #include "CardManager.h"
 #include "TombolaFunction.h"

 ListaPremi premi = { { "Ambo", 50, 0, F, 0 }, { "Terno", 70, 0, F, 0 }, { "Quaterna", 90, 0, F,0 },
                    { "Cinquina", 100, 0, F, 0 }, { "Bingo", 120, 0, F, 0 } };

Cartella *initCartella( void )
{
     return NULL;
}

int getIdCartella(Cartella *c)
{
     return c->id;
}

int isSetCartella( Cartella *cart )
{
    int controllo = 0;

    if ( !cart)
        set_error(ELCART);
    else
        controllo = 1;

    return controllo;
}
void setIdCartella(Cartella *c, int id)
{
     if(!isSetCartella(c))
       set_error(ELCART);
      else
         c->id = id;
}

Cartella *getNextC(Cartella *c)
{
     return c->next_cart;
}

Cartella *allocCartella()
{
     return (Cartella*)malloc(sizeof(Cartella));
}
/* Inserisce in coda il nodo passato per parametro */
void addCartella(Cartella *c, Cartella *comodo)
{
    if(!isSetCartella(c->next_cart))
       c->next_cart = comodo;
     else addCartella(getNextC(c),comodo);
}



Cartella * genCartella(Estrazione *estr)
{
    int vet[3];
    int i,j,z,x;
    static int id_cart = 1;
    Cartella *comodo = allocCartella();
    int error = 1;
    int blind[3][4];
    scriviNumGen(estr, 3);
    scriviTotNumEstratti(estr, 0);


   for( j=0; j<CARTC; j++)
   {
    for (i=0; i<CARTR; i++)
      {

          if( j==0) vet[i] = rand_num (1,9,estr);
          else if ( j==8 )  vet[i] = rand_num ( 79,90,estr );
               else vet[i] = rand_num(0,9,estr)+j*10;
      }

    bubble_sort(vet,3);

    for(i=0;i<3;i++)
     {
       scriviNumeroCard(comodo->cart,i,j,vet[i]);
       scriviCheckedCard(comodo->cart,i,j, EXIST);
     }
   }

   while(error)
    error = genBlind( blind ,estr);


  z=0;
  for(i=0;i<3;i++)
  {
    for(j=0;j<9;j++)
    {
       for(x=0;x<4;x++)
        if(j==blind[z][x])
         scriviCheckedCard(comodo->cart,i,j, FALSE);
    }
    z++;
  }
  comodo->next_cart = NULL;
  setIdCartella(comodo, id_cart++);
  return comodo;
}

void fill_numbers ( int num[], int min, int max )
{
    int i;
    int k;

    for ( i = 0, k = min; i < (max-min)+1; num[i] = k, i++, k++ );


}

int rand_num( int min, int max, Estrazione *estr)
{
    int rand_number;

    if ( !getVettoreNumeri(estr) )
        setVettoreNumeri(estr, leggiTotNumeri(estr));

    if ( leggiTotNumEstratti(estr) == 0 || leggiTotNumEstratti(estr) >= leggiNumGen(estr) )
    {
    	scriviTotNumEstratti(estr, 0);
    	fill_numbers( getVettoreNumeri(estr), min, max);
    	shuffle(getVettoreNumeri(estr), (max-min)+1);

    	rand_number = estr->numbers[estr->tot_numeri_estr++];

    }
    else
    	rand_number = estr->numbers[estr->tot_numeri_estr++];

    return rand_number;
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

int genBlind ( int blind[3][4],Estrazione *estr )
{
  int error = 0;
  int cont = 0;
  int comodo = 0;

  int i,j;
  int vet[3][4];

  scriviNumGen(estr,4);
  scriviTotNumEstratti(estr, 0);


  for ( i=0; i<3; i++)
  {
   for ( j=0; j<4; j++)
    vet[i][j] = rand_num (0,8,estr);
   bubble_sort(vet[i],4);

   if ( vet[i][0] >= 4 || vet[i][3] <= 4 )error = 1;

   if(!error)
   {
    for ( j=0; j<4 ; j++)
      if((vet[i][j+1]-vet[i][j])>=5)error = 1;
   }

  }

   while(comodo < CARTC && !error)
   {
    for ( i=0; i<3; i++)
     for ( j=0; j<4; j++)
        if(vet[i][j]==comodo) cont++;

    if(cont==0 || cont>= CARTR )
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


  memcpy(blind,vet,sizeof(int)*12);

  return error;

}

Cartella *getCartList(Cartella *c, int pos)
{
    while ( pos != getIdCartella(c) )
    c = getNextC(c);

   return c;
}
int leggiNumeroCard( Card cart, int i, int j )
{
    if ( ( i < 0 || i > CARTR ) && ( j < 0 || j > CARTC ) )
        set_error(ERNUM);
    else
        return cart[i][j].num;
}

int scriviNumeroCard( Card cart, int i, int j, int num  )
{
    if ( ( i < 0 || i > CARTR ) && ( j < 0 || j > CARTC ) )
        set_error(EWNUM);
    else
        cart[i][j].num = num;

    return get_curr_error();

}


flag leggiCheckedCard( Card cart, int i, int j )
{
    if( ( i < 0 || i > CARTR ) && ( j < 0 || j > CARTC ) )
        set_error(ERCHEK);
    else
        return cart[i][j].checked;
}

int scriviCheckedCard( Card cart, int i, int j, flag f )
{
   if( ( i < 0 || i > CARTR ) && ( j < 0 || j > CARTC ) )
        set_error(ERCHEK);
    else
        cart[i][j].checked = f;

    return get_curr_error();
}

void controllaNumero( ListaGiocatori *list, Tombolone *t, int num )
{
    int i, j;
    Giocatore *curr_g = leggiPrimoGioc(list);
    Cartella *curr_card = getCartella(curr_g);

    for ( curr_g = leggiPrimoGioc(list); isSetGiocatore(curr_g); curr_g = getNextG(curr_g) )
        for ( curr_card = getCartella(curr_g); isSetCartella(curr_card); curr_card = getNextC(curr_card) )
            segnaNumeroUscito( curr_card->cart, num);

    for ( i = 0; i < leggiRigheTombolone(t); i++ )
        for ( j = 0; j < leggiColTombolone(t); j++ )
            segnaNumeroUscitoTomb( t->cart_tomb[i][j], num );


}
void segnaNumeroUscitoTomb( Cart_Tomb cart_tab , int num )
{
    int i, j;

    for( i = 0; i < CTOMBR; i++ )
        for( j = 0; j < CTOMBC; j++ )
            if( ( leggiNumFlagTombolone( cart_tab, i, j ) == EXIST ) && ( leggiNumTombolone(cart_tab, i, j )  == num ) )
                scriviNumFlagTombolone( cart_tab, i, j,  TRUE);


}
void segnaNumeroUscito( Card cartella, int num )
{
    int i, j;

    for( i = 0; i < CARTR; i++ )
        for( j = 0; j < CARTC; j++ )
            if ( ( leggiNumeroCard( cartella, i, j )  == num ) && ( leggiCheckedCard( cartella, i, j ) == EXIST ) )
                scriviCheckedCard(cartella, i, j, TRUE);


}

int controllaCartella( Cartella *cartella, int in_a_row )
{
    int num_usciti = 0;
    int i,j;


    if ( in_a_row == 10 )
    {
        num_usciti = 15;
        for ( i = 0; i < CARTR && num_usciti == 15; i++ )
            for ( j = 0; j < CARTC && num_usciti == 15; j++ )
                if ( leggiCheckedCard(cartella->cart,i,j) == EXIST )
                    num_usciti = 0;
       /* TUTTI I NUMERI SONO USCITI, SETTO LA TOMBOLA CON  DIECI*/
        if ( num_usciti == 15 )
            num_usciti = 10;

    }
    else
    {
       for ( i = 0; i < CARTR && num_usciti != in_a_row; i++ )
       {
            num_usciti = 0;

            for ( j = 0; j < CARTC && num_usciti != in_a_row; j++ )
                if ( leggiCheckedCard( cartella->cart, i, j ) == TRUE )
                    num_usciti++;

       }
    }


    return num_usciti;

}

int controllaCartTomb( Cart_Tomb cart_tab, int in_a_row )
{
    int num_usciti = 0;
    int i,j;


    if ( in_a_row == 10 )
    {
        num_usciti = 15;
        for ( i = 0; i < CTOMBR && num_usciti == 15; i++ )
            for ( j = 0; j < CTOMBC; j++ )
                if ( leggiNumFlagTombolone(cart_tab, i,j ) == EXIST )
                    num_usciti = 0;
        if ( num_usciti == 15 )
            num_usciti = 10;

    }
    else
    {

        for( i = 0; i < CTOMBR && num_usciti != in_a_row; i++ )
        {
            num_usciti = 0;

           for ( j = 0; j < CTOMBC && num_usciti != in_a_row; j++ )
           {

               if ( leggiNumFlagTombolone(cart_tab,i,j) == TRUE )
                    num_usciti++;

           }
        }
    }

    return num_usciti;
}

