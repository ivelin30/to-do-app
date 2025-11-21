#pragma once
#include "ToDoManager.h"

class ToDoEngine : public ToDoManager
{
public:
	ToDoEngine() {
		loadDataFromFiles();
	};

	void run();
	void exit();
	void loadDataFromFiles();
	void saveDataToFiles();

	void mainMenu();

	void taskList();
	void addTask();
	void deleteTask();
	void editTask();
	void changeTaskStatus();

	void categoryMenu();
	void addCategory();
	void deleteCategory();

	void searchFilterMenu();
	void searchFilterTaskList(vector<Task> filterTasks, string type, string search);
	void searchByTitle();
	void filterByCategory();
	void filterByPriority();
};

