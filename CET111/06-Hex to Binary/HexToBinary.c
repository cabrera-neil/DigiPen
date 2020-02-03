/******************************************************************************
Filename: HexToBinary.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 07 Jun 2019
Brief Description: Convert HexaDecimal To Binary and Vice Versa
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

static const char* allowedCharacters = "FEDCBA9876543210";
static const int maxHexLength=8, maxBinLength=32;

char* HexToBin(char* charBin, char* formula);
char* BinToHex(char* charHex, char* formula);

int main(int argc,char* argv[]) 
{
    char* operation = argv[1];
    char* charNumbr = argv[2];
    
    /* STORAGE FOR CONVERSION AND SET TO INITIAL VALUE OF '0'*/
    char charHex[9] = { 0 }, charBin[33] = { 0 };
    memset(charHex, '0', maxHexLength);
    memset(charBin, '0', maxBinLength);

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
    if(!strcmp(operation, "-htob"))
    {
        /* ADDITIONAL ERROR CHECKS */
        if((int)strlen(charNumbr)!=(int)strspn(charNumbr, allowedCharacters))
        {
            printf("Invalid usage: %s.exe (%s) - Invalid Characters detected in the parameter!", argv[0], operation);
            return ERROR_INVALID_CHARACTERS;
        }

        if((int)(strlen)(charNumbr)>maxHexLength)
        {
            printf("Invalid usage: %s.exe (%s) - Overflow during conversion (Max is %d hexadecimal characters)!", argv[0], operation, maxHexLength);
            return ERROR_OVERFLOW;
        }

        /* COMPUTE */
        printf("%s is %s in Binary", charNumbr, HexToBin(&charBin[0], charNumbr));
    }
    else if(!strcmp(operation, "-btoh"))
    {
        /* ADDITIONAL ERROR CHECKS */
        if((int)strlen(charNumbr)!=(int)strspn(charNumbr, &allowedCharacters[14]))
        {
            printf("Invalid usage: %s.exe (%s) - Invalid Characters detected in the parameter!", argv[0], operation);
            return ERROR_INVALID_CHARACTERS;
        }

        if((int)(strlen)(charNumbr)>maxBinLength)
        {
            printf("Invalid usage: %s.exe (%s) - Overflow during conversion (Max is %d binary characters)!", argv[0], operation, maxBinLength);
            return ERROR_OVERFLOW;
        }

        /* COMPUTE */
        printf("%s is %s in Hexadecimal", charNumbr, BinToHex(&charHex[0], charNumbr));
    }
    else
    {
        printf("Invalid usage: %s.exe - Invalid Operation (only -htob or -btoh is allowed)!", argv[0]);
        return ERROR_INVALID_OPERAND;
    }

    return OK;
    /******************************/
    /* END OF PARSING AND COMPUTE */
    /******************************/
}

/* CONVERTS INPUT HEXADECIMAL TO BINARY 
   Returns: Pointer to the array of binary characters*/
char* HexToBin(char* charBin, char* formula)
{
    int counter, binPosition=maxBinLength-1;
    for(counter=(int)strlen(formula)-1; counter>=0; counter--)
    {
        /* ADJUST THE CHARACTER FROM CHAR TO NUMERICAL VALUE BY MINUSING OFFSET 
           If less than 10, offset by '0' to give 0-9 else offset by '7' to give 10-15 (refer to ASCII table)*/
        int hexValue, baseTwoPower;
        hexValue = formula[counter] - (formula[counter]<='9' ? '0' : '7');
        
        /* PERFORM BIT SHIFT BASED ON POWER OF 2 FROM 2^0=1 TO 2^3=8 
           If & operation results to != 0, then it means that Power of 2 position should be 1, else 0*/
        for(baseTwoPower=1; baseTwoPower<16; baseTwoPower*=2)
            charBin[binPosition--] = (hexValue&baseTwoPower)!=0 ? '1' : '0';
    }
    return charBin;
}

/* CONVERTS INPUT BINARY HEXADECIMAL STRING 
   Returns: Pointer to the array of hexadecimal characters*/
char* BinToHex(char* charHex, char* formula)
{
    int counter, hexPosition=maxHexLength-1;
    for(counter=(int)strlen(formula)-1; counter>=0;)
    {
        /* ADJUST THE CHARACTER FROM CHAR TO NUMERICAL VALUE BY MINUSING OFFSET 
           Multiply the character numerical value to the Power of Base 2 and keep adding to the hex value
           2^3, 2^2, 2^1, 2^0 */
        int hexValue=0, baseTwoPower;
        for(baseTwoPower=1; baseTwoPower<16 && counter>=0; baseTwoPower*=2)
        {
            /* Calculate the Final Hex Character after every 4th Binary Digit */
            hexValue+=baseTwoPower*(formula[counter]-'0');
            counter--;
        }
        charHex[hexPosition--] = allowedCharacters[15-hexValue];
    }
    return charHex;
}