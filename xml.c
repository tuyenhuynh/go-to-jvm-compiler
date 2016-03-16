#include "xml.h"
#include <stdio.h>

void openTag(char* tagName) {
	printf("\n</%s>", tagName);
}

void closeTag(char* tagName) {
	printf("\n</%s>", tagName);
}