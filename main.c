#include <stdio.h>
#include "cpu.h"

int main() {
    cpu_t* cpu = cpu_new();

    // Substraction demo
    const char* routine[] = {
        "MOV 15 R00",
        "MOV 10 R01",
        "INV R01",
        "INC R01",
        "ADD R00 R01"
    };
    cpu_process(cpu, 5, routine);

    printf("[%d, %d]\n", cpu_memAt(cpu, 0), cpu_memAt(cpu, 1));

    cpu_delete(cpu);
    return 0;
}