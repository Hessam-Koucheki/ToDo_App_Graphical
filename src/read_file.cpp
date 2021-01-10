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

// A function to avoid re-read contents from file
// Actully it controls if a task has been added to vector 
// and prevents adding it again.
bool search(const string t ,const vector<Task> & v ){
    for (size_t i = 0; i < v.size(); i++)
    {
        if ( t == v[i].get_task() )
            return true;
    }
    return false;
}


void read_file(vector<Task> & vec)
{
    ifstream in;
    in.open("../db.dat", std::ios::in | std::ios::app);
    Task tmp_task;
    string task;
    bool fav, state;

    while (!in.eof())
    {
        // skip if there is an empty line
        getline(in, task, ';');
        if( task == "" ){
            continue;
        }
        if ( search(task, vec) == false ){
            tmp_task.set_task(task); // reads TASK from file
            in >> fav >> state; // reads first-int(fav) and then second-int(is_done)
            tmp_task.set_favourite(fav);
            tmp_task.set_state(state);
            vec.push_back(tmp_task); // adds task to the vector
            in.ignore();
        } else {
            in.ignore(4);  // Ignore :      ; int int '\n 
        }
    }
    in.clear();
    in.close();
}