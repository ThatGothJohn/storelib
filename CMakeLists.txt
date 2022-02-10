cmake_minimum_required(VERSION 3.21)
project(storelib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(HashMap)

add_library(storelib STATIC
        HashMap/hashmap.cpp
        HashMap/hashmap.h)
