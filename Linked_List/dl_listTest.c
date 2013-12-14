#include "dl_list.h"
#include <stdlib.h>
#include <string.h>
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

DLList* list;

void tearDown(){
	dispose(list);
}
void test_gives_an_Doubly_link_list_with_head_NULL(){
	list = create();
	ASSERT(NULL == list->head);
	ASSERT(0 == list->length);
}

void test_create_node(){
    Node expected = {NULL,NULL,NULL};
    Node *actual = createNode(NULL,NULL);
    ASSERT(expected.next == actual->next);
    ASSERT(expected.prev == actual->prev);
}

void test_inserts_an_element_as_the_head_of_linklist_for_integer(){
	int* num = malloc(sizeof(int));
	list = create();
	*num = 10;
	insert(list, num, 0);
	ASSERT(10 == *(int*)list->head->data);
	ASSERT(NULL == list->head->prev);
	ASSERT(NULL == list->head->next);
	ASSERT(1 == list->length);
}

void test_inserts_elements_at_the_end_of_linkList_for_integer(){
	int* nums = malloc(sizeof(int)*3);
	Node *result1,*result2;
	list = create();
	nums[0] = 10;nums[1] = 12;nums[2] = 14;

	insert(list, &nums[0], 0);
	ASSERT(10 == *(int*)list->head->data);
	ASSERT(NULL == list->head->prev);
	ASSERT(NULL == list->head->next);
	ASSERT(1 == list->length);

	insert(list, &nums[1], 1);
	result1 = list->head->next;
	ASSERT(12 == *(int*)result1->data);
	ASSERT(list->head == result1->prev);
	ASSERT(NULL == result1->next);
	ASSERT(2 == list->length);

	insert(list, &nums[2], 2);
	result2 = result1->next;
	ASSERT(14 == *(int*)result2->data);
	ASSERT(result1 == result2->prev);
	ASSERT(NULL == result2->next);
	ASSERT(3 == list->length);
}

void test_adds_element_in_middle_of_linkList_integer(){
    Node *second,*third,*fourth;
    int* nums = malloc(sizeof(int)*4);
    nums[0] = 12;nums[1] = 14;nums[2] = 15;nums[3] = 20;
    list = create();
    insert(list, &nums[0], 0);
    ASSERT(1 == list->length);
    insert(list, &nums[2], 1);
    ASSERT(2 == list->length);
    insert(list, &nums[3], 2);
    ASSERT(3 == list->length);
    insert(list, &nums[1], 1);
    ASSERT(4 == list->length);
    second = list->head->next;
    third = second->next;
    fourth = third->next;
    ASSERT(12 == *(int*)list->head->data);
    ASSERT(14 == *(int*)second->data);
    ASSERT(15 == *(int*)third->data);
    ASSERT(20 == *(int*)fourth->data);
}

void test_inserts_multiple_element_as_the_head_of_linklist_for_integer(){
	int* nums = malloc(sizeof(int)*3);
	list = create();
	nums[0] = 10;nums[1] = 15;nums[2] = 16;
	insert(list, nums, 0);
	ASSERT(10 == *(int*)list->head->data);
	ASSERT(1 == list->length);
	insert(list, nums+1, 0);
	ASSERT(15 == *(int*)list->head->data);
	ASSERT(NULL == list->head->prev);
	insert(list, nums+2, 0);
	ASSERT(16 == *(int*)list->head->data);
	ASSERT(3 == list->length);
}

void test_inserts_the_doubles_in_the_linklist(){
	double* nums = malloc(sizeof(double)*3);
	list = create();
	nums[0] = 1.0;nums[1] = 2.0; nums[2] = 3.0;
	insert(list, &nums[0], 0);
	ASSERT(1.0 == *(double*)list->head->data);
	ASSERT(1 == list->length);
	insert(list, &nums[1], 1);
	ASSERT(2.0 == *(double*)list->head->next->data);
	ASSERT(2 == list->length);
	insert(list, &nums[2], 1);
	ASSERT(3.0 == *(double*)list->head->next->data);
	ASSERT(3 == list->length);
}

