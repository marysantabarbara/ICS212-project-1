/*****************************************************************
//
// NAME: Mary Santabarbara
//
// HOMEWORK: Project 1
//
// CLASS: ICS 212
//
// INSTRUCTOR: Ravi Narayan
//
// DATE: March 7, 2016
//
// FILE: database.c
//
// DESCRIPTION: This file contains the bank database functions for 
//		project 1. 
//
//****************************************************************/

#include "prototypes.h"

extern int debugmode;

/*****************************************************************
//
// Function name: addRecord
//
// DESCRIPTION: A data function 
// 		This function gets the values from the paramaters and 
//		stores the values in the data base.
//
// Parameters: 	start (record**) : the start of the linked list.
//		accountno (int) : the new account number of the person
//		name (char[]) : the name of the person
//		address (char[]) : the address of the person
//		yearofbirth (int) : the year of birth of the person
//
// Return values: 0 : success
// 		 -1 : failure
//
//****************************************************************/
int addRecord(struct record** start, int accountno, char name[], char address[], int yearofbirth)
{
    struct record * current = *start;
    struct record * newRecord;
    struct record * next;
    int on = 1;
    int returnValue = -1;

    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction called: addRecord\n");
        printf("Paramaters passed:\n");

        printf("start: %u\n", &start);
        printf("accountno : %d\n", accountno);
        printf("name: %s\n", name);
        printf("address: %s\n", address);
        printf("yearofbirth: %d\n", yearofbirth);
        printf("\n");
    }

    newRecord = (struct record*) malloc(sizeof(struct record));
    newRecord->accountno = accountno;
    strcpy(newRecord->name, name);
    strcpy(newRecord->address, address);
    newRecord->yearofbirth = yearofbirth;

    if(current == NULL || accountno < current->accountno)
    {
        newRecord->next = current;
        *start = newRecord;
        on = 0;
        returnValue = 0;
    }
    else
    {
        
        while(on == 1 && current != NULL)
        {
            next = current->next;
            
            if(next == NULL)
            {                
                current->next = newRecord;
                newRecord->next = NULL;
                on = 0;
                returnValue = 0;
            }
            else if(accountno < next->accountno)
            {   
                current->next = newRecord;
                newRecord->next = next;
                on = 0;
                returnValue = 0;
            }
            else
            {
                current = next;
            }
        }
    }

    return returnValue;
}   

/*****************************************************************
//
// Function name: printRecord
//
// DESCRIPTION: A data function 
// 		This function prints a specific record with the 
//		account number as key. The function will iterate from
//		start and find the account number and print that record.
//
// Parameters: start (record*) : the start of the linked list.
//	       accountno (int) : the number of the account being printed.
//
// Return values: 0 : success
//		  -1 : if the account no. was not found
//
//****************************************************************/
int printRecord (struct record * start, int accountno)
{
    struct record * current = start;
    int returnValue = -1;

    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction called: printRecord\n");
        printf("Paramaters passed:\n");

        printf("start : %u\n", &start);
        printf("accountno: %d\n", accountno);
        printf("\n");
    }
     
    printf("\n");

    while(current != NULL)
    {
        if(accountno == current->accountno)
        {
            printf("%d\n", current->accountno);
            printf("%s\n", current->name);
            printf("%s\n", current->address);
            printf("%d\n", current->yearofbirth); 
            printf("\n");
 
            returnValue = 0;
        }

        current = current->next;
    }

    return returnValue;
}

/*****************************************************************
//
// Function name: modifyRecord
//   
// DESCRIPTION: A data function
//              This function modifies a specific record with the
//              account number as key. The function will only modify the 
//		address.
//
// Parameters: start (record*) : the start of the linked list.
//              accountno (int) : the number of the account being printed
//   		update (char[]) : the updated information for the record
//
// Return values: 0 : success
//		 -1 : the value was not found
//
//****************************************************************/
int modifyRecord (struct record * start, int accountno, char update[ ])
{
    struct record * current = start;
    int returnValue = -1;
    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction called: modifyRecord\n");
        printf("Paramaters passed:\n");

        printf("start: %u\n", &start);
        printf("accountno : %d\n", accountno);
        printf("update: %s\n", &update);
        printf("\n");
    }

    while(current != NULL)
    {
        if(accountno == current->accountno)
        {
            strcpy(current->address, update);
            returnValue = 0;
        }
        current = current->next;
    }

    return returnValue;
}

