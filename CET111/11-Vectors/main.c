#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Vector.h"

/* Implement error checking for all divide by 0 */

int main()
{
    struct Vec4* vA = NULL;
    struct Vec4* vB = NULL;
    struct Vec4* vCP = NULL;
    struct Vec4* nvA = NULL;
    struct Vec4* nvB = NULL;
    struct Vec4* svA = NULL;
    struct Vec4* rvB = NULL;

    vA = malloc(sizeof(struct Vec4));
    vB = malloc(sizeof(struct Vec4));

    SetVector(vA, 1,-6,5,0);
    CopyVector(vB, vA);
    
    PrintVector(vA);
    PrintVector(vB);
    
    vCP = malloc(sizeof(struct Vec4));

    VectorCrossProduct(vCP, vA, vB);
    printf("Cross Vector Product is: (%f, %f, %f, %f)\n", vCP->x, vCP->y, vCP->z, vCP->w);

    printf("Vector Dot Product is: %f\n", VectorDotProduct(vA, vB));
    
    nvA = malloc(sizeof(struct Vec4));
    NormalizeVector(nvA, vA);
    printf("Normalized vA: ");
    PrintVector(nvA);

    
    nvB = malloc(sizeof(struct Vec4));
    NormalizeVector(nvB, vB);
    printf("Normalized vB: ");
    PrintVector(nvB);

    printf("Max for Vector is: %f\n", GetVectorMax(vA));
    printf("Max for Vector is: %f\n", GetVectorMax(vB));

    printf("Min for Vector is: %f\n", GetVectorMin(vA));
    printf("Min for Vector is: %f\n", GetVectorMin(vB));

    printf("Vector Length: %f\n", GetVectorLength(vA));
    printf("Vector Length: %f\n", GetVectorLength(vB));

    
    svA = malloc(sizeof(struct Vec4));
    ScaleVector(svA, vA, 369);
    
    rvB = malloc(sizeof(struct Vec4));

    AddVector(rvB, vA, vB);
    PrintVector(rvB);

    SubtractVector(rvB, vA, vB);
    PrintVector(rvB);

    MultiplyVector(rvB, vA, vB);
    PrintVector(rvB);

    DivideVector(rvB, vA, vB);
    PrintVector(rvB);

    /* ************************ */
    SetVector(NULL, 1,-6,5,0);
    
    PrintVector(vA);
    PrintVector(vB);
    
    vCP = malloc(sizeof(struct Vec4));

    VectorCrossProduct(vCP, vA, NULL);
    VectorCrossProduct(vCP, NULL, vB);
    VectorCrossProduct(NULL, vA, vB);
    VectorCrossProduct(vCP, vA, vB);
    printf("Cross Vector Product is: (%f, %f, %f, %f)\n", vCP->x, vCP->y, vCP->z, vCP->w);

    printf("Vector Dot Product is: %f\n", VectorDotProduct(vA, vB));
    
    nvA = malloc(sizeof(struct Vec4));
    NormalizeVector(nvA, NULL);
    NormalizeVector(NULL, vA);
    NormalizeVector(nvA, vA);
    printf("Normalized vA: ");
    PrintVector(nvA);PrintVector(NULL);

    
    nvB = malloc(sizeof(struct Vec4));
    NormalizeVector(nvB, vB);
    printf("Normalized vB: ");
    PrintVector(nvB);

    printf("Max for Vector is: %f\n", GetVectorMax(vA));
    printf("Max for Vector is: %f\n", GetVectorMax(NULL));
    printf("Max for Vector is: %f\n", GetVectorMax(vB));
    printf("Max for Vector is: %f\n", GetVectorMax(NULL));

    printf("Min for Vector is: %f\n", GetVectorMin(vA));
    printf("Min for Vector is: %f\n", GetVectorMin(NULL));
    printf("Min for Vector is: %f\n", GetVectorMin(vB));
    printf("Min for Vector is: %f\n", GetVectorMin(NULL));

    printf("Vector Length: %f\n", GetVectorLength(vA));
    printf("Vector Length: %f\n", GetVectorLength(vB));
    printf("Vector Length: %f\n", GetVectorLength(NULL));
    printf("Vector Length: %f\n", GetVectorLength(NULL));

    
    svA = malloc(sizeof(struct Vec4));
    ScaleVector(svA, vA, 369);
    
    rvB = malloc(sizeof(struct Vec4));

    AddVector(rvB, vA, vB);
    PrintVector(rvB);

    SubtractVector(rvB, vA, vB);
    PrintVector(rvB);

    MultiplyVector(rvB, vA, vB);
    PrintVector(rvB);

    DivideVector(rvB, vA, vB);
    PrintVector(rvB);

    return 0;
}