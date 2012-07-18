#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* <------------------ Types declaration ------------------------------------> */

/* Linked list which represents a list of names */
typedef struct list_name
{
	char *name; /* Pointer to char which represents a specific name */
	unsigned int length_name; /* The name's length */
	struct list_name *next_name; /* Pointer to the next node of the list */

}ListName;

/*Linked list which represents a list of dates*/

typedef struct list_year
{
	int year;
	struct list_year *next_year;

}ListYear;

/*  <-------------- Prototypes' declaration --------------------------------> */
void addNames( ListName **, char * );
void addYear( ListYear **, int );
void readFile( ListYear **, ListName **);
void printYear( ListYear * );
void printName( ListName * );
int isSetName( ListName * );
int checkYear( ListYear *, int );
int checkName( ListName *, char *);
int isSetYear( ListYear *);
ListName *initName( void );
ListYear *initYear( void );



#endif