cmake_minimum_required(VERSION 3.17)
project(Task2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Task2 main.c TextSorter.c TextSorter.h TestTextSorter.c TestTextSorter.h MyQuickSort.c MyQuickSort.h)