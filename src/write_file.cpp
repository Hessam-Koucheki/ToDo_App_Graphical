#include "../include/write_file.hpp"
#include "../include/task.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
using std::endl;
using std::vector;

void write_file(vector<Task> &vec)
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
    out.flush();
    out.close();
}