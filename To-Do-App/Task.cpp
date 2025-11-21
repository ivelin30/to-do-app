#include "Task.h"
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int Task::getId() const {
	return id;
}
string Task::getTitle() const {
	return title;
}
Priority Task::getPriority() const  {
	return priority;
}

int Task::getCategoryId() const
{
	return categoryId;
}

Status Task::getStatus() const {
	return status;
}

void Task::setTitle(string newTitle) {
	title = newTitle;
}

void Task::setCategoryId(int newCategoryId) {
	categoryId = newCategoryId;
}

void Task::setDueDate(string newDueDate) {
	dueDate = newDueDate;
}

void Task::setPriority(Priority newPriority) {
	priority = newPriority;
}

void Task::setStatus(Status newStatus) {
	status = newStatus;
}

void Task::printTaskRow(const vector<Category>& categories) const {
	string categoryName = "Uncategorized";
	for (const Category& cat : categories) {
		if (cat.getCatId() == categoryId) {
			categoryName = cat.getCategory();
			break;
		}
	}
	string prioStr = (priority == Low ? "Low" : priority == Medium ? "Medium" : "High");
	string statusStr = (status == Incomplete ? "Incomplete" : status == InProgress ? "In Progress" : "Completed");
	cout << "| "
		<< setw(2) << id << " "
		<< "| " << setw(21) << title.substr(0, 20)
		<< "| " << setw(17) << createdDate
		<< "| " << setw(17) << dueDate
		<< "| " << setw(9) << prioStr
		<< "| " << setw(21) << categoryName
		<< "| " << setw(12) << statusStr
		<< "|" << endl;
}

ostream& operator<<(ostream& os, const Task& task) {
	os << task.id << "," << task.title << "," << task.createdDate << "," << task.dueDate << "," << (task.priority == Low ? "Low" : task.priority == Medium ? "Medium" : "High") << "," << task.categoryId << "," << (task.status == Incomplete ? "Incomplete" : task.status == InProgress ? "In Progress" : "Completed") << endl;
	return os;
}