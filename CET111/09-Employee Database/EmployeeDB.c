/******************************************************************************
Filename: EmployeeDB.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 10 June 2019
Brief Description: Program for Employee DB Implementation using Linked Lists
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define OK 0x00
#define ERROR_EXCESS_PARAMS 0x01
#define ERROR_MISSING_PARAMS 0x02
#define ERROR_INVALID_OPERATION 0x03
#define ERROR_INVALID_PARAMS 0x04
#define ERROR_MEMORY_ALLOCATION 0x05
#define ERROR_EMPTY_LIST 0x06
#define QUIT 0x99

/*****************************************************************************/
/*****************************************************************************/
/* Employee Struct with Value and Pointer */
struct Employee
{
  int uniqueID;
  char* name;
  int salary;
  int phoneNumber;
  struct Employee* next;
};

/* Generate Running Number Employee ID */
int GetEmployeeID();

/* Adds a node to the front of the list */
int AddToFront(struct Employee** ppList, const char* name, const char* salary, const char* phoneNumber);

/* Returns number of nodes in the list */
int Count(struct Employee* list);

/* Frees (deletes) all nodes in the list */
int FreeList(struct Employee** pList);

/* Prints values of all nodes in list */
int PrintList(struct Employee* list);

/* Search values of all nodes in list */
int Search(struct Employee* list, const char* mode, const char* searchValue);

/* Remove node by Id */
int Remove(struct Employee** list, const char* searchValue);

/*****************************************************************************/
/*****************************************************************************/
/* Print the User Options during Program Start and Help */
int PrintHeader();

/* Process User Input and break it down into Tokens */
int Tokenize(struct Employee** employeeList);

/* Tokens will be Processed and Directed to Designated Functions */
int Process(const char* inputCommand, struct Employee** employeeList);

/*****************************************************************************/
/*****************************************************************************/
int main()
{
    /* Place the Employee Linked List here to make it persist 
       through all the function calls */
    struct Employee* nodeHead = NULL;

    /* Welcome Message */
    printf("Welcome to the Employee Database\n");
    PrintHeader();
    
    /* Start the Employee Database and keep running until user quits */
    while(1)
    {
        /* Prompt for User Input */
        printf("$Input:> ");

        /* Tokenize the Input, Process the Command
           and Pass the Head of the Linked List */
        /* Code to get User Input moved into Function
           as workaround for the stdin flush issue */
        if(Tokenize(&nodeHead)==QUIT)
            return OK;
    }
}

/*****************************************************************************/
/*****************************************************************************/
int GetEmployeeID()
{
    static int employeeID = 0;
    return ++employeeID;
}

int AddToFront(struct Employee** ppList, const char* name, const char* salary, const char* phoneNumber)
{
    struct Employee* newNode = NULL;
    char* newName = NULL;
    int newSalary = 0;
    int newPhoneNumber = 0;
    
    /* Check if name is NULL */
    if(name==NULL)
    {
        printf("Error - Name passed is NULL!\n\n");
        return ERROR_INVALID_PARAMS;
    }

    /* Create a New Node */
    newNode =  malloc(sizeof(struct Employee));
    if(newNode==NULL)
    {
        printf("Error - Unable to Allocate Memory!\n\n");
        return ERROR_MEMORY_ALLOCATION;
    }

    /* Create a New String */
    newName = malloc(sizeof(char)*(int)strlen(name));
    if(newName==NULL)
    {
        free(newNode); /* Free the Node Allocated Node */
        printf("Error - Unable to Allocate Memory!\n\n");
        return ERROR_MEMORY_ALLOCATION;
    }

    /* Convert the Salary and Phone Number */
    if(salary==NULL)
    {
        printf("Error - Salary cannot be NULL or Empty!\n\n");
        return ERROR_INVALID_PARAMS;
    } 
    
    newSalary = (int)atoi(salary);
    if(newSalary<=0)
    {
        printf("Error - Invalid Salary!\n\n");
        return ERROR_INVALID_PARAMS;
    }
    
    /* Phone Number is Optional */
    if(phoneNumber!=NULL)
    {
        newPhoneNumber = (int)atoi(phoneNumber);
        if(newPhoneNumber<=0)
        {
            printf("Error - Invalid Phone Number!\n\n");
            return ERROR_INVALID_PARAMS;
        }
    }

    newNode->uniqueID = GetEmployeeID();
    strcpy(newName, name);
    newNode->name = newName;
    newNode->salary = newSalary;
    newNode->phoneNumber = newPhoneNumber;
    newNode->next = *ppList;
    
    /* Update the Head and point it to the New Node */
    *ppList = newNode;
    
    printf("Success - New Employee added!\n\n");
    return OK;
}

