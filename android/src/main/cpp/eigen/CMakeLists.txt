cmake_minimum_required(VERSION 3.5)

add_library(eigen INTERFACE)
target_include_directories(eigen INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} Eigen)
