cmake_minimum_required(VERSION 3.15)
project(Hamiltonian)

set(CMAKE_CXX_STANDARD 14)

add_executable(Hamiltonian main.cpp HamiltonianLoop.cpp HamiltonianLoop.h Graph.cpp Graph.h)