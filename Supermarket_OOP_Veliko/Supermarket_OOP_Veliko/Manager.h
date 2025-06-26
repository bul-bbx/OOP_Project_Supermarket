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
    public Employee
{
private:
    MyString type = "Manager";
    void copyFrom(Manager& const man);
    void free();
public:
    Manager();
    Manager(Manager& man);
    Manager(int _id, char* _firstName, char* _familyName, char* _telephoneNumber, int _age, char* _password);
    ~Manager();

    Manager& operator=(Manager& other);

    MyString getType() override;
    void approve() override;
    void warn(int points) override;

    int getTransactions() override;
    int getWarningPoints() override;
    bool isApproved() override;
};

char getRandomNumAsChar();
char getRandomLetterUpper();
char getRandomLetterLower();
MyString createSpecialKey();

