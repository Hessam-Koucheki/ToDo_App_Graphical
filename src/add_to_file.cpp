#include "../include/add_to_file.hpp"
#include "../include/task.hpp"
#include <iostream>
#include <fstream>
#include <vector>
using std::endl;
using std::vector;

void add_to_file(vector<Task> &vec)
{
    std::ofstream out("../db.dat", std::ios::out);
    if (!out.is_open())
    {
        out.open("../db.dat", std::ios::out);
    }
    else
    {
        out.close();
        out.open("../db.dat", std::ios::out);
    }
    for (auto const &task : vec)
        out << task.get_task() << ";" << task.get_favourite() << ' ' << task.get_state() << endl;
    out.close();
}