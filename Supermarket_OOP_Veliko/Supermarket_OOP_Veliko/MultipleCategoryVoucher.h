#pragma once
#include "Voucher.h"
class MultipleCategoryVoucher:
	public Voucher
{
	MyString type = "Multiple";
	int id;
	int categoriesCount;
	int* categories;
	int percentage;
	MyString code;
	void free();
	void copyFrom(MultipleCategoryVoucher& const other);
public:
	MultipleCategoryVoucher();
	MultipleCategoryVoucher(MultipleCategoryVoucher& const other);
	MultipleCategoryVoucher(int _id, int categoriesCount, int* _categories, double _percentage, MyString _code);
	~MultipleCategoryVoucher();

	int getId() override;
	MyString getType() override;
	double getPercentage() override;
	int getCategoriesCount() override;
	int* getCategories() override;
	int getCategory() override ;
	MyString getCode() override;
};

