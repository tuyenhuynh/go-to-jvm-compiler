#include "dot.h"
#include <stdio.h>

void printNode(int id, char* label) {
	printf("%d [label = %s]\n", id, label); 
}

void printEdge(int sourceId, int destId) {
	printf("%d -> %d\n", sourceId, destId); 
}

void printEdgeWithDestName(int sourceId, int destId, char*destNodeName) {
	printEdge(sourceId, destId);
	printNode(destId, destNodeName); 
}