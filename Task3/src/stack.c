/** @file */

#ifdef TYPE

#include "utility.h"

#ifdef STACK_CHECK
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
    if (stack->size > stack->capacity) {
        return SIZE_GREATER_CAPACITY;
    }
#ifdef STACK_CANARY
    if (stack->top_canary != DATA_PROTECTOR_VALUE) {
        return BAD_STRUCT_TOP_PROTECTOR;
    }
    if (stack->bottom_canary != DATA_PROTECTOR_VALUE) {
        return BAD_STRUCT_BOTTOM_PROTECTOR;
    }
    if (*((DATA_PROTECTOR_TYPE *)stack->data - 1) != DATA_PROTECTOR_VALUE) {
        return BAD_DATA_TOP_PROTECTOR;
    }
    if (*(DATA_PROTECTOR_TYPE *)(stack->data + stack->capacity) != DATA_PROTECTOR_VALUE) {
        return BAD_DATA_BOTTOM_PROTECTOR;
    }
#endif
     // TODO: check hash
    return STACK_OK;

}

#endif

void TEMPLATE(StackConstructor, TYPE)(TEMPLATE(Stack, TYPE) *stack, ssize_t capacity) {
#ifdef STACK_CANARY
    int state;
    void *data                         = calloc(capacity * sizeof(TYPE) + 2 * sizeof(DATA_PROTECTOR_TYPE), sizeof(uint8_t)); 
    DATA_PROTECTOR_TYPE *top_canary    = (DATA_PROTECTOR_TYPE *)data;
    DATA_PROTECTOR_TYPE *bottom_canary = (DATA_PROTECTOR_TYPE *)((uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE) + capacity * sizeof(TYPE));
    *top_canary                        = DATA_PROTECTOR_VALUE;
    *bottom_canary                     = DATA_PROTECTOR_VALUE;
    stack->data                        = (TYPE *)((DATA_PROTECTOR_TYPE *)data + 1);
    stack->top_canary                  = DATA_PROTECTOR_VALUE;
    stack->bottom_canary               = DATA_PROTECTOR_VALUE;
#else
    stack->data = (TYPE *)calloc(capacity, sizeof(TYPE));
#endif
    stack->capacity                    = capacity;
    stack->size                        = 0;
#ifdef STACK_CHECK
    if ((state = TEMPLATE(CheckStack, TYPE)(stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
}


void TEMPLATE(StackDestructor, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
#ifdef STACK_CHECK
    int state;
    if ((state = TEMPLATE(CheckStack, TYPE)(stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
#ifdef STACK_CANARY
    free((DATA_PROTECTOR_TYPE *)stack->data - 1);
#else
    free(stack->data);
#endif
    stack->data     = NULL;
    stack->capacity = -1;
    stack->size     = -1;
}


TEMPLATE(Stack, TYPE) TEMPLATE(StackCopyConstructor, TYPE)(TEMPLATE(Stack, TYPE) *old_stack) {
#ifdef STACK_CHECK
    int state;
    if ((state = TEMPLATE(CheckStack, TYPE)(old_stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *old_stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
    TEMPLATE(Stack,TYPE) new_stack;
#ifdef STACK_CANARY
    void *data                         = calloc(old_stack->capacity * sizeof(TYPE) + 2 * sizeof(DATA_PROTECTOR_TYPE), sizeof(uint8_t)); 
    DATA_PROTECTOR_TYPE *top_canary    = (DATA_PROTECTOR_TYPE *)data;
    DATA_PROTECTOR_TYPE *bottom_canary = (DATA_PROTECTOR_TYPE *)((uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE) + old_stack->capacity * sizeof(TYPE));
    *top_canary                        = DATA_PROTECTOR_VALUE;
    *bottom_canary                     = DATA_PROTECTOR_VALUE;
    new_stack.data                     = (TYPE *)((DATA_PROTECTOR_TYPE *)data + 1);
    new_stack.top_canary               = old_stack->top_canary;
    new_stack.bottom_canary            = old_stack->bottom_canary;
#else
    new_stack.data                     = (TYPE *)calloc(old_stack->capacity, sizeof(TYPE));
#endif
    new_stack.capacity                 = old_stack->capacity;
    new_stack.size                     = old_stack->size;
#ifdef STACK_CHECK
    if ((state = TEMPLATE(CheckStack, TYPE)(&new_stack)) != STACK_OK) {
        STACKDUMP(new_stack, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
    return new_stack;
}


void TEMPLATE(Push, TYPE)(TEMPLATE(Stack, TYPE) *stack, TYPE value) {
#ifdef STACK_CHECK
    int state;
    if ((state = TEMPLATE(CheckStack, TYPE)(stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
#ifdef STACK_CANARY
        void *data = realloc((DATA_PROTECTOR_TYPE *)stack->data - 1, stack->capacity * sizeof(TYPE) + 2 * sizeof(DATA_PROTECTOR_TYPE));
#else
        TYPE *data = (TYPE *)realloc(stack->data, stack->capacity * sizeof(*stack->data));
#endif
        if (!data) {
            printf("Cannot realloc new space for stack\n");
            assert(!"Reallocation error");
            exit(-1);
        } else {
#ifdef STACK_CANARY
            DATA_PROTECTOR_TYPE *top_canary    = (DATA_PROTECTOR_TYPE *)data;
            DATA_PROTECTOR_TYPE *bottom_canary = (DATA_PROTECTOR_TYPE *)((uint8_t *)data + sizeof(DATA_PROTECTOR_TYPE) + stack->capacity * sizeof(TYPE));
            *top_canary                        = DATA_PROTECTOR_VALUE;
            *bottom_canary                     = DATA_PROTECTOR_VALUE;
            stack->data                        = (TYPE *)((DATA_PROTECTOR_TYPE *)data + 1);
#else
            stack->data = data;
#endif
        }
    }
    stack->data[stack->size++] = value;
}

TYPE TEMPLATE(ShowLast, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
#ifdef STACK_CHECK
    int state;
    if ((state = TEMPLATE(CheckStack, TYPE)(stack)) != STACK_OK) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, state);
        assert(!"Bad stack");
        exit(-1);
    }
#endif
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