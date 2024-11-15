#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Cpu.h"

#define COLOR_RESET         "\x1b[0m"
#define COLOR_CYAN          "\x1b[36m"
#define COLOR_YELLOW        "\x1b[33m"
#define COLOR_BLUE          "\x1b[34m"
#define COLOR_RED           "\x1b[31m"
#define COLOR_MAGENTA       "\x1b[35m"
#define COLOR_GREEN         "\x1b[32m"

/*
   -------------------------------
    CPU FUNCS
   ------------------------------- 
 */
void displayRegisters(struct CPU *cpu, bool isHex){
    /*  Application Binary Interface registers */
    char* abi[] = { 
        "zero", "ra",  "sp",  "gp",
          "tp", "t0",  "t1",  "t2",
          "s0", "s1",  "a0",  "a1",
          "a2", "a3",  "a4",  "a5",
          "a6", "a7",  "s2",  "s3",
          "s4", "s5",  "s6",  "s7",
          "s8", "s9", "s10", "s11",
          "t3", "t4",  "t5",  "t6",
    };
    if(isHex){
        for (int i = 0; i < 8; i++) {
            printf("%4s| %sx%02d:%s %#-8.2x" COLOR_RESET "\t", abi[i],      COLOR_CYAN,  i,      COLOR_MAGENTA,    cpu->registers[i]);
            printf("%4s| %sx%02d:%s %#-8.2x" COLOR_RESET "\t", abi[i + 8],  COLOR_CYAN,  i + 8,  COLOR_MAGENTA,    cpu->registers[i + 8]);
            printf("%4s| %sx%02d:%s %#-8.2x" COLOR_RESET "\t", abi[i + 16], COLOR_CYAN,  i + 16, COLOR_MAGENTA,    cpu->registers[i + 16]);
            printf("%4s| %sx%02d:%s %#-8.2x" COLOR_RESET "\n", abi[i + 24], COLOR_CYAN,  i + 24, COLOR_MAGENTA,    cpu->registers[i + 24]);
        }
        return;
    } 
    for (int i = 0; i < 8; i++) {
        printf("%4s| %sx%02d:%s %-8.2d" COLOR_RESET "\t", abi[i],      COLOR_MAGENTA,  i,      COLOR_CYAN,    cpu->registers[i]);
        printf("%4s| %sx%02d:%s %-8.2d" COLOR_RESET "\t", abi[i + 8],  COLOR_MAGENTA,  i + 8,  COLOR_CYAN,    cpu->registers[i + 8]);
        printf("%4s| %sx%02d:%s %-8.2d" COLOR_RESET "\t", abi[i + 16], COLOR_MAGENTA,  i + 16, COLOR_CYAN,    cpu->registers[i + 16]);
        printf("%4s| %sx%02d:%s %-8.2d" COLOR_RESET "\n", abi[i + 24], COLOR_MAGENTA,  i + 24, COLOR_CYAN,    cpu->registers[i + 24]);
    }

}

void CPUInit(struct CPU *cpu) { 
    cpu->registers[0] = 0x00;
    cpu->registers[2] = DRAM_BASE + DRAM_SIZE;
    cpu->pc = DRAM_BASE;
    labelTableInit(&cpu->labelTable);
    
}

uint32_t CPUFetch(struct CPU *cpu){
    uint32_t instruction = busLoad(&(cpu->bus), cpu->pc, 32);
    return instruction;
}

uint32_t CPULoad(struct CPU * cpu, uint32_t addr, uint32_t size){
    return busLoad(&(cpu->bus), addr, size);
}
void CPUStore(struct CPU * cpu, uint32_t addr, uint32_t size, uint32_t value){
    busStore(&(cpu->bus), addr, size, value);
}

void CPUDestroy(struct CPU *cpu){
    if (cpu == NULL) { return; } // Safety check
    labelTableDestroy(&cpu->labelTable);
}




/* -------------------------------
    INSTRUCTION DECODING
   ------------------------------- 
    R-Type: Register type instructions
    I-Type: Immediate type instructions
    S-Type: Store type instructions
    B-Type: Break type instructions
    U-Type: Register type instructions
    J-Type: Jump type instructions
 */

