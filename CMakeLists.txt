# cmake 版本
cmake_minimum_required(VERSION 3.26)
# 语言
project(Win32-learning)

# c语言标准
set(CMAKE_CXX_STANDARD 20)


# 包含头文件
#include_directories(
#        ./EasyX_4/include
#)


# 连接静态库的路径--os,core库 link_libraries(<static lib> [<static lib>...])
#link_directories(
#        ./EasyX_4/lib64
#)
## 连接到静态库--os,core
#link_libraries(
#        libeasyx.a
#)

#可执行文件
#add_executable(Win32-learning win32learnig/windem001/main.cpp)

# 添加子目录
add_subdirectory(win32learnig/windem001)
add_subdirectory(win32learnig/windem002)
add_subdirectory(win32learnig/windem003)
add_subdirectory(win32learnig/windem004)

#if (WIN32)
#    add_definitions(-D_WIN32_WINNT=0x0601)
#endif ()
#
#if (WIN32)
#    set(CMAKE_MFC_FLAG 2)
#    add_definitions(-D_AFXDLL)
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")
#ENDIF ()

