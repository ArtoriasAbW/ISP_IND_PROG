#include "mmap_file.h"
#include <ctype.h>

enum opcodes {
    ADD = 1,
    SUB = 2,
    MUL = 3,
    DIV = 4,
    PUSH_NUM = 5,
    PUSH_REG = 6,
    POP = 7,
    SQRT = 8,
    IN = 9,
    OUT = 10,
    HLT = 11,
    RAX_REG = 25,
    RBX_REG = 26,
    RCX_REG = 27,
    RDX_REG = 28
};


static char parse_reg(char *token_begin, size_t token_size) { // return reg_code or zero if not reg
    if (!strncmp(token_begin, "rax", token_size)) {
        return RAX_REG;
    }
    if (!strncmp(token_begin, "rbx", token_size)) {
        return RBX_REG;
    }
    if (!strncmp(token_begin, "rcx", token_size)) {
        return RCX_REG;
    }
    if (!strncmp(token_begin, "rdx", token_size)) {
        return RDX_REG;
    }
    return 0;
}


static void parse_op(char **token_begin, char **token_end, char *instructions_end) {
    while (isspace(**token_end)) {
            ++(*token_end);
            if (**token_end == '\0') {
                fprintf(stderr, "No operand\n");
                exit(1);
            }
        }
    *token_begin = *token_end;
    while (!isspace(**token_end)) { // идем до конца токена
        ++*token_end;
        if (*token_end >= instructions_end) {
            break;
        }
    }
}

static char parse_num(char *token_begin, double *number) { // return 1 if ok and fill number
    char *end_ptr = NULL;
    *number = strtod(token_begin, &end_ptr);
    if (end_ptr == token_begin) {
        fprintf(stderr, "Error when parsing double value\n");
        return 0;
    }
    return 1;
}

static char process(char **token_begin, char **token_end, char *instructions_end, char *opcode, int fd) {
    size_t len = *token_end - *token_begin;
    if (!strncmp(*token_begin, "add", len)) {
        *opcode = ADD;
        return 1;
    }
    if (!strncmp(*token_begin, "sub", len)) {
        *opcode = SUB;
        return 1;
    }
    if (!strncmp(*token_begin, "mul", len)) {
        *opcode = MUL;
        return 1;
    }
    if (!strncmp(*token_begin, "div", len)) {
        *opcode = DIV;
        return 1;
    }
    if (!strncmp(*token_begin, "push", len)) { // push reg or push double
        // need to parse next token
        parse_op(token_begin, token_end, instructions_end);
        char reg = parse_reg(*token_begin, *token_end - *token_begin);
        if (reg) {
            *opcode = PUSH_REG;
            int byte_num = write(fd, opcode, 1);
            assert(byte_num == 1);
            byte_num = write(fd, &reg, 1);
            assert(byte_num == 1);
            return 0;
        }
        double number;
        char correct_number = parse_num(*token_begin, &number);
        if (correct_number) {
            *opcode = PUSH_NUM;
            int byte_num = write(fd, opcode, 1);
            assert(byte_num == 1);
            byte_num = write(fd, &number, sizeof(number));
            assert(byte_num == sizeof(number));
            return 0;
        } else {
            fprintf(stderr, "Invalid push operand\n");
            exit(1);
        }
    }
    if (!strncmp(*token_begin, "pop", len)) { 
        parse_op(token_begin, token_end, instructions_end);
        char reg = parse_reg(*token_begin, *token_end - *token_begin);
        if (reg) {
            *opcode = PUSH_REG;
            int byte_num = write(fd, opcode, 1);
            assert(byte_num == 1);
            byte_num = write(fd, &reg, 1);
            assert(byte_num == 1);
            return 0;
        } else {
            fprintf(stderr, "Invalid pop operand\n");
            exit(1);
        }
    }
    if (!strncmp(*token_begin, "sqrt", len)) {
        *opcode = SQRT;
        return 1;
    }
    if (!strncmp(*token_begin, "in", len)) {
         *opcode = IN;
        return 1;
    }
    if (!strncmp(*token_begin, "out", len)) {
         *opcode = OUT;
        return 1;
    }
    if (!strncmp(*token_begin, "hlt", len)) {
         *opcode = HLT;
        return 1;
    }
    fprintf(stderr, "Error:Invalid instruction\n");
    exit(1);
}


static void assembler_to_file(char *instructions, size_t size, int fd)  { // FIX: double output of last instr
    char *instructions_end = instructions + size;
    assert(instructions != NULL && fd != -1);
    char *token_begin = instructions;
    char *token_end = instructions;
    while (token_end < instructions_end) {
        while (!isspace(*token_end)) { // идем до конца токена
            ++token_end;
            if (token_end >= instructions_end) {
                break;
            }
        }
        char opcode;
        char need_to_write = process(&token_begin, &token_end, instructions_end,  &opcode, fd);
        if (need_to_write) {
            int byte_num = write(fd, &opcode, 1);
            assert(byte_num == 1);
        }
        while (isspace(*token_end)) {
            ++token_end;
            if (*token_end == '\0') {
                break;
            }
        }
        token_begin = token_end;
    }
    close(fd);
    munmap(instructions, size);
}


int main(int argc, char **argv) { // file path in argv[1]
    if (argc > 2) {
        size_t size = 0;
        char *instrs = mmap_file(argv[1], &size);
        int fd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);
        assembler_to_file(instrs, size, fd);
    }
}