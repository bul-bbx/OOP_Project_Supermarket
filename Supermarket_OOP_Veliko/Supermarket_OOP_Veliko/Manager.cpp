#pragma once
#include "Manager.h"

using namespace std;

char getRandomNumAsChar()
{
	srand(static_cast<unsigned>(time(0)));
	char randomNumber = '0' + rand() % 10;
	return randomNumber;
}

char getRandomLetterUpper()
{
	srand(static_cast<unsigned>(time(0)));
	char randomLetter = 'A' + rand() % 26;
	return randomLetter;
}

char getRandomLetterLower()
{
	srand(static_cast<unsigned>(time(0)));
	char randomLetter = 'a' + rand() % 26;
	return randomLetter;
}

MyString createSpecialKey()
{
	char* key = new char[8];
	key[0] = getRandomNumAsChar();
	key[1] = getRandomLetterUpper();
	key[2] = getRandomLetterUpper();
	key[3] = getRandomNumAsChar();
	key[4] = getRandomNumAsChar();
	key[5] = getRandomNumAsChar();
	key[6] = getRandomLetterLower();
	key[7] = '\0';
	return MyString(key);
}

void Manager::copyFrom(Manager& const man)
{
	Employee::copyFrom(man);
}

void Manager::free()
{
	Employee::free();
}

Manager::Manager() : Employee() {}

Manager::Manager(Manager& man) : Employee(man)
{
	copyFrom(man);
}

Manager::Manager(int _id, char* _firstName, char* _familyName, char* _telephoneNumber, int _age, char* _password) : Employee(_id, _firstName, _familyName, _telephoneNumber, _age, _password) {}

Manager::~Manager()
{
	free();
}

void Manager::warn(int points) {
	return;
}

void Manager::approve() {
	return;
}

Manager& Manager::operator=(Manager& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

MyString Manager::getType() {
	return type;
}

int Manager::getTransactions() {
	return 0;
}

int Manager::getWarningPoints() {
	return 0;
}

bool Manager::isApproved() {
	return 1;
}