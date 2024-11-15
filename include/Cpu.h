#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>
#include "Bus.h"
#include "Instructions.h"
#include "LabelTable.h"

typedef struct CPU {
    uint32_t pc;                    // 64-bit program counter
    uint32_t registers[32];         // 32 64-bit registers (a0-a31)
    struct LabelTable labelTable;   // Table for labels
    struct Bus bus;                 // CPU connected to BUS
} CPU;



/*  
Function: CPUInit
-----------------
 The CPUInit function initializes the provided cpu by pointer
 by 0 initializing all the 32 registers, and setting the program
 counter pc to the start of the memory.
*/
void        CPUInit(struct CPU *cpu);

/*  
Function: CPUFetch
-----------------
 The CPUFetch function reads instructions from the
  memory (DRAM) for execution.
*/
uint32_t    CPUFetch(struct CPU *cpu);

/*  
Function: CPUExecute
-----------------
 CPUExecute is basically the ALU and the instruction
 decoder combined. It decodes the instruction fetched 
 from the DRAM in the inst variable and executes the 
 instruction accordingly.
*/
int         CPUExecute(struct CPU *cpu, Instruction * inst);
void        CPUDestroy(struct CPU *cpu);
void        CPUStore(struct CPU * cpu, uint32_t addr, uint32_t size, uint32_t value);
uint32_t    CPULoad(struct CPU * cpu, uint32_t addr, uint32_t size);
void        displayRegisters(struct CPU *cpu, bool isHex); 
#endif