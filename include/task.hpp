#pragma once

#include <string>

using std::string;

class Task
{
public:
    void set_task(string);
    string get_task();
    void set_favourite(bool);
    bool get_favourite();
    void set_state(bool);
    bool get_state();

private:
    bool state = false;
    bool favourite = false;
    char task[60] = "";
};