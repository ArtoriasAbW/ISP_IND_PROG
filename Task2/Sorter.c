//
// Created by pavel on 13.09.2020.
//

#include "Sorter.h"
#include "Tests.h"
#include "StructureCreator.h"

int ClassicStringComparator(char *str1, char *str2) {
    return strcmp(str1, str2);
}

void MyQuickSort(MyStringView *data, size_t low, size_t high,  int (*StringComparator)(char*, char*)) {
    if (low < high) {
        char *pivot = data[(low + high) / 2].str;
        int right = high, left = low;
        do {
            while (StringComparator(data[left].str, pivot) < 0) {
                ++left;
            }
            while (StringComparator(data[right].str, pivot) > 0) {
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
        MyQuickSort(data, low, right, StringComparator);
        MyQuickSort(data, left, high, StringComparator);
    }
}