#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "labeltable.h"


LabelTable *phase1(char *filename);
int phase2(LabelTable *table, char *filename);


/*********************** N O T I C E ******************************
 * Following changes are made to to original main(int argc, char * argv[]) function.
 *
 * 1. Please input the test and eo file correctly(e.g. testfile.asm), or an error will be generated.
 *
 * 2. The argc is set to the lenth of argv.
 *
 * 3.In my labeltable.h, table is defined by LabelTable *char instead of LabelTable char.
 *
 **************/


//int main(){
//    char filename[1024];
//    printf("Please input you testfile:\n");
//    scanf("%s",filename);
//    LabelTable *table;
//    table = phase1 (filename);
//    (void)phase2(table, filename);
//    return 0;
//}

int compare_files(FILE* fp1, FILE* fp2)
{
    char char1 = fgetc(fp1);
    char char2 = fgetc(fp2);

    while(char1 != EOF && char2 != EOF){
        if(char1 != char2){
            return -1;
        }
        char1 = fgetc(fp1);
        char2 = fgetc(fp2);
    }
    while(char1 != EOF && (char1 == ' ' || char1 == '\n') ){
        char1 = fgetc(fp1);
    }
    while(char2 != EOF && (char2 == ' ' || char2 == '\n')){
        char2 = fgetc(fp2);
    }
    if(char1 == EOF && char2 == EOF){
        return 0;
    }
    return -1;
}
int main (int argc, char * argv[])
{
    char filename[1024];
    printf("Please input you testfile:\n");
    scanf("%s",filename);
    FILE *fp;
    if ((fp = fopen(filename, "r")) == NULL){
        (void)fprintf(stderr,"Error: Could not open temporary file\n");
        return 0;
    }
    (void)fclose(fp);

    char filename2[1024];
    printf("Please input you expectedoutput file:\n");
    scanf("%s",filename2);
    FILE *fpeo;
    if ((fpeo = fopen(filename2, "r")) == NULL){
        (void)fprintf(stderr,"Error: Could not open temporary file\n");
        return 0;
    }
    (void)fclose(fpeo);

    // Edited version
    argv[0] = "assembler";
    argv[1] = filename;
    argv[2] = "output.txt";
    argv[3] = filename2;
    argc = strlen(*argv);
    if(argc < 4)
    {
        printf("Please enter an input file, an output file, and expected output file \n");
    }
    // Edited version
    LabelTable *table;
    table = phase1 (argv[1]);
    (void)phase2(table, argv[1]);

    FILE* fp1;
    FILE* fp2;
    fp1 = fopen(argv[3], "r");
    fp2 = fopen(argv[2], "r");

    if(fp1 == NULL || fp2 == NULL){
        printf("Error: Files are not open correctly \n");
    }

    int res = compare_files(fp1, fp2);

    if(res == 0){
        printf("ALL PASSED! CONGRATS :) \n");
    }else{
        printf("YOU DID SOMETHING WRONG :( \n");
    }

    fclose(fp1);
    fclose(fp2);
    
    return 0;
}

