#include "../include/FileParser.h"
#include "../include/LabelTable.h"
#include <stdio.h>  
#include <string.h>


void fileParserInit(FileParser * parser, FILE * file){
    parser->file = file;
}

void substr(const char *src, int start, int len, char *dest) {
    strncpy(dest, src + start, len);
    dest[len] = '\0'; // Null-terminate the destination string
}

void replace(char *str, const char *find, const char *replace) {
    int find_len = strlen(find);
    int replace_len = strlen(replace);

    char *temp = strstr(str, find);
    while (temp != NULL) {
        memmove(temp + replace_len, temp + find_len, strlen(temp + find_len) + 1);
        strncpy(temp, replace, replace_len);
        temp = strstr(temp + replace_len, find);
    }
}

/* 
I-Type:
opcode | rd | rs1 | immediate
Examples: addi, jalr, lw
S-Type:
opcode | rs2 | rs1 | immediate
Examples: sw, sb, sh
B-Type:
opcode | rs1 | rs2 | immediate
Examples: beq, bne, blt, bge
R-Type:
opcode | rd | rs1 | rs2
Examples: add, sub, mul
 */

Instruction* printError(Instruction *instr){
    fprintf(stderr, "\033[1;7;31mError: Not enough arguments for instruction %s\n\033[0m", instr->name); 
    free(instr->name);
    free(instr);
    return NULL;
}

Instruction * printUnknown(Instruction *instr, char * token){
    fprintf(stderr, "\033[1;7;31mError: Not enough arguments for instruction %s\n\033[0m",token); 
    free(instr->name);
    free(instr);
    return NULL;
}

