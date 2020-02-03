/******************************************************************************
Filename: DecToBinary.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 03 Jun 2019
Brief Description: Convert Decimal To Binary and Vice Versa
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0x00
#define ERROR_MISSING_PARAM 0x01
#define ERROR_EXCESS_PARAMS 0x02
#define ERROR_INVALID_CHARACTERS 0x03
#define ERROR_INVALID_OPERAND 0x04
#define ERROR_OVERFLOW 0x05

#define MODE 0x20
#define BASE 0x02

void DecimalToBinary(int number);
int BinaryToDecimal(char* formula);

int main(int argc,char* argv[]) 
{
    char* operation = argv[1];
    char* charNumbr = argv[2];
    const char* allowedCharacters = "9876543210";
    const int maxInt = 2147483647;

    /*************************************/
    /* START OF PRELIMINARY ERROR CHECKS */
    /*************************************/
    if(3>argc)
    {
        printf("Invalid Usage %s.exe - Missing Parameter or Incomplete Parameters!", argv[0]);
        return ERROR_MISSING_PARAM;
    }

    if(3<argc)
    {
        printf("Invalid Usage %s.exe - Excess Parameters!", argv[0]);
        return ERROR_EXCESS_PARAMS;
    }
    /***********************************/
    /* END OF PRELIMINARY ERROR CHECKS */
    /***********************************/

    /********************************/
    /* START OF PARSING AND COMPUTE */
    /********************************/
    if(!strcmp(operation, "-dtob"))
    {
        /* ADDITIONAL ERROR CHECKS */
        if((int)strlen(charNumbr)!=(int)strspn(charNumbr, allowedCharacters))
        {
            printf("Invalid usage: %s.exe - Invalid Characters detected in the parameter!", argv[0]);
            return ERROR_INVALID_CHARACTERS;
        }

        if((long)atol(charNumbr)>(long)maxInt)
        {
            printf("Invalid usage: %s.exe - Overflow during conversion (Cannot exceed 2^31-1)!", argv[0]);
            return ERROR_OVERFLOW;
        }

        /* COMPUTE */
        DecimalToBinary((int)atoi(charNumbr));
    }
    else if(!strcmp(operation, "-btod"))
    {
        /* ADDITIONAL ERROR CHECKS */
        if((int)strlen(charNumbr)!=(int)strspn(charNumbr, &allowedCharacters[8]))
        {
            printf("Invalid usage: %s.exe - Invalid Characters detected in the parameter!", argv[0]);
            return ERROR_INVALID_CHARACTERS;
        }

        if((int)strlen(charNumbr)>=MODE)
        {
            printf("Invalid usage: %s.exe - Overflow during conversion (Cannot exceed 31 bits)!", argv[0]);
            return ERROR_OVERFLOW;
        }

        /* COMPUTE */
        printf("%s is %d in Decimal", charNumbr, BinaryToDecimal(charNumbr));
    }
    else
    {
        printf("Invalid usage: %s.exe - Invalid Operation (only -btod or -dtob is allowed)!", argv[0]);
        return ERROR_INVALID_OPERAND;
    }

    return OK;
    /******************************/
    /* END OF PARSING AND COMPUTE */
    /******************************/
}

/* CONVERTS INPUT DECIMAL TO BINARY STRING */
void DecimalToBinary(int number)
{
    char charBinary[MODE] = { 0 };
    int counter;
    
    printf("%d is ", number);
    for(counter=0; counter<MODE; counter++)
    {
        charBinary[counter] = 0==number%BASE ? '0' : '1';
        number /= BASE;
    }
    
    for(; counter>0; counter--)
        printf("%c%c", 0!=counter%4 ? '\0' : ' ', charBinary[counter-1]);
    printf(" in Binary");
}

/* CONVERTS INPUT BINARY STRING TO DECIMAL */
int BinaryToDecimal(char* formula)
{
    int numberLength, counter, digit, total=0, multiplier=1;
    numberLength = strlen(formula);

    for(counter=numberLength-1; counter>=0; counter--)
    {
        digit = formula[counter] - '0';
        total+=digit*multiplier;
        multiplier*=2;
    }

    return total;
}