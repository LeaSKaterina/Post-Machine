cmake_minimum_required(VERSION 3.15)
project(PostMachine)

set(CMAKE_CXX_STANDARD 14)

add_executable(PostMachine main.cpp PostMachineLibrary.cpp PostMachineLibrary.h Rules.h Rules.cpp Rules.h catch.hpp Tests.h)