cmake_minimum_required(VERSION 3.15)
project(forthinterpreter C)

set(CMAKE_C_STANDARD 99)

add_executable(forthinterpreter main.c wordlib.c stack.c stack.h list.h list.c context.h context.c util.h wordlib.h)