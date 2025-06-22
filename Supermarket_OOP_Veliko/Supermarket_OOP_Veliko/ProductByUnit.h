#pragma once
#include "Product.h"
#include "Constants.h"
using namespace std;
class ProductByUnit :
    public Product
{
private:
    MyString type = "Unit";
    int count;
    void copyFrom(ProductByUnit& prod);
public: 
    ProductByUnit();
    ProductByUnit(ProductByUnit& prod);
    ProductByUnit(char* name, int cat, double price, int count);
    MyString getType() override;

    int getCount() override;
    double getWeight() override;
};

