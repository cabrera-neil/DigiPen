#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSVParser.h"

int main (int argc, char* argv[])
{
    long rCount=0, cCount=0;
    
    struct CSVData* csvFile;
    struct CSVData* csvFile3;
    struct CSVData csvFile4;
    struct CSVData csvFile5;
    struct CSVData* csvFile6;

    /* Get rid of the warning */
    rCount = argc - argc;

    /* TEST1 - CLEAN CSVDATA AND FREE */
    printf("Test1.............................................................\n");
    csvFile = calloc(1,sizeof(struct CSVData));

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(csvFile, argv[1]);
    for(rCount=0; rCount<csvFile->size; rCount++)
    {
        for(cCount=0; cCount<csvFile->rowData[rCount].size; cCount++)
            if(csvFile->rowData[rCount].colData[cCount][0] != '\0')
                printf("%s ",csvFile->rowData[rCount].colData[cCount]);
            else
                printf("(null)");
        
        printf("\n");
    }

    /* Print using Get Entry */
    for(rCount=0; rCount<csvFile->size; rCount++)
    {
        for(cCount=0; cCount<csvFile->rowData[rCount].size; cCount++)
            printf("%s ",GetEntry(csvFile, rCount, cCount));
        
        printf("\n");
    }

    FreeCSVData(csvFile);

    /* TEST2 - USED CSVDATA (BUT FREED INITIALLY) */
    printf("Test2.............................................................\n");
    rCount=0, cCount=0;

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(csvFile, argv[2]);
    for(rCount=0; rCount<csvFile->size; rCount++)
    {
        for(cCount=0; cCount<csvFile->rowData[rCount].size; cCount++)
            if(csvFile->rowData[rCount].colData[cCount][0] != '\0')
                printf("%s ",csvFile->rowData[rCount].colData[cCount]);
            else
                printf("(null)");
        
        printf("\n");
    }

    FreeCSVData(csvFile);

    /* TEST3 - CLEAN CSVDATA and REUSE WITHOUT FREE, ONLY FREE AT THE END */
    printf("Test3.............................................................\n");
    rCount=0, cCount=0;
    csvFile3 = calloc(1,sizeof(struct CSVData));

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(csvFile3, argv[1]);
    for(rCount=0; rCount<csvFile3->size; rCount++)
    {
        for(cCount=0; cCount<csvFile3->rowData[rCount].size; cCount++)
            if(csvFile3->rowData[rCount].colData[cCount][0] != '\0')
                printf("%s ",csvFile3->rowData[rCount].colData[cCount]);
            else
                printf("(null)");
        
        printf("\n");
    }

    /* Print using Get Entry */
    for(rCount=0; rCount<csvFile3->size; rCount++)
    {
        for(cCount=0; cCount<csvFile3->rowData[rCount].size; cCount++)
            printf("%s ",GetEntry(csvFile3, rCount, cCount));
        
        printf("\n");
    }

    rCount=0, cCount=0;

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(csvFile3, argv[2]);
    for(rCount=0; rCount<csvFile3->size; rCount++)
    {
        for(cCount=0; cCount<csvFile3->rowData[rCount].size; cCount++)
            if(csvFile3->rowData[rCount].colData[cCount][0] != '\0')
                printf("%s ",csvFile3->rowData[rCount].colData[cCount]);
            else
                printf("(null)");
        
        printf("\n");
    }

    /* Print using Get Entry */
    for(rCount=0; rCount<csvFile3->size; rCount++)
    {
        for(cCount=0; cCount<csvFile3->rowData[rCount].size; cCount++)
            printf("%s ",GetEntry(csvFile3, rCount, cCount));
        
        printf("\n");
    }

    FreeCSVData(csvFile3);

    /* TEST4 - STATIC CSVDATA and CLEAN */
    printf("Test4.............................................................\n");
    rCount=0, cCount=0;
    
    csvFile4.size = 0;
    csvFile4.rowData = NULL;

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(&csvFile4, argv[1]);
    for(rCount=0; rCount<csvFile4.size; rCount++)
    {
        for(cCount=0; cCount<csvFile4.rowData[rCount].size; cCount++)
            if(csvFile4.rowData[rCount].colData[cCount][0] != '\0')
                printf("%s ",csvFile4.rowData[rCount].colData[cCount]);
            else
                printf("(null)");
        
        printf("\n");
    }

    /* Print using Get Entry */
    for(rCount=0; rCount<csvFile4.size; rCount++)
    {
        for(cCount=0; cCount<csvFile4.rowData[rCount].size; cCount++)
            printf("%s ",GetEntry(&csvFile4, rCount, cCount));
        
        printf("\n");
    }

    rCount=0, cCount=0;

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(&csvFile4, argv[2]);
    for(rCount=0; rCount<csvFile4.size; rCount++)
    {
        for(cCount=0; cCount<csvFile4.rowData[rCount].size; cCount++)
            if(csvFile4.rowData[rCount].colData[cCount][0] != '\0')
                printf("%s ",csvFile4.rowData[rCount].colData[cCount]);
            else
                printf("(null)");
        
        printf("\n");
    }

    /* Print using Get Entry */
    for(rCount=0; rCount<csvFile4.size; rCount++)
    {
        for(cCount=0; cCount<csvFile4.rowData[rCount].size; cCount++)
            printf("%s ",GetEntry(&csvFile4, rCount, cCount));
        
        printf("\n");
    }

    FreeCSVData(&csvFile4);

    /* TEST5 - STATIC CSVDATA and DIRTY */
    printf("Test5.............................................................\n");
    rCount=0, cCount=0;
    
    csvFile5.size = 0;
    csvFile5.rowData = NULL;

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(&csvFile5, argv[1]);
    for(rCount=0; rCount<csvFile5.size; rCount++)
    {
        for(cCount=0; cCount<csvFile5.rowData[rCount].size; cCount++)
            if(csvFile5.rowData[rCount].colData[cCount][0] != '\0')
                printf("%s ",csvFile5.rowData[rCount].colData[cCount]);
            else
                printf("(null)");
        
        printf("\n");
    }

    /* Print using Get Entry */
    for(rCount=0; rCount<csvFile5.size; rCount++)
    {
        for(cCount=0; cCount<csvFile5.rowData[rCount].size; cCount++)
            printf("%s ",GetEntry(&csvFile5, rCount, cCount));
        
        printf("\n");
    }

    rCount=0, cCount=0;

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(&csvFile5, argv[2]);
    for(rCount=0; rCount<csvFile5.size; rCount++)
    {
        for(cCount=0; cCount<csvFile5.rowData[rCount].size; cCount++)
            if(csvFile5.rowData[rCount].colData[cCount][0] != '\0')
                printf("%s ",csvFile5.rowData[rCount].colData[cCount]);
            else
                printf("(null)");
        
        printf("\n");
    }

    /* Print using Get Entry */
    for(rCount=0; rCount<csvFile5.size; rCount++)
    {
        for(cCount=0; cCount<csvFile5.rowData[rCount].size; cCount++)
            printf("%s ",GetEntry(&csvFile5, rCount, cCount));
        
        printf("\n");
    }

    FreeCSVData(&csvFile5);

    /* TEST6 - MALLOC CSVDATA and DIRTY */
    printf("Test6.............................................................\n");
    rCount=0, cCount=0;
    
    csvFile6 = malloc(sizeof(struct CSVData));

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(csvFile6, argv[1]); /* ERROR TEST and INFINITE LOOP */
    /* Print using Get Entry */
    /* for(rCount=0; rCount<csvFile6->size; rCount++)
    {
        for(cCount=0; cCount<csvFile6->rowData[rCount].size; cCount++)
            printf("%s ",GetEntry(csvFile6, rCount, cCount));
        
        printf("\n");
    }*/

    /* Read and Print by Accessing Individual Cells */
    ReadCSVFile(csvFile6, argv[2]);  /* ERROR TEST and INFINITE LOOP */
    /* Print using Get Entry */
    /* for(rCount=0; rCount<csvFile6->size; rCount++)
    {
        for(cCount=0; cCount<csvFile6->rowData[rCount].size; cCount++)
            printf("%s ",GetEntry(csvFile6, rCount, cCount));
        
        printf("\n");
    } */

    FreeCSVData(csvFile6);
    return 0;
}