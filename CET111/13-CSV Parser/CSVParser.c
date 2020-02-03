/******************************************************************************
Filename: CSVParser.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 27 June 2019
Brief Description: Implement CSV Parsing Functionality
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "CSVParser.h"

/* Tokenise the Input String and Populate the CSVData* */
int Tokenise(struct CSVData*, const char*, const long);

/* Reads the CSV contents of a file, writes to result and return OK/FAIL */
int ReadCSVFile(struct CSVData* result, const char* filePath)
{
    /* Variable Declarations - Have to do it here, otherwise C will get compile warnings! */
    FILE* filePointer; long fileSize = 0;   /* File Operations */
    char* inputString = NULL;               /* Container for Input and Output File Contents */
    char ch; long counter = 0;              /* Used for reading the Input File */
    int errCode;                            /* Store Error Code */

    /* Check if Result is NULL */
    if(result==NULL)
    {
        printf("Error - Cannot pass a NULL CSVData!\n");
        return FAIL;
    }

    /* Check if Result is Dirty */
    if(result!=NULL)
    {
        /* Check if User is attempting to pass some errorneous CSV Data */
        if (result->rowData!=NULL)
        {
            if (result->rowData[0].colData!=NULL)
            {
                printf("Error - Invalid CSV Data Structure!\n");
                printf("Use an Initialised and Clean CSV Data!\n");
                return FAIL;
            }
        }
    }

    /* Check if filePath is empty */
    if(filePath==NULL)
    {
        printf("Error - Invalid File Path!\n");
        return FAIL;
    }

    /* Error Checks for Input File */
    filePointer = fopen(filePath, "r");
    if(filePointer==NULL)
    {
        printf("Error - Unable to Open Input File!\n");
        return FAIL;
    }

    /* Count the Number of Characters by Seeking the End of the File 
       and check for Errors while */
    if(fseek(filePointer, 0, SEEK_END))
    {
        printf("Error - Unable to get File Size!\n");
        return FAIL;
    }

    /* Check if Input File is Empty, if Empty do not proceed */
    fileSize = ftell(filePointer);
    if(fileSize==0)
    {
        printf("Error - File is Empty!\n");
        return FAIL;
    }

    /* Check if unable to traverse Input File */
    if(fseek(filePointer, 0, SEEK_SET))
    {
        printf("Error - Unable to get set file pointer!\n");
        return FAIL;
    }

    printf("%ld characters in the file.\n", fileSize);

    /* Allocate Memory for Input and Output Contents 
       Do not proceed if this allocation fails */
    inputString = calloc(fileSize+1,sizeof(char));
    if(inputString==NULL)
    {
        printf("Error - Unable to allocate memory!\n");
        return FAIL;
    }

    /* Read the Input File and Store the Contents in the Memory */
    while((ch=getc(filePointer))!=EOF)
        inputString[counter++]=ch;

    /* Check if Input File was closed properly */
    if(fclose(filePointer))
    {
        /* Clear the Allocated Memory */
        free(inputString);

        printf("Error - Unable to close Input File!\n");
        return FAIL;
    }
    
    /* Process the Input String and Store the Error Code */
    errCode = Tokenise(result, inputString, fileSize);

    free(inputString);  /* Clear the Allocated Memory */
    return errCode;     /* Return Error Code */
}

