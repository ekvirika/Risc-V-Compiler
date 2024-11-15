#ifndef LABEL_TABLE_H
#define LABEL_TABLE_H

typedef struct Label {
   char* name;
   int address; 
} Label;

typedef struct LabelTable {
   struct Label * labels;
   int num_labels;
} LabelTable;


void labelTableInit(struct LabelTable * table);
void labelTableDestroy(struct LabelTable * table);
void addLabelToTable(struct LabelTable *table, char * name, int address);
int lookupLabel(struct LabelTable * table, char * name);
void iterateLabels(struct LabelTable *table);

#endif