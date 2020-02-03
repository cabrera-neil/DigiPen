/******************************************************************************
Filename: Matrix.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 26 Jun 2019
Brief Description: Implementation of Matrix.h functions
******************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "Matrix.h"

#define RADIAN 3.14159265358979323846 / 180 /* Use this for the Trigo Functions */

/* Prints the matrix as such: mat4x4(0,1,2...,15) */
void PrintMatrix(const struct Mat4x4* a)
{
    /* Check if a is not NULL */
    if(a!=NULL)
    {
        int row, col;
        printf("Printing Mat4x4:\n");
        for(row=0; row<4; row++)
            for(col=0; col<4; col++)
                printf("%0.4f, %s", a->value[row][col], col==3 ? "\n" : "");
    }
    else
        printf("Error - Mat4x4 is not Initialised!\n");
}

/* Sets the given matrix to identity */
void SetIdentityMatrix(struct Mat4x4* result)
{
    /* Check if result is not NULL */
    if(result!=NULL)
    {
        int row, col;
        for(row=0; row<4; row++)
            for(col=0; col<4; col++)
                result->value[row][col] = row==col ? 1 : 0;
    }
    else
        printf("Error - Mat4x4 is not Initialised!\n");
}

/* Sets the given matrix to a scaling matrix of scaling factor given */
void SetScaleMatrix(struct Mat4x4* result, float scalingFactor)
{
    int position;

    /* Check if result is not NULL */
    if(result!=NULL)
    {
        /* Reuse the SetIdentity Matrix */
        SetIdentityMatrix(result);

        /* No need to Set the Last Column and Row and Keep it as 1 */
        for(position=0; position<3; position++)
            result->value[position][position] = scalingFactor;
    }
    else
        printf("Error - Mat4x4 is not Initialised!\n");
}

/* Sets the given matrix to a rotation along X axis by degree given */
void SetRotateXMatrix(struct Mat4x4* result, float degree)
{
    /* Check if result is not NULL */
    if(result!=NULL)
    {
        /* Create Transformation Matrix */
        SetMatrixRow(result, 0,1,0,0,0);
        SetMatrixRow(result, 1,0,cos(degree*RADIAN),-sin(degree*RADIAN),0);
        SetMatrixRow(result, 2,0,sin(degree*RADIAN), cos(degree*RADIAN),0);
        SetMatrixRow(result, 3,0,0,0,1);
    }
    else
        printf("Error - Mat4x4 is not Initialised!\n");
}

/* Sets the given matrix to a rotation along Y axis by degree given */
void SetRotateYMatrix(struct Mat4x4* result, float degree)
{
    /* Check if result is not NULL */
    if(result!=NULL)
    {
        /* Create Transformation Matrix */
        SetMatrixRow(result, 0,cos(degree*RADIAN),0,sin(degree*RADIAN),0);
        SetMatrixRow(result, 1,0,1,0,0);
        SetMatrixRow(result, 2,-sin(degree*RADIAN),0,cos(degree*RADIAN),0);
        SetMatrixRow(result, 3,0,0,0,1); 
    }
    else
        printf("Error - Mat4x4 is not Initialised!\n");
}

/* Sets the given matrix to a rotation along Z axis by degree given */
void SetRotateZMatrix(struct Mat4x4* result, float degree)
{
    /* Check if result is not NULL */
    if(result!=NULL)
    {
        /* Create Transformation Matrix */
        SetMatrixRow(result, 0,cos(degree*RADIAN),-sin(degree*RADIAN),0,0);
        SetMatrixRow(result, 1,sin(degree*RADIAN), cos(degree*RADIAN),0,0);
        SetMatrixRow(result, 2,0,0,1,0);
        SetMatrixRow(result, 3,0,0,0,1);
    }
    else
        printf("Error - Mat4x4 is not Initialised!\n");
}

