/** @file */

#include "StructureCreator.h"

Buffer WriteInBuffer(char* file_name) {
    assert(file_name != NULL);
    char* buffer = NULL;
    int f_descriptor = open(file_name, O_RDONLY);
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
    Buffer buf;
    buf.buffer = buffer;
    buf.size = statistics.st_size;
    return buf;
}

MyStringViews Create(Buffer *buffer) {
    assert(buffer != NULL);
    int capacity = 20;
    MyStringView *lines = calloc(capacity, sizeof(*lines));
    if (lines == NULL) {
        printf("Cannot allocate memory.\n");
        exit(1);
    }
    int cur_size = 0;
    for (size_t i = 0; i < buffer->size;) {
        lines[cur_size].str = &buffer->buffer[i];
        lines[cur_size].len = 0;
        while (buffer->buffer[i] != '\n') {
            ++i;
            ++lines[cur_size].len;
        }
        buffer->buffer[i] = '\0';
        ++i;
        ++cur_size;
        if (cur_size == capacity - 1) {
            capacity *= 2;
            MyStringView* new_lines = realloc(lines, capacity * sizeof(*new_lines));
            if (!new_lines) {
                free(lines);
                printf("Allocation error.");
                exit(1);
            }
            lines = new_lines;
        }
    }
    MyStringViews res;
    res.data = lines;
    res.size = cur_size;
    return res;
}
