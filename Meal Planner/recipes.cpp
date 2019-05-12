#include "recipes.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>
#include "dirent.h"
#include <algorithm>
#include <sstream>
#include "structures.h"
#include "products.h"

#ifdef _WIN32
#include <direct.h>
#elif __linux__
#include <unistd.h>
#endif

//add if to print error if database is writter wrong

void operator>>(std::string dir_name, recipes& r)
{
	DIR *root = opendir(dir_name.c_str());
	dirent *entry;

	//reading dir twice for . and ..
	entry = readdir(root);
	entry = readdir(root);

	std::fstream file;
	std::string data;

#ifdef _WIN32
	_chdir(dir_name.c_str());
#elif __linux__
	chdir(dir_name.c_str());
#endif

	//entry is going through folders in Recipes folder
	//names of those folders are names of recipes
	while ((entry = readdir(root)) != NULL)
	{
#ifdef _WIN32
		_chdir(entry->d_name);
#elif __linux__
		chdir(entry->d_name);
#endif

		recipe temp;

		file.open("needed_products.txt", std::ios::in);
		std::getline(file, data);

		temp.name = entry->d_name;
		temp.num_of_meals = std::stof(data);
		temp.price = 0;
		temp.value = -1;

		item temp_item;

		while (std::getline(file, temp_item.name, ','))
		{
			std::getline(file, data, ',');
			temp_item.amount = std::stof(data);

			std::getline(file, temp_item.unit);

			temp_item.unit = change_unit(temp_item.unit, &temp_item.amount);

			temp.items.push_back(temp_item);
		}

		r.list.push_back(temp);

		file.close();

#ifdef _WIN32
		_chdir("..");
#elif __linux__
		chdir("..");
#endif
	}
}


//to do----------------------
//add get_similar_products in products class that will return vector of products that contain name
//it's the code from ++++++++ to +++++++
//recipes is now vector<> list in class recipes
//optimal price for x meals, or days

void recipes::calculate_recipe_prices(products p)
{
	//for all recipes
	for (int i = 0; i < list.size(); ++i)
	{
		//for all items (products) in current recipe
		for (int j = 0; j < list[i].items.size(); ++j)
		{

			std::vector<product> product_list;
			product_list = p.get_similar(list[i].items[j].name);

			float amount_to_buy = list[i].items[j].amount;

			//curr_price is trying to buy without waste
			//best_buy is if we can't buy without waste
			//best_buy is for dynamic programming
			//in 99% we will have waste

			std::vector<int> best_buy;
			int index = 0;
			float curr_price = 0;

			//for all items that match product name
			while (index < product_list.size() && amount_to_buy > 0)
			{
				int number = 1;
				bool t = false;

				if (product_list[index].amount < amount_to_buy)
				{
					t = true;
					while (number * product_list[index].amount <= amount_to_buy)
						number++;

					best_buy.push_back(curr_price + number * product_list[index].price);
					number--;
				}
				else
				{
					t = false;
					best_buy.push_back(curr_price + product_list[index].price);
				}

				//so we don't buy too much (a.k.a. waste of products)
				//but we are counting it in best_buy if we can't buy without waste
				if (t)
				{
					amount_to_buy -= number * product_list[index].amount;
					curr_price += number * product_list[index].price;
				}

				index++;
			}

			//if we can't buy the exact amount, we'll add the best value to curr_price
			if (amount_to_buy > 0 && product_list.size() > 0)
				curr_price += product_list[0].price;

			std::sort(best_buy.begin(), best_buy.end());

			if (best_buy.size() > 0 && curr_price > best_buy[0])
				list[i].price += best_buy[0];
			else
				list[i].price += curr_price;
		}

		list[i].value = list[i].price / list[i].num_of_meals;
	}

	std::sort(list.begin(), list.end(), increasing_by_value<recipe>);
}


std::ostream & operator<<(std::ostream & out, const recipes & data)
{
	std::cout << "Recipes" << std::endl << std::endl;
	
	for (int i = 0; i < data.list.size(); ++i)
	{
		std::cout << data.list[i].name << std::endl;
		std::cout << "\t" << "Price: " << data.list[i].price << "\t" << "Meals: " << data.list[i].num_of_meals << "\t"
			<< "Price per meal: " << data.list[i].value << "\t" << std::endl << std::endl;

		for (int j = 0; j < data.list[i].items.size(); ++j)
			std::cout << data.list[i].items[j].name << "\t" << data.list[i].items[j].amount << data.list[i].items[j].unit << std::endl;

		std::cout << "........................................." << std::endl << std::endl;
	}
	return out;
}

std::ostream & operator<(std::ostream & out, const recipes & data)
{
	out << "Name\tPrice\tMeals\tPrice per meal" << std::endl;

	for (int i = 0; i < data.list.size(); ++i)
	{
		out << data.list[i].name << "\t" << data.list[i].price << "\t" << data.list[i].num_of_meals << "\t"
			<< data.list[i].value << "\t" << std::endl;
	}
	return out;
}