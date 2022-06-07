cmake_minimum_required(VERSION 3.18)

message(STATUS "Initializing exiv2")
add_library(exiv2 INTERFACE)

target_link_libraries(exiv2 INTERFACE debug ${CMAKE_CURRENT_LIST_DIR}/lib/exiv2d.lib optimized ${CMAKE_CURRENT_LIST_DIR}/lib/exiv2.lib)
target_include_directories(exiv2 INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

get_target_property(OUT exiv2 LINK_LIBRARIES)
message(STATUS ${OUT})