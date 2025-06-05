#pragma once
#include "ProductByUnit.h"

void ProductByUnit::free()
{
	Product::free();
}

void ProductByUnit::copyFrom(ProductByUnit& prod)
{
	count = prod.count;
}

ProductByUnit::ProductByUnit() : Product()
{
	count = 0;
}

ProductByUnit::ProductByUnit(ProductByUnit& prod) : Product(prod)
{
	copyFrom(prod);
}

ProductByUnit::ProductByUnit(char* _name, char* _cat, double _price, int _count) : Product(_name, _cat, _price)
{
	count = _count;
}

ProductByUnit::~ProductByUnit()
{
	free();
}
