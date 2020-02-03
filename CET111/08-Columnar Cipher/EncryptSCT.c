/******************************************************************************
Filename: EncryptSCT.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 11 June 2019
Brief Description: Implement Simple Columnar Cipher on a File (Encrypt or Decrpt)
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OK 0x00
#define ERROR_MISSING_PARAM 0x01
#define ERROR_EXCESS_PARAMS 0x02
#define ERROR_INVALID_OPERATION 0X03
#define ERROR_INPUT_FILE_NOT_EXIST_OR_EMPTY 0x04
#define ERROR_FILE_SIZE 0x05
#define ERROR_FILE_SEEK 0x06
#define ERROR_CREATE_OUTPUT_FILE 0x07
#define ERROR_FILE_CLOSE 0x08
#define ERROR_WRITE_OUTPUT_FILE 0x09
#define ERROR_MEMORY_ALLOCATE 0x0A
#define ERROR_FILE_NOT_SQUARE 0x0B

int EncryptDecrypt(char* inputFile, char* outputFile, char* operation);

int main (int argc, char* argv[]) 
{
    int RESULT;

    /*************************************/
    /* START OF PRELIMINARY ERROR CHECKS */
    /*************************************/
    if(1==argc)
    {
        printf("Invalid usage: Missing Parameters!");
        return ERROR_MISSING_PARAM;
    }

    if(5<=argc)
    {
        printf("Invalid usage: Too many parameters!");
        return ERROR_EXCESS_PARAMS;
    }
    /***********************************/
    /* END OF PRELIMINARY ERROR CHECKS */
    /***********************************/

    /********************************/
    /* START OF PARSING AND COMPUTE */
    /********************************/
    if(argc==4)
    {
        if(!strcmp(argv[1], "-e"))
            RESULT = EncryptDecrypt(argv[2], argv[3], argv[1]);
        else if(!strcmp(argv[1], "-d"))
            RESULT = EncryptDecrypt(argv[2], argv[3], argv[1]);
        else
        {
            printf("Invalid usage: %s.exe - Invalid Operation (only -e or -d is allowed)!", argv[0]);
            return ERROR_INVALID_OPERATION;
        }
    }
    else
    {
        printf("Invalid usage: Missing Parameters!");
        return ERROR_MISSING_PARAM;
    }

    return RESULT;
}

