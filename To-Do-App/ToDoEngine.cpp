#include "ToDoEngine.h"
#include "DisplayPanels.cpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void ToDoEngine::run() {
    mainMenu();
}

void ToDoEngine::saveDataToFiles() {
    ofstream file("tasks.csv");
    if (!file) { cout << "Error opening tasks.csv for writing.\n"; return; }
    for (const Task& task : tasks) {
        file << task;
    }
    file.close();

    ofstream catFile("category.csv");
    if (!catFile) { cout << "Error opening category.csv for writing.\n"; return; }
    for (const Category& category : categories) {
        catFile << category;
    }
    catFile.close();

    cout << "Data saved!\n";
}

void ToDoEngine::loadDataFromFiles() {
    ifstream file("tasks.csv");
    if (!file) { cout << "Error opening tasks.csv for reading.\n"; return; }

    tasks.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string part;
        vector<string> parts;
        while (getline(ss, part, ',')) parts.push_back(part);
        if (parts.size() == 7) {
            int id = stoi(parts[0]);
            string title = parts[1];
            string createdDate = parts[2];
            string dueDate = parts[3];
            Priority prio = (parts[4] == "Low" ? Low : parts[4] == "Medium" ? Medium : High);
            int catId = stoi(parts[5]);
            Status status = (parts[6] == "Incomplete" ? Incomplete : parts[6] == "In Progress" ? InProgress : Completed);
            tasks.push_back(Task(id, title, createdDate, dueDate, prio, catId, status));
            nextTaskId = max(nextTaskId, id + 1);
        }
    }
    file.close();

    ifstream catFile("category.csv");
    if (!catFile) { cout << "Error opening category.csv for reading.\n"; return; }
    categories.clear();
    while (getline(catFile, line)) {
        stringstream ss(line);
        string part;
        vector<string> parts;
        while (getline(ss, part, ',')) parts.push_back(part);
        if (parts.size() == 2) {
            int catId = stoi(parts[0]);
            string categoryName = parts[1];
            categories.push_back(Category(catId, categoryName));
            nextCategoryId = max(nextCategoryId, catId + 1);
        }
    }
    catFile.close();

    cout << "Data loaded!\n";
}

void ToDoEngine::exit() {
    saveDataToFiles();
    cout << "Exiting To-Do App. Goodbye!\n";
}

void ToDoEngine::mainMenu() {
    int option;
    while (true) {
        displayMainPanel();
        cout << "Select option: ";
        if (!(cin >> option)) { cin.clear(); cin.ignore(1000, '\n'); option = -1; }
        switch (option) {
        case 1: taskList(); break;
        case 2: searchFilterMenu(); break;
        case 3: categoryMenu(); break;
        case 9: loadDataFromFiles(); break;
        case 0: exit(); return;
        default: cout << "Invalid option. Try again.\n"; break;
        }
    }
}

void ToDoEngine::taskList() {
    int option;
    while (true) {
        displayTaskPanel(tasks, categories);
        cout << "Select option: ";
        if (!(cin >> option)) { cin.clear(); cin.ignore(1000, '\n'); option = -1; }
        switch (option) {
        case 1: addTask(); break;
        case 2: deleteTask(); break;
        case 3: editTask(); break;
        case 4: searchFilterMenu(); break;
        case 5: changeTaskStatus(); break;
        case 0: return;
        default: cout << "Invalid option. Try again.\n"; break;
        }
    }
}

