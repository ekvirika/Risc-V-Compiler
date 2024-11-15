#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "Instructions.h"
#include "LabelTable.h"


typedef struct FileParser{
    FILE* file;
} FileParser;

/* Helper functions */
void fileParserInit(FileParser * parser, FILE * file);
bool parseLabels(FileParser * parser, struct LabelTable * table, int addr);
Instruction* parseNextInstruction(FileParser * parser, struct LabelTable * table);
Instruction* STypeInstruction(char* token);
Instruction* RTypeInstruction(char* token);
Instruction* BTypeInstruction(char* token, struct LabelTable * table);
Instruction* ITypeInstruction(char* token, struct LabelTable *table);
Instruction* JTypeInstruction(char* token, struct LabelTable *table);
#endif