/*****************************************************************
//
// Function name: printAllRecords
//   
// DESCRIPTION: A data function
//              This function prints a specific record with the
//              account number.
//
// Parameters: start (record*) : the start of the linked list.
//
//****************************************************************/
void printAllRecords(struct record * start)
{
    struct record * current = start;

    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction called: printAllRecord\n");
        printf("Paramaters passed:\n");

        printf("start: %u\n", &start);
        printf("\n");
    }

    printf("\n");

    while(current != NULL)
    {
        printf("%d\n", current->accountno);
        printf("%s\n", current->name);
        printf("%s\n", current->address);
        printf("%d\n", current->yearofbirth);
        printf("\n");

        current = current->next;
    }
}

/*****************************************************************
//
// Function name: deleteRecord
//   
// DESCRIPTION: A data function
//              This function prints a specific record with the
//              account number.
//
// Parameters: start (record**) : the start of the linked list.
//              accountno (int) : the number of the account being printed.
//   
// Return values: 0 : success
// 		 -1 : the account number  not found
//
//****************************************************************/
int deleteRecord(struct record ** start, int accountno)
{
    struct record * previous = *start;
    struct record * current = *start;
    struct record * delete;
    int returnValue = -1;

    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction called: deleteRecord\n");
        printf("Paramaters passed:\n");

        printf("start: %u\n", &start);
        printf("accountno : %d\n", accountno);
        printf("\n");
    }

    while(current != NULL)
    {
        if(current == *start)
        {
            if(accountno == current->accountno)
            {
                delete = current;
                *start = current->next;
                current = current->next;
                previous = previous->next;

                free(delete);

                returnValue = 0;
             }
             else
             {
                 current = current->next;
             }
        }
        else if(accountno == current->accountno)
        {
            delete = current;
            previous->next = current->next;
            current = current->next;

            free(delete);
 
            returnValue = 0;
        }
        else
        {
            previous = previous->next;
            current = current->next;
        }
        
    }

    return returnValue;
}

/*****************************************************************
//
// Function name: readfile
//
// DESCRIPTION: A data function 
// 		This function reads a file and then puts the information
//		into a linked list.
//
// Parameters: start (record **) : the start of the record list.
//	       filename (char[])  : the name of the file to be read.
//
// Return values: 0 : success
//		  -1 : the file was not found.
//
//****************************************************************/
int readfile(struct record ** start, char filename[])
{
    FILE * inbuffer;
    char * mode = "r";
    int accountno, yob;
    char name[25], address[80];
    char trash[10], c;
    int returnValue = 0;

    if(debugmode)
    { 
        printf("Debug Mode On\n");

        printf("\nFunction call: readfile\n");
        printf("Parameters passed\n");
 
        printf("start: %u\n", &start);
        printf("filename: %s\n", filename);
    }

    inbuffer = fopen(filename, mode);

    if(inbuffer == NULL)
    {
        returnValue = -1;
    }
    else
    {
        while(fscanf(inbuffer, "%d", &accountno) !=  EOF)
        {
           fgets(trash, 10, inbuffer); /*gets the line after the fscan*/

           fgets(name, 25, inbuffer);
           strtok(name, "\n");

           fgets(address, 80, inbuffer);
           strtok(address, "\n");

           fscanf(inbuffer, "%d", &yob);
           fgets(trash, 10, inbuffer);
 
           fgets(trash, 10, inbuffer); /*Gets rid of the line break.*/
           
           addRecord(start, accountno, name, address, yob); 
           
       }
    }
 
    fclose(inbuffer);

    return returnValue;
}

/*****************************************************************
//
// Function name: writefile  
//
// DESCRIPTION: A data function
//              This function writes all the information into a file.        
//
// Parameters: start (record *) : the start of the record list.
//             filename (char[])  : the name of the file to be read.
//
//****************************************************************/
void writefile(struct record * start, char filename[])
{
    FILE * outbuffer;
    char * mode = "w";
    struct record * current = start;

    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction call: writefile\n");
        printf("Parameters passed\n");
     
        printf("start: %u\n", &start);
        printf("filename: %s\n", filename);
    }

    outbuffer = fopen(filename, mode);

    while(current != NULL)
    {
        fprintf(outbuffer, "%d\n", current->accountno);
        fprintf(outbuffer, "%s\n", current->name);
        fprintf(outbuffer, "%s\n", current->address);
        fprintf(outbuffer, "%d\n", current->yearofbirth);
        fprintf(outbuffer, "\n");

        current = current->next;
    }

    fclose(outbuffer);
}