int EncryptDecrypt(char* inputFile, char* outputFile, char* operation)
{
    /* Variable Declarations - Have to do it here, otherwise C will get compile warnings! */
    FILE* filePointer; int fileSize = 0;            /* File Operations */
    int size = 0, dimension = 0;                    /* Used for Getting the Nearest Square Dimension */
    char* inputString = NULL; char* buffer = NULL;  /* Container for Input and Output File Contents */
    char ch; int counter = 0;                       /* Used for reading the Input File */
    int row=0, column=0, matrixCounter=0;           /* Used for Transposing the File (Columnar) */

    /* Error Checks for Input File */
    filePointer = fopen(inputFile, "r");
    if(filePointer==NULL)
    {
        printf("Error - Unable to Open Input File!\n");
        return ERROR_INPUT_FILE_NOT_EXIST_OR_EMPTY;
    }

    /* Count the Number of Characters by Seeking the End of the File 
       and check for Errors while */
    if(fseek(filePointer, 0, SEEK_END))
    {
        printf("Error - Unable to get File Size!\n");
        return ERROR_FILE_SIZE;
    }

    /* Check if Input File is Empty, if Empty do not proceed */
    fileSize = ftell(filePointer);
    if(fileSize==0)
    {
        printf("Error - File is Empty!\n");
        return ERROR_INPUT_FILE_NOT_EXIST_OR_EMPTY;
    }

    /* Check if unable to traverse Input File */
    if(fseek(filePointer, 0, SEEK_SET))
    {
        printf("Error - Unable to get set file pointer!\n");
        return ERROR_FILE_SEEK;
    }

    printf("%d characters in the file.\n", fileSize);
    
    /* Calculate the Dimension based on the Number of Characters in the File */
    while(dimension<fileSize)
        dimension = pow(++size, 2);

    /* For Decrypt Only - If Input File size is not a perfect square, cannot proceed */
    if(!strcmp(operation, "-d"))
    {
        if(dimension!=fileSize)
        {
            printf("Error - Input File cannot be decrypted!\n");
            return ERROR_FILE_NOT_SQUARE;
        }
    }

    printf("%dx%d will be the dimension size\n", size, size);

    /* Allocate Memory for Input and Output Contents 
       Do not proceed if this allocation fails */
    inputString = malloc((int)sizeof(char)*(fileSize+1));
    if(inputString==NULL)
    {
        printf("Error - Unable to allocate memory!\n");
        return ERROR_MEMORY_ALLOCATE;
    }
    
    buffer = malloc((int)sizeof(char)*(size*size+1));
    if(buffer==NULL)
    {
        free(inputString);
        printf("Error - Unable to allocate memory!\n");
        return ERROR_MEMORY_ALLOCATE;
    }
    
    /* Set the Contents of Both Input and Buffer to 0 */
    memset(inputString, 0, fileSize+1);
    memset(buffer, 0, size*size+1);

    /* Read the Input File and Store the Contents in the Memory */
    while((ch=getc(filePointer))!=EOF)
        inputString[counter++]=ch;

    /* Check if Input File was closed properly */
    if(fclose(filePointer))
    {
        /* Clear the Allocated Memory */
        free(inputString);
        free(buffer);

        printf("Error - Unable to close Input File!\n");
        return ERROR_FILE_CLOSE;
    }

    /* Transpose the String */
    for(column=0; column<size; column++)
    {
        int offset = column;
        for(row=0; row<size; row++)
        {
            /* Transpose the Contents but after exceeding the file contents
               just repeat the last character */
            buffer[matrixCounter++] = inputString[offset<fileSize ? offset : (fileSize-1)];
            offset+=size;
        }
    }

    /* Truncate the Excess Characters - For Decrypt Only */
    if(!strcmp(operation, "-d"))
    {
        for(counter=strlen(buffer)-1; counter>=0; counter--)
        {
            /* Compare the characters starting from the end if they are the same
               If same, set to 0, if not, break the loop - this may result in loss of info */
            if(buffer[counter]==buffer[counter-1])
                buffer[counter] = 0;
            else
                break;
        }
    }

    /* Error Checks for Output File */
    filePointer = fopen(outputFile, "w");
    if(filePointer==NULL)
    {
        /* Clear the Allocated Memory */
        free(inputString);
        free(buffer);

        printf("Error - Unable to Open Output File!\n");
        return ERROR_CREATE_OUTPUT_FILE;
    }

    /* Write the Contents into the Output File */
    for(counter=0; counter<(int)strlen(buffer); counter++)
    {
        if(fputc(buffer[counter], filePointer)==EOF)
        {
            printf("Error - Unable to Write to Output File!\n");

            /* Clear the Allocated Memory */
            free(inputString);
            free(buffer);

            /* Attempt to Close the File Stream */
            if(fclose(filePointer))
                printf("Error - Unable to close Output File!\n");

            return ERROR_WRITE_OUTPUT_FILE;
        }
    }
    
    /* Check if Output File was closed properly */
    if(fclose(filePointer))
    {
        /* Clear the Allocated Memory */
        free(inputString);
        free(buffer);

        printf("Error - Unable to close Output File!\n");
        return ERROR_FILE_CLOSE;
    }

    /* Clear the Allocated Memory */
    free(inputString);
    free(buffer);

    if(!strcmp(operation, "-d"))
        printf("Successfully Decrypted %s to %s!\n", inputFile, outputFile);
    else    
        printf("Successfully Encrypted %s to %s!\n", inputFile, outputFile);

    /* Success - Hooray! */
    return OK;
}