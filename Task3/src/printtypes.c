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


void PrintValue_uint64_t(uint64_t value) {
    fprintf(stderr, "%lu\n", value);
}


void PrintValue_int64_t(int64_t value) {
    fprintf(stderr, "%ld\n", value);
}


void PrintValue_uint32_t(uint32_t value) {
    fprintf(stderr, "%u\n", value);
}

void PrintTypename_double() {
    fprintf(stderr, "stack dump [TYPE = double]");
}

void PrintTypename_int() {
    fprintf(stderr, "stack dump [TYPE = int]");
}

void PrintTypename_short() {
    fprintf(stderr, "stack dump [TYPE = short]");
}

void PrintTypename_char() {
    fprintf(stderr, "stack dump [TYPE = char]");
}


void PrintTypename_uint64_t() {
    fprintf(stderr, "stack dump [TYPE = uint64_t]");
}


void PrintTypename_int64_t() {
    fprintf(stderr, "stack dump [TYPE = int64_t]");
}

void PrintTypename_uint32_t() {
    fprintf(stderr, "stack dump [TYPE = uint32_t]");
}