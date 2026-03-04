#include <stdio.h>
#include <stdlib.h>

struct stackNode {                                      
   int data; 
   struct stackNode *nextPtr; 
}; 

typedef struct stackNode STACKNODE; 
typedef STACKNODE *STACKNODEPTR; 

void push(STACKNODEPTR *, int);
int pop(STACKNODEPTR *);
int isEmpty(STACKNODEPTR);
void printStack(STACKNODEPTR);
void instructions(void);

int main()
{ 
   STACKNODEPTR startPtr = NULL; 
   int choice;
   char value;
   instructions();
   printf("? ");
   scanf("%d", &choice);
   while (choice != 3){ 
      switch (choice){ 
         case 1:
            printf("Enter an integer: ");
            scanf("%d", &value);
            push(&startPtr, value);
            printStack(startPtr);
            break;
         case 2: 
            if (!isEmpty(startPtr)){ 
                  printf("%d deleted.\n", pop(&startPtr));
                  printStack(startPtr);
            } 
            else {
               printf("Stack is empty.\n\n");
            } 
            break;
         default:
            printf("Invalid choice.\n");
            instructions();
            break;
      }
      printf("? ");
      scanf("%d", &choice);
   } 
   printf("End of run.");
   return 0;
} 

void instructions(void)
{ 
   printf("Enter your choice:\n"
      "   1 to push a value on the stack.\n"
      "   2 to pop a value off the stack.\n"
      "   3 to end.\n");
} 

void push(STACKNODEPTR *sPtr, int info)
{ 
   STACKNODEPTR newPtr = malloc(sizeof(STACKNODE));
   if (newPtr != NULL){ 
      newPtr->data = info;
      newPtr->nextPtr = *sPtr;
      *sPtr = newPtr;
   }
   else{
      printf("%d not inserted. No memory available.\n", info);
   } 
} 

int pop(STACKNODEPTR *sPtr)
{ 
    STACKNODEPTR tempPtr = *sPtr;
    int popValue;
    popValue = (* sPtr)->data;
    * sPtr = (* sPtr)->nextPtr;
    free(tempPtr);
    return popValue;
} 

int isEmpty(STACKNODEPTR sPtr)
{ 
   return sPtr == NULL;
} 

void printStack(STACKNODEPTR currentPtr)
{ 
   if (isEmpty(currentPtr)){
      printf("Stack is empty.\n\n");
   } 
   else { 
      printf("The stack is:\n");
      while (currentPtr != NULL){ 
         printf("%d --> ", currentPtr->data);
         currentPtr = currentPtr->nextPtr;   
      } 
      printf("NULL\n\n");
   } 
} 