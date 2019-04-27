#include "meal_planner.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>
#include "dirent.h"
#include <algorithm>
#include <sstream>
#include <cctype>

#ifdef _WIN32
#include <direct.h>

#elif __linux__
#include <unistd.h>
#endif

bool better_value(const product& a, const product& b)
{
	if (a.price_per_amount > b.price_per_amount) return true;
	return false;
}

bool smaller_r(const recipe& a, const recipe& b)
{
	if (a.price_per_meal < b.price_per_meal) return true;
	return false;
}

std::string change_unit(std::string data, float* amount_to_buy)
{
	if (!data.compare("kg"))
	{
		*amount_to_buy *= 1000;
		data.assign("g");
	}
	else
		if (!data.compare("l"))
		{
			*amount_to_buy *= 1000;
			data.assign("ml");
		}
	return data;
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

	while (std::getline(file, temp.name, '\t'))
	{
		std::getline(file, data, '\t');
		temp.amount = std::stof(data);
		
		std::getline(file, temp.unit, '\t');
		
		temp.unit = change_unit(temp.unit,&temp.amount);

		std::getline(file, data, '\t');
		temp.price = std::stof(data);
		
		std::getline(file, temp.shop);

		temp.price_per_amount = temp.amount / temp.price;

		products.push_back(temp);
	}

	file.close();

#ifdef _WIN32
	_chdir("Meal Planner");
#elif __linux__
	chdir("Meal Planner");
#endif
}

/*
u racunanje cene ukljuci inventory za svako jelo posebno bez menjanja inventorija
posle toga uz menjanje inventorija, ali kako tacno, sta je cilj
*/

//add if to print error if database is writter wrong

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

		recipe temp;

		file.open(products_file_name, std::ios::in);
		std::getline(file, data);

		temp.name = entry->d_name;
		temp.num_of_meals = std::stof(data);
		temp.price = -1;
		temp.price_per_meal = -1;

		item temp_item;

		while (std::getline(file, temp_item.name, ','))			//product name
		{
			std::getline(file, data, ',');
			temp_item.amount = std::stof(data);

			std::getline(file, temp_item.unit);

			temp_item.unit = change_unit(temp_item.unit, &temp_item.amount);

			temp.items.push_back(temp_item);
		}
		
		recipes.push_back(temp);

		file.close();

#ifdef _WIN32
		_chdir("..");
#elif __linux__
		chdir("..");
#endif
	}
}

void meal_planner::get_inventory_items(std::string file_name)
{
#ifdef _WIN32
	_chdir("..");
#elif __linux__
	chdir("..");
#endif

	std::fstream file;
	file.open(file_name, std::ios::in);

	item temp;
	std::string data;

	while (std::getline(file, temp.name, ','))
	{
		std::getline(file, data, ',');
		temp.amount = std::stof(data);

		std::getline(file, temp.unit);

		temp.unit = change_unit(temp.unit,&temp.amount);

		inventory.push_back(temp);
	}

	file.close();

#ifdef _WIN32
	_chdir("Meal Planner");
#elif __linux__
	chdir("Meal Planner");
#endif
}



//need new algorithm

void meal_planner::calculate_recipe_prices()
{
	for (int i = 0; i < recipes.size(); ++i)	//for all recipes
	{
		for (int j = 0; j < recipes[i].items.size(); ++j)	//for all items in that recipe
		{
			std::vector<std::string> product_name;
			std::stringstream stream(recipes[i].items[j].name);
			std::string data;

			//breaking name of the item from current recipe on words
			while (std::getline(stream, data, ' '))
				product_name.push_back(data);

			std::vector<product> list;

			//adding all products that have at least all words 
			//from needed product_name into list
			for (int i = 0; i < products.size(); ++i)
			{
				bool t = true;
				for (int j = 0; j < product_name.size(); ++j)
					if (!strstr(products[i].name.c_str(), product_name[j].c_str()))
					{
						t = false;
						break;
					}

				if (t)
					list.push_back(products[i]);
			}

			std::sort(list.begin(), list.end(), better_value);
			float amount_to_buy = recipes[i].items[j].amount;

			/*for (int i = 0; i < list.size(); ++i)
				std::cout << list[i].name << "\t" << list[i].amount << list[i].unit << "\t"
				<< list[i].price << "\t" << list[i].shop << std::endl;
				*/
			int index = 0;
			while (index < list.size() && amount_to_buy > 0)
			{
				int number = 1;
				bool t = false;
				if (list[index].amount < amount_to_buy)
				{
					t = true;
					while (number * list[index].amount <= amount_to_buy)
						number++;
					number--;
				}
				else
					t = false;

				if (t)
				{
					//std::cout << list[index].name << "----\t" << list[index].price << std::endl;
					amount_to_buy -= number * list[index].amount;
					recipes[i].price += number * list[index].price;
				}
				index++;
			}

			if (amount_to_buy > 0 && index > 0)
				recipes[i].price += list[index - 1].price;
		}
	}
		
}

void meal_planner::print_products()
{
	std::cout << "Products" << std::endl;
	std::cout << "Name" << "\t" << "Amount" << "\t" << "Unit" << "\t" << "Price" << "\t" << "Shop" << std::endl;
	for (int i = 0; i < products.size(); ++i)
		std::cout << products[i].name << "\t" << products[i].amount << products[i].unit << "\t"
				  << products[i].price << "\t" << products[i].shop << std::endl;
}

void meal_planner::print_recipes()
{
	std::cout << "Recipes" << std::endl << std::endl;

	for (int i = 0; i < recipes.size(); ++i)
	{
		std::cout << recipes[i].name << std::endl;
		std::cout << "\t" << "Price: " << recipes[i].price << "\t" << "Meals: " << recipes[i].num_of_meals << "\t"
				  << "Price per meal: " << recipes[i].price << "\t" << std::endl << std::endl;

		for(int j = 0; j < recipes[i].items.size(); ++j)
			std::cout << recipes[i].items[j].name << "\t" << recipes[i].items[j].amount << recipes[i].items[j].unit << std::endl;

		std::cout << "-----------------------------" << std::endl << std::endl;
	}
		
}

void meal_planner::print_inventory()
{
	std::cout << "Inventory" << std::endl;
	std::cout << "Name" << "\t" << "Amount" << "\t" << "Unit" << std::endl;
	for (int i = 0; i < inventory.size(); ++i)
		std::cout << inventory[i].name << "\t" << inventory[i].amount << "\t" << inventory[i].unit << std::endl;
}

