#include <stdio.h>
#include <stdlib.h>
#define start_size 100
#define max_recipe_len 100

//typedef char[max_recipe_len] recipe_name;

void error()
{
	fprintf(stderr,"-1");
	exit(EXIT_FAILURE);
}

void* expand(void *ptr,size_t prev_size) // Function to realloc
{
	return realloc(ptr,prev_size*2);
}

typedef struct // Recipe Name/Value
{
	char name[max_recipe_len];
	float price;
}recipe_nv;

void by_budget(FILE *input_stream,int budget)
{
	/* Read recipes and prices into database, then perform an algorithm 
	and print a monthly meal plan sticking with the budget.*/
	recipe_nv *database=(recipe_nv*)malloc(start_size*sizeof(recipe_nv));
	FILE *stream=input_stream;
	int prev_size=start_size; // Saving the previous array size for expansion.
	int i=0; // Database index counter, checking for illegal index
	while(fscanf(stream,"%s %f",database[i].name,&database[i++].price)!=EOF){
		if(i==prev_size){
			database=(recipe_nv*)expand(database,prev_size);
			prev_size*=2;		
		}
	}
	for(int j=0;j<i;j++)
		printf("%s %f\n",database[j].name,database[j].price);
	/* --------Not finished-------- */
}

/* -----------Test main function----------- */

int main(int argc, char *argv[])
{
	if(argc != 2) 
		error();
	FILE *in=fopen(argv[1],"r");
	if(in==NULL)
		error();
	by_budget(in,10000);
	return 0;
}
