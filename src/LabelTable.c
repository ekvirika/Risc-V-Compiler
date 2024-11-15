#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/LabelTable.h"

void iterateLabels(struct LabelTable *table) {
    printf("Labels: %d\n", table->num_labels);
    for (int i = 0; i < table->num_labels; i++) {
        printf("Label %d: Name=%s, Address=%d\n", i + 1, table->labels[i].name, table->labels[i].address);
    }
}

void labelTableInit(struct LabelTable * table){
    table->labels = malloc(50 * sizeof(struct Label));
    if (table->labels == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for labels array\n");
        exit(EXIT_FAILURE);
    }
    table->num_labels = 0;
}

void labelTableDestroy(struct LabelTable * table){
    if (table == NULL) return;
    for (int i = 0; i < table->num_labels; i++) {
        if (table->labels[i].name != NULL) {
            free(table->labels[i].name);
        }
    }
    free(table->labels);  
}



int lookupLabel(struct LabelTable * table, char * name){
    // printf("lookupLabel:  LabelTable Pointer: %p, Labels Array Pointer: %p\n", table, table->labels);
    int n = table->num_labels;
    for(int i = 0; i < n; i++){
        if(table->labels[i].name != NULL && strcmp(table->labels[i].name, name) == 0){
            return table->labels[i].address;
        }
    }
    return -1;
}


void addLabelToTable(struct LabelTable *table, char *name, int address) {
    if (table == NULL || name == NULL) {
        fprintf(stderr, "Error: Invalid arguments\n");
        return;
    }
    if (table->num_labels >= 100) {
        fprintf(stderr, "Error: Label table full\n");
        return;
    }
    char *new_name = strdup(name);
    if (new_name == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for label name\n");
        return;
    }
    table->labels[table->num_labels].name = new_name;
    table->labels[table->num_labels].address = address+1;
    table->num_labels++;
}
