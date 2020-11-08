# CPU, assember, dissasember
# Description

Implementation of CPU with stack and registers, assembler and disassembler.

Commands available are:

in (get float number from stdin and push a result)

out (output float number from the top ofstack)

hlt (stop executing)

add (add two numbers from the stack and push a result)

sub (subtract one value from another and push a result)

mul (multiply two numbers from the stack and push a result)

div (divide one number by another and push a result)

sqrt (take square root from the top value and push a result)

push (push number or register to the stack)

pop (pop number from stack to some register)

There are four double registers in processor provided: rax, rbx, rcx and rdx.

## Getting Started

### Installing
 
 * Download the project from GitHub or clone repository by
 
```
git clone https://github.com/ArtoriasAbW/ISP_IND_PROG.git
```

### Building and running programs

```
cd ISP_IND_PROG/Task4
```

* CPU
```
make build_cpu
./cpu <computer language file>
```


* Assembler
```
make build_asm
./asm <file with mnemonics> <output file>
```


* Disassembler
```
make build_disasm
./disasm <computer language file> <output file>
```

* Deleting exectuble file
```
make clean
```
