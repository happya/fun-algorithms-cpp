cmake_minimum_required(VERSION 3.13)
project(GraphBasic)

set(CMAKE_CXX_STANDARD 14)

add_executable(GraphBasic main.cpp AdjMatrix.h AdjList.h AdjSet.h Graph.h)