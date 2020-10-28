#include <ctype.h>
#include "../Utility/mmap_file.h"
#include "../Assembler/asm.h"

void disassembler_to_file(char *instructions, size_t size, int fd) {
    size_t idx = 0;
    int num;
    char *buf;
    char buf_for_double[100];
    double val1 = 0, val2 = 0;
    while (idx < size) {
        switch (instructions[idx]) {
        case ADD:
            buf = "add\n";
            ++idx;
            break;
        case SUB:
            buf = "sub\n";
            ++idx;
            break;
        case MUL:
            buf = "mul\n";
            ++idx;
            break;
        case DIV:
            buf = "div\n";
            ++idx;
            break;
        case PUSH_NUM:
            ++idx;
            buf = "push ";
            num = write(fd, buf, strlen(buf));
            assert(num == strlen(buf));
            val1 = *(double *)(instructions + idx);
            idx += sizeof(val1);
            snprintf(buf_for_double, 100, "%lf\n", val1);
            buf = buf_for_double;
            break;
        case PUSH_REG:
            ++idx;
            buf = "push ";
            num = write(fd, buf, strlen(buf));
            assert(num == strlen(buf));
            switch (instructions[idx]) {
            case RAX_REG:
                buf = "rax\n";
                ++idx;
                break;
            case RBX_REG:
                buf = "rbx\n";
                ++idx;
                break;
            case RCX_REG:
                buf = "rcx\n";
                ++idx;
                break;
            case RDX_REG:
                buf = "rdx\n";
                ++idx;
                break;    
            default:
                fprintf(stderr, "Invalid register value.");
                munmap(instructions, size);
                close(fd);
                exit(1);
                break;
            }
            break;
        case POP:
            ++idx;
            buf = "pop ";
            num = write(fd, buf, strlen(buf));
            assert(num == strlen(buf));
            switch (instructions[idx]) {
            case RAX_REG:
                buf = "rax\n";
                ++idx;
                break;
            case RBX_REG:
                buf = "rbx\n";
                ++idx;
                break;
            case RCX_REG:
                buf = "rcx\n";
                ++idx;
                break;
            case RDX_REG:
                buf = "rdx\n";
                ++idx;
                break;    
            default:
                break;
            }
            break;
        case SQRT:
            buf = "sqrt\n";
            ++idx;
            break;
        case IN:
            buf = "in\n";
            ++idx;
            break;
        case OUT:
            buf = "out\n";
            ++idx;
            break;
        case HLT:
            buf = "hlt\n";
            ++idx;
            break;
        default:
            fprintf(stderr, "Invalid command.\n");
            munmap(instructions, size);
            close(fd);
            exit(1);
            break;
        }
        num = write(fd, buf, strlen(buf));
        assert(num == strlen(buf));
    }
}

int main(int argc, char **argv) {
     if (argc > 2) {
        size_t size = 0;
        char *instrs = mmap_file(argv[1], &size);
        int fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
        disassembler_to_file(instrs, size, fd);
        munmap(instrs, size);
        close(fd);
    }
}