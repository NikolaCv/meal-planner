#include <iostream>
#include "structures.h"

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

template <class T>
bool increasing_by_value(T a, T b)
{
	if (a.value < b.value) return true;
	return false;
}