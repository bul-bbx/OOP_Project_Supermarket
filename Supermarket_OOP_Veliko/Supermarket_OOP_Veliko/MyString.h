#pragma once
#include <iostream>
using namespace std;

class MyString
{
private:
    void copyDynamicMemory(const MyString& other);
    void free();
public:
    int length;
    char* data;
    MyString();
    MyString(const char* data);
    MyString(char* data, int length);
    MyString(const MyString& other);
    ~MyString();
    MyString& operator=(const MyString& other);
    MyString& operator=(char* other);
    bool operator==(const MyString& other) const;
    MyString& append(const char* other);
    MyString& append(char* other, int length);
    MyString& append(const MyString& other);
    bool compare(const MyString& other);
    bool compare(MyString& other);

    //MyString & append(const MyString & other);
    char* getString() const;
};
ostream& operator<<(ostream& os, MyString& str);
istream& operator>>(istream& is, MyString& str);
MyString* stringToArray(MyString& input, char delimiter, int& outSize);
MyString* stringToArray(MyString& input, char delimiter);
bool tryConvertToInt(const char* str, int& result);
bool convertToString(int num, MyString& res);
bool tryConvertToDouble(const MyString& input, double& result);
bool convertDoubleToString(double value, MyString& result, int precision);