/*  rd = PC + 4
    PC = PC + offset */
void instruction_JAL(CPU* cpu, Instruction* instr) {
    int imm = instr->imm;
    cpu->registers[instr->rd] = cpu->pc; // Store return address in rd
    cpu->pc = instr->imm ;
    // printf("jal\n");
}

/*  rd = PC + 4 // ra
    PC = rs1 + imm  */
void instruction_JALR(CPU * cpu, Instruction* instr){ 
    int target_address = cpu->registers[instr->rs1] + instr->imm;
    cpu->registers[instr->rd] = cpu->pc; 
    cpu->pc = target_address;
    // printf("jalr\n");
}

/* -------------------------------
    Branch instructions
*/
/*  if (rs1 == rs2)
    PC = PC + offset */
void instruction_BEQ(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    if(cpu->registers[instr->rs1] == cpu->registers[instr->rs2]){
        cpu->pc = imm;
    }
    // printf("beq\n");
}

/*  if (rs1 != rs2)
    PC = PC + offset */
void instruction_BNE(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    if(cpu->registers[instr->rs1] != cpu->registers[instr->rs2]){
        cpu->pc = imm;
    }
    // printf("bne\n");
}

/* if (rs1 <= rs2)
    PC = PC + offset */
void instruction_BLE(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    if(cpu->registers[instr->rs1] <= cpu->registers[instr->rs2]){
        cpu->pc = imm ;
    }
    // printf("ble\n");
}

/* if (rs1 >= rs2)
    PC = PC + offset */
void instruction_BGE(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    if(cpu->registers[instr->rs1] >= cpu->registers[instr->rs2]){
        cpu->pc = imm;
    }
    // printf("%d\n", cpu->pc);
}
 

/* if (rs1 > rs2)
    PC = PC + offset */
void instruction_BGT(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    if(cpu->registers[instr->rs1] > cpu->registers[instr->rs2]){
        cpu->pc = imm;
    }
    // printf("bgt\n");
}

/* if (rs1 < rs2)
    PC = PC + offset */
void instruction_BLT(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    if(cpu->registers[instr->rs1] < cpu->registers[instr->rs2]){
        cpu->pc = imm;
    }
    // printf("blt\n");
}

/* -------------------------------
    Load instructions
*/
void instruction_LB(CPU* cpu, Instruction* instr) {
    int imm = instr->imm;
    int addr = cpu->registers[instr->rs1] + imm;
    cpu->registers[instr->rd] = (int)(int8_t) CPULoad(cpu, addr, 8);
    // printf("lb\n");
}

void instruction_LH(CPU* cpu, Instruction* instr) {
    int imm = instr->imm;
    int addr = cpu->registers[instr->rs1] + imm;
    cpu->registers[instr->rd] = (int)(int16_t) CPULoad(cpu, addr, 16);
    // printf("lh\n");
}

void instruction_LW(CPU* cpu, Instruction* instr) {
    int imm = instr->imm;
    int addr = cpu->registers[instr->rs1] + imm;
    // printf("%d %d\n", DRAM_BASE, DRAM_BASE + DRAM_SIZE);
    // printf("rs1 value: %d, imm: %d, calculated addr: %u\n", cpu->registers[instr->rs1], imm, addr);
    cpu->registers[instr->rd] = (int) CPULoad(cpu, addr, 32);
}

/* -------------------------------
    Store instructions
*/

void instruction_SB(CPU* cpu, Instruction* instr) {
    int32_t imm = instr->imm;
    int32_t addr = cpu->registers[instr->rs1] + imm;
    CPUStore(cpu, DRAM_BASE + addr, 8, cpu->registers[instr->rs2]);
    // printf("sb\n");
}

void instruction_SH(CPU* cpu, Instruction* instr) {
    int32_t imm = instr->imm;
    int32_t addr = cpu->registers[instr->rs1] + imm ;
    CPUStore(cpu, addr, 16, cpu->registers[instr->rs2]);
    // printf("sh\n");
}

