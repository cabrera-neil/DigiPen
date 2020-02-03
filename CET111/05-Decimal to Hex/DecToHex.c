/******************************************************************************
Filename: DecToHex.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 06 Jun 2019
Brief Description: Convert Decimal To HexaDecimal and Vice Versa
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

int HexToDec(char* formula);
char* DecToHex(char* charHex, int maxLength, int decimal);

static const char* allowedCharacters = "FEDCBA9876543210";
static const int maxInt = 2147483647, hexCharCount = 16;

int main(int argc,char* argv[]) 
{
    char* operation = argv[1];
    char* charNumbr = argv[2];
    
    /* STORAGE FOR CONVERSION */
    char charHex[9] = { 0 };
    int numberDec;

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
    if(!strcmp(operation, "-htod"))
    {
        /* ADDITIONAL ERROR CHECKS */
        if((int)strlen(charNumbr)!=(int)strspn(charNumbr, allowedCharacters))
        {
            printf("Invalid usage: %s.exe (%s) - Invalid Characters detected in the parameter!", argv[0], operation);
            return ERROR_INVALID_CHARACTERS;
        }

        if((int)(strlen)(charNumbr)>8)
        {
            printf("Invalid usage: %s.exe (%s) - Overflow during conversion (Max is 8 hexadecimal characters)!", argv[0], operation);
            return ERROR_OVERFLOW;
        }

        /* COMPUTE AND CHECK RETURNED RESULT*/
        numberDec = HexToDec(charNumbr);
        if (numberDec==-1)
        {
            printf("Invalid usage: %s.exe (%s) - Overflow during conversion (Cannot exceed 7FFF FFFF)!", argv[0], operation);
            return ERROR_OVERFLOW;
        }
        else
            printf("%s is %d in Decimal", charNumbr, numberDec);
    }
    else if(!strcmp(operation, "-dtoh"))
    {
        /* ADDITIONAL ERROR CHECKS */
        if((int)strlen(charNumbr)!=(int)strspn(charNumbr, &allowedCharacters[6]))
        {
            printf("Invalid usage: %s.exe (%s) - Invalid Characters detected in the parameter!", argv[0], operation);
            return ERROR_INVALID_CHARACTERS;
        }

        if((long)atol(charNumbr)>(long)maxInt)
        {
            printf("Invalid usage: %s.exe (%s) - Overflow during conversion (Cannot exceed 2^31-1)!", argv[0], operation);
            return ERROR_OVERFLOW;
        }

        /* COMPUTE */
        printf("%s is %s in Hexadecimal", charNumbr, DecToHex(&charHex[0], MODE/4, (int)atoi(charNumbr)));
    }
    else
    {
        printf("Invalid usage: %s.exe - Invalid Operation (only -htod or -dtoh is allowed)!", argv[0]);
        return ERROR_INVALID_OPERAND;
    }

    return OK;
    /******************************/
    /* END OF PARSING AND COMPUTE */
    /******************************/
}

/* CONVERTS INPUT HEXADECIMAL TO DECIMAL 
   Returns: -1 if Overflow or Resulting Decimal Equivalent if Successful*/
int HexToDec(char* formula)
{
    int counter;
    long int total = 0, multiplier=1;
    for(counter=strlen(formula)-1; counter>=0; counter--)
    {
        /* ADJUST THE CHARACTER FROM CHAR TO NUMERICAL VALUE BY MINUSING OFFSET 
           If less than 10, offset by '0' to give 0-9 else offset by '7' to give 10-15 (refer to ASCII table)*/
        total+=(formula[counter] - (formula[counter]<='9' ? '0' : '7'))*multiplier;
        multiplier*=hexCharCount;
    }
    return total>(long)maxInt ? -1 : (int)total;
}

/* CONVERTS INPUT DECIMAL HEXADECIMAL STRING 
   Returns: Pointer to the array of hexadecimal characters*/
char* DecToHex(char* charHex, int maxLength, int decimal)
{
    int counter;
    for(counter=maxLength-1; counter>=0; counter--)
    {
        /* REUSE THE ALLOWED CHARACTERS TO DETERMINE THE HEX CHARACTER BASED ON THE REMAINDER */
        charHex[counter] = allowedCharacters[hexCharCount-decimal%hexCharCount-1];
        decimal/=hexCharCount;
    }
    return charHex;
}