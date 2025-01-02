cmake_minimum_required(VERSION 3.10)

project(modbusapp)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
add_subdirectory(src)