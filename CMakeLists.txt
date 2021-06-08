cmake_minimum_required(VERSION 3.17)
project(PPPTrabalho3 C)

set(CMAKE_C_STANDARD 99)

add_executable(PPPTrabalho3_mainparte2 mainPARTE2.c funcsPARTE2.h funcsPARTE2.c)
add_executable(PPPTrabalho3 mainPARTE1.c funcsPARTE1.h funcsPARTE1.c)
