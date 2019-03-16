/********************** N O T I C E****************************
 * There is no phase1.c because there are only two functions in phase1.
 **************************************************************/

/*****************************
 * File name:phase1.c
 * Purpose: Read in the file and find all the labels.
 *          Then pass the name and the address of the label.
 *          Take the filename as the parameter and return a
 *          LabelTable generated.
 ****************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "labeltable.h"

// Used to deconstruct the tabel in to text-only file.
const char* IGNORE_CHARS = " \f\n\t\r\v,()";

/*****************************
 * Function:eliminateComments
 * Purpose:  eliminate the content after "#".
 ****************************/
void eliminateComments(char *text);



/**************** FUNCTION IMPLIMENTATIONS ****************/
LabelTable *phase1(char *filename){
    FILE *fp;
    char text[1024];
    int numOfLine = 0;
    LabelTable *table = createTable();

    fp=fopen(filename, "r");
    if (!fp){
        printf("Could not open temporary file");
    }

    while (fgets(text,1024,fp) != NULL){

        eliminateComments(text);

        char* token = strtok(text, IGNORE_CHARS);
        if(token == NULL){
            continue;
        }
        int lenthOfStarter = strlen(token);

        if (token[lenthOfStarter - 1] == ':'){
            token[lenthOfStarter - 1] = '\0';
            int addresult = addLabel(table, token, numOfLine);
            if (addresult == 1){
                token = strtok(NULL, IGNORE_CHARS);
                if(token == NULL){
                    continue;
                }
                   //lenthOfStarter += 1;
            }
        }
         token = strtok(NULL, IGNORE_CHARS);
         while(token != NULL){
             token = strtok(NULL, IGNORE_CHARS);
         }

        numOfLine++;
    }
    (void)fclose(fp);
    return table;
}

void eliminateComments(char *text){
    char *comment = strchr(text, '#');
    if (comment) {
        *comment = '\0';
    }
}
