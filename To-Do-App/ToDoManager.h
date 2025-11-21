#pragma once
#include <string>
#include <vector>
#include "Task.h"
#include "Category.h"

using namespace std;


class ToDoManager
{
protected:
	vector<Task> tasks;
	vector<Category> categories;
	int nextTaskId = 1;
	int nextCategoryId = 1;

public:
	void addCategory(string name);
	void deleteCategory(int id);
	void addTask(string title, string date, Priority prio, int catId);
	void deleteTask(int id);
	void editTask(int id, string title, string date, Priority prio, int catId);
	void changeTaskStatus(int id, Status status);
	vector<Task> searchByTitle(string keyword);
	vector<Task> filterByCategory(int catId);
	vector<Task> filterByPriority(Priority prio);
	
};

