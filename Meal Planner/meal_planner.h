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

class meal_planner
{
private:
	std::vector<product> products;
public:
	void get_products(std::string file_name);
	void get_recipes(std::string file_name);
	void print_products();
};
