#pragma once
#include <iostream>
#include <fstream>
#include "Manager.h"
#include "Cashier.h"
#include "Category.h"
#include "Cashier.h"
#include "MyString.h"
#include "Voucher.h"
#include "Product.h"
#include "Warning.h"
#include "Voucher.h"
#include "MultipleCategoryVoucher.h"
#include "SingleCategoryVoucher.h"
#include "AllProductsVoucher.h"


using namespace std;
class Instance
{
	const size_t MAX_CATEGORIES = 100;
	const size_t MAX_VOUCHERS = 100;
	const size_t MAX_USERS = 1000;
	const size_t MAX_PRODUCTS = 10000;
	const size_t MAX_WARNINGS = 1000;



public:
	int latestTransactionsId;

	int latestEmployeeId;
	Employee** employees = new Employee * [MAX_USERS];
	size_t employeeCount;
	size_t managersCount;
	size_t cashiersCount;

	int lastestCategoryId;
	Category** categories = new Category * [MAX_CATEGORIES];
	size_t categoryCount;

	int latestVoucherId;
	Voucher** vouchers = new Voucher * [MAX_VOUCHERS];
	size_t voucherCount;

	int latestProductId;
	Product** products = new Product * [MAX_PRODUCTS];
	size_t productCount;

	int latestWarningId;
	Warning** warnings = new Warning * [MAX_WARNINGS];
	size_t warningCount;

	void run();
	Instance();
	~Instance();

	void sell() const;
	void leaveWork() const;
	void listPending() const;
	void listTransactions() const;
	bool login(MyString id, MyString password);
	bool isManager() const;
	bool isCashier() const;
	bool registerCashier(char* fisrt_name, char* last_name, char* telephoneNumber, char* age, char* password);
	bool registerManager(char* first_name, char* last_name, char* telephoneNumber, char* age, char* password);
	void listUserData() const;
	void listWorkers() const;
	void listProducts() const;
	void listProductsCategory(MyString cat) const;
	void cashierApprove(int cId) const;
	void cashierDecline(int cId) const;
	void listWarnedCashiers(int points) const;
	void warnCashier(int cId, int severity) const;
	void promoteCashier(int cId) const;
	void fireCashier(int cId) const;
	void deleteCategory(int cId);
	void addProduct(MyString type);
	void deleteProduct(int cId);
	void loadProducts(MyString fileName);
	void loadGiftCards(MyString fileName);
};

