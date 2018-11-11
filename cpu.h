#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define REGISTERS_SIZE 99 // R00 to R99
#define MAX_ARGUMENT_LENGTH 10
#define DATA_LIMIT 4294967296
#define MAX_INSTRUCTION_LENGTH 3

typedef struct {
    int instructionPointer;
    uint32_t memory[REGISTERS_SIZE];
} cpu_t;

typedef struct {
    char name[MAX_INSTRUCTION_LENGTH+1];
    char arg1[MAX_ARGUMENT_LENGTH+1];
    char arg2[MAX_ARGUMENT_LENGTH+1];
} cpu_instr_t;

cpu_t* cpu_new();
void cpu_delete(cpu_t* cpu);

void cpu_exe(cpu_t* cpu, cpu_instr_t* instruction);
void cpu_process(cpu_t* cpu, unsigned int instructions, const char* routines[]);

uint32_t cpu_memAt(cpu_t* cpu, unsigned int position);

#endif //CPU_H
