cmake_minimum_required(VERSION 3.8)
project(File_System)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c globaluti.h InterfaceFunc.c syscalls.c utifunc.c grouplinkmethod.c)
add_executable(File_System ${SOURCE_FILES})