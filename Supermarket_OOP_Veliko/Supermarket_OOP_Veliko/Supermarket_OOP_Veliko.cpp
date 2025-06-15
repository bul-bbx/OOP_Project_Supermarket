#pragma once
#include <iostream>
#include <fstream>
#include "Manager.h"
#include "Cashier.h"
#include "Category.h"
#include "Cashier.h"
#include "MyString.h"

using namespace std;

enum Role {
	None = 0,
	Cashier = 1,
	Manager = 2
};
Role role = None;
MyString* currentUserInfo;
Cashier cash;
Manager man;
bool logged = false;

enum Warning {
	Low = 100,
	Medium = 200,
	High = 300
};

bool login(MyString id, MyString password) {
	ifstream fileM(MANAGERS_FILE_NAME);
	if (!fileM.is_open()) {
		cout << "File '" << MANAGERS_FILE_NAME << "' failed to open." << endl;
		return 0;
	}
	int length = 0;
	fileM >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		fileM >> input.data;
		MyString* words = stringToArray(input, ':');
		if (words[0].compare(id.data)) {
			if (words[5].compare(password)) {
				currentUserInfo = words;
				role = Manager;
				return true;
			}
		}
	}
	fileM.close();

	ifstream fileC(CASHIERS_FILE_NAME);
	if (!fileC.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
		return 0;
	}
	length = 0;
	fileC >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		fileC >> input.data;
		MyString* words = stringToArray(input, ':');
		if (words[0].compare(id.data)) {
			if (words[5].compare(password)) {
				currentUserInfo = words;
				role = Cashier;
				return true;
			}
		}

	}
	fileC.close();

	return false;
}

bool isManager() {
	ifstream file(MANAGERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << MANAGERS_FILE_NAME << "' failed to open." << endl;
		return 0;
	}
	int length = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		file >> input.data;
		MyString* words = stringToArray(input, ':');
		if (words[0].compare(currentUserInfo[0])) {
			return true;
		}
		delete[] words;
	}
	file.close();
	return false;
}
bool isCashier() {
	ifstream file(CASHIERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
		return 0;
	}
	int length = 0;
	file >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		file >> input.data;
		MyString* words = stringToArray(input, ':');
		if (words[0].compare(currentUserInfo[0])) {
			return true;
		}
		delete[] words;
	}
	file.close();
	return false;
}

bool registerCashier(char* fisrt_name, char* last_name, char* telephoneNumber, char* age, char* password) {
	ofstream file(MANAGERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << MANAGERS_FILE_NAME << "' failed to open." << endl;
		return 0;
	}
	MyString data = "";
	data.append(fisrt_name);
	data.append(":");
	data.append(last_name);
	data.append(":");
	data.append(age);
	data.append(":");
	data.append(password);
	data.append(":");
	data.append("0");
	data.append(":");
	data.append("0");
	data.append(":");
	data.append("0");

	file << data.data << endl;
	file.close();
}

bool registerManager(char* first_name, char* last_name, char* telephoneNumber, char* age, char* password) {
	ofstream file(MANAGERS_FILE_NAME);
	if (!file.is_open()) {
		cout << "File '" << MANAGERS_FILE_NAME << "' failed to open." << endl;
		return false;
	}
	MyString data = "";
	MyString idChar;
	convertToString(getLatestWorkerId(), idChar);
	data.append(idChar.data);
	data.append(":");
	data.append(first_name);
	data.append(":");
	data.append(last_name);
	data.append(":");
	data.append(age);
	data.append(":");
	data.append(password);
	file << data.data << endl;
	file.close();

	ofstream writer(MANAGERS_FILE_NAME);
	if (!writer.is_open()) {
		cout << "File '" << MANAGERS_FILE_NAME << "' failed to open." << endl;
		return false;
	}
	writer << data.data << endl;
	writer.close();

	MyString specialCodePlace = idChar;
	specialCodePlace.append("_special_code.txt");

	ofstream specialWriter(specialCodePlace.data);
	if (!specialWriter.is_open()) {
		cout << "File '" << specialCodePlace.data << "' failed to open." << endl;
		return false;
	}
	MyString code = createSpecialKey();
	specialWriter << code.data;
	specialWriter.close();
	

	cout << "Successfully registered manager:" << endl;
	cout << "Special code: " << code.data << endl;
	cout << "Code: " << specialCodePlace.data << endl;

	return true;
}

