#include "queue.h"
#include<assert.h>

Queue initializeQueue(void)
{
    return NULL;
}

int queueIsEmpty(const Queue queue)
{
    isEmpty(queue);
}

void enqueue(Queue* queue, const Data data)
{
    addLast(queue, data);
}

void dequeue(Queue* queue)
{
    assert(!queueIsEmpty(*queue));
    removeFirst(queue);
}

Data peekQueue(const Queue queue)
{
    assert(!queueIsEmpty(queue));
    return getFirstElement(queue);
}

void printQueue(const Queue queue, FILE *textfile)
{
    printList(queue, textfile);
}