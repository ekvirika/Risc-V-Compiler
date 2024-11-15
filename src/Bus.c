#include "../include/Bus.h"

uint32_t busLoad(Bus* bus, uint32_t addr, uint32_t size) {
    return dramLoad(&(bus->dram), addr, size);
}
void busStore(Bus* bus, uint32_t addr, uint32_t size, uint32_t value) {
    dramStore(&(bus->dram), addr, size, value);
}