void listUserData() {
	cout << "ID: " << currentUserInfo[0].data << endl;
	cout << "Fisrt Name: " << currentUserInfo[1].data << endl;
	cout << "Last Name: " << currentUserInfo[2].data << endl;
	cout << "Telephone Number: " << currentUserInfo[3].data << endl;
	cout << "Age: " << currentUserInfo[4].data << endl;
	cout << "Password: Hidden" << endl;
	if (isCashier) {
		cout << "Transactions: " << currentUserInfo[6].data << endl;
		cout << "Warning Points: " << currentUserInfo[7].data << endl;
		cout << "Is Approved" << currentUserInfo[8].data << endl;
	}
}

void listWorkers() {
	ifstream cashiers(CASHIERS_FILE_NAME);
	if (!cashiers.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
	}
	int length = 0;
	cashiers >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		cashiers >> input.data;
		MyString* filed = stringToArray(input, ':');
		cout << "Role: Cahier" << endl;
		cout << "ID: " << currentUserInfo[0].data << endl;
		cout << "Fisrt Name: " << currentUserInfo[1].data << endl;
		cout << "Last Name: " << currentUserInfo[2].data << endl;
		cout << "Telephone Number: " << currentUserInfo[3].data << endl;
		cout << "Age: " << currentUserInfo[4].data << endl;
		cout << "Password: Hidden" << endl;
		cout << "Transactions: " << currentUserInfo[6].data << endl;
		cout << "Warning Points: " << currentUserInfo[7].data << endl;
		cout << "Is Approved" << currentUserInfo[8].data << endl;
	}
	cashiers.close();
	ifstream managers(CASHIERS_FILE_NAME);
	if (!cashiers.is_open()) {
		cout << "File '" << CASHIERS_FILE_NAME << "' failed to open." << endl;
	}
	length = 0;
	cashiers >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		cashiers >> input.data;
		MyString* filed = stringToArray(input, ':');
		cout << "Role: Manager" << endl;
		cout << "ID: " << currentUserInfo[0].data << endl;
		cout << "Fisrt Name: " << currentUserInfo[1].data << endl;
		cout << "Last Name: " << currentUserInfo[2].data << endl;
		cout << "Telephone Number: " << currentUserInfo[3].data << endl;
		cout << "Age: " << currentUserInfo[4].data << endl;
		cout << "Password: Hidden" << endl;
	}
	managers.close();
}

