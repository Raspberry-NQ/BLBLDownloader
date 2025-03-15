cmake_minimum_required(VERSION 3.23)
project(findnumberFile)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "-fexec-charset=GBK -finput-charset=UTF-8")
add_executable(findnumberFile main.cpp)

add_executable(main main.cpp)
set(CMAKE_EXE_LINKER_FLAGS -static)