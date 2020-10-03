/** @file */
#include "Sorter.h"
#include "Tests.h"
#include "StructureCreator.h"

int ClassicStringComparator(MyStringView str1, MyStringView str2) {
    assert(str1.str != NULL && str2.str != NULL);
    return strcmp(str1.str, str2.str);
}

int RhytmedStringComparator(MyStringView str1, MyStringView str2) {
    assert(str1.str != NULL && str2.str != NULL);
    int i = str1.len;
    int j = str2.len;
    int min_len = i >= j ? j : i;
    int count = 0;
    while (count < min_len) {
        ++count;
        if (isalpha(str1.str[i]) && isalpha(str2.str[j])) {
            if (str1.str[i] != str2.str[j]) {
                return (unsigned char)str1.str[i] - (unsigned char)str2.str[j];
            }
            --i;
            --j;
        } else {
            if (!isalpha(str1.str[i])) {
                --i;
            }
            if (!isalpha(str2.str[j])) {
                --j;
            }
        }
    }
    return 0;
}

void MyQuickSort(MyStringView *data, int low, int high,  int (*StringComparator)(MyStringView, MyStringView)) {
    assert(data != NULL);
    if (low < high) {
        MyStringView pivot_view;
        pivot_view.str = data[(low + high) / 2].str;
        pivot_view.len = strlen(pivot_view.str);
        int right = high, left = low;
        do {
            while (StringComparator(data[left], pivot_view) < 0) {
                ++left;
            }
            while (StringComparator(data[right], pivot_view) > 0) {
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
