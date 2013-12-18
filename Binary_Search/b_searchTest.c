#include "b_search.h"
#include <string.h>
#include "../customTypes.h"
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

int compareInt (constVoidPtr a, constVoidPtr b){
	return (*(int*)a - *(int*)b);
}

int compareDoubles(constVoidPtr a, constVoidPtr b){
	return (*(double*)a - *(double*)b);
}

int compareChars(constVoidPtr a, constVoidPtr b){
	return (*(char*)a - *(char*)b);
}

int compareStrings(constVoidPtr a, constVoidPtr b){
	return strcmp((char*)a, (char*)b);
}


//********************************Integers*******************************
void test_1_search_element_from_the_sorted_collection_integers(){
	int elements[5] = {1,2,3,4,5};
	int key = 4;
	int* result = binarySearch(&key, elements, 5, sizeof(int), compareInt);
	ASSERT(4==*result);
	ASSERT(&elements[3] == result);
};

void test_2_search_element_from_the_sorted_collection_only_2_elements_for_first(){
	int elements[2] = {1,2};
	int key = 1;
	int* result = binarySearch(&key, elements, 2, sizeof(int), compareInt);
	ASSERT(1 == *result);
	ASSERT(&elements[0] == result);
};

void test_3_search_element_from_the_sorted_collection_only_2_elements_for_second(){
	int elements[2] = {1,2};
	int key = 2;
	int* result = binarySearch(&key, elements, 2, sizeof(int), compareInt);
	ASSERT(2 == *result);
	ASSERT(&elements[1] == result);
};

void test_4_search_last_element_in_collection(){
	int elements[7] = {1,2,3,4,5,6,7};
	int key = 7;
	int* result = binarySearch(&key, elements, 7, sizeof(int), compareInt);
	ASSERT(7 == *result);
	ASSERT(&elements[6] == result);
}

void test_5_gives_NULL_if_element_is_not_present(){
	int elements[7] = {1,2,3,4,5,6,7};
	int key = 9;
	int* result = binarySearch(&key, elements, 7, sizeof(int), compareInt);
	ASSERT(NULL == result);
}
//********************************Doubles*******************************

void test_6_search_element_from_the_sorted_collection_doubles(){
	double elements[5] = {1.0,2.0,3.0,4.0,5.0};
	double key = 2.0;
	double* result = binarySearch(&key, elements, 5, sizeof(double), compareDoubles);
	ASSERT(2.0==*result);
	ASSERT(&elements[1] == result);
};

void test_7_search_element_from_the_sorted_collection_only_2_elements_for_first_doubles(){
	double elements[2] = {1.0,2.0};
	double key = 1.0;
	double* result = binarySearch(&key, elements, 2, sizeof(double), compareDoubles);
	ASSERT(1.0 == *result);
	ASSERT(&elements[0] == result);
};

void test_8_search_element_from_the_sorted_collection_only_2_elements_for_second_doubles(){
	double elements[2] = {1.0,2.0};
	double key = 2.0;
	double* result = binarySearch(&key, elements, 2, sizeof(double), compareDoubles);
	ASSERT(2.0 == *result);
	ASSERT(&elements[1] == result);
};

void test_9_search_last_element_in_collection_doubles(){
	double elements[7] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0};
	double key = 7.0;
	double* result = binarySearch(&key, elements, 7, sizeof(double), compareDoubles);
	ASSERT(7.0 == *result);
	ASSERT(&elements[6] == result);
}

void test_10_gives_NULL_if_element_is_not_present_doubles(){
	double elements[7] = {1.0,2.0,3.0,4.0,5.0,6.0,7.0};
	double key = 0.0;
	double* result = binarySearch(&key, elements, 7, sizeof(double), compareDoubles);
	ASSERT(NULL == result);
}

//********************************Characters*******************************

void test_11_search_element_from_the_sorted_collection_Chars(){
	char elements[5] = {'C','a','c','o','w'};
	char key = 'c';
	char* result = binarySearch(&key, elements, 5, sizeof(char), compareChars);
	ASSERT('c'==*result);
	ASSERT(&elements[2] == result);
};

void test_12_search_element_from_the_sorted_collection_only_2_elements_for_first_Chars(){
	char elements[2] = {'s','w'};
	char key = 's';
	char* result = binarySearch(&key, elements, 2, sizeof(char), compareChars);
	ASSERT('s' == *result);
	ASSERT(&elements[0] == result);
};

