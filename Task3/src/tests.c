/** @file */

#include "defines.h"


void TestPushPopInt() {
    TEMPLATE(Stack, int) stack;
    ssize_t capacity = 20;
    TEMPLATE(StackConstructor, int)(&stack, capacity);
    assert(stack.size == 0 && stack.capacity == capacity && stack.data != NULL);
    for (int i = 0; i < 30; ++i) {
        TEMPLATE(Push, int)(&stack, i);
    }
    assert(stack.size == 30 && stack.capacity == 40 && stack.data != NULL);
    for (int i = 29; i >= 0; --i) {
        assert(TEMPLATE(Pop, int)(&stack) == i);
    }
    TEMPLATE(StackDestructor, int)(&stack);
    fprintf(stderr, "Test PushPopInt done.\n");
}

void TestPushPopDouble() {
    TEMPLATE(Stack, double) stack;
    ssize_t capacity = 5;
    TEMPLATE(StackConstructor, double)(&stack, capacity);
    assert(stack.size == 0 && stack.capacity == capacity && stack.data != NULL);
    TEMPLATE(Push, double)(&stack, 2.323);
    TEMPLATE(Push, double)(&stack, 3.323);
    TEMPLATE(Push, double)(&stack, 4.323);
    TEMPLATE(Push, double)(&stack, 5.323);
    TEMPLATE(Push, double)(&stack, 6.777);
    assert(stack.size == capacity && stack.capacity == capacity && stack.data != NULL);
    assert(TEMPLATE(Pop, double)(&stack) == 6.777);
    assert(TEMPLATE(Pop, double)(&stack) == 5.323);
    assert(TEMPLATE(Pop, double)(&stack) == 4.323);
    assert(TEMPLATE(Pop, double)(&stack) == 3.323);
    assert(TEMPLATE(Pop, double)(&stack) == 2.323);
    assert(stack.size == 0 && stack.capacity == capacity);
    TEMPLATE(StackDestructor, double)(&stack);
    fprintf(stderr, "Test PushPopDouble done.\n");
}


void TestCopyConstructor() {
    TEMPLATE(Stack, short) stack;
    ssize_t capacity = 10;
    TEMPLATE(StackConstructor, short)(&stack, capacity);
    for (short i = 0; i < 2 * capacity; ++i) {
        TEMPLATE(Push, short)(&stack, i);
    }
    TEMPLATE(Stack, short) new_stack = TEMPLATE(StackCopyConstructor, short)(&stack);
    assert(stack.capacity == new_stack.capacity && stack.size == new_stack.size);

    printf("%lx", *(DATA_PROTECTOR_TYPE *)(new_stack.data - 1));
    TEMPLATE(StackDestructor, short)(&stack);
    TEMPLATE(StackDestructor, short)(&new_stack);
    fprintf(stderr, "Test CopyConstructor done.\n");

}

void TestDestructor() {
    TEMPLATE(Stack, char) stack;
    ssize_t capacity = 10;
    TEMPLATE(StackConstructor, char)(&stack, capacity);
    TEMPLATE(StackDestructor, char)(&stack);
    assert(stack.data == NULL && stack.size == -1 && stack.capacity == -1);
    fprintf(stderr, "Test Destructor done\n");
}


int main() {
    TestPushPopInt();
    TestPushPopDouble();
    TestCopyConstructor();
    TestDestructor();
}