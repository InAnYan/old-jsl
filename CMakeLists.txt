cmake_minimum_required(VERSION 3.22)

project(JSL)

find_package(Boost REQUIRED)

add_subdirectory(JSLLib)
add_subdirectory(JSLExe)
