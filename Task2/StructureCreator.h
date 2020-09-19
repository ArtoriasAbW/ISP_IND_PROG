//
// Created by pavel on 13.09.2020.
//

#ifndef TASK2_STRUCTURECREATOR_H
#define TASK2_STRUCTURECREATOR_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <zconf.h>



typedef struct {
    char *buffer;
    size_t size;
}Buffer;

typedef struct {
    char* str;
    size_t len;
} MyStringView;

typedef struct {
    MyStringView* data;
    int size;
}MyStringViews;

Buffer WriteInBuffer();
MyStringViews Create(Buffer* data);

#endif //TASK2_STRUCTURECREATOR_H
