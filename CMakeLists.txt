cmake_minimum_required(VERSION 4.2)
project(WindowsTest)

set(CMAKE_CXX_STANDARD 20)

add_executable(WindowsTest main.cpp)

if (MSVC)
    target_link_options(WindowsTest PRIVATE /SUBSYSTEM:WINDOWS)
ELSE()
    add_compile_options(WindowsTest PRIVATE mwindows)
ENDIF()
