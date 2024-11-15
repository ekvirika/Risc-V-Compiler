#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "include/FileParser.h"
#include "include/Cpu.h"


/* 
-------------- COLORS -------------
*/
#define COLOR_RESET         "\x1b[0m"
#define COLOR_CYAN          "\x1b[36m"
#define COLOR_YELLOW        "\x1b[33m"
#define COLOR_BLUE          "\x1b[34m"
#define COLOR_RED           "\x1b[31m"
#define COLOR_MAGENTA       "\x1b[35m"
#define COLOR_GREEN         "\x1b[32m"
#define COLOR_BOLD_BLACK    "\033[1;30m"      
#define COLOR_BOLD_RED      "\033[1;31m"     
#define COLOR_BOLD_GREEN    "\033[1;32m"     
#define COLOR_BOLD_YELLOW   "\033[1;33m"     
#define COLOR_BOLD_BLUE     "\033[1;34m"     
#define COLOR_BOLD_MAGENTA  "\033[1;35m"      
#define COLOR_BOLD_CYAN     "\033[1;36m"      
#define COLOR_BOLD_WHITE    "\033[1;37m"
#define COLOR_BOLD_MAGENTA_REVERSED  "\033[1;7;35m"    

/* 
------------- CUSTOM FUNCS ----------
*/
void printWelcomeText();
void printInstruction(Instruction * instr);


/* 
------------- MAIN PART -------------
*/
int main(int argc, char *argv[]) {
    printWelcomeText();
    if (argc != 2) {
        printf("\033[1;7;31m Usage: %s <filename>\n %s", argv[0], COLOR_RESET);
        return 1;
    }
    struct CPU cpu;
    CPUInit(&cpu);

    char * filePath = argv[1];
    FILE * file = fopen(filePath, "r");
    assert(file != NULL);
    FileParser* fileParser = malloc(sizeof(FileParser));
    fileParserInit(fileParser, file);

    /* Pass one for instructions */
    while (parseLabels(fileParser, &cpu.labelTable, cpu.pc)) {
        cpu.pc++;
    }
    /* Reset Variables */
    Instruction* instr;
    cpu.pc = 0;
    rewind(file);
    // iterateLabels(&(cpu.labelTable));
    /* Pass two: main part */
    int lastPc = 0;
    printf("\n%sStarting compilation....\n\n%s", COLOR_BOLD_MAGENTA_REVERSED, COLOR_RESET);
    while ((instr = parseNextInstruction(fileParser, &cpu.labelTable)) != NULL) {
        cpu.pc += 1;
        if(instr->isLabel || instr->isComment) {
            instr->imm = 0;
            instr->rd = 0;
            instr->rs1 = 0;
            instr->isLabel = false;
            instr->isComment = false;
            free(instr->name);
            free(instr);
            continue;
        }
        lastPc = cpu.pc;
        // printf("%sPC: %d  %s", COLOR_GREEN, cpu.pc, COLOR_RESET);
        printInstruction(instr);
        if (!CPUExecute(&cpu, instr)) break; 
        if(cpu.pc == 0) break;
        
        if(lastPc != cpu.pc){
            int diff = 0;
            if(cpu.pc < lastPc){
                diff = cpu.pc;
                rewind(file);
            }  else diff = cpu.pc - lastPc;
            char tmp[150];
            while(diff-- && fgets(tmp, sizeof(tmp), file) != NULL) { 
                /* Do nothing */
            }
        } 
        displayRegisters(&cpu, false);
        instr->imm = 0;
        instr->rd = 0;
        instr->rs1 = 0;
        instr->isComment = false;
        instr->isLabel = false;
        free(instr->name);
        free(instr);
    }
    printf("\n%sProgram terminated. Last Register Values in hex: %s\n\n", COLOR_BOLD_MAGENTA_REVERSED, COLOR_RESET);
    displayRegisters(&cpu, true);
    CPUDestroy(&cpu);
    fclose(file);
    free(fileParser);
    return 0;
}


void printWelcomeText(){
    printf("\033[1;7;36m        |-----------------------------|        \033[0m\n");
    printf("\033[1;7;36m        %s| Welcome to RISC-V Emulator! |%s        \033[0m\n", "\033[1;7;35m", "\033[1;7;36m"); 
    printf("\033[1;7;36m        |-----------------------------|        \033[0m\n"); 
}

void printInstruction(Instruction * instr){
    printf("%sInstruction: %s%s, ", COLOR_BOLD_YELLOW,   COLOR_BOLD_CYAN,       instr->name); 
    printf("%srd: %s%d%s, ",        COLOR_BOLD_YELLOW,   COLOR_RED,        instr->rd, COLOR_RESET);  
    printf("%srs1: %s%d%s, ",       COLOR_BOLD_YELLOW,   COLOR_BOLD_WHITE,     instr->rs1, COLOR_RESET); 
    printf("%srs2: %s%d%s, ",       COLOR_BOLD_YELLOW,   COLOR_BLUE,       instr->rs2, COLOR_RESET);   
    printf("%simm: %s%d%s\n",       COLOR_BOLD_YELLOW,   COLOR_MAGENTA,    instr->imm, COLOR_RESET); 
}
