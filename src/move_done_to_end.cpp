#include "../include/move_done_to_end.hpp"
#include <vector>

void move_done_to_end(std::vector<Task> &vec)
{
    size_t number_of_done_tasks = 0;
    for (auto const &it : vec)
    {
        number_of_done_tasks += it.get_state();
    }


    size_t attempts = 0;
    for (size_t i = 0;; i++)
    {
        if (vec[i].get_state() == true)
        {
            vec.push_back(vec[i]);
            vec.erase(vec.begin() + i);
            attempts++;
            i--;
        }
        if (attempts == number_of_done_tasks)
            break;
    }
}