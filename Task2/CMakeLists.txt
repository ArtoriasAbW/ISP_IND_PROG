cmake_minimum_required(VERSION 3.17)
project(Task2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Task2 main.c StructureCreator.c StructureCreator.h Tests.c Tests.h Sorter.c Sorter.h)