#include "stack.h"
#include<assert.h>

/*Funktionen ar fardig*/
Stack initializeStack(void)
{
    return createEmptyList();
}

int stackIsEmpty(const Stack stack)
{
    isEmpty(stack);
}

/* Postcondition 'data' ligger overst p� stacken */
void push(Stack* stack, const Data data)
{
    addFirst(stack, data);
}

/* Precondition: stacken far inte vara tom */
void pop(Stack* stack)
{
    if(!stackIsEmpty(*stack))
    {
        removeFirst(stack);
    }
    return;
}

/* Precondition: stacken far inte vara tom */
Data peekStack(const Stack stack)
{
    if(!stackIsEmpty(stack))
    {
        return getFirstElement(stack);
    }
    return NULL;
}

/* Anvands for testning och felsokning
 Tips: det kan vara bra att ocksa notera i urskriften vart toppen pa stacken ar */
void printStack(const Stack stack, FILE *textFile)
{
    fprintf(textFile, "\nStacken innehaller: ");
    printList(stack, textFile);
    fprintf(textFile, "\n");
}
