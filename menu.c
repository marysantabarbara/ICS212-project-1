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
// FILE: menu.c
//
// DESCRIPTION: This file contains the driver and the user-interface functions
// 		for Project 1. 
//
//****************************************************************/

#include "prototypes.h"

void isDebug(int, char*[]);
void printMenu();
int getOptionInput();
void getInfo(int*, char[], char[], int*);
int getAccountNo();
void getfield(char[], int);

int debugmode;

/*****************************************************************
//
// Function name: main
//
// DESCRIPTION: A driver
// This function calls the methods and handles user interface.
//
// Parameters: argc (int) : number of argments.
//	       argv (char*[]) : the poiner to the string of arguments.
//
//****************************************************************/
main(int argc, char * argv[])
{
    struct record * start = NULL;
    int optionInput;
    char name[25], address[80], reset[80];
    int accountno, yob;

    isDebug(argc, &argv[1]);

    readfile(&start, "file.txt");

    do
    {    
        printMenu();
        optionInput = getOptionInput();

        printf("\n");

        switch(optionInput)
        {
            case 1: getInfo(&accountno, name, address, &yob);

                    if(addRecord(&start, accountno, name, address, yob) == 0)
                    {
                        printf("Add successful.\n");
                    }
                    else
                    {
                        printf("Error: Add unsucessful.\n");
                    }

                    *address = *reset;

                    break;

            case 2: accountno = getAccountNo();
                    getfield(address, 80);

                    if(modifyRecord(start, accountno, address) == 0)
                    {
                        printf("Modify successful.\n");
                    } 
                    else
                    {
                        printf("Error: Account number not found.\n");
                    }
                    *address = *reset;

                    break;

            case 3: if(printRecord(start, getAccountNo()) == -1)
                    {
                        printf("Error: Account number not found.\n");
                    } 

                    break;

            case 4: printAllRecords(start); 
                    printf("All records printed.\n");
                    break;

            case 5: if(deleteRecord(&start, getAccountNo()) == 0)
                    {
                        printf("Delete successful.\n");
                    }
                    else
                    {
                        printf("Error: Account number not found.\n");
                    }
 
                    break;

            case 6: printf("Exited Program.\n"); 
                    break;

            default: printf("Error. Command not read.\n"); break;

        }

    } while(optionInput != 6);

    writefile(start, "file.txt");
}

/*****************************************************************
//
// Function name: isDebug
//
// DESCRIPTION: A function that activates debug mode.
//
// Parameters:	count (int) : contains the number of arguments that 
//		were processed
//
//****************************************************************/ 
void isDebug(int count, char* arg[])
{
    if(count == 2)
    {
        if(strcmp(*arg, "debug") == 0)
        { 
            debugmode = 1;
            printf("Debug Mode On\n");
        }
        else
        {
            debugmode = 0;
            printf("%s: Command not found.\n", *arg);
            exit(0);
        }
    }
    else if(count > 2)
    {
        debugmode = 0;
        printf("Error: There are too much paramaters.\n");
        printf("Usage: ./bank\n");
        printf("       ./bank debug\n");
        exit(0);
    }
    else
    {
        debugmode = 0;
        printf("Debug Mode: Off\n");
    }
} 

/*****************************************************************
//
// Function name: printMenu
//
// DESCRIPTION:	A userinterface function 
// 		This function prints the menu options..
//
//****************************************************************/
void printMenu()
{
    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction called: printMenu\n");
        printf("No parameters passed.\n");
        printf("\n");
    }

    printf("\n******************************************************************\n");
    printf("\nPlease enter a number 1 - 6 to select your option.\n");
    printf("\n");
    printf("[1] Add a new record in the database.\n");
    printf("[2] Modify a record in the database.\n");
    printf("[3] Print information about a record.\n");
    printf("[4] Print all information in the database.\n");
    printf("[5] Delete an existing record from the database.\n");
    printf("[6] Quit the program.\n");
    printf("\n");
    printf("\n******************************************************************\n");

}

