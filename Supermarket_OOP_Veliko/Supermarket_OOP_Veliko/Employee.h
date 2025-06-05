#pragma once
#include "Constants.h"
#include <fstream>
#include <iostream>
class Employee
{
protected:
	int id;
	char* firstName;
	char* familyName;
	char* telephoneNumber = new char[DEFAULT_STRING_LENGTH];
	short age;
	char* password;
	
	void copyFrom(Employee& const emp);
	void free();
public:
	Employee();
	Employee(Employee& const emp);
	Employee(int id, char* firstName, char* familyName, char* telephoneNumber, short age, char* password);
	~Employee();
};
int getLatestWorkerId();