Instruction * ITypeInstruction(char * token, struct LabelTable * table) {
    Instruction* instr = (Instruction*) malloc(sizeof(Instruction));
    if (instr == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    instr->name = strdup(token); // Set opcode
    
    // Extract rd
    token = strtok(NULL, " ,\t"); 
    if (token != NULL) {
        if(token[0] != 'x') return printUnknown(instr, token);
        instr->rd = atoi(token + 1); 
    }
    else return printError(instr);
    token = strtok(NULL, " ,\t\n");  

    /* Handle special JAL case */
    if(strcmp(instr->name, "jal") == 0){
        instr->imm = lookupLabel(table, token);
        if(instr->imm == -1) {
            fprintf(stderr, "\033[1;7;31mError: No such label\"%s\" exists. \n\033[0m", token); 
            free(instr->name);
            free(instr);
            return NULL;
        } 
        return instr;
    }

    /* Handle other instructions */
    if (token != NULL) {
        // printf("%s\n", token);
        if (token[strlen(token) - 1] == ')') {
            char* imm_str = strtok(token, ",(");
            instr->imm = atoi(imm_str);
            token = strtok(NULL, "(),"); 
            if (token != NULL) {
                if(token[0] != 'x') return printUnknown(instr, token);
                instr->rs1 = atoi(token + 1); 
            }
            else return printError(instr);
        } else {
            if(token[0] != 'x') return printUnknown(instr, token);
            instr->rs1 = atoi(token+1);
            token = strtok(NULL, " ,\t");
            if (token != NULL) instr->imm = atoi(token); 
            else return printError(instr);
        }
    } else return printError(instr);
    if (strtok(NULL, " ),\t\n") != NULL) {
        fprintf(stderr, "\033[1;7;31mError: Too many operands for instruction %s\n\033[0m", instr->name); 
        free(instr->name);
        free(instr);
        return NULL;
    }

    return instr;
}

Instruction* JTypeInstruction(char* token, struct LabelTable *table) {
    Instruction* instr = (Instruction*) malloc(sizeof(Instruction));
    if (instr == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    
    instr->name = strdup(token); // Set opcode
    if (instr->name == NULL) {
        perror("Memory allocation failed for instruction name");
        free(instr); // Free the allocated memory for instr before returning NULL
        return NULL;
    }

    token = strtok(NULL, " ,\t\n");
    if (token != NULL) {
        if(token[0] != 'x') return printUnknown(instr, token);
        instr->rd = atoi(token + 1);
    }
    else return printError(instr); 
    token = strtok(NULL, " ,\t\n");  
    if(token != NULL) {        
        if(token[0] != 'x') return printUnknown(instr, token);
        instr->rs1 = atoi(token+1);
    }
    else return printError(instr);
    token = strtok(NULL, " ,\t\n"); 
    if(token != NULL) instr->imm = atoi(token); 
    else {
        fprintf(stderr, "\033[1;7;31mError: Missing operand for instruction %s\n\033[0m", instr->name); 
        free(instr->name);
        free(instr);
        return NULL;
    }
    // Check for extra operands
    if (strtok(NULL, " ),\t\n") != NULL) {
        fprintf(stderr, "\033[1;7;31mError: Too many operands for instruction %s\n\033[0m", instr->name); 
        free(instr->name);
        free(instr);
        return NULL;
    }

    return instr;
}

Instruction * STypeInstruction(char * token) {
    Instruction* instr = (Instruction*) malloc(sizeof(Instruction));
    if (instr == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    instr->name = strdup(token);
    // Extract rs2, rs1, immediate
    token = strtok(NULL, " ,\t");
    if (token != NULL) {
        if(token[0] != 'x') return printUnknown(instr, token);
        instr->rs2 = atoi(token + 1);
    }
    else return printError(instr);
    token = strtok(NULL, " ,\t");
    if (token != NULL) {
        char* imm_str = strtok(token, "()");
        instr->imm = atoi(imm_str);
        token = strtok(NULL, "(),"); 
        if (token != NULL) {
            if(token[0] != 'x') return printUnknown(instr, token);
            instr->rs1 = atoi(token + 1); 
        }  
        else return printError(instr); 
    } else return printError(instr);

    if (strtok(NULL, " ),\t\n") != NULL) {
        fprintf(stderr, "\033[1;7;31mError: Too many operands for instruction %s\n\033[0m", instr->name); 
        free(instr->name);
        free(instr);
        return NULL;
    }
    return instr;
}




Instruction * BTypeInstruction(char * token, struct LabelTable * table) {
    Instruction* instr = (Instruction*) malloc(sizeof(Instruction));
    if (instr == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    instr->name = strdup(token); // Set opcode

    // Extract rs1, rs2, immediate 
    token = strtok(NULL, " ,\t");
    if (token != NULL) {
        if(token[0] != 'x') return printUnknown(instr, token);
        instr->rs1 = atoi(token + 1); 
    }
    else return printError(instr);
    token = strtok(NULL, " ,\t");
    if (token != NULL){
        if(token[0] != 'x') return printUnknown(instr, token);
         instr->rs2 = atoi(token + 1);
    }
    else return printError(instr); 
    token = strtok(NULL, " ,\t\n");
    if (token != NULL) instr->imm = lookupLabel(table, token);
    else return printError(instr);
    if(instr->imm == -1) {
        fprintf(stderr, "\033[1;7;31mError: No such label\"%s\" exists. \n\033[0m", token); 
        free(instr->name);
        free(instr);
        return NULL;
    }

    if (strtok(NULL, " ,\t\n") != NULL) {
        fprintf(stderr, "\033[1;7;31mError: Too many operands for instruction %s\n\033[0m", instr->name); 
        free(instr->name);
        free(instr);
        return NULL;
    }

    return instr;
}

Instruction * RTypeInstruction(char * token) {
    Instruction* instr = (Instruction*) malloc(sizeof(Instruction));
    if (instr == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }
    instr->name = strdup(token); 
    // Extract rd, rs1, rs2 
    token = strtok(NULL, " ,\t"); 
    if (token != NULL) {
        if(token[0] != 'x') return printUnknown(instr, token);
        instr->rd = atoi(token + 1); 
    }
    else return printError(instr);
    token = strtok(NULL, " ,\t"); 
    if (token != NULL) instr->rs1 = atoi(token + 1); 
    else return printError(instr);
    token = strtok(NULL, " ,\t\n");
    if (token != NULL) instr->rs2 = atoi(token + 1);
    else return printError(instr);
    if (strtok(NULL, " ,\t\n") != NULL) {
        fprintf(stderr, "\033[1;7;31mError: Too many operands for instruction %s\n\033[0m", instr->name); 
        free(instr->name);
        free(instr);
        return NULL;
    }

    return instr;
}



bool parseLabels(FileParser * parser, struct LabelTable * table, int addr){
    char line[150]; 
    if (fgets(line, sizeof(line), parser->file) == NULL) {
        return false;
    }
    /* Parse the line. */
    char* token = strtok(line, " ,\t\n");
    /* Check for label definition */
    if(token != NULL && token[strlen(token) - 1] == ':') { 
        token[strlen(token) - 1] = '\0'; 
        addLabelToTable(&(table->labels), token, addr);
    } 
    return true;
}

Instruction* parseNextInstruction(FileParser * parser, struct LabelTable * table) {
    // printf("parseNext:  LabelTable Pointer: %p, Labels Array Pointer: %p\n", table, table->labels);
    char line[150]; 
    if (fgets(line, sizeof(line), parser->file) == NULL) return NULL; 

    /*  Ignore comments */
    if (line[0] == '#' ) {
        Instruction* instr = (Instruction*) malloc(sizeof(Instruction));
        instr->isComment = true;
        instr->name = NULL;
        return instr;       
    }
    /*  Detect and remove comments */
    char* comment_pos = strchr(line, '#');
    if (comment_pos != NULL) {
        *comment_pos = '\0'; // Truncate the line at the position of the comment
    }
    // printf("line: %sline\n", line);
    if(strstr(line, "ecall\0\n") != NULL) return NULL;
    replace(line, "ret", "jalr x0 x1 0");
    replace(line, "sp", "x2");
    replace(line, " sp,", " x2 ");
    replace(line, " ra ", " x1 ");
    replace(line, " ra,", " x1 ");
    replace(line, " zero ", " x0 ");
    replace(line, " zero, ", " x0 ");
    replace(line, "call", "jal x1");
    
    if(strstr(line, "j ") != NULL) {
        replace(line, "j ", "jal x0 ");
    } else if(strstr(line, "jr ") != NULL){
        replace(line, "\n", "");
        replace(line, "\t", "");
        replace(line, "jr", "jalr x0 ");
        strcat(line, "0\n");
    } else if((strstr(line, "mv ") != NULL)){
        replace(line, "\n", "");
        replace(line, "\t", "");
        replace(line, "mv ", "add ");
        strcat(line, " x0\0\n");
    } 

    /* Parse the line. */
    char* token = strtok(line, " ,\t\n\r");
    if(token == NULL || token[strlen(token) - 1] == ':') {
        Instruction* instr = (Instruction*) malloc(sizeof(Instruction));
        instr->name = NULL;
        instr->isLabel = true;
        return instr;
    } 


    if(strcmp(token, "add") == 0 || strcmp(token, "mul") == 0 ||
        strcmp(token, "sub") == 0  || strcmp(token, "div") == 0 ) {
        return RTypeInstruction(token);
    } else if(strcmp(token, "lh") == 0 || strcmp(token, "lb") == 0 ||
             strcmp(token, "lw") == 0  || strcmp(token, "addi") == 0 
             || strcmp(token, "srai")== 0 || strcmp(token, "srli")== 0
             || strcmp(token, "slai")== 0 || strcmp(token, "slli")== 0
             || strcmp(token, "jal")==0){
        return ITypeInstruction(token, table);
    } else if(strcmp(token, "sw") == 0 || strcmp(token, "sh") == 0 ||
            strcmp(token, "sb") == 0  ){
        return STypeInstruction(token);
    } else if(strcmp(token, "bge") == 0 || strcmp(token, "bne") == 0 ||
            strcmp(token, "beq") == 0  || strcmp(token, "blt") == 0  ||
            strcmp(token, "ble")==0 || strcmp(token, "bgt") == 0){
        return BTypeInstruction(token, table);
    } else if(strcmp(token, "jalr") == 0){
        return JTypeInstruction(token, table);
    }   

    printf("\033[1;7;31m [-] Invalid Instruction\n\033[0m");
    return NULL;
}


