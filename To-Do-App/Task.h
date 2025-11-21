#pragma once
#include <string>
#include <vector>
#include "Category.h"
#include <iostream>
using namespace std;

enum Priority { Low, Medium, High };
enum Status { Incomplete, InProgress, Completed };

class Task
{
protected:
int id;
string title;
int categoryId;
string createdDate;
string dueDate;
Priority priority;
Status status;

public:

    Task(int id, string title, string createdDate, string dueDate, Priority priority, int category, Status status)
        : id(id), title(title), createdDate(createdDate), dueDate(dueDate), priority(priority), categoryId(category), status(status) {
    }
    Task(int id, string title, string createdDate, string dueDate, Priority priority, int category)
        : id(id), title(title), createdDate(createdDate), dueDate(dueDate), priority(priority), categoryId(category), status(Incomplete) {
    }

int getId() const;
string getTitle() const;
Priority getPriority() const;
int getCategoryId() const;
Status getStatus() const;
 
void setTitle(string newTitle);
void setCategoryId(int newCategoryId);
void setDueDate(string newDueDate);
void setPriority(Priority newPriority);
void setStatus(Status newStatus);

void printTaskRow(const vector<Category>& categories) const;

friend ostream& operator<<(ostream& os, const Task& task);
};

