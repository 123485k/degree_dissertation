aux_source_directory(. SRC_LIST)
add_subdirectory(modbus-server)
add_subdirectory(phymodule)
add_subdirectory(timer)
add_executable(
    ${PROJECT_NAME}
    ${SRC_LIST}
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${PROJECT_NAME}
PRIVATE
    modbus-server
    phymodule
    timer
)
