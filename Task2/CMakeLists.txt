cmake_minimum_required(VERSION 3.16)
project(RhymedSort C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(RhymedSort src/main.c src/StructureCreator.c src/StructureCreator.h 
src/Tests.c src/Tests.h src/Sorter.c src/Sorter.h src/Output.c src/Output.h)
