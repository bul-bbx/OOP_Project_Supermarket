#pragma once
#include "MyString.h"
#include "Category.h"
#include "Constants.h"
#include <fstream>
using namespace std;
class Product
{
protected:
	char* name;
	char* category;
	double price;
	void copyFrom(Product& prod);
	void free();
public:
	Product();
	Product(Product& const prod);
	Product(char* const _name, char* _cat, double const _price);
	~Product();
};
int productExists(char* name);

