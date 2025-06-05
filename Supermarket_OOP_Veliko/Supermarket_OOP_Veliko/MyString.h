#pragma once

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
    MyString& append(const char* other);
    MyString& append(char* other, int length);
    MyString& append(const MyString& other);
    bool compare(const MyString& other);

    //MyString & append(const MyString & other);
    char* getString() const;
};
MyString* stringToArray(const MyString& input, char delimiter, int& outSize);
MyString* stringToArray(const MyString& input, char delimiter);
bool tryConvertToInt(const char* str, int& result);
bool convertToString(int num, MyString& res);