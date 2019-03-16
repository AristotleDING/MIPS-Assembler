/*****************************
 * File name:phase2.c
 * Purpose: Impliment functions to read and translate the file
 *          by using the table returned by phase1.
 *          Functions execpt translateType were defined in phase2.h.
 ****************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "phase2.h"
#include <stdint.h>
#include <math.h>
#include "labeltable.h"
const char* IGNORE_CHARS;

//call the eliminateComments function defined in phase1.h
void eliminateComments(char *text);

/*************************************************************************
 * Function: translateType
 * Purpose: Translate each line of MIPS instructions in to binary machine code.
 * Implimentation idea: 1. 4 arrays were made(Name[], OPcode[], Type[] and Func[])
 *                          using same index sequence.
 *                          One can iterate and find the name, opcode and type for one
 *                          index. And if it's a R type instruction, the function bit can also
 *                          be found.
 *                      2. With the type of the instruction known, specific translation process
 *                          was apply to R, I and J type instructions. Please Refer to comments
 *                          between the lines of implimentation for more details.
 ***************************************************************************/
void translateType(char *name, char **inst, char **args, LabelTable *table);



/**************** FUNCTION IMPLIMENTATIONS ****************/

int phase2(LabelTable *table, char *filename){
    FILE *fp;
    char text[300];
    //int numOfLine = 0;
    char *args[5];

    fp=fopen(filename,"r");
    FILE *fpo;
    fpo = fopen("output.txt", "w");

    if (!fp || !fpo){
        printf("Could not open temporary file");
    }


    while (fgets(text,200,fp) != NULL){

        eliminateComments(text);

        char* token = strtok(text, IGNORE_CHARS);
        if(token == NULL){
            continue;
        }
        int lenthOfStarter = strlen(token);

        if (strcmp(token, "\n") == 0){
            continue;
        }
        if (token[lenthOfStarter - 1] == ':'){
            token[lenthOfStarter - 1] = '\0';
            //int addresult = addLabel(table, token, numOfLine);
            //if (addresult == 1){
            token = strtok(NULL, IGNORE_CHARS);
            if(token == NULL){
                continue;
            }
            //lenthOfStarter += 1;
            //}
        }
        char *inst[10];
        char name[10];
        strcpy(name, token);
        int num_args = 0;
        while (token != NULL){
            char *temp = token;
            args[num_args] = temp;
            token = strtok(NULL, IGNORE_CHARS);
            num_args++;
        }

        (void)translateType(name, inst, args, table);
        //printf("%s\n",decimalToBinary(-6, 5));
        if(strcmp(inst[6],"I") == 0){
            fprintf(fpo,"%s", inst[0]);
            fprintf(fpo,"%s", inst[1]);
            fprintf(fpo,"%s", inst[2]);
            fprintf(fpo,"%s\n", inst[3]);
        }else if(strcmp(inst[6],"R") == 0){
            fprintf(fpo,"%s", inst[0]);
            fprintf(fpo,"%s", inst[1]);
            fprintf(fpo,"%s", inst[2]);
            fprintf(fpo,"%s", inst[3]);
            fprintf(fpo,"%s", inst[4]);
            fprintf(fpo,"%s\n", inst[5]);
        }else{
            fprintf(fpo,"%s", inst[0]);
            fprintf(fpo,"%s\n", inst[1]);
        }

    }
    (void)fclose(fp);
    (void)fclose(fpo);
    return 0;
}


