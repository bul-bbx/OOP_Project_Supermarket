#pragma once
#include "Employee.h"
#include "Config.h"
#include "MyString.h"
#include "Constants.h"
#include "Category.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime> 
class Manager :
    protected Employee
{
protected:
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
    Manager& operator=(Manager& other);
    Manager& operator=(MyString* other);
};

char getRandomNumAsChar();
char getRandomLetterUpper();
char getRandomLetterLower();
char* createSpecialKey();

