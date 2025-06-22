#pragma once
#include "Product.h"
class ProductByWeight :
    public Product
{
private:
    MyString type = "Weight";
    double weight;
    void copyFrom(ProductByWeight& prod);
public:
    ProductByWeight();
    ProductByWeight(ProductByWeight& prod);
    ProductByWeight(char* _name, int _category, double _price, double _weight);
    MyString getType() override;

    int getCount() override;
    double getWeight() override;
};

