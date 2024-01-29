cmake_minimum_required(VERSION 3.10)

project(modbusapp VERSION 0.1.0)
include(cmake/modbus.cmake)
file(GLOB_RECURSE PROJECT_SRCS "src/*.c" "src/*.cpp")

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SRCS}
)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE modbus
)
configure_file(config.h.in config.h)