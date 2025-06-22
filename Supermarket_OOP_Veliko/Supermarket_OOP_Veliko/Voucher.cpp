#pragma once
#include "Voucher.h"

Voucher::Voucher()
{
	id = -1;
	percentage = 0;
}

Voucher::Voucher(Voucher& const other)
{
	id = other.id;
	percentage = other.percentage;
	code = other.code;
}

Voucher::Voucher(int _id, int _userId, double _percentage, MyString _code)
{
	id = _id;
	percentage = _percentage;
	code = _code;
}
