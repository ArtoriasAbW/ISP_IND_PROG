/** @file */
#include "StructureCreator.h"
#include "Sorter.h"
#include "Output.h"

int main(void) {
    Buffer buffer = WriteInBuffer("textfiles/hamlet.txt");
    MyStringViews strings = Create(&buffer);
    WriteInFile(strings, "textfiles/source_hamlet.txt");
    MyQuickSort(strings.data, 0, strings.size - 1, ClassicStringComparator);
    WriteInFile(strings, "textfiles/sorted_hamlet.txt");
    MyQuickSort(strings.data, 0, strings.size - 1, RhytmedStringComparator);
    WriteInFile(strings, "textfiles/rhymed_hamlet.txt");
    free(buffer.buffer);
    free(strings.data);
    return 0;
}
