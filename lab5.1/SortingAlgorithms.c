#define _CRT_SECURE_NO_WARNINGS
#include "SortingAlgorithms.h"
#include "Statistics.h"
#include "Array.h"
#include <assert.h>
#include <string.h>

int isImplemented(SortingAlgorithm algorithm)
{
	switch (algorithm)
	{
      case BUBBLE_SORT:
      case INSERTION_SORT:
      case SELECTION_SORT:
      case QUICK_SORT:
//      case MERGE_SORT:
            return 1;
        default:
            return 0;
	}
}

/*Antalet byten i en och samma algoritm kan vara olika beroende p� implementationen. Ibland ligger datat redan p� r�tt plats och d� kan man v�lja att testa det och inte g�ra ett byte (vilket ger extra j�mf�relse) eller s� kan man �nd� g�ra ett byte (med sig sj�lv). F�ljer man de algoritmer som vi g�tt igenom p� f�rel�sningarna exakt s� g�r man en swap �ven p� ett element som ligger p� r�tt plats
 
    N�r du analyserar det data som genereras (result.txt) s� beh�ver du ha detta i �tanke */

/******************************************************************************************/
/* Era algoritmer har: */

static void bubbleSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)						// Bubble Sort
{
	for(int outer = 0; lessThan(outer, size - 1, statistics); outer++){ 										// Outer loop, loops over array once
		int sort = 0;																							// Sort variable to check if array is sorted
		for(int inner = 0; lessThan(inner, size - outer - 1, statistics); inner++){								// Inner loop checks values and swaps places

			if(greaterThan(arrayToSort[inner], arrayToSort[inner + 1], statistics)){							// If items are not in order swap them
				swapElements(&arrayToSort[inner], &arrayToSort[inner + 1], statistics);
				sort++;																							// Increment sort variable
			}
		}
		if(sort == 0) return;																					// Checks if array is sorted and returns if true
	}
}

static void insertionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)					// Insertion Sort
{
	for(int sortedLimit = 1; lessThan(sortedLimit, size, statistics); sortedLimit++){ 							// Loops through the array
		
		int index = 0;
		for(int i = 0; lessThan(i, sortedLimit, statistics); i++){												// Loops through the sorted part of the array
			lessThan(arrayToSort[sortedLimit], arrayToSort[i], statistics) == 1 ? 0 : index++;					// Checks if the first element in the unsorted part is smaller than the current element in the sorted part
		}																										// If true increment the index
		
		if(index != sortedLimit){																				// Small optimisation, checks if the element is already in the right place
			for(int k = sortedLimit; greaterThan(k, index, statistics); k--){									// Loops from first element in the unsorted part to target index (index)
				swapElements(&arrayToSort[k], &arrayToSort[k-1], statistics);									// Swap the elements to the left until firt element in the unsorted part is at target index
			}
		}
	}
}

static void selectionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)					// Selection Sort
{
	for(int first = 0; lessThan(first, size, statistics); first++){												// Loops through the array

		int smallest = first; 																					// Sets the smallest index to the first index in the unsorted part of the array
		for(int i = first; lessThan(i, size, statistics); i++){													// Loops through the unsorted part of the array
			lessThan(arrayToSort[i], arrayToSort[smallest], statistics) == 1 ? smallest = i : 0;				// Checks if current element is smaller than the current smallest element, if true set the smallest index to the current index
		}
		if(arrayToSort[smallest] < arrayToSort[first]){															// Make size comparison to avoid unnecessary swaps
			swapElements(&arrayToSort[smallest], &arrayToSort[first], statistics);								// Swap the smallest element with the first element in the unsorted part of the array
		}
	}
}

static void mergeSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)						// Merge Sort, not started
{
}

static void auxQuick(ElementType* arrayToSort, unsigned int size, int firstIndex, int lastIndex, Statistics* statistics){	// Auxilary function for Quick Sort
	if(greaterThanOrEqualTo(firstIndex, lastIndex, statistics)) return; 										// Checks if the first index is greater than or equal to the last index, if true return

	int pivot = arrayToSort[lastIndex]; 																		// Sets the pivot to the last element in the array
	int i = firstIndex; 																						// Sets swap index to the first index in the array

	for(int j = firstIndex; lessThan(j, lastIndex, statistics); j++){											// Loops through the array
		if(lessThan(arrayToSort[j], pivot, statistics)){														// Checks if the current element is smaller than the pivot
			swapElements(&arrayToSort[i], &arrayToSort[j], statistics);											// If true swap the elements
			i++;																								// Increment the swap index
		}
	}

	swapElements(&arrayToSort[i], &arrayToSort[lastIndex], statistics);											// Swap the pivot with the element at the swap index
	auxQuick(arrayToSort, size, firstIndex, i - 1, statistics);													// Call the function recursively for the left part of the array
	auxQuick(arrayToSort, size, i + 1, lastIndex, statistics);													// Call the function recursively for the right part of the array
}

