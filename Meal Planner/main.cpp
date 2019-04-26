#include <iostream>
#include <stdlib.h>
#include "meal_planner.h"

int main()
{
	meal_planner meals;

	std::string product_file = "Scraper/baza.txt";
	std::string recipes_dir_info = "Recipes";
	std::string preparation_file_name = "preparation.txt";
	std::string needed_products_file_name = "needed_products.txt";
	   
	//meals.get_products(product_file);

	meals.get_recipes(recipes_dir_info, needed_products_file_name);

	meals.print_products();

	meals.print_recipes();

	std::cout << std::endl;
	system("pause");
	return 0;
}