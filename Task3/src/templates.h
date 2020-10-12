/** @file */
#include <stdio.h>
#ifndef TEMPLATES_H_
#define TEMPLATES_H_

#define CAT(X,Y) X##_##Y
#define TEMPLATE(X,Y) CAT(X,Y)


#define PRINT(TYPE) PrintValue_##TYPE 

void PrintValue_int(int value);
void PrintValue_char(char value);

void PrintValue_short(short value);

void PrintValue_double(double value);

#endif 