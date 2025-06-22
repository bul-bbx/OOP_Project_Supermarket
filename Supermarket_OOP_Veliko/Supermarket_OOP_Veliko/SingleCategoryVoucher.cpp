#include "SingleCategoryVoucher.h"

SingleCategoryVoucher::SingleCategoryVoucher()
{
	id = -1;
	categoryId = -1;
	percentage = 0;
}

SingleCategoryVoucher::SingleCategoryVoucher(SingleCategoryVoucher& const other)
{
	id = other.id;
	categoryId = other.categoryId;
	percentage = other.percentage;
	code = other.code;
}

SingleCategoryVoucher::SingleCategoryVoucher(int _id, int _categoryId, double _percentage, MyString _code)
{
	id = _id;
	categoryId = _categoryId;
	percentage = _percentage;
	code = _code;
}

int SingleCategoryVoucher::getId()
{
	return id;
}

MyString SingleCategoryVoucher::getType()
{
	return type;
}

double SingleCategoryVoucher::getPercentage()
{
	return percentage;
}

int SingleCategoryVoucher::getCategoriesCount()
{
	return 0;
}

int* SingleCategoryVoucher::getCategories()
{
	return nullptr;
}

int SingleCategoryVoucher::getCategory()
{
	return categoryId;
}

MyString SingleCategoryVoucher::getCode()
{
	return code;
}
