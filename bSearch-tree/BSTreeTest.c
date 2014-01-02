#include "BSTree.h"
#include <stdlib.h>
#include <string.h>
#include "../customTypes.h"
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

int compareInetgerNodes(void* first, void* second){
	return *(int*)first - *(int*)second;
}

int compareDoubleNodes(void* first, void* second){
	return *(double*)first - *(double*)second;
}

int compareStringNodes(void* first, void* second){
	return strcmp((char*)first, (char*)second);
}

int compareAccountNodes(void* first, void* second) {
    Account* firstAccount = (Account*)first;
    Account* secondAccount = (Account*)second;
    return firstAccount->accNo - secondAccount->accNo;
}

void test_inserts_first_data_as_root_of_the_tree(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int number = 15;
	ASSERT(insertInBSTree(&tree, &number));
	ASSERT(&number == getRootData(tree));
	disposeBSTree(&tree);	
}

void test_inserts_children_of_root_data(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int number = 15;
	int num2 = 12;
	ASSERT(insertInBSTree(&tree, &number));
	ASSERT(insertInBSTree(&tree, &num2));
	ASSERT(&number == getRootData(tree));	
	disposeBSTree(&tree);	
}

void test_insertion_failed_when_data_is_already_present(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int num = 12;
	ASSERT(insertInBSTree(&tree, &num));
	ASSERT(0 == insertInBSTree(&tree, &num));
	disposeBSTree(&tree);	
}

void test_inserts_left_child_when_given_data_is_less_than_node_data(){
	BS_Tree tree = createBSTree(compareStringNodes);
	String names[2] = {"Digvijay", "Raaz"};
	Children_data result;
	insertInBSTree(&tree, &names[1]);
	insertInBSTree(&tree, &names[0]);
	result = getChildrenData(tree, &names[1]);
	ASSERT(&names[0] == result.left);
	ASSERT(NULL == result.right);
	disposeBSTree(&tree);	
}

void test_inserts_right_child_when_given_data_is_greater_than_node_data(){
	BS_Tree tree = createBSTree(compareAccountNodes);
	Account accounts[2] = {{100,2000},{200,4000}};
	Children_data result;
	insertInBSTree(&tree, &accounts[0]);
	insertInBSTree(&tree, &accounts[1]);
	result = getChildrenData(tree, &accounts[0]);
	ASSERT(NULL == result.left);
	ASSERT(&accounts[1] == result.right);
	disposeBSTree(&tree);	
}

void test_inserts_data_at_defferent_level(){
    BS_Tree tree = createBSTree(compareInetgerNodes);
    int i, number[8] = {22,24,20,6,30,40,50,12};
    Children_data result;
    for(i = 0;i<8;i++){
        ASSERT(insertInBSTree(&tree, &number[i]));
    }
    result = getChildrenData(tree, &number[0]);
    ASSERT(&number[1] == result.right);
    ASSERT(&number[2] == result.left);
    result = getChildrenData(tree, &number[4]);
    ASSERT(&number[5] == result.right);
    ASSERT(NULL == result.left);
	disposeBSTree(&tree);	
}

void test_gives_the_children_of_the_node_which_data_is_given(){
	BS_Tree tree = createBSTree(compareDoubleNodes);
	int i;double nums[5] = {9.0,10.0,4.0,8.0,2.0};
	Children_data result;
	for(i = 0;i<5;i++){
		ASSERT(insertInBSTree(&tree, &nums[i]));
	}
	result = getChildrenData(tree, &nums[2]);
	ASSERT(&nums[4] == result.left);
	ASSERT(&nums[3] == result.right);
	disposeBSTree(&tree);	
}

void test_gives_the_children_as_null_if_given_data_is_not_present(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int num = 10;
	Children_data result = getChildrenData(tree, &num);
	ASSERT(NULL == result.left);
	ASSERT(NULL == result.right);
	disposeBSTree(&tree);	
}

void test_tells_that_the_given_data_is_present_in_Tree(){
	BS_Tree tree = createBSTree(compareStringNodes);
	String name = "Mritunjay";
	insertInBSTree(&tree, &name);
	ASSERT(searchInBSTree(tree, &name));
	disposeBSTree(&tree);	
}

void test_tells_that_the_given_data_is_not_present_in_Tree(){
	BS_Tree tree = createBSTree(compareAccountNodes);
	Account account = {14,15};
	ASSERT(0 == searchInBSTree(tree, &account));
	disposeBSTree(&tree);	
}

