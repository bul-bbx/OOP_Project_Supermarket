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
	int getId();
	MyString getFirstName();
	MyString getLastName();
	MyString getTelephone();
	short getAge();
	MyString getPassword();
	virtual MyString getType() = 0;

	virtual void approve() = 0;
	virtual void warn(int points) = 0;
	virtual int getTransactions() = 0;
	virtual int getWarningPoints() = 0;
	virtual bool isApproved() = 0;
};
int getLatestWorkerId();
