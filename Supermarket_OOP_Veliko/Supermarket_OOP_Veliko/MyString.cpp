#pragma once
#include "MyString.h"

using namespace std;
void MyString::copyDynamicMemory(const MyString& other)
{
    this->length = other.length;
    this->data = new char[length + 1];

    for (int i = 0; i < length; i++) {
        this->data[i] = other.data[i];
    }

    data[length] = '\0';
}

void MyString::free()
{
    delete[] this->data;
}

MyString::MyString()
{
    data = nullptr;
    length = 0;
}

int getLength(const char* data) {
    int i = 0;
    while (data[i] != '\0') {
        i++;
    }
    i++;
    return i;
}

MyString::MyString(const char* _data)
{
    length = getLength(data);
    data = new char[length];
    for (int i = 0; i < length; i++) {
        data[i] = _data[i];
    }
}

MyString::MyString(char* _data, int _length)
{
    int k = 0;
    while (_data[k] != '\0') {
        k++;
    }
    data = new char[k];
    for (int i = 0; i < k; i++) {
        this->data[i] = _data[i];
    }
    length = _length;
}

MyString::MyString(const MyString& other)
{
    copyDynamicMemory(other);
}

MyString::~MyString()
{
    free();
}

MyString& MyString::operator=(const MyString& other)
{
    if (this != &other) {
        free();
        copyDynamicMemory(other);
    }
    return *this;
}

MyString& MyString::operator=(char* other)
{
    if (data != other) {
        free();
        copyDynamicMemory(MyString(other, getLength(other)));
    }
    return *this;
}

bool MyString::operator==(const MyString& other) const
{
    if (length != other.length) return false;
    for (int i = 0; i < length; i++)
        if (data[i] != other.data[i])
            return false;

    return true;
}

MyString& MyString::append(char* other, int length)
{
    char* temp = new char[length + this->length - 1];
    int i = 0;
    while (i < this->length) {
        if (this->data[i] == '\0') {
            break;
        }
        temp[i] = this->data[i];
        i++;
    }
    for (int a = 0; a < length; a++) {
        temp[i] = other[a];
        i++;
    }

    free();
    this->length += length - 1;
    this->data = temp;

    return *this;
}

bool MyString::compare(const MyString& other)
{
    if (length != other.length)
        return false;

    for (int i = 0; i < other.length; i++) {
        if (data[i] != other.data[i])
            return false;
    }
    return true;
}

MyString& MyString::append(const char* other)
{
    int length = getLength(other);
    this->append((char*)other, length);
    return *this;
}

MyString& MyString::append(const MyString& other)
{
    this->append(other.data, other.length);
    return *this;
}

char* MyString::getString() const
{
    return this->data;
}

MyString* stringToArray(const MyString& input, char delimiter, int& outSize)
{
    int segments = 1;
    for (int i = 0; i < input.length; i++) {
        if (input.data[i] == delimiter)
            segments++;
    }

    MyString* res = new MyString[segments];
    outSize = segments;

    int currentWord = 0;
    int currentLength = 0;

    for (int i = 0; i <= input.length; i++) {
        if (input.data[i] == delimiter || input.data[i] == '\0') {
            char* word = new char[currentLength + 1];
            for (int j = 0; j < currentLength; j++) {
                word[j] = input.data[i - currentLength + j];
            }
            word[currentLength] = '\0';

            res[currentWord] = word;
            delete[] word;

            currentWord++;
            currentLength = 0;
        }
        else {
            currentLength++;
        }
    }

    return res;
}

MyString* stringToArray(const MyString& input, char delimiter)
{
    int segments = 1;
    for (int i = 0; i < input.length; i++) {
        if (input.data[i] == delimiter)
            segments++;
    }

    MyString* res = new MyString[segments];

    int currentWord = 0;
    int currentLength = 0;

    for (int i = 0; i <= input.length; i++) {
        if (input.data[i] == delimiter || input.data[i] == '\0') {
            char* word = new char[currentLength + 1];
            for (int j = 0; j < currentLength; j++) {
                word[j] = input.data[i - currentLength + j];
            }
            word[currentLength] = '\0';

            res[currentWord] = word;
            delete[] word;

            currentWord++;
            currentLength = 0;
        }
        else {
            currentLength++;
        }
    }

    return res;
}

bool tryConvertToInt(const char* str, int& result) {
    if (str == nullptr) return false;

    result = 0;
    bool isNegative = false;
    int i = 0;

    if (str[i] == '-') {
        isNegative = true;
        i++;
    }
    else if (str[i] == '+') {
        i++;
    }

    if (str[i] == '\0') return false;

    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9') {
            return false;  
        }
        result = result * 10 + (str[i] - '0');
        i++;
    }

    if (isNegative) result = -result;
    return true;
}

bool convertToString(int num, MyString& res) {
    // Handle 0 explicitly
    if (num == 0) {
        char* str = new char[2];
        str[0] = '0';
        str[1] = '\0';
        res = str;
        delete[] str;
        return true;
    }

    bool isNegative = false;
    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    // Count digits
    int temp = num;
    int length = 0;
    while (temp > 0) {
        temp /= 10;
        length++;
    }

    int totalLength = length + (isNegative ? 1 : 0);
    char* str = new char[totalLength + 1];
    str[totalLength] = '\0';

    for (int i = totalLength - 1; i >= (isNegative ? 1 : 0); i--) {
        str[i] = (num % 10) + '0';
        num /= 10;
    }

    if (isNegative) {
        str[0] = '-';
    }

    res = str;
    delete[] str;
    return true;
}
