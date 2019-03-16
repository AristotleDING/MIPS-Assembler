/*****************************
 * File name:labeltable.c
 * Purpose: Impliment functions to manage the table.
 *          Functions were defined in labeltable.h.
 ****************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "labeltable.h"



/**************** FUNCTION IMPLIMENTATIONS ****************/

LabelTable *createTable(){
    LabelTable *table = (LabelTable*)malloc(sizeof(LabelTable));
    table->numOfLabels = 0;
    table->labels = malloc(100 * sizeof(Label));
    return table;
}

int addLabel(LabelTable *table, char *name, int address){

    if (table == NULL) return 0;

    table->labels[table->numOfLabels].label = malloc(10 * sizeof(char));
    strcpy(table->labels[table->numOfLabels].label, name);
    table->labels[table->numOfLabels].address =  address;
    table->numOfLabels += 1;
    return 1;
}

int getAddressFromTable(LabelTable *table, const char *name){
    for (int i = 0; i < table->numOfLabels; i++){
        if (strcmp(name, table->labels[i].label) == 0){
            return table->labels[i].address;
        }
    }
    return -1;
}
