#include "products.h"
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <errno.h>
#include "dirent.h"
#include <algorithm>
#include <sstream>

std::string change_unit(std::string data, float* amount_to_buy)
{
	if (!data.compare("kg"))
	{
		*amount_to_buy *= 1000;
		data.assign("g");
	}
	else
		if (!data.compare("l"))
		{
			*amount_to_buy *= 1000;
			data.assign("ml");
		}
	return data;
}

std::istream& operator>>(std::istream& in, products& data)
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

std::istream& operator>(std::istream& in, products& data)
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

std::ostream& operator<<(std::ostream& out, const products& data)
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

