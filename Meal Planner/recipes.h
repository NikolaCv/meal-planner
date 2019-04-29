#pragma once
#include <iostream>
#include <vector>

struct item
{
	std::string name;
	float amount;
	std::string unit;
};

struct recipe
{
	std::string name;
	std::vector<item> items;
	float price;
	float num_of_meals;
	float value;		//price per meal
};

class recipes
{
private:
	std::vector<recipe> list;
public:
	friend std::istream& operator>>(std::ostream& out, recipes& data);
	//void get_recipes(std::string dir_name, std::string products_file_name);
	//void calculate_recipe_prices();
	friend std::ostream& operator<<(std::ostream& out, const recipes& data);
	friend std::ostream& operator<(std::ostream& out, const recipes& data);
};