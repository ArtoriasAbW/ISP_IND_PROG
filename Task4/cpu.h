#define TYPE double
#define STACK_CHECK

#include "Stack.h"

#include <stdio.h>
#include <string.h>

#include "mmap_file.h"

#define START_CAPACITY 20 // random number

#define MAX_INSTR_LEN 4 // maybe other

enum States {
    OFF,
    ON
};


typedef struct {
    int state;
    Stack_double *stack;
    // TODO: regs
} CPU;


void CPU_init(CPU *cpu) { // * because will be more fields
    cpu->state = ON;
    cpu->stack = (Stack_double *)calloc(1, sizeof(*cpu->stack));
    StackConstructor_double(cpu->stack, START_CAPACITY);
}