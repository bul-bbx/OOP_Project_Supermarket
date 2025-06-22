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
	Employee& operator=(Employee& const other);
	virtual int getId() = 0;
	virtual bool ComparePass(MyString pass);
	virtual MyString getFirstName() = 0;
	virtual MyString getLastName() = 0;
	virtual MyString getTelephone() = 0;
	virtual short getAge() = 0;
	virtual MyString getPassword() = 0;
	virtual MyString getType() = 0;

	virtual int getTransactions() = 0;
	virtual int getWarningPoints() = 0;
	virtual bool isApproved() = 0;
};
int getLatestWorkerId();
