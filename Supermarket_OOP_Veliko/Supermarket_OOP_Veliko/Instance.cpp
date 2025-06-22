#include "Instance.h"
#include "ProductByUnit.h"
#include "ProductByWeight.h"
using namespace std;

enum Role {
	None = 0,
	Cash = 1,
	Man = 2
};
Role role = None;
Employee* currentUser;
bool logged = false;

void Instance::run()
{
	cout << "Welcome to FMI Supermarket Management System 2024-2025!" << endl << "Please choose an action:" << endl;

	MyString input = "";
	while (!input.compare("END")) {
		cin >> input.data;
		int size = 0;
		MyString* words = stringToArray(input, ' ', size);
		if (role == None) {
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
								//TODO
							}
							else {
								if (words[0].compare("list-transactions")) {
									listTransactions();
								}
								else {
									if (words[0].compare("leave")) {
										leaveWork();
									}
									else {
										if (words[0].compare("logout")) {
											currentUser = nullptr;
											role = None;
										}
										else {
											if (role == Cash) {
												if (words[0].compare("sell")) {

												}
												else {
													cout << "Unknown command!" << endl;
												}
											}
											else {
												if (role == Man) {
													if (words[0].compare("list-pending")) {
														listPending();
													}
													else {
														if (words[0].compare("approve")) {

														}
														else {
															if (words[0].compare("decline")) {

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
																			if (words[0].compare("fire-cashier")) {
																			
																			}
																			else {
																				if (words[0].compare("add-category")) {

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
		}
	}
	cout << "Thank you for shopping in FMI Supermarket!" << endl;
}

Instance::Instance()
{
	//Employees
		//Managers
		ifstream man(MANAGERS_FILE_NAME);
		if (!man.is_open()) {
			cout << "Failed to open save file!" << endl;
		}
		man >> managersCount;
		for (int i = employeeCount; i < managersCount && i < MAX_USERS; i++) {
			MyString input;
			man >> input.data;
			MyString* arr = stringToArray(input, ':');
			int idM = 0;
			tryConvertToInt(arr[0].data, idM);
			int ageM = 0;
			tryConvertToInt(arr[4].data, ageM);
			Manager m (idM, arr[1].data, arr[2].data, arr[3].data, ageM, arr[5].data);
			employees[i] = &m;
			delete[] arr;
		}
		man.close();
		//
	
		//Cashiers
		ifstream cash(CASHIERS_FILE_NAME);
		if (!cash.is_open()) {
			cout << "Failed to open save file!" << endl;
		}
		cash >> cashiersCount;
		int lengthUse = 0;
		if (managersCount + cashiersCount > MAX_USERS) {
			lengthUse = MAX_USERS;
		}
		else {
			lengthUse = managersCount + cashiersCount;
		}
		for (int i = managersCount; i < lengthUse; i++) {
			MyString input;
			cash >> input.data;
			MyString* arr = stringToArray(input, ':');
			int idC = 0;
			tryConvertToInt(arr[0].data, idC);
			int ageC = 0;
			tryConvertToInt(arr[4].data, ageC);
			int transactions = 0;
			tryConvertToInt(arr[6].data, transactions);
			int warningId = 0;
			tryConvertToInt(arr[7].data, warningId);
			int approved = 0;
			tryConvertToInt(arr[8].data, approved);
			bool approvedB = approved;
			Cashier c(idC, arr[1].data, arr[2].data, arr[3].data, ageC, arr[5].data, transactions, warningId, approvedB);
			employees[i] = &c;
			delete[] arr;
		}
		employeeCount = lengthUse;
		cash.close();
		//
	ifstream lId(EMPLOYEE_LATEST_ID_FILE_NAME);
	if (!lId.is_open()) {
		cout << "Failed to open save file!" << endl;
	}
	lId >> latestEmployeeId;
	lId.close();
	//

	//Products
	ifstream prod(PRODUCTS_FILE_NAME);
	if (!prod.is_open()) {
		cout << "Failed to open save file!" << endl;
	}
	prod >> latestProductId;
	prod >> productCount;
	for (int i = 0; i < productCount; i++) {
		MyString input;
		prod >> input.data;
		MyString* arr = stringToArray(input, ':');
		if (arr[0].compare("Unit")) {
			double price = 0;
			tryConvertToDouble(arr[2].data, price);
			int catId = 0;
			tryConvertToInt(arr[1].data, catId);
			int count = 0;
			tryConvertToInt(arr[3].data, count);
			ProductByUnit p(arr[0].data, catId, price, count);
			products[i] = &p;
		}
		else {
			double price = 0;
			tryConvertToDouble(arr[2].data, price);
			int catId = 0;
			tryConvertToInt(arr[1].data, catId);
			double weight = 0;
			tryConvertToDouble(arr[3].data, weight);
			ProductByWeight p(arr[0].data, catId, price, weight);
			products[i] = &p;
		}
		delete[] arr;
	}
	prod.close();
	//

	//Categories
	ifstream cats(CATEGORIES_FILE_NAME);
	if (!cats.is_open()) {
		cout << "Failed to open save file!" << endl;
	}
	cats >> lastestCategoryId;
	cats >> categoryCount;
	for (int i = 0; i < categoryCount; i++) {
		MyString input;
		cats >> input.data;
		MyString* arr = stringToArray(input, ':');
		int catId = 0;
		tryConvertToInt(arr[0].data, catId);
		Category c(catId, arr[1].data, arr[2].data);
		categories[i] = &c;
		delete[] arr;
	}
	cats.close();
	//

	//Vouchers
	ifstream vou(VOUCHERS_FILE_NAME);
	if (!vou.is_open()) {
		cout << "Failed to open save file!" << endl;
	}
	vou >> latestVoucherId;
	vou >> voucherCount;
	for (int i = 0; i < voucherCount; i++) {
		MyString input;
		vou >> input.data;
		MyString* arr = stringToArray(input, ':');
		if (arr[0].compare("All")) {
			int id = 0;
			tryConvertToInt(arr[1].data, id);
			double perc = 0;
			tryConvertToDouble(arr[2].data, perc);
			AllProductsVoucher a(id, perc, arr[3]);
			vouchers[i] = &a;
		}
		else if (arr[0].compare("Single")) {
			int id = 0;
			tryConvertToInt(arr[1].data, id);
			double perc = 0;
			tryConvertToDouble(arr[2].data, perc);
			int catId = 0;
			tryConvertToInt(arr[3].data, catId);
			SingleCategoryVoucher s(id, catId, perc, arr[4]);
			vouchers[i] = &s;
		}
		else {
			int id = 0;
			tryConvertToInt(arr[1].data, id);
			int catCount = 0;
			tryConvertToInt(arr[2].data, catCount);
			int* cates = new int[catCount];
			for (int k = 0; k < catCount; k++) {
				int catid = 0;
				tryConvertToInt(arr[2 + k].data, catid);
				cates[k] = catid;
			}
			double perc = 0;
			tryConvertToDouble(arr[catCount + 2].data, perc);
			MultipleCategoryVoucher m(id, catCount, cates, perc, arr[catCount + 3]);
			vouchers[i] = &m;
		}
		delete[] arr;
	}
	vou.close();
	//
	
	//Warnings
	ifstream warns(WARNINGS_FILE_NAME);
	if (!warns.is_open()) {
		cout << "Failed to open save file!" << endl;
	}
	warns >> latestWarningId;
	warns >> warningCount;
	for (int i = 0; i < warningCount; i++) {
		MyString input;
		warns >> input.data;
		MyString* arr = stringToArray(input, ':');
		int id = 0;
		tryConvertToInt(arr[0].data, id);
		int senderid = 0;
		tryConvertToInt(arr[1].data, senderid);
		int receiverid = 0;
		tryConvertToInt(arr[2].data, receiverid);
		int severity = 0;
		tryConvertToInt(arr[4].data, severity);
		Warning w(id, senderid, receiverid, arr[3], severity);
		warnings[i] = &w;
		delete[] arr;
	}
	warns.close();
	//
}

Instance::~Instance()
{
	//Employees
		//Managers
		ofstream man(MANAGERS_FILE_NAME, ios::trunc);
		if (!man.is_open()) {
			cout << "Failed to open file to save!" << endl;
		}
		man << managersCount << endl;
		for (int i = 0; i < employeeCount; i++) {
			if (employees[i]->getType().compare("Manager")) {
				MyString data;
				convertToString(employees[i]->getId(), data);
				data.append(":");
				data.append(employees[i]->getFirstName());
				data.append(":");
				data.append(employees[i]->getLastName());
				data.append(":");
				data.append(employees[i]->getTelephone());
				MyString age;
				convertToString(employees[i]->getAge(), age);
				data.append(":");
				data.append(age);
				data.append(":");
				data.append(employees[i]->getPassword());
				man << data.data << endl;
			}
		}
		man.close();
		// 
		//Cashiers
		ofstream cash(MANAGERS_FILE_NAME, ios::trunc);
		if (!man.is_open()) {
			cout << "Failed to open file to save!" << endl;
		}
		cash << managersCount << endl;
		for (int i = 0; i < employeeCount; i++) {
			if (employees[i]->getType().compare("Cashier")) {
				MyString data;
				convertToString(employees[i]->getId(), data);
				data.append(":");
				data.append(employees[i]->getFirstName());
				data.append(":");
				data.append(employees[i]->getLastName());
				data.append(":");
				data.append(employees[i]->getTelephone());
				MyString age;
				convertToString(employees[i]->getAge(), age);
				data.append(":");
				data.append(age);
				data.append(":");
				data.append(employees[i]->getPassword());
				data.append(":");
				MyString transactions;
				convertToString(employees[i]->getTransactions(), transactions);
				data.append(transactions);
				data.append(":");
				MyString warnings;
				convertToString(employees[i]->getWarningPoints(), warnings);
				data.append(warnings);
				data.append(":");
				MyString approved;
				convertToString(employees[i]->isApproved(), approved);
				data.append(approved);
				cash << data.data << endl;
			}
		}
		cash.close();
		// 
	ofstream lWI(EMPLOYEE_LATEST_ID_FILE_NAME, ios::trunc);
	if (!lWI.is_open()) {
		cout << "Failed to open file to save!" << endl;
	}
	lWI << latestEmployeeId;
	lWI.close();
	//
	//Products
	ofstream prod(PRODUCTS_FILE_NAME, ios::trunc);
	if (!prod.is_open()) {
		cout << "Failed to open file to save!" << endl;
	}
	prod << latestProductId << endl;
	prod << productCount << endl;
	for (int i = 0; i < productCount; i++) {
		MyString data = products[i]->getType();
		products[i]->getName();
		data.append(":");
		MyString catId;
		convertToString(products[i]->getCatId(), catId);
		data.append(catId);
		data.append(":");
		MyString price;
		convertDoubleToString(products[i]->getPrice(), price, 2);
		data.append(price);
		prod << data.data << endl;
	}
	prod.close();
	// 
	//Categories
	ofstream cats(CATEGORIES_FILE_NAME, ios::trunc);
	if (!cats.is_open()) {
		cout << "Failed to open file to save!" << endl;
	}
	cats << lastestCategoryId;
	cats << categoryCount;
	for (int i = 0; i < categoryCount; i++) {
		
		MyString data;
		convertToString(categories[i]->getId(), data);
		data.append(":");
		data.append(categories[i]->getName());
		data.append(":");
		data.append(categories[i]->getDescription());
		cats << data.data << endl;
	}
	cats.close();
	//
	//Vouchers
	ofstream vou(VOUCHERS_FILE_NAME, ios::trunc);
	if (!vou.is_open()) {
		cout << "Failed to open file to save!" << endl;
	}
	vou << latestVoucherId;
	vou << voucherCount;
	for (int i = 0; i < voucherCount; i++) {
		MyString data = vouchers[i]->getType();
		if (data.compare("All")) {
			data.append(":");
			MyString vouId;
			convertToString(vouchers[i]->getId(), vouId);
			data.append(vouId);
			data.append(":");
			MyString percentage;
			convertDoubleToString(vouchers[i]->getPercentage(), percentage, 2);
			data.append(percentage);
			data.append(":");
			data.append(vouchers[i]->getCode());
		}
		else if (data.compare("Multiple")) {
			data.append(":");
			MyString vouId;
			convertToString(vouchers[i]->getId(), vouId);
			data.append(vouId);
			data.append(":");
			MyString catCount;
			convertToString(vouchers[i]->getCategoriesCount(), catCount);
			data.append(catCount);
			data.append(":");
			for (int k = 0; k < vouchers[i]->getCategoriesCount(); k++) {
				MyString cat;
				convertToString(vouchers[i]->getCategories()[k], cat);
				data.append(cat);
				data.append(":");
			}
			MyString percentage;
			convertDoubleToString(vouchers[i]->getPercentage(), percentage, 2);
			data.append(percentage);
			data.append(":");
			data.append(vouchers[i]->getCode());
		}
		else {
			data.append(":");
			MyString vouId;
			convertToString(vouchers[i]->getId(), vouId);
			data.append(vouId);
			data.append(":");
			MyString cat;
			convertToString(vouchers[i]->getCategory(), cat);
			data.append(cat);
			data.append(":");
			MyString percentage;
			convertDoubleToString(vouchers[i]->getPercentage(), percentage, 2);
			data.append(percentage);
			data.append(":");
			data.append(vouchers[i]->getCode());
		}
		vou << data.data << endl;
	}
	vou.close();
	//
	//Warnings
	ofstream warn(WARNINGS_FILE_NAME, ios::trunc);
	if (!warn.is_open()) {
		cout << "Failed to open file to save!" << endl;
	}
	warn << latestWarningId;
	warn << warningCount;
	for (int i = 0; i < warningCount; i++) {
		MyString data;
		convertToString(warnings[i]->getId(), data);
		data.append(":");
		MyString rId;
		convertToString(warnings[i]->getReceiverId(), rId);
		data.append(rId);
		data.append(":");
		MyString sId;
		convertToString(warnings[i]->getSenderId(), sId);
		data.append(sId);
		data.append(":");
		data.append(warnings[i]->getDescription());
		data.append(":");
		MyString points;
		convertToString(warnings[i]->getSeverity(), points);
		data.append(points);
		warn << data.data << endl;
	}
	warn.close();
	//
	for (int i = 0; i < employeeCount; i++) {
		delete employees[i];
	}
	delete[] employees;
	
	for (int i = 0; i < productCount; i++) {
		delete products[i];
	}
	delete[] products;

	for (int i = 0; i < categoryCount; i++) {
		delete categories[i];
	}
	delete[] categories;

	for (int i = 0; i < voucherCount; i++) {
		delete vouchers[i];
	}
	delete[] vouchers;

	for (int i = 0; i < warningCount; i++) {
		delete warnings[i];
	}
	delete[] warnings;
}

void Instance::leaveWork() const
{
	delete[] currentUser;
	role = None;
}

void Instance::listPending() const
{
	for (int i = 0; i < employeeCount; i++) {
		if (employees[i]->getType().compare("Cashier")) {
			if (!employees[i]->isApproved()) {
				cout << "ID: " << currentUser->getId() << endl;
				cout << "Fisrt Name: " << currentUser->getFirstName().data << endl;
				cout << "Last Name: " << currentUser->getLastName().data << endl;
				cout << "Telephone Number: " << currentUser->getTelephone().data << endl;
				cout << "Age: " << currentUser->getAge() << endl;
				cout << "Transactions: " << currentUser->getTransactions() << endl;
				cout << "Warning Points: " << currentUser->getWarningPoints() << endl;
			}
		}
		cout << endl;
	}
}

void Instance::listTransactions() const
{

}

bool Instance::login(MyString id, MyString password) {
	int idI = 0;
	tryConvertToInt(id.data, idI);
	for (int i = 0; i < employeeCount; i++) {
		if (employees[i]->getId() == idI) {
			if (employees[i]->getPassword().compare(password)) {
				cout << "User " << employees[i]->getFirstName().data << " " << employees[i]->getLastName().data << " with ID: " << employees[i]->getId() << " has been logged into the system." << endl;
				currentUser = employees[i];
				if (currentUser->getType().compare("Manager")) {
					role = Man;
				}
				else {
					role = Cash;
				}
				return true;
			}
			else {
				cout << "Invalid creditentials!" << endl;
				return false;
			}
		}
	}
	cout << "No user with ID " << id.data << " has been found!" << endl;
	return false;
}

bool Instance::isManager() const{
	return role == Man;
}

bool Instance::isCashier() const{
	return role == Cash;
}

bool Instance::registerCashier(char* first_name, char* last_name, char* telephoneNumber, char* age, char* password) {
	//Check if we've reached max buffer size for users
	if (employeeCount == MAX_USERS) {
		cout << "You have reached the maximum amount of employees!" << endl;
		return 0;
	}
	//Check the input
	if (first_name == nullptr || last_name == nullptr || telephoneNumber == nullptr || age == nullptr || password == nullptr) {
		cout << "Invalid creditentials try again!" << endl;
		return 0;
	}
	//Create the user and assign it to the array
	int ageC = 0;
	tryConvertToInt(age, ageC);
	Cashier c (++latestEmployeeId, first_name, last_name, telephoneNumber, ageC, password, 0, 0, false);
	employees[employeeCount++] = &c;
	cashiersCount;
	cout << "Successfully registered a cashier! Wait for approval!" << endl;
	return true;
	
}

bool Instance::registerManager(char* first_name, char* last_name, char* telephoneNumber, char* age, char* password) {
	//Check if we've reached max buffer size for users
	if (employeeCount == MAX_USERS) {
		cout << "You have reached the maximum amount of employees!" << endl;
		return 0;
	}
	//Check the input
	if (first_name == nullptr || last_name == nullptr || telephoneNumber == nullptr || age == nullptr || password == nullptr) {
		cout << "Invalid creditentials try again!" << endl;
		return 0;
	}
	//Create the user and assign it to the array
	int ageC = 0;
	tryConvertToInt(age, ageC);
	Manager m(++latestEmployeeId, first_name, last_name, telephoneNumber, ageC, password);
	employees[employeeCount++] = &m;
	managersCount++;
	MyString key = createSpecialKey();
	cout << "Special code: " << key.data << endl;
	MyString dir = "data/Special Codes/";
	MyString mId;
	convertToString(m.getId(), mId);
	dir.append(mId);
	dir.append("_special_code.txt");
	ofstream spCodeDir(dir.data);
	if (!spCodeDir.is_open()) {
		cout << "Failed to save special code!" << endl;
	}
	spCodeDir << key.data;
	spCodeDir.close();
	cout << "Successfully registered a manager!" << endl;
	return true;
}

void Instance::listUserData() const{
	//List all properties
	cout << "ID: " << currentUser->getId() << endl;
	cout << "Fisrt Name: " << currentUser->getFirstName().data << endl;
	cout << "Last Name: " << currentUser->getLastName().data << endl;
	cout << "Telephone Number: " << currentUser->getTelephone().data << endl;
	cout << "Age: " << currentUser->getAge() << endl;
	//if the user is cashier print the cashier properties
	if (isCashier()) {
		cout << "Transactions: " << currentUser->getTransactions() << endl;
		cout << "Warning Points: " << currentUser->getWarningPoints() << endl;
		cout << "Is Approved" << (bool)currentUser->isApproved() << endl;
	}
}

void Instance::listWorkers() const{
	//Loop through every employee
	for (int i = 0; i < employeeCount; i++) {
		cout << "Role: " << employees[i]->getType().data << endl;
		cout << "ID: " << employees[i]->getId() << endl;
		cout << "Fisrt Name: " << employees[i]->getFirstName().data << endl;
		cout << "Last Name: " << employees[i]->getLastName().data << endl;
		cout << "Telephone Number: " << employees[i]->getTelephone().data << endl;
		cout << "Age: " << employees[i]->getAge() << endl;
		//If the employee is cashier print cashier properties
		if (employees[i]->getType().compare("Cashier")) {
			cout << "Transactions: " << employees[i]->getTransactions() << endl;
			cout << "Warning Points: " << employees[i]->getWarningPoints() << endl;
			cout << "Is Approved: " << (bool)employees[i]->isApproved() << endl;
		}
		cout << endl;
	}
}

void Instance::listProducts() const{
	for (int i = 0; i < productCount; i++) {
		cout << "Product Name: " << products[i]->getName().data << endl;
		//Search for category
		bool found = false;
		for (int k = 0; k < categoryCount; k++) {
			if (categories[k]->getId() == products[i]->getCatId()) {
				cout << "Category: " << categories[k]->getName().data << endl;
				found = true;
				break;
			}
		}
		//If not found print N/A
		if (!found) {
			cout << "Category: N/A" << endl;
		}
		cout << "Price (per Unit/Kg): " << products[i]->getPrice() << endl;
		//Print wether it has units of kilograms left
		if (products[i]->getType().compare("Unit")) {
			cout << "Units left: " << products[i]->getCount() << endl;
		}
		else {
			cout << "Kilograms left: " << products[i]->getWeight() << endl;
		}
		cout << endl;
	}
}

void Instance::listProductsCategory(MyString cat) const{
	int catId = -1;
	//Check if category exists
	for (int i = 0; i < categoryCount; i++) {
		if (categories[i]->getName().compare(cat)) {
			catId = categories[i]->getId();
			break;
		}
	}
	if (catId < 0) {
		cout << "No category found in the records!" << endl;
		return;
	}
	//Check for products of that category
	int count = 0;
	for (int i = 0; i < productCount; i++) {
		if (products[i]->getCatId() == catId) {
			cout << "Product Name: " << products[i]->getName().data << endl;
			cout << "Price (per Unit/Kg): " << products[i]->getPrice() << endl;
			if (products[i]->getType().compare("Unit")) {
				cout << "Units left: " << products[i]->getCount() << endl;
			}
			else {
				cout << "Killograms left: " << products[i]->getWeight() << endl;
			}
		}
		count++;
		cout << endl;
	}
	//Print this if no products are found
	if (count == 0) {
		cout << "No products of category " << cat.data << endl;
	}
}

