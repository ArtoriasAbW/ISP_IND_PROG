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
  char str[30] = "Hello world\nfoo\nC++\nRussia\n";
  Buffer buffer;
  buffer.buffer = str;
  buffer.size = strlen(str);
  MyStringViews strings = Create(&buffer);
  assert(!strcmp(strings.data[0].str, "Hello world") && !strcmp(strings.data[1].str, "foo"));
  assert(!strcmp(strings.data[2].str, "C++") && !strcmp(strings.data[3].str, "Russia"));
  free(strings.data);
  printf("Testing Create done.\n");
}


