#include "cpu.h"
#include "asm.h"

// assume that file is correct

void compute(char *instructions, char *instructions_end, CPU *cpu) {
    if (cpu->state != ON) {
        CPU_init(cpu);
    }
    size_t idx = 0;
    int num;
    double val1 = 0, val2 = 0;
    while (instructions < instructions_end) {
        switch (instructions[idx]) {
        case ADD:
            val1 = Pop_double(cpu->stack);
            val2 = Pop_double(cpu->stack);
            Push_double(cpu->stack, val1 + val2);
            ++idx;
            break;
        case SUB:
            val1 = Pop_double(cpu->stack);
            val2 = Pop_double(cpu->stack);
            Push_double(cpu->stack, val1 - val2);
            ++idx;
            break;
        case MUL:
            val1 = Pop_double(cpu->stack);
            val2 = Pop_double(cpu->stack);
            Push_double(cpu->stack, val1 * val2);
            ++idx;
            break;
        case DIV:
            val1 = Pop_double(cpu->stack);
            val2 = Pop_double(cpu->stack);
            if (fabs(val2) < 0.00001) {
                fprintf(stderr, "Zero division error.\n");
                exit(1);
            }
            Push_double(cpu->stack, val1 / val2);
            ++idx;
            break;
        case PUSH_NUM:
            ++idx;
            val1 = *(double *)(instructions + idx);
            Push_double(cpu->stack, val1);
            idx += sizeof(val1);
            break;
        case PUSH_REG:
            ++idx;
            switch (instructions[idx])
            {
            case RAX_REG:
                Push_double(cpu->stack, cpu->rax);
                ++idx;
                break;
            case RBX_REG:
                Push_double(cpu->stack, cpu->rbx);
                ++idx;
                break;
            case RCX_REG:
                Push_double(cpu->stack, cpu->rcx);
                ++idx;
                break;
            case RDX_REG:
                Push_double(cpu->stack, cpu->rdx);
                ++idx;
                break;    
            default:
                fprintf(stderr, "Invalid register value\n");
                exit(1);
                break;
            }
            break;
        case POP:
            ++idx;
            switch (instructions[idx])
            {
            case RAX_REG:
                cpu->rax = Pop_double(cpu->stack);
                ++idx;
                break;
            case RBX_REG:
                cpu->rbx = Pop_double(cpu->stack);
                ++idx;
                break;
            case RCX_REG:
                cpu->rcx = Pop_double(cpu->stack);
                ++idx;
                break;
            case RDX_REG:
                cpu->rdx = Pop_double(cpu->stack);
                ++idx;
                break;    
            default:
                fprintf(stderr, "Invalid register value\n");
                exit(1);
                break;
            }
            break;
        case SQRT:
            val1 = Pop_double(cpu->stack);
            if (val1 < 0) {
                fprintf(stderr, "Error: square root of a negative number.\n");
                exit(1);
            }
            Push_double(cpu->stack, sqrt(val1));
            ++idx;
            break;
        case IN:
            num = scanf("%lf", &val1);
            assert(num == 1);
            Push_double(cpu->stack, val1);
            ++idx;
            break;
        case OUT:
            val1 = ShowLast_double(cpu->stack);
            printf("%lf\n", val1);
            ++idx;
            break;
        case HLT:
            ++idx;
            cpu->state = WAIT;
            return;
        default:
            fprintf(stderr, "Invalid instuction.");
            exit(1);
            break;
        }
    }
}


int main(int argc, char **argv) { // file path in argv[1]
    if (argc < 2) {
        printf("No file name. Exit.\n");
        return 1;
    }
    size_t size;
    char *instuctions = mmap_file(argv[1], &size);
    char *instructions_end = instuctions + size;
    CPU cpu;
    cpu.state = OFF;
    compute(instuctions, instructions_end, &cpu);
    munmap(instuctions, size);
    return 0;

}