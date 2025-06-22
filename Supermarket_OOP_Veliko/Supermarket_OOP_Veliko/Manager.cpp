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

void Manager::listPending() const
{
	ifstream cashiers(CASHIERS_FILE_NAME);
	if (!cashiers.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
		return;
	}
	int length = 0;
	cashiers >> length;
	for (int i = 0; i < length; i++) {
		MyString input;
		cashiers >> input.data;
		int strlen = 0;
		while (input.data[strlen] != '\0') {
			strlen++;
		}
		if (input.data[strlen - 1] == '0') {
			int j = 0;
			int b = 0;
			int l = 0;
			MyString* words = new MyString [9];
			for (int k = 0; k < length; k++)
			{
				if (input.data[k] == ':') {
					j = 0;
					b++;
					words[b].data[l + 1] = '\0';
					l = 0;
				}
				words[b].data[l] = input.data[k];
			}
			int s = 0;
			int id = 0;
			while (words[0].data[s] != '\0')
				id = id * 10 + words[0].data[s];
			s = 0;
			int age = 0;
			while (words[4].data[s] != '\0')
				age = age * 10 + words[4].data[s];
			s = 0;
			int transactions = 0;
			while (words[6].data[s] != '\0')
				transactions = transactions * 10 + words[6].data[s];
			s = 0;
			int warningPoints = 0;
			while (words[7].data[s] != '\0')
				warningPoints = warningPoints * 10 + words[7].data[s];
			cout << "ID: " << id << endl;
			cout << "First Name: " << words[1].data << endl;
			cout << "Family Name: " << words[2].data << endl;
			cout << "Telephone Number: " << words[3].data << endl;
			cout << "Age: " << age << endl;
			cout << "Transactions: " << transactions << endl;
			cout << "Warning Points: " << warningPoints << endl;
			cout << "Approved: " << words[8].data[0] - '0' << endl << endl;
			delete[] words;
		}
	}
}

void Manager::approve(int const cashierId, char* specialCode) const
{
	int SPECIAL_CODE_LENGTH = 7;
	char* sc = new char[SPECIAL_CODE_LENGTH + 1];
	ifstream specialCodeFile("");
	if (!specialCodeFile.is_open()) {
		cout << "Could not check if the code matches";
		return;
	}
	specialCodeFile >> sc;
	for (int i = 0; i < SPECIAL_CODE_LENGTH; i++)
	{
		if (sc[i] != specialCode[i])
		{
			cout << "Special code is incorrect.";
			return;
		}
	}
	delete[] sc;
	specialCodeFile.close();

	ifstream file(CASHIERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
		return;
	}
	int length;
	int trueId = 0;
	MyString data;
	int line = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		MyString input;
		file >> input.data;
		int tempId = 0;
		MyString* words = stringToArray(input, ':');
		tryConvertToInt(words[0].data, tempId);
		if (tempId == cashierId) {
			trueId = tempId;
			line = i;
			data = input;
			break;
		}
	}
	file.close();
	int i = 0;
	while (data.data[i] != '\0') {
		if (data.data[i + 1] == '\0')
		{
			data.data[i] = '1';
		}
	}
	replaceLineInFile(CASHIERS_FILE_NAME, line, data.data);
}

void Manager::decline(int const cashierId, char* specialCode) const
{
	int SPECIAL_CODE_LENGTH = 7;
	char* sc = new char[SPECIAL_CODE_LENGTH + 1];
	ifstream specialCodeFile("");
	if (!specialCodeFile.is_open()) {
		cout << "Could not check if the code matches";
		return;
	}
	specialCodeFile >> sc;
	for (int i = 0; i < SPECIAL_CODE_LENGTH; i++)
	{
		if (sc[i] != specialCode[i])
		{
			cout << "Special code is incorrect.";
			return;
		}
	}
	delete[] sc;
	specialCodeFile.close();

	ifstream file(CASHIERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
		return;
	}
	int length;
	int trueId = 0;
	int line = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		file >> input.data;
		int tempId = 0;
		MyString* words = stringToArray(input, ':');
		tryConvertToInt(words[0].data, tempId);
		if (tempId == cashierId) {
			trueId = tempId;
			line = i;
			break;
		}
	}
	deleteLineFromFile(CASHIERS_FILE_NAME, line + 1);
	file.close();
}

