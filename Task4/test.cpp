#include <iostream>

#define TYPE int
#define STACK_CHECK

#include "Stack.h"



int main() {
    Stack_int stack;
    StackConstructor_int(&stack, 10);
    for (int i = 0; i < 10; ++i) {
        Push_int(&stack, i);
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << Pop_int(&stack) << "\n";
    }
    return 0;
}