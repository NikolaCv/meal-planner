#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define recipe_name_len 100
#define max_line_len 250
#define ingredient_name_len 40
#define ingredients_file "needed_products.txt"
#define preparation_file "preparation.txt"


int main()
{
	// Set default directories
	char rootdir[4]="../";
	char recipesdir[20]="../Recipes/";
	char databasedir[20]="../Scraper/";

	char newdir[50];
	strcpy(newdir,recipesdir);

	char name[recipe_name_len];
	printf("New recipe:");
	scanf("%s",name);

	// Create a new directory for the recipe
	strcat(newdir,name);
	mkdir(newdir,0744);

	// Change working directory to the new one
	chdir(newdir);

	FILE *ingredients=fopen(ingredients_file,"w+");

	// Meal size
	int size;
	printf("Meal size:");
	scanf("%d",&size);
	fprintf(ingredients,"%d\n",size);

	// Ingredients
	char ingr_name[ingredient_name_len];
	char unit[4];
	int amount;
	printf("Ingredients [NAME,AMOUNT,UNIT]:\n");
	while(scanf("%s,%d,%s\n",ingr_name,&amount,unit)!=EOF){
		fprintf(ingredients,"%s,%d,%s\n",ingr_name,amount,unit);
	}
	printf("Instructions:\n");

	fflush(stdin);

	// Recipe instructions
	/* While is not working
	   Program exists prematurely. */
	FILE *preparation=fopen(preparation_file,"w+");
	char line[max_line_len];
	while(scanf("%s\n",line)!=EOF){
		fprintf(preparation,"%s\n",line);
	}
	
	/* Need to add
	file closing here */

	return 0;
}
