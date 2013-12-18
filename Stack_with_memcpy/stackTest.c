#include <memory.h>
#include <stdlib.h>
#include "stack.h"
#include "testUtils.h"
#include "../customTypes.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

Stack* stack;

void tearDown(){
	free(stack->elements);
	free(stack);
}

int areEqual(Stack a, Stack b){
	int result = a.length == b.length && a.top == b.top && a.elementSize == b.elementSize;
	if(!result) return result;
	return 0 == memcmp(a.elements,b.elements,a.length*a.elementSize);
}

//**********************************Create Tests*************************************

void test_creates_a_stack_for_integer_elements_with_default_value_zero (){
	int a[3] = {0,0,0};
	Stack expected = {a,0,3,sizeof(int)};
	stack = create(3, sizeof(int));
	ASSERT(areEqual(expected, *stack));
};

void test_creates_a_stack_for_doubles_elements_with_default_value_zero (){
	double a[3] = {0.0,0.0,0.0};
	Stack expected = {a,0,3,sizeof(double)};
	stack = create(3, sizeof(double));
	ASSERT(areEqual(expected, *stack));
};

void test_creates_a_stack_for_Chars_elements_with_default_value_Null (){
	char a[3] = {'\0','\0','\0'};
	Stack expected = {a,0,3,sizeof(char)};
	stack = create(3, sizeof(char));
	ASSERT(areEqual(expected, *stack));
};
void test_creates_a_stack_for_Strings_elements_with_default_value_blank (){
	String name[3] = {"","",""};
	Stack expected = {name,0,3,sizeof(String)};
	stack = create(3, sizeof(String));
	ASSERT(areEqual(expected, *stack));
};

//**************************************push***********************************

void test_adds_the_given_integer_at_the_top_of_the_stack(){
	int a[1] = {12};
	int _12 = 12;
	Stack expected = {a,1,1,sizeof(int)};
	stack = create(1, sizeof(int));
	push(stack, &_12);
	ASSERT(areEqual(expected, *stack));
}

void test_adds_the_given_doubles_at_the_top_of_the_stack(){
	double a[2] = {12.67,76.45};
	double _12 = 12.67;
	double _76 = 76.45;
	Stack expected = {a,2,2,sizeof(double)};
	stack = create(2, sizeof(double));
	push(stack, &_12);
	push(stack, &_76);
	ASSERT(areEqual(expected, *stack));
}

void test_adds_the_given_characters_at_the_top_of_the_stack(){
	char chars[2] = {'a','m'};
	char a = 'a';
	char m = 'm';
	Stack expected = {chars,2,2,sizeof(char)};
	stack = create(2, sizeof(char));
	push(stack, &a);
	push(stack, &m);
	ASSERT(areEqual(expected, *stack));
}

void test_adds_the_given_Strings_at_the_top_of_the_stack(){
	String names[2] = {"Digs","Raj"};
	String digs_nm = "Digs";
	String raj_nm = "Raj";
	Stack expected = {names,2,2,sizeof(String)};
	stack = create(2, sizeof(String));
	push(stack, digs_nm);
	push(stack, raj_nm);
	ASSERT(areEqual(expected, *stack));
}

void test_doubles_the_length_of_stack_if_stack_is_full(){
	int _5_nums[5] = {23,12,56,34,789};
	Stack expected = {_5_nums,5,5,sizeof(int)};
	int _12 = 12;
	int result;
	stack = create(5, sizeof(int));
	memcpy(stack->elements, _5_nums, sizeof(_5_nums));
	stack->top = 5;
	ASSERT(areEqual(expected, *stack));
	result = push(stack, &_12);
	ASSERT(1==result);
	ASSERT(6 == stack->top && 10 == stack->length);
	ASSERT(12 == *(int*)(stack->elements + 5*sizeof(int)));
}

//***************************pop***********************************************

