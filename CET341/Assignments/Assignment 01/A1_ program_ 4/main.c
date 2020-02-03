//; Assignment 1 File
//; Assembly File for Question 12d
//; Title: Odd_Event_Sort Implementation
//; Date: 13-Sep 2019
//; Author: Neil Cabrera

#include <stdlib.h>

typedef unsigned int T;

#define P_SIZE 10

#define DATA00 65537
#define DATA01 45
#define DATA02 0
#define DATA03 800000
#define DATA04 16
#define DATA05 230
#define DATA06 65536
#define DATA07 175
#define DATA08 65535
#define DATA09 1000

extern void odd_even_sort(T a[] , unsigned int n);

int main(void)
{
	//	; NOTE: Set Breakpoint at the next line to demonstrate
	T data[] = {DATA00, DATA01, DATA02, DATA03, DATA04, DATA05, DATA06, DATA07, DATA08, DATA09};

	// Please implement the odd_even_sort() function in ARM assembly.
	odd_even_sort(data,P_SIZE);

  while (1)
  {    
		__nop();
		__nop();
		__nop();
  }
}
