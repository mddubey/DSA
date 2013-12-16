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

int areArrayEqual(void** a,void** b, int length){
	int i;
	for(i = 0;i<length;i++){
		if(a[i] != b[i])
			return 1;
	}
	return 0;
}

//************************************************************************************

void test_sorts_collections_of_Integers(){
	int nums[5] = {5,10,12,20,25};
	void* ptrs[5] = {(nums+4),(nums+3),(nums+2),(nums+1),(nums+0)};
	void* expected[5] = {(nums+0),(nums+1),(nums+2),(nums+3),(nums+4)};
	isort(ptrs, 5, sizeof(int), compareInt);
	ASSERT(areArrayEqual(ptrs, expected, 5));
}

// void test_sorts_collections_of_Doubles(){
// 	double nums[5] = {1.0,2.0,5.0,1.5,1.7};
// 	double expected[5] = {1.0,1.5,1.7,2.0,5.0};
// 	isort(nums, 5, sizeof(double), compareDoubles);
// 	printf("%lf\n", nums[1]);
// 	ASSERT(areArrayEqual(nums, expected, 5, sizeof(double)));
// }

void test_sorts_collections_of_Doubles(){
	double nums[5] = {1.0,2.0,3.0,5.0,7.0};
	void* ptrs[5] = {(nums+3),(nums+1),(nums+4),(nums+2),(nums)};
	void* expected[5] = {(nums+0),(nums+1),(nums+2),(nums+3),(nums+4)};
	isort(ptrs, 5, sizeof(double), compareDoubles);
	ASSERT(areArrayEqual(ptrs, expected, 5));
}

void test_sorts_collections_of_Characters(){
	char chars[5] = {'a','b','r','u','z'};
	void* ptrs[5] = {(chars+3),(chars+1),(chars+4),(chars+2),(chars)};
	void* expected[5] = {(chars+0),(chars+1),(chars+2),(chars+3),(chars+4)};
	isort(ptrs, 5, sizeof(char), compareChars);
	ASSERT(areArrayEqual(ptrs, expected, 5));
}

// typedef char String[256];
// void test_sorts_collections_of_String(){
// 	String names[5] = {"Raaj","Raaz","Raam","Rahul","Rajan"};
// 	String expected[5] = {"Raaj","Raam","Raaz","Rahul","Rajan"};
// 	isort(names, 5, sizeof(String), compareStrings);
// 	ASSERT(areArrayEqual(names, expected, 5, sizeof(String)));
// }


