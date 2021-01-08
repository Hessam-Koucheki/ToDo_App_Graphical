#include "../include/task.hpp"
#include <string.h>

void Task::set_task(string task)
{
    if (task.length() >= 30)
        strcpy(this->task, (task.substr(0, 29)).c_str());
    else
        strcpy(this->task, task.c_str());
}

string Task::get_task() const
{
    return this->task;
}

void Task::set_favourite(bool t)
{
    this->favourite = t;
}

bool Task::get_favourite() const
{
    if (this->favourite == true)
        return 1;
    else
        return 0;
}

void Task::set_state(bool t)
{
    this->state = t;
}

bool Task::get_state() const
{
    if (this->state == true)
        return 1;
    else
        return 0;
}