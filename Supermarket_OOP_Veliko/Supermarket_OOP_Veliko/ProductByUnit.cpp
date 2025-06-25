#pragma once
#include "ProductByUnit.h"

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

ProductByUnit::ProductByUnit(int id, char* _name, int _cat, double _price, int _count) : Product(id, _name, _cat, _price)
{
	count = _count;
}

MyString ProductByUnit::getType()
{
	return type;
}

int ProductByUnit::getCount()
{
	return count;
}

double ProductByUnit::getWeight()
{
	return 0;
}
