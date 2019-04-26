#include <stdio.h>
#include <stdlib.h>
#define start_size 100

typedef char[100] recipe_name;

void* expand(void *ptr,size_t prevsize) // Function to realloc
{
	return realloc(ptr,prevsize*2);
}

typedef struct recipe_nv // Recipe Name/Value
{
	char name[100];
	float cena;
};

char **by_budget(FILE *input,int budget)
{
	recipe_nv *database=(recipe_nv*)malloc(start_size*sizeof(
}
