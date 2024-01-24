cmake_minimum_required(VERSION 3.10)

project(IP_FILTER VERSION 0.0.1)

find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

add_executable(ip_filter Lab2/ip_filter.cpp)
add_executable(test Lab2/test.cpp)

file(COPY Lab2/ip_filter.tsv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(test PRIVATE gtest gtest_main pthread)
