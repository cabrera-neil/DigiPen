/******************************************************************************
filename main.c
author Kyaw Min Thein
email kyawmin.t@digipen.edu
date created 02 Jul 2019
Brief Description: StringNum
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "StringNum.h"

int main(void)
{
	char *b = NULL;
	/*char d[] = "abc23?-~fgz";*/
	char *e, *f;		
	char *dest, *source, *result;
	int length;	
	
	/*int StringLength(const char* s1)*/
	printf("Checking: int StringLength(const char* s1)\n");
	printf("Ans:5 Output:%d\n", StringLength("Hello"));
	printf("Ans:Print error for NULL input and return 0! Output:%d\n", StringLength(b));
	printf("Ans:0 Print error for NULL input and return 0! Output:%d\n", StringLength(""));
	printf("Ans:1 Output:%d\n", StringLength("h"));
	printf("\n\n");
	
	/*void StringToUpper(char* s1)*/
	printf("Checking: void StringToUpper(char* s1)\n");
	e = malloc(12*sizeof(char));
	strcpy(e,"abc23?-~fgz");
	StringToUpper(e);
	printf("Ans:ABC23?-!FGZ Output:%s\n", e);
	StringToUpper(b);
	printf("Ans:Print error for NULL input! Output:%s\n", b);
	f=malloc(sizeof(char));
	strcpy(f,"");
	StringToUpper(f);
	printf("Ans:Print error for NULL input! Output:%s\n", f);	
	printf("\n\n");
	
	/*StringToLower(char* s1)*/
	printf("Checking: void StringToLower(char* s1)\n");	
	StringToLower(e);
	printf("Ans:abc23?-~fgz Output:%s\n", e);
	StringToLower(b);
	printf("Ans:NULL Output:%s\n", b);
	StringToLower(f);
	printf("Ans:Print error for NULL input! Output:%s\n", f);	
	free(e);
	free(f);
	printf("\n\n");
	
	/*StringCopy(char* dest, const char* source, int length)*/
	printf("Checking: void StringCopy(char* dest, const char* source, int length)\n");
	/*source and dest are NULL*/
	source = NULL;
	dest = NULL;
	length = 3;
	StringCopy(dest,source,length);
	printf("Ans:Print error for NULL value input!\n");
	/*source is NULL and dest is not NULL*/
	source = NULL;
	length = 8;
	dest = malloc(length*sizeof(char));
	StringCopy(dest,source,length);
	printf("Ans:Print error for NULL value input!\n");
	free(dest);
	/*source is not null and dest is null*/
	source = malloc(50*sizeof(char));
	strcpy(source,"Hello World");
	length = 8;
	dest = NULL;	
	StringCopy(dest,source,length);
	printf("Ans:Print error for NULL value input!\n");
	/*Length is 0*/
	source = malloc(50*sizeof(char));
	strcpy(source,"Hello World");
	length = 0;
	dest = malloc(length*sizeof(char));
	StringCopy(dest,source,length);
	printf("Ans:Print error for length 0!\n");
	free(source);
	free(dest);		
	/*source and length the same*/
	source = malloc(50*sizeof(char));
	strcpy(source,"Hello World");
	length = 8;
	dest = malloc(length*sizeof(char));
	StringCopy(dest,source,length);
	printf("Ans:Hello W Output:%s\n",dest);
	free(source);
	free(dest);		
	/*source is less than length*/
	source = malloc(50*sizeof(char));
	strcpy(source,"Hello");
	length = 7;
	dest = malloc(length*sizeof(char));
	StringCopy(dest,source,length);
	printf("Ans:Hello Output:%s\n",dest);
	free(dest);
	free(source);	
	/*source is more than length*/
	source = malloc(50*sizeof(char));
	strcpy(source,"Hello World");	
	length = 4;
	dest = malloc(length*sizeof(char));
	StringCopy(dest,source,length);
	printf("Ans:Hel Output:%s\n",dest);
	free(dest);
	free(source);	
	/*source and dest have the same address*/	
	source = malloc(50*sizeof(char));
	strcpy(source,"Hello World");
	dest = source;	
	length = 5;	
	StringCopy(dest,source,length);
	printf("Ans:Need to print warning error for same address!\n");
	free(dest);	
	/*source and dest have memory overlapping*/
	dest = source+6;
	printf("source before copying: %s\n",source);
	StringCopy(dest,source,3);
	printf("After copying dest, Ans:He output:%s\n",dest);
	printf("source after copying: %s\n",source);
	printf("Ans:Need to print warning error for memory overlapping*/!\n");	
	printf("\n\n");
	
	/*int StringIsEqual(const char* s1, const char* s2)*/
	printf("Checking: int StringIsEqual(const char* s1, const char* s2)\n");
	printf("Ans:Print error for NULL value input and return 0 Output:%d!\n",StringIsEqual("",""));
	printf("Ans:Print error for NULL value input and return 0 Output:%d!\n",StringIsEqual("Hello",""));
	printf("Ans:Print error for NULL value input and return 0 Output:%d!\n",StringIsEqual("","Hello"));
	printf("Ans:0 Output:%d\n",StringIsEqual("Hello","Hello "));
	printf("Ans:0 Output:%d\n",StringIsEqual("Hello","Hell"));
	printf("Ans:0 Output:%d\n",StringIsEqual(" Hello","Hell0"));	
	printf("Ans:1 Output:%d\n",StringIsEqual("Hello World","Hello World"));	
	printf("\n\n");
	
	/*int StringFind(const char* target, const char* value)*/
	printf("Checking: int StringFind(const char* target, const char* value)\n");
	printf("Ans:Print error for NULL value input and return 0 Output:%d!\n",StringFind("",""));
	printf("Ans:Print error for NULL value input and return 0 Output:%d!\n",StringFind("Hello",""));
	printf("Ans:Print error for NULL value input and return 0 Output:%d!\n",StringFind("","Hello"));	
	printf("Ans:0 Output:%d\n",StringFind("Hello","lloo"));
	printf("Ans:0 Output:%d\n",StringFind("Hello","Helo"));	
	printf("Ans:1 Output:%d\n",StringFind("Hello","Hello"));
	printf("Ans:1 Output:%d\n",StringFind("Hello","Hell"));
	printf("Ans:1 Output:%d\n",StringFind("Hello","ll"));
	printf("Ans:1 Output:%d\n",StringFind("Hello","lo"));
	printf("Ans:1 Output:%d\n",StringFind("Hello","o"));
	printf("Ans:1 Output:%d\n",StringFind("I am home","m h"));
	printf("\n\n");
	
	/*int StringContains(const char* target, const char* values)*/
	printf("Checking: int StringContains(const char* target, const char* values)\n");
	printf("Ans:Print error for NULL value input and return 0! Output:%d!\n",StringContains("",""));
	printf("Ans:Print error for NULL value input and return 0! Output:%d!\n",StringContains("Hello",""));
	printf("Ans:Print error for NULL value input and return 0! Output:%d!\n",StringContains("","Hello"));
	printf("Ans:Print error for NULL value input and return 0! Output:%d\n",StringContains("","\0"));	
	printf("Ans:0 Output:%d\n",StringContains("Hello","skd"));	
	printf("Ans:1 Output:%d\n",StringContains("Hello","e"));
	printf("Ans:1 Output:%d\n",StringContains("Hello","ao"));
	printf("Ans:1 Output:%d\n",StringContains("Hello","l"));
	printf("\n\n");
	
	/*int ArrayToInt(const char* input)*/
	printf("Checking: int ArrayToInt(const char* input)\n");
	printf("Ans:Print error for NULL value input and return 0! Output:%d\n",ArrayToInt(""));
	printf("Ans:Print error and return 0! Output:%d\n",ArrayToInt("/1234:"));	
	printf("Ans:1234 Output:%d\n",ArrayToInt("1234/abc"));
	printf("Ans:10 Output:%d\n",ArrayToInt("10:5"));
	printf("\n\n");
	
	/*void IntToString(char* result, int input, int limit)*/
	printf("Checking: void IntToString(char* result, int input, int limit)\n");
	/*result is null*/
	result=NULL;
	IntToString(result, 123456, 6);
	printf("Ans:Print error for NULL value input! Output:%s\n",result);	
	
	result = malloc(10*sizeof(char));	
	IntToString(result, 12345, 6);
	printf("Ans:12345 Output:%s\n",result);
	free(result);
		
	return 0;
}