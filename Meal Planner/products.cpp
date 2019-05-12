#include "products.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>
#include "dirent.h"
#include <algorithm>
#include <sstream>
#include "structures.h"

std::istream & operator>>(std::istream & in, products & data)
{
	product temp;
	std::string str;

	while (std::getline(in, temp.name, '\t'))
	{
		std::getline(in, str, '\t');
		temp.amount = std::stof(str);

		std::getline(in, temp.unit, '\t');

		temp.unit = change_unit(temp.unit, &temp.amount);

		std::getline(in, str, '\t');
		temp.price = std::stof(str);

		std::getline(in, temp.shop);

		temp.value = temp.price / temp.amount;
		data.list.push_back(temp);
	}
	return in;
}

std::istream & operator>(std::istream & in, products & data)
{
	item temp;
	std::string str;

	while (std::getline(in, temp.name, ','))
	{
		std::getline(in, str, ',');
		temp.amount = std::stof(str);

		std::getline(in, temp.unit);

		temp.unit = change_unit(temp.unit, &temp.amount);
		
		data.inventory.push_back(temp);
	}
	return in;
}

std::ostream & operator<<(std::ostream & out, const products & data)
{
	out << "Products" << std::endl;
	out << "Name" << "\t" << "Amount" << "\t" << "Unit" << "\t" << "Price" << "\t" << "Shop" << std::endl;
	for (int i = 0; i < data.list.size(); ++i)
		std::cout << data.list[i].name << "\t" << data.list[i].amount << data.list[i].unit << "\t"
		<< data.list[i].price << "\t" << data.list[i].shop << std::endl;
	return out;
}

std::ostream & operator<(std::ostream & out, const products & data)
{
	out << "Products" << std::endl;
	out << "Name" << "\t" << "Amount" << "\t" << "Unit" << std::endl;
	for (int i = 0; i < data.list.size(); ++i)
		std::cout << data.inventory[i].name << "\t" << data.inventory[i].amount << data.inventory[i].unit << std::endl;
	return out;
}

std::vector<product> products::get_similar(std::string name)
{
	std::vector<std::string> product_name;
	std::stringstream stream(name);
	std::string data;

	//breaking name of the item (string name) from current recipe on words
	while (std::getline(stream, data, ' '))
		product_name.push_back(data);

	std::vector<product> product_list;

	//adding all products that have at least all words 
	//from needed product_name into product_list
	for (int i = 0; i < list.size(); ++i)
	{
		bool t = true;
		for (int j = 0; j < product_name.size(); ++j)
			if (!strstr(list[i].name.c_str(), product_name[j].c_str()))
			{
				t = false;
				break;
			}

		if (t)
			product_list.push_back(list[i]);
	}
	
	std::sort(product_list.begin(), product_list.end(), increasing_by_value<product>);
	
	return product_list;
}
