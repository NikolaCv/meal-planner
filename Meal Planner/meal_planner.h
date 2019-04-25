#pragma once
#include <iostream>
#include <vector>

struct product
{
	std::string name;
	int amount;
	std::string unit;
	float price;
	std::string shop;
};

struct recipe
{
	std::string name;
	float price;
	float num_of_meals;
};

class meal_planner
{
private:
	std::vector<product> products;
	std::vector<recipe> recipes;
public:
	void get_products(std::string file_name);
	void get_recipes(std::string dir_name, std::string products_file_name);
	void print_products();
	void print_recipes();
};