void test_13_search_element_from_the_sorted_collection_only_2_elements_for_second_Chars(){
	char elements[2] = {'s','w'};
	char key = 'w';
	char* result = binarySearch(&key, elements, 2, sizeof(char), compareChars);
	ASSERT('w' == *result);
	ASSERT(&elements[1] == result);
};

void test_14_search_last_element_in_collection_Chars(){
	char elements[7] = {'e','f','g','h','i','m','p'};
	char key = 'p';
	char* result = binarySearch(&key, elements, 7, sizeof(char), compareChars);
	ASSERT('p' == *result);
	ASSERT(&elements[6] == result);
}

void test_15_gives_NULL_if_element_is_not_present_Chars(){
	char elements[7] = {'W','W','W','W','W','W','p'};
	char key = 'w';
	char* result = binarySearch(&key, elements, 7, sizeof(char), compareChars);
	ASSERT(NULL == result);
}

//********************************Strings*******************************

void test_16_search_element_from_the_sorted_collection_Strings(){
	String elements[5] = {"Ajay","Mahesh","Ramesh","Suresh","Zuresh"};
	char* key = "Suresh";
	char* result = binarySearch(key, elements, 5, sizeof(String), compareStrings);
	ASSERT(0 == strcmp("Suresh", result));
};

void test_17_search_element_from_the_sorted_collection_only_2_elements_for_first_Strings(){
	String elements[2] = {"Digs","Raaz"};
	char* key = "Digs";
	char* result = binarySearch(key, elements, 2, sizeof(String), compareStrings);
	ASSERT(0 == strcmp("Digs", result));
};

void test_18_search_element_from_the_sorted_collection_only_2_elements_for_second_Strings(){
	String elements[2] = {"Digs","Raaz"};
	char* key = "Raaz";
	char* result = binarySearch(key, elements, 2, sizeof(String), compareStrings);
	ASSERT(0 == strcmp("Raaz", result));
};

void test_19_search_last_element_in_collection_Strings(){
	String elements[7] = {"Aniket","Assert","Arora","Mahesh","Queen","aap","ppo"};
	char* key = "ppo";
	char* result = binarySearch(key, elements, 7, sizeof(String), compareStrings);
	ASSERT(0 == strcmp("ppo", result));
}

void test_20_gives_NULL_if_element_is_not_present_Strings(){
	String elements[7] = {"Arm","Barm","Darm","Farm","Garm","Harm","Warm"};
	char* key = "Diff";
	char* result = binarySearch(key, elements, 7, sizeof(String), compareStrings);
	ASSERT(NULL == result);
}

void test_21_gives_the_first_element_which_mached_with_key(){
	char elements[2] = {'s','s'};
	char key = 's';
	char* result = binarySearch(&key, elements, 2, sizeof(char), compareChars);
	ASSERT('s' == *result);
	ASSERT(&elements[0] == result);	
}


//*********************************Sort**************************************
int areArraysEqual(void* arr1,void* arr2,int size){
	return (0==memcmp(arr1, arr2, size));
};

void test_22_sorts_the_elements_in_the_collection_integers(){
	int nums[5] = {12,45,23,56,24};
	int expected[5] = {12,23,24,45,56};
	sortElements(nums, 5, sizeof(int), compareInt);
	ASSERT(areArraysEqual(expected, nums, sizeof(nums)));
}
void test_23_sorts_the_elements_in_the_collection_doubles(){
	double nums[5] = {12.0,45.0,23.0,56.0,24.0};
	double expected[5] = {12.0,23.0,24.0,45.0,56.0};
	sortElements(nums, 5, sizeof(double), compareDoubles);
	ASSERT(areArraysEqual(expected, nums, sizeof(nums)));
}
void test_23_sorts_the_elements_in_the_collection_chars(){
	char chars[5] = {'i','a','o','u','e'};
	char expected[5] = {'a','e','i','o','u'};
	sortElements(chars, 5, sizeof(char), compareChars);
	ASSERT(areArraysEqual(expected, chars, sizeof(chars)));
}
// void test_22_sorts_the_elements_in_the_collection_String(){
// 	String names[5] = {12,45,23,56,24};
// 	String expected[5] = {12,23,24,45,56};
// 	sortElements(names, 5, sizeof(String), compareInt);
// 	ASSERT(areArraysEqual(expected, names, sizeof(names)));
// }