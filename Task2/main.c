#include "StructureCreator.h"
#include "Sorter.h"
#include "Tests.h"

int main() {
    TestReadInBuffer();
    TestMyQuickSort();
    Buffer buffer = WriteInBuffer();
    MyStringViews strings = Create(&buffer);
    printf("\n");
    for (int i = 0; i < strings.size; ++i) {
        printf("%s\n", strings.data[i].str);
    }
    MyQuickSort(strings.data, 0, strings.size - 1, ClassicStringComparator);
    printf("\n\n");
    for (int i = 0; i < strings.size; ++i) {
        printf("%s\n", strings.data[i].str);
    }
    return 0;
}
