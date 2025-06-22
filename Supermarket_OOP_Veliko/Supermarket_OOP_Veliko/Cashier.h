#pragma once
#include "Employee.h"
#include "Constants.h"
class Cashier :
    public Employee
{
private:
    MyString type = "Cashier";
    int transactions;
    int warningPoints;
    bool approved;

    void copyFrom(Cashier& const cash);
    void free();
public:
    Cashier();
    Cashier(Cashier& cash);
    Cashier(int _id, char* _firstName, char* _familyName, char* _telephoneNumber, int _age, char* _password, int _transactions, int _warningPoints, bool _approved);
    ~Cashier();
    Cashier& operator= (Cashier& const other);
    void sell() const;

    int getId() override;
    MyString getFirstName() override;
    MyString getLastName() override;
    MyString getType() override;
    MyString getTelephone() override;
    short getAge() override;
    MyString getPassword() override;

    int getTransactions() override;
    int getWarningPoints() override;
    bool isApproved() override;
};