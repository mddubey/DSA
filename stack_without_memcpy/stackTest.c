#include <memory.h>
#include <stdlib.h>
#include "stack.h"
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

Stack* stack;

void tearDown(){
	free(stack->elements);
	free(stack);
}

typedef struct {
	int accNo;
	int balance;
}Account;

int areAccountsEqual(Account expected,Account actual){
	return expected.accNo == actual.accNo && expected.balance == actual.balance;
}

int areEqual(Stack a, Stack b){
	int result = a.length == b.length && a.top == b.top;
	if(!result) return result;
	return 0 == memcmp(a.elements,b.elements,a.length*sizeof(void*));
}

//**********************************Create Tests*************************************

void test_creates_a_stack_for_with_given_length (){
	void* Nulls[3] = {NULL,NULL,NULL};
	Stack expected = {Nulls,0,3};
	stack = create(3);
	ASSERT(areEqual(expected, *stack));
};

//**************************************push***********************************

void test_adds_the_given_integer_at_the_top_of_the_stack(){
	int* num = malloc(sizeof(int));
	*num = 12;
	stack = create(1);
	push(stack, num);
	ASSERT(12 == **(int**)stack->elements);
	ASSERT(1 == stack->top && 1 == stack->length);
}

void test_adds_the_given_doubles_at_the_top_of_the_stack(){
	double *nums = malloc(sizeof(double)*2);
	nums[0] = 12.0;nums[1] = 10.0;
	stack = create(2);
	push(stack, &nums[0]);
	push(stack, &nums[1]);
	ASSERT(12.0 == **(double**)getElement(stack, 0));
	ASSERT(10.0 == **(double**)getElement(stack, 1));
	ASSERT(2 == stack->top && 2 == stack->length);
}

void test_adds_the_given_characters_at_the_top_of_the_stack(){
	char* chars = malloc(sizeof(char)*2);
	chars[0] = 'a';
	chars[1] = 'm';
	stack = create(3);
	push(stack, &chars[0]);
	push(stack, &chars[1]);
	ASSERT('a' == **(char**)getElement(stack, 0));
	ASSERT('m' == **(char**)getElement(stack, 1));
	ASSERT(2 == stack->top && 3 == stack->length);
}

void test_adds_the_given_Strings_at_the_top_of_the_stack(){
	String_256* names = malloc(sizeof(String_256)*2);
	strcpy(names[0], "Digs");
	strcpy(names[1], "Raaz");
	stack = create(2);
	push(stack, &names[0]);
	push(stack, &names[1]);
	ASSERT(0 == strcmp(names[0], *(char**)getElement(stack, 0)));
	ASSERT(0 == strcmp(names[1], *(char**)getElement(stack, 1)));
}

void test_adds_structures_on_the_top_of_stacks(){
	Account* account = malloc(sizeof(Account));
	account->accNo = 100;account->balance = 1000;
	stack = create(3);
	push(stack, account);
	ASSERT(areAccountsEqual(*account, **(Account**)getElement(stack, 0)));
	ASSERT(1 == stack->top && 3 == stack->length);
}

void test_doubles_the_length_of_stack_if_stack_is_full(){
	int *nums = malloc(sizeof(int)*3);
	int result;
	nums[0] = 10;nums[1] = 12;nums[2] = 15;
	stack = create(3);
	push(stack, &nums[0]);
	push(stack, &nums[2]);
	push(stack, &nums[1]);
	ASSERT(3 == stack->length);
	result = push(stack, &nums[0]);
	ASSERT(1 == result);
	ASSERT(6 == stack->length);
	ASSERT(4 == stack->top);
	ASSERT(10 == **(int**)getElement(stack, 3));
}

// //***************************pop***********************************************

// void test_10_removes_the_top_most_element_from_the_stack_integers(){
// 	int _4_nums[4] = {12,14,45,78};
// 	int *result;
// 	stack = create(4, sizeof(int));
// 	memcpy(stack->elements,_4_nums,4*sizeof(int));
// 	stack->top = 4;
// 	result = (int*)(pop(stack));
// 	ASSERT(78==*result);
// 	ASSERT(3==stack->top);
// };