int Count(struct Employee* list)
{
    int counter = 0;
    struct Employee* nodePointer = list;

    /* Go through the Linked List until NULL is reached 
       each loop will be counted as 1 Node */
    while(nodePointer!=NULL)
    {
        nodePointer = nodePointer->next;
        counter++;
    }

    return counter;
}

int FreeList(struct Employee** pList)
{
    int count = 0;
    struct Employee* nodePointer = *pList;

    /* Always check if the List is Empty 
       If Empty, inform the User, else Proceed to clear the Linked List */
    if(*pList==NULL)
    {
        printf("Employee DB Empty - %d record(s) cleared!\n", count);
        return QUIT;
    }
    
    while(nodePointer!=NULL)
    {
        struct Employee* newNodePointer = nodePointer->next;
        free(nodePointer->name);
        free(nodePointer);
        nodePointer = newNodePointer;
        ++count;
    }

    /* Dereference the Head */
    *pList = NULL;

    printf("SUCCESS - %d record(s) cleared!\n", count);
    return QUIT;
}

int PrintList(struct Employee* list)
{
    int counter = 0;
    struct Employee* nodePointer = list;

    /* Always check if the List is Empty 
       If Empty, inform the User, else Proceed to traverse the Employee Database */
    if(list==NULL)
    {
        printf("Error - Nothing to Print! Database is empty!\n\n");
        return ERROR_MISSING_PARAMS;
    }

    printf("Searching Employee DB...\n");

    /* Go through the Linked List and Print each value */
    while(nodePointer!=NULL)
    {
        printf("\tEntry[%d]: ", counter);
        printf("%d : %s : ", nodePointer->uniqueID, nodePointer->name);
        printf("%d : ", nodePointer->salary);

        if(nodePointer->phoneNumber!=0)
            printf("%d", nodePointer->phoneNumber);
        else
            printf("NULL");

        printf("\n");
        nodePointer = nodePointer->next;
        ++counter;
    }

    printf("%d record(s) found in the Employee DB\n\n", counter);
    return OK;
}

int Search(struct Employee* list, const char* mode, const char* searchValue)
{
    int counter = 0;
    struct Employee* nodePointer = list;

    /* Always check if the List is Empty 
       If Empty, inform the User, else Proceed to clear the Linked List */
    if(list==NULL)
    {
        printf("Error - Nothing to Search! Employee DB is empty!\n\n");
        return ERROR_MISSING_PARAMS;
    }

    /* Always check if the Mode is Empty */
    if(mode==NULL)
    {
        printf("Error - Mode is empty!\n\n");
        return ERROR_MISSING_PARAMS;
    }

    /* Always check if the Value is Empty */
    if(searchValue==NULL)
    {
        printf("Error - Search Value is empty!\n\n");
        return ERROR_MISSING_PARAMS;
    }

    printf("Searching Employee DB...\n");

    /* Go through the Linked List and Print each value */
    while(nodePointer!=NULL)
    {
        int isFound = 0;

        if(!strcmp(mode, "-id"))
        {
            int id = (int)atoi(searchValue);
            if(id<=0)
            {
                printf("Error - Invalid ID!\n\n");
                return ERROR_INVALID_PARAMS;
            }

            isFound = nodePointer->uniqueID==id ? 1 : 0;
        }
        else if(!strcmp(mode, "-name"))
            isFound = !strcmp(nodePointer->name, searchValue) ? 1 : 0;
        else if(!strcmp(mode, "-salary"))
        {
            int salary = (int)atoi(searchValue);
            if(salary<=0)
            {
                printf("Error - Invalid Salary!\n\n");
                return ERROR_INVALID_PARAMS;
            }

            isFound = nodePointer->salary==salary ? 1 : 0;
        }
        else if(!strcmp(mode, "-phonenum"))
        {
            int phoneNumber = (int)atoi(searchValue);
            if(phoneNumber<=0)
            {
                printf("Error - Invalid Phone Number!\n\n");
                return ERROR_INVALID_PARAMS;
            }

            isFound = nodePointer->phoneNumber==phoneNumber ? 1 : 0;
        }
        else
        {
            printf("Error - Invalid Search Mode!\n\n");
            return ERROR_INVALID_PARAMS;
        }

        if(isFound)
        {
            printf("\tEntry[%d]: ", counter);
            printf("%d : %s : ", nodePointer->uniqueID, nodePointer->name);
            printf("%d : ", nodePointer->salary);

            if(nodePointer->phoneNumber!=0)
                printf("%d", nodePointer->phoneNumber);
            else
                printf("NULL");

            printf("\n");
            ++counter;
        }

        /* If current node is not matching, move to the next */
        nodePointer = nodePointer->next;
        isFound = 0;
    }

    printf("%d matching record(s) found!\n\n", counter);
    return OK;
}

