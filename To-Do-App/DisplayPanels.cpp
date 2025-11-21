#include <iostream>
#include <iomanip>
#include <vector>
#include "Task.h"

using namespace std;

static void displayMainPanel() {
	cout << "+----- TO-DO APP -----+\n";
	cout << "| 1-VIEW TASKS        |\n";
	cout << "| 2-SEARCH & FILTER   |\n";
	cout << "| 3-MANAGE CATEGORY   |\n";
	cout << "+---------------------+\n";
	cout << "| 9-LOAD FROM FILE    |\n";
	cout << "| 0-SAVE & EXIT       |\n";
	cout << "+---------------------+\n";
	cout << "| Dev: Ivelin Lukanov |\n";
	cout << "+---------------------+\n";

}
 
static void displayTaskPanel(const vector<Task>& tasks,const vector<Category>& category) {
	cout << "+-----------------------------------------------------------------------------------------------------------------+\n";
	cout << "|                                                   TASK LIST                                                     |\n";
	cout << "+----+----------------------+------------------+------------------+----------+----------------------+-------------+\n";
	cout << "| ID |        Title         |   Created Date   |     Due Date     | Priority |      Category        |   Status    |\n";
	cout << "+----+----------------------+------------------+------------------+----------+----------------------+-------------+\n";
	for (const Task& task : tasks) {
		task.printTaskRow(category);
		cout << "+----+----------------------+------------------+------------------+----------+----------------------+-------------+\n";
	}
	cout << "| 1-ADD TASK | 2-DELETE TASK | 3-EDIT TASK | 4-SEARCH & FILTER | 5-CHANGE STATUS |                       | 0-BACK |\n";
	cout << "+------------+---------------+-------------+-------------------+-----------------+-----------------------+--------+\n";
}

static void displayCategoryPanel(const vector<Category>& categories, bool hasControls = true) {
	cout << "+------------------------------+\n";
	cout << "|         CATEGORY LIST        |\n";
	cout << "+----+-------------------------+\n";
	cout << "| ID |        Category         |\n";
	cout << "+----+-------------------------+\n";
	for (const Category& cat : categories) {
		cat.printCategoryRow();
		cout << "+----+-------------------------+\n";
	}
	if (hasControls) {
		cout << "| 1-ADD | 2-DELETE |    0-BACK |\n";
		cout << "+-------+----------+-----------+\n";
	}
}

static void displaySearchFilterPanel() {
	cout << "+---------------------------+\n";
	cout << "|     SEARCH & FILTER       |\n";
	cout << "+---------------------------+\n";
	cout << "| 1-SEARCH BY TITLE         |\n";
	cout << "| 2-FILTER BY CATEGORY      |\n";
	cout << "| 3-FILTER BY PRIORITY      |\n";
	cout << "| 4-UNSET SEARCH & FILTER   |\n";
	cout << "+---------------------------+\n";
	cout << "|          0-BACK           |\n";
	cout << "+---------------------------+\n";
}

static void displayFilteredAndSearchTasksPanel(const vector<Task>& tasks, const vector<Category>& category, string type, string search = "") {
	cout << "+-----------------------------------------------------------------------------------------------------------------+\n";
	cout << "                                     "<< type << " " << search << " LIST                                \n";
	cout << "+----+----------------------+------------------+------------------+----------+----------------------+-------------+\n";
	cout << "| ID |        Title         |   Created Date   |     Due Date     | Priority |      Category        |   Status    |\n";
	cout << "+----+----------------------+------------------+------------------+----------+----------------------+-------------+\n";
	for (const Task& task : tasks) {
		task.printTaskRow(category);
		cout << "+----+----------------------+------------------+------------------+----------+----------------------+-------------+\n";
	}
	cout << "| 1-ADD TASK | 2-DELETE TASK | 3-EDIT TASK | 4-SEARCH & FILTER | 5-CHANGE STATUS |                       | 0-BACK |\n";
	cout << "+------------+---------------+-------------+-------------------+-----------------+-----------------------+--------+\n";
}