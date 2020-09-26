/** @file */
#include "Sorter.h"
#include "Tests.h"
#include "StructureCreator.h"

int ClassicStringComparator(const char *str1, const char *str2) {
    return strcmp(str1, str2);
}

int RhytmedStringComparator(const char *str1, const char* str2) {
    int number_of_symbols = 3;
    assert(str1 != NULL && str2 != NULL);
    int i = strlen(str1) - 1;
    int j = strlen(str2) - 1;
    int count = 0;
    while (str1[i] != *str1 && str2[j] != *str2) {
        if (isalpha(str1[i]) && isalpha(str2[j])) {
            ++count;
            if (str1[i] != str2[j]) {
                return (unsigned char)str1[i] - (unsigned char)str2[j];
            }
            --i;
            --j;
        } else {
            if (!isalpha(str1[i])) {
                --i;
            }
            if (!isalpha(str2[j])) {
                --j;
            }
        }
        if (count == number_of_symbols) {
            break;
        }
    }
    return 0;
}

void MyQuickSort(MyStringView *data, int low, int high,  int (*StringComparator)(const char*, const char*)) {
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