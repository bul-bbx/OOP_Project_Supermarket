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
	
	i = 0;
	while (prod.category[i] != '\0') {
		i++;
	}
	category = new char[i];
	for (int k = 0; k < i; k++) {
		category[i] = prod.category[i];
	}

	price = prod.price;
}

void Product::free()
{
	delete[] name;
	delete[] category;
}

Product::Product()
{
	price = 0;
	category = new char[DEFAULT_STRING_LENGTH];
	name = new char[DEFAULT_STRING_LENGTH];
}

Product::Product(Product& const prod)
{
	copyFrom(prod);
}

Product::Product(char* const _name, char* _cat, double const _price)
{
	int k = 0;
	while (_name[k] != '\0') {
		k++;
	}
	name = new char[k];
	for (int i = 0; i < k; i++) {
		name[i] = _name[i];
	}

	k = 0;
	while (_cat[k] != '\0') {
		k++;
	}
	category = new char[k];
	for (int i = 0; i < k; i++) {
		category[i] = _cat[i];
	}

	price = _price;
}

Product::~Product() {
	free();
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
