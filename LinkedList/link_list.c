#include "link_list.h"

void addNames( ListName **list_node, char *new_string )
{
	ListName *curr = NULL;

	/* If the current node was empty, so create a new node and add the new string */
	if  ( !isSetName( *list_node ) )
	{
		curr = malloc( sizeof(ListName));
		if ( !curr ) 
		{
			perror("MALLOC ERROR ::> ");
			getchar();
			exit(-1);
		
		}
		curr->next_name = NULL;
		curr->length_name = strlen(new_string);
		curr->name = malloc( curr->length_name + 1 * sizeof(char));
		
		if ( !curr->name )
		{
			perror("MALLOC ERROR ::> ");
			getchar();
			exit(-1);
		
		}
		strcpy( curr->name, new_string);
		*list_node = curr;  
	
	}
	else 
		addNames( &(*list_node)->next_name, new_string);

}

void addYear( ListYear **list_year, int new_year )
{
	ListYear *curr = NULL;

	if ( !isSetYear( *list_year ) )
	{
		curr = malloc( sizeof(ListYear));
		if ( !isSetYear(curr) ) 
		{
			perror("MALLOC ERROR ::> ");
			getchar();
			exit(-1);
		}
	
		curr->next_year = NULL;
		curr->year = new_year;
		*list_year = curr;
	
	}
	else
		addYear( &(*list_year)->next_year, new_year );



}

void readFile( ListYear **year, ListName **name )
{
	FILE *fp;
	char buffer[512];
	int value;

	if ( ( fp = fopen("prova.txt", "r") ) == NULL )
	{
		perror("ERROR READING FILE ::> ");
		getchar();
		exit(-1);
	
	}

	while( !feof(fp) )
	{
		fscanf(fp,"%s %d\n", buffer, &value);
		addNames(name, buffer);
		addYear(year, value);
			
	}

	fclose(fp);

}
void printYear( ListYear *list_year )
{


	ListYear *curr_year = NULL;


	printf("YEARS INFORMATION \n");

	for ( curr_year = list_year;
			isSetYear(curr_year);
			curr_year = curr_year->next_year )

	{
		printf("YEAR : %d \n", curr_year->year);
	
	
	}

}
void printName( ListName *list_names )
{


	ListName *curr = NULL;

	printf("NAMES INFORMATION \n");

	for ( curr = list_names;
			isSetName(curr);
			curr = curr->next_name )
	{
		printf("NAME %s --- Length %d\n", curr->name, curr->length_name );
	
	
	}

}
int isSetName( ListName *list_name ) 
{
	return ( list_name != NULL ) ? 1 : 0;

}
int isSetYear( ListYear *list_year )
{
	return ( list_year != NULL ) ? 1 : 0;

}
ListName *initName( void )
{
	return NULL;

}
ListYear *initYear( void )
{
	return NULL;
}

int checkYear( ListYear *list_year, int year )
{

	int res = 0;
	ListYear *curr_year = list_year;

	while( curr_year != NULL && res != 1 )
	{
		if ( curr_year->year == year )
			res = 1;

		curr_year = curr_year->next_year;
	
	}

	return res;
	

}

int checkName( ListName *list_name, char *name ) 
{
	int res = 0;
	ListName *curr_name = list_name;

	while( curr_name != NULL && res != 1 )
	{
		if ( strcmp( curr_name->name, name ) == 0 )
			res = 1;
		curr_name = curr_name->next_name;
	}
	return res;
}
