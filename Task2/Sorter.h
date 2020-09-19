//
// Created by pavel on 13.09.2020.
//

#ifndef TASK2_SORTER_H
#define TASK2_SORTER_H

#include <stddef.h>
#include <memory.h>
#include "StructureCreator.h"

int ClassicStringComparator(char *str1, char *str2);

void MyQuickSort(MyStringView* data, size_t low, size_t high, int (*StringComparator)(char*, char*));
#endif //TASK2_SORTER_H
