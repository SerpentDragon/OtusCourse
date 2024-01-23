cmake_minimum_required(VERSION 3.10)

project(IP_FILTER VERSION 0.0.1)

add_executable(ip_filter ip_filter.cpp)

file(COPY ip_filter.tsv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
