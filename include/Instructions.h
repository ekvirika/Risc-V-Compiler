#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include <stdbool.h>

typedef struct Instruction {
   char* name;       // e.g., "addi", "add"
   int rd;           // Destination register
   int rs1;          // Source register 1
   int rs2;          // Source register 2
   int   imm;        // Immediate value
   bool isLabel;     // bool for determining instruction type
   bool isComment;   // bool for determining instruction type
} Instruction;

 
#endif