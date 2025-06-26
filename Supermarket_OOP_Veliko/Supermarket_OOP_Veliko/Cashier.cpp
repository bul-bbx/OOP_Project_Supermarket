#pragma once
#include "Cashier.h"

using namespace std;

void Cashier::copyFrom(Cashier& const cash)
{
	Employee::copyFrom(cash);
	transactions = cash.transactions;
	warningPoints = cash.warningPoints;
	approved = cash.approved;

};

void Cashier::free()
{
	Employee::free();
	transactions = 0;
	warningPoints = 0;
	approved = 0;
};

Cashier::Cashier() : Employee() 
{
	transactions = 0;
	warningPoints = 0;
	approved = false;
};

Cashier::Cashier(Cashier& cash) : Employee() 
{
	copyFrom(cash);
};

Cashier::Cashier(int _id, char* _firstName, char* _familyName, char* _telephoneNumber, int _age, char* _password, int _transactions, int _warningPoints, bool _approved) : Employee(_id, _firstName, _familyName, _telephoneNumber, _age, _password)
{
	transactions = _transactions;
	warningPoints = _warningPoints;
	approved = _approved;
};

Cashier::~Cashier() {
	free();
}

Cashier& Cashier::operator= (Cashier& const other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

void Cashier::approve()
{
	approved = 1;
}

void Cashier::warn(int points)
{
	warningPoints += points;
}

MyString Cashier::getType()
{
	return type;
}
int Cashier::getTransactions()
{
	return transactions;
}
int Cashier::getWarningPoints()
{
	return warningPoints;
}
bool Cashier::isApproved()
{
	return approved;
}
;

