/******************************************************************************
Filename: GCDLCD.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 17 June 2019
Brief Description: Program for calculating GCD and LCD
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define OK 0x00
#define ERROR_INVALID_INPUT 0x01
#define SUCCESS_GCD_FOUND 0x02
#define SUCCESS_LCD_FOUND 0x03
#define ERROR_GCD_NOT_FOUND 0x04
#define ERROR_LCD__NOT_FOUND 0x05
#define ERROR_MISSING_PARAMETERS 0x06
#define ERROR_MEMORY_ALLOCATION 0x07

int FindGCD(int* argv, int paramsCount, int base);
int FindLCD(int* argv, int paramsCount, int base);

int main(int argc, char* argv[])
{
    /* Variables for Parsing Input and Validation */
    int counter;
    int validInputs = 0, small = 0, large = 0;
    char* allowedCharacters = "9876543210";
    int* numbers = NULL;

    printf("Checking inputs...");
    /* Error Check if User provided any Parameters */
    if(argc==1)
    {
        printf("\nError - Missing Parameters\n");
        return ERROR_MISSING_PARAMETERS;
    }

    /* Parse all Input, Perform Checks and Convert to Integer Array */
    for(counter=1; counter<argc; counter++)
    {
        long number;

        /* Do some checking here for Invalid Characters */
        if((int)strlen(argv[counter])!=(int)strspn(argv[counter], allowedCharacters))
        {
            printf("\nError - Invalid input: '%s' detected!", argv[counter]);
            continue; /* Proceed to the Next Argv */
        }
        
        /* Do some checking here for Extremely Large Numbers */
        number = (long)atol(argv[counter]);
        if(number>((long)pow(2,31)-1))
        {
            printf("\nError - Invalid input: '%s' detected. Number too large!", argv[counter]);
            continue; /* Proceed to the Next Argv */
        }

        /* Do some checking here for Negative Numbers */ 
        if(number<1)
        {
            printf("\nError - Invalid input: '%s' detected. Number must be greater than 0!", argv[counter]);
            continue; /* Proceed to the Next Argv */
        }

        ++validInputs;

        /* In the Beginning, Large and Small will have the value of the First Element */
        if(validInputs==1)
        {
            small = (int)number;
            large = (int)number;
        }
        else 
        {
            /* Do number comparison 
               smallest number will be used as base for GCD 
               largest number will be used as base for LCD */
            if(small>(int)number)
                small = (int)number;
            
            if(large<(int)number)
                large = (int)number;
        }

        /* Do memory allocation for to expand the Integer Array */
        numbers = realloc(numbers, sizeof(int)*(validInputs));

        /* Check if Memory Allocation Failed */
        if(numbers==NULL)
        {
            printf("\nError - Memory Allocation failed!");
            return ERROR_MEMORY_ALLOCATION;
        }

        numbers[validInputs-1] = (int)number;
    }

    printf("%s\n", validInputs == (argc-1) ? " OK!" : "");
    printf("\nNumber of Valid Inputs: %d\n", validInputs);

    if(validInputs>1)
    {
        printf("Smallest number in the list is: %d\n", small);
        printf("Largest number in the list is: %d\n", large);

        /* GCD Calculation */
        FindGCD(numbers, validInputs, small);

        /* LCD Calculation */
        FindLCD(numbers, validInputs, large);
    }
    else
        printf("Error - Not enough Valid Inputs found!\n");

    /* Free Memory Allocation */
    free(numbers);

    return OK;
}

/* Start with 1, get modulo for each input until
   the smallest number in the list */
int FindGCD(int* argv, int paramsCount, int base)
{
    /* GCD Calculation */
    /* Start with 1, get modulo for each input until
       the smallest number */
    int gcd = 1;
    int gcd_counter = 1;
    for(gcd_counter=1; gcd_counter<=base; gcd_counter++)
    {
        int counter;
        for(counter=0; counter<paramsCount; counter++)
        {
            if(argv[counter]%gcd_counter!=0)
                break;
        }

        if(counter==paramsCount)
            gcd = gcd_counter;
    }

    /* Lowest possible GCD is always 1
       hence there is no need for Error Return */
    printf("GCD for the list is: %d\n", gcd);
    return SUCCESS_GCD_FOUND;
}

/* Start with the largest, get modulo for each input until
   the until 2^31-1 and break once LCD is found or display error
   if LCD not found */
int FindLCD(int* argv, int paramsCount, int base)
{
    int lcd;
    long lcd_counter;
    for(lcd_counter=base; lcd_counter<pow(2,31); lcd_counter++)
    {
        int counter;
        for(counter=0; counter<paramsCount; counter++)
        {
            /* If the Current LCD_Counter divided by any of the numbers
               has a remainder != 0, break the loop - meaning it is not
               an LCD */
            if(lcd_counter%argv[counter]!=0)
                break;
        }

        /* Break the Loop once LCD is found but only
           if all the inputs have been processed */
        if(counter==paramsCount)
        {
            lcd = lcd_counter;
            printf("LCD for the list is: %d\n", lcd);
            return SUCCESS_LCD_FOUND;
        }
    }

    /* Unlike GCD, it is possible that there is no LCD
       for the input numbers based on the range limit */
    printf("LCD not found for the list or have exceeded allowed range!\n");
    return ERROR_LCD__NOT_FOUND;
}