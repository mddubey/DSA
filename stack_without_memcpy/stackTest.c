#include <memory.h>
#include <stdlib.h>
#include "stack.h"
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

void* stack;
typedef char String_256[256];

void tearDown(){
	disposeStack(stack);
}

typedef struct {
	int accNo;
	int balance;
}Account;

int areAccountsEqual(Account expected,Account actual){
	return expected.accNo == actual.accNo && expected.balance == actual.balance;
}

// int areEqual(Stack a, Stack b){
// 	int result = a.length == b.length && a.top == b.top;
// 	if(!result) return result;
// 	return 0 == memcmp(a.elements,b.elements,a.length*sizeof(void*));
// }

//**********************************Create Tests*************************************

// void test_creates_a_stack_for_with_given_length (){
// 	void* Nulls[3] = {NULL,NULL,NULL};
// 	Stack expected = {Nulls,0,3};
// 	stack = create(3);
// 	ASSERT(areEqual(expected, *stack));
// };

//**************************************push***********************************

void test_adds_the_given_integer_at_the_top_of_the_stack(){
	int num = 12;
	int res;
	stack = create(1);
	res = push(stack, &num);
	ASSERT(1 == res);
}

void test_adds_the_given_doubles_at_the_top_of_the_stack(){
	double nums[2] = {12.0,10.0};
	int res;
	stack = create(2);
	res = push(stack, &nums[0]);
	ASSERT(1 == res);
	res = push(stack, &nums[1]);
	ASSERT(1 == res);
}

void test_adds_the_given_characters_at_the_top_of_the_stack(){
	char chars[2] = {'a','m'};
	int res;
	stack = create(3);
	res = push(stack, &chars[0]);
	ASSERT(1 == res);
	res = push(stack, &chars[1]);
	ASSERT(1 == res);
}

void test_adds_the_given_Strings_at_the_top_of_the_stack(){
	String_256 names[2] = {"Digs","Raaz...."};
	int res;
	stack = create(2);
	res = push(stack, &names[0]);
	ASSERT(1 == res);
	res = push(stack, &names[1]);
	ASSERT(1 == res);
}

void test_adds_structures_on_the_top_of_stacks(){
	Account account = {100,1000};
	int res;
	stack = create(3);
	res = push(stack, &account);
	ASSERT(res == 1);
}

void test_doubles_the_length_of_stack_if_stack_is_full(){
	int nums[4] = {10,20,30,40};
	int result;
	stack = create(3);
	push(stack, &nums[0]);
	push(stack, &nums[2]);
	push(stack, &nums[1]);
	result = push(stack, &nums[3]);
	ASSERT(1 == result);
}

// //***************************pop***********************************************

// void test_removes_the_top_most_element_from_the_stack_integers(){
// 	int *nums = malloc(sizeof(int)*4);
// 	int* result;
// 	nums[0] = 10;nums[1] = 12;nums[2] = 15;nums[3] = 20;
// 	stack = create(3);
// 	push(stack, &nums[0]);
// 	push(stack, &nums[2]);
// 	push(stack, &nums[1]);
// 	push(stack, &nums[3]);
// 	result = pop(stack);
// 	ASSERT(20==*result);
// 	ASSERT(3==stack->top);
// };

// void test_removes_the_top_most_element_from_the_stack_doubles(){
// 	double* nums = malloc(sizeof(double)*4);
// 	double* result;
// 	nums[0] = 10.0;nums[1] = 12.0;nums[2] = 15.0;nums[3] = 20.0;
// 	stack = create(3);
// 	push(stack, &nums[0]);
// 	push(stack, &nums[2]);
// 	push(stack, &nums[1]);
// 	push(stack, &nums[3]);
// 	result = pop(stack);
// 	ASSERT(20.0 == *result);
// 	ASSERT(3 == stack->top);
// };

// void test_removes_the_top_most_element_from_the_stack_characters(){
// 	char* chars = malloc(sizeof(char)*4);
// 	char* result;
// 	chars[0] = 'a';chars[1] = 'm';chars[2] = 'd';chars[3] = 'k';
// 	stack = create(3);
// 	push(stack, &chars[0]);
// 	push(stack, &chars[2]);
// 	push(stack, &chars[1]);
// 	push(stack, &chars[3]);
// 	result = pop(stack);
// 	ASSERT('k' == *result);
// 	ASSERT(3 == stack->top);
// };

// void test_removes_the_top_most_element_from_the_stack_Strings(){
// 	String_256* nums = malloc(sizeof(String_256)*2);
// 	char* result;
// 	strcpy(nums[0], "Mritunjay");
// 	strcpy(nums[1], "kartik");
// 	stack = create(2);
// 	push(stack, &nums[0]);
// 	push(stack, &nums[1]);
// 	result = pop(stack);
// 	ASSERT(0 == strcmp("kartik", result));
// 	ASSERT(1 == stack->top);
// };

