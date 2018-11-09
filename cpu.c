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

int parseDecimal(const int offset, const char arg[]) {
    int n = 0;
    for(int i = offset; arg[i] != '\0'; ++i) {
        n *= 10;
        n += arg[i] - '0';
    }
    return n;
}

void cpu_exe(cpu_t* cpu, cpu_instr_t* instruction) {
    // Jump instructions
    if(strcmp(instruction->name, "JMP") == 0) {
        cpu->instructionPointer = parseDecimal(0, instruction->arg1);
        return;
    } else if(strcmp(instruction->name, "JZ") == 0) {
        if(cpu->memory[0] == 0) {
            cpu->instructionPointer = parseDecimal(0, instruction->arg1);
            return;
        }
    }

    // One argument instructions
    if(strcmp(instruction->name, "INV") == 0) {
        // Bitwise inversion of register arg1
    } else if(strcmp(instruction->name, "DEC") == 0) {
        int destRegister = parseDecimal(1, instruction->arg1);
        cpu->memory[destRegister] = (cpu->memory[destRegister] - 1) % DATA_LIMIT;
    } else if(strcmp(instruction->name, "INC") == 0) {
        int destRegister = parseDecimal(1, instruction->arg1);
        cpu->memory[destRegister] = (cpu->memory[destRegister] + 1) % DATA_LIMIT;

    // Two argument instructions
    } else if(strcmp(instruction->name, "MOV") == 0) {
        int destRegister = parseDecimal(1, instruction->arg2);
        if(isRegister(instruction->arg1)) {
            cpu->memory[destRegister] = parseDecimal(1, instruction->arg1);
        } else {
            cpu->memory[destRegister] = parseDecimal(0, instruction->arg1);
        }
    } else if(strcmp(instruction->name, "ADD") == 0) {
        int destRegister = parseDecimal(1, instruction->arg1);
        cpu->memory[destRegister] = (cpu->memory[destRegister] + cpu->memory[parseDecimal(1, instruction->arg2)]) % DATA_LIMIT;
    } else if(strcmp(instruction->name, "SUB") == 0) {
        int destRegister = parseDecimal(1, instruction->arg1);
        cpu->memory[destRegister] = (cpu->memory[destRegister] - cpu->memory[parseDecimal(1, instruction->arg2)]) % DATA_LIMIT;
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