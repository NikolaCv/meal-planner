#pragma once
#include <iostream>
#include <vector>
#include "structures.h"

class recipes
{
private:
	std::vector<recipe> list;
public:
	friend void operator>>(std::string dir_name, recipes& data);
	//void get_recipes(std::string dir_name, std::string products_file_name);
	//void calculate_recipe_prices();
	friend std::ostream& operator<<(std::ostream& out, const recipes& data);
	friend std::ostream& operator<(std::ostream& out, const recipes& data);
};