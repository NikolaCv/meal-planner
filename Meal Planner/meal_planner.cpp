#include "meal_planner.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>
#include "dirent.h"
#include <algorithm>

#ifdef _WIN32
#include <direct.h>

#elif __linux__
#include <unistd.h>
#endif

/*
bool smaller_p(const product& a, const product& b)
{
	if (a.price_per_meal < b.price_per_meal) return true;
	return false;
}
*/

bool smaller_r(const recipe& a, const recipe& b)
{
	if (a.price_per_meal < b.price_per_meal) return true;
	return false;
}

void meal_planner::get_products(std::string file_name)
{
#ifdef _WIN32
	_chdir("..");
#elif __linux__
	chdir("..");
#endif
	
	std::fstream file;
	file.open(file_name, std::ios::in);
	
	product temp;
	std::string data;

	while (std::getline(file, temp.name, ','))
	{
		std::cout << temp.name;
		std::getline(file, data, ',');
		temp.amount = std::stoi(data);

		std::getline(file, temp.unit, ',');

		std::getline(file, data, ',');
		temp.price = std::stof(data);

		std::getline(file, temp.shop);

		products.push_back(temp);
	}

	//std::sort(products.begin(), products.end(), smaller_p);
	file.close();
}

void meal_planner::get_recipes(std::string dir_name, std::string products_file_name)
{
#ifdef _WIN32
	_chdir("..");
#elif __linux__
	chdir("..");
#endif

	DIR *root = opendir(dir_name.c_str());
	dirent *entry;

	entry = readdir(root);
	entry = readdir(root);

	recipe temp;
	std::fstream file;
	std::string data;

#ifdef _WIN32
	_chdir(dir_name.c_str());
#elif __linux__
	chdir(dir_name.c_str());
#endif

	while ((entry = readdir(root)) != NULL)
	{
#ifdef _WIN32
		_chdir(entry->d_name);
#elif __linux__
		chdir(entry->d_name);
#endif
		file.open(products_file_name, std::ios::in);
		std::getline(file, data);

		temp.name = entry->d_name;
		temp.num_of_meals = std::stof(data);
		temp.price = 0;

		while (std::getline(file, data, ','))			//mleko,100			--- bez merne jedinice za sada 
		{
			std::vector<product>::iterator it;
			it = std::find_if(products.begin(), products.end(), [&p_name = data](const product& p) -> bool { return strstr(p.name.c_str(), p_name.c_str()); });

			std::getline(file, data);

			if (it == products.end())
			{
				temp.price = -1;
				break;
			}
			else
			{
				int ind = std::distance(products.begin(), it);
				int number = 0;

				while (number * products[ind].amount < std::stof(data))
					number++;

				temp.price += number * products[ind].price;
			}
		}

		temp.price_per_meal = temp.price / temp.num_of_meals;
		recipes.push_back(temp);

		file.close();

#ifdef _WIN32
		_chdir("..");
#elif __linux__
		chdir("..");
#endif
	}

	std::sort(recipes.begin(), recipes.end(), smaller_r);
}

void meal_planner::print_products()
{
	std::cout << "Products" << std::endl;
	std::cout << "Name" << "\t" << "Amount" << "\t" << "Unit" << "\t" << "Price" << "\t" << "Shop" << std::endl;
	for (int i = 0; i < products.size(); ++i)
		std::cout << products[i].name << "\t" << products[i].amount << "\t" << products[i].unit << "\t" << products[i].price << "\t" << products[i].shop << std::endl;
}

void meal_planner::print_recipes()
{
	std::cout << "Recipes" << std::endl;
	std::cout << "Name" << "\t" << "Price" << "\t" << "Meals" << "\t" << "Price per meal" << std::endl;
	for (int i = 0; i < recipes.size(); ++i)
		std::cout << recipes[i].name << "\t" << recipes[i].price << "\t" << recipes[i].num_of_meals << "\t" << recipes[i].price_per_meal << std::endl;
}

void meal_planner::eat_cheap(int days, int people)
{
	
}
