/** @file */

#ifdef TYPE
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
    return stack->data != NULL && stack->size >= 0 && stack->capacity >= stack->size;
}

void TEMPLATE(StackConstructor, TYPE)(TEMPLATE(Stack, TYPE) *stack, ssize_t capacity) {
    stack->data     = (TYPE *)calloc(capacity, sizeof(*stack->data));
    stack->capacity = capacity;
    stack->size     = 0;
    if (!TEMPLATE(CheckStack, TYPE)(stack)) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, 0);
        assert(!"Bad stack");
        exit(-1);
    }
}


void TEMPLATE(StackDestructor, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
    if (!TEMPLATE(CheckStack, TYPE)(stack)) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, 0);
        assert(!"Bad stack");
        exit(-1);
    }
    free(stack->data);
    stack->data = NULL;
    stack->capacity = -1;
    stack->size     = -1;
}


TEMPLATE(Stack, TYPE) TEMPLATE(StackCopyConstructor, TYPE)(TEMPLATE(Stack, TYPE) *old_stack) {
    if (!TEMPLATE(CheckStack, TYPE)(old_stack)) {
        TEMPLATE(Stack, TYPE) tmp = *old_stack;
        STACKDUMP(tmp, TYPE, 0);
        assert(!"Bad stack");
        exit(-1);
    }
    TEMPLATE(Stack,TYPE) new_stack;
    new_stack.capacity = old_stack->capacity;
    new_stack.size = old_stack->size;
    new_stack.data = (TYPE *)calloc(old_stack->capacity, sizeof(*new_stack.data));
    if (!TEMPLATE(CheckStack, TYPE)(&new_stack)) {
        STACKDUMP(new_stack, TYPE, 0);
        assert(!"Bad stack");
        exit(-1);
    }
    return new_stack;
}


void TEMPLATE(Push, TYPE)(TEMPLATE(Stack, TYPE) *stack, TYPE value) {
    if (!TEMPLATE(CheckStack, TYPE)(stack)) {
        TEMPLATE(Stack, TYPE) tmp = *stack;
        STACKDUMP(tmp, TYPE, 0);
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

TYPE TEMPLATE(ShowLast, TYPE)(TEMPLATE(Stack, TYPE) *stack) {
    if (!TEMPLATE(CheckStack, TYPE)(stack)) {
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