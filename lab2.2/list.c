#include "list.h"
#include <stdlib.h>
#include <assert.h>

static struct node* createListNode(const Data data)             //initialize a new node with data
{
  struct node* newNode = NULL;                                  //creates empty new node
  newNode = (struct node*)malloc(sizeof(struct node));          //allocates memory
  assert(newNode != NULL);                                      //check success of malloc()
  
  newNode->next = NULL;
  newNode->previous = NULL;
  newNode->data = data;                                         //saves data
 
  return newNode;                                               //returns data
}

List createEmptyList(void)                                      //creates empty List item
{
    return NULL;
}

int isEmpty(const List list)                                    //checks to see if list is empty, returns 1 if empty
{
  if(list == NULL){
    return 1;
  } else {
    return 0;
  } 
}

void addItem(struct node* nxt, struct node* prvs, List* list){  //adds item to specified position of list
  struct node* itm = createListNode((*itm).data);               //creates new node item

  assert(list != NULL);                                         //check success of malloc()
  
  if(nxt != NULL){                                              //if next node exists
    if(prvs != NULL){                                           //if previous node exists
      (*itm).next = nxt;                                        //set next node to next node
      (*itm).previous = prvs;                                   //set previous node to previous node
      (*prvs).next = itm;                                       //set previous node next pointer to new node
      (*nxt).previous = itm;                                    //set next node previous pointer to new node
    }else{                                                      //if previous node does not exist
      (*itm).next = nxt;                                        //set next node to next node
      (*itm).previous = NULL;                                   //set previous node to null
      (*nxt).previous = itm;                                    //set next node previous pointer to new node
      *list = itm;                                              //set list to new node
    }
  }else{                                                        //if next node does not exist
    if(prvs != NULL){                                           //if previous node exists
      (*itm).next = NULL;                                       //set next node to null
      (*itm).previous = prvs;                                   //set previous node to previous node
      (*prvs).next = itm;                                       //set previous node next pointer to new node
    }else{                                                      //if previous node does not exist
      (*itm).next = NULL;                                       //set next node to null
      (*itm).previous = NULL;                                   //set previous node to null
      *list = itm;                                              //set list to new node
    }
  }
}

void addFirst(List* list, const Data data)                      //add node to first position of list
{
  struct node* itm = createListNode(data);                      //creates node

  if(isEmpty(*list)){                                           //if list is empty set list equal to new node
    *list = itm;
  }else{
    addItem(*list,NULL, list);                                  //if list is not empty links node to next coming
  }
}

void addLast(List* list, const Data data)                       //adds new node after last current position in list
{
  struct node* itm = createListNode(data);                      //creates new node item

  if(isEmpty(*list)){                                           //checks if list is empty
    *list = itm;                                                //if the list is empty set list equal to new node
  }else{
    struct node* nxtNde = *list;                                //if the list is not empty create new node item to iterate existing list
    while(nxtNde->next != NULL){                                //iterates over existing list to find last item
      nxtNde = nxtNde->next;
    }
    addItem(NULL, nxtNde, list);                                //adds item after last current item by linking to iterated node
  } 
}

void removeNode(List* list, struct node* trgt){                 //removes specified node
  if(trgt->next != NULL){                                       //if next node exists
    if(trgt->previous != NULL){                                 //if previous node exists
      trgt->previous->next = trgt->next;                        //set previous node next pointer to next node
      trgt->next->previous = trgt->previous;                    //set next node previous pointer to previous node
    }else{                                                      //if previous node does not exist
      trgt->next->previous = NULL;                              //set next node previous pointer to null
      *list = trgt->next;                                       //set list to next node
    }
  }else{                                                        //if next node does not exist
    if(trgt->previous != NULL){                                 //if previous node exists
      trgt->previous->next = NULL;                              //set previous node next pointer to null
    }else{                                                      //if previous node does not exist
      *list = NULL;                                             //set list to null
    }
  }
  free(trgt);                                                   //free memory
}

void removeFirst(List* list)                                    //removes the first node in list
{
  assert(*list != NULL);                                        //useless prerequisite to double check list is not empty i guess?
  removeNode(list, *list);                                      
}

void removeLast(List* list)                                     //removes the last node in the list
{
  assert(*list != NULL);                                        //useless prerequisite to double check list is not empty i guess?

  struct node* iterate = (*list);                               //iterates over list to find the last node
  while(iterate->next != NULL){
    iterate = iterate->next;
  }

  removeNode(list, iterate);                                    //removes the last node from the list
}

int search(const List list, const Data data)                    //searches list for target data, returns 1 if data is found otherwise returns 0
{
  if(!isEmpty(list)){                                           //checks if list is empty
    struct node* trgt = list;                                   //creates a target node

    while(trgt->next != NULL){                                  //iterates over list 
      if(trgt->data == data){                                   //returns 1 if target data matches
        return 1;
      }else{
        trgt = trgt->next;                                      //moves onto next node in list
      }
    }

    if(trgt->data == data){                                     //returns 1 if target data matches
      return 1;                                                 //returns 0 if the entire list is exhausted
    }else{
      return 0;                                                 //returns 0 if list is empty since an empty list does not contain any data
    } 
  }
  return 0;
}

int removeElement(List* list, const Data data)                  //removes first node with specified data 
{
  if(!isEmpty(list) && search(*list, data)){                    //checks if list is empty and contain target data
    struct node* trgt = *list;                                  //creates a target node

    while(trgt->next != NULL){                                  //iterates over list 
      if(trgt->data == data){                                   
        removeNode(list, trgt);                                 //removes target node
        return 1;

      }else{
        trgt = trgt->next;                                      //moves onto next node in list
      }
    }
    if(trgt->data == data){                                     //removes target node if it is the last node in the list
        removeNode(list, trgt);                                 //removes target node
        return 1;                                               //returns 0 if the entire list is exhausted
    }else{
      return 0;                                                 //returns 0 if list is empty or does not contain target data
    } 
  }
}

int numberOfNodesInList(const List list)                        //counts nodes in list
{
  if(!isEmpty(list)){                                           //checks if list is empty
    struct node* iNde = list; int i = 0;                        //creates an iteration node
    
    while(iNde != NULL){                                        //iterates over list 
      i++;
      iNde = iNde->next;                                        //moves onto next node in list
    }
    return i;                                                   //returns number of iterations
  }else{
    return 0;                                                   //returns 0 if list is empty since an empty list does not contain any nodes
  } 
}

void clearList(List* list)                                      //empties list of all nodes
{
  if(!isEmpty(*list)){                                          //checks if list is empty before starting
    while(!isEmpty(*list)){                                     //while list is not empty removes the first node
      removeFirst(list);
    }
    assert(*list == NULL);                                       //checks if function was successful
  }
}

void printList(const List list, FILE* textfile) {               //prints all nodes in list
  if (list == NULL) {
    fprintf(textfile, "\n\n");
    return;
  }

  fprintf(textfile, "%i ", list->data);
  printList(list->next, textfile);
}

Data getFirstElement(const List list)                           //returns value of data in first node of list
{
  assert(list != NULL);                                         //why does isEmptylea() exist if assert is going to be used instead?
  return list->data;                                            //returns value
}

Data getLastElement(const List list)
{                                                               //returns last value
  if(!isEmpty(list)){                                           //checks if list is empty
    struct node* iNde = list;                                   //creates an iteration node
    
    while(iNde->next != NULL){                                  //iterates over list 
      iNde = iNde->next;                                        //moves onto next node in list
    }
    
    return iNde->data;                                          //returns value of last node
  }
    return 0;                                                   //returns 0 if list is empty since an empty list does not contain any nodes

}
