/** @file */

#ifdef TYPE

#include "utility.h"

/*!
* Dumps the state of the stack on stderr
*/
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


int TEMPLATE(CheckStack, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
    if (stack->capacity < 0) {
        return BAD_CAPACITY;
    }
    if (stack->size < 0) {
        return BAD_SIZE;
    }
    if (stack->data == NULL) {
        return BAD_DATA;
    }
    if (stack->top_canary != DATA_PROTECTOR_VALUE) {
        return BAD_STRUCT_TOP_PROTECTOR;
    }
    if (stack->bottom_canary != DATA_PROTECTOR_VALUE) {
        return BAD_STRUCT_BOTTOM_PROTECTOR;
    }
    if (stack->size > stack->capacity) {
        return SIZE_GREATER_CAPACITY;
    }
    if (*((DATA_PROTECTOR_TYPE *)stack->data - 1) != DATA_PROTECTOR_VALUE) {
        return BAD_DATA_TOP_PROTECTOR;
    }
    if (*(DATA_PROTECTOR_TYPE *)(stack->data + stack->capacity) != DATA_PROTECTOR_VALUE) {
        return BAD_DATA_BOTTOM_PROTECTOR;
    }
     // TODO: check hash
    return STACK_OK;

}

void TEMPLATE(StackConstructor, TYPE)(TEMPLATE(Stack, TYPE) *stack, ssize_t capacity) {
    void *data                         = calloc(capacity * sizeof(TYPE) + 2 * sizeof(DATA_PROTECTOR_TYPE), sizeof(uint8_t)); 
    DATA_PROTECTOR_TYPE *top_canary    = (DATA_PROTECTOR_TYPE *)data;
    DATA_PROTECTOR_TYPE *bottom_canary = (DATA_PROTECTOR_TYPE *)((uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE) + capacity * sizeof(TYPE));
    *top_canary                        = DATA_PROTECTOR_VALUE;
    *bottom_canary                     = DATA_PROTECTOR_VALUE;
    stack->data                        = (TYPE *)((DATA_PROTECTOR_TYPE *)data + 1);
    stack->capacity                    = capacity;
    stack->size                        = 0;
    stack->top_canary                  = DATA_PROTECTOR_VALUE;
    stack->bottom_canary               = DATA_PROTECTOR_VALUE;
    if (TEMPLATE(CheckStack, TYPE)(stack) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, 0);

        assert(!"Bad stack");
        exit(-1);
    }
}


void TEMPLATE(StackDestructor, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
    if (TEMPLATE(CheckStack, TYPE)(stack) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, 0);
        assert(!"Bad stack");
        exit(-1);
    }
    free((DATA_PROTECTOR_TYPE *)stack->data - 1);
    stack->data     = NULL;
    stack->capacity = -1;
    stack->size     = -1;
}


TEMPLATE(Stack, TYPE) TEMPLATE(StackCopyConstructor, TYPE)(TEMPLATE(Stack, TYPE) *old_stack) {
    if (TEMPLATE(CheckStack, TYPE)(old_stack) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *old_stack;
        STACKDUMP(tmp, TYPE, 0);
        assert(!"Bad stack");
        exit(-1);
    }
    TEMPLATE(Stack,TYPE) new_stack;
    void *data                         = calloc(old_stack->capacity * sizeof(TYPE) + 2 * sizeof(DATA_PROTECTOR_TYPE), sizeof(uint8_t)); 
    DATA_PROTECTOR_TYPE *top_canary    = (DATA_PROTECTOR_TYPE *)data;
    DATA_PROTECTOR_TYPE *bottom_canary = (DATA_PROTECTOR_TYPE *)((uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE) + old_stack->capacity * sizeof(TYPE));
    *top_canary                        = DATA_PROTECTOR_VALUE;
    *bottom_canary                     = DATA_PROTECTOR_VALUE;
    new_stack.capacity                 = old_stack->capacity;
    new_stack.size                     = old_stack->size;
    new_stack.data                     = (TYPE *)((DATA_PROTECTOR_TYPE *)data + 1);
    new_stack.top_canary               = old_stack->top_canary;
    new_stack.bottom_canary            = old_stack->bottom_canary;
    if (TEMPLATE(CheckStack, TYPE)(&new_stack) != STACK_OK) {
        STACKDUMP(new_stack, TYPE, 0);
        assert(!"Bad stack");
        exit(-1);
    }
    return new_stack;
}


void TEMPLATE(Push, TYPE)(TEMPLATE(Stack, TYPE) *stack, TYPE value) {
    if (TEMPLATE(CheckStack, TYPE)(stack) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, 0);
        assert(!"Bad stack");
        exit(-1);
    }
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        void *data = realloc((DATA_PROTECTOR_TYPE *)stack->data - 1, stack->capacity * sizeof(TYPE) + 2 * sizeof(DATA_PROTECTOR_TYPE));
        if (!data) {
            printf("Cannot realloc new space for stack\n");
            assert(!"Reallocation error");
            exit(-1);
        } else {
            DATA_PROTECTOR_TYPE *top_canary    = (DATA_PROTECTOR_TYPE *)data;
            DATA_PROTECTOR_TYPE *bottom_canary = (DATA_PROTECTOR_TYPE *)((uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE) + stack->capacity * sizeof(TYPE));
            *top_canary                        = DATA_PROTECTOR_VALUE;
            *bottom_canary                     = DATA_PROTECTOR_VALUE;
            stack->data = (TYPE *)((DATA_PROTECTOR_TYPE *)data + 1);
        }
    }
    stack->data[stack->size++] = value;
}

TYPE TEMPLATE(ShowLast, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
    if (TEMPLATE(CheckStack, TYPE)(stack) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, 0);
        assert(!"Bad stack");
        exit(-1);
    }
    if (stack->size < 1) {
        assert(!"Stack is empty");
        printf("Stack is empty. Nothing to show(pop).\n"); //for release
        return (TYPE)1;
    }
    return stack->data[stack->size - 1];
}

TYPE TEMPLATE(Pop, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
    TYPE value = TEMPLATE(ShowLast, TYPE)(stack);
    stack->size--;
    return value;
}

#endif