// void test_removes_structures_on_the_top_of_stacks(){
// 	Account* account = malloc(sizeof(Account));
// 	Account* result;
// 	account->accNo = 100;account->balance = 1000;
// 	stack = create(3);
// 	push(stack, account);
// 	ASSERT(areAccountsEqual(*account, **(Account**)getElement(stack, 0)));
// 	result = pop(stack);
// 	ASSERT(areAccountsEqual(*result, *account));
// 	ASSERT(0 == stack->top && 3 == stack->length);
// }

// void test_removes_the_top_most_element_and_adds_one_more_element_at_top(){
// 	int *nums = malloc(sizeof(int)*4);
// 	int* result;
// 	nums[0] = 10;nums[1] = 12;nums[2] = 15;nums[3] = 20;
// 	stack = create(4);
// 	push(stack, &nums[0]);
// 	push(stack, &nums[2]);
// 	push(stack, &nums[1]);
// 	push(stack, &nums[3]);
// 	ASSERT(20 == **(int**)getElement(stack, 3));
// 	result = (int*)(pop(stack));
// 	ASSERT(20 == *result);
// 	push(stack, &nums[1]);
// 	ASSERT(4==stack->top);
// 	ASSERT(12 == **(int**)getElement(stack, 3));
// };

// void test_prevents_to_delete_the_element_if_top_is_zero(){
// 	void* result;
// 	stack = create(5);
// 	result = pop(stack);
// 	ASSERT(NULL == result);
// }

// //******************************************peek******************************

// void test_gives_the_top_most_element_from_the_stack_integers(){
// 	int *nums = malloc(sizeof(int)*4);
// 	int* result;
// 	nums[0] = 10;nums[1] = 12;nums[2] = 15;nums[3] = 20;
// 	stack = create(3);
// 	push(stack, &nums[0]);
// 	push(stack, &nums[2]);
// 	push(stack, &nums[1]);
// 	push(stack, &nums[3]);
// 	result = peek(stack);
// 	ASSERT(20 == *result);
// 	ASSERT(4 == stack->top);
// };

// void test_gives_the_top_most_element_from_the_stack_doubles(){
// 	double* nums = malloc(sizeof(double)*4);
// 	double* result;
// 	nums[0] = 10.0;nums[1] = 12.0;nums[2] = 15.0;nums[3] = 20.0;
// 	stack = create(3);
// 	push(stack, &nums[0]);
// 	push(stack, &nums[2]);
// 	push(stack, &nums[1]);
// 	push(stack, &nums[3]);
// 	result = peek(stack);
// 	ASSERT(20.0 == *result);
// 	ASSERT(4 == stack->top);
// };

// void test_gives_the_top_most_element_from_the_stack_characters(){
// 	char* chars = malloc(sizeof(char)*4);
// 	char* result;
// 	chars[0] = 'a';chars[1] = 'm';chars[2] = 'd';chars[3] = 'k';
// 	stack = create(3);
// 	push(stack, &chars[0]);
// 	push(stack, &chars[2]);
// 	push(stack, &chars[1]);
// 	push(stack, &chars[3]);
// 	result = peek(stack);
// 	ASSERT('k' == *result);
// 	ASSERT(4 == stack->top);
// };

// void test_gives_the_top_most_element_from_the_stack_Strings(){
// 	String_256* nums = malloc(sizeof(String_256)*2);
// 	char* result;
// 	strcpy(nums[0], "Mritunjay");
// 	strcpy(nums[1], "kartik");
// 	stack = create(2);
// 	push(stack, &nums[0]);
// 	push(stack, &nums[1]);
// 	result = peek(stack);
// 	ASSERT(0 == strcmp("kartik", result));
// 	ASSERT(2 == stack->top);
// };

// void test_gives_structures_on_the_top_of_stacks(){
// 	Account* account = malloc(sizeof(Account));
// 	Account* result;
// 	account->accNo = 100;account->balance = 1000;
// 	stack = create(3);
// 	push(stack, account);
// 	ASSERT(areAccountsEqual(*account, **(Account**)getElement(stack, 0)));
// 	result = peek(stack);
// 	ASSERT(areAccountsEqual(*result, *account));
// 	ASSERT(1 == stack->top && 3 == stack->length);
// }

// void test_prevents_to_access_the_element_if_top_is_zero(){
// 	void* result;
// 	stack = create(5);
// 	result = peek(stack);
// 	ASSERT(NULL == result);
// }

// //***********************************isEmpty*****************

// void test_tells_the_stack_is_empty_integers(){
// 	int result;
// 	stack = create(5);
// 	result = isEmpty(stack);
// 	ASSERT(1 == result);
// }

// void test_tells_the_stack_is_not_empty(){
// 	int result;
// 	stack = create(5);
// 	*(int*)stack->elements = 15;
// 	stack->top = 1;
// 	result = isEmpty(stack);
// 	ASSERT(0 == result);
// }

// //****************************isFull**********************

// void test_tells_the_stack_is_full_integers(){
// 	int* num = malloc(sizeof(int));
// 	int result;
// 	stack = create(1);
// 	*num = 15;
// 	push(stack, num);
// 	result = isFull(stack);
// 	ASSERT(1==result);
// }

// void test_tells_the_stack_is_not_full(){
// 	int result;
// 	stack = create(4);
// 	result = isFull(stack);
// 	ASSERT(0 == result);
// }