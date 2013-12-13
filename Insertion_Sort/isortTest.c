#include "isort.h"
#include <string.h>
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

int compareInt (void* a, void* b){
	return (*(int*)a - *(int*)b);
}

int compareDoubles(void* a, void* b){
	return (*(double*)a - *(double*)b);
}

int compareChars(void* a, void* b){
	return (*(char*)a - *(char*)b);
}

int compareStrings(void* a, void* b){
	return strcmp((char*)a, (char*)b);
}

int areArrayEqual(void* a,void* b, int length, int size){
	return 0 == memcmp(a, b, length*size);
}

//************************************************************************************

void test_sorts_collections_of_Integers(){
	int nums[5] = {25,20,12,10,5};
	int expected[5] = {5,10,12,20,25};
	isort(nums, 5, sizeof(int), compareInt);
	ASSERT(areArrayEqual(nums, expected, 5, sizeof(int)));
}

// void test_sorts_collections_of_Doubles(){
// 	double nums[5] = {1.0,2.0,5.0,1.5,1.7};
// 	double expected[5] = {1.0,1.5,1.7,2.0,5.0};
// 	isort(nums, 5, sizeof(double), compareDoubles);
// 	printf("%lf\n", nums[1]);
// 	ASSERT(areArrayEqual(nums, expected, 5, sizeof(double)));
// }

void test_sorts_collections_of_Doubles(){
	double nums[5] = {1.0,2.0,5.0,3.0,7.0};
	double expected[5] = {1.0,2.0,3.0,5.0,7.0};
	isort(nums, 5, sizeof(double), compareDoubles);
	ASSERT(areArrayEqual(nums, expected, 5, sizeof(double)));
}

void test_sorts_collections_of_Characters(){
	char chars[5] = {'r','a','u','z','b'};
	char expected[5] = {'a','b','r','u','z'};
	isort(chars, 5, sizeof(char), compareChars);
	ASSERT(areArrayEqual(chars, expected, 5, sizeof(char)));
}

typedef char String[256];
void test_sorts_collections_of_String(){
	String names[5] = {"Raaj","Raaz","Raam","Rahul","Rajan"};
	String expected[5] = {"Raaj","Raam","Raaz","Rahul","Rajan"};
	isort(names, 5, sizeof(String), compareStrings);
	ASSERT(areArrayEqual(names, expected, 5, sizeof(String)));
}