/*****************************************************************
//
// Function name: getOptionInput
//   
// DESCRIPTION: A function that gets the menu option input from the user.
//
// Return values: input : the input of the user as an int.
//
//****************************************************************/
int getOptionInput()
{
    int input;
    char trash[10];

    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction called: getOptionInput\n");
        printf("No parameters passed.\n");
        printf("\n");
    }

    do
    {
        printf("Command:");
        scanf("%d", &input);
        fgets(trash, 10, stdin);

        if (input < 1 || input > 6)
        {
            printf("Error: Please input an number  1 - 6 for an option.\n");
        }
        
    } while (input < 1 || input > 6);


    return input;

}

/*****************************************************************
//
// Function name: getInfo
//
// DESCRIPTION: A user interface function.
//		This function collects the data of a user.
//
// Parameters:	uaccountno (int*) : an int pointer for the users account no.
//	   	uname (char[]) : a char pointer for the users name.
//		uaddr (char[]) : a char pointer for the users address.
//		uyob (int *) : an int pointer for the users year of birth.
//
//****************************************************************/
void getInfo(int * uaccountno, char uname[], char uaddr[], int * uyob)
{
    char trash[80];
    int yearofbirth;
  
    if(debugmode)
    {
        printf("Debug Mode On\n");
 
        printf("\nFunction called: getInfo\n");
        printf("Paramaters passed:\n");

        printf("uaccountno: %d\n", &uaccountno);
        printf("uname: %s\n", uname);
        printf("uaddr: %s\n", uaddr);
        printf("uyob: %d\n", uyob);
        printf("\n");
    }

    *uaccountno = getAccountNo();

    printf("\nType your full name and then press enter.\n");
    fgets(uname, 25, stdin);
    strtok(uname, "\n");
 
    getfield(uaddr, 80);

    printf("\nType your year of birth and then press enter.\n");
    scanf("%d", &yearofbirth);
    fgets(trash, 10, stdin);
    *uyob = yearofbirth;    
}

/*****************************************************************
//
// Function name: getAccountNo
//
// DESCRIPTION: A userinterface function 
// 		This function obtains the account number of the user.
//
// Return values: getNo : the account number of the user.
//
//****************************************************************/
int getAccountNo()
{
    int getNo = -1, i;
    char trash[10];

    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction called: getAccountNo\n");
        printf("No parameters passed\n");
        printf("\n");
    }

    for(i = 0; getNo < 0; i++)
    {
        if(i > 1)
        {
            printf("\nType the NUMBER of your account.");
        } 
        else
        {
            printf("\nPlease type your account number.");
        }

        printf("Then press enter.\n");

        scanf("%d", &getNo);
        fgets(trash, 10, stdin);
    }

    return getNo;
}

/*****************************************************************
//
// Function name: getfield
//
// DESCRIPTION: A userinterface function 
// 		This function obtains the users address with as many
//		lines they want to put in.
//
// Parameters: addressInput (char []): the address being inputed.
//		size (int) : the size of char array being inputed.
//
//****************************************************************/
void getfield(char addressInput[], int size)
{
    char address[80], line[80];
    int i;
    
    if(debugmode)
    {
        printf("Debug Mode On\n");

        printf("\nFunction called: getfield\n");
        printf("Paramaters passed:\n");
 
        printf("addressInput: %s\n", addressInput);
        printf("size: %d\n", size);
        printf("\n");
    }

    printf("\nEnter your address. Press enter on a blank line to exit.\n");

    while(*line != '\n')
    {
        fgets(line, 80, stdin);
        strcat(addressInput, line);
    }

    /*This will take away all of the new lines*/
    for(i = 0; i < 80; i++)
    {
        if(addressInput[i] == '\n')
        {
            addressInput[i] = ' ';
        }
    }

}
