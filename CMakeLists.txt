cmake_minimum_required(VERSION 3.9)
project(clogger_test C)

set(CMAKE_C_STANDARD 99)

add_executable(clogger_test main.c clogger.c clogger.h)