/******************************************************************************
Filename: DiamondPrint.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 28 May 2019
Brief Description: Create diamond pattern in the console
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]) 
{ 
    /* Check if there are no parameters passed to the program */
    if(argc==1) 
        printf("\nInvalid usage: %s.exe - Missing Parameter!", argv[0]);
    else
    {
        /* Program will only execute if there is exactly 1 parameter supplied */
        if(argc==2) 
        { 
            int input = atoi(argv[1]);

            if(input>0)
            {
                int row, space, col;
                /* Draw the upper diamond */
                for (row=1; row<=input; row++)
                {
                    for (space=input-row; space>=1; space--)
                        printf(" ");

                    for (col=1; col<=2*row-1; col++)
                    {
                        if (col<=row)
                            printf("%d", col%10);
                        else
                            printf("%d", (2*row-col)%10);
                    }
                    printf("\n");
                }

                /* Draw the lower diamond */
                for (row=input-1; row>=1; row--)
                {
                    for (space=1; space<=input-row; space++)
                        printf(" ");

                    for (col=1; col<=2*row-1; col++)
                    {
                        if (col<=row)
                            printf("%d", col%10);
                        else
                            printf("%d", (2*row-col)%10);
                    }
                    printf("\n");
                }
            }
            else /* Program does not accept less than 1 dimension */
                printf("\nInvalid usage: %s.exe - Diamond dimension cannot be less than 1!", argv[0]);
        }
        else /* Program accepts only 1 parameter */
            printf("\nInvalid usage: %s.exe - Too many parameters! Program expects only 1.", argv[0]);
    }
    return 0; 
}  