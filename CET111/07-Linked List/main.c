#include <stdlib.h>
#include <stdio.h>
#include "List.h"

int main(void)
{
    struct Node* nodeHead = NULL;

    /* Add */    
    InsertAt(&nodeHead, "1", 0);
    printf("%d\n", Count(nodeHead));
    FreeList(&nodeHead);
    printf("%d\n", Count(nodeHead));

    EraseNode(&nodeHead, 0);
    EraseNode(&nodeHead, 10);
    EraseNode(&nodeHead, -1);
    EraseValue(&nodeHead, "");
    EraseValue(&nodeHead, NULL);
    InsertAt(&nodeHead, NULL, 0);

    InsertAt(&nodeHead, "5", 0);

    AddToFront(&nodeHead, NULL);
    AddToFront(&nodeHead, NULL);
    AddToFront(&nodeHead, "");
    AddToFront(&nodeHead, "sdasdasdc");
    AddToFront(&nodeHead, "d");
    AddToFront(&nodeHead, "e");
    AddToFront(&nodeHead, "xvxcvxvxcvf");
    AddToFront(&nodeHead, "g");
    AddToFront(&nodeHead, "h");
    PrintList(nodeHead);
    
    /* Reverse after Add */
    ReverseList(&nodeHead);
    PrintList(nodeHead);

    /* Double Free */
    FreeList(&nodeHead);
    FreeList(&nodeHead);
    PrintList(nodeHead);

    /* Front and End */
    AddToFront(&nodeHead, "1");
    AddToEnd(&nodeHead, "2");
    AddToFront(&nodeHead, "3");
    AddToEnd(&nodeHead, "1");
    AddToFront(&nodeHead, "5");
    AddToEnd(&nodeHead, "6");
    AddToFront(&nodeHead, "7");
    AddToEnd(&nodeHead, "6");
    PrintList(nodeHead);

    /* Erase By Node */
    EraseValue(&nodeHead, NULL);
    PrintList(nodeHead);
    EraseValue(&nodeHead, "9");
    PrintList(nodeHead);
    EraseValue(&nodeHead, "11");
    PrintList(nodeHead);
    EraseValue(&nodeHead, "61");
    PrintList(nodeHead);

    EraseNode(&nodeHead, 0);
    EraseNode(&nodeHead, 1);
    EraseNode(&nodeHead, 0);

    EraseNode(&nodeHead, 1);
    PrintList(nodeHead);

    EraseNode(&nodeHead, 5);
    PrintList(nodeHead);

    FreeList(&nodeHead);
    FreeList(&nodeHead);

    InsertAt(&nodeHead, "5", 1);
    PrintList(nodeHead);

    InsertAt(&nodeHead, "5", 0);
    PrintList(nodeHead);

    InsertAt(&nodeHead, "7", 0);
    AddToFront(&nodeHead, "h");
    InsertAt(&nodeHead, "7", 1);
    PrintList(nodeHead);

    ReverseList(&nodeHead);
    PrintList(nodeHead);
    
    return 0;
}