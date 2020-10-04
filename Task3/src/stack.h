#include <sys/types.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "templates.h"

// move constuctor may be added and doxygen??

#ifdef TYPE

typedef struct TEMPLATE(Stack, TYPE) {
    ssize_t size;
    ssize_t capacity;
    TYPE *data;
} TEMPLATE(Stack, TYPE);

int TEMPLATE(CheckStack, TYPE)(TEMPLATE(Stack, TYPE) *stack);

void TEMPLATE(StackConstructor, TYPE)(TEMPLATE(Stack, TYPE) *stack, ssize_t capacity);

void TEMPLATE(StackDestructor, TYPE)(TEMPLATE(Stack, TYPE) *stack);

TEMPLATE(Stack, TYPE) TEMPLATE(StackCopyConstructor, TYPE)(TEMPLATE(Stack, TYPE) *old_stack);


void TEMPLATE(Push, TYPE)(TEMPLATE(Stack, TYPE) *stack, TYPE value);

TYPE* TEMPLATE(Pop, TYPE)(TEMPLATE(Stack, TYPE) *stack);


TYPE TEMPLATE(ShowLast, TYPE)(TEMPLATE(Stack, TYPE) *stack);
#endif