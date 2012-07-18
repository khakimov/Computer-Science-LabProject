#include "link_list.h"

int main(void )
{
	ListName *names = NULL;
	ListYear *years  = NULL;
	int choice = 0;
	int year;
	char name[512];

	readFile(&years, &names);

	do
	{
		printf("Do you want to find a name or a year?\n1) Year   2)Name  0) Exit\nChoice : ");
		scanf("%d", &choice);
		switch( choice )
		{
		case 1: 
			printf("Insert the year that you will look for  : ");
			scanf("%d", &year);
			printf(" The year %d %s\n", year, ( checkYear(years, year) == 1 ) ? "was found!" : "was not found!");
			printYear(years);
		break;

		case 2:
			printf("Insert the name that you will look for : ");
			scanf("%s", name);
			printf(" The name %s %s\n", name, ( checkName(names, name) == 1 ) ? "was found!" : "was not found!");
		break;

		case 0:
			printf("You are exiting...\n");
		break;

		
		}
	
	}while ( choice != 0 );


	getchar();
	return EXIT_SUCCESS;

}