#pragma once
#include "Voucher.h"
class SingleCategoryVoucher :
    public Voucher
{
    MyString type = "Single";
    int id;
    int categoryId;
    double percentage;
    MyString code;
public: 
    SingleCategoryVoucher();
    SingleCategoryVoucher(SingleCategoryVoucher& const other);
    SingleCategoryVoucher(int _id, int _categoryId, double _percentage, MyString _code);

    int getId() override;
    MyString getType() override;
    double getPercentage() override;
    int getCategoriesCount() override ;
    int* getCategories() override ;
    int getCategory() override;
    MyString getCode() override;
};

