#pragma once
#include <iostream>
#include <vector>

struct item
{
	std::string name;
	float amount;
	std::string unit;
};

struct product
{
	std::string name;
	float amount;
	std::string unit;
	float price;
	std::string shop;
	float price_per_amount;
};

struct recipe
{
	std::string name;
	std::vector<item> items;
	float price;
	float num_of_meals;
	float price_per_meal;
};

class meal_planner
{
private:
	std::vector<product> products;
	std::vector<recipe> recipes;
	std::vector<item> inventory;
public:
	void get_products(std::string file_name);
	void get_recipes(std::string dir_name, std::string products_file_name);
	void get_inventory_items(std::string file_name);
	void calculate_recipe_prices();
	void print_products();
	void print_recipes();
	void print_recipes_to_file(std::string file_name);
	void print_inventory();
	void eat_cheap(int days, int people);
	void eat_within_the_budget(int budget);
};