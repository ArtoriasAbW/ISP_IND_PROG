//
// Created by pavel on 13.09.2020.
//

#ifndef TASK2_MYQUICKSORT_H
#define TASK2_MYQUICKSORT_H

#include <stddef.h>
#include <memory.h>
#include "TextSorter.h"
#include "TestTextSorter.h"

typedef struct {
    char** str;
    size_t len;
} MyStringView;

void MyQuickSort(MyStringView* data, size_t low, size_t high);
#endif //TASK2_MYQUICKSORT_H
