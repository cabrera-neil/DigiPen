/******************************************************************************
filename Vector.h
author Howard Sin
email howard.sin@digipen.edu
date created 22 May 2019
Brief Description: A header file containing Vec4 struct and Vector Functions
******************************************************************************/
#ifndef VECTOR_H
#define VECTOR_H

struct Vec4
{
	float x, y, z, w;
};

/* Prints the vector given in the following format: vec4(x,y,z,w) */
void PrintVector(const struct Vec4* a);

/* Sets the values in the given vector */
void SetVector(struct Vec4* result, float x, float y, float z, float w);

/* Copies the values from a to result */
void CopyVector(struct Vec4* result, const struct Vec4* a);

/* Adds the values in vector a and b and write to result */
void AddVector(struct Vec4* result, const struct Vec4* a, const struct Vec4* b);

/* Subtracts the values of a by b and write to result */
void SubtractVector(struct Vec4* result, const struct Vec4* a, const struct Vec4* b);

/* Multiplies the values of a by b and write to result */
void MultiplyVector(struct Vec4* result, const struct Vec4* a, const struct Vec4* b);

/* Divides the values of a by b and write to result */
void DivideVector(struct Vec4* result, const struct Vec4* a, const struct Vec4* b);

/* Normalizes the given vector a and write to result */
void NormalizeVector(struct Vec4* result, const struct Vec4* a);

/* Scale vector a by scale and write to result */
void ScaleVector(struct Vec4* result, const struct Vec4* a, float scale);

/* Compute the squared length of given vector a */
float GetVectorSquaredLength(const struct Vec4* a);

/* Compute the length of given vector a */
float GetVectorLength(const struct Vec4* a);

/* Compute the dot product of vectors a and b */
float VectorDotProduct(const struct Vec4* a, const struct Vec4* b);

/* Compute the cross product of vectors a x b and write to result */
void VectorCrossProduct(struct Vec4* result, const struct Vec4* a, const struct Vec4* b);

/* Find the largest value among components in given vector a */
float GetVectorMax(const struct Vec4* a);

/* Find the smallest value among components in given vector a */
float GetVectorMin(const struct Vec4* a);

#endif /* VECTOR_H */
/*****************************************************************************/