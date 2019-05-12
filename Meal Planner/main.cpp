#include <iostream>
#include <string>
#include <stdlib.h>
#include "products.h"
#include "recipes.h"
#include <fstream>

int main()
{
	//meal_planner meals;

	std::string products_file = "../Scraper/database.txt";
	std::string recipes_dir = "../Recipes";
	std::string inventory_file = "../Inventory/inventory.txt";
	std::string recipes_printing_dir = "../dump/recipes.txt";

	products product_list;
	recipes recipe_list;
	std::fstream file(products_file, std::ios::in);
	
	file >> product_list;
	file.close();

	file.open(inventory_file, std::ios::in);
	file > product_list;

	std::cout << product_list;

	std::cout << std::endl;

	recipes_dir >> recipe_list;

	recipe_list.calculate_recipe_prices(product_list);

	std::cout << recipe_list;

	system("pause");
	return 0;
}