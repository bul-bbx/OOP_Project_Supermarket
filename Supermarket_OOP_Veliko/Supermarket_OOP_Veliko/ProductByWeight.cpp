#pragma once
#include "ProductByWeight.h"

void ProductByWeight::free()
{
	Product::free();
}

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

ProductByWeight::ProductByWeight(char* _name, char* _category, double _price, double _weight) : Product(_name, _category, _price)
{
	weight = _weight;
}

ProductByWeight::~ProductByWeight()
{
	free();
}
