#include <stdio.h>
#include "cpu.h"

int main() {
    cpu_t* cpu = cpu_new();
    const char* routines[] = {
        "MOV 5 R00",
        "MOV 10 R01",
        "JZ 6",
        "ADD R02 R01",
        "DEC R00",
        "JMP 2",
        "MOV R02 R42"
    };
    cpu_process(cpu, 7, routines);

    printf("[%d, %d, %d]\n", cpu_memAt(cpu, 0), cpu_memAt(cpu, 1), cpu_memAt(cpu, 2));

    cpu_delete(cpu);
    return 0;
}