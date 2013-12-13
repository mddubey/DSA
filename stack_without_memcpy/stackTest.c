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

void test_removes_the_top_most_element_from_the_stack_integers(){
	int *nums = malloc(sizeof(int)*4);
	int* result;
	nums[0] = 10;nums[1] = 12;nums[2] = 15;nums[3] = 20;
	stack = create(3);
	push(stack, &nums[0]);
	push(stack, &nums[2]);
	push(stack, &nums[1]);
	push(stack, &nums[3]);
	result = pop(stack);
	ASSERT(20==*result);
	ASSERT(3==stack->top);
};

void test_removes_the_top_most_element_from_the_stack_doubles(){
	double* nums = malloc(sizeof(double)*4);
	double* result;
	nums[0] = 10.0;nums[1] = 12.0;nums[2] = 15.0;nums[3] = 20.0;
	stack = create(3);
	push(stack, &nums[0]);
	push(stack, &nums[2]);
	push(stack, &nums[1]);
	push(stack, &nums[3]);
	result = pop(stack);
	ASSERT(20.0 == *result);
	ASSERT(3 == stack->top);
};

void test_removes_the_top_most_element_from_the_stack_characters(){
	char* chars = malloc(sizeof(char)*4);
	char* result;
	chars[0] = 'a';chars[1] = 'm';chars[2] = 'd';chars[3] = 'k';
	stack = create(3);
	push(stack, &chars[0]);
	push(stack, &chars[2]);
	push(stack, &chars[1]);
	push(stack, &chars[3]);
	result = pop(stack);
	ASSERT('k' == *result);
	ASSERT(3 == stack->top);
};

void test_removes_the_top_most_element_from_the_stack_Strings(){
	String_256* nums = malloc(sizeof(String_256)*2);
	char* result;
	strcpy(nums[0], "Mritunjay");
	strcpy(nums[1], "kartik");
	stack = create(2);
	push(stack, &nums[0]);
	push(stack, &nums[1]);
	result = pop(stack);
	ASSERT(0 == strcmp("kartik", result));
	ASSERT(1 == stack->top);
};

void test_removes_structures_on_the_top_of_stacks(){
	Account* account = malloc(sizeof(Account));
	Account* result;
	account->accNo = 100;account->balance = 1000;
	stack = create(3);
	push(stack, account);
	ASSERT(areAccountsEqual(*account, **(Account**)getElement(stack, 0)));
	result = pop(stack);
	ASSERT(areAccountsEqual(*result, *account));
	ASSERT(0 == stack->top && 3 == stack->length);
}

void test_removes_the_top_most_element_and_adds_one_more_element_at_top(){
	int *nums = malloc(sizeof(int)*4);
	int* result;
	nums[0] = 10;nums[1] = 12;nums[2] = 15;nums[3] = 20;
	stack = create(4);
	push(stack, &nums[0]);
	push(stack, &nums[2]);
	push(stack, &nums[1]);
	push(stack, &nums[3]);
	ASSERT(20 == **(int**)getElement(stack, 3));
	result = (int*)(pop(stack));
	ASSERT(20 == *result);
	push(stack, &nums[1]);
	ASSERT(4==stack->top);
	ASSERT(12 == **(int**)getElement(stack, 3));
};

void test_prevents_to_delete_the_element_if_top_is_zero(){
	void* result;
	stack = create(5);
	result = pop(stack);
	ASSERT(NULL == result);
}

// //******************************************peek******************************

void test_gives_the_top_most_element_from_the_stack_integers(){
	int *nums = malloc(sizeof(int)*4);
	int* result;
	nums[0] = 10;nums[1] = 12;nums[2] = 15;nums[3] = 20;
	stack = create(3);
	push(stack, &nums[0]);
	push(stack, &nums[2]);
	push(stack, &nums[1]);
	push(stack, &nums[3]);
	result = peek(stack);
	ASSERT(20 == *result);
	ASSERT(4 == stack->top);
};

void test_gives_the_top_most_element_from_the_stack_doubles(){
	double* nums = malloc(sizeof(double)*4);
	double* result;
	nums[0] = 10.0;nums[1] = 12.0;nums[2] = 15.0;nums[3] = 20.0;
	stack = create(3);
	push(stack, &nums[0]);
	push(stack, &nums[2]);
	push(stack, &nums[1]);
	push(stack, &nums[3]);
	result = peek(stack);
	ASSERT(20.0 == *result);
	ASSERT(4 == stack->top);
};

void test_gives_the_top_most_element_from_the_stack_characters(){
	char* chars = malloc(sizeof(char)*4);
	char* result;
	chars[0] = 'a';chars[1] = 'm';chars[2] = 'd';chars[3] = 'k';
	stack = create(3);
	push(stack, &chars[0]);
	push(stack, &chars[2]);
	push(stack, &chars[1]);
	push(stack, &chars[3]);
	result = peek(stack);
	ASSERT('k' == *result);
	ASSERT(4 == stack->top);
};

void test_gives_the_top_most_element_from_the_stack_Strings(){
	String_256* nums = malloc(sizeof(String_256)*2);
	char* result;
	strcpy(nums[0], "Mritunjay");
	strcpy(nums[1], "kartik");
	stack = create(2);
	push(stack, &nums[0]);
	push(stack, &nums[1]);
	result = peek(stack);
	ASSERT(0 == strcmp("kartik", result));
	ASSERT(2 == stack->top);
};

void test_gives_structures_on_the_top_of_stacks(){
	Account* account = malloc(sizeof(Account));
	Account* result;
	account->accNo = 100;account->balance = 1000;
	stack = create(3);
	push(stack, account);
	ASSERT(areAccountsEqual(*account, **(Account**)getElement(stack, 0)));
	result = peek(stack);
	ASSERT(areAccountsEqual(*result, *account));
	ASSERT(1 == stack->top && 3 == stack->length);
}

void test_prevents_to_access_the_element_if_top_is_zero(){
	void* result;
	stack = create(5);
	result = peek(stack);
	ASSERT(NULL == result);
}

// //***********************************isEmpty*****************

void test_21_tells_the_stack_is_empty_integers(){
	int result;
	stack = create(5);
	result = isEmpty(stack);
	ASSERT(1==result);
}

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

// void test_29_gives_the_top_most_structure_from_stack(){
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