void Manager::listWarnedCashiers(int const _warningPoints) const
{
	MyString input = "";

	ifstream file(CASHIERS_FILE_NAME);
	if (file.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
		return;
	}
	int number;
	file >> number;
	for (int i = 0; i < number; i++)
	{
		file >> input.data;
		int length = 0;
		while (input.data[length] != '\0') {
			length++;
		}
		int j = 0;
		int b = 0;
		int l = 0;
		MyString* words = new MyString[9];
		for (int k = 0; k < length; k++)
		{
			if (input.data[k] == ':') {
				j = 0;
				b++;
				words[b].data[l + 1] = '\0';
				l = 0;
			}
			words[b].data[l] = input.data[k];
		}
		int s = 0;
		int id = 0;
		while (words[0].data[s] != '\0')
			id = id * 10 + words[0].data[s];
		s = 0;
		int age = 0;
		while (words[4].data[s] != '\0')
			age = age * 10 + words[4].data[s];
		s = 0;
		int transactions = 0;
		while (words[6].data[s] != '\0')
			transactions = transactions * 10 + words[6].data[s];
		s = 0;
		int warningPoints = 0;
		while (words[7].data[s] != '\0')
			warningPoints = warningPoints * 10 + words[7].data[s];
		if (warningPoints < _warningPoints)
			continue;
		cout << "ID: " << id << endl;
		cout << "First Name: " << words[1].data << endl;
		cout << "Family Name: " << words[2].data << endl;
		cout << "Telephone Number: " << words[3].data << endl;
		cout << "Age: " << age << endl;
		cout << "Transactions: " << transactions << endl;
		cout << "Warning Points: " << warningPoints << endl;
		cout << "Approved: " << words[8].data[0] - '0' << endl << endl;
		delete[] words;
	}
	file.close();
}

void Manager::warnCashier(int const cashierId, int points) const
{

	ifstream file(CASHIERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
		return;
	}
	int length;
	int trueId = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		MyString input;
		file >> input.data;
		int tempId = 0;
		int k = 0;
		while (input.data[k] != ':') {
			tempId = tempId * 10 + input.data[k] - '0';
		}
		if (tempId == cashierId) {
			trueId = tempId;
			MyString newLine;
			int z = 0;
			int b = 0;
			int colons = 0;
			while (input.data[z] != '\0') {
				if (input.data[z] == ':')
				{
					colons++;
				}
				if (colons == 7) {
					int existingPoints = 0;
					while (input.data[z] != ':') {
						existingPoints = existingPoints * 10 + input.data[b] - '0';
						z++;
					}
					existingPoints += points;
					int temp = existingPoints;
					int l = 0;
					while (temp != 0) {
						temp /= 10;
						l++;
					}
					for (int r = 0; r < l; r++) {
						int divisor = 1;
						for (int a = 0; 0 < l; a++)
							divisor *= 10;
						newLine.data[b] = '0' + existingPoints / divisor;
						existingPoints %= divisor;
						divisor /= 10;
						b++;
					}
				}
				else {
					newLine.data[b] = input.data[z];
					z++;
				}

				b++;
			}
			replaceLineInFile(CASHIERS_FILE_NAME, i + 1, newLine.data);
			break;
		}
	}
	file.close();
}

void Manager::promoteCashier(int const cashierId, char* specialCode)
{
	int SPECIAL_CODE_LENGTH = 7;
	char* sc = new char[SPECIAL_CODE_LENGTH + 1];
	ifstream specialCodeFile("");
	if (!specialCodeFile.is_open()) {
		cout << "Could not check if the code matches";
		return;
	}
	specialCodeFile >> sc;
	for (int i = 0; i < SPECIAL_CODE_LENGTH; i++)
	{
		if (sc[i] != specialCode[i])
		{
			cout << "Special code is incorrect.";
			return;
		}
	}
	delete[] sc;
	specialCodeFile.close();

	ifstream file(CASHIERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
		return;
	}
	int length;
	int line = 0;
	int trueId = 0;
	MyString data;
	file >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		file >> input.data;
		int tempId = 0;
		MyString* words = stringToArray(input, ':');
		tryConvertToInt(words[0].data, tempId);
		if (tempId == cashierId) {
			trueId = tempId;
			line = i;
			data = input;
			break;
		}
	}
	file.close();
	deleteLineFromFile(CASHIERS_FILE_NAME, line + 1);
	ofstream manFile(MANAGERS_FILE_NAME);
	manFile << data.data << endl;
	manFile.close();
}

