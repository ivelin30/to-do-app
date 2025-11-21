#include "Category.h"
#include <iostream>
#include <iomanip>

using namespace std;

int Category::getCatId() const { return catId; }
string Category::getCategory() const { return category; }

void Category::printCategoryRow() const {
	cout << "| " << setw(2) << catId << " | " << setw(23) << category << " |\n";
}

ostream& operator<<(ostream& os, const Category& category) {
	os << category.catId << "," << category.category << endl;
	return os;
}