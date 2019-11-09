cmake_minimum_required(VERSION 3.12)
project(project3)

set(CMAKE_CXX_STANDARD 11)

add_executable(project3 mainChain.cpp testMain.cpp logic_unit.cpp logic_unit_tests.cpp)