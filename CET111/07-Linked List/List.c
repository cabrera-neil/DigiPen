/******************************************************************************
Filename: List.c
Author: Neil Cabrera
Email: cabrera.n@digipen.edu
Date Created: 10 June 2019
Brief Description: Implement the Declared Functions in List.H, testing was done in
a separate file
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

/* Set to 1 if User wants to see the Notification for each function
   Set to 0 is User wants to suppress and just keep the Error Messages */
static const int NotificationsON = 0;

/* Adds a node to the end of the list */
void AddToEnd(struct Node** ppList, const char* value)
{   
    /* Check if value is NULL */
    if(value==NULL)
    {
        printf("Error - Value passed is NULL!\n");
        return;
    }

    /* Always check if the List is Empty 
       If Empty, call the AddToFront, else Find the Tail and Create a New Node */
    if(*ppList==NULL)
        AddToFront(ppList, value);
    else
    {
        struct Node* nodePointer = *ppList;
        while(1)
        {
            /* Do a forward checking of the next Node until we reach the end of the Linked List */
            if(nodePointer->next!=NULL)
                nodePointer = nodePointer->next;
            else
            {
                struct Node* newNode = NULL;
                char* newValue = NULL;
                
                /* Create a New Node */
                newNode = malloc(sizeof(struct Node));
                if(newNode==NULL)
                {
                    printf("Error - Unable to Allocate Memory!\n");
                    return;
                }
                
                /* Create a New String */
                newValue = malloc(sizeof(char)*(int)strlen(value));
                if(newValue==NULL)
                {
                    free(newNode); /* Free the Node Allocated Node */
                    printf("Error - Unable to Allocate Memory!\n");
                    return;
                }

                strcpy(newValue, value);
                newNode->value = newValue;
                newNode->next = NULL;
                
                /* Last Node will now point to the New Node */
                nodePointer->next = newNode;
                
                if(NotificationsON)
                    printf("Success - Inserted Node at End(Index '%d') with Value '%s'\n", Count(*ppList)-1, value);
                
                break;
            }
        }
    }
}

/* Adds a node to the front of the list */
void AddToFront(struct Node** ppList, const char* value)
{
    struct Node* newNode = NULL;
    char* newValue = NULL;
    
    /* Check if value is NULL */
    if(value==NULL)
    {
        printf("Error - Value passed is NULL!\n");
        return;
    }

    /* Create a New Node */
    newNode =  malloc(sizeof(struct Node));
    if(newNode==NULL)
    {
        printf("Error - Unable to Allocate Memory!\n");
        return;
    }

    /* Create a New String */
    newValue = malloc(sizeof(char)*(int)strlen(value));
    if(newValue==NULL)
    {
        free(newNode); /* Free the Node Allocated Node */
        printf("Error - Unable to Allocate Memory!\n");
        return;
    }
    
    strcpy(newValue, value);
    newNode->value = newValue;
    newNode->next = *ppList;
    
    /* Update the Head and point it to the New Node */
    *ppList = newNode;
    
    if(NotificationsON)
        printf("Success - Inserted Node at Index '%d' with Value '%s'\n", 0, value);
}

/* Inserts a node in front of given index node */
void InsertAt(struct Node** ppList, const char* value, int index)
{
    int counter=0;
    int nodeCount = Count(*ppList);
    
    struct Node* newPPList = NULL;
    struct Node* nodePointer = *ppList;

    /* Error Check - Negative Index or Below 0 */
    if(index<0)
    {
        printf("Error - Index must be greater than 0!\n");
        return;
    }
    
    /* Error Check - Index is beyond the length of the Linked List */
    if(index>nodeCount)
    {
        printf("Error - Cannot insert '%s' at Index %d. Index is out of range!\n", value, index);
        return;
    }

    /* Check if value is NULL */
    if(value==NULL)
    {
        printf("Error - Value passed is NULL!\n");
        return;
    }

    /* Special Case - Index is After the Last Node, Call AddToEnd */
    if(index==nodeCount)
    {
        AddToEnd(ppList, value);
        return;
    }

    /* Perform the Search and Create a New Linked List without the Matching Index */
    while(nodePointer!=NULL)
    {
        if(index==counter)
            AddToEnd(&newPPList, value);
        
        /* Reuse the Existing AddEnd Function as this works like a Queue which 
           is also what is being solved here */
        AddToEnd(&newPPList, nodePointer->value);
        nodePointer=nodePointer->next;
        counter++;
    }

    FreeList(ppList);
    *ppList = newPPList;
    
    if(NotificationsON)
        printf("Success - Inserted Node at Index '%d' with Value '%s'\n", index, value);
}

