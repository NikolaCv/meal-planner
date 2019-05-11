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

struct recipe
{
	std::string name;
	std::vector<item> items;
	float price;
	float num_of_meals;
	float value;		//price per meal
};

std::string change_unit(std::string data, float* amount_to_buy);

template <class T>
bool increasing_by_value(T a, T b);