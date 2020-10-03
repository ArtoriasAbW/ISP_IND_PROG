#define TYPE int
#include "stack.h"

void TestPushPopInt() {
    Stack stack;
    ssize_t capacity = 20;
    StackConstructor(&stack, capacity);
    assert(stack.size == 0 && stack.capacity == capacity && stack.data != NULL);
    for (int i = 0; i < 30; ++i) {
        Push(&stack, i);
    }
    assert(stack.size == 30 && stack.capacity == 40 && stack.data != NULL);
    for (int i = 29; i >= 0; --i) {
        assert(*Pop(&stack) == i);
    }
    printf("Test PushPopInt done.\n");
}


void TestStackDestructor() {

}


void TestCopyConstructor() {
    
}
#undef TYPE


int main() {
    TestPushPopInt();
}