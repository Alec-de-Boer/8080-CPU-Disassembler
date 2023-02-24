cmake_minimum_required(VERSION 3.24)
project(8080Disassembler)

set(CMAKE_CXX_STANDARD 20)

include_directories("boost_1_80_0")
include_directories("include")
include_directories("rom")


add_executable(8080Disassembler src/main.cpp src/opCodeInitilization.h src/opCodeInitilization.cpp)