#include "../include/Memory.h"
#include <stdio.h>


uint32_t dramLoad8(DRAM* dram, uint32_t addr); 
uint32_t dramLoad16(DRAM* dram, uint32_t addr);
uint32_t dramLoad32(DRAM* dram, uint32_t addr);

void dramStore8(DRAM* dram, uint32_t addr, uint32_t value); 
void dramStore16(DRAM* dram, uint32_t addr, uint32_t value);
void dramStore32(DRAM* dram, uint32_t addr, uint32_t value);


uint32_t dramLoad(DRAM* dram, uint32_t addr, uint32_t size){
    switch (size) {
        case 8:  return dramLoad8(dram, addr);  break;
        case 16: return dramLoad16(dram, addr); break;
        case 32: return dramLoad32(dram, addr); break;
        default: ;
    }
    return 1;
}

void dramStore(DRAM* dram, uint32_t addr, uint32_t size, uint32_t value) {
    switch (size) {
        case 8:  dramStore8(dram, addr, value);  break;
        case 16: dramStore16(dram, addr, value); break;
        case 32: dramStore32(dram, addr, value); break;
        default: ;
    }

}

uint32_t dramLoad8(DRAM* dram, uint32_t addr){
    return (uint32_t) dram->memory[addr - DRAM_BASE];
}

uint32_t dramLoad16(DRAM* dram, uint32_t addr){
    return (uint32_t) dram->memory[addr - DRAM_BASE] | 
      (uint32_t) dram->memory[addr-DRAM_BASE + 1] << 8;
}

uint32_t dramLoad32(DRAM* dram, uint32_t addr){
 return (uint32_t) dram->memory[addr - DRAM_BASE] 
    |   (uint32_t) dram->memory[addr-DRAM_BASE + 1] << 8 
    |   (uint32_t) dram->memory[addr-DRAM_BASE + 2] << 16
    |   (uint32_t) dram->memory[addr-DRAM_BASE + 3] << 24;
}


void dramStore8(DRAM* dram, uint32_t addr, uint32_t value) {
    dram->memory[addr - DRAM_BASE] = (uint8_t)(value & 0xff); 
}


void dramStore16(DRAM* dram, uint32_t addr, uint32_t value){
    dram->memory[addr - DRAM_BASE] = (uint8_t) (value & 0xff);
    dram->memory[addr - DRAM_BASE + 1] = (uint8_t) ((value >> 8) & 0xff);
}

void dramStore32(DRAM* dram, uint32_t addr, uint32_t value){

    dram->memory[addr - DRAM_BASE] = (uint8_t) (value & 0xff);
    dram->memory[addr - DRAM_BASE + 1] = (uint8_t) ((value >> 8) & 0xff);
    dram->memory[addr - DRAM_BASE + 2] = (uint8_t) ((value >> 16) & 0xff);
    dram->memory[addr - DRAM_BASE + 3] = (uint8_t) ((value >> 24) & 0xff);
}

