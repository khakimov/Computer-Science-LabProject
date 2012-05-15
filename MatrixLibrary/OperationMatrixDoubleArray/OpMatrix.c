#include "OpMatrix.h"
#include "ReadWriteFoo.h"

/* Prints to video the values present in the matrix passed as a parameter */
int stampaMatrice( matrice *mat )
{
  int i,j;

  if ( matrixExist(mat) )
  {
	  for(i = 0; i < leggiRighe(mat); printf("\n"),i++)
		  for(j=0;j < leggiColonne(mat);j++)
			  printf("%15.3f ",leggiElemento(mat, i, j)); 
	 
  }

  return ( get_curr_error() == EMNOTF ) ? 1 : 0;
}

/*
    Function which make the transposition operation of a
    matrix passed as a parameter.
    It returns a double pointer which points to the current location
    in which the new trasposed matrix will be.
*/
matrice* trasposta( matrice *mt, matrice *m )
{
  int i,j;
  
  if ( !matrixExist(m) )
  {
    set_error(EMNI);
    
  }
  else
  {
      
      for ( i=0; i < leggiRighe(mt); i++ )
          for ( j = 0; j < leggiColonne(mt); j++ )
              scriviElemento(mt,i,j,leggiElemento(m,j,i));
  }
  
  return ( get_curr_error() == EMNOTF ) ? mt : NULL;
}


matrice* somma( matrice *sum_mat, matrice *m, matrice *n)
{
    int i, j;
    
    if ( !matrixExist(m) )
    {
      set_error(EMPAR1);
     
           
    }
    else
        if ( !matrixExist(n) ) 
        {
              set_error(EMPAR2);
              
          
        }
    else
        if ( !checkDim( m , n) )
        {
             set_error(EMNEQ);
             
        }
    else          
    {
        for ( i = 0; i < leggiRighe(sum_mat); i++ )
            for ( j = 0; j < leggiColonne(sum_mat); j++ )
                scriviElemento( sum_mat,i, j, leggiElemento(m, i, j) + leggiElemento(n, i, j));
    }
    
    return ( get_curr_error == EMNOTF ) ? sum_mat : NULL;
    

}

matrice* scalare( matrice *ma, matrice *m, float a )
{

    int i, j;

  if ( !matrixExist(m) )
  {
    set_error(EMNI);
    
  }
  else
  {
    for( i = 0; i < leggiRighe(ma); i++ )
        for ( j = 0; j < leggiColonne(ma); j++ )
            scriviElemento(ma,i,j, a * leggiElemento(m,i,j));
  }          

  return ( get_curr_error() == EMNOTF ) ? ma : NULL;

}

matrice* differenza( matrice *diff_mat, matrice *m, matrice *n )
{
    int i,j;

    if ( !matrixExist(m) )
    {
      set_error(EMPAR1);
      
           
    }
    else
        if ( !matrixExist(n) ) 
        {
              set_error(EMPAR2);
              
          
        }
    else
        if ( !checkDim( m , n) )
        {
             set_error(EMNEQ);
             
        }
    else 
    {
        for( i=0; i < leggiRighe(diff_mat);i++)
             for(j=0; j < leggiColonne(diff_mat); j++)
              scriviElemento( diff_mat, i, j, leggiElemento(m,i,j)- leggiElemento(n, i,j));
    }         

    return ( get_curr_error() == EMNOTF ) ? diff_mat : NULL;
}

matrice* prodotto( matrice *prod_mat, matrice *m, matrice *n)
{

    int i,j,k;
    int tot = 0;
    
    if ( !matrixExist(m) )
    {
      set_error(EMNI);
      
           
    }
    else
        if ( !matrixExist(n) ) 
        {
              set_error(EMNI);
              
          
        }
    else
        if ( !checkRowCol( m , n) )
        {
             set_error(EMPROD);
             
        }
    else
        if ( matrixExist(prod_mat) )
        {
            set_error(EMNI);     
             
        }
    else 
    {
    for(i=0;i< leggiRighe(prod_mat);i++)
       for(j=0;j< leggiColonne(prod_mat);j++)
       {
    	  tot = 0;

          for(k=0;k < leggiColonne(m);k++)
          tot += leggiElemento(m,i,k)* leggiElemento(n,k,j);
            scriviElemento( prod_mat, i, j, tot);
       }
    }   
    
    return ( get_curr_error() == EMNOTF ) ? prod_mat : NULL;
}

