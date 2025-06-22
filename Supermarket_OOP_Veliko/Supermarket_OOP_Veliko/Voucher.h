#pragma once
#include "MyString.h"
class Voucher
{
	int id;
	double percentage;
	MyString code;
public:
	Voucher();
	Voucher(Voucher& const other);
	Voucher(int _id, int _userId, double _percentage, MyString code);
	
	virtual int getId() = 0;
	virtual MyString getType() = 0;
	virtual double getPercentage() = 0;
	virtual int getCategoriesCount() = 0;
	virtual int* getCategories() = 0;
	virtual int getCategory() = 0;
	virtual MyString getCode() = 0;
};

