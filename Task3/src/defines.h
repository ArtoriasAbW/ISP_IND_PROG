/** @file */

#ifndef DEFINES_H   
#define DEFINES_H 

#include <stdint.h>

/*!
* Dumps the state of the stack on stderr
*/

#ifdef STACK_CHECK
#define STACKDUMP(stack, TYPE, state) \
{\
    PRINTTYPE(TYPE)();\
    if (state != STACK_OK) {\
        fprintf(stderr, "(not ok) ERROR:%s", state_table[state]);\
        if (stack.data != NULL) {\
            fprintf(stderr, "[%p]", stack.data);\
        }\
    } else {\
        fprintf(stderr, "(ok)[%p]", stack.data);\
    }\
    fprintf(stderr, "[%s:%d in func %s] {\n", __FILE__, __LINE__, __func__);\
    fprintf(stderr, "    size = %ld\n    capacity = %ld\n", stack.size, stack.capacity);\
    if (stack.data != NULL) {\
        fprintf(stderr, "    data[%p] {\n", stack.data);\
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
#endif


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
#undef TYPE

#define TYPE uint64_t
#include "stack.h"
#undef TYPE


#define TYPE int64_t
#include "stack.h"
#undef TYPE


#define TYPE uint32_t
#include "stack.h"
#undef TYPE

#endif