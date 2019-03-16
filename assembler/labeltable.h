/*****************************
 * File name:labeltable.h
 * Purpose:  DS LabelTable and label has been defined here.
 *           Used to Store the name and the address of each label
 *           read in phase1.
 ****************************/
#ifndef LABLETABLE_H
#define LABLETABLE_H


/******************************
 * Data Structure:Label
 * Purpose: Store the name of a label(label),
 *          and the address of it(address).
 *          It's the basic unit in LabelTabel.
 ******************************/
typedef struct {
    char *label;
    int address;
}Label;

/******************************
 * Data Structure:LabelTable
 * Purpose:Store labels in a linked structure,
 *         each Label can be access by using
 *         the numOfLabels as index.
 ******************************/
typedef struct {
    Label *labels;
    int numOfLabels;
}LabelTable;


/*****************************
 * Function: createTable
 * Purpose: Pre-acquire memory for LabelTable and Label;
 *          set numOfLabels to 0.
 *****************************/
LabelTable *createTable();

/*****************************
 * Function: addLabel
 * Purpose: Acquire memory for the new label found in phase1,
 *          then link the name as label, numofline as address,
 *          updating the numOfLabels.
 *****************************/
int addLabel(LabelTable *table, char *name, int address);


/*****************************
 * Function: getAddressFromTable
 * Purpose: Use the name of the lable to get the corresponding address.
 *          used in phase2.
 *****************************/
int getAddressFromTable(LabelTable *table, const char *name);

#endif // LABLETABLE_H
