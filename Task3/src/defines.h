/** @file */

#ifndef DEFINES_H   
#define DEFINES_H 

#define STACKDUMP(stack, TYPE, ok_flag) \
{\
    fprintf(stderr, "stack dump [TYPE = %s]", #TYPE);\
    if (!ok_flag) {\
        fprintf(stderr, "(not ok)");\
        if (stack.data != NULL) {\
            fprintf(stderr, "[%p]", stack.data);\
        }\
    } else {\
        fprintf(stderr, "(ok)[%p]", stack.data);\
    }\
    fprintf(stderr, "[%s:%d in func %s] {\n", __FILE__, __LINE__, __func__);\
    fprintf(stderr, "    size = %ld\n    capacity = %ld\n", stack.size, stack.capacity);\
    if (stack.top_canary == DATA_PROTECTOR_VALUE) {\
        fprintf(stderr, "    struct_top cannary ok\t");\
    } else { \
        fprintf(stderr, "    struct_top cannary corrupted\t");\
    }\
    if (stack.bottom_canary == DATA_PROTECTOR_VALUE) {\
        fprintf(stderr, "struct_bottom cannary ok\n");\
    } else { \
        fprintf(stderr, "struct_bottom cannary corrupted\n");\
    }\
    if (stack.data != NULL) {\
        fprintf(stderr, "    data[%p] {\n", stack.data);\
        if (*((DATA_PROTECTOR_TYPE *)stack.data - 1) == DATA_PROTECTOR_VALUE) {\
            fprintf(stderr, "        data_top cannary ok\t");\
        } else { \
            fprintf(stderr, "        data_top cannary corrupted\t");\
        }\
        if (*(DATA_PROTECTOR_TYPE *)(stack.data + stack.capacity) == DATA_PROTECTOR_VALUE) {\
            fprintf(stderr, "data_bottom cannary ok\n");\
        } else { \
            fprintf(stderr, "data_bottom cannary corrupted\n");\
        }\
        for (ssize_t i = 0; i < stack.size; ++i) {\
            fprintf(stderr, "        *[%ld] = ", i);\
            if (stack.data + i != NULL) {\
                PRINT(TYPE)(stack.data[i]); \
            } else {\
                fprintf(stderr, "ERROR\n");\
            }\
        }\
        fprintf(stderr, "    }\n}\n");\
    }\
}



#define TYPE int
#include "stack.h"
#undef TYPE

#define TYPE double
#include "stack.h"
#undef TYPE

#define TYPE short
#include "stack.h"
#undef TYPE

#define TYPE char
#include "stack.h"
#endif