void listProducts() {
	ifstream products(PRODUCTS_FILE_NAME);
	if (products.is_open()) {
		cout << "File '" << PRODUCTS_FILE_NAME << "' failed to open.";
	}
	int latestid = 0;
	int length = 0;
	products >> latestid;
	products >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		products >> input.data;
		MyString* details = stringToArray(input, ':');
		if (details[0].compare(PRODUCTS_WORD_NEW)) {
			cout << "Type: ";
			if (details[1].compare("0")) {
				cout << "Product By Unit" << endl;
			}
			else {
				cout << "Product By Weight" << endl;
			}
			cout << "ID: " << details[2].data << endl;
			cout << "Name: " << details[3].data << endl;
			cout << "Category: " << details[4].data << endl;
			cout << "Quantity: " << details[5].data << endl;
		}
		else {
			cout << "Type: ";
			if (details[0].compare("0")) {
				cout << "Product By Unit" << endl;
			}
			else {
				cout << "Product By Weight" << endl;
			}
			cout << "ID: " << details[1].data << endl;
			cout << "Name: " << details[2].data << endl;
			cout << "Category: " << details[3].data << endl;
			cout << "Quantity: " << details[4].data << endl;
		}
	}
}
void listProductsCategory(MyString cat) {
	ifstream products(PRODUCTS_FILE_NAME);
	if (products.is_open()) {
		cout << "File '" << PRODUCTS_FILE_NAME << "' failed to open.";
	}
	int latestid = 0;
	int length = 0;
	products >> latestid;
	products >> length;
	for (int i = 0; i < length; i++) {
		MyString input = "";
		products >> input.data;
		MyString* details = stringToArray(input, ':');
		if (details[0].compare(PRODUCTS_WORD_NEW)) {
			if (details[4].compare(cat)) {
				cout << "Type: ";
				if (details[1].compare("0")) {
					cout << "Product By Unit" << endl;
				}
				else {
					cout << "Product By Weight" << endl;
				}
				cout << "ID: " << details[2].data << endl;
				cout << "Name: " << details[3].data << endl;
				cout << "Quantity: " << details[5].data << endl;
			}
		}
		else {
			if (details[3].compare(cat)) {
				cout << "Type: ";
				if (details[0].compare("0")) {
					cout << "Product By Unit" << endl;
				}
				else {
					cout << "Product By Weight" << endl;
				}
				cout << "ID: " << details[1].data << endl;
				cout << "Name: " << details[2].data << endl;
				cout << "Quantity: " << details[4].data << endl;
			}
		}
	}
}

int main()
{
	cout << "Welcome to FMI Supermarket Management System 2024-2025!" << endl << "Please choose an action:" << endl;

	MyString input = "";
	while (!input.compare("END")) {
		cin >> input.data;
		int size = 0;
		MyString* words = stringToArray(input, ' ', size);
		if (role == 0) {
			if (words[0].compare("login")) {
				logged = login(words[1], words[2]);
				if (!logged) {
					cout << "Failed to log in." << endl;
					continue;
				}
			}
			else {
				if (words[0].compare("register")) {
					bool success = false;
					if (words[1].compare("Cashier")) {
						success = registerCashier(words[2].data, words[3].data, words[4].data, words[5].data, words[6].data);

					}
					else {
						if (words[1].compare("Manager")) {
							success = registerManager(words[2].data, words[3].data, words[4].data, words[5].data, words[6].data);
						}
					}
					if (!success) {
						cout << "Failed to register." << endl;
						continue;
					}
				}
				else {
					cout << "Unknown command!" << endl;
				}
			}
		}
		else
		{
			if (words[0].compare("list-user-data")) {
				listUserData();
			}
			else {
				if (words[0].compare("list-workers")) {
					listWorkers();
				}
				else {
					if (words[0].compare("list-products") && size > 1) {
						listProductsCategory(words[1]);
					}
					else {
						if (words[0].compare("list-products")) {
							listProducts();
						}
						else {
							if (words[0].compare("list-feed")) {

							}
							else {
								if (words[0].compare("list-transactions")) {

								}
								else {
									if (words[0].compare("leave")) {

									}
									else {
										if (words[0].compare("logout")) {
											delete[] currentUserInfo;
											role = None;
										}
										else {
											if (role == 1) {
												if (words[0].compare("sell")) {

												}
												else {
													cout << "Unknown command!" << endl;
												}
											}
											else {
												if (role == 2) {
													if (words[0].compare("list-pending")) {

													}
													else {
														if (words[0].compare("approve")) {

														}
														else {
															if(words[0].compare("decline")) {

															}
															else {
																if (words[0].compare("list-warned-cashier")) {

																}
																else {
																	if (words[0].compare("warn-cashier")) {

																	}
																	else {
																		if (words[0].compare("promote-cashier")) {

																		}
																		else {
																			cout << "Unknown command!" << endl;

																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout << "Thank you for shopping in FMI Supermarket!" << endl;
}