cmake_minimum_required(VERSION 3.0)
project(ToDo)
set(CMAKE_CXX_STANDARD 11)
set(SOURCES
    src/main.cpp
    src/app.cpp
    src/add.cpp
    src/task.cpp
    src/write_file.cpp
    src/read_file.cpp
    src/move_done_to_end.cpp
)
include_directories(include)
add_executable(app ${SOURCES})
target_link_libraries(app sfml-window sfml-system sfml-graphics -lsfml-audio)