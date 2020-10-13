/** @file */
#ifndef TEMPLATES_H_
#define TEMPLATES_H_
#include <stdint.h>
#include <stdio.h>
#define CAT(X,Y) X##_##Y
#define TEMPLATE(X,Y) CAT(X,Y)


#define PRINT(TYPE) PrintValue_##TYPE 

void PrintValue_int(int value);
void PrintValue_char(char value);
void PrintValue_short(short value);
void PrintValue_double(double value);
void PrintValue_uint64_t(uint64_t value);
void PrintValue_int64_t(int64_t value);
void PrintValue_uint32_t(uint32_t value);


#define PRINTTYPE(TYPE) PrintTypename_##TYPE


void PrintTypename_double();
void PrintTypename_int();
void PrintTypename_short();
void PrintTypename_char();
void PrintTypename_uint64_t();
void PrintTypename_int64_t();
void PrintTypename_uint32_t();



#endif 