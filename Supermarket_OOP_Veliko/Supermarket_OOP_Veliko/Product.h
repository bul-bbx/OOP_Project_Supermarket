#pragma once
#include "MyString.h"
#include "Category.h"
#include "Constants.h"
#include <fstream>
using namespace std;
class Product
{
private:
	int id;
	char* name;
	int categoryId;
	double price;
	void copyFrom(Product& prod);
	void free();
public:
	Product();
	Product(Product& const prod);
	Product(int id, char* _name, int _cat, double _price);
	~Product();

	int getId();
	virtual MyString getType() = 0;
	MyString getName();
	int getCatId();
	double getPrice();
	virtual int getCount() = 0;
	virtual double getWeight() = 0;
};
int productExists(char* name);

