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
	if(isSorted(arrayToSort, size) == 1){																		// Checks if the array is sorted
		return;																									// If true return
	}

	for(int i = 0; lessThan(i, size - 1, statistics); i++){														// Loops through the array
		if(greaterThan(arrayToSort[i], arrayToSort[i+1], statistics)){											// Checks if the current element is bigger than the next
			swapElements(&arrayToSort[i], &arrayToSort[i+1], statistics);										// If true swap the elements
		}
	}
	isSorted(arrayToSort, size) == 1 ? 0 : bubbleSort(arrayToSort, size, statistics);							// If the array is not sorted, call the function again
}

static void insertionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	for(int sortedLimit = 1; lessThan(sortedLimit, size, statistics); sortedLimit++){

		int index = 0;
		for(int i = 0; lessThan(i, sortedLimit, statistics); i++){
			lessThan(arrayToSort[sortedLimit], arrayToSort[i], statistics) == 1 ? 0 : index++;
		}

		for(int k = sortedLimit; greaterThan(k, index, statistics); k--){
			swapElements(&arrayToSort[k], &arrayToSort[k-1], statistics);
		}
	}
}

static void auxSelection(ElementType* arrayToSort, unsigned int size, int firstIndex, Statistics* statistics){
	if(greaterThanOrEqualTo(firstIndex, size, statistics)){
		return;
	}

	int smallestIndex = firstIndex;
	for(int i = firstIndex; lessThan(i, size, statistics); i++){
		lessThan(arrayToSort[i], arrayToSort[smallestIndex], statistics) == 1 ? smallestIndex = i : 0;
	}

	// printf("\n------------------\n");
	// for(int h = 0; h < size; h++){
	// 	printf("%i, ", arrayToSort[h]);
	// }
	// printf("\n------------------\n");

	swapElements(&arrayToSort[smallestIndex], &arrayToSort[firstIndex], statistics);
	isSorted(arrayToSort, size) == 1 ? 0 : auxSelection(arrayToSort, size, ++firstIndex, statistics);
}

static void selectionSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	isSorted(arrayToSort, size) == 1 ? 0 : auxSelection(arrayToSort, size, 0, statistics);
}

static void mergeSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
}

static void auxQuick(ElementType* arrayToSort, unsigned int size, int firstIndex, int lastIndex, Statistics* statistics){
	if(greaterThanOrEqualTo(firstIndex, lastIndex, statistics)){
		return;
	}

	int pivot = arrayToSort[lastIndex];
	int i = firstIndex - 1;
	for(int j = firstIndex; lessThan(j, lastIndex, statistics); j++){
		if(lessThan(arrayToSort[j], pivot, statistics)){
			i++;
			swapElements(&arrayToSort[i], &arrayToSort[j], statistics);
		}
	}
	swapElements(&arrayToSort[i+1], &arrayToSort[lastIndex], statistics);

	isSorted(arrayToSort, size) == 1 ? 0 : auxQuick(arrayToSort, size, firstIndex, i, statistics);
	isSorted(arrayToSort, size) == 1 ? 0 : auxQuick(arrayToSort, size, i+2, lastIndex, statistics);
}

static void quickSort(ElementType* arrayToSort, unsigned int size, Statistics* statistics)
{
	isSorted(arrayToSort, size) == 1 ? 0 : auxQuick(arrayToSort, size, 0, size - 1, statistics);
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