/* Tokenise the Input String and Populate the CSVData* */
int Tokenise(struct CSVData* result, const char* inputString, const long fileSize)
{
    long counter=0, rowCounter=0, colCounter=0, wordLength=0;

    /* Loop through the Input until end is reached */
    while(counter<fileSize)
    {
        /* Initialise CSVRow Array 
           This will only happen once */
        if(rowCounter==0 && colCounter==0)
        {
            result->size = ++rowCounter;
            result->rowData = calloc(1, sizeof(struct CSVRow));

            /* Check if Allocation Failed */
            if(result->rowData==NULL)
            {
                printf("Error - Unable to allocate memory for CSV Data!\n");
                FreeCSVData(result);
                return FAIL;
            }
        }

        /* Initialise Column Array 
           Perform for every new row*/
        if(colCounter==0)
        {
            result->rowData[rowCounter-1].size = ++colCounter;
            result->rowData[rowCounter-1].colData = calloc(1,sizeof(char*));

            /* Check if Allocation Failed */
            if(result->rowData[rowCounter-1].colData==NULL)
            {
                printf("Error - Unable to allocate memory for CSV Row!\n");
                FreeCSVData(result);
                return FAIL;
            }
        }

        /* Row is Empty and just contains CRLF */
        if(inputString[counter]=='\r' && inputString[counter+1]=='\n')
        {
            result->rowData[rowCounter-1].size = colCounter;

            /* Initialise Column with 0 length */
            /* Terminator is not Counted as Word Length */
            wordLength = 0; 
            result->rowData[rowCounter-1].colData[colCounter-1] = calloc(wordLength+1, sizeof(char));

            /* Check if Allocation Failed */
            if(result->rowData[rowCounter-1].colData[colCounter-1]==NULL)
            {
                printf("Error - Unable to allocate memory for CSV Cell!\n");
                FreeCSVData(result);
                return FAIL;
            }

            result->rowData[rowCounter-1].colData[colCounter-1][wordLength] = '\0'; /* Add the Initial Terminator */
        }

        /* 1 cell can be terminated by either ',' or CRLF */
        if(inputString[counter]!=','  && inputString[counter]!='\r' && inputString[counter]!='\n')
        {
            result->rowData[rowCounter-1].size = colCounter;

            /* Initialise Column with 0 length */
            /* Terminator is not Counted as Word Length */
            wordLength = 0; 
            result->rowData[rowCounter-1].colData[colCounter-1] = calloc(wordLength+1, sizeof(char));

            /* Check if Allocation Failed */
            if(result->rowData[rowCounter-1].colData[colCounter-1]==NULL)
            {
                printf("Error - Unable to allocate memory for CSV Cell!\n");
                FreeCSVData(result);
                return FAIL;
            }

            result->rowData[rowCounter-1].colData[colCounter-1][wordLength] = '\0'; /* Add the Initial Terminator */

            /* Loop until delimeter is found or CR or LF */
            while(inputString[counter]!=',' && inputString[counter]!='\r' && inputString[counter]!='\n' && counter<fileSize)
            {
                /* Realloc for each Character and Set Terminator */
                result->rowData[rowCounter-1].colData[colCounter-1] = realloc(result->rowData[rowCounter-1].colData[colCounter-1], sizeof(char)*(wordLength+1));
                
                /* Check if Re-Allocation Failed */
                if(result->rowData[rowCounter-1].colData[colCounter-1]==NULL)
                {
                    printf("Error - Unable to reallocate memory for CSV Cell!\n");
                    FreeCSVData(result);
                    return FAIL;
                }
                
                result->rowData[rowCounter-1].colData[colCounter-1][wordLength] = inputString[counter];
                
                ++wordLength;   /* Make space for next character */
                ++counter;      /* Move to the next character */
            }
            result->rowData[rowCounter-1].colData[colCounter-1][wordLength+1] = '\0';   /* Add the Terminator */
            ++colCounter; /* Increment Column Number */
        }

        if(inputString[counter]==',')
        {
            ++counter; /* Move to the next character */

            result->rowData[rowCounter-1].size = colCounter;
            result->rowData[rowCounter-1].colData = realloc(result->rowData[rowCounter-1].colData, sizeof(char*)*(colCounter));

            /* Check if Re-Allocation Failed */
            if(result->rowData[rowCounter-1].colData==NULL)
            {
                printf("Error - Unable to allocate memory for additional cell in CSV Row!\n");
                FreeCSVData(result);
                return FAIL;
            }

            /* Check if EOL, Create an Empty Column */
            if(inputString[counter]=='\r' && inputString[counter+1]=='\n')
            {
                wordLength = 0;
                result->rowData[rowCounter-1].colData[colCounter-1] = calloc(wordLength+1, sizeof(char));

                /* Check if Allocation Failed */
                if(result->rowData[rowCounter-1].colData[colCounter-1]==NULL)
                {
                    printf("Error - Unable to allocate memory for CSV Cell!\n");
                    FreeCSVData(result);
                    return FAIL;
                }

                result->rowData[rowCounter-1].colData[colCounter-1][wordLength] = '\0'; /* Add the Initial Terminator */
                result->rowData[rowCounter-1].size = colCounter;                        /* Count the Empty Column */
                
                counter += 2;   /* Jump Over \r\n */
                ++rowCounter;   /* Increment Row Number */
                colCounter = 0; /* Reset Column Number */

                /* Check if EOF before Extending or Creating New Row*/
                if(counter<fileSize)
                {
                    result->size = rowCounter;
                    result->rowData = realloc(result->rowData, sizeof(struct CSVRow)*(rowCounter));

                    /* Check if Re-Allocation Failed */
                    if(result->rowData==NULL)
                    {
                        printf("Error - Unable to reallocate memory for CSV Row!\n");
                        FreeCSVData(result);
                        return FAIL;
                    }
                } 
            }
            continue;
        }
        
        /* If New Line, Increment Row Counter and Reset Column Counter */
        if(inputString[counter]=='\r' && inputString[counter+1]=='\n')
        {
            counter += 2;   /* Jump Over \r\n */
            ++rowCounter;   /* Increment Row Number */
            colCounter = 0; /* Reset Column Number */         

            /* Check if EOF before Extending or Creating New Row*/
            if(counter<fileSize)
            {
                result->size = rowCounter;
                result->rowData = realloc(result->rowData, sizeof(struct CSVRow)*(rowCounter));

                /* Check if Re-Allocation Failed */
                if(result->rowData==NULL)
                {
                    printf("Error - Unable to reallocate memory for CSV Row!\n");
                    FreeCSVData(result);
                    return FAIL;
                }
            }
            continue;
        }
    }
    return OK;
}

