#ifndef TASK2_SORTER_H
#define TASK2_SORTER_H
/** @file */

#include <stddef.h>
#include <memory.h>
#include <ctype.h>
#include "StructureCreator.h"
/*!
 * Compares strings in lexicographic order
 * @param [in] str1 first string
 * @param [in] str2 second string
 * @return 0 if str1 == str2, value is greater than 0 if str1 > str2, else value less than 0
 */
int ClassicStringComparator(const char *str1, const char *str2);

/*!
 * Compares strings in rhymed order(for details implementation)
 * @param [in] str1
 * @param [in] str2
 * @return 0 if str1 == str2, value is greater than 0 if str1 > str2, else value less than 0
 */
int RhytmedStringComparator(const char *str1, const char* str2);

/*!
 * Classic QuickSort for MyStringView array with custom comparator
 * @param [in,out] data
 * @param [in] low
 * @param [in] high
 * @param [in] StringComparator
 */
void MyQuickSort(MyStringView* data, int low, int high, int (*StringComparator)(const char*, const char*));
#endif //TASK2_SORTER_H
