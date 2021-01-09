#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../include/read_file.hpp"
#include "../include/task.hpp"

using std::ifstream;
using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;

void read_file(vector<Task> vec)
{
    ifstream in("../db.dat", std::ios::in);
    Task tmp_task;
    string task;
    bool fav, state;

    while (!in.eof())
    {
        getline(in, task, ';');
        tmp_task.set_task(task);
        in >> fav >> state;
        tmp_task.set_favourite(fav);
        tmp_task.set_state(state);
        vec.push_back(tmp_task);
        in.ignore();
    }
    
    in.clear();
    in.close();
}