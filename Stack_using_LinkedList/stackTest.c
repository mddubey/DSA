#include "stack.h"
#include <stdlib.h>
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed
Stack* stack;
void tearDown(){
	disposeStack(stack);
}


void test_creates_an_stack(){
	stack = createStack();
	ASSERT(0 == stack->list->length);
	ASSERT(0x0 == stack->list->head);
}

void test_adds_a_new_element_in_the_stack(){
	int* nums = malloc(sizeof(int));
	int res;
	stack = createStack();
	res = push(stack, nums);
	ASSERT(1 == res);
	ASSERT(10 == *(int*)stack->list->head->data);
}
