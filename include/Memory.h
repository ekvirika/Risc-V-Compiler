#ifndef MEMORY_H
#define MEMORY_H

/* The dram is the memory of the system. It has two 
basic operations: writing and reading from memory. */
#include <stdint.h>

#define DRAM_BASE 0x00
#define DRAM_SIZE 1024*1024*2  // 2 MiB DRAM

typedef struct DRAM {
	uint8_t memory[DRAM_SIZE]; // Dram memory of DRAM_SIZE
} DRAM;


/* 
Function: dramLoad
-------------------
The dramLoad() takes the pointer to the dram to be 
read from, the address of the data to be read, and the 
size of the data to be read, which might be 8, 16 or 32 bits 
as per the instruction (LB, LH and LW respectively).
*/
uint32_t dramLoad(DRAM* dram, uint32_t addr, uint32_t size);


/* 
Function: dramStore
-------------------
  The dramStore(), takes the same args as dramLoad(),
  plus the uint32_t value arg, which contains the data to be written 
  to the given address of the given dram.
*/
void dramStore(DRAM* dram, uint32_t addr, uint32_t size, uint32_t value);

#endif