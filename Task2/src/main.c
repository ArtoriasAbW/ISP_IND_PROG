/** @file */
#include "StructureCreator.h"
#include "Sorter.h"
#include "Tests.h"
#include "Output.h"

int main(int argc, char **argv) {
    TestWriteInBuffer();
    TestMyQuickSort();
    Buffer buffer = WriteInBuffer("hamlet.txt");
    MyStringViews strings = Create(&buffer);
    WriteInFile(strings, "source_hamlet.txt");
    MyQuickSort(strings.data, 0, strings.size - 1, ClassicStringComparator);
    WriteInFile(strings, "sorted_hamlet.txt");
    MyQuickSort(strings.data, 0, strings.size - 1, RhytmedStringComparator);
    WriteInFile(strings, "rhymed_hamlet.txt");
    free(buffer.buffer);
    free(strings.data);
    return 0;
}