void test_removes_the_top_most_element_from_the_stack_integers(){
	int _4_nums[4] = {12,14,45,78};
	int *result;
	stack = create(4, sizeof(int));
	memcpy(stack->elements,_4_nums,4*sizeof(int));
	stack->top = 4;
	result = (int*)(pop(stack));
	ASSERT(78==*result);
	ASSERT(3==stack->top);
};

void test_removes_the_top_most_element_from_the_stack_doubles(){
	double _4_nums[4] = {12.14,14.96,45.25,4478.14};
	double *result;
	stack = create(4, sizeof(double));
	memcpy(stack->elements,_4_nums,4*sizeof(double));
	stack->top = 4;
	result = (double*)(pop(stack));
	ASSERT(4478.14==*result);
	ASSERT(3==stack->top);
};

void test_removes_the_top_most_element_from_the_stack_characters(){
	char _4_chars[4] = {'m','d','a','k'};
	char *result;
	stack = create(4, sizeof(char));
	memcpy(stack->elements,_4_chars,4*sizeof(char));
	stack->top = 4;
	result = (char*)(pop(stack));
	ASSERT('k'==*result);
	ASSERT(3==stack->top);
};

void test_removes_the_top_most_element_from_the_stack_Strings(){
	String _4_chars[4] = {"mritunjay","dubey","aniket","kartik"};
	char* result;
	String expected = "kartik";
	stack = create(4, sizeof(String));
	memcpy(stack->elements,_4_chars,4*sizeof(String));
	stack->top = 4;
	result = (char*)(pop(stack));
	ASSERT(0==strcmp(result, expected));
	ASSERT(3==stack->top);
};

void test_removes_the_top_most_element_and_adds_one_more_element_at_top(){
	int _3_nums[3] = {12,14,45};
	int _4_nums[4] = {12,14,45,78};
	int _res_4_nums[4] = {12,14,45,1000};
	int _1000 = 1000;
	int *result;
	Stack expected = {_res_4_nums,4,4,sizeof(int)};
	stack = create(4, sizeof(int));
	memcpy(stack->elements,_4_nums,4*sizeof(int));
	stack->top = 4;
	result = (int*)(pop(stack));
	ASSERT(78==*result);
	push(stack, &_1000);
	ASSERT(areEqual(expected, *stack));
	ASSERT(4==stack->top);
};

void test_prevents_to_delete_the_element_if_top_is_zero(){
	void* result;
	stack = create(5, sizeof(int));
	result = pop(stack);
	ASSERT(NULL == result);
}

//******************************************peek******************************

void test_gives_the_top_most_element_of_stack_integers(){
	int *result;
	int _3_nums[3] = {14,58,17};
	stack = create(5, sizeof(int));
	stack->top = 3;
	memcpy(stack->elements, _3_nums, 3*stack->elementSize);
	result = (int*)peek(stack);
	ASSERT(17==*result);
	ASSERT(3==stack->top);
};

void test_gives_the_top_most_element_of_stack_doubles(){
	double *result;
	double _3_nums[3] = {14.25,58.4,17.0458};
	stack = create(5, sizeof(double));
	stack->top = 3;
	memcpy(stack->elements, _3_nums, 3*stack->elementSize);
	result = (double*)peek(stack);
	ASSERT(17.0458==*result);
	ASSERT(3==stack->top);
};

void test_gives_the_top_most_element_of_stack_characters(){
	char *result;
	char _3_chars[3] = {'m','m','p'};
	stack = create(5, sizeof(char));
	stack->top = 3;
	memcpy(stack->elements, _3_chars, 3*stack->elementSize);
	result = (char*)peek(stack);
	ASSERT('p'==*result);
	ASSERT(3==stack->top);
};

