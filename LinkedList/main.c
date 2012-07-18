#include "link_list.h"

int main(void )
{
	ListName *names = NULL;
	ListYear *years  = NULL;

	readFile(years, names);
	printYear( years);
	printName(names);


	getchar();
	return EXIT_SUCCESS;

}