//
// Created by pavel on 13.09.2020.
//

#include "TestTextSorter.h"
#include "TextSorter.h"
#include "MyQuickSort.h"
void TestReadInBuffer() {
    int fd = open("text.txt", O_RDWR | O_CREAT);
    int value = 7;
    write(fd, &value, sizeof(value));
    close(fd);
    fd = open("text.txt", O_RDONLY);
    int buf;
    read(fd, &buf, sizeof(buf));
    assert(buf == value);
    close(fd);
    printf("Testing ReadInBuffer done.\n");
}

void TestMyQuickSort() {
    size_t size = 4;
    char* s[4] = {"dd", "cc", "aa", "bb"};
    MyStringView *data = calloc(size, sizeof(*data));
    for (int i = 0; i < size; ++i) {
        data[i].str = &s[i];
        data[i].len = 2;
    }
    MyQuickSort(data, 0, 3);
    assert(!strcmp(*data[0].str, "aa") && !strcmp(*data[1].str, "bb") && !strcmp(*data[2].str, "cc")
           && !strcmp(*data[3].str, "dd"));
    free(data);
    printf("Testing MyQuickSort done.\n");
}
