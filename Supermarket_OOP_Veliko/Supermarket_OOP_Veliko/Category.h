#pragma once
class Category
{
	int id;
	char* name;
	char* description;
private:
	void CopyFrom(Category* const category);
	void free();
public:
	Category();
	Category(int id, char* name, char* description);
	~Category();
};

