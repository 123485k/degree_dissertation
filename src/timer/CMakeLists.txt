# 编译静态库，暂不添加任何源码。
add_library(timer "")

# 随后用target_sources添加源码。
# 这种方式更好，因为可以更细粒度地访问权限。
# 例如对cpp文件就是PRIVATE，而hpp则是PUBLIC
target_sources(timer
PRIVATE
    # 注：${CMAKE_CURRENT_LIST_DIR}代表当前的CMakeLists.txt文件所在的绝对路径。
    ${CMAKE_CURRENT_LIST_DIR}/timer.cpp
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/timer.hpp
)

# 增加头文件目录
target_include_directories(timer
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

set_property(TARGET timer PROPERTY CXX_STANDARD 20)