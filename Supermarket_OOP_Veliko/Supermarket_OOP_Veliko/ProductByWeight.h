#pragma once
#include "Product.h"
class ProductByWeight :
    protected Product
{
    double weight;
    void free();
    void copyFrom(ProductByWeight& prod);
public:
    ProductByWeight();
    ProductByWeight(ProductByWeight& prod);
    ProductByWeight(char* _name, char* _category, double _price, double _weight);
    ~ProductByWeight();
};

