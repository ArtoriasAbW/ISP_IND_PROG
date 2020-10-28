ASM_FILES = Assembler/asm.c Utility/mmap_file.c

DISASM_FILES = Disassembler/disasm.c Utility/mmap_file.c

CPU_FILES = CPU/cpu.c Utility/mmap_file.c


build_asm:
	gcc -std=c11 -O2 -g -o asm $(ASM_FILES)

build_disasm:
	gcc -std=c11 -O2 -g -o disasm $(DISASM_FILES)

build_cpu:
	gcc -std=c11 -O2 -g -o cpu $(CPU_FILES) -lm

clean:
	rm cpu disasm asm