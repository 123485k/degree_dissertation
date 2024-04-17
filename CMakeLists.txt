cmake_minimum_required(VERSION 3.10)

project(modbusapp VERSION 0.1.0)
include(cmake/modbus.cmake)
file(GLOB_RECURSE PROJECT_SRCS "src/*.c" "src/*.cpp")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SRCS}
)
add_subdirectory(3rdparty/eigen)
target_link_libraries(${PROJECT_NAME} PRIVATE modbus Eigen3::Eigen)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
configure_file(config.h.in config.h)