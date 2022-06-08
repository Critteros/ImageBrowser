cmake_minimum_required(VERSION 3.18)

message(STATUS "Initializing FreeImage")
add_library(FreeImage INTERFACE)

target_link_libraries(FreeImage INTERFACE debug ${CMAKE_CURRENT_LIST_DIR}/FreeImageLibd.lib optimized ${CMAKE_CURRENT_LIST_DIR}/FreeImageLib.lib)
target_include_directories(FreeImage INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_compile_definitions(FreeImage INTERFACE -DFREEIMAGE_LIB)

get_target_property(OUT FreeImage LINK_LIBRARIES)
message(STATUS ${OUT})