void ToDoEngine::addTask() {
    cin.ignore(1000, '\n');
    string title;
    while (title.empty()) {
        cout << "Enter task title: ";
        getline(cin, title);
        if (title.empty()) cout << "Title cannot be empty. Try again.\n";
    }

    string dueDate;
    while (dueDate.empty()) {
        cout << "Enter due date (YYYY-MM-DD HH-MM): ";
        getline(cin, dueDate);
        if (dueDate.empty()) cout << "Due date cannot be empty. Try again.\n";
    }

    int prioOption = 0;
    while (prioOption < 1 || prioOption > 3) {
        cout << "Select priority:\n1. Low\n2. Medium\n3. High\nYour choice: ";
        if (!(cin >> prioOption)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
    }
    Priority priority = static_cast<Priority>(prioOption - 1);

    int catId = 0;
    while (true) {
        displayCategoryPanel(categories, false);
        cout << "Enter category ID (0 for Uncategorized): ";
        if (!(cin >> catId)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (catId == 0) break;
        bool valid = false;
        for (const Category& c : categories) if (c.getCatId() == catId) { valid = true; break; }
        if (valid) break;
        cout << "Invalid category ID. Try again.\n";
    }

    ToDoManager::addTask(title, dueDate, priority, catId);
	saveDataToFiles();
}

void ToDoEngine::deleteTask() {
    if (tasks.empty()) { cout << "No tasks available to delete.\n"; return; }
    int taskId;
    while (true) {
        cout << "Enter task ID to delete (0-EXIT): ";
        if (!(cin >> taskId)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (taskId == 0) return;
        bool valid = false;
        for (const Task& t : tasks) if (t.getId() == taskId) { valid = true; break; }
        if (valid) break;
        cout << "Invalid task ID. Try again.\n";
    }
    ToDoManager::deleteTask(taskId);
	saveDataToFiles();
}

void ToDoEngine::editTask() {
    int id;
    cout << "Enter task ID to edit: ";
    if (!(cin >> id)) { cin.clear(); cin.ignore(1000, '\n'); cout << "Invalid ID.\n"; return; }

    Task* task = nullptr;
    for (Task& t : tasks) if (t.getId() == id) { task = &t; break; }
    if (!task) { cout << "Task not found.\n"; return; }

    cin.ignore(1000, '\n');
    cout << "Leave fields empty to keep current value.\n";

    cout << "New title: ";
    string newTitle; getline(cin, newTitle);
    if (newTitle.empty()) newTitle = "";

    cout << "New due date: ";
    string newDate; getline(cin, newDate);
    if (newDate.empty()) newDate = "";

    int prioOption = 0;
    while (prioOption < 0 || prioOption > 3) {
        cout << "Select new priority (1. Low, 2. Medium, 3. High, 0-Keep Current): ";
        if (!(cin >> prioOption)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (prioOption == 0) break;
    }
    Priority newPriority = (prioOption == 0) ? task->getPriority() : static_cast<Priority>(prioOption - 1);

    int newCatId = 0;
    while (true) {
        displayCategoryPanel(categories, false);
        cout << "Enter new category ID (0 - Keep Current): ";
        if (!(cin >> newCatId)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (newCatId == 0) break;
        bool valid = false;
        for (const Category& c : categories) if (c.getCatId() == newCatId) { valid = true; break; }
        if (valid) break;
        cout << "Invalid category ID. Try again.\n";
    }

    ToDoManager::editTask(id, newTitle, newDate, newPriority, newCatId);
	saveDataToFiles();
}

void ToDoEngine::changeTaskStatus() {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    int taskId;
    while (true) {
        cout << "Enter task ID to delete (0-EXIT): ";
        if (!(cin >> taskId)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (taskId == 0) return;
        bool valid = false;
        for (const Task& t : tasks) if (t.getId() == taskId) { valid = true; break; }
        if (valid) break;
        cout << "Invalid task ID. Try again.\n";
    }

    int option = 0;
    while (option < 1 || option > 3) {
        cout << "Select new status:\n1. Incomplete\n2. In Progress\n3. Completed\nYour choice: ";
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    Status newStatus = static_cast<Status>(option - 1);
    ToDoManager::changeTaskStatus(taskId, newStatus);
       

}

// --- Category Menu ---
void ToDoEngine::categoryMenu() {
    int option;
    while (true) {
        displayCategoryPanel(categories);
        cout << "Select option: ";
        if (!(cin >> option)) { cin.clear(); cin.ignore(1000, '\n'); option = -1; }
        switch (option) {
        case 1: addCategory(); break;
        case 2: deleteCategory(); break;
        case 0: return;
        default: cout << "Invalid option. Try again.\n"; break;
        }
    }
}

void ToDoEngine::addCategory() {
    cin.ignore(1000, '\n');
    string name;
    while (name.empty()) { cout << "Enter category name: "; getline(cin, name); }
    ToDoManager::addCategory(name);
	saveDataToFiles();
}

void ToDoEngine::deleteCategory() {
    if (categories.empty()) { cout << "No categories to delete.\n"; return; }
    int catId;
    while (true) {
        cout << "Enter category ID to delete (0-EXIT): ";
        if (!(cin >> catId)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (catId == 0) return;
        bool valid = false;
        for (const Category& c : categories) if (c.getCatId() == catId) { valid = true; break; }
        if (valid) break;
        cout << "Invalid category ID. Try again.\n";
    }
    ToDoManager::deleteCategory(catId);
	saveDataToFiles();
}

// --- Search & Filter ---
void ToDoEngine::searchFilterMenu() {
    int option;
    displaySearchFilterPanel();
    cout << "Select option: ";
    if (!(cin >> option)) { cin.clear(); cin.ignore(1000, '\n'); option = -1; }
    switch (option) {
    case 1: searchByTitle(); break;
    case 2: filterByCategory(); break;
    case 3: filterByPriority(); break;
    case 4: return;
    default: break;
    }
}

void ToDoEngine::searchFilterTaskList(vector<Task> filterTasks, string type, string search) {
    int option;
    displayFilteredAndSearchTasksPanel(filterTasks, categories, type, search);
    cout << "Select option: ";
    if (!(cin >> option)) { cin.clear(); cin.ignore(1000, '\n'); option = -1; }
    switch (option) {
    case 1: addTask(); break;
    case 2: deleteTask(); break;
    case 3: editTask(); break;
    case 4: searchFilterMenu(); break;
    default: break;
    }
}

void ToDoEngine::searchByTitle() {
    cin.ignore(1000, '\n');
    string keyword;
    cout << "Enter keyword to search: ";
    getline(cin, keyword);
    if (keyword.empty()) { cout << "Keyword cannot be empty.\n"; return; }
    searchFilterTaskList(ToDoManager::searchByTitle(keyword), "SEARCH BY TITLE", keyword);
}

void ToDoEngine::filterByCategory() {
    int catId = 0;
    string cat;
    while (true) {
        displayCategoryPanel(categories, false);
        cout << "Enter category ID to filter: ";
        if (!(cin >> catId)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        if (catId == 0) return;
        bool valid = false;
        for (const Category& c : categories) if (c.getCatId() == catId) { valid = true; cat = c.getCategory(); break; }
        if (valid) break;
        cout << "Invalid category ID. Try again.\n";
    }

    searchFilterTaskList(ToDoManager::filterByCategory(catId), "FILTER BY CATEGORY", cat);
}

void ToDoEngine::filterByPriority() {
    int prioOption = 0;
    
    while (prioOption < 1 || prioOption > 3) {
        cout << "Select priority to filter:\n1. Low\n2. Medium\n3. High\nYour choice: ";
        if (!(cin >> prioOption)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
    }
    Priority priority = static_cast<Priority>(prioOption - 1);
    searchFilterTaskList(ToDoManager::filterByPriority(priority), "FILTER BY PRIORITY", (priority == Low ?"Low" :priority == Medium ?"Medium" :"High"));
}
