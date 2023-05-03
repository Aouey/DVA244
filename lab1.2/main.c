#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <assert.h>

int sum(int numToAdd) {
	if(numToAdd <= 0) 
		return 0; // If the number is negative, return 0 (no negative numbers

	printf("\nSum(%i) anropas", numToAdd);

	int output = numToAdd + sum(numToAdd - 1);

	printf("\nSum(%i) returnerar %i", numToAdd, output);
	return output;

}

void main() {
	int num = 0, result = 0;
	printf("How many numbers to add? ");
	scanf("%i", &num);
	result = sum(num);
	printf("\n\nEntered number: %i, Returned value %i\n\nAsserts: -----------------", num, result);

	assert(sum(1) == 1);
	assert(sum(2) == 3);
	assert(sum(3) == 6);
	assert(sum(4) == 10);
	assert(sum(5) == 15);
	assert(sum(20) == 210);
	assert(sum(0) == 0);
	assert(sum(-1) == 0);
}