/* Gets an entry in the CSV data given the row and column index */
char* GetEntry(struct CSVData* result, int rowIndex, int colIndex)
{
    /* Error Check - CSV Data is NULL */
    if(result==NULL)
    {
        printf("Error - CSV Data is NULL!\n");
        return (char*) "";
    }

    /* Error Check - Row Index is Out of Range */
    if(rowIndex<0)
    {
        printf("Error - Row Index out of Range!\n");
        return (char*) "";
    }

    /* Error Check - Row Index is Out of Range */
    if(rowIndex>(result->size-1))
    {
        printf("Error - Row Index out of Range!\n");
        return (char*) "";
    }

    /* Error Check - Column Index is Out of Range */
    if(colIndex<0)
    {
        printf("Error - Column Index out of Range!\n");
        return (char*) "";
    }

    /* Error Check - Column Index is Out of Range */
    if(colIndex>(result->rowData[rowIndex].size-1))
    {
        printf("Error - Column Index out of Range!\n");
        return (char*) "";
    }

    /* Error Check - Row may not be Initialised or NULL */
    if(result->rowData[rowIndex].colData == NULL)
    {
        printf("Error - Invalid Row location!\n");
        return (char*) "";
    }

    /* Error Check - CSV Data is Dirty or Unitialised */
    if(result->rowData->size == 0)
    {
        printf("Error - Unitialised CSV Data!\n");
        return (char*) "";
    }

    /* Error Check - String may not be Initialised or NULL */
    if(result->rowData[rowIndex].colData[colIndex] == NULL)
    {
        printf("Error - Invalid Cell location!\n");
        return (char*) "";
    }

    /* Check if String is just a Terminator (Empty Column) */
    return strlen(result->rowData[rowIndex].colData[colIndex]) == 0 ? "<empty>" : result->rowData[rowIndex].colData[colIndex];
}

/* Deallocates all entries of the given CSV Data */
/* It is possible for this function to generate an Undefined Behavior
   as the CSVData size and data may not be correct if abused */
void FreeCSVData(struct CSVData* target)
{   
    long rowCount, colCount;

    printf("Warning - Attempting to Free a CSVData with an Invalid Structure or Proper Initialisation can fail!\n");

    /* Check if Target is already NULL to begin with */
    if(target==NULL)
    {
        printf("Error - Target is already NULL!\n");
        errno = 1;
        return;
    }

    /* Check if Row Count is < 1 */
    if(target->size<1)
    {
        printf("Error - Target Row Size is less than 1!\n");
        errno = 1;
        return;
    }

    /* Check if Row Count is 0 but Row Data is not NULL */
    if(target->size==0 && target->rowData!=NULL)
    {
        printf("Error - Target Row Size is 0 but Row Data is not NULL!\n");
        errno = 1;
        return;
    }

    /* Check if Row Data is NULL */
    if(target->rowData==NULL)
    {
        printf("Error - Target Row Data is NULL!\n");
        errno = 1;
        return;
    }

    /* Check if Row Data is not NULL but ColData is NULL */
    if(target->rowData!=NULL && target->rowData->colData==NULL)
    {
        printf("Error - Target Row Data is NULL!\n");
        errno = 1;
        return;
    }

    /* Loop through all the Elements in Reverse */
    for(rowCount=target->size; rowCount>0; rowCount--)
    {
        /* Check if Col Count is less than 1 */
        if(target->rowData->size<1)
        {
            printf("Error - Target Column Size is less than 1!\n");
            errno = 1;
            return;
        }

        /* Check if First Col Data is NULL
           Same check as the ReadCSV, if this is not check, it can proceed to segerrors below */
        if(target->rowData[0].colData==NULL)
        {
            printf("Error - Target Column Data is NULL!\n");
            errno = 1;
            return;
        }
        
        /* Check if Col Count is 0 but Col Data is not NULL */
        if(target->rowData[rowCount-1].size==0 && target->rowData[rowCount-1].colData!=NULL)
        {
            printf("Error - Target Column Size is 0 but Column Data is not NULL!\n");
            errno = 1;
            return;
        }

        /* Check if Current Col Data is NULL */
        if(target->rowData[rowCount-1].colData==NULL)
        {
            printf("Error - Target Column Data is NULL!\n");
            errno = 1;
            return;
        }

        /* Free Column */
        for(colCount=target->rowData[rowCount-1].size; colCount>0; colCount--)
        {
            /* Check if the Cell Value is NULL */
            if(target->rowData[rowCount-1].colData[colCount-1]==NULL)
            {
                printf("Error - Target Cell Value is NULL!\n");
                errno = 1;
                return;
            }

            free(target->rowData[rowCount-1].colData[colCount-1]);
        }
        
        /* Free 2D Column Data and Set Col Counter to 0*/
        free(target->rowData[rowCount-1].colData);
        target->rowData[rowCount-1].size = 0;
    }
    
    /* Free Pointers to 2D Column Data and Set to NULL, Set the Row Counter to 0*/
    free(target->rowData); 
    target->rowData = NULL;
    target->size = 0;

    /* Leave the Target as Not NULL 
       as it's up to the user to perform their own deallocation
       since they are just passing target as a parameter */
    /* target = NULL; */

    /* Notify User */
    errno = 0;
    printf("Success - Target has been freed!\n");
}