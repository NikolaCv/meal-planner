#pragma once
#include <iostream>
#include <vector>
#include "structures.h"
#include "products.h"

class recipes
{
private:
	std::vector<recipe> list;
public:
	friend void operator>>(std::string dir_name, recipes& data);
	void calculate_recipe_prices(products p);
	friend std::ostream& operator<<(std::ostream& out, const recipes& data);
	friend std::ostream& operator<(std::ostream& out, const recipes& data);
};