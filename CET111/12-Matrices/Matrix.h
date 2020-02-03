/******************************************************************************
filename Matrix.h
author Howard Sin
email howard.sin@digipen.edu
date created 22 May 2019
Brief Description: A header file containing Mat4x4 struct and Matrix Functions
******************************************************************************/
#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector.h"

struct Mat4x4
{
	float value[4][4];
};

/* Prints the matrix as such: mat4x4(0,1,2...,15) */
void PrintMatrix(const struct Mat4x4* a);

/* Sets the given matrix to identity */
void SetIdentityMatrix(struct Mat4x4* result);

/* Sets the given matrix to a scaling matrix of scaling factor given */
void SetScaleMatrix(struct Mat4x4* result, float scalingFactor);

/* Sets the given matrix to a rotation along X axis by degree given */
void SetRotateXMatrix(struct Mat4x4* result, float degree);

/* Sets the given matrix to a rotation along Y axis by degree given */
void SetRotateYMatrix(struct Mat4x4* result, float degree);

/* Sets the given matrix to a rotation along Z axis by degree given */
void SetRotateZMatrix(struct Mat4x4* result, float degree);

/* Sets the given matrix to a translation matrix by offsets x,y,z given */
void SetTranslateMatrix(struct Mat4x4* result, float x, float y, float z);

/* Transpose the given matrix and writes to result */
void TransposeMatrix(struct Mat4x4* result, const struct Mat4x4* a);

/* Sets the result matrix to the special inverse of the given rotate & translate matrix */
void SetRotateTranslateInverse(struct Mat4x4* result, const struct Mat4x4* a);

/* Sets the given row of the matrix to the given x,y,z,w values provided */
void SetMatrixRow(struct Mat4x4* result, int rowIndex, float x, float y, float z, float w);

/* Sets the given column of the matrix to the given x,y,z,w values provided */
void SetMatrixColumn(struct Mat4x4* result, int colIndex, float x, float y, float z, float w);

/* Copies the given matrix a values to the result */
void CopyMatrix(struct Mat4x4* result, const struct Mat4x4* a);

/* Adds the values component-wise from a and b and writes to result */
void AddMatrix(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b);

/* Subtracts the values component-wise of a by b and writes to result */
void SubtractMatrix(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b);

/* Multiplies the values component-wise of a by b and writes to result */
void MultiplyMatrixComponent(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b);

/* Divides the values component-wise of a by b and writes to result */
void DivideMatrix(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b);

/* Scales the given matrix by scale given and writes to result */
void ScaleMatrix(struct Mat4x4* result, const struct Mat4x4* a, float scale);

/* Matrix multiplication of a with b and writes to result */
void MatrixMultiply(struct Mat4x4* result, const struct Mat4x4* a, const struct Mat4x4* b);

/* Matrix multiplication of a with Vector b and writes to result */
void MatrixVecMultiply(struct Vec4* result, const struct Mat4x4* a, const struct Vec4* b);

/* Gets the 3x3 matrix determinant using the Rule of Sarrus */
float Get3x3MatrixDeterminant(const struct Mat4x4* a);

#endif /* MATRIX4X4_H */
/*****************************************************************************/
