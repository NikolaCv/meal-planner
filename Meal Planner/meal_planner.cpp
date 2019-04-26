#include "meal_planner.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>
#include "dirent.h"
#include <algorithm>
#include <sstream>

#ifdef _WIN32
#include <direct.h>

#elif __linux__
#include <unistd.h>
#endif

bool bigger_amount(const product& a, const product& b)
{
	if (a.amount > b.amount) return true;
	return false;
}

bool smaller_r(const recipe& a, const recipe& b)
{
	if (a.price_per_meal < b.price_per_meal) return true;
	return false;
}

product change_unit_p(product temp)
{
	if (temp.unit.compare("kg"))
	{
		temp.amount *= 1000;
		temp.unit.assign("g");
	}
	else
		if (temp.unit.compare("l"))
		{
			temp.amount *= 1000;
			temp.unit.assign("ml");
		}
	return temp;
}

std::string change_unit(std::string data, float* amount_to_buy)
{
	if (data.compare("kg"))
	{
		*amount_to_buy *= 1000;
		data.assign("g");
	}
	else
		if (data.compare("l"))
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

		temp = change_unit_p(temp);

		std::getline(file, data, '\t');
		temp.price = std::stof(data);
		
		std::getline(file, temp.shop);

		products.push_back(temp);
	}

	file.close();

#ifdef _WIN32
	_chdir("Meal Planner");
#elif __linux__
	chdir("Meal Planner");
#endif
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

		while (std::getline(file, data, ','))			//product name
		{
			std::vector<std::string> product_name;
			std::stringstream stream(data);
			
			while (std::getline(stream, data, ' '))
				product_name.push_back(data);

			std::vector<product> list;

			for (int i = 0; i < products.size(); ++i)
			{
				bool t = true;
				for (int j = 0; j < product_name.size(); ++j)
					if(!strstr(products[i].name.c_str(),product_name[j].c_str()))
						t = false;
				if(t)
					list.push_back(products[i]);
			}
			
			std::sort(list.begin(), list.end(), bigger_amount);

			std::getline(file, data, ',');				//amount
			float amount_to_buy = std::stof(data);

			std::getline(file, data);					//unit
			
			data = change_unit(data, &amount_to_buy);
			
			int index = 0;
			while (index < list.size() && amount_to_buy > 0)
			{
				int number = 1;
				bool t = false;
				if (list[index].amount < amount_to_buy)
				{
					t = true;
					while (number * list[index].amount < amount_to_buy)
						number++;
					number--;
				}
				else
					t = false;

				if (t)
				{
					amount_to_buy -= number * list[index].amount;
					temp.price += number * list[index].price;
				}
				index++;
			}

			if (amount_to_buy > 0 && index > 0)
				temp.price += list[index - 1].price;
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