void translateType(char *name, char **inst, char **args, LabelTable *table){
    //printf("Enter!");
    static char *Name[] = {
        "add",
        "addu",
        "and",
        "div",
        "divu",
        "jr",
        "mfhi",
        "mflo",
        "mthi",
        "mtlo",
        "mult",
        "multu",
        "nor",
        "or",
        "sll",
        "slt",
        "sltu",
        "srl",
        "sub",
        "subu",
        "xor",
        "addi",
        "addiu",
        "andi",
        "beq",
        "bgez",
        "bgtz",
        "blez",
        "bltz",
        "bne",
        "lb",
        "lbu",
        "lui",
        "lw",
        "ori",
        "sb",
        "slti",
        "sltiu",
        "sw",
        "xori",
        "j",
        "jal",
    };
    static char *OPcode[] = {
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "000000",
        "001000",
        "001001",
        "001100",
        "000100",
        "000001",
        "000111",
        "000110",
        "000001",
        "000101",
        "100000",
        "100100",
        "001111",
        "100011",
        "001101",
        "101000",
        "001010",
        "001011",
        "101011",
        "001110",
        "000010",
        "000011",
    };
    static char *Type[] = {
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "R",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "I",
        "J",
        "J",
    };
    static char *Func[] = {
        "100000",
        "100001",
        "100100",
        "011010",
        "011011",
        "001000",
        "010000",
        "010010",
        "010001",
        "010011",
        "011000",
        "011001",
        "100111",
        "100101",
        "000000",
        "101010",
        "101011",
        "000010",
        "100010",
        "100011",
        "100110",
    };
    for (int i = 0; i < 42; i++){
        if (strcmp(name, Name[i]) == 0){
            inst[0] = OPcode[i];
            inst[6] = Type[i];

            // R Type:
            // inst      0       1         2          3       4       5
            //         opcode    rs        rt         rd      sa      function
            if (strcmp(inst[6], "R") == 0){
                inst[5] = Func[i];
                // deal with sll and srl
                if (strcmp(name, "sll") == 0 || strcmp(name, "srl") == 0){
                    inst[1] = "00000";
                    inst[2] = getReg(args[2]);
                    inst[3] = getReg(args[1]);
                    inst[4] = getNum(args[3]);
                }
                // deal with jr, mthi and mtlo
                else if (i == 5 || i == 8 || i == 9){
                    inst[1] = getReg(args[1]);
                    inst[2] = "00000";
                    inst[3] = "00000";
                    inst[4] = "00000";
                }
                // deal with div, divu, mult, multu
                else if (i == 3 || i == 4 || i == 10 || i == 11){
                    inst[1] = getReg(args[1]);
                    inst[2] = getReg(args[2]);
                    inst[3] = "00000";
                    inst[4] = "00000";
                }
                // deal with mfhi and mflo
                else if (i == 6 || i == 7){
                    inst[3] = getReg(args[1]);
                    inst[2] = "00000";
                    inst[1] = "00000";
                    inst[4] = "00000";
                }
                // other cases
                else{
                    inst[1] = getReg(args[2]);
                    inst[2] = getReg(args[3]);
                    inst[3] = getReg(args[1]);
                    inst[4] = "00000";
                }
            }
            // I Type:
            // inst      0       1         2          3
            //         opcode    rs         rt      immediate
            else if(strcmp(inst[6], "I") == 0){
                //for beq, bne,
                if ( i == 24 || i == 29 ){
                    inst[1] = getReg(args[1]);
                    inst[2] = getReg(args[2]);
                    char *name = args[3];
                    int address = getAddressFromTable(table, name);
                    if (address != -1){
                        inst[3] = decimalToBinary(address, 16);
                    }
                }
                // for bgez, bgtz, blez, bltz
                else if (i > 24 && i < 29){
                    inst[1] = getReg(args[1]);
                    char *name = args[2];
                    int address = getAddressFromTable(table, name);
                    if (address != -1){
                        inst[3] = decimalToBinary(address, 16);
                        if (strcmp(args[0], "bgez") == 0){
                            inst[2] = "00001";
                        }else{
                            inst[2] = "00000";
                        }
                    }
                }
                // for lb, lbu, lw, sb, sw
                else if (i == 30 || i == 31 || i == 33 || i == 35 || i == 38){
                    inst[2] = getReg(args[1]);
                    char *endptr;
                    long int immediate = strtol(args[2], &endptr, 0);
                    inst[3] = decimalToBinary(immediate, 16);
                    inst[1] = getReg(args[3]);
                }
                //deal with lui
                else if (i == 32){
                    inst[2] = getReg(args[1]);
                    char *endptr;
                    long int immediate = strtol(args[2], &endptr, 0);
                    inst[3] = decimalToBinary(immediate, 16);
                    inst[1] = "00000";
                }
                // deal with others (e.g. addi)
                else{
                    inst[1] = getReg(args[2]);
                    inst[2] = getReg(args[1]);
                    char *endptr;
                    long int immediate = strtol(args[3], &endptr, 0);
                    inst[3] = decimalToBinary(immediate, 16);
                }
            }
            // J Type:
            // inst     0       1
            //          opcode  target
            // deal with j and jal
            else{
                char *name = args[1];
                int address = getAddressFromTable(table, name);
                if (address != -1){
                    inst[1] = decimalToBinary(address, 26);
                }
            }
        }
    }
}