void test_inserts_the_chars_in_the_linklist(){
	char* chars = malloc(sizeof(char)*3);
	list = create();
	chars[0] = 'a';chars[1] = 'n'; chars[2] = 'm';
	insert(list, &chars[0], 0);
	ASSERT('a' == *(char*)list->head->data);
	ASSERT(1 == list->length);
	insert(list, &chars[1], 1);
	ASSERT('n' == *(char*)list->head->next->data);
	ASSERT(2 == list->length);
	insert(list, &chars[2], 1);
	ASSERT('m' == *(char*)list->head->next->data);
	ASSERT(3 == list->length);
}

typedef char String_256[256];
typedef struct 
{
	int accNo;
	int balance;
}Account;

int areAccountsEqual(Account expected,Account actual){
	return expected.accNo == actual.accNo && expected.balance == actual.balance;
}

void test_inserts_the_strings_in_the_linklist(){
	String_256* names = malloc(sizeof(String_256)*3);
	list = create();
	strcpy(names[0], "prateek");
	strcpy(names[1], "Manish");
	strcpy(names[2], "Shweta");
	insert(list, &names[0], 0);
	ASSERT(0 == strcmp("prateek",(char*)list->head->data));
	ASSERT(1 == list->length);
	insert(list, &names[1], 1);
	ASSERT(0 == strcmp("Manish",(char*)list->head->next->data));
	ASSERT(2 == list->length);
	insert(list, &names[2], 1);
	ASSERT(0 == strcmp("Shweta",(char*)list->head->next->data));
	ASSERT(3 == list->length);
}

void test_inserts_the_structures_in_the_linklist(){
	Account* accounts = malloc(sizeof(Account)*3);
	list = create();
	accounts[0].accNo = 100;accounts[0].balance = 1000;
	accounts[1].accNo = 101;accounts[1].balance = 2000;
	accounts[2].accNo = 102;accounts[2].balance = 4000;
	insert(list, &accounts[0], 0);
	ASSERT(areAccountsEqual(accounts[0], *(Account*)list->head->data));
	ASSERT(1 == list->length);
	insert(list, &accounts[1], 1);
	ASSERT(areAccountsEqual(accounts[1], *(Account*)list->head->next->data));
	ASSERT(2 == list->length);
	insert(list, &accounts[2], 1);
	ASSERT(areAccountsEqual(accounts[2], *(Account*)list->head->next->data));
	ASSERT(3 == list->length);
}

void test_deletes_first_element_in_list_with_one_element(){
    int* nums = malloc(sizeof(int));
    *nums = 5;
   	list = create();
    insert(list, nums, 0);
    ASSERT(deleteNode(list, 0));
    ASSERT(0 == list->length);
    ASSERT(NULL == list->head);
}

void test_deletes_first_element_in_list_when_more_than_one_elements(){
    int* nums = malloc(sizeof(int)*3);
	list = create();
	nums[0] = 10;nums[1] = 15;nums[2] = 16;
    insert(list,&nums[0], 0);
    insert(list,&nums[1], 1);
    insert(list,&nums[2], 2);
    ASSERT(3 == list->length);
    ASSERT(10 == *(int*)list->head->data);
    ASSERT(deleteNode(list, 0));
    ASSERT(2 == list->length);
    ASSERT(15 == *(int*)list->head->data);
}

void test_deletes_last_element_in_the_linkList(){
    int* nums = malloc(sizeof(int)*3);
	list = create();
	nums[0] = 10;nums[1] = 15;nums[2] = 16;
    insert(list,&nums[0], 0);
    insert(list,&nums[1], 1);
    insert(list,&nums[2], 2);
    ASSERT(deleteNode(list, 2));
    ASSERT(2 == list->length);
    ASSERT(NULL == list->head->next->next);
}

void test_deletes_element_in_between(){
    int* nums = malloc(sizeof(int)*3);
	list = create();
	nums[0] = 10;nums[1] = 15;nums[2] = 16;
    insert(list,&nums[0], 0);
    insert(list,&nums[1], 1);
    insert(list,&nums[2], 2);
    ASSERT(deleteNode(list, 1));
    ASSERT(2 == list->length);
    ASSERT(16 == *(int*)list->head->next->data);
}