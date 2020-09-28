/** @file */

#include "Tests.h"
#include "StructureCreator.h"
#include "Sorter.h"
void TestWriteInBuffer() {
    int fd = open("textfiles/text.txt", O_RDWR | O_CREAT, 0755);
    char s[3] = "abc";
    int count = write(fd, s, sizeof(s));
    assert(count == sizeof(s));
    close(fd);
    Buffer buffer = WriteInBuffer("textfiles/text.txt");
    assert(!strcmp(buffer.buffer, s) && buffer.size == strlen(s));
    close(fd);
    free(buffer.buffer);
    printf("Testing WriteInBuffer done.\n");
}

void TestMyQuickSort() {
    size_t size = 4;
    char* s[4] = {"dd", "cc", "aa", "bb"};
    MyStringView *data = calloc(size, sizeof(*data));
    for (size_t i = 0; i < size; ++i) {
        data[i].str = s[i];
        data[i].len = 2;
    }
    MyQuickSort(data, 0, 3, ClassicStringComparator);
    assert(!strcmp(data[0].str, "aa") && !strcmp(data[1].str, "bb") && !strcmp(data[2].str, "cc")
           && !strcmp(data[3].str, "dd"));
    free(data);
    printf("Testing MyQuickSort done.\n");
}

void TestCreate() {

}
