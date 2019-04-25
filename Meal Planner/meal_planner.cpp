#include "meal_planner.h"
#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>
#include "dirent.h"
#include <direct.h>
#include <algorithm>

void meal_planner::get_products(std::string file_name)
{
	std::fstream file;
	file.open(file_name, std::ios::in);

	std::string data;

	product temp;

	while (std::getline(file, temp.name, ','))
	{
		std::getline(file, data, ',');
		temp.amount = std::stoi(data);

		std::getline(file, temp.unit, ',');

		std::getline(file, data, ',');
		temp.price = std::stof(data);

		std::getline(file, temp.shop);

		products.push_back(temp);
	}

	file.close();
}

void meal_planner::get_recipes(std::string dir_name, std::string products_file_name)
{
	DIR *root = opendir(dir_name.c_str());
	dirent *entry;

	entry = readdir(root);
	entry = readdir(root);

	recipe temp;
	std::fstream file;
	std::string data = products[1].name;

	_chdir(dir_name.c_str());

	while ((entry = readdir(root)) != NULL)
	{
		_chdir(entry->d_name);

		file.open(products_file_name, std::ios::in);
		std::getline(file, data);

		temp.name = entry->d_name;
		temp.num_of_meals = std::stof(data);
		temp.price = 0;

		while (std::getline(file, data, ','))			//mleko,100			--- bez merne jedinice za sada
		{
			std::vector<product>::iterator it;
			it = std::find_if(products.begin(), products.end(), [&p_name = data](const product& p) -> bool { return p.name == p_name; });

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

		recipes.push_back(temp);

		file.close();
		_chdir("..");
	}
	
}

void meal_planner::print_products()
{
	for (int i = 0; i < products.size(); ++i)
		std::cout << products[i].name << "\t" << products[i].amount << "\t" << products[i].unit << "\t" << products[i].price << "\t" << products[i].shop << std::endl;
}

void meal_planner::print_recipes()
{
	for (int i = 0; i < recipes.size(); ++i)
		std::cout << recipes[i].name << "\t" << recipes[i].price << "\t" << recipes[i].num_of_meals << std::endl;
}