char *getReg(const char *arg){
    if (strcmp(arg, "$zero") == 0)      return "00000";
    else if (strcmp(arg, "$0") == 0)    return "00000";
    else if (strcmp(arg, "$at") == 0)   return "00001";
    else if (strcmp(arg, "$v0") == 0)   return "00010";
    else if (strcmp(arg, "$a0") == 0)   return "00100";
    else if (strcmp(arg, "$a1") == 0)   return "00101";
    else if (strcmp(arg, "$a2") == 0)   return "00110";
    else if (strcmp(arg, "$a3") == 0)   return "00111";
    else if (strcmp(arg, "$t0") == 0)   return "01000";
    else if (strcmp(arg, "$t1") == 0)   return "01001";
    else if (strcmp(arg, "$t2") == 0)   return "01010";
    else if (strcmp(arg, "$t3") == 0)   return "01011";
    else if (strcmp(arg, "$t4") == 0)   return "01100";
    else if (strcmp(arg, "$s0") == 0)   return "10000";
    else if (strcmp(arg, "$s1") == 0)   return "10001";
    else if (strcmp(arg, "$s2") == 0)   return "10010";
    else if (strcmp(arg, "$s3") == 0)   return "10011";
    else if (strcmp(arg, "$sp") == 0)   return "11101";
    else if (strcmp(arg, "$ra") == 0)   return "11111";
    else                                return "ERROR";
}

char *getNum(const char *num){
    char *endptr;
    long int result = strtol(num, &endptr, 0);
    if (result == 0)      return "00000";
    else if (result == 1)   return "00001";
    else if (result == 2)   return "00010";
    else if (result == 3)   return "00011";
    else if (result == 4)   return "00100";
    else if (result == 5)   return "00101";
    else if (result == 6)   return "00110";
    else if (result == 7)   return "00111";
    else if (result == 8)   return "01000";
    else if (result == 9)   return "01001";
    else if (result == 10)   return "01010";
    else if (result == 11)   return "01011";
    else if (result == 12)   return "01100";
    else if (result == 13)   return "01101";
    else if (result == 14)   return "01110";
    else if (result == 15)   return "01111";
    else if (result == 16)   return "10000";
    else if (result == 17)   return "10001";
    else if (result == 18)   return "10010";
    else if (result == 19)   return "10011";
    else if (result == 20)   return "10100";
    else if (result == 21)   return "10101";
    else if (result == 22)   return "10110";
    else if (result == 23)   return "10111";
    else if (result == 24)   return "11000";
    else if (result == 25)   return "11001";
    else if (result == 26)   return "11010";
    else if (result == 27)   return "11011";
    else if (result == 28)   return "11100";
    else if (result == 29)   return "11101";
    else if (result == 30)   return "11110";
    else if (result == 31)   return "11111";
    else                     return "ERROR";
}


char *decimalToBinary(int n, int bit){
   int c, d, count;
   char *pointer;

   count = 0;
   pointer = (char*)malloc(64+1);


   if (pointer == NULL)
      exit(EXIT_FAILURE);

   for (c = 63 ; c >= 0 ; c--)
   {
      d = n >> c;

      if (d & 1)
         *(pointer+count) = 1 + '0';
      else
         *(pointer+count) = 0 + '0';

      count++;
   }
   *(pointer+count) = '\0';

   return  pointer+(64-bit);
}