void Manager::fireCashier(int const cashierId, char* specialCode) const
{
	int SPECIAL_CODE_LENGTH = 7;
	char* sc = new char[SPECIAL_CODE_LENGTH + 1];
	ifstream specialCodeFile("");
	if (!specialCodeFile.is_open()) {
		cout << "Could not check if the code matches";
		return;
	}
	specialCodeFile >> sc;
	for (int i = 0; i < SPECIAL_CODE_LENGTH; i++)
	{
		if (sc[i] != specialCode[i])
		{
			cout << "Special code is incorrect.";
			return;
		}
	}
	delete[] sc;
	specialCodeFile.close();
	ifstream file(CASHIERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
		return;
	}
	int length;
	int trueId = 0;
	MyString data;
	int line = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		file >> input.data;
		int tempId = 0;
		MyString* words = stringToArray(input, ':');
		tryConvertToInt(words[0].data, tempId);
		if (tempId == cashierId) {
			trueId = tempId;
			line = i;
			break;
		}
	}

	//Reduce the number length in the file
	length--;
	int lengthI = 0;
	int temp = length;
	int divisor = 1;
	while (temp != 0) {
		lengthI++;
		length /= 10;
		divisor *= 10;
	}
	char* lengthChar = new char[lengthI];

	for (int i = 0; i < lengthI; i++)
	{
		lengthChar[i] = length / divisor;
		length %= divisor;
		divisor / 10;
	}

	deleteLineFromFile(CASHIERS_FILE_NAME, line + 1);
	replaceLineInFile(CASHIERS_FILE_NAME, 0, lengthChar);
}

//Returns -1 if file cannot be opened, 0 if it does not exist and 1 if it does


void Manager::addCategory(char* categoryName, char* categoryDescription) const
{
	if (categoryExists(categoryName) == -1) {
		return;
	}
	else if (categoryExists(categoryName) == 1) {
		cout << "Category " << categoryName << " already exists!";
		return;
	}
	ifstream cats(CATEGORIES_FILE_NAME);
	if (!cats.is_open()) {
		cout << "File '" << CATEGORIES_FILE_NAME << "' failed to open." << endl;
		return;
	}
	int i = 0;
	cats >> i;
	cats.close();

	ofstream ofCats(CATEGORIES_FILE_NAME);
	if (!ofCats.is_open()) {
		cout << "File '" << CATEGORIES_FILE_NAME << "' failed to open." << endl;
		return;
	}
	ofCats << i << ":" << categoryName << ":" << categoryDescription << endl;
}

void Manager::deleteCategory(int categoryId) const
{
	ifstream file(CATEGORIES_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << CATEGORIES_FILE_NAME << "' failed to open." << endl;
		return;
	}
	int length = 0;
	int latestId = 0;
	int line = 0;
	file >> latestId;
	file >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		file >> input.data;
		int tempId = 0;
		MyString* words = stringToArray(input, ':');
		tryConvertToInt(words[0].data, tempId);
		if (tempId == categoryId) {
			line = i;
			break;
		}
	}
	file.close();

	//Reduce the number length in the file
	length--;
	int lengthI = 0;
	int temp = length;
	int divisor = 1;
	while (temp != 0) {
		lengthI++;
		length /= 10;
		divisor *= 10;
	}
	char* lengthChar = new char[lengthI];

	for (int i = 0; i < lengthI; i++)
	{
		lengthChar[i] = length / divisor;
		length %= divisor;
		divisor / 10;
	}

	deleteLineFromFile(CATEGORIES_FILE_NAME, line + 1);
	replaceLineInFile(CATEGORIES_FILE_NAME, 1, lengthChar);
}

void Manager::addProduct(int const productType)
{
	int k = 0;
	switch (productType) {
	case 0: k = 0; break;
	case 1: k = 1; break;
	default: cout << "Unsupported product type"; return;
	}

}

void Manager::deleteProduct(int const productId)
{
}

void Manager::loadProducts(char* fileName)
{
}

void Manager::loadGiftCards(char* fileName)
{
}

Manager& Manager::operator=(Manager& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

int Manager::getId() {
	return id;
}

MyString Manager::getFirstName() {
	return firstName;
}

MyString Manager::getLastName() {
	return familyName;
}

MyString Manager::getTelephone() {
	return telephoneNumber;
}

short Manager::getAge() {
	return age;
}

MyString Manager::getPassword() {
	return password;
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