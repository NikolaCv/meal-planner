#include <iostream>
#include <string>
#include <stdlib.h>
#include "products.h"
#include <fstream>

int main()
{
	//meal_planner meals;

	std::string products_file = "../Scraper/database.txt";
	std::string recipes_dir = "Recipes";
	std::string needed_products_file = "needed_products.txt";
	std::string inventory_file = "../Inventory/inventory.txt";
	std::string recipes_printing_dir = "../dump/recipes.txt";

	/*meals.get_products(products_file);
	
	meals.get_inventory_items(inventory_file);

	meals.get_recipes(recipes_dir, needed_products_file);
	
	//meals.print_products();
	meals.calculate_recipe_prices();
	//meals.print_inventory();
	meals.print_recipes();
	//meals.print_recipes_to_file(recipes_printing_dir);
	
	std::ofstream file;
	file.open(recipes_printing_dir);

	file << meals;
	*/

	products product_list;
	std::fstream file(products_file, std::ios::in);

	file >> product_list;
	file.close();

	file.open(inventory_file, std::ios::in);
	file > product_list;

	std::cout << product_list;

	std::cout << std::endl;
	system("pause");
	return 0;
}