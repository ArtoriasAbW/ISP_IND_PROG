#pragma once
#define TYPE double
#define STACK_CHECK

#include "../Utility/Stack.h"

#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../Utility/mmap_file.h"

#define START_CAPACITY 20 // random number

#define MAX_INSTR_LEN 4 // maybe other

enum States {
    OFF,
    ON,
    WAIT
};


typedef struct {
    int state;
    Stack_double *stack;
    double rax;
    double rbx;
    double rcx;
    double rdx;
} CPU;


void CPU_init(CPU *cpu) {
    if (cpu->state == OFF) {
        cpu->stack = (Stack_double *)calloc(1, sizeof(*cpu->stack));
        StackConstructor_double(cpu->stack, START_CAPACITY);
        cpu->rax = 0;
        cpu->rbx = 0;
        cpu->rcx = 0;
        cpu->rdx = 0;
    }
    cpu->state = ON;
}