cmake_minimum_required(VERSION 3.10)

project(ALLOCATOR VERSION 0.0.1)

add_executable(main Lab3/source/main.cpp)

target_include_directories(main PRIVATE Lab3/course)
