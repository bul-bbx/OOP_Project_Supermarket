#include "MultipleCategoryVoucher.h"

void MultipleCategoryVoucher::free()
{
    delete[] categories;
}

void MultipleCategoryVoucher::copyFrom(MultipleCategoryVoucher& const other)
{
    id = other.id;
    categoriesCount = other.categoriesCount;
    for (int i = 0; i < categoriesCount; i++) {
        categories[i] = other.categories[i];
    }
    percentage = other.percentage;
    code = other.code;
}

MultipleCategoryVoucher::MultipleCategoryVoucher()
{
    id = -1;
    categoriesCount = 0;
    categories = nullptr;
    percentage = 0;
}

MultipleCategoryVoucher::MultipleCategoryVoucher(MultipleCategoryVoucher& const other)
{
    copyFrom(other);
}

MultipleCategoryVoucher::MultipleCategoryVoucher(int _id, int _categoriesCount, int* _categories, double _percentage, MyString _code)
{
    id = _id;
    categoriesCount = _categoriesCount;
    categories = new int[categoriesCount];
    for (int i = 0; i < categoriesCount; i++) {
        categories[i] = _categories[i];
    }
    percentage = _percentage;
    code = _code;
}

MultipleCategoryVoucher::~MultipleCategoryVoucher()
{
    free();
}

int MultipleCategoryVoucher::getId()
{
    return id;
}

MyString MultipleCategoryVoucher::getType()
{
    return type;
}

double MultipleCategoryVoucher::getPercentage()
{
    return percentage;
}

int MultipleCategoryVoucher::getCategoriesCount()
{
    return categoriesCount;
}

int* MultipleCategoryVoucher::getCategories()
{
    return categories;
}

int MultipleCategoryVoucher::getCategory()
{
    return -1;
}

MyString MultipleCategoryVoucher::getCode()
{
    return code;
}
