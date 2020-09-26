cmake_minimum_required(VERSION 3.16)
project(RhymedSort C)

set(CMAKE_C_STANDARD 11)

add_executable(RhymedSort main.c StructureCreator.c StructureCreator.h Tests.c Tests.h Sorter.c Sorter.h Output.c Output.h)
