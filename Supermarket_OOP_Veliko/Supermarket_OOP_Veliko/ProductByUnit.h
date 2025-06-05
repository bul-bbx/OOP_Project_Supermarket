#pragma once
#include "Product.h"
#include "Constants.h"
using namespace std;
class ProductByUnit :
    protected Product
{
    int count;
protected:
    void free();
    void copyFrom(ProductByUnit& prod);
public: 
    ProductByUnit();
    ProductByUnit(ProductByUnit& prod);
    ProductByUnit(char* name, char* cat, double price, int count);
    ~ProductByUnit();
};

