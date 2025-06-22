#include "AllProductsVoucher.h"

AllProductsVoucher::AllProductsVoucher()
{
    id = -1;
    percentage = 0;
}

AllProductsVoucher::AllProductsVoucher(AllProductsVoucher& const other)
{
    id = other.id;
    percentage = other.percentage;
    code = other.code;
}

AllProductsVoucher::AllProductsVoucher(int _id, double _percentage, MyString _code)
{
    id = _id;
    percentage = _percentage;
    code = _code;
}

int AllProductsVoucher::getId()
{
    return id;
}

MyString AllProductsVoucher::getType()
{
    return type;
}

double AllProductsVoucher::getPercentage()
{
    return percentage;
}

int AllProductsVoucher::getCategoriesCount()
{
    return 0;
}

int AllProductsVoucher::getCategory()
{
    return -1;
}

int* AllProductsVoucher::getCategories()
{
    return nullptr;
}

MyString AllProductsVoucher::getCode()
{
    return code;
}
