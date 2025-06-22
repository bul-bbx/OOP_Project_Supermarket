#pragma once
#include "MyString.h"
#include <iostream>


class Warning
{
	int id;
	int senderId;
	int receiverId;
	MyString description;
	int severity;
public:
	Warning();
	Warning(Warning& const other);
	Warning(int _id, int _senderId, int _receiverId, MyString _description, int _severity);

	int getSenderId();
	int getReceiverId();
	MyString getDescription();
	int getId();
	int getSeverity();
	void printWarning();

};

