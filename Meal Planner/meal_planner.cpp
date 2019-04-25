#include "meal_planner.h"
#include <iostream>
#include <fstream>
#include <string>

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
}

void meal_planner::get_recipes(std::string file_name)
{
}

void meal_planner::print_products()
{
	for (int i = 0; i < products.size(); ++i)
		std::cout << products[i].name << "\t" << products[i].amount << "\t" << products[i].unit << "\t" << products[i].price << "\t" << products[i].shop << std::endl;
}