# cmake 版本
cmake_minimum_required(VERSION 3.26)
# 语言
project(windem008)
# c语言标准
set(CMAKE_C_STANDARD 17)

# 设置源文件地址 file(GLOB/GLOB_RECURSE(递归) 变量名 要搜索的文件路径和文件类型)
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# 设置头文件地址
file(GLOB HEADER ${CMAKE_CURRENT_SOURCE_DIR}/*.h)


# 包含头文件
#include_directories(
#        ../os/win32
#        ../core
#)


## 连接静态库的路径--os,core库 link_libraries(<static lib> [<static lib>...])
#link_directories(
#        ${OS_LIB_PATH}
#        ${CORE_LIB_PATH}
#)
## 连接到静态库--os,core
#link_libraries(
#        ${OS_LIB_NAME}
#        ${CORE_LIB_NAME}
#)


#可执行文件
add_executable(windem008 ${SRC})
