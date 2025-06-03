#include "Manager.h"

using namespace std;

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

Manager::Manager(int _id, char* _firstName, char* _familyName, char* _telephoneNumber, int _age, char* _password) : Employee(_id, _firstName, _familyName, _telephoneNumber, _age, _password)
{
}

Manager::~Manager()
{
	free();
}

void Manager::listPending() const
{
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

	ifstream file("Cashiers.txt");
	if (!file.is_open()) {
		cout << "File 'Cashiers.txt' failed to open." << endl;
		return;
	}
	int length;
	int trueId = 0;
	string data;
	int line = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		string input = "";
		file >> input;
		int tempId = 0;
		int k = 0;
		while (input[k] != ':') {
			tempId = tempId * 10 + input[k] - '0';
		}
		if (tempId == cashierId) {
			trueId = tempId;
			line = i;
			data = input;
			break;
		}
	}
	file.close();
	int i = 0;
	while (data[i] != '\0') {
		if (data[i + 1] == '\0')
		{
			data[i] = '1';
		}
	}
	replaceLineInFile(CASHIERS_FILE_NAME, line, data);
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
		cout << "File 'Cashiers.txt' failed to open." << endl;
		return;
	}
	int length;
	int trueId = 0;
	string data;
	int line = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		string input = "";
		file >> input;
		int tempId = 0;
		int k = 0;
		while (input[k] != ':') {
			tempId = tempId * 10 + input[k] - '0';
		}
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
	string input = "";

	ifstream file(CASHIERS_FILE_NAME);
	if (file.is_open()) {
		int number;
		file >> number;
		for (int i = 0; i < number; i++)
		{
			file >> input;
			int length = 0;
			while (input[length] != '\0') {
				length++;
			}
			int j = 0;
			int b = 0;
			int l = 0;
			char** words = new char* [9];
			for (int k = 0; k < length; k++)
			{
				if (input[k] == ':') {
					j = 0;
					b++;
					words[b][l + 1] = '\0';
					l = 0;
				}
				words[b][l] = input[k];
			}
			int s = 0;
			int id = 0;
			while (words[0][s] != '\0')
				id = id * 10 + words[0][s];
			s = 0;
			int age = 0;
			while (words[4][s] != '\0')
				age = age * 10 + words[4][s];
			s = 0;
			int transactions = 0;
			while (words[6][s] != '\0')
				transactions = transactions * 10 + words[6][s];
			s = 0;
			int warningPoints = 0;
			while (words[7][s] != '\0')
				warningPoints = warningPoints * 10 + words[7][s];
			if (warningPoints < _warningPoints)
				continue;
			cout << "ID: " << id << endl;
			cout << "First Name: " << words[1] << endl;
			cout << "Family Name: " << words[2] << endl;
			cout << "Telephone Number: " << words[3] << endl;
			cout << "Age: " << age << endl;
			cout << "Transactions: " << transactions << endl;
			cout << "Warning Points: " << warningPoints << endl;
			cout << "Approved: " << words[8] - '0' << endl << endl;
			for (int k = 0; k <= b; k++)
			{
				delete[] words[b];
			}
			delete[] words;
		}
	}
	file.close();
}

void Manager::warnCashier(int const cashierId, int points) const
{

	ifstream file(CASHIERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File 'Cashiers.txt' failed to open." << endl;
		return;
	}
	int length;
	int trueId = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		string input = "";
		file >> input;
		int tempId = 0;
		int k = 0;
		while (input[k] != ':') {
			tempId = tempId * 10 + input[k] - '0';
		}
		if (tempId == cashierId) {
			trueId = tempId;
			string newLine;
			int z = 0;
			int b = 0;
			int colons = 0;
			while (input[z] != '\0') {
				if (input[z] == ':')
				{
					colons++;
				}
				if (colons == 7) {
					int existingPoints = 0;
					while (input[z] != ':') {
						existingPoints = existingPoints * 10 + input[b] - '0';
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
						newLine[b] = '0' + existingPoints / divisor;
						existingPoints %= divisor;
						divisor / 10;
						b++;
					}
				}
				else {
					newLine[b] = input[z];
					z++;
				}

				b++;
			}
			replaceLineInFile(CASHIERS_FILE_NAME, i + 1, newLine);
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
		cout << "File 'Cashiers.txt' failed to open." << endl;
		return;
	}
	int length;
	int line = 0;
	int trueId = 0;
	string data;
	file >> length;
	for (int i = 0; i < length; i++) {
		string input = "";
		file >> input;
		int tempId = 0;
		int k = 0;
		while (input[k] != ':') {
			tempId = tempId * 10 + input[k] - '0';
		}
		if (tempId == cashierId) {
			trueId = tempId;
			line = i;
			data = input;
			break;
		}
	}
	file.close();
	deleteLineFromFile(CASHIERS_FILE_NAME, line + 1);
	ofstream manFile("Managers.txt");
	manFile << data << endl;
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
		cout << "File 'Cashiers.txt' failed to open." << endl;
		return;
	}
	int length;
	int trueId = 0;
	string data;
	int line = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		string input = "";
		file >> input;
		int tempId = 0;
		int k = 0;
		while (input[k] != ':') {
			tempId = tempId * 10 + input[k] - '0';
		}
		if (tempId == cashierId) {
			trueId = tempId;
			line = i;
			break;
		}
	}
	deleteLineFromFile(CASHIERS_FILE_NAME, line + 1);
}

void Manager::addCategory(char* categoryName, char* categoryDescription) const
{
	ifstream cats(CATEGORIES_FILE_NAME);
	if (!cats.is_open()) {
		cout << "File 'Categories.txt' failed to open." << endl;
		return;
	}
	int i = 0;
	cats >> i;
	cats.close();

	ofstream ofCats(CATEGORIES_FILE_NAME);
	if (!ofCats.is_open()) {
		cout << "File 'Categories.txt' failed to open." << endl;
		return;
	}
	ofCats << i << ":" << categoryName << ":" << categoryDescription << endl;
}

void Manager::deleteCategory(int categoryId) const
{
	ifstream file(CATEGORIES_FILE_NAME);
	if (!file.is_open()) {
		cout << "File 'Categories.txt' failed to open." << endl;
		return;
	}
	int length = 0;
	int latestId = 0;
	int line = 0;
	file >> latestId;
	file >> length;
	for (int i = 0; i < length; i++) {
		string input = "";
		file >> input;
		int tempId = 0;
		int k = 0;
		while (input[k] != ':') {
			tempId = tempId * 10 + input[k] - '0';
		}
		if (tempId == categoryId) {
			line = i;
			break;
		}
	}
	file.close();
	deleteLineFromFile(CATEGORIES_FILE_NAME, line + 1);
}

void Manager::addProduct(int const productType)
{
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