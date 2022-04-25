cmake_minimum_required(VERSION 3.0)
project(minesweeper CXX)

## C++14 Rocks!
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
else()
    set(CMAKE_BUILD_TYPE Debug)
endif()

SET ( CMAKE_INSTALL_PREFIX ../ )

add_subdirectory(src)