void test_searchs_the_given_data_in_tree_deeply(){
    BS_Tree tree = createBSTree(compareInetgerNodes);
    int i, number[8] = {22,24,20,6,30,40,50,12};
    for(i = 0;i<8;i++){
       insertInBSTree(&tree, &number[i]);
    }
    ASSERT(1 == searchInBSTree(tree, &number[6]));
	disposeBSTree(&tree);	
}

void test_deletes_the_single_present_element_in_tree(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int num = 10;
	insertInBSTree(&tree, &num);
	ASSERT(deleteFromBSTree(&tree, &num));
	// disposeBSTree(&tree);	
}

void test_deletes_the_root_which_has_only_left_child(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int num = 10;
	int num2 = 5;
	insertInBSTree(&tree, &num);
	insertInBSTree(&tree, &num2);
	ASSERT(deleteFromBSTree(&tree, &num));
	ASSERT(0 == searchInBSTree(tree, &num));
	// disposeBSTree(&tree);	
}

void test_deletes_the_root_which_has_only_right_child(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int num = 10;
	int num2 = 15;
	insertInBSTree(&tree, &num);
	insertInBSTree(&tree, &num2);
	ASSERT(deleteFromBSTree(&tree, &num));
	ASSERT(0 == searchInBSTree(tree, &num));
	// disposeBSTree(&tree);	
}

void test_deletes_the_root_which_has_both_child(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int num = 10;
	int num2 = 15;
	int num3 = 5;
	insertInBSTree(&tree, &num);
	insertInBSTree(&tree, &num2);
	insertInBSTree(&tree, &num3);
	ASSERT(deleteFromBSTree(&tree, &num));
	ASSERT(0 == searchInBSTree(tree, &num));
	disposeBSTree(&tree);	
}

void test_deletes_node_with_no_children(){
	BS_Tree tree = createBSTree(compareDoubleNodes);
	double nums[5] = {23.0,15.0,17.0,14.0,24.0};
	int i;
	for(i = 0;i<5 ;i++)
		insertInBSTree(&tree, &nums[i]);
	ASSERT(searchInBSTree(tree, &nums[2]));
	ASSERT(deleteFromBSTree(&tree, &nums[2]));
	ASSERT(0 == searchInBSTree(tree, &nums[2]));
	disposeBSTree(&tree);	
}

void test_deletes_node_with_only_left_children(){
	BS_Tree tree = createBSTree(compareStringNodes);
	String names[5] = {"Raaz","Shweta","Sayali","Manish","Shabrin"};
	int i;
	for(i = 0;i<5 ;i++)
		insertInBSTree(&tree, &names[i]);
	ASSERT(searchInBSTree(tree, &names[1]));
	ASSERT(deleteFromBSTree(&tree, &names[1]));
	ASSERT(0 == searchInBSTree(tree, &names[1]));
	disposeBSTree(&tree);	
}

void test_deletes_node_with_only_right_children(){
	BS_Tree tree = createBSTree(compareDoubleNodes);
	Account accounts[5] = {{400,2000},{100,1000},{200,4000},{300,1000},{500,5000}};
	int i;
	for(i = 0;i<5 ;i++)
		insertInBSTree(&tree, &accounts[i]);
	ASSERT(searchInBSTree(tree, &accounts[1]));
	ASSERT(deleteFromBSTree(&tree, &accounts[1]));
	ASSERT(0 == searchInBSTree(tree, &accounts[1]));
	// disposeBSTree(&tree);	
}

void test_deletes_node_with_both_children(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
    int i, number[8] = {22,24,20,6,30,40,50,12};
    for(i = 0;i<8;i++)
       insertInBSTree(&tree, &number[i]);
    ASSERT(searchInBSTree(tree, &number[3]));
    ASSERT(deleteFromBSTree(&tree, &number[3]));
    ASSERT(0 == searchInBSTree(tree, &number[3]));
	disposeBSTree(&tree);	
}

void test_deletion_failed_when_data_is_not_present(){
	BS_Tree tree = createBSTree(compareDoubleNodes);
	int num = 10.0;
	ASSERT(0 == deleteFromBSTree(&tree, &num));
	disposeBSTree(&tree);	
}

// void test_tells_that_tree_is_not_balanced(){
// 	BS_Tree tree = createBSTree(compareInetgerNodes);
// 	int i; int nums[] = {1,2,3,4,5,6,7,8};
// 	for( i = 0;i<8; i++)
// 		insertInBSTree(&tree, &nums[i]);
// 	ASSERT(0 == isBSTBalanced(tree));
// }