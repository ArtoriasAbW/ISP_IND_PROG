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

}
