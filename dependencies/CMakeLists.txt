cmake_minimum_required(VERSION 3.22)

add_library(dependencies INTERFACE)

add_subdirectory(exiv2)

target_link_libraries(dependencies INTERFACE exiv2)