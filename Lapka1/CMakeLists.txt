cmake_minimum_required(VERSION 3.10)
project(ConsoleApplication12)

set(CMAKE_CXX_STANDARD 11)

include_directories(ConsoleApplication12)
include_directories(ConsoleApplication12/Debug)

add_executable(ConsoleApplication12
        ConsoleApplication12/Debug/ConsoleApplication12.pch
        ConsoleApplication12/ConsoleApplication12.cpp
        ConsoleApplication12/pch.cpp
        ConsoleApplication12/pch.h
        ConsoleApplication12/Screen.h
        ConsoleApplication12/Shape.h)