/* Remove node by Id */
int Remove(struct Employee** ppList, const char* searchValue)
{

    struct Employee* prevNode = NULL;
    struct Employee* currNode = *ppList;
    int employeeID = 0;

    /* Always check if the List is Empty 
       If Empty, inform the User, else Proceed to clear the Linked List */
    if(ppList==NULL)
    {
        printf("Error - Nothing to Search! Linked List is empty!\n\n");
        return ERROR_MISSING_PARAMS;
    }

    /* Always check if the Id is Invalid */
    employeeID = atoi(searchValue);
    if(employeeID<1)
    {
        printf("Error - Invalid ID!\n\n");
        return ERROR_INVALID_PARAMS;
    }

    printf("Searching Employee DB...\n");

    /* Go through the Linked List and Delete Matching Id */
    while(currNode!=NULL)
    {
        if(currNode->uniqueID==employeeID)
        {
            if(prevNode==NULL) /* 1st Case - Node to be Removed is at the Head */
            {
                prevNode = currNode;
                currNode = currNode->next;

                free(prevNode->name);
                free(prevNode);
                *ppList = currNode;
            }
            else /* 2nd Case - Node is between or at the End of the List */
            {
                currNode = currNode->next;

                free(prevNode->next->name);
                free(prevNode->next);

                prevNode->next = currNode;
            }

            printf("Employee ID(%d) record deleted!\n\n", employeeID);
            return OK;
        }

        /* If current node is not matching, move to the next */
        prevNode = currNode;
        currNode = currNode->next;
    }

    printf("Employee ID(%d) record not found!\n\n", employeeID);
    return OK;
}
/*****************************************************************************/
/*****************************************************************************/
int PrintHeader()
{
    printf("Choose from the following, enter your inputs and press ENTER to process:\n\n");
    printf("\tAdd Employee:\t\tadd <Name> <Salary> <PhoneNumber-Optional>\n");
    printf("\tPrint Employee List:\tprintall (by Latest Order)\n");
    printf("\tSearch for Employee:\tsearch <Mode: -id, -name, -salary, -phonenum> <Search Value>\n");
    printf("\tRemove Employee:\tremove <ID>\n");
    printf("\tHelp:\t\t\thelp\n");
    printf("\tQuit:\t\t\tquit\n\n");

    return OK;
}

int Tokenize(struct Employee** employeeList)
{
    /* User Input Variables */
    char keyboardInput;
    char* inputString = NULL;
    int inputStringLength=0;

    /* Terminate loop once 'ENTER' key is pressed */
    while((keyboardInput = getchar())!='\n')
    {
        /* Create buffer to make space for new character input
            plus string terminator - \0 */
        char* buffer = NULL;
        buffer = malloc(sizeof(char)*(inputStringLength+2));
        
        /* Only copy inputString if it is not empty
            otherwise you get segmentation errors */
        if(inputStringLength!=0)
            strcpy(buffer, inputString);
        
        buffer[inputStringLength] = keyboardInput;
        buffer[inputStringLength+1] = '\0';

        /* Free the input string to prepare for new malloc and copy */
        free(inputString);

        /* Update the string length after the concat */
        inputStringLength = strlen(buffer);

        /* Clear the input string and copy the buffer back */
        inputString = malloc(sizeof(char)*(inputStringLength+1));
        strcpy(inputString, buffer);
        inputString[inputStringLength] = '\0';

        /* Free the buffer */
        free(buffer);
    }

    /* Flushing the STDIN does not work 
       Exit this Function to Clear the Stack and stdin */
    return Process(inputString, employeeList);
}

