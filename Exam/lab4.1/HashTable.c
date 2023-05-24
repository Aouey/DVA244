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
    int index = hash(key, (int)htable.size);                                                // Get hash index of key
    int iterateIndex = 0;                                                                   // Index to iterate through table
    
    if(htable.table[index].key == key){                                                     // If key is at hash index, return index
        return index;

    }else{
        for(int i = 1; i < (int)htable.size; i++){
            iterateIndex = hash(key + i, (int)htable.size);                                 // Get index to iterate through table

            if(htable.table[iterateIndex].key == key){                                      // If key is at iterate index, return index
                return iterateIndex;
            }
        }
    }
    return -1;                                                                              // If key is not found, return -1
}

// Added for exam 24/05----------------                                                     // The function could not be called collisions (plural) as there already was a variable with the same name

int collision(HashTable table){                                                             // Returns how many keys have the "wrong" index
    int collisions = 0;
    for(int i = 0; i < table.size; i++){                                                    // Loops through the hash table
        int key = table.table[i].key;
        int pos = getIndex(table, key);
        int trgt = hash(key, table.size);

        if(pos != trgt && key != UNUSED) collisions++;                                      // Checks if the key is on the same index as the hash function says
    }                                                                                       // If true add one to collisions variable
    return collisions;                                                                      // Return collisions 
}

// ------------------------------------

static int linearProbe(const HashTable* htable, Key key, unsigned int *col)                 // Linear probing, returns closest free index
{
    int size = (int)htable->size;                                                           // Size of table
    int index = hash(key, size);                                                            // Index of key

    if(htable->table[index].key == UNUSED){                                                 // If key is free, return index
        return index;
    }else{                                                                                  // Else, find closest free index
        
        int iterate = 0;
        for(int i = 1; i < (int)htable->size; i++){
            iterate = hash(key + i, size);                                                  // Get index to iterate through table
            (*col)++;                                                                       // Increment number of collisions
            if(htable->table[iterate].key == UNUSED){
                return iterate;
            }
        }
    }
    return -1;                                                                              // If no free index is found, return -1
}

HashTable createHashTable(unsigned int size)                                                // Creates a new HashTable
{
    HashTable htable = {0};
    htable.size = size;                                                                     // Set size of table
    htable.table = (struct Bucket*)malloc(sizeof(struct Bucket) * size); 
    assert(htable.table != NULL);                                                           // Assert that memory is allocated

    for(int i = 0; (int)i < (int)size; i++){                                                // Set all keys to UNUSED
        htable.table[i].key = UNUSED;
    }

    return htable;                                                                          // Return HashTable
}

unsigned int insertElement(HashTable* htable, const Key key, const Value value)             // Inserts data into HashTable
{
    int col = 0;
    int index = 0;

    if(lookup(htable, key) != NULL){                                                        // If key already exists, update value
        index = getIndex(*htable, key);
        htable->table[index].value = value;
    
        return (int)col;

    }else{                                                                                  // Else, insert new element
        index = linearProbe(htable, key, &col);

        if(index >= 0){
            htable->table[index].key = key;
            htable->table[index].value = value;
            assert(lookup(htable, key) != NULL);
            
            return (int)col;                                                                // Return number of collisions
        }else{
            return -1;
        }

    }
}

void deleteElement(HashTable* htable, const Key key)                                        // Deletes element with target key from HashTable
{
    int index = getIndex(*htable, key);                                                     // Get index of key
    index >= 0 ? htable->table[index].key = UNUSED : 0;                                     // If key exists, set key to UNUSED

    for(int i = 0; i < (int)htable->size; i++){                                             // Rehash all elements
        struct Bucket temp = htable->table[i];
        htable->table[i].key = UNUSED;
        insertElement(htable, temp.key, temp.value);
    }
}

const Value* lookup(const HashTable* htable, const Key key)                                 // Returns pointer to value of target key
{
    int index = getIndex(*htable, key);                                                     // Get index of key

    if(index >= 0){                                                                         // If key exists, return pointer to value
        return &(*htable).table[index].value;
    }else{                                                                                  // Else, return NULL
        return NULL;
    }
}

void freeHashTable(HashTable* htable)                                                       // Frees memory of HashTable
{
    free(htable->table);                                                                    // Free memory of Buckets
    htable->table = NULL;                                                                   // Set pointer to NULL
    htable->size = 0;                                                                       // Set size to 0

    assert(htable->size == 0);                                                              // Assert that size is 0
}

unsigned int getSize(const HashTable* htable)                                               // Returns size of HashTable
{
    return htable->size;
}

void printHashTable(const HashTable* htable)                                                // Prints HashTable
{
    for(int i = 0; i < (int)htable->size; i++){                                             // Print all Buckets
        if(htable->table[i].key != UNUSED){                                                 // If key is not UNUSED, print key and value
            printf("%i; Key: %i, Name: %s, PersonalNumber: %i, Weight: %f\n", 
                i, 
                htable->table[i].key, 
                htable->table[i].value.name, 
                htable->table[i].value.personalNumber, 
                htable->table[i].value.weight);
        }else{                                                                              // Else, print UNUSED
            printf("%i; Key: UNUSED\n", i);
        }
    }
    printf("\n");
}