#pragma once
#include "Employee.h"

using namespace std;

void Employee::copyFrom(Employee& const emp)
{
	//id
	id = emp.id;

	//firstName
	int i = 0;
	while (emp.firstName[i] != '\0') {
		i++;
	}
	firstName = new char[i + 1];
	for (int k = 0; k < i; k++) {
		firstName[k] = emp.firstName[k];
	}

	//familyName
	i = 0;
	while (emp.familyName[i] != '\0') {
		i++;
	}
	familyName = new char[i + 1];
	for (int k = 0; k < i; k++) {
		familyName[k] = emp.familyName[k];
	}

	//telephoneNumber
	i = 0;
	while (emp.telephoneNumber[i] != '\0') {
		i++;
	}
	telephoneNumber = new char[i + 1];
	for (int k = 0; k < i; k++) {
		telephoneNumber[k] = emp.telephoneNumber[k];
	}

	//age
	age = emp.age;

	//password
	i = 0;
	while (emp.password[i] != '\0') {
		i++;
	}
	password = new char[i + 1];
	for (int k = 0; k < i; k++) {
		password[k] = emp.password[k];
	}
};

void Employee::free()
{
	id = -1;
	age = 0;
	delete[] firstName;
	delete[] familyName;
	delete[] telephoneNumber;
	delete[] password;
};

Employee::Employee()
{
	int latestId = getLatestWorkerId();
	if (latestId == -1) {
		return;
	}
	id = latestId + 1;
	firstName = new char[DEFAULT_STRING_LENGTH];
	familyName = new char[DEFAULT_STRING_LENGTH];
	age = 0;
	password = new char[DEFAULT_STRING_LENGTH];
};

Employee::Employee(Employee& const emp)
{
	copyFrom(emp);
};

Employee::Employee(int _id, char* _firstName, char* _familyName, char* _telephoneNumber, short _age, char* _password)
{
	//id
	this->id = id;

	//firstName
	int i = 0;
	while (_firstName[i] != '\0') {
		i++;
	}
	firstName = new char[i + 1];
	for (int k = 0; k < i; k++)
	{
		firstName[k] = _firstName[k];
	}

	//familyName
	i = 0;
	while (_familyName[i] != '\0') {
		i++;
	}
	familyName = new char[i + 1];
	for (int k = 0; k < i; k++)
	{
		familyName[k] = _familyName[k];
	}

	//telephoneNumber
	i = 0;
	while (_telephoneNumber[i] != '\0') {
		i++;
	}
	telephoneNumber = new char[i + 1];
	for (int k = 0; k < i; k++)
	{
		telephoneNumber[k] = _telephoneNumber[k];
	}

	//age
	age = _age;

	//password
	i = 0;
	while (_password[i] != '\0') {
		i++;
	}
	password = new char[i + 1];
	for (int k = 0; k < i; k++)
	{
		password[k] = _password[k];
	}
};

Employee::~Employee()
{
	free();
}

Employee& Employee::operator= (Employee& const other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

int Employee::getId()
{
	return id;
}

bool Employee::ComparePass(MyString pass) {
	return pass.compare(password);
}


//Returns -1 if the file did not open
int getLatestWorkerId() {
	ifstream workers("EmployeeLatestId.txt");
	if (!workers)
	{
		cout << "File 'EmployeeLatestId.txt' did not open." << endl;
		return -1;
	}
	int lId = 0;
	workers >> lId;
	workers.close();
	return lId;
};

