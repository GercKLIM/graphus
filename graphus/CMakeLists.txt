cmake_minimum_required(VERSION 3.27)
project(VK_Algorithms_hw1)

set(CMAKE_CXX_STANDARD 17)

add_executable(main-test
        main.cpp
        include/IGraph.h
        include/ListGraph.h
        include/MatrixGraph.h
        include/SetGraph.h
        include/ArcGraph.h
        src/ListGraph.cpp
        src/MatrixGraph.cpp
        src/SetGraph.cpp
        src/ArcGraph.cpp
        tests/graph_test.cpp
        tests/graph_test.h
)