// void test_11_removes_the_top_most_element_from_the_stack_doubles(){
// 	double _4_nums[4] = {12.14,14.96,45.25,4478.14};
// 	double *result;
// 	stack = create(4, sizeof(double));
// 	memcpy(stack->elements,_4_nums,4*sizeof(double));
// 	stack->top = 4;
// 	result = (double*)(pop(stack));
// 	ASSERT(4478.14==*result);
// 	ASSERT(3==stack->top);
// };

// void test_12_removes_the_top_most_element_from_the_stack_characters(){
// 	char _4_chars[4] = {'m','d','a','k'};
// 	char *result;
// 	stack = create(4, sizeof(char));
// 	memcpy(stack->elements,_4_chars,4*sizeof(char));
// 	stack->top = 4;
// 	result = (char*)(pop(stack));
// 	ASSERT('k'==*result);
// 	ASSERT(3==stack->top);
// };

// void test_13_removes_the_top_most_element_from_the_stack_Strings(){
// 	String_256 _4_chars[4] = {"mritunjay","dubey","aniket","kartik"};
// 	char* result;
// 	String_256 expected = "kartik";
// 	stack = create(4, sizeof(String_256));
// 	memcpy(stack->elements,_4_chars,4*sizeof(String_256));
// 	stack->top = 4;
// 	result = (char*)(pop(stack));
// 	ASSERT(0==strcmp(result, expected));
// 	ASSERT(3==stack->top);
// };

// void test_14_removes_the_top_most_element_and_adds_one_more_element_at_top(){
// 	int _3_nums[3] = {12,14,45};
// 	int _4_nums[4] = {12,14,45,78};
// 	int _res_4_nums[4] = {12,14,45,1000};
// 	int _1000 = 1000;
// 	int *result;
// 	Stack expected = {_res_4_nums,4,4,sizeof(int)};
// 	stack = create(4, sizeof(int));
// 	memcpy(stack->elements,_4_nums,4*sizeof(int));
// 	stack->top = 4;
// 	result = (int*)(pop(stack));
// 	ASSERT(78==*result);
// 	push(stack, &_1000);
// 	ASSERT(areEqual(expected, *stack));
// 	ASSERT(4==stack->top);
// };

// void test_15_prevents_to_delete_the_element_if_top_is_zero(){
// 	void* result;
// 	stack = create(5, sizeof(int));
// 	result = pop(stack);
// 	ASSERT(NULL == result);
// }

// //******************************************peek******************************

// void test_16_gives_the_top_most_element_of_stack_integers(){
// 	int *result;
// 	int _3_nums[3] = {14,58,17};
// 	stack = create(5, sizeof(int));
// 	stack->top = 3;
// 	memcpy(stack->elements, _3_nums, 3*stack->elementSize);
// 	result = (int*)peek(stack);
// 	ASSERT(17==*result);
// 	ASSERT(3==stack->top);
// };

// void test_17_gives_the_top_most_element_of_stack_doubles(){
// 	double *result;
// 	double _3_nums[3] = {14.25,58.4,17.0458};
// 	stack = create(5, sizeof(double));
// 	stack->top = 3;
// 	memcpy(stack->elements, _3_nums, 3*stack->elementSize);
// 	result = (double*)peek(stack);
// 	ASSERT(17.0458==*result);
// 	ASSERT(3==stack->top);
// };

// void test_18_gives_the_top_most_element_of_stack_characters(){
// 	char *result;
// 	char _3_chars[3] = {'m','m','p'};
// 	stack = create(5, sizeof(char));
// 	stack->top = 3;
// 	memcpy(stack->elements, _3_chars, 3*stack->elementSize);
// 	result = (char*)peek(stack);
// 	ASSERT('p'==*result);
// 	ASSERT(3==stack->top);
// };

// void test_19_gives_the_top_most_element_of_stack_String(){
// 	char* result;
// 	String_256 _3_names[3] = {"manish","mritunjay","prateek"};
// 	String_256 expected = "prateek";
// 	stack = create(5, sizeof(String_256));
// 	stack->top = 3;
// 	memcpy(stack->elements, _3_names, 3*stack->elementSize);
// 	result = (char*)peek(stack);
// 	ASSERT(0==strcmp(expected, result));
// 	ASSERT(3==stack->top);
// };

