/*
 * ErrorManager.h
 *
 *  Created on: 14/mag/2012
 *      Author: AlexZ
 *
 *      Simple Error Manager create in order
 *      to manage all the possible error that
 *      could be generated while we're used the
 *      Matrix Library.
 *      Everything works using a specific errno global
 *      value whose aim was to take trace of the last error
 *      that was tracked during the execution.
 *
 */

#ifndef _ERRORMANAGER_H_
#define _ERRORMANAGER_H_

#include <stdio.h>

/*< ------------ Specific error that could be tracked ----------------------> */

#define EMNI -1 /* Error matrix not initialized */
#define EMPAR1 -7 
#define EMPAR2 -8
#define EMROW -2 /* Error matrix's row not correct */
#define EMCOL -3 /* Error matrix's col not correct */
#define EMNEQ -4 /* Error matrices are not equal */
#define EMPROD -5 /* Error the matrices haven't the correct row and col in order to do the vectorial product */
#define EMCOORD -6 /* Error in selecting the position in which will be located the element that will be selected from the matrix */
#define EMNOTF 0 /* Error not found, everything is ok fortunately :) */

extern int mat_err;
extern char *mat_list[];

void mat_error( char * );
void set_error( int );
int get_curr_error( void );


#endif