int Process(const char* inputCommand, struct Employee** employeeList)
{
    /* Token Variables */
    int argc = 0;                   /* Number of Parameters in the Input Command */
	char* inputCommandCopy = NULL;  /* Copy of the Input Command */
	char* delim = " ";              /* Separator for the Parameters */
    char *token = NULL;             /* Pointer to the Current Token */
    int tokenLength = 0;

    /* Input Tokens */
    char* tkCommand = NULL; /* add, printall, search, remove, quit */
    char* tkparam02 = NULL; /* name, mode, id */
    char* tkparam03 = NULL; /* salary, search value */
    char* tkparam04 = NULL; /* phone number (optional) */

    /* Create a copy of the Input Command as strtok will directly modifiy the input */
    inputCommandCopy = malloc(sizeof(char)*(int)strlen(inputCommand));
    strcpy(inputCommandCopy, inputCommand);

    /* Perform Tokenisation and Store the Tokens */
    token = strtok(inputCommandCopy, delim);
	while (token != NULL)
	{
        ++argc; /* Start Argument Count from 1 */
        if(argc<5)
        {
            tokenLength = strlen(token);
            switch(argc)
            {
                case 1:
                    tkCommand = malloc(sizeof(char)*(tokenLength+1));
                    strcpy(tkCommand, token);
                    tkCommand[tokenLength] = '\0';
                    break;
                case 2:
                    tkparam02 = malloc(sizeof(char)*(tokenLength+1));
                    strcpy(tkparam02, token);
                    tkparam02[tokenLength] = '\0';
                    break;
                case 3:
                    tkparam03 = malloc(sizeof(char)*(tokenLength+1));
                    strcpy(tkparam03, token);
                    tkparam03[tokenLength] = '\0';
                    break;
                case 4:
                    tkparam04 = malloc(sizeof(char)*(tokenLength+1));
                    strcpy(tkparam04, token);
                    tkparam04[tokenLength] = '\0';
                    break;
            }
        }
        else
        {
            printf("Invalid Command - Excess Parameters!\n\n");
            return ERROR_EXCESS_PARAMS;
        }
        token = strtok(NULL, delim); /* Get the Next Token */
	}

    /* Process the Tokens and Perform the Next Step */
    if(!strcmp(tkCommand,"add"))
    {
        /* Error Check - add can either have : printall */
        if(argc>4)
        {
            printf("Excess Parameters - Maximum of 3 Parameters(Name, Salary and Phone Number)!\n\n");
            return ERROR_EXCESS_PARAMS;
        }

        if(argc<3)
        {
            printf("Missing Parameters - Name and Salary are required!\n\n");
            return ERROR_MISSING_PARAMS;
        }

        return AddToFront(employeeList, tkparam02, tkparam03, tkparam04);
    }
    else if(!strcmp(tkCommand,"printall"))
    {
        /* Error Check - printall has only 1 argument: printall */
        if(argc>1)
        {
            printf("Excess Parameters - Printing the Database does not require any parameters!\n\n");
            return ERROR_EXCESS_PARAMS;
        }
        
        return PrintList(*employeeList);
    }
    else if(!strcmp(tkCommand,"search"))
    {
        /* Error Check - search has 3 arguments: search, mode and searchValue */
        if(argc>3)
        {
            printf("Excess Parameters - Search requires only the Mode and Search Value!\n\n");
            return ERROR_EXCESS_PARAMS;
        }

        if(argc<3)
        {
            printf("Missing Parameters - Search requires Mode and Search Value to be provided!\n\n");
            return ERROR_MISSING_PARAMS;
        }

        return Search(*employeeList, tkparam02, tkparam03);
    }
    else if(!strcmp(tkCommand,"remove"))
    {
        /* Error Check - remove has 2 arguments: remove and employeeID */
        if(argc>2)
        {
            printf("Excess Parameters - Remove Employee requires only the ID!\n\n");
            return ERROR_EXCESS_PARAMS;
        }

        if(argc<2)
        {
            printf("Missing Parameters - Remove Employee requires ID!\n\n");
            return ERROR_MISSING_PARAMS;
        }

        return Remove(employeeList, tkparam02);
    }
    else if(!strcmp(tkCommand,"help"))
    {
        /* Error Check - help has only 1 argument: help */
        if(argc>1)
        {
            printf("Excess Parameters - help does not require any parameters!\n\n");
            return ERROR_EXCESS_PARAMS;
        }
        
        return PrintHeader(); /* Print the Header again for user to see the options */
    }
    else if(!strcmp(tkCommand,"quit"))
    {
        /* Error Check - quit has only 1 argument: quit */
        if(argc>1)
        {
            printf("Excess Parameters - Quitting the Database does not require any parameters!\n\n");
            return ERROR_EXCESS_PARAMS;
        }

        printf("Program Terminating... All records in the database will be discarded!\n");
        printf("Freeing up memory... ");
        
        return FreeList(employeeList); /* Clear the Database and Deallocate Everthing from the Heap */
    }
    else
    {
        printf("Invalid Command - Unrecognised Operation!\n\n");
        return ERROR_INVALID_OPERATION;
    }
}