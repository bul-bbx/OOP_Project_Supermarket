#pragma once
#include "MyString.h"
#include "Constants.h"
#include <fstream>
#include <iostream>

class Category
{
	int id;
	char* name;
	char* description;
	void copyFrom(Category& const category);
	void free();
public:
	Category();
	Category(Category& const cat);
	Category(int _id, char* _name, char* _description);
	~Category();

	int getId();
	MyString getName();
	MyString getDescription();
};

int categoryExists(char* name);

