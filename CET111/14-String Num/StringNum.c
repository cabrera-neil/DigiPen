/******************************************************************************
filename StringNum.c
author Neil Cabrera
email cabrera.n@digipen.edu
date created 02 Jul 2019
Brief Description: Implementation of StringNum Functions
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "StringNum.h"

/* Finds and return the length of given string */
/* check if string is too long above max int */
/* use limits.h */
int StringLength(const char* s1)
{
    /* Use Long in Case the String is too Long
       and check later if overflow beyond Int */
    long length = 0;
    
    if(s1==NULL)
    {
        printf("Error - Cannot pass an empty or null string!\n");
        return 0;
    }

    while(s1[length]!='\0')
    {
        if(length==INT_MAX-1)
        {
            printf("Error - String is too long! Unable to determine true length!\n");
            return 0;
        }

        ++length;
    }
    
    return length;
}

/* Converts the alphabet letters to all upper-case for given string */
void StringToUpper(char* s1)
{
    int length = 0;
    
    length = StringLength(s1);
    if(length==0)
        printf("Error - Cannot pass an empty or null string!\n");
    else
    {
        while(--length>=0)
        {
            /* Restrict Upper Case to ALPHA Chars, the Rest will be Ignored! */
            if(s1[length]>='a' && s1[length]<='z')
                s1[length] = s1[length] - ('a'-'A');
        }
    }
}

/* Converts the alphabet letters to all lower-case for given string */
void StringToLower(char* s1)
{
    int length = 0;
    
    length = StringLength(s1);
    if(length==0)
        printf("Error - Cannot pass an empty or null string!\n");
    else
    {
        while(--length>=0)
        {
            /* Restrict Lower Case to ALPHA Chars, the Rest will be Ignored! */
            if(s1[length]>='A' && s1[length]<='Z')
                s1[length] = s1[length] + ('a'-'A');
        }
    }
}

/* Copies a string from a source to a given destination up to length */
void StringCopy(char* dest, const char* source, int length)
{
    int index = 0, sourceLength = 0;
    char* temp = NULL;

    /* Error Check for Source is NULL */
    if(source==NULL)
    {
        printf("Error - Cannot pass an empty or null string as Source!\n");
        return;
    }

    /* Error Check for Destination is NULL */
    if(dest==NULL)
    {
        printf("Error - Cannot pass an empty or null string as Destination!\n");
        return;
    }

    /* Error Check for Source = Destination */
    if(source==dest)
    {
        printf("Error - Source and Destination is the same!\n");
        return;
    }

    /* Error Check for Length <= 0 */
    if(length<=0)
    {
        printf("Error - Invalid Length!\n");
        return;
    }

    /* Error Check for Source Length <= 0 */
    sourceLength = StringLength(source);
    if(sourceLength==0)
    {
        printf("Error - Source is NULL or Empty! Nothing to Copy!\n");
        return;
    }

    /* Possible Scenarios 
        1) Destination longer than Source
        2) Destination shorter than Source
        3) Destination equal to Source 
        4) Address of Source and Destination Overlap (vice versa) */
    
    /* Overlap from Source to Dest */
    index = 0;
    while(index<sourceLength)
    {
        if(&source[index]==&dest[0])
        {
            printf("Error - Overlap of Source and Destination Memory Address!\n");
            return;
        }
        ++index;
    }

    /* Overlap from Dest to Source 
       Add 1 to Destination Length to take into account the Terminator */
    index = 0;
    while(index<length+1)
    {
        if(&dest[index]==&source[0])
        {
            printf("Error - Overlap of Destination and Source Memory Address!\n");
            return;
        }
        ++index;
    }

    /* Input Source is shorter than Destination Length
       copy only until the length of the source */
    if(sourceLength<length)
        printf("Warning - Destination Length is more than Source Length!\n");

    /* Input Source is longer than Destination Length, not all will be copied */
    if(sourceLength>length)
        printf("Warning - Source is longer than Destination, excess will be truncated!\n");

    /* Create Buffer Location to Save the Source */
    temp = (char*) calloc(sourceLength+1, sizeof(char));

    /* Error Check for Memory Allocation */
    if(temp==NULL)
    {
        printf("Error - Memory Allocation failed. Unable to copy!\n");
        return;
    }

    /* Perform Copy to Temp from Source */
    index = 0;
    while(index<sourceLength)
    {
        temp[index] = source[index];
        ++index;
    }

    /* Add Terminator at the end of the Temp */
    temp[index] = '\0';

    /* Perform Copy to Temp from Dest 
       Source Length does not include Terminator 
       whereas Input Length is the Destination length inclusive of Terminator
       hence length - 1 */
    index = 0;
    while(index<sourceLength && index<length-1)
    {
        dest[index] = temp[index];
        ++index;
    }

    /* Add Terminator at the end of the Dest */
    dest[index] = '\0';

    /* Free Allocated Memory */
    free(temp);
}

/* Compares 2 strings, return 1 for match, 0 otherwise */
int StringIsEqual(const char* s1, const char* s2)
{
    int counter = 0, lengthS1 = 0, lengthS2 = 0;

    lengthS1 = StringLength(s1);
    lengthS2 = StringLength(s2);

    /* Error Check for S1 is NULL or Empty */
    if(lengthS1==0)
    {
        printf("Error - Cannot pass an empty or null string!\n");
        return 0;
    }

    /* Error Check for S2 is NULL or Empty */
    if(lengthS2==0)
    {
        printf("Error - Cannot pass an empty or null string!\n");
        return 0;
    }

    /* Error Check for S1 and S2 pointing to the same variable */
    /* Same Pointer, Return 1 */
    if(&s1[0]==&s2[0])
    {
        printf("Warning - Comparing to itself!\n");
        return 1;
    }

    /* Compare Length, if Different Return 0 */
    if(lengthS1!=lengthS2)
        return 0;
    else
    {
        while(counter<lengthS1)
        {
            /* Break loop and Return 0 once there is Difference
               otherwise continue until end */
            if(s1[counter]!=s2[counter])
                return 0;
            ++counter;
        }
    }
    return 1;
}

