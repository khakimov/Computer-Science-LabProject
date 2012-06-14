/*
 * ErrorManager.c
 *
 *  Created on: 14/giu/2012
 *      Author: AlexZ
 */


#include "ErrorManager.h"

void tombola_error( char *mess )
{

}

void set_error( int err )
{
	tomb_err = err;

}

int get_error( void )
{
	return tomb_err;

}
