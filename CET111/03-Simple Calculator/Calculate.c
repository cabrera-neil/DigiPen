/******************************************************************************
Filename: Calculate.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 29 May 2019
Brief Description: Process simple math expressions and provide the answer
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0x00
#define ERROR_MISSING_PARAM 0x01
#define ERROR_EXCESS_PARAMS 0x02
#define ERROR_INVALID_CHARACTERS 0x03
#define ERROR_DIVIDE_BY_ZERO 0x04
#define ERROR_MATH_EQUATION 0x05

int isDigit(char character);
int isOperand(char character);

int main(int argc,char* argv[]) 
{ 
    char* formula = argv[1];
    char* allowedCharacters = "1234567890+-*/";
    int formulaLength;

    int counter, result;
    char operand = ' ';
    result = 0;

    /*************************************/
    /* START OF PRELIMINARY ERROR CHECKS */
    /*************************************/
    if(1==argc)
    {
        printf("\nInvalid usage: %s.exe - Missing Mathematical Expression!", argv[0]);
        return ERROR_MISSING_PARAM;
    }

    if(3<=argc)
    {
        printf("\nInvalid usage: %s.exe - Too many parameters!", argv[0]);
        return ERROR_EXCESS_PARAMS;
    }

    formulaLength = strlen(formula);
    if(formulaLength!=(int)strspn(formula, allowedCharacters))
    {
        printf("\nInvalid usage: %s.exe - Invalid Characters detected in the Mathematical Expression!", argv[0]);
        return ERROR_INVALID_CHARACTERS;
    }

    if(isOperand(formula[0]))
    {
        printf("\nInvalid usage: %s.exe - Mathematical Expression cannot start with an operand!", argv[0]);
        return ERROR_MATH_EQUATION;
    }

    if(isOperand(formula[formulaLength-1]))
    {
        printf("\nInvalid usage: %s.exe - Mathematical Expression cannot end with an operand!", argv[0]);
        return ERROR_MATH_EQUATION;
    }
    /***********************************/
    /* END OF PRELIMINARY ERROR CHECKS */
    /***********************************/

    /********************************/
    /* START OF PARSING AND COMPUTE */
    /********************************/
    for(counter=0; counter<(int)strlen(formula); counter++)
    {
        /* PARSE FOR NUMBER */
        if(isDigit(formula[counter]))
        {
            int numberCounter;
            char temp[255] = {0};

            for(numberCounter=0; isDigit(formula[counter+numberCounter]); numberCounter++)
                temp[numberCounter] = formula[counter+numberCounter];
            
            counter+=numberCounter-1;

            if(operand=='+')
                result+=atoi(temp);
            else if(operand=='-')
                result-=atoi(temp);
            else if(operand=='*')
                result*=atoi(temp);
            else if(operand=='/')
            {
                /* ADDITIONAL ERROR CHECKING - PROTECTION FOR DIVIDE BY 0 */
                if(atoi(temp)==0)
                {
                    printf("\nInvalid usage: %s.exe - Divide by 0 Error!", argv[0]);
                    return ERROR_DIVIDE_BY_ZERO;
                }

                result/=atoi(temp);
            }
            else
                result=atoi(temp); /* IF OPERAND IS EMPTY, THIS IS THE BEGINNING OF THE EQUATION */
            
            /* CLEAR OPERAND BY DEFAULT EITHER ON INITIAL RUN OR AFTER COMPUTATION */    
            operand=' ';
            continue;    
        }
        
        /* PARSE FOR OPERAND */
        if(operand==' ' && isOperand(formula[counter]))
        {
            operand=formula[counter];
            continue;
        }

        /* ADDITIONAL ERROR CHECKING - CONSECUTIVE OPERANDS */
        if(operand!=' ' && isOperand(formula[counter]))
        {
            printf("\nInvalid usage: %s.exe - Mathematical Expression cannot have consecutive operands!", argv[0]);
            return ERROR_MATH_EQUATION;
        }
    }
    printf("\n%s = %d", formula, result);
    /******************************/
    /* END OF PARSING AND COMPUTE */
    /******************************/

    /* PROGRAM TERMINATES WITH NO ERROR */
    return OK;
}

int isDigit(char character)
{
    return (character>='0' && character<='9');
}

int isOperand(char character)
{
    return (character=='+' || character=='-' || character=='*' || character=='/');
}