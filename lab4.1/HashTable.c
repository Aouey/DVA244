#define _CRT_SECURE_NO_WARNINGS // Behovs for vissa funktioner i visual studio
#include "HashTable.h"
#include "Bucket.h"
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

	// Anvands for att markera en ledig plats i Hashtabellen


/* Denna funktion tar en nyckel och returnerar ett hash-index
dvs ett index till arrayen som �r Hashtabellen */
static int hash(Key key, int tablesize)
{
	return key % tablesize;
}

/*Leta fram�t enligt principen �ppen adressering
 Antalet krockar returneras via pekaren col i parameterlistan*/
static int linearProbe(const HashTable* htable, Key key, unsigned int *col)
{
    int size = (*htable).size;
    int index = hash(key, size);

    if((*htable).table[index].key == UNUSED){
        return index;
    }else{
        while((*htable).table[index].key != UNUSED){

            (*col)++;
            index++;
            if(index >= size){
                index = 0;
            }
        }
        return index;
    }
}



/*Allokera minne f�r hashtabellen*/
HashTable createHashTable(unsigned int size)
{
    HashTable* htable = (HashTable*)malloc(sizeof(HashTable) * size);
    htable->table = (struct Bucket*)malloc(sizeof(struct Bucket) * size);    
    assert(htable != NULL);
    (*htable).size = size;

    for(int i = 0; i < size; i++){
        (*htable).table[i].key = UNUSED;
    }

    return *htable;
}

/* Satter in paret {key,data} i Hashtabellen, om en nyckel redan finns ska vardet uppdateras */
/* Returnerar antalet krockar (som r�knas i linearProbe() )*/
unsigned int insertElement(HashTable* htable, const Key key, const Value value)
{
    int col = 0;
    int index = linearProbe(htable, key, &col);
    (*htable).table[index].key = key;
    (*htable).table[index].value = value;

    for(int i = 0; i < htable->size; i++){
        printf("%d ", (*htable).table[i].key);
    }
    printf("\n");

    assert(lookup(htable, key) != NULL);
    return col; 
}

/* Tar bort datat med nyckel "key" */
void deleteElement(HashTable* htable, const Key key)
{
	// Postcondition: inget element med key finns i tabellen (anvand loookup() for att verifiera)
}

/* Returnerar en pekare till vardet som key ar associerat med eller NULL om ingen sadan nyckel finns */
const Value* lookup(const HashTable* htable, const Key key)
{
    int size = (*htable).size;
    int index = hash(key, size);

    if((*htable).table[index].key == key){
        return &(*htable).table[index].value;
    }else{
        for(int i = 0; i < size; i++){
            if((*htable).table[i].key == key){
                return &(*htable).table[i].value;
            }
        }
        return NULL;
    }
}


/* Tommer Hashtabellen */
void freeHashTable(HashTable* htable)
{
	// Postcondition: hashtabellen har storlek 0
}

/* Ger storleken av Hashtabellen */
unsigned int getSize(const HashTable* htable)
{
    return (*htable).size;
}

/* Denna for att ni enkelt ska kunna visualisera en Hashtabell */
void printHashTable(const HashTable* htable)
{
	// Tips: anvand printPerson() i Person.h for att skriva ut en person
}
