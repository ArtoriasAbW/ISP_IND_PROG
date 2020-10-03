#include "stack.h"

int main() {
    Stack stack;
    StackConstructor(&stack, 20);
    for (int i = 0; i < 30; ++i) {
        Push(&stack, i);
    }
    Stack stack_two = StackCopyConstructor(&stack);
    printf("capacity = %ld size = %ld\n", stack_two.capacity, stack_two.size);
    for (int i = 0; i < 30; ++i) {
        printf("%d ", *Pop(&stack));
    }
    printf("\n");
    StackDestructor(&stack_two);
    StackDestructor(&stack);

}