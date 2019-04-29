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
	float value;		//price per amount
};

class products
{
private:
	std::vector<product> list;
	std::vector<item> inventory;
public:
	//products();
	friend std::istream& operator>>(std::istream& in, products& data);
	friend std::istream& operator>(std::istream& in, products& data);
	friend std::ostream& operator<<(std::ostream& out, const products& data);
	friend std::ostream& operator<(std::ostream& out, const products& data);
	//products get_similar(std::string product_name);
	//~products();
};

