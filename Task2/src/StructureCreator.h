#ifndef TASK2_STRUCTURECREATOR_H
#define TASK2_STRUCTURECREATOR_H
/** @file */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <zconf.h>

/*!
 * String buffer with size
 */
typedef struct {
    char *buffer;
    size_t size;
} Buffer;
/*!
 * String with len
 */
typedef struct {
    char *str;
    size_t len;
} MyStringView;
/*!
 * MyStringView array with size
 */
typedef struct {
    MyStringView *data;
    int size;
} MyStringViews;

/*!
 * Read from file_name and write in Buffer
 * @param [in] file_name the name of the file to read from
 * @return filled Buffer
 */
Buffer WriteInBuffer(char* file_name);


/*!
 * Create MyStringViews structure with data from the data
 * @param [in] data data to read
 * @return MyStringViews
 */
MyStringViews Create(Buffer *data);

#endif //TASK2_STRUCTURECREATOR_H
