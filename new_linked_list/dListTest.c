#include "testUtils.h"
#include "dList.h"
#include <stdlib.h>
#include <string.h>
#include "../customTypes.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

DoubleList list;

void setup(){
	list = create();
}

void tearDown(){
	dispose(list);
}
void test_gives_an_Doubly_link_list_with_head_NULL(){
	ASSERT(NULL == list.head);
	ASSERT(0 == list.length);
}

void test_inserts_an_element_as_the_head_of_linklist_for_integer(){
	int num = 2;
	ASSERT(insert(&list, 0, &num));
	ASSERT(2 == *(int*)getNodeData(list, 0));
	ASSERT(list.length);
}

void test_inserts_elements_at_the_end_of_linkList_for_integer(){
	int nums[3] = {10,12,14};
	ASSERT(insert(&list, 0, &nums[0]));
	ASSERT(insert(&list, 1, &nums[1]));
	ASSERT(12 == *(int*)getNodeData(list, 1));
	ASSERT(insert(&list, 2, &nums[2]));
	ASSERT(14 == *(int*)getNodeData(list, 2));
	ASSERT(3 == list.length);
}

void test_adds_element_in_middle_of_linkList_integer(){
    int nums[4] = {12,14,15,20};
  
    ASSERT(insert(&list, 0, &nums[0]));
    ASSERT(insert(&list, 1, &nums[2]));
    ASSERT(insert(&list, 2, &nums[3]));
    ASSERT(15 == *(int*)getNodeData(list, 1));
    ASSERT(insert(&list, 1, &nums[1]));
    ASSERT(14 == *(int*)getNodeData(list, 1));
    ASSERT(4 == list.length);
}

void test_inserts_multiple_element_as_the_head_of_linklist_for_integer(){
	int nums[3] = {10,15,16};
	ASSERT(insert(&list, 0, &nums[0]));
	ASSERT(insert(&list, 0, &nums[1]));
	ASSERT(insert(&list, 0, &nums[2]));
	ASSERT(10 == *(int*)getNodeData(list, 2));
	ASSERT(3 == list.length);
}

void test_inserts_the_doubles_in_the_linklist(){
	double nums[3] = {1.0,2.0,3.0};
	ASSERT(insert(&list, 0, &nums[0]));
	ASSERT(insert(&list, 1, &nums[1]));
	ASSERT(insert(&list, 1, &nums[2]));
	ASSERT(3.0 == *(double*)getNodeData(list, 1));
	ASSERT(3 == list.length);
}

void test_inserts_the_chars_in_the_linklist(){
	char chars[3] = {'a','n','m'};
	ASSERT(insert(&list, 0, &chars[0]));
	ASSERT(insert(&list, 1, &chars[1]));
	ASSERT(insert(&list, 1, &chars[2]));
	ASSERT('n' == *(char*)getNodeData(list, 2));
	ASSERT(3 == list.length);
}

void test_inserts_the_strings_in_the_linklist(){
	String names[3] = {"prateek","Manish","Shweta"};
	ASSERT(insert(&list, 0, &names[0]));
	ASSERT(insert(&list, 1, &names[1]));
	ASSERT(insert(&list, 1, &names[2]));
	ASSERT(0 == strcmp("prateek", (char*)getNodeData(list, 0)));
	ASSERT(3 == list.length);
}

void test_inserts_the_structures_in_the_linklist(){
	Account accounts[3] = {{100,1000},{101,2000},{102,4000}};
	ASSERT(insert(&list, 0, &accounts[0]));
	ASSERT(insert(&list, 1, &accounts[1]));
	ASSERT(insert(&list, 1, &accounts[2]));
	ASSERT(areAccountsEqual(accounts[0], *(Account*)getNodeData(list, 0)));
	ASSERT(3 == list.length);
}

void test_deletes_first_element_in_list_with_one_element(){
    int nums[1] = {10};  
    insert(&list, 0, nums);
    ASSERT(delete_node(&list, 0));
    ASSERT(0 == list.length);
    ASSERT(NULL == getNodeData(list, 0));
}

void test_deletes_first_element_in_list_when_more_than_one_elements(){
    int nums[3] = {10,15,16};
    insert(&list, 0, &nums[0]);
    insert(&list, 1, &nums[1]);
    insert(&list, 2, &nums[2]);
    ASSERT(delete_node(&list, 0));
    ASSERT(NULL == getNodeData(list, 2));
    ASSERT(2 == list.length);
}

void test_deletes_last_element_in_the_linkList(){
    int nums[3] = {10,15,16};
    insert(&list, 0, &nums[0]);
    insert(&list, 1, &nums[1]);
    insert(&list, 2, &nums[2]);
    ASSERT(16 == *(int*)getNodeData(list, 2));
    ASSERT(delete_node(&list, 2));
    ASSERT(NULL == getNodeData(list, 2));
    ASSERT(2 == list.length);
}

void test_deletes_element_in_between(){
    int nums[3] = {10,15,16};
    insert(&list, 0, &nums[0]);
    insert(&list, 1, &nums[1]);
    insert(&list, 2, &nums[2]);
    ASSERT(16 == *(int*)getNodeData(list, 2));
    ASSERT(delete_node(&list, 1));
    ASSERT(2 == list.length);
}

void test_deletion_failed_when_list_is_empty(){
	ASSERT(0 == delete_node(&list, 1));
}