void instruction_SW(CPU* cpu, Instruction* instr) {
    int32_t imm = instr->imm;
    int32_t rs1Val = cpu->registers[instr->rs1];
    int32_t result = rs1Val + imm;
    CPUStore(cpu, result, 32, cpu->registers[instr->rs2]);
}

/* -------------------------------
    Immediate Value instructions
*/

/*  rd = rs1 + imm  */
void instruction_ADDI(CPU * cpu, Instruction* instr){
    int imm =instr->imm;
    cpu->registers[instr->rd] = cpu->registers[instr->rs1] + imm;
    // printf("addi\n");
}

void instruction_SRLI(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    cpu->registers[instr->rd] = cpu->registers[instr->rs1] >> imm;
    // printf("srli\n");
}

void instruction_SRAI(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    cpu->registers[instr->rd] =(int32_t)cpu->registers[instr->rs1] >> imm;
    // printf("srai\n");
}

void instruction_SLLI(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    cpu->registers[instr->rd] = cpu->registers[instr->rs1] << imm;
}

void instruction_SLAI(CPU * cpu, Instruction* instr){
    int imm = instr->imm;
    cpu->registers[instr->rd] = (int32_t) cpu->registers[instr->rs1] << imm;
}
/* -------------------------------
    Arithmetic R-Type instructions
*/

void instruction_ADD(CPU * cpu, Instruction* instr){
    cpu->registers[instr->rd] = cpu->registers[instr->rs1] + cpu->registers[instr->rs2];
    // printf("add\n");
}

void instruction_SUB(CPU * cpu, Instruction* instr){
    cpu->registers[instr->rd] = cpu->registers[instr->rs1] - cpu->registers[instr->rs2];
    // printf("sub\n");
}

void instruction_MUL(CPU * cpu, Instruction* instr){
    cpu->registers[instr->rd] = cpu->registers[instr->rs1] * cpu->registers[instr->rs2];
    // printf("mul\n");
}

void instruction_DIV(CPU * cpu, Instruction* instr){
    cpu->registers[instr->rd] = cpu->registers[instr->rs1] / cpu->registers[instr->rs2];
    // printf("div\n");
}



/* Function type for instruction handlers */
typedef void (*InstructionHandler)(struct CPU*, Instruction*);

/* Structure to map instruction names to handlers */
struct InstructionMapEntry {
    const char* name;
    InstructionHandler handler; 
};

/* Declare instruction map globally */
struct InstructionMapEntry instructionMap[] = {
    { "jal", instruction_JAL },
    { "jalr", instruction_JALR },
    { "beq", instruction_BEQ },
    { "bne", instruction_BNE },
    { "bge", instruction_BGE },
    { "bgt", instruction_BGT },
    { "blt", instruction_BLT },
    { "ble", instruction_BLE },
    { "lb", instruction_LB },
    { "lh", instruction_LH },
    { "lw", instruction_LW },
    { "sb", instruction_SB },
    { "sh", instruction_SH },
    { "sw", instruction_SW },
    { "addi", instruction_ADDI },
    { "slli", instruction_SLLI },
    { "slai", instruction_SLAI },
    { "srli", instruction_SRLI },
    { "srai", instruction_SRAI },
    { "add", instruction_ADD },
    { "sub", instruction_SUB },
    { "mul", instruction_MUL },
    { "div", instruction_DIV },
    { NULL, NULL } // IMPORTANT: Null terminator for the table 
};



/* -----------------------
    MAIN PART
    ---------------------- */


int CPUExecute(struct CPU *cpu, Instruction* instr) {
    cpu->registers[0] = 0; // x0 hardwired to 0
    for (int i = 0; instructionMap[i].name != NULL; i++) {
        if (strcmp(instr->name, instructionMap[i].name) == 0) {
            instructionMap[i].handler(cpu, instr);
            return 1;
        }
    }

    
    printf("\033[1;7;31mUnknown instruction: %s%s\n",  instr->name, COLOR_RESET);
    return 0; 
}


