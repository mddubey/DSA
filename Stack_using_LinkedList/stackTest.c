#include "stack.h"
#include <stdlib.h>
#include <string.h>
#include "testUtils.h"
#include "../customTypes.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed
Stack* stack;
void tearDown(){
	disposeStack(stack);
}

typedef struct{
	int accNo;
	int balance;
}Account;

int areAccountsEqual(Account expected, Account actual){
	return expected.accNo == actual.accNo && expected.balance == actual.balance;
}


void test_creates_an_stack(){
	stack = createStack();
	ASSERT(0 == stack->list->length);
	ASSERT(0x0 == stack->list->head);
}

//********************************************PUSH********************************

void test_adds_a_new_element_in_the_stack(){
	int* nums = malloc(sizeof(int));
	int res;
	*nums = 10;
	stack = createStack();
	res = push(stack, nums);
	ASSERT(1 == res);
	ASSERT(1 == stack->list->length);
	ASSERT(10 == *(int*)stack->list->head->data);
}

void test_adds_a_new_element_in_the_stack_doubles(){
	double* nums = malloc(sizeof(double)*2);
	Node* node;
	nums[0] = 10.0;nums[1] = 15.0;
	stack = createStack();
	push(stack, &nums[0]);
	push(stack, &nums[1]);
	node = stack->list->head;
	ASSERT(10.0 == *(double*)node->data);
	node = node->next;
	ASSERT(15.0 == *(double*)node->data);
	ASSERT(2 == stack->list->length);
}

void test_adds_a_new_element_in_the_stack_chars(){
	char* chars = malloc(sizeof(char)*2);
	Node* node;
	chars[0] = 'm';chars[1] = 'a';
	stack = createStack();
	push(stack, &chars[0]);
	push(stack, &chars[1]);
	node = stack->list->head;
	ASSERT('m' == *(char*)node->data);
	node = node->next;
	ASSERT('a' == *(char*)node->data);
	ASSERT(2 == stack->list->length);
}

void test_adds_a_new_element_in_the_stack_String(){
	String* names = malloc(sizeof(String)*2);
	Node* node;
	strcpy(names[0],"Raaz");
	strcpy(names[1],"Digs");
	stack = createStack();
	push(stack, &names[0]);
	push(stack, &names[1]);
	node = stack->list->head;
	ASSERT(0 == strcmp("Raaz", *(String*)node->data));
	node = node->next;
	ASSERT(0 == strcmp("Digs", *(String*)node->data));
	ASSERT(2 == stack->list->length);
}

void test_adds_a_new_element_in_the_stack_Structure(){
	Account* accounts = malloc(sizeof(Account)*2);
	Node* node;
	accounts[0].accNo = 100;accounts[0].balance = 1000;
	accounts[1].accNo = 111;accounts[1].balance = 1111;
	stack = createStack();
	push(stack, &accounts[0]);
	push(stack, &accounts[1]);
	node = stack->list->head;
	ASSERT(areAccountsEqual(accounts[0], *(Account*)node->data));
	node = node->next;
	ASSERT(areAccountsEqual(accounts[1], *(Account*)node->data));
	ASSERT(2 == stack->list->length);
}

//********************************************POP********************************

void test_removes_single_element_from_stack(){
	int* nums = malloc(sizeof(int));
	int res;
	*nums = 10;
	stack = createStack();
	push(stack, nums);
	res = pop(stack);
	ASSERT(res == 1);
	ASSERT(0 == stack->list->length);
	ASSERT(NULL == stack->list->head);
}

void test_removes_the_top_element_from_stack_doubles(){
	double* nums = malloc(sizeof(double)*2);
	Node* node;
	nums[0] = 10.0;nums[1] = 15.0;
	stack = createStack();
	push(stack, &nums[0]);
	push(stack, &nums[1]);
	pop(stack);
	node = stack->list->head;
	ASSERT(10.0 == *(double*)node->data);
	ASSERT(1 == stack->list->length);
	ASSERT(NULL == node->next);
}

void test_removes_the_top_element_from_stack_chars(){
	char* chars = malloc(sizeof(char)*2);
	Node* node;
	chars[0] = 'm';chars[1] = 'a';
	stack = createStack();
	push(stack, &chars[0]);
	push(stack, &chars[1]);
	pop(stack);
	node = stack->list->head;
	ASSERT('m' == *(char*)node->data);
	ASSERT(NULL == node->next);
	ASSERT(1 == stack->list->length);
}

