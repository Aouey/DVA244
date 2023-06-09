#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "BSTree.h"

// Added for exam 24/05----------------

static int findSmallest(BSTree tree){                                                              // Finds the smallest value in tree
   BSTree temp = tree;
   while(temp->left != NULL){                                                                      // Loops left part of tree to find smallest value
      temp = temp->left;
   }
   return temp->data;                                                                              // Returns smallest data
}

static int findLargest(BSTree tree){                                                               // Finds the largest value in tree
   BSTree temp = tree;
   while(temp->right != NULL){                                                                     // Loops right part of tree to find largest value
      temp = temp->right;
   }
   return temp->data;                                                                              // Returns largest data
}

void removeExtremes(BSTree* tree){                                                                 // Removes the largest and smallest values from tree
   if(isEmpty(*tree)) return;                                                                      // If tree is empty return

   int smallest = findSmallest(*tree);                                                             // Find largest and smallest elements in tree
   int largest = findLargest(*tree);

   removeElement(tree, smallest);                                                                  // Removes elements from tree
   removeElement(tree, largest);
}

// ------------------------------------

static struct treeNode* createNode(int data)                                                       // creates a new node with data and returns it
{
   struct treeNode* newNode = (struct treeNode*)malloc(sizeof(struct treeNode));                   // allocate memory for node
   if(newNode == NULL){                                                                            // if allocation failed return NULL
      return newNode;
   }else{                                                                                          // if allocation succeeded, initialize node
      newNode->left = NULL;
      newNode->right = NULL;
      newNode->data = data;

      return newNode;                                                                              // return node
   }
}

void writeInorder(const BSTree tree, int* array, int* index)                                       // writes the tree to an array in inorder
{
   if(tree == NULL){                                                                               // if tree is empty return
      return;
   }else{
      writeInorder(tree->left, array, index);                                                      // recursive call
      array[*index] = tree->data;                                                                  // write current node to array
      (*index)++;                                                                                  // increment index
      writeInorder(tree->right, array, index);                                                     // recursive call
   }
}

static int* writeSortedToArray(const BSTree tree)                                                  // writes the tree to an array in sorted order  
{
   if(isEmpty(tree)){                                                                              // if tree is empty return NULL
      return NULL;
   }else{
      int size = numberOfNodes(tree);
      int* array = (int*)malloc(sizeof(int) * size);                                               // allocate memory for array
      assert(array != NULL);                                                                       // assert that allocation succeeded
      
      int index = 0;                                                                               // index for array
      writeInorder(tree, array, &index);                                                           // recursive call

      return array;                                                                                // return array
   }
}

static void buildTreeSortedFromArray(BSTree* tree, const int arr[], int size)                      // builds a balanced tree from a sorted array
{
   if(size == 0){                                                                                  // if size is 0, return
      return;
   }else{
      int middle = size / 2;                                                                       // find middle of array
      insertSorted(tree, arr[middle]);                                                             // insert middle element in tree
      buildTreeSortedFromArray(tree, arr, middle);                                                 // build tree from left half of array
      buildTreeSortedFromArray(tree, arr + middle + 1, size - middle - 1);                         // build tree from right half of array
   }
}

BSTree emptyTree(void)                                                                             // creates an empty tree 
{
	return NULL;
}

int isEmpty(const BSTree tree)                                                                     // returns 1 if tree is empty, 0 otherwise
{
   if(tree == NULL){
      return 1;
   }else{
      return 0;
   }
}

void insertSorted(BSTree* tree, int data)                                                          // inserts data in tree
{
   if(*tree == NULL){                                                                              // if tree is empty or end of tree is reached create new node                             
      *tree = createNode(data);
      assert(*tree != NULL);

   }else{                                                                                          // if duplicate node is found abort funtion
      if(data == (*tree)->data){
         return;
      }

      if(data > (*tree)->data){                                                                    // if data is greater than current node, search right
         insertSorted(&(*tree)->right, data);
      }else if(data < (*tree)->data){                                                              // if data is less than current node, search left
         insertSorted(&(*tree)->left, data);
      }
   }
}

void printPreorder(const BSTree tree, FILE *textfile)
{
   if(isEmpty(tree)){                                                                              // if tree is empty return
      return;
   }else{
      fprintf(textfile, "%i, ", tree->data);                                                       // print current node
      printPreorder(tree->left, textfile);                                                         // recursive call
      printPreorder(tree->right, textfile);                                                        // recursive call
   }
}

void printInorder(const BSTree tree, FILE *textfile)                                               // prints tree in inorder
{
   if(isEmpty(tree)){                                                                              // if tree is empty return
      return;
   }else{
      printInorder(tree->left, textfile);                                                          // recursive call
      fprintf(textfile, "%i, ", tree->data);                                                       // print current node
      printInorder(tree->right, textfile);                                                         // recursive call
   }
}

