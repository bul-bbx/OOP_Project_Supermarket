#pragma once
#include "Voucher.h"
class AllProductsVoucher :
	public Voucher
{
	MyString type = "All";
	int id;
	double percentage;
	MyString code;
public:
	AllProductsVoucher();
	AllProductsVoucher(AllProductsVoucher& const other);
	AllProductsVoucher(int _id, double _percentage, MyString _code);

	int getId() override;
	MyString getType() override;
	double getPercentage() override;
	int getCategoriesCount() override ;
	int getCategory() override ;
	int* getCategories() override ;
	MyString getCode() override;
};

