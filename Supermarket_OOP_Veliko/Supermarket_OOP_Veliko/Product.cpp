#pragma once
#include "Product.h"

using namespace std;

void Product::copyFrom(Product& prod)
{
	int i = 0;
	while (prod.name[i] != '\0') {
		i++;
	}
	name = new char[i];
	for (int k = 0; k < i; k++) {
		name[i] = prod.name[i];
	}
	
	categoryId = prod.categoryId;

	price = prod.price;
}

void Product::free()
{
	delete[] name;
}

Product::Product()
{
	price = 0;
	categoryId = -1;
	name = new char[DEFAULT_STRING_LENGTH];
}

Product::Product(Product& const prod)
{
	copyFrom(prod);
}

Product::Product(int _id, char* const _name, int _cat, double const _price)
{
	id = _id;
	int k = 0;
	while (_name[k] != '\0') {
		k++;
	}
	name = new char[k];
	for (int i = 0; i < k; i++) {
		name[i] = _name[i];
	}

	categoryId = _cat;

	price = _price;
}

Product::~Product() {
	free();
}

int Product::getId()
{
	return id;
}

MyString Product::getName() {
	return name;
}

int Product::getCatId() {
	return categoryId;
}

double Product::getPrice() {
	return price;
}

int productExists(char* name)
{
	ifstream file(PRODUCTS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << PRODUCTS_FILE_NAME << "' failed to open." << endl;
		return -1;
	}
	int latestId = 0;
	file >> latestId;
	int count = 0;
	file >> count;
	for (int i = 0; i < count; i++) {
		MyString input = "";
		file >> input.data;
		MyString* words = stringToArray(input, ':');
		if (words[0].compare(PRODUCTS_WORD_NEW)) {
			if (words[2].compare(name)) {
				return 1;
			}
		} else {
			if (words[1].compare(name)) {
				return 1;
			}
		}
	}
	file.close();
	return 0;
}
