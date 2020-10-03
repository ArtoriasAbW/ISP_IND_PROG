#include <sys/types.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// move constuctor may be added and doxygen??

typedef struct Stack {
    ssize_t size;
    ssize_t capacity;
    TYPE *data;
} Stack;

int CheckStack(Stack *stack) {
    return stack->data != NULL && stack->size >= 0 && stack->capacity >= stack->size;
}

void StackConstructor(Stack *stack, ssize_t capacity) {
    stack->data     = (TYPE *)calloc(capacity, sizeof(*stack->data));
    stack->capacity = capacity;
    stack->size     = 0;
    if (!CheckStack(stack)) {
        assert(!"Bad stack");
        exit(-1);
    }
}


void StackDestructor(Stack *stack) {
    if (!CheckStack(stack)) {
        assert(!"Bad stack");
        exit(-1);
    }
    free(stack->data);
    stack->capacity = -1;
    stack->size     = -1;
}


Stack StackCopyConstructor(Stack *old_stack) {
    if (!CheckStack(old_stack)) {
        assert(!"Bad stack");
        exit(-1);
    }
    Stack new_stack;
    new_stack.capacity = old_stack->capacity;
    new_stack.size = old_stack->size;
    new_stack.data = (TYPE *)calloc(old_stack->capacity, sizeof(*new_stack.data));
    if (!CheckStack(&new_stack)) {
        assert(!"Bad stack");
        exit(-1);
    }
    return new_stack;
}


void Push(Stack *stack, TYPE value) {
    if (!CheckStack(stack)) {
        assert(!"Bad stack");
        exit(-1);
    }
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        TYPE *new_data = (TYPE *)realloc(stack->data, stack->capacity * sizeof(*stack->data));
        if (!new_data) {
            printf("Cannot realloc new space for stack\n");
            assert(!"Reallocation error");
            exit(-1);
        } else {
            stack->data = new_data;
        }
    }
    stack->data[stack->size++] = value;
}

TYPE* Pop(Stack *stack) {
    if (!CheckStack(stack)) {
        assert(!"Bad stack");
        exit(-1);
    }
    if (stack->size < 1) {
        assert(!"Stack is empty");
        exit(-1);
    }
    return &stack->data[--stack->size];
}


TYPE ShowLast(Stack *stack) {
    if (!CheckStack(stack)) {
        assert(!"Bad stack");
        exit(-1);
    }
    if (stack->size < 1) {
        assert(!"Stack is empty");
        exit(-1);
    }
    return stack->data[--stack->size];
}