/* Returns number of nodes in the list */
int Count(struct Node* list)
{
    struct Node* nodePointer = list;
    int counter = 0;

    /* Go through the Linked List until NULL is reached 
       each loop will be counted as 1 Node */
    while(nodePointer!=NULL)
    {
        nodePointer = nodePointer->next;
        counter++;
    }

    return counter;
}

/* Frees (deletes) all nodes in the list */
void FreeList(struct Node** pList)
{
    /* Always check if the List is Empty 
       If Empty, inform the User, else Proceed to clear the Linked List */
    if(*pList==NULL)
        printf("Error - Linked List is empty!\n");
    else
    {
        struct Node* nodePointer = *pList;
        while(nodePointer!=NULL)
        {
            struct Node* newNodePointer = nodePointer->next;
            free(nodePointer->value);
            free(nodePointer);
            nodePointer = newNodePointer;
        }

        /* Dereference the Head */
        *pList = NULL;
        
        if(NotificationsON)
            printf("Success - Linked List has been cleared of all values!\n");
    }
}

/* Prints values of all nodes in list */
void PrintList(struct Node* list)
{
    /* Always check if the List is Empty 
       If Empty, inform the User, else Proceed to clear the Linked List */
    if(list==NULL)
        printf("Error - Nothing to Print! Linked List is empty!\n");
    else
    {
        /* Go through the Linked List and Print each value */
        int counter = 0;
        struct Node* nodePointer = list;
        while(nodePointer!=NULL)
        {
            printf("Node[%d] Value is: %s\n", counter++, nodePointer->value);
            nodePointer = nodePointer->next;
        }
    }
}

/* Erases a node at the given index node */
void EraseNode(struct Node** ppList, int index)
{
    int counter=0;
    int nodeCount = Count(*ppList);
    
    struct Node* newPPList = NULL;
    struct Node* nodePointer = *ppList;

    /* Error Check - Negative Index or Below 0 */
    if(index<0)
    {
        printf("Error - Index must be greater than 0!\n");
        return;
    }
    
    /* Error Check - Linked List is Empty */
    if(nodeCount==0)
    {
        printf("Error - Nothing to Erase. Linked List is Empty!\n");
        return;
    }

    /* Error Check - Index supplied is Out of Bounds of the Linked List */
    if(index>(nodeCount-1))
    {
        printf("Error - Cannot erase Index %d. Index is out of range!\n", index);
        return;
    }

    /* Perform the Search and Create a New Linked List without the Matching Index */
    while(nodePointer!=NULL)
    {
        /* Reuse the Existing AddEnd Function as this works like a Queue which 
           is also what is being solved here */
        if(index!=counter)
            AddToEnd(&newPPList, nodePointer->value);
        
        nodePointer=nodePointer->next;
        counter++;
    }

    FreeList(ppList);
    *ppList = newPPList;
    
    if(NotificationsON)
        printf("Success - Deleted Node with Matching Index to '%d'\n", index);
}

/* Erase all nodes with the given value in the list */
void EraseValue(struct Node** ppList, const char* value)
{
    struct Node* newPPList = NULL;
    struct Node* nodePointer = *ppList;

    /* Error Checking - Check if the Linked List is Empty */
    int nodeCount = Count(*ppList);
    if(nodeCount==0)
    {
        printf("Error - Nothing to Erase. Linked List is Empty!\n");
        return;
    }

    /* Check if value is NULL */
    if(value==NULL)
    {
        printf("Error - Value passed is NULL!\n");
        return;
    }

    /* Perform the Search and Create a New Linked List without the Matching Values */
    while(nodePointer!=NULL)
    {
        /* Reuse the Existing AddEnd Function as this works like a Queue which 
           is also what is being solved here */
        if(strcmp(nodePointer->value, value))
            AddToEnd(&newPPList, nodePointer->value);
        
        nodePointer=nodePointer->next;
    }

    FreeList(ppList);
    *ppList = newPPList;
    
    if(NotificationsON)
        printf("Success - Deleted nodes with Matching Value to '%s'\n", value);
}

/* Reverses the list */
void ReverseList(struct Node** ppList)
{
    struct Node* newPPList = NULL;
    struct Node* nodePointer = *ppList;

    /* Error Checking - Check if the Linked List is Empty */
    int nodeCount = Count(*ppList);
    if(nodeCount==0)
    {
        printf("Error - Nothing to Reverse here!\n");
        return;
    }

    /* Reuse the Existing AddToFront Function as this works like a Stack which 
       is also what is being solved here */
    while(nodePointer!=NULL)
    {
        AddToFront(&newPPList, nodePointer->value);
        nodePointer=nodePointer->next;
    }

    FreeList(ppList);
    *ppList = newPPList;

    if(NotificationsON)
        printf("Success - Linked List Reversed!\n");
}