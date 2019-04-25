#include <iostream>
#include <stdlib.h>
#include "meal_planner.h"




int main()
{
	meal_planner meals;

	std::string product_file_info = "Products/input.txt";

	meals.get_products(product_file_info);

	meals.print_products();

	std::cout << std::endl;
	system("pause");
	return 0;
}