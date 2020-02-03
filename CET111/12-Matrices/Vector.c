/******************************************************************************
filename Vector.C
author Neil Cabrera
email cabrera.n@digipen.edu
date created 20 Jun 2019
Brief Description: Implementation of Vector Functions from Vector.h
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"

/* Prints the vector given in the following format: vec4(x,y,z,w) */
void PrintVector(const struct Vec4* a)
{
    /* Check if a is not NULL */
    if(a!=NULL)
        printf("vec4(%f, %f, %f, %f)\n",a->x, a->y, a->z, a->w);
    else
        printf("Error - vec4 is not Initialised!\n");
}

/* Sets the values in the given vector */
void SetVector(struct Vec4* result, float x, float y, float z, float w)
{
    /* Check if Target Vector is NULL,
       if Yes, do not perform allocation as there is no way to clear it
       later on  */
    if(result!=NULL)
    {
        result->x = x;
        result->y = y;
        result->z = z;
        result->w = w;
    }
    else
        printf("Error - Target vec4 is not Initialised!\n");
}

/* Copies the values from a to result */
void CopyVector(struct Vec4* result, const struct Vec4* a)
{
    /* Check if Source Vector is not NULL */
    if(a==NULL)
    {
        printf("Error - Source vec4 is not Initialised!\n");
        return;
    }

    /* Check if Target Vector is not NULL */
    if(result==NULL)
    {
        printf("Error - Target vec4 is not Initialised!\n");
        return;
    }

    SetVector(result, a->x, a->y, a->z, a->w);
}

