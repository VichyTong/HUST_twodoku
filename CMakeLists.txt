cmake_minimum_required(VERSION 3.22)
project(HUST_twodoku)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(HUST_twodoku
        src/cnfparser.cpp
        src/main.cpp src/head/head.h src/linkedlist.cpp src/head/linkedlist.h src/head/cnfparser.h src/solver.cpp src/head/solver.h src/initsudoku.cpp src/head/initsudoku.h src/heap.cpp src/head/heap.h)
