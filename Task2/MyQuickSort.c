//
// Created by pavel on 13.09.2020.
//

#include "MyQuickSort.h"
#include "TestTextSorter.h"
#include "TextSorter.h"

void MyQuickSort(MyStringView *data, size_t low, size_t high) {
    if (low < high) {
        char *pivot = *data[(low + high) / 2].str;
        int right = high, left = low;
        do {
            while (strcmp(*data[left].str, pivot) < 0) {
                ++left;
            }
            while (strcmp(*data[right].str, pivot) > 0) {
                --right;
            }
            if (left <= right) {
                MyStringView *tmp = calloc(1, sizeof(MyStringView));
                tmp->str = data[left].str;
                tmp->len = data[left].len;
                data[left].str = data[right].str;
                data[left].len = data[right].len;
                data[right].str = tmp->str;
                data[right].len = tmp->len;
                ++left;
                --right;
                free(tmp);
            }
        } while (left <= right);
        MyQuickSort(data, low, right);
        MyQuickSort(data, left, high);
    }
}