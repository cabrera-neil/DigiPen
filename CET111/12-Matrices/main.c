#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "Matrix.h"

int main (void)
{
	float s;
	struct Mat4x4 *a, *b, *result;
	struct Vec4 *c, *vecResult;
	int i,j,k;

	a = malloc(sizeof(struct Mat4x4));
	b = malloc(sizeof(struct Mat4x4));
	c = malloc(sizeof(struct Vec4));
	vecResult = malloc(sizeof(struct Vec4));

	result = malloc(sizeof(struct Mat4x4));

	SetVector(c, 4, 5, 6, 1);

	k=1;
	for (i=0;i<4;++i)
	{
		for (j=0;j<4;++j)
		{
			a->value[i][j]=k++;
		}
	}

	k=1;
	for (i=0;i<4;++i)
	{
		for (j=0;j<4;++j)
		{
			b->value[i][j]=2*k++;
		}
	}

	PrintMatrix(a);

	printf("\nSetIdentityMatrix\n");
	SetIdentityMatrix(result);
	PrintMatrix(result);

	printf("\nSetScaleMatrix by 3\n");
	SetScaleMatrix(result, 3);
	PrintMatrix(result);

	printf("\nSetRotateXMatrix\n");
	SetRotateXMatrix(result, 90);
	PrintMatrix(result);

	printf("\nSetRotateYMatrix\n");
	SetRotateYMatrix(result, 90);
	PrintMatrix(result);

	printf("\nSetRotateZMatrix\n");
	SetRotateZMatrix(result, 90);
	PrintMatrix(result);

	printf("\nSetTranslateMatrix\n");
	SetTranslateMatrix(result, 2, 3, 4);
	PrintMatrix(result);

	printf("\nTransposeMatrix\n");
	TransposeMatrix(result, a);
	PrintMatrix(result);

	printf("\nSetMatrixRow\n");
	SetMatrixRow(result, 3, 5, 5, 5, 5);
	PrintMatrix(result);

	printf("\nSetMatrixColumn\n");
	SetMatrixColumn(result, 3, 8, 8, 8, 8);
	PrintMatrix(result);

	printf("\nCopyMatrix\n");
	CopyMatrix(result,a);
	PrintMatrix(result);

	printf("\nAddMatrix\n");
	AddMatrix(result,a,b);
	PrintMatrix(result);

	printf("\nSubtractMatrix\n");
	SubtractMatrix(result,a,b);
	PrintMatrix(result);

	printf("\nMultiplyMatrixComponent\n");
	MultiplyMatrixComponent(result,a,b);
	PrintMatrix(result);

	printf("\nDivideMatrix\n");
	DivideMatrix(result,a,b);
	PrintMatrix(result);

	printf("\nMatrixMultiply\n");
	MatrixMultiply(result,a,b);
	PrintMatrix(result);

	printf("\nScaleMatrix\n");
	ScaleMatrix(result,a,3);
	PrintMatrix(result);

	printf("\nMatrixVecMultiply\n");
	MatrixVecMultiply(vecResult,a,c);
	printf("%f %f %f %f\n",vecResult->x,vecResult->y,vecResult->z,vecResult->w);

	printf("\nGet3x3MatrixDeterminant\n");
	a->value[2][2]=5;
	PrintMatrix(a);
	printf("Det 3x3 of a is %f\n", Get3x3MatrixDeterminant(a));

	printf("\nSetRotateTranslateInverse\n");
	SetRotateTranslateInverse(result,a);
	PrintMatrix(result);

	printf("\n\n\nTESTING OVERFLOWS!\n");
	k=1;
	for (i=0;i<4;++i)
	{
		for (j=0;j<4;++j)
		{
			a->value[i][j]=FLT_MAX;
		}
	}

	k=1;
	for (i=0;i<4;++i)
	{
		for (j=0;j<4;++j)
		{
			b->value[i][j]=FLT_MIN;
		}
	}

	PrintMatrix(a);

	printf("\nSetIdentityMatrix\n");
	SetIdentityMatrix(result);
	PrintMatrix(result);

	printf("\nSetScaleMatrix by 3\n");
	SetScaleMatrix(result, 3);
	PrintMatrix(result);

	printf("\nSetRotateXMatrix\n");
	SetRotateXMatrix(result, 90);
	PrintMatrix(result);

	printf("\nSetRotateYMatrix\n");
	SetRotateYMatrix(result, 90);
	PrintMatrix(result);

	printf("\nSetRotateZMatrix\n");
	SetRotateZMatrix(result, 90);
	PrintMatrix(result);

	printf("\nSetTranslateMatrix\n");
	SetTranslateMatrix(result, 2, 3, 4);
	PrintMatrix(result);

	printf("\nTransposeMatrix\n");
	TransposeMatrix(result, a);
	PrintMatrix(result);

	printf("\nSetMatrixRow\n");
	SetMatrixRow(result, 3, 5, 5, 5, 5);
	PrintMatrix(result);

	printf("\nSetMatrixColumn\n");
	SetMatrixColumn(result, 3, 8, 8, 8, 8);
	PrintMatrix(result);

	printf("\nCopyMatrix\n");
	CopyMatrix(result,a);
	PrintMatrix(result);

	printf("\nAddMatrix\n");
	AddMatrix(result,a,b);
	PrintMatrix(result);

	printf("\nSubtractMatrix\n");
	SubtractMatrix(result,a,b);
	PrintMatrix(result);

	printf("\nMultiplyMatrixComponent\n");
	MultiplyMatrixComponent(result,a,b);
	PrintMatrix(result);

	printf("\nDivideMatrix\n");
	DivideMatrix(result,a,b);
	PrintMatrix(result);

	printf("\nMatrixMultiply\n");
	MatrixMultiply(result,a,b);
	PrintMatrix(result);

	printf("\nScaleMatrix\n");
	ScaleMatrix(result,a,3);
	PrintMatrix(result);

	printf("\nMatrixVecMultiply\n");
	MatrixVecMultiply(vecResult,a,c);
	printf("%f %f %f %f\n",vecResult->x,vecResult->y,vecResult->z,vecResult->w);

	printf("\nGet3x3MatrixDeterminant\n");
	a->value[2][2]=5;
	PrintMatrix(a);
	printf("Det 3x3 of a is %f\n", Get3x3MatrixDeterminant(a));

	printf("\nSetRotateTranslateInverse\n");
	SetRotateTranslateInverse(result,a);
	PrintMatrix(result);

	result = a;

	PrintMatrix(a);

	printf("\nSetIdentityMatrix\n");
	SetIdentityMatrix(result);
	PrintMatrix(result);

	printf("\nSetScaleMatrix by 3\n");
	SetScaleMatrix(result, 3);
	PrintMatrix(result);

	printf("\nSetRotateXMatrix\n");
	SetRotateXMatrix(result, 90);
	PrintMatrix(result);

	printf("\nSetRotateYMatrix\n");
	SetRotateYMatrix(result, 90);
	PrintMatrix(result);

	printf("\nSetRotateZMatrix\n");
	SetRotateZMatrix(result, 90);
	PrintMatrix(result);

	printf("\nSetTranslateMatrix\n");
	SetTranslateMatrix(result, 2, 3, 4);
	PrintMatrix(result);

	printf("\nTransposeMatrix\n");
	TransposeMatrix(result, a);
	PrintMatrix(result);

	printf("\nSetMatrixRow\n");
	SetMatrixRow(result, 3, 5, 5, 5, 5);
	PrintMatrix(result);

	printf("\nSetMatrixColumn\n");
	SetMatrixColumn(result, 3, 8, 8, 8, 8);
	PrintMatrix(result);

	printf("\nCopyMatrix\n");
	CopyMatrix(result,a);
	PrintMatrix(result);

	printf("\nAddMatrix\n");
	AddMatrix(result,a,b);
	PrintMatrix(result);

	printf("\nSubtractMatrix\n");
	SubtractMatrix(result,a,b);
	PrintMatrix(result);

	printf("\nMultiplyMatrixComponent\n");
	MultiplyMatrixComponent(result,a,b);
	PrintMatrix(result);

	printf("\nDivideMatrix\n");
	DivideMatrix(result,a,b);
	PrintMatrix(result);

	printf("\nMatrixMultiply\n");
	MatrixMultiply(result,a,b);
	PrintMatrix(result);

	printf("\nScaleMatrix\n");
	ScaleMatrix(result,a,3);
	PrintMatrix(result);

	printf("\nMatrixVecMultiply\n");
	MatrixVecMultiply(vecResult,a,c);
	printf("%f %f %f %f\n",vecResult->x,vecResult->y,vecResult->z,vecResult->w);

	printf("\nGet3x3MatrixDeterminant\n");
	a->value[2][2]=5;
	PrintMatrix(a);
	printf("Det 3x3 of a is %f\n", Get3x3MatrixDeterminant(a));

	printf("\nSetRotateTranslateInverse\n");
	SetRotateTranslateInverse(result,a);
	PrintMatrix(result);

	SetScaleMatrix(result,1000000000000000000000000000000000000.0);
	PrintMatrix(result);

	s=(long double)(1000000000000000000000000000000000000.0 * 1);
	printf("%Lf\n", (long double)(340282346638528859811704183484516925440.000000));
	printf("%Lf\n", (long double)s - (long double)(1000000000000000000000000000000000000.0 * 1));

	s=FLT_MAX;
	printf("%f\n", s);

	return 0;
}