/* Adds the values in vector a and b and write to result */
void AddVector(struct Vec4* result, const struct Vec4* a, const struct Vec4* b)
{
    /* Check if Operand A Vector is not NULL */
    if(a==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Operand B Vector is not NULL */
    if(b==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Target Vector is not NULL */
    if(result!=NULL)
    {
        result->x = a->x + b->x;
        result->y = a->y + b->y;
        result->z = a->z + b->z;
        result->w = a->w + b->w;
    }
    else
        printf("Error - Target vec4 is not Initialised!\n");
}

/* Subtracts the values of a by b and write to result */
void SubtractVector(struct Vec4* result, const struct Vec4* a, const struct Vec4* b)
{
    /* Check if Operand A Vector is not NULL */
    if(a==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Operand B Vector is not NULL */
    if(b==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Target Vector is not NULL */
    if(result!=NULL)
    {
        result->x = a->x - b->x;
        result->y = a->y - b->y;
        result->z = a->z - b->z;
        result->w = a->w - b->w;
    }
    else
        printf("Error - Target vec4 is not Initialised!\n");
}

/* Multiplies the values of a by b and write to result */
void MultiplyVector(struct Vec4* result, const struct Vec4* a, const struct Vec4* b)
{
    /* Check if Operand A Vector is not NULL */
    if(a==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Operand B Vector is not NULL */
    if(b==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Target Vector is not NULL */
    if(result!=NULL)
    {
        result->x = a->x * b->x;
        result->y = a->y * b->y;
        result->z = a->z * b->z;
        result->w = a->w * b->w;
    }
    else
        printf("Error - Target vec4 is not Initialised!\n");
}

/* Divides the values of a by b and write to result */
void DivideVector(struct Vec4* result, const struct Vec4* a, const struct Vec4* b)
{
    /* Check if Operand A Vector is not NULL */
    if(a==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Operand B Vector is not NULL */
    if(b==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Target Vector is not NULL */
    if(result!=NULL)
    {
        /* Set the Result to 0 beforehand as the calculation
           may be Divide by 0 */
        SetVector(result,0,0,0,0);

        /* If any of the components results to Divide by 0,
           do not proceed */
        if((b->x * b->y * b->z * b->w)!=0)
        {
            /* Check for Divide by 0 */
            result->x = a->x / b->x;
            result->y = a->y / b->y;
            result->z = a->z / b->z;
            result->w = a->w / b->w;
        }
        else
            printf("Error - Divide by 0!\n");
    }
    else
        printf("Error - Target vec4 is not Initialised!\n");
}

/* Scale vector a by scale and write to result */
void ScaleVector(struct Vec4* result, const struct Vec4* a, float scale)
{
    /* Check if Source Vector is not NULL */
    if(a==NULL)
    {
        printf("Error - Source vec4 is not Initialised!\n");
        return;
    }

    /* Check if Target Vector is not NULL */
    if(result!=NULL)
    {
        result->x = a->x * scale;
        result->y = a->y * scale;
        result->z = a->z * scale;
        result->w = a->w * scale;
    }
    else
        printf("Error - Target vec4 is not Initialised!\n");
}

/* Compute the squared length of given vector a */
float GetVectorSquaredLength(const struct Vec4* a)
{
    /* Check if Source Vector is not NULL 
       if NULL, return a 0 value */
    if(a!=NULL)
        return pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2) + pow(a->w, 2);
    else
        return 0;
}

/* Compute the length of given vector a */
float GetVectorLength(const struct Vec4* a)
{
    /* Check if Source Vector is not NULL 
       if NULL return a 0 value */
    if(a!=NULL)
        return sqrt(GetVectorSquaredLength(a));
    else
        return 0;
}

/* Normalizes the given vector a and write to result */
void NormalizeVector(struct Vec4* result, const struct Vec4* a)
{
    float vectorLength;

    /* Check if Source Vector is not NULL */
    if(a==NULL)
    {
        printf("Error - Source vec4 is not Initialised!\n");
        return;
    }

    /* Check if Target Vector is not NULL */
    if(result==NULL)
    {
        printf("Error - Target vec4 is not Initialised!\n");
        return;
    }

    vectorLength = GetVectorLength(a);
    if(vectorLength!=0)
    {
        result->x = a->x / vectorLength;
        result->y = a->y / vectorLength;
        result->z = a->z / vectorLength;
        result->w = a->w / vectorLength;
    }
    else
    {
        /* If Divide by 0, return a 0 Vector */
        SetVector(result, 0, 0, 0,0 );
        printf("Error - Divide by 0!\n");
    }
}

/* Compute the dot product of vectors a and b */
float VectorDotProduct(const struct Vec4* a, const struct Vec4* b)
{
    /* Check if Operand A Vector is not NULL */
    if(a==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return 0;
    }

    /* Check if Operand B Vector is not NULL */
    if(b==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return 0;
    }

    return (a->x * b->x) + (a->y * b->y) + (a->z * b->z) + (a->w * b->w);
}

/* Compute the cross product of vectors a x b and write to result */
void VectorCrossProduct(struct Vec4* result, const struct Vec4* a, const struct Vec4* b)
{
    /* Check if Operand A Vector is not NULL */
    if(a==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Operand B Vector is not NULL */
    if(b==NULL)
    {
        printf("Error - Operand vec4 is not Initialised!\n");
        return;
    }

    /* Check if Target Vector is not NULL */
    if(result!=NULL)
    {
        result->x = (a->y * b->z) - (a->z * b->y);
        result->y = (a->z * b->x) - (a->x * b->z);
        result->z = (a->x * b->y) - (a->y * b->x);
        result->w = 0;
    }
    else
        printf("Error - Target vec4 is not Initialised!\n");
}

/* Find the largest value among components in given vector a */
float GetVectorMax(const struct Vec4* a)
{
    float largest = 0;

    /* Check if Vector is NULL */
    if(a==NULL)
    {
        printf("Error - Source vec4 is not Initialised!\n");
        return largest;
    }

    /* Vector Components are Scalar, therefore compare by
       absolute value and return */
    if(fabs(a->x) > largest)
        largest = fabs(a->x);
    if(fabs(a->y) > largest)
        largest = fabs(a->y);
    if(fabs(a->z) > largest)
        largest = fabs(a->z);
    if(fabs(a->w) > largest)
        largest = fabs(a->w);
    
    return largest;
}

/* Find the smallest value among components in given vector a */
float GetVectorMin(const struct Vec4* a)
{
    float smallest = 0;

    /* Check if Vector is NULL */
    if(a==NULL)
    {
        printf("Error - Source vec4 is not Initialised!\n");
        return smallest;
    }

    /* Vector Components are Scalar, therefore compare by
       absolute value and return */
    if(fabs(a->x) < smallest)
        smallest = fabs(a->x);
    if(fabs(a->y) < smallest)
        smallest = fabs(a->y);
    if(fabs(a->z) < smallest)
        smallest = fabs(a->z);
    if(fabs(a->w) < smallest)
        smallest = fabs(a->w);
    
    return smallest;
}