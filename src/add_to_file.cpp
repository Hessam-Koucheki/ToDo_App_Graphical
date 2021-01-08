#include "../include/add_to_file.hpp"
#include "../include/task.hpp"
#include <iostream>
#include <fstream>

using std::endl;

void add_to_file(const Task &task)
{
    std::ofstream out("../db.dat", std::ios::out | std::ios::app);
    if ( !out.is_open() ){
        out.open("../db.dat", std::ios::out | std::ios::app);
    } else {
        out.close();
        out.open("../db.dat", std::ios::out | std::ios::app);
    }

    out << task.get_task() << ";" << task.get_favourite() << task.get_state() << endl;
    out.close();
}