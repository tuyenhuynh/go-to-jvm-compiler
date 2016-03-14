#include <stdio.h>
#include "scanner.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Program takes only one argument (path to source code file)\n");
		return 1;
	}

	yyin = fopen(argv[1], "r");
	
	printf("Scanning file %s ...\n\n", argv[1]);
	
	yyparse();

	fclose(yyin);

	printf("\nScanning is over");
	
	return 0;
}