static void quickSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	auxQuick(arrayToSort, size, 0, size - 1, statistics);
}

/******************************************************************************************/


char* getAlgorithmName(SortingAlgorithm algorithm)
{
	/* Ar inte strangen vi allokerar lokal for funktionen?
	   Nej, inte i detta fall. Strangkonstanter ar ett speciallfall i C */
	switch (algorithm)
	{
        case BUBBLE_SORT:	 return "  Bubble sort ";
        case SELECTION_SORT: return "Selection sort";
        case INSERTION_SORT: return "Insertion sort";
        case MERGE_SORT:	 return "  Merge sort  ";
        case QUICK_SORT:	 return "  Quick sort  ";
        default: assert(0 && "Ogiltig algoritm!"); return "";
	}
}

// Sorterar 'arrayToSort' med 'algorithmToUse'. Statistik for antal byten och jamforelser hamnar i *statistics
static void sortArray(ElementType* arrayToSort, unsigned int size, SortingAlgorithm algorithmToUse, Statistics* statistics)
{
	if(statistics != NULL)
		resetStatistics(statistics);

	switch (algorithmToUse)
	{
	case BUBBLE_SORT:	 bubbleSort(arrayToSort, size, statistics); break;
	case SELECTION_SORT: selectionSort(arrayToSort, size, statistics); break;
	case INSERTION_SORT: insertionSort(arrayToSort, size, statistics); break;
	case MERGE_SORT:	 mergeSort(arrayToSort, size, statistics); break;
	case QUICK_SORT:	 quickSort(arrayToSort, size, statistics); break;
	default:
		assert(0 && "Ogiltig algoritm!");
	}
}

// Forbereder arrayer for sortering genom att allokera minne for dem, samt intialisera dem
static void prepareArrays(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], const unsigned int sizes[])
{
	assert(isImplemented(algorithm));

	int i;
	int totalArraySize;

	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		totalArraySize = sizeof(ElementType)*sizes[i];
		sortingArray[i].arrayToSort = malloc(totalArraySize);
		memcpy(sortingArray[i].arrayToSort, arrays[i], totalArraySize);

		sortingArray[i].algorithm = algorithm;
		sortingArray[i].arraySize = sizes[i];
		resetStatistics(&sortingArray[i].statistics);
	}
}

// Sorterar arrayerna
static void sortArrays(SortingArray toBeSorted[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		SortingArray* current = &toBeSorted[i];
		sortArray(current->arrayToSort, current->arraySize, current->algorithm, &current->statistics);
	
		if (!isSorted(current->arrayToSort, current->arraySize))
		{
			printf("Fel! Algoritmen %s har inte sorterat korrekt!\n", getAlgorithmName(current->algorithm));
			printf("Resultatet �r: \n");
			printArray(current->arrayToSort, current->arraySize, stdout);
			assert(0); // Aktiveras alltid
		}
	}
}

void printResult(SortingArray sortedArrays[], FILE* file)
{
	assert(file != NULL);

	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		fprintf(file, "%4d element: ", sortedArrays[i].arraySize);
		printStatistics(&sortedArrays[i].statistics, file);
		fprintf(file, "\n");
	}
	fprintf(file, "\n");
}

void sortAndPrint(SortingArray sortingArray[], SortingAlgorithm algorithm, const ElementType* arrays[], unsigned int sizes[], FILE* file)
{
	assert(file != NULL);

	prepareArrays(sortingArray, algorithm, arrays, sizes);
	sortArrays(sortingArray);
	printResult(sortingArray, file);
}

void freeArray(SortingArray sortingArray[])
{
	int i;
	for (i = 0; i < NUMBER_OF_SIZES; i++)
	{
		if (sortingArray[i].arrayToSort != NULL)
			free(sortingArray[i].arrayToSort);
		sortingArray[i].arrayToSort = NULL;
		sortingArray[i].arraySize = 0;
		resetStatistics(&sortingArray[i].statistics);
	}
}