/* Sets the given matrix to a translation matrix by offsets x,y,z given */
void SetTranslateMatrix(struct Mat4x4* result, float x, float y, float z)
{
    /* Check if result is not NULL */
    if(result!=NULL)
    {
        /* Create Transformation Matrix */
        SetMatrixRow(result, 0,1,0,0,x);
        SetMatrixRow(result, 1,0,1,0,y);
        SetMatrixRow(result, 2,0,0,1,z);
        SetMatrixRow(result, 3,0,0,0,1);
    }
    else
        printf("Error - Mat4x4 is not Initialised!\n");
}

/* Transpose the given matrix and writes to result */
void TransposeMatrix(struct Mat4x4* result, const struct Mat4x4* a)
{
    int row, col;

    /* Check if Source is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }
    
    /* Check if Target is not NULL */
    if(result==NULL)
    {
        printf("Error - Target Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==a)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Transpose all: X,Y,Z  and W */
    for(col=0; col<4; col++)
        for(row=0; row<4; row++)
            result->value[col][row] = a->value[row][col];
}

/* Sets the result matrix to the special inverse of the given rotate & translate matrix */
void SetRotateTranslateInverse(struct Mat4x4* result, const struct Mat4x4* a)
{
    int row, col;

    /* Check if Source is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }
    
    /* Check if Target is not NULL */
    if(result==NULL)
    {
        printf("Error - Target Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==a)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Transpose the X, Y, Z from Source to Target */
    for(col=0; col<3; col++)
        for(row=0; row<3; row++)
            result->value[col][row] = a->value[row][col];

    /* Negate the Translate Values */
    result->value[0][3] = -a->value[0][3]; /* x */
    result->value[1][3] = -a->value[1][3]; /* y */
    result->value[2][3] = -a->value[2][3]; /* z */

    /* Copy the Last Row */
    SetMatrixRow(result, 3,a->value[3][0],a->value[3][1],a->value[3][2],a->value[3][3]);
}

/* Sets the given row of the matrix to the given x,y,z,w values provided */
void SetMatrixRow(struct Mat4x4* result, int rowIndex, float x, float y, float z, float w)
{
    /* Check if a is not NULL */
    if(result!=NULL)
    {
        if(rowIndex<4 && rowIndex>=0) /* Check if Index is out of Range */
        {
            result->value[rowIndex][0] = x;
            result->value[rowIndex][1] = y;
            result->value[rowIndex][2] = z;
            result->value[rowIndex][3] = w;
        }
        else
            printf("Error - Row Index out of range!\n");
    }
    else
        printf("Error - Mat4x4 is not Initialised!\n");
}

/* Sets the given column of the matrix to the given x,y,z,w values provided */
void SetMatrixColumn(struct Mat4x4* result, int colIndex, float x, float y, float z, float w)
{
    /* Check if a is not NULL */
    if(result!=NULL)
    {
        if(colIndex<4 && colIndex>=0) /* Check if Index is out of Range */
        {
            result->value[0][colIndex] = x;
            result->value[1][colIndex] = y;
            result->value[2][colIndex] = z;
            result->value[3][colIndex] = w;
        }
        else
            printf("Error - Col Index out of range!\n");
    }
    else
        printf("Error - Mat4x4 is not Initialised!\n");
}

/* Copies the given matrix a values to the result */
void CopyMatrix(struct Mat4x4* result, const struct Mat4x4* a)
{
    int row, col;

    /* Check if Source is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }
    
    /* Check if Target is not NULL */
    if(result==NULL)
    {
        printf("Error - Target Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==a)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Perform a Cell by Cell Copy */
    for(row=0; row<4; row++)
        for(col=0; col<4; col++)
            result->value[row][col] = a->value[row][col];
}

/* Adds the values component-wise from a and b and writes to result */
void AddMatrix(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b)
{
    int row, col;
    double value;

    /* Check if Source is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Source is not NULL */
    if(b==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }
    
    /* Check if Target is not NULL */
    if(result==NULL)
    {
        printf("Error - Target Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==a)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==b)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Perform a Cell by Cell Copy */
    for(row=0; row<4; row++)
        for(col=0; col<4; col++)
        {
            value = a->value[row][col] + b->value[row][col];
            if(value>-FLT_MAX && value<FLT_MAX)
                result->value[row][col] = value;
            else
            {
                printf("Error - Overflow/Underflow! Returning an Identity Matrix.\n");
                SetIdentityMatrix(result);
                return;
            }
        }
}

/* Subtracts the values component-wise of a by b and writes to result */
void SubtractMatrix(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b)
{
    int row, col;
    double value;

    /* Check if Source is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Source is not NULL */
    if(b==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }
    
    /* Check if Target is not NULL */
    if(result==NULL)
    {
        printf("Error - Target Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==a)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==b)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Perform a Cell by Cell Copy */
    for(row=0; row<4; row++)
        for(col=0; col<4; col++)
        {
            value = a->value[row][col] - b->value[row][col];
            if(value>-FLT_MAX && value<FLT_MAX)
                result->value[row][col] = value;
            else
            {
                printf("Error - Overflow/Underflow! Returning an Identity Matrix.\n");
                SetIdentityMatrix(result);
                return;
            }
        }
}

/* Multiplies the values component-wise of a by b and writes to result */
void MultiplyMatrixComponent(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b)
{
    int row, col;
    double value;

    /* Check if Source is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Source is not NULL */
    if(b==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }
    
    /* Check if Target is not NULL */
    if(result==NULL)
    {
        printf("Error - Target Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==a)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==b)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Perform a Cell by Cell Copy */
    for(row=0; row<4; row++)
        for(col=0; col<4; col++)
        {
            value = a->value[row][col] * b->value[row][col];
            if(value>-FLT_MAX && value<FLT_MAX)
                result->value[row][col] = value;
            else
            {
                printf("Error - Overflow/Underflow! Returning an Identity Matrix.\n");
                SetIdentityMatrix(result);
                return;
            }
        }
}

/* Divides the values component-wise of a by b and writes to result */
void DivideMatrix(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b)
{
    int row, col;
    double value;

    /* Check if Source is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Source is not NULL */
    if(b==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }
    
    /* Check if Target is not NULL */
    if(result==NULL)
    {
        printf("Error - Target Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==a)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==b)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Perform a Cell by Cell Copy */
    for(row=0; row<4; row++)
        for(col=0; col<4; col++)
        {
            if(b->value[row][col]!=0)
            {
                value = a->value[row][col] / b->value[row][col];
                if(value>-FLT_MAX && value<FLT_MAX)
                    result->value[row][col] = value;
                else
                {
                    /* Return a Identity Matrix */
                    SetIdentityMatrix(result);
                    printf("Error - Overflow/Underflow! Returning an Identity Matrix.\n");
                    return;
                }
            }
            else
            {
                /* Return a Identity Matrix */
                SetIdentityMatrix(result);
                printf("Error - Divide by 0! (Resulting Matrix will be set to Identity)\n");
                return;
            }
        }
}

/* Scales the given matrix by scale given and writes to result */
void ScaleMatrix(struct Mat4x4* result, const struct Mat4x4* a, float scale)
{
    struct Mat4x4 matTransformation;

    /* Check if Source is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }
    
    /* Check if Target is not NULL */
    if(result==NULL)
    {
        printf("Error - Target Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==a)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Prepare Transformation Matrix as Identity Matrix and then SetScale to Scale */
    SetScaleMatrix(&matTransformation, scale);

    /* Prepare Target Matrix as Identity Matrix and then SetScale to Scale */
    MatrixMultiply(result, &matTransformation, a);
}

/* Matrix multiplication of a with b and writes to result */
void MatrixMultiply(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b)
{   
    /* Check if a is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if b is not NULL */
    if(b==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==a)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==b)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Check if result is not NULL */
    if(result!=NULL)
    {
        int row_a, col_a, b_counter;
        double value;
        for(row_a=0; row_a<4; row_a++)
            for(col_a=0; col_a<4; col_a++)
            {
                value = 0;
                for(b_counter=0; b_counter<4; b_counter++)
                    value += a->value[row_a][b_counter] * b->value[b_counter][col_a];
                
                if(value>-FLT_MAX && value<FLT_MAX)
                    result->value[row_a][col_a] = value;
                else
                {
                    /* Return a Identity Matrix */
                    SetIdentityMatrix(result);
                    printf("Error - Overflow/Underflow! Returning an Identity Matrix.\n");
                    return;
                }
            }
    }
    else
        printf("Error - Target Mat4x4 is not Initialised!\n");
}

/* Matrix multiplication of a with Vector b and writes to result */
void MatrixVecMultiply(struct Vec4* result, const struct Mat4x4* a, const struct Vec4* b)
{
    double value;

    /* Check if a is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return;
    }

    /* Check if b is not NULL */
    if(b==NULL)
    {
        printf("Error - Source Vec4 is not Initialised!\n");
        return;
    }

    /* Check if Parameters are the Same */
    if(result==b)
    {
        printf("Error - Source and Target is the Same!\n");
        return;
    }

    /* Check if result is not NULL */
    if(result!=NULL)
    {
        value = a->value[0][0] * b->x + a->value[0][1] * b->y + a->value[0][2] * b->z + a->value[0][3] * b->w;
        if(value>-FLT_MAX && value<FLT_MAX)
            result->x = value;
        else
        {
            printf("Error - Overflow/Underflow! Returning a 0 Vector.\n");
            SetVector(result, 0,0,0,0);
            return;
        }
        
        value = a->value[1][0] * b->x + a->value[1][1] * b->y + a->value[1][2] * b->z + a->value[1][3] * b->w;
        if(value>-FLT_MAX && value<FLT_MAX)
            result->y = value;
        else
        {
            printf("Error - Overflow/Underflow! Returning a 0 Vector.\n");
            SetVector(result, 0,0,0,0);
            return;
        }

        value = a->value[2][0] * b->x + a->value[2][1] * b->y + a->value[2][2] * b->z + a->value[2][3] * b->w;
        if(value>-FLT_MAX && value<FLT_MAX)
            result->z = value;
        else
        {
            printf("Error - Overflow/Underflow! Returning a 0 Vector.\n");
            SetVector(result, 0,0,0,0);
            return;
        }

        value = a->value[3][0] * b->x + a->value[3][1] * b->y + a->value[3][2] * b->z + a->value[3][3] * b->w;
        if(value>-FLT_MAX && value<FLT_MAX)
            result->w = value;
        else
        {
            printf("Error - Overflow/Underflow! Returning a 0 Vector.\n");
            SetVector(result, 0,0,0,0);
            return;
        }
    }
    else
        printf("Error - Target Vec4 is not Initialised!\n");
}

/* Gets the 3x3 matrix determinant using the Rule of Sarrus */
float Get3x3MatrixDeterminant(const struct Mat4x4* a)
{
    double determinant;

    /* Check if a is not NULL */
    if(a==NULL)
    {
        printf("Error - Source Mat4x4 is not Initialised!\n");
        return 0;
    }

    determinant = a->value[0][0] * (a->value[1][1]*a->value[2][2] - a->value[2][1]*a->value[1][2]) - a->value[0][1] * (a->value[1][0]*a->value[2][2]-a->value[2][0]*a->value[1][2]) + a->value[0][2] * (a->value[1][0]*a->value[2][1]-a->value[2][0]*a->value[1][1]);
    
    if(determinant==0)
        printf("Warning - Determinant is 0!\n");
    
    if(determinant>-FLT_MAX && determinant<FLT_MAX)
        return (float) determinant;
    else
    {
        printf("Error - Overflow! Value set to 0.\n");
        return (float) 0;
    }
}