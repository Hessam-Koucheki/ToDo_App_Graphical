#include "../include/task.hpp"
#include <string.h>

void Task::set_task(string task)
{
    if (task.length() >= 60)
        strcpy(this->task, (task.substr(0, 59)).c_str());
    else
        strcpy(this->task, task.c_str());
}

string Task::get_task()
{
    return this->task;
}

void Task::set_favourite(bool t)
{
    this->favourite = t;
}

bool Task::get_favourite()
{
    return this->favourite;
}

void Task::set_state(bool t)
{
    this->state = t;
}

bool Task::get_state()
{
    return this->state;
}