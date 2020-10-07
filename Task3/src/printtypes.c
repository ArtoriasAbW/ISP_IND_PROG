#include"templates.h"

void PrintValue_int(int value) {
    fprintf(stderr, "%d\n", value);
}

void PrintValue_char(char value) {
    fprintf(stderr, "%c\n", value);
}

void PrintValue_short(short value) {
    fprintf(stderr, "%hu\n", value);
}

void PrintValue_double(double value) {
    fprintf(stderr, "%lf\n", value);
}