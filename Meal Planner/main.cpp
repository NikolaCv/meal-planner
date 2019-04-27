#include <iostream>
#include <stdlib.h>
#include "meal_planner.h"

int main()
{
	meal_planner meals;

	std::string product_file = "Scraper/database.txt";
	std::string recipes_dir_info = "Recipes";
	//std::string preparation_file_name = "preparation.txt";
	std::string needed_products_file_name = "needed_products.txt";
	std::string inventory_file = "Inventory/inventory.txt";

	//za pocetak uzimamo da pravimo 1 jelo
	//pa ce za svako jelo gledati inventory i nece ga menjati
	//posle cemo to promeniti
	meals.get_products(product_file);
	
	meals.get_inventory_items(inventory_file);

	meals.get_recipes(recipes_dir_info, needed_products_file_name);
	
	//meals.print_products();
	meals.calculate_recipe_prices();
	//meals.print_inventory();

	meals.print_recipes();

	std::cout << std::endl;
	system("pause");
	return 0;
}