void printPostorder(const BSTree tree, FILE *textfile)
{
   if(isEmpty(tree)){                                                                              // if tree is empty return
      return;
   }else{
      printPostorder(tree->left, textfile);                                                        // recursive call
      printPostorder(tree->right, textfile);                                                       // recursive call
      fprintf(textfile, "%i, ", tree->data);                                                       // print current node
   }
}

int find(const BSTree tree, int data)                                                              // returns 1 if data is in tree, 0 otherwise
{
   if(isEmpty(tree)){                                                                              // if tree is empty return 0
      return 0;
   }else{                                                                                          // if tree is not empty
      if(tree->data == data){                                                                      // if data is found return 1
         return 1;

      }else if(data > tree->data){                                                                 // if data is not found, search right and left
            return find(tree->right, data);
      }else if(data < tree->data){
            return find(tree->left, data);
      }
   }
   return -1;
}

void removeElement(BSTree* tree, int data)                                                         // removes data from tree
{
   if(isEmpty(*tree) || find(*tree, data) == 0){                                                   // if tree is empty or data is not found abort function
      return;

   }else{                                                                                          // if tree is not empty and data is found
      if(data == (*tree)->data){                                                                   // removes specific node

         if((*tree)->left == NULL && (*tree)->right == NULL){                                      // if node is extremity, remove node and set to NULL
            free(*tree);
            *tree = NULL;

         }else if((*tree)->left == NULL && (*tree)->right != NULL){                                // if right node is not NULL, remove node and set to right node
            struct treeNode* temp = *tree;
            *tree = (*tree)->right;
            free(temp);
            temp = NULL;

         }else if((*tree)->left != NULL && (*tree)->right == NULL){                                // if left node is not NULL, remove node and set to left node
            struct treeNode* temp = *tree;
            *tree = (*tree)->left;
            free(temp);
            temp = NULL;

         }else if((*tree)->left != NULL && (*tree)->right != NULL){                                // if node has two children find smallest node in right subtree and replace node with smallest node, then remove target node
            struct treeNode* temp = (*tree)->right;
            while(temp->left != NULL){
               temp = temp->left;
            }
            (*tree)->data = temp->data;
            removeElement(&(*tree)->right, temp->data);
         }
         
      }else{                                                                                       // if data is not found, search right and left
         if(data > (*tree)->data){
            removeElement(&(*tree)->right, data);
         }else if(data < (*tree)->data){
            removeElement(&(*tree)->left, data);
         }
      }
   }
}

int numberOfNodes(const BSTree tree)                                                               // returns number of nodes in tree
{
   if(isEmpty(tree)){                                                                              // if tree is empty return 0
      return 0;
   }else{                                                                                          // if tree is not empty add add to number of nodes and return
      return numberOfNodes(tree->left) + numberOfNodes(tree->right) + 1;                  
   }
}

int depth(const BSTree tree)                                                                       // returns depth of tree
{
   if(isEmpty(tree)){                                                                              // if tree is empty return 0
      return 0;
   }

   int depthLeft = 0, depthRight = 0;                                                              // if tree is not empty add to depth and return

   depthLeft = depthLeft + depth(tree->left) + 1;
   depthRight = depthRight + depth(tree->right) + 1;

   if(depthLeft > depthRight){                                                                     // return greatest depth
      return depthLeft;
   }else{
      return depthRight;
   }
}

int minDepth(const BSTree tree)                                                                    // returns minimum depth of tree
{
   if(isEmpty(tree)){                                                                              // if tree is empty return 0
      return 0;
   }else{                                                                                          // if tree is not empty calculate minimum depth and return
      return (int)log2(numberOfNodes(tree)) + 1;
   }
}

void balanceTree(BSTree* tree)                                                                     // balances tree
{
   if(isEmpty(*tree)){                                                                              // if tree is empty break function
      return;
   }else{
      int size = numberOfNodes(*tree);                                                             // if tree is not empty, declare variables and call functions
      int* array = writeSortedToArray(*tree);
      freeTree(tree);
      buildTreeSortedFromArray(tree, array, size);                                                 // build tree from array

      free(array);                                                                                 // free memory allocated for array
      array = NULL;
   }
}

void freeTree(BSTree* tree)                                                                        // Frees the memory allocated to tree
{
   if(isEmpty(*tree)){
      return;
   }else{
      freeTree(&(*tree)->left);
      freeTree(&(*tree)->right);
      isEmpty(*tree) ? 0 : free(*tree);
      
      *tree = NULL;

      assert(isEmpty(*tree));
   }
}