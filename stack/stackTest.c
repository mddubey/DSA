#include <memory.h>
#include <stdlib.h>
#include "stack.h"
#include "testUtils.h"
#include "../customTypes.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

void* stack;

void tearDown(){
        disposeStack(stack);
}

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
        String names[2] = {"Digs","Raaz...."};
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

// //******************************************peek******************************

void test_gives_the_top_most_element_from_the_stack_integers(){
        int nums[4] = {10,12,15,20};
        int* result;
        stack = create(3);
        push(stack, &nums[0]);
        push(stack, &nums[2]);
        push(stack, &nums[1]);
        push(stack, &nums[3]);
        result = peek(stack);
        ASSERT(20 == *result);
};

void test_gives_the_top_most_element_from_the_stack_doubles(){
        double nums[2] = {10.0,12.0};
        double* result;
        stack = create(3);
        push(stack, &nums[0]);
        result = peek(stack);
        ASSERT(10.0 == *result);
        push(stack, &nums[1]);
        result = peek(stack);
        ASSERT(12.0 == *result);
};

void test_gives_the_top_most_element_from_the_stack_characters(){
        char chars[2] = {'a', 'm'};
        char* result;
        stack = create(3);
        push(stack, &chars[0]);
        result = peek(stack);
        ASSERT('a' == *result);
        push(stack, &chars[1]);
        result = peek(stack);
        ASSERT('m' == *result);
};

void test_gives_the_top_most_element_from_the_stack_Strings(){
        String names[2] = {"Mritunjay","kartik"};   
        char* result;
        stack = create(2);
        push(stack, &names[0]);
        result = peek(stack);
        ASSERT(0 == strcmp("Mritunjay", result));
        push(stack, &names[1]);
        ASSERT(0 == strcmp("Mritunjay", result));
};

void test_gives_structures_on_the_top_of_stacks(){
        Account accounts[2] = {{100,1000},{12,200}};
        Account* result;
        stack = create(3);
        push(stack, &accounts[0]);
        result = peek(stack);
        ASSERT(areAccountsEqual(accounts[0], *result));
        push(stack, &accounts[1]);
        result = peek(stack);
        ASSERT(areAccountsEqual(*result, accounts[1]));
}

void test_prevents_to_access_the_element_if_stack_is_empty(){
        void* result;
        stack = create(5);
        result = peek(stack);
        ASSERT(NULL == result);
}

// //***************************pop***********************************************

void test_removes_the_top_most_element_from_the_stack_integers(){
        int nums[1] = {20};
        int* result;
        stack = create(1);
        push(stack, &nums[0]);
        result = pop(stack);
        ASSERT(20 == *result);
        result = pop(stack);
        ASSERT(NULL == result);
};

void test_removes_the_top_most_element_from_the_stack_doubles(){
        double nums[3] = {10.0,12.0};
        double* result;
        stack = create(3);
        push(stack, &nums[0]);
        push(stack, &nums[1]);
        result = pop(stack);
        ASSERT(12.0 == *result);
        result = pop(stack);
        ASSERT(10.0 == *result);
        result = pop(stack);
        ASSERT(NULL == result);
};

void test_removes_the_top_most_element_from_the_stack_characters(){
        char chars[2] = {'a','m'};
        char* result;
        stack = create(3);
        push(stack, &chars[0]);
        push(stack, &chars[1]);
        result = pop(stack);
        ASSERT('m' == *result);
        result = pop(stack);
        ASSERT('a' == *result);
        result = pop(stack);
        ASSERT(NULL == result);
};

void test_removes_the_top_most_element_from_the_stack_Strings(){
        String names[2] = {"Mritunjay","kartik"};
        char* result;
        stack = create(2);
        push(stack, &names[0]);
        push(stack, &names[1]);
        result = pop(stack);
        ASSERT(0 == strcmp("kartik", result));
        result = pop(stack);
        ASSERT(0 == strcmp("Mritunjay", result));
        result = pop(stack);
        ASSERT(NULL == result);
};

void test_removes_structures_on_the_top_of_stacks(){
        Account account = {100,1000};
        Account* result;
        stack = create(3);
        push(stack, &account);
        result = pop(stack);
        ASSERT(areAccountsEqual(account, *result));
        result = pop(stack);
        ASSERT(NULL == result);
}

void test_removes_the_top_most_element_and_adds_one_more_element_at_top(){
        int nums[2] = {10,12};
        int* result;
        stack = create(2);
        push(stack, &nums[0]);
        push(stack, &nums[1]);
        result = (int*)(pop(stack));
        ASSERT(12 == *result);
        push(stack, &nums[0]);
        result = (int*)(pop(stack));
        ASSERT(10 == *result);
};

void test_prevents_to_delete_the_element_if_stack_is_empty(){
        void* result;
        stack = create(5);
        result = pop(stack);
        ASSERT(NULL == result);
}