// void test_20_prevents_to_search_the_top_element_if_top_is_zero(){
// 	void* result;
// 	stack = create(5, sizeof(int));
// 	result = peek(stack);
// 	ASSERT(NULL == result);
// }

// //***********************************isEmpty*****************

// void test_21_tells_the_stack_is_empty_integers(){
// 	int result;
// 	stack = create(5, sizeof(int));
// 	result = isEmpty(stack);
// 	ASSERT(1==result);
// }
// void test_22_tells_the_stack_is_empty_strings(){
// 	int result;
// 	stack = create(5, sizeof(String_256));
// 	result = isEmpty(stack);
// 	ASSERT(1==result);
// }
// void test_23_tells_the_stack_is_not_empty(){
// 	int result;
// 	stack = create(5, sizeof(int));
// 	*(int*)stack->elements = 15;
// 	stack->top = 1;
// 	result = isEmpty(stack);
// 	ASSERT(0==result);
// }

// //****************************isFull**********************

// void test_24_tells_the_stack_is_full_integers(){
// 	int result;
// 	stack = create(1, sizeof(int));
// 	*(int*)stack->elements = 15;
// 	stack->top = 1;
// 	result = isFull(stack);
// 	ASSERT(1==result);
// }

// void test_25_tells_the_stack_is_full_Strings(){
// 	int result;
// 	stack = create(1, sizeof(String_256));
// 	strcpy(stack->elements, "Mritunjay");
// 	stack->top = 1;
// 	result = isFull(stack);
// 	ASSERT(1==result);
// }

// void test_26_tells_the_stack_is_not_full_Strings(){
// 	int result;
// 	stack = create(4, sizeof(String_256));
// 	strcpy(stack->elements, "Mritunjay");
// 	stack->top = 1;
// 	result = isFull(stack);
// 	ASSERT(0==result);
// }

// //*****************************Structure*******************************
// typedef struct{
// 	int roll;
// 	char name[18];
// }Class;

// void test_27_creates_a_stack_for_structure(){
// 	Class studs[1] = {{0,""}};
// 	Stack expected = {studs,0,1,sizeof(Class)};
// 	stack = create(1, sizeof(Class));
// 	ASSERT(areEqual(expected, *stack));

// };

// void test_28_adds_structure_on_top_of_stack(){
// 	Class studs[2] = {{1,"Raj"},{2,"Digs"}};
// 	Class rajStud = {1,"Raj"};
// 	Class digStud = {2,"Digs"};
// 	Stack expected = {studs,2,2,sizeof(Class)};
// 	stack = create(2, sizeof(Class));
// 	push(stack, &rajStud);
// 	push(stack, &digStud);
// 	ASSERT(areEqual(expected, *stack));
// };

// void test_29_removes_the_top_most_structure_from_stack(){
// 	Class studs[2] = {{1,"Raj"},{2,"Digs"}};
// 	Class* result;
// 	Class rajStud = {1,"Raj"};
// 	Class digStud = {2,"Digs"};
// 	stack = create(2, sizeof(Class));
// 	memcpy(stack->elements, studs, sizeof(Class)*2);
// 	stack->top = 2;
// 	result = pop(stack);
// 	ASSERT(0==memcmp(&digStud, result, sizeof(Class)));
// 	ASSERT(1==stack->top);
// 	result = pop(stack);
// 	ASSERT(0==memcmp(&rajStud, result, sizeof(Class)));
// 	ASSERT(0==stack->top);
// 	result = pop(stack);
// 	ASSERT(NULL == result);
// 	ASSERT(0==stack->top);
// };

// void test_30_gives_the_top_most_element_of_the_stack(){
// 	Class studs[2] = {{1,"Raj"},{2,"Digs"}};
// 	Class* result;
// 	Class rajStud = {1,"Raj"};
// 	Class digStud = {2,"Digs"};
// 	stack = create(2, sizeof(Class));
// 	memcpy(stack->elements, studs, sizeof(Class)*2);
// 	stack->top = 2;
// 	result = peek(stack);
// 	ASSERT(0==memcmp(&digStud, result, sizeof(Class)));
// 	ASSERT(2==stack->top);
// };