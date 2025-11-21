#pragma once
#include <string>
using namespace std;

class Category
{
protected:
	int catId;
	string category;
public:
	Category(int catId, string category) : catId(catId), category(category) {}
	
	int getCatId() const;
	string getCategory() const;
	void printCategoryRow() const;

	friend ostream& operator<<(ostream& os, const Category& category);
};

