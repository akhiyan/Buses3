cmake_minimum_required(VERSION 3.27)
project(Buses3)

set(CMAKE_CXX_STANDARD 23)

add_executable(Buses3 main.cpp
        include/Bus.h
        include/City.h
        include/Road.h
        include/Crossroad.h
        include/Crossroad.h
        realizations/Bus.cpp
        realizations/City.cpp
        realizations/Crossroad.cpp
        realizations/Road.cpp)
