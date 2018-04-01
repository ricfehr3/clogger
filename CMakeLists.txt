cmake_minimum_required(VERSION 3.9)
project(clogger C)

set(CMAKE_C_STANDARD 99)

add_library(clogger clogger.c include/clogger.h)