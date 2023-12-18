cmake_minimum_required(VERSION 3.22)
project(JSLLib)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-gdwarf-4)

add_library(JSLLib
        include/JSLLib/Header.hpp
        src/Header.cpp)
target_include_directories(JSLLib PRIVATE include)
set_target_properties(JSLLib PROPERTIES LINKER_LANGUAGE CXX)

