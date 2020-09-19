//
// Created by pavel on 13.09.2020.
//

#ifndef TASK2_SORTER_H
#define TASK2_SORTER_H

#include <stddef.h>
#include <memory.h>
#include <ctype.h>
#include "StructureCreator.h"

int ClassicStringComparator(const char *str1, const char *str2);

int RhytmedStringComparator(const char *str1, const char* str2);

void MyQuickSort(MyStringView* data, int low, int high, int (*StringComparator)(const char*, const char*));
#endif //TASK2_SORTER_H
