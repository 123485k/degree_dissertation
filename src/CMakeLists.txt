aux_source_directory(. SRC_LIST)
add_subdirectory(modbus-server)
add_subdirectory(phymodule)
add_subdirectory(timer)
add_executable(
    ${PROJECT_NAME}
    ${SRC_LIST}
)
find_package(CLI11 CONFIG REQUIRED)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)
target_link_libraries(${PROJECT_NAME}
PRIVATE
    modbus-server
    phymodule
    timer
    CLI11::CLI11
)
