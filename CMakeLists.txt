cmake_minimum_required(VERSION 4.0)
project(DS_PJ)

set(CMAKE_CXX_STANDARD 17)

add_executable(DS_PJ main.cpp
        Entity/Road.cpp
        Entity/Road.h
        Entity/Demand.cpp
        Entity/Demand.h
        Entity/Graph.cpp
        Entity/Graph.h
        Entity/Map.cpp
        Entity/Map.h
        Tool/FileList.cpp
        Tool/FileList.h)