void test_gives_the_top_most_element_of_stack_String(){
	char* result;
	String _3_names[3] = {"manish","mritunjay","prateek"};
	String expected = "prateek";
	stack = create(5, sizeof(String));
	stack->top = 3;
	memcpy(stack->elements, _3_names, 3*stack->elementSize);
	result = (char*)peek(stack);
	ASSERT(0==strcmp(expected, result));
	ASSERT(3==stack->top);
};

void test_prevents_to_search_the_top_element_if_top_is_zero(){
	void* result;
	stack = create(5, sizeof(int));
	result = peek(stack);
	ASSERT(NULL == result);
}

//***********************************isEmpty*****************

void test_tells_the_stack_is_empty_integers(){
	int result;
	stack = create(5, sizeof(int));
	result = isEmpty(stack);
	ASSERT(1==result);
}
void test_tells_the_stack_is_empty_strings(){
	int result;
	stack = create(5, sizeof(String));
	result = isEmpty(stack);
	ASSERT(1==result);
}
void test_tells_the_stack_is_not_empty(){
	int result;
	stack = create(5, sizeof(int));
	*(int*)stack->elements = 15;
	stack->top = 1;
	result = isEmpty(stack);
	ASSERT(0==result);
}

//****************************isFull**********************

void test_tells_the_stack_is_full_integers(){
	int result;
	stack = create(1, sizeof(int));
	*(int*)stack->elements = 15;
	stack->top = 1;
	result = isFull(stack);
	ASSERT(1==result);
}

void test_tells_the_stack_is_full_Strings(){
	int result;
	stack = create(1, sizeof(String));
	strcpy(stack->elements, "Mritunjay");
	stack->top = 1;
	result = isFull(stack);
	ASSERT(1==result);
}

void test_tells_the_stack_is_not_full_Strings(){
	int result;
	stack = create(4, sizeof(String));
	strcpy(stack->elements, "Mritunjay");
	stack->top = 1;
	result = isFull(stack);
	ASSERT(0==result);
}

//*****************************Structure*******************************
typedef struct{
	int roll;
	char name[18];
}Class;

void test_creates_a_stack_for_structure(){
	Class studs[1] = {{0,""}};
	Stack expected = {studs,0,1,sizeof(Class)};
	stack = create(1, sizeof(Class));
	ASSERT(areEqual(expected, *stack));

};

void test_adds_structure_on_top_of_stack(){
	Class studs[2] = {{1,"Raj"},{2,"Digs"}};
	Class rajStud = {1,"Raj"};
	Class digStud = {2,"Digs"};
	Stack expected = {studs,2,2,sizeof(Class)};
	stack = create(2, sizeof(Class));
	push(stack, &rajStud);
	push(stack, &digStud);
	ASSERT(areEqual(expected, *stack));
};

void test_removes_the_top_most_structure_from_stack(){
	Class studs[2] = {{1,"Raj"},{2,"Digs"}};
	Class* result;
	Class rajStud = {1,"Raj"};
	Class digStud = {2,"Digs"};
	stack = create(2, sizeof(Class));
	memcpy(stack->elements, studs, sizeof(Class)*2);
	stack->top = 2;
	result = pop(stack);
	ASSERT(0==memcmp(&digStud, result, sizeof(Class)));
	ASSERT(1==stack->top);
	result = pop(stack);
	ASSERT(0==memcmp(&rajStud, result, sizeof(Class)));
	ASSERT(0==stack->top);
	result = pop(stack);
	ASSERT(NULL == result);
	ASSERT(0==stack->top);
};

void test_gives_the_top_most_element_of_the_stack(){
	Class studs[2] = {{1,"Raj"},{2,"Digs"}};
	Class* result;
	Class rajStud = {1,"Raj"};
	Class digStud = {2,"Digs"};
	stack = create(2, sizeof(Class));
	memcpy(stack->elements, studs, sizeof(Class)*2);
	stack->top = 2;
	result = peek(stack);
	ASSERT(0==memcmp(&digStud, result, sizeof(Class)));
	ASSERT(2==stack->top);
};