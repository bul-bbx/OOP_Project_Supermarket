#pragma once
#include "Employee.h"
#include "Constants.h"
class Cashier :
    protected Employee
{
private:
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
    void sell() const;
};