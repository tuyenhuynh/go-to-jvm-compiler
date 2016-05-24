#include <stdio.h>
#include "scanner.h"
#include "parser.h"
#include "print_tree.h"
#include <semantic.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Program should take 3 arguments (path to source code file)\n");
		return 1;
	}

	yyin = fopen(argv[1], "r");
	
	if (yyin != NULL)
	{
		if (!yyparse()) 
		{
			printf("Parsing was successful\n");
			
			bool semanticResult = doSemantic(root);
			if (semanticResult) {
				printf("Semantic checking successful\n");
				printProgram(argv[2]);
				printConstantsTable(); 
			}
			else {
				printf("Semantic checking failed\n");
			}
		}
		else 
		{
			printf("Parsing failed\n");
		}
	}

	else 
	{
		printf("Error opening file!\n");
		return 1;
	}

	fclose(yyin);
	
	return 0;
}