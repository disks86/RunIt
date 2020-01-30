cmake_minimum_required(VERSION 3.15)
project(RunIt)

set(CMAKE_CXX_STANDARD 20)

add_executable(RunIt main.cpp Executable.cpp Executable.h COFFHeader.h OptionalHeaderStandardFields.h OptionalHeaderWindowsSpecificFields.h)