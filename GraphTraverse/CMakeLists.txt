cmake_minimum_required(VERSION 3.15)
project(GraphTraverse)

set(CMAKE_CXX_STANDARD 14)

add_executable(GraphTraverse main.cpp PathNumFinder.h SlidingPuzzle.h CityPaths.h
        StringTransfer.h SingleSourcePathFinder.h PathNumFinderDp.h
        CityPathsFinder.h)