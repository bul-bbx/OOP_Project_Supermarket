#pragma once
#include "Category.h"

using namespace std;

void Category::copyFrom(Category& const category)
{
	this->id = category.id;
	int length = 0;
	while (category.name[length] != '\0') {
		length++;
	}
	this->name = new char[length + 1];
	for (int i = 0; i < length; i++) {
		this->name[i] = category.name[i];
	}
	length = 0;
	while (category.description[length] != '\0') {
		length++;
	}
	this->description = new char[length + 1];
	for (int i = 0; i < length; i++) {
		this->description[i] = category.description[i];
	}
}

void Category::free()
{
	delete[] name;
	delete[] description;
}

Category::Category()
{
	name = new char[DEFAULT_STRING_LENGTH];
	description = new char[DEFAULT_STRING_LENGTH];
}

Category::Category(Category& const cat) {
	copyFrom(cat);
}

Category::Category(int _id, char* _name, char* _description)
{
	id = _id;
	int length = 0;
	while (_name[length] != '\0') {
		length++;
	}
	name = new char[length];
	for (int i = 0; i < length; i++) {
		name[i] = _name[i];
	}
}

Category::~Category()
{
	free();
}

int categoryExists(char* name)
{
	bool success = 0;
	ifstream file(CATEGORIES_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << CATEGORIES_FILE_NAME << "' failed to open." << endl;
		return -1;
	}
	int length = 0;
	int latestId = 0;
	int line = 0;
	file >> latestId;
	file >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		file >> input.data;
		MyString* words = stringToArray(input, ':');
		if (words[1].compare(name)) {
			return 1;
		}
	}
	file.close();
	return true;
}