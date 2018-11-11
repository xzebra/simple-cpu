#include "cpu.h"

cpu_t* cpu_new() {
    cpu_t* new_cpu = (cpu_t*) malloc(sizeof(cpu_t));
    new_cpu->instructionPointer = 0;
    // clear memory
    for(unsigned int i = 0; i < REGISTERS_SIZE; ++i) {
        new_cpu->memory[i] = 0;
    }
    return new_cpu;
}

void cpu_delete(cpu_t* cpu) {
    free(cpu);
}

int fillInstructionElement(int *i, const char* routine, char dest[]) {
    unsigned int offset = *i;
    while(routine[*i] != ' ') {
        if(routine[*i] == '\0') {
            dest[(*i)-offset] = '\0';
            return 1;
        }
        dest[(*i)-offset] = routine[*i];
        ++(*i);
    }
    dest[(*i)-offset] = '\0';
    return 0;
}

void splitRoutine(const char* routine, cpu_instr_t* instruction) {
    unsigned int i = 0;
    if(fillInstructionElement(&i, routine, instruction->name)) return;
    i++;
    if(fillInstructionElement(&i, routine, instruction->arg1)) return;
    i++;
    fillInstructionElement(&i, routine, instruction->arg2); // dont care if end of string
}

int isRegister(const char arg[]) {
    return arg[0] == 'R';
}

void assert(int condition, const char* errorMsg) {
    if(!condition) printf("err: %d\n");
}

int parseDecimal(const int offset, const char arg[]) {
    int n = 0;
    for(int i = offset; arg[i] != '\0'; ++i) {
        n *= 10;
        n += arg[i] - '0';
    }
    return n;
}

void cpu_exe(cpu_t* cpu, cpu_instr_t* instruction) {
    const int isReg = isRegister(instruction->arg1);
    const int arg1 = parseDecimal(isReg, instruction->arg1);

    // Jump instructions
    // We need return to stop function execution so it doesnt
    // continue with the normal program flow because of 
    // cpu->instructionPointer++;
    if(strcmp(instruction->name, "JMP") == 0) {
        cpu->instructionPointer = arg1;
        return;
    } else if(strcmp(instruction->name, "JZ") == 0) {
        if(cpu->memory[0] == 0) {
            cpu->instructionPointer = arg1;
            return;
        }
    }

    // One argument instructions
    if(strcmp(instruction->name, "INV") == 0) {
        // Bitwise inversion of register arg1
        assert(isReg, "INV instruction requires a register argument");
        cpu->memory[arg1] = ~cpu->memory[arg1];
    } else if(strcmp(instruction->name, "DEC") == 0) {
        assert(isReg, "DEC instruction requires a register argument");
        cpu->memory[arg1] = (cpu->memory[arg1] - 1) % DATA_LIMIT;
    } else if(strcmp(instruction->name, "INC") == 0) {
        assert(isReg, "INC instruction requires a register argument");
        cpu->memory[arg1] = (cpu->memory[arg1] + 1) % DATA_LIMIT;
    } else {
        // Two argument instructions
        int arg2 = parseDecimal(1, instruction->arg2);
        if(strcmp(instruction->name, "MOV") == 0) {
            cpu->memory[arg2] = arg1;
        } else if(strcmp(instruction->name, "ADD") == 0) {
            assert(isReg, "ADD first argument must be a register");
            cpu->memory[arg1] = (cpu->memory[arg1] + cpu->memory[arg2]) % DATA_LIMIT;
        } else if(strcmp(instruction->name, "SUB") == 0) {
            assert(isReg, "SUB first argument must be a register");
            cpu->memory[arg1] = (cpu->memory[arg1] - cpu->memory[arg2]) % DATA_LIMIT;
        }
    }

    cpu->instructionPointer++;
}

void cpu_process(cpu_t* cpu, unsigned int instructions, const char* routines[]) {
    cpu->instructionPointer = 0;
    while(cpu->instructionPointer < instructions) {
        // Get instruction and registers
        cpu_instr_t instruction;
        splitRoutine(routines[cpu->instructionPointer], &instruction);

        cpu_exe(cpu, &instruction);
    }
}

uint32_t cpu_memAt(cpu_t* cpu, unsigned int position) {
    return cpu->memory[position];
}