#include "isort.h"
#include <string.h>
#include "testUtils.h"
#include "../customTypes.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

typedef struct {
	int accountNumber;
	int balance;
} Account;

int compareAccountsByAccountNumber(void* first, void* second) {
	Account* firstAccount = (Account*)first;
	Account* secondAccount = (Account*)second;
	return firstAccount->accountNumber - secondAccount->accountNumber;
}

int compareAccountsByBalance(void* first, void* second) {
	Account* firstAccount = (Account*)first;
	Account* secondAccount = (Account*)second;
	return firstAccount->balance - secondAccount->balance;
}

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

void test_sorts_collections_of_Doubles_(){
	double nums[5] = {1.0,1.5,1.7,2.0,5.0};
	void* ptrs[5] = {(nums+3),(nums+1),(nums+4),(nums+2),(nums)};
	void* expected[5] = {(nums+0),(nums+1),(nums+2),(nums+3),(nums+4)};
	isort(ptrs, 5, sizeof(double), compareDoubles);
	ASSERT(areArrayEqual(ptrs, expected, 5));
}

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

void test_sorts_collections_of_String(){
	String names[5] = {"Raaj","Raam","Raaz","Rahul","Rajan"};
	void* ptrs[5] = {(names+3),(names+1),(names+4),(names+2),(names)};
	void* expected[5] = {(names+0),(names+1),(names+2),(names+3),(names+4)};
	isort(ptrs, 5, sizeof(String), compareStrings);
	ASSERT(areArrayEqual(ptrs, expected, 5));
}

void test_sorts_collection_of_Accounts_according_to_account_number(){
	Account accounts[] = {{12, 10} , {23,1200}, {33, 10000}, {40, 3}, {100, 100}};
	void* ptrs[5] = {(accounts+3),(accounts+1),(accounts+4),(accounts+2),(accounts)};
	void* expected[5] = {(accounts+0),(accounts+1),(accounts+2),(accounts+3),(accounts+4)};
	isort(ptrs, 5, sizeof(String), compareStrings);
	ASSERT(areArrayEqual(ptrs, expected, 5));
}

void test_sorts_collection_of_Accounts_according_to_balance(){
	Account accounts[] = {{40, 3}, {12, 10}, {100, 100} , {23,1200}, {33, 10000}};
	void* ptrs[5] = {(accounts+3),(accounts+1),(accounts+4),(accounts+2),(accounts)};
	void* expected[5] = {(accounts+0),(accounts+1),(accounts+2),(accounts+3),(accounts+4)};
	isort(ptrs, 5, sizeof(String), compareStrings);
	ASSERT(areArrayEqual(ptrs, expected, 5));
}


