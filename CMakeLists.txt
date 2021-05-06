cmake_minimum_required(VERSION 3.17)
project(PPPTrabalho3 C)

set(CMAKE_C_STANDARD 99)

add_executable(PPPTrabalho3 structs.h main.c utf8lib/lib-utf8.h utf8lib/lib-utf8.c funcs.h funcs.c)