#ifndef BUS_H
#define BUS_H

#include "Memory.h"

typedef struct Bus{
    struct DRAM dram;
} Bus;

uint32_t busLoad(Bus* bus, uint32_t addr, uint32_t size) ;
void busStore(Bus* bus, uint32_t addr, uint32_t size, uint32_t value) ;

#endif