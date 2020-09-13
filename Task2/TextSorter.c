//
// Created by pavel on 13.09.2020.
//

#include "TextSorter.h"

char* ReadInBuffer() {
    char* buffer = NULL;
    int f_descriptor = open("file.txt", O_RDONLY);
    if (f_descriptor == -1) {
        printf("Failed to open file.\nExit.\n");
        exit(1);
    }
    struct stat statistics;

    if (fstat(f_descriptor, &statistics) != -1) {
        buffer = (char *)calloc(statistics.st_size, sizeof(char));
    }
    if (read(f_descriptor, buffer, statistics.st_size) != statistics.st_size) {
        printf("Failed to read %ld bytes.\nExit.\n", statistics.st_size);
        exit(1);
    }
    close(f_descriptor);
    return buffer;
}