/* Finds the value string in target string, returns 1 for match, 0 otherwise */
int StringFind(const char* target, const char* value)
{
    int counterT = 0, counterV = 0, lengthV = 0, lengthT = 0;

    lengthV = StringLength(value);
    lengthT = StringLength(target);

    /* Error Check for Value is NULL or Empty */
    if(lengthV==0)
    {
        printf("Error - Cannot pass an empty or null string!\n");
        return 0;
    }

    /* Error Check for Target is NULL or Empty */
    if(lengthT==0)
    {
        printf("Error - Cannot pass an empty or null string!\n");
        return 0;
    }

    /* Error Check for Target and Value pointing to the same variable */
    /* Same Pointer, Return 1 */
    if(target==value)
    {
        printf("Warning - Pointing to same Value and Target!\n");
        return 1;
    }

    /* If Target is already less than Value, definitely cannot find already,
       Return 0 */
    if(lengthT<lengthV)
    {
        printf("Info - '%s' not found in '%s'!\n", value, target);
        return 0;
    }
    else
    {
        /* Loop Through Each Character in the Target until end 
           and compare the source from the current index of the target */
        while(counterT<lengthT)
        {
            /* Check if current Target Index plus the length of the Value
               is still within the bounds of the Target */
            if((counterT+lengthV)<=lengthT)
            {
                counterV=0;
                while(counterV<lengthV)
                {
                    if(value[counterV]!=target[counterT+counterV])
                        break;
                    ++counterV;
                }

                /* When the Inner Loop is Terminated, Check if it ran through its course
                   If yes, then the string was found in the target */
                if((counterV)==lengthV)
                {
                    printf("Info - Found occurence of '%s' in '%s'.\n", value, target);
                    return 1;
                }
            }
            else
            {
                printf("Info - '%s' not found in '%s'!\n", value, target);
                return 0;
            }
            ++counterT;
        }
    }

    printf("Info - '%s' not found in '%s'!\n", value, target);
    return 0;
}

/* Finds of any of the values are in target, return 1 for match, 0 otherwise */
int StringContains(const char* target, const char* values)
{
    int counterV = 0, lengthV = 0, lengthT = 0;

    lengthV = StringLength(values);
    lengthT = StringLength(target);

    /* Error Check for Value is NULL or Empty */
    if(lengthV==0)
    {
        printf("Error - Cannot pass an empty or null string!\n");
        return 0;
    }

    /* Error Check for Target is NULL or Empty */
    if(lengthT==0)
    {
        printf("Error - Cannot pass an empty or null string!\n");
        return 0;
    }

    /* Error Check for Target and Value pointing to the same variable */
    /* Same Pointer, Return 1 */
    if(target==values)
    {
        printf("Warning - Pointing to same Value and Target!\n");
        return 1;
    }

    while(counterV<lengthV)
    {
        /* Create temp storage to store char as string and pass to StringFind */
        char temp[] = " ";
        temp[0] = values[counterV++];
        if(StringFind(target, temp))
        {
            printf("Info - Found occurence of '%s' in '%s'.\n", values, target);
            return 1;
        }
    }

    printf("Info - Value(s) not Found!\n");
    return 0;
}

/* Converts the string to an integer output */
/* allow to negative numbers and positive hehehe */
int ArrayToInt(const char* input)
{
    long index = 0, length = 0, multiplier = 1, convertedValue = 0;
    
    length = StringLength(input);
    if(length==0)
    {
        printf("Error - Cannot pass an empty or null string!\n");
        return 0;
    }

    while(index<length)
    {
        /* Restrict to Numbers Only, Ignore the Sign */
        if(input[index]>='0' && input[index]<='9')
        {
            convertedValue = convertedValue*multiplier + (input[index] - '0');
            
            if(convertedValue>0 && multiplier!=10)
                multiplier *= 10;
        }
        else
        {
            printf("Warning - Invalid Characters found (Ignore remaining characters)!\n");
            break;
        }
        ++index;
    }

    if(convertedValue>INT_MAX)
    {
        printf("Error - Integer Overflow, Returning 0!\n");
        return 0;
    }
    else
        return (int) convertedValue;
}

/* Converts an integer to a string and write to result with size limit */
void IntToString(char* result, int input, int limit)
{
    long index = 0, multiplier = 1;

    /* Error Check for Destination is NULL */
    if(result==NULL)
    {
        printf("Error - Cannot pass an empty or null string!\n");
        return;
    }

    /* This Function only takes in Positive Numbers */
    if(input<0)
    {
        printf("Error - Input can only be 0 or Positive!\n");
        return;
    }

    /* Error Check for Limit <= 1
       Limit needs to be greater than 1 because it includes the terminator */
    if(limit<=1)
    {
        printf("Error - Invalid Limit (Limit needs to be greater than 1 because it includes the terminator)!\n");
        return;
    }

    /* Calculate the Biggest Multiplier in Base 10 */
    while(input/multiplier!=0)
        multiplier *= 10;
    
    multiplier /= 10;
    /* Extract the Digits from Right to Left by Division */
    while(index<limit-1 && multiplier!=0)
    {
        result[index++] = '0' + input/multiplier;
        input %= multiplier;
        multiplier /= 10;
    }

    /* Check if Index didn't increment
       It means the Value is 0 */
    if(index==0)
        result[index++] = '0';

    result[index] = '\0';
}