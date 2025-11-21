#include "ToDoManager.h"
#include "Task.h"
#include <ctime>

void ToDoManager::addTask(string title, string date, Priority prio, int catId) {
	int newId = tasks.size() + 1;
	time_t now = time(0);
	tm local;
	localtime_s(&local, &now);
	string createdDate = to_string(1900 + local.tm_year) + "-" +
		to_string(1 + local.tm_mon) + "-" +
		to_string(local.tm_mday) + " " +
		to_string(local.tm_hour) + ":" +
		to_string(local.tm_min);
	
	tasks.push_back(Task(newId, title, createdDate , date, prio, catId));
	cout << "Task added successfully.\n";
}

void ToDoManager::deleteTask(int id) {
	tasks.erase(remove_if(tasks.begin(), tasks.end(),
		[id](Task& t) { return t.getId() == id; }), tasks.end());
	cout << "Task deleted successfully.\n";

}

void ToDoManager::editTask(int id, string title, string date, Priority prio, int catId) {
	for (Task& task : tasks) {
		if (task.getId() == id) {
			if (title != "")
				task.setTitle(title);
			if (date != "")
				task.setDueDate(date);
			task.setPriority(prio);
			if (catId != 0)
				task.setCategoryId(catId);
			return;
		}
	}
	cout << "Task edited successfully.\n";
}

void ToDoManager::changeTaskStatus(int id, Status status) {
	for (Task& task : tasks) {
		if (task.getId() == id) {
			task.setStatus(status);
			return;
		}
	}
	cout << "Task status changed successfully.\n";
}

vector<Task> ToDoManager::searchByTitle(string keyword) {
	vector<Task> results;
	for (const Task& task : tasks) {
		if (task.getTitle().find(keyword) != string::npos) {
			results.push_back(task);
		}
	}
	return results;
}

vector<Task> ToDoManager::filterByCategory(int catId) {
	vector<Task> results;
	for (const Task& task : tasks) {
		if (task.getCategoryId() == catId) {
			results.push_back(task);
		}
	}
	return results;
}

vector<Task> ToDoManager::filterByPriority(Priority prio) {
	vector<Task> results;
	for (const Task& task : tasks) {
		if (task.getPriority() == prio) {
			results.push_back(task);
		}
	}
	return results;
}

void ToDoManager::addCategory(string name)
{
	categories.push_back(Category(nextCategoryId, name));
	nextCategoryId++;
}
void ToDoManager::deleteCategory(int id)
{
	categories.erase(remove_if(categories.begin(), categories.end(),
		[id](Category& c) { return c.getCatId() == id; }), categories.end());
}