void test_removes_the_top_element_from_stack_String(){
	String* names = malloc(sizeof(String)*2);
	Node* node;
	strcpy(names[0],"Raaz");
	strcpy(names[1],"Digs");
	stack = createStack();
	push(stack, &names[0]);
	push(stack, &names[1]);
	pop(stack);
	node = stack->list->head;
	ASSERT(0 == strcmp("Raaz", *(String*)node->data));
	ASSERT(NULL == node->next);
	ASSERT(1 == stack->list->length);
}

void test_removes_the_top_element_from_stack_Structure(){
	Account* accounts = malloc(sizeof(Account)*2);
	Node* node;
	accounts[0].accNo = 100;accounts[0].balance = 1000;
	accounts[1].accNo = 111;accounts[1].balance = 1111;
	stack = createStack();
	push(stack, &accounts[0]);
	push(stack, &accounts[1]);
	node = stack->list->head;
	ASSERT(areAccountsEqual(accounts[0], *(Account*)node->data));
	node = node->next;
	ASSERT(areAccountsEqual(accounts[1], *(Account*)node->data));
	pop(stack);
	pop(stack);
	ASSERT(NULL == stack->list->head);
	ASSERT(0 == stack->list->length);
}

void test_prevents_in_deletion_if_stack_is_empty(){
	double* nums = malloc(sizeof(double)*2);
	int res;
	nums[0] = 10.0;nums[1] = 15.0;
	stack = createStack();
	push(stack, &nums[0]);
	push(stack, &nums[1]);
	res = pop(stack);
	ASSERT(res == 1);
	res = pop(stack);
	ASSERT(res == 1);
	res = pop(stack);
	ASSERT(res == 0);
	ASSERT(NULL == stack->list->head);
	ASSERT(0 == stack->list->length);
}

//***************************peek*****************************************
void test_gives_single_element_from_top_of_stack(){
	int* nums = malloc(sizeof(int));
	int* res;
	*nums = 10;
	stack = createStack();
	push(stack, nums);
	res = peek(stack);
	ASSERT(*res == 10);
	ASSERT(1 == stack->list->length);
}

void test_gives_the_top_element_from_stack_doubles(){
	double* nums = malloc(sizeof(double)*2);
	double* result;
	nums[0] = 10.0;nums[1] = 15.0;
	stack = createStack();
	push(stack, &nums[0]);
	push(stack, &nums[1]);
	result = peek(stack);
	ASSERT(15.0 == *result);
	ASSERT(2 == stack->list->length);
}

void test_gives_the_top_element_from_stack_chars(){
	char* chars = malloc(sizeof(char)*2);
	char* result;
	chars[0] = 'm';chars[1] = 'a';
	stack = createStack();
	push(stack, &chars[0]);
	push(stack, &chars[1]);
	result = peek(stack);
	ASSERT('a' == *result);
	ASSERT(2 == stack->list->length);
}

void test_gives_the_top_element_from_stack_String(){
	String* names = malloc(sizeof(String)*2);
	String* result;
	strcpy(names[0],"Raaz");
	strcpy(names[1],"Digs");
	stack = createStack();
	push(stack, &names[0]);
	push(stack, &names[1]);
	result = peek(stack);
	ASSERT(0 == strcmp("Digs", *result));
	ASSERT(2 == stack->list->length);
}

void test_gives_the_top_element_from_stack_Structure(){
	Account* accounts = malloc(sizeof(Account)*2);
	Account* result;
	accounts[0].accNo = 100;accounts[0].balance = 1000;
	accounts[1].accNo = 111;accounts[1].balance = 1111;
	stack = createStack();
	push(stack, &accounts[0]);
	push(stack, &accounts[1]);
	result = peek(stack);
	ASSERT(areAccountsEqual(accounts[1], *result));
	ASSERT(2 == stack->list->length);
}

//********************************* isEmpty**********************

void test_tells_the_stack_is_not_empty(){
	int* nums = malloc(sizeof(int));
	int res;
	*nums = 10;
	stack = createStack();
	push(stack, nums);
	res = isEmpty(stack);
	ASSERT(res == 0);
	ASSERT(1 == stack->list->length);
}

void test_tells_the_stack_is_empty(){
	int res;
	stack = createStack();
	res = isEmpty(stack);
	ASSERT(res == 1);
	ASSERT(0 == stack->list->length);
}