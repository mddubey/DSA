#include "tree.h"
#include <stdlib.h>
#include "testUtils.h"
#include <string.h>
#include "../customTypes.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

int areNodesEqualInt(void* nodeData, void* parentData){
	return (*(int*)nodeData == *(int*)parentData);
}

int areNodesEqualDouble(void* nodeData, void* parentData){
	return (*(double*)nodeData == *(double*)parentData);
}

int areNodesEqualStrings(void* nodeData, void* parentData){
	return (0 == strcmp((char*)nodeData,(char*)parentData));
}

int areNodesEqualAccount(void* first, void* second){
	return ((Account*)first)->accNo == ((Account*)second)->accNo;
}

void test_inserts_a_root_node_into_tree(){
	Tree tree = createTree(areNodesEqualInt);
	int number = 12;
	Iterator it;
	ASSERT(insertInTree(&tree, NULL, &number));
	it = getChildren(tree, &number);
	ASSERT(0 == it.hasNext(&it));
	ASSERT(&number == getRootData(tree));
	ASSERT(NULL == it.next(&it));
	disposeTree(&tree);
}

void test_inserts_a_child_of_root_into_tree(){
	Tree tree = createTree(areNodesEqualInt);
	int nums[2] = {12,25};
	Iterator it;
	ASSERT(insertInTree(&tree, NULL, &nums[0]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[1]));
	it = getChildren(tree, &nums[0]);
	ASSERT(1 == it.hasNext(&it));
	ASSERT(25 == *(int*)it.next(&it));
	ASSERT(0 == it.hasNext(&it));
	disposeTree(&tree);
}

void test_inserts_two_children_of_root_into_tree(){
	Tree tree = createTree(areNodesEqualInt);
	int nums[3] = {12,25,14};
	Iterator it;
	ASSERT(insertInTree(&tree, NULL, &nums[0]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[1]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[2]));
	it = getChildren(tree, &nums[0]);
	ASSERT(25 == *(int*)it.next(&it));
	ASSERT(14 == *(int*)it.next(&it));
	disposeTree(&tree);
}

void test_inserts_children_to_different_level(){
	Tree tree = createTree(areNodesEqualDouble);
	double nums[5] = {10.0,10.1,10.2,10.3,10.4};
	Iterator it;
	insertInTree(&tree, NULL, &nums[0]);
	insertInTree(&tree, &nums[0], &nums[1]);
	insertInTree(&tree, &nums[0], &nums[2]);
	ASSERT(insertInTree(&tree, &nums[1], &nums[3]));
	ASSERT(insertInTree(&tree, &nums[2], &nums[4]));
	it = getChildren(tree, &nums[1]);
	ASSERT(10.3 == *(double*)it.next(&it));
	ASSERT(NULL == it.next(&it));
	it = getChildren(tree, &nums[2]);
	ASSERT(10.4 == *(double*)it.next(&it));
	ASSERT(NULL == it.next(&it));
	disposeTree(&tree);
}

void test_gives_iterator_to_check_children_data_of_a_parent(){
	Tree tree = createTree(areNodesEqualInt);
	int nums[3] = {12,25,14};
	Iterator it;
	ASSERT(insertInTree(&tree, NULL, &nums[0]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[1]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[2]));
	it = getChildren(tree, &nums[0]);
	ASSERT(25 == *(int*)it.next(&it));
	ASSERT(14 == *(int*)it.next(&it));
	disposeTree(&tree);
}

void test_searchs_the_given_data_in_list(){
	Tree tree = createTree(areNodesEqualStrings);
	String names[2];
	strcpy(names[0], "Raaz");
	strcpy(names[1], "Digs");
	insertInTree(&tree, NULL, &names[0]);
	insertInTree(&tree, &names[0], &names[1]);
	ASSERT(searchInTree(tree, &names[0]));
	ASSERT(searchInTree(tree, &names[1]));
	disposeTree(&tree);
}

void test_search_fails_when_data_is_not_present(){
	Tree tree = createTree(areNodesEqualStrings);
	String names[1];
	strcpy(names[0], "Raaz");
	ASSERT(0 == searchInTree(tree, &names[0]));
}

void test_search_a_Account_in_tree(){
	Tree tree = createTree(areNodesEqualAccount);
	Account accounts[5] = {{1,10},{2,12},{3,30},{4,45}};
	insertInTree(&tree, NULL, &accounts[0]);
	insertInTree(&tree, &accounts[0], &accounts[1]);
	insertInTree(&tree, &accounts[0], &accounts[2]);
	insertInTree(&tree, &accounts[0], &accounts[3]);
	insertInTree(&tree, &accounts[1], &accounts[4]);
	ASSERT(searchInTree(tree, &accounts[3]));
	ASSERT(searchInTree(tree, &accounts[4]));
	disposeTree(&tree);
}

void test_deletes_the_root_from_the_tree(){
	Tree tree = createTree(areNodesEqualInt);
	int number = 12;
	insertInTree(&tree, NULL, &number);
	ASSERT(searchInTree(tree, &number));
	ASSERT(1 == deleteFromTree(&tree, &number));
	disposeTree(&tree);
}

void test_deletion_failed_when_data_is_not_in_tree(){
	Tree tree = createTree(areNodesEqualInt);
	int number = 12;
	ASSERT(0 == deleteFromTree(&tree, &number));
}

void test_deletion_failed_when_Node_has_children(){
	Tree tree = createTree(areNodesEqualInt);
	int nums[3] = {12,25};
	insertInTree(&tree, NULL, &nums[0]);
	insertInTree(&tree, &nums[0], &nums[1]);
	ASSERT(0 == deleteFromTree(&tree, &nums[0]));
	disposeTree(&tree);
}

void test_deletes_first_child_of_root(){
	Tree tree = createTree(areNodesEqualStrings);
	String names[3];
	strcpy(names[0], "Shital");
	strcpy(names[1], "Manali");
	strcpy(names[2], "shweta");
	insertInTree(&tree, NULL, &names[0]);
	insertInTree(&tree, &names[0], &names[1]);
	insertInTree(&tree, &names[0], &names[2]);
	ASSERT(1 == searchInTree(tree, "Manali"));
	ASSERT(1 == deleteFromTree(&tree, &names[1]));
	ASSERT(0 == searchInTree(tree, "Manali"));
	disposeTree(&tree);
}

void test_deletes_second_child_of_root(){
	Tree tree = createTree(areNodesEqualStrings);
	String names[3];
	strcpy(names[0], "Raaz");
	strcpy(names[1], "Digs");
	strcpy(names[2], "Manish");
	insertInTree(&tree, NULL, &names[0]);
	insertInTree(&tree, &names[0], &names[1]);
	insertInTree(&tree, &names[0], &names[2]);
	ASSERT(1 == searchInTree(tree, "Manish"));
	ASSERT(1 == deleteFromTree(&tree, &names[2]));
	ASSERT(0 == searchInTree(tree, "Manish"));
	disposeTree(&tree);
}

void test_deletes_nodes_from_different_level(){
	Tree tree = createTree(areNodesEqualAccount);
	Account accounts[5] = {{1,10},{2,12},{3,30},{4,45}};
	insertInTree(&tree, NULL, &accounts[0]);
	insertInTree(&tree, &accounts[0], &accounts[1]);
	insertInTree(&tree, &accounts[0], &accounts[2]);
	insertInTree(&tree, &accounts[0], &accounts[3]);
	insertInTree(&tree, &accounts[1], &accounts[4]);
	ASSERT(1 == searchInTree(tree, &accounts[2]));
	ASSERT(1 == deleteFromTree(&tree, &accounts[2]));
	ASSERT(0 == searchInTree(tree, &accounts[2]));
	disposeTree(&tree);
}

void test_deletes__nodes_from_different_level(){
	Tree tree = createTree(areNodesEqualAccount);
	Account accounts[7] = {{1,10},{2,12},{3,30},{4,45},{5,50},{6,60},{7,70}};
	insertInTree(&tree, NULL, &accounts[0]);
	insertInTree(&tree, &accounts[0], &accounts[1]);
	insertInTree(&tree, &accounts[0], &accounts[2]);
	insertInTree(&tree, &accounts[0], &accounts[3]);
	insertInTree(&tree, &accounts[1], &accounts[4]);
	insertInTree(&tree, &accounts[3], &accounts[5]);
	insertInTree(&tree, &accounts[3], &accounts[6]);
	ASSERT(1 == searchInTree(tree, &accounts[2]));
	ASSERT(1 == deleteFromTree(&tree, &accounts[2]));
	ASSERT(0 == searchInTree(tree, &accounts[2]));
	ASSERT(1 == searchInTree(tree, &accounts[6]));
	ASSERT(1 == deleteFromTree(&tree, &accounts[6]));
	ASSERT(0 == searchInTree(tree, &accounts[6]));
	disposeTree(&tree);
}

void test_checking_dispose_for_each_node(){
	Tree tree = createTree(areNodesEqualAccount);
	int nums[7] = {1,2,3,4,5,6,7};
	insertInTree(&tree, NULL, &nums[0]);
	insertInTree(&tree, &nums[0], &nums[1]);
	insertInTree(&tree, &nums[0], &nums[2]);
	insertInTree(&tree, &nums[0], &nums[3]);
	insertInTree(&tree, &nums[1], &nums[4]);
	insertInTree(&tree, &nums[3], &nums[5]);
	insertInTree(&tree, &nums[3], &nums[6]);
	disposeTree(&tree);
}


