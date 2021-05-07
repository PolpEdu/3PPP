cmake_minimum_required(VERSION 3.17)
project(3PPP C)

set(CMAKE_C_STANDARD 99)

add_executable(3PPP structs.h main.c utf8lib/lib-utf8.h utf8lib/lib-utf8.c funcs.h funcs.c)