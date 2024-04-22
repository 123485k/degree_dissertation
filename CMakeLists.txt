cmake_minimum_required(VERSION 3.10)

project(modbusapp VERSION 0.1.0)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_subdirectory(3rdparty/modbus)
add_subdirectory(3rdparty/eigen)
add_subdirectory(src)


configure_file(config.h.in config.h)