#pragma once
#include "Employee.h"
#include "Cashier.h"
#include "Config.h"
#include <fstream>
#include <iostream>
#include <string>
class Manager :
    protected Employee
{
protected:
    const string& CASHIERS_FILE_NAME = "Cashiers.txt";
    const string CATEGORIES_FILE_NAME = "Categories.txt";
    void copyFrom(Manager& const man);
    void free();
public:
    Manager();
    Manager(Manager& man);
    Manager(int _id, char* _firstName, char* _familyName, char* _telephoneNumber, int _age, char* _password);
    ~Manager();

    void listPending() const;
    void approve(int const cashierId, char* specialCode) const;
    void decline(int const cashierId, char* specialCode) const;
    void listWarnedCashiers(int const warningPoints) const;
    void warnCashier(int const cashierId, int points) const;
    void promoteCashier(int const cashierId, char* specialCode);
    void fireCashier(int const cashierId, char* specialCode) const;
    void addCategory(char* categoryName, char* categoryDescription) const;
    void deleteCategory(int categoryId) const;
    void addProduct(int const productType);
    void deleteProduct(int const productId);
    void loadProducts(char* fileName);
    void loadGiftCards(char* fileName);
};

