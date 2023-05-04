#define _CRT_SECURE_NO_WARNINGS
#include "HashTable.h"
#include "Bucket.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

static int hash(Key key, int tablesize)                                                     // Hashfunction, returns index 
{
	return key % tablesize;
}

int getIndex(HashTable htable, Key key){                                                    // Returns index of key, -1 if not found
    for(int i = 0; i < htable.size; i++){
        if(htable.table[i].key == key){
            return i;
        }
    }
    return -1;
}

static int linearProbe(const HashTable* htable, Key key, unsigned int *col)                 // Linear probing, returns closest free index
{
    int size = (*htable).size;                                                              // Size of table
    int index = hash(key, size);                                                            // Index of key

    if((*htable).table[index].key == UNUSED){                                               // If key is free, return index
        return index;
    }else{                                                                                  // Else, find closest free index
        while((*htable).table[index].key != UNUSED){

            (*col)++;                                                                       // Count collisions, important that () is used here because PEMDAS
            index++;
            if(index >= size){                                                              // If probed to end of table, start from beginning
                index = 0;
            }
        }
        return index;                                                                       // Return index of free spot
    }
}

HashTable createHashTable(unsigned int size)                                                // Creates a new HashTable
{
    HashTable* htable = (HashTable*)malloc(sizeof(HashTable) * size);                       // Allocate memory for HashTable and Buckets
    htable->table = (struct Bucket*)malloc(sizeof(struct Bucket) * size); 

    assert(htable != NULL);                                                                 // Assert that memory was allocated
    assert(htable->table != NULL);

    (*htable).size = size;                                                                  // Set size of table

    for(int i = 0; i < size; i++){                                                          // Set all keys to UNUSED
        (*htable).table[i].key = UNUSED;
    }

    return *htable;                                                                         // Return HashTable
}

unsigned int insertElement(HashTable* htable, const Key key, const Value value)             // Inserts data into HashTable
{
    int col = 0;
    int index = linearProbe(htable, key, &col);                                             // Get index of free spot

    if(lookup(htable, key) != NULL){                                                        // If key already exists, update value
        index = getIndex(*htable, key);
        (*htable).table[index].value = value;
    
        return col;
    }else{                                                                                  // Else, insert data
        (*htable).table[index].key = key;
        htable->table[index].value = value;

        assert(lookup(htable, key) != NULL);
        return col;                                                                         // Return number of collisions
    }
}

void deleteElement(HashTable* htable, const Key key)                                        // Deletes element with target key from HashTable
{
    int index = getIndex(*htable, key);                                                     // Get index of key
    index >= 0 ? (*htable).table[index].key = UNUSED : 0;                                   // If key exists, set key to UNUSED

    assert(lookup(htable, key) == NULL);                                                    // Assert that key is deleted
}

const Value* lookup(const HashTable* htable, const Key key)                                 // Returns pointer to value of target key
{
    int size = (*htable).size;
    int index = hash(key, size);                                                            // Get hash index of key

    if((*htable).table[index].key == key){                                                  // If key is at hash index, return value
        return &(*htable).table[index].value;
    }else{                                                                                  // Else, search for key
        index = getIndex(*htable, key);                                                     // Get index of key
        if(index > 0){                                                                      // If key exists, return value
            return &(*htable).table[index].value;
        }else{                                                                              // Else, return NULL
            return NULL;
        }
    }
}

void freeHashTable(HashTable* htable)                                                       // Frees memory of HashTable
{
    free((*htable).table);                                                                  // Free memory of Buckets
    (*htable).table = NULL;                                                                 // Set pointer to NULL
    (*htable).size = 0;                                                                     // Set size to 0

    assert((*htable).size == 0);                                                            // Assert that size is 0
}

unsigned int getSize(const HashTable* htable)                                               // Returns size of HashTable
{
    return (*htable).size;
}

void printHashTable(const HashTable* htable)                                                // Prints HashTable
{
    for(int i = 0; i < htable->size; i++){                                                  // Print all Buckets
        if(htable->table[i].key != UNUSED){                                                 // If key is not UNUSED, print key and value
            printf("%i; Key: %i, Name: %s, PersonalNumber: %i, Weight: %f\n", 
                i, htable->table[i].key, htable->table[i].value.name, htable->table[i].value.personalNumber, htable->table[i].value.weight);
        }else{                                                                              // Else, print UNUSED
            printf("%i; Key: UNUSED\n", i);
        }
    }
    printf("\n");
}