#include "StructureCreator.h"
#include "Sorter.h"
#include "Tests.h"

int main() {
    TestWriteInBuffer();
    TestMyQuickSort();
    Buffer buffer = WriteInBuffer("onegin.txt");
    MyStringViews strings = Create(&buffer);
    printf("\n");
    MyQuickSort(strings.data, 0, strings.size - 1, ClassicStringComparator);
    printf("\n\n");
    for (int i = 0; i < strings.size; ++i) {
        printf("%s\n", strings.data[i].str);
    }
    free(buffer.buffer);
    free(strings.data);
    return 0;
}
