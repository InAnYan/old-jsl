cmake_minimum_required(VERSION 3.22)
project(JSLLib)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-gdwarf-4)

add_executable(JSLExe
        src/main.cpp)
target_include_directories(JSLExe PRIVATE ../JSLLib/include)
target_link_libraries(JSLExe JSLLib)
