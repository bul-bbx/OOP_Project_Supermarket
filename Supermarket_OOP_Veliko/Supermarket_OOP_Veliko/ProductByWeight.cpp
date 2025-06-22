#pragma once
#include "ProductByWeight.h"

void ProductByWeight::copyFrom(ProductByWeight& prod)
{
	weight = prod.weight;
}

ProductByWeight::ProductByWeight() : Product()
{
	weight = 0;
}

ProductByWeight::ProductByWeight(ProductByWeight& prod) : Product(prod)
{
	copyFrom(prod);
}

ProductByWeight::ProductByWeight(char* _name, int _category, double _price, double _weight) : Product(_name, _category, _price)
{
	weight = _weight;
}

MyString ProductByWeight::getType()
{
	return type;
}

int ProductByWeight::getCount()
{
	return 0;
}

double ProductByWeight::getWeight()
{
	return weight;
}
