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
        assert(*TEMPLATE(Pop, int)(&stack) == i);
    }
    printf("Test PushPopInt done.\n");
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
    assert(*TEMPLATE(Pop, double)(&stack) == 6.777);
    assert(*TEMPLATE(Pop, double)(&stack) == 5.323);
    assert(*TEMPLATE(Pop, double)(&stack) == 4.323);
    assert(*TEMPLATE(Pop, double)(&stack) == 3.323);
    assert(*TEMPLATE(Pop, double)(&stack) == 2.323);
    printf("Test PushPopDouble done.\n");
}


void TestStackDestructor() {

}


void TestCopyConstructor() {

}


int main() {
    TestPushPopInt();
    TestPushPopDouble();
}