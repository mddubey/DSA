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

void test_inserts_a_root_node_into_tree(){
	Tree tree = createTree(areNodesEqualInt);
	int number = 12;
	Iterator it;
	ASSERT(insertInTree(&tree, NULL, &number));
	it = getChildren(tree, &number);
	ASSERT(NULL == it.next(&it));
}

void test_inserts_a_child_of_root_into_tree(){
	Tree tree = createTree(areNodesEqualInt);
	int nums[2] = {12,25};
	Iterator it;
	ASSERT(insertInTree(&tree, NULL, &nums[0]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[1]));
	it = getChildren(tree, &nums[0]);
	ASSERT(25 == *(int*)getNextChildData(&it));
}

void test_inserts_two_children_of_root_into_tree(){
	Tree tree = createTree(areNodesEqualInt);
	int nums[3] = {12,25,14};
	Iterator it;
	ASSERT(insertInTree(&tree, NULL, &nums[0]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[1]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[2]));
	it = getChildren(tree, &nums[0]);
	ASSERT(25 == *(int*)getNextChildData(&it));
	ASSERT(14 == *(int*)getNextChildData(&it));
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
	ASSERT(10.3 == *(double*)getNextChildData(&it));
	ASSERT(NULL == getNextChildData(&it));
	it = getChildren(tree, &nums[2]);
	ASSERT(10.4 == *(double*)getNextChildData(&it));
	ASSERT(NULL == getNextChildData(&it));
}

void test_gives_iterator_to_check_children_data_of_a_parent(){
	Tree tree = createTree(areNodesEqualInt);
	int nums[3] = {12,25,14};
	Iterator it;
	ASSERT(insertInTree(&tree, NULL, &nums[0]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[1]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[2]));
	it = getChildren(tree, &nums[0]);
	ASSERT(25 == *(int*)getNextChildData(&it));
	ASSERT(14 == *(int*)getNextChildData(&it));
}

void test_deletes_the_root_from_the_tree(){
	Tree tree = createTree(areNodesEqualInt);
	int number = 12;
	insertInTree(&tree, NULL, &number);
	ASSERT(1 == deleteFromTree(&tree, &number));
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
}

void test_deletes_first_child_of_root(){
	Tree tree = createTree(areNodesEqualStrings);
	Iterator it;
	String names[3];
	strcpy(names[0], "Raaz");
	strcpy(names[1], "Digs");
	strcpy(names[2], "shweta");
	insertInTree(&tree, NULL, &names[0]);
	insertInTree(&tree, &names[0], &names[1]);
	insertInTree(&tree, &names[0], &names[2]);
	ASSERT(1 == deleteFromTree(&tree, &names[1]));
	it = getChildren(tree, &names[0]);
	ASSERT(&names[2] == getNextChildData(&it));
	ASSERT(NULL == getNextChildData(&it));
}

void test_deletes_second_child_of_root(){
	Tree tree = createTree(areNodesEqualStrings);
	Iterator it;
	String names[3];
	strcpy(names[0], "Raaz");
	strcpy(names[1], "Digs");
	strcpy(names[2], "shweta");
	insertInTree(&tree, NULL, &names[0]);
	insertInTree(&tree, &names[0], &names[1]);
	insertInTree(&tree, &names[0], &names[2]);
	ASSERT(1 == deleteFromTree(&tree, &names[2]));
	it = getChildren(tree, &names[0]);
	ASSERT(&names[1] == getNextChildData(&it));
	ASSERT(NULL == getNextChildData(&it));
}

int areNodesEqualAccount(void* first, void* second){
	return ((Account*)first)->accNo == ((Account*)second)->accNo;
}

void test_deletes_nodes_from_different_level(){
	Tree tree = createTree(areNodesEqualAccount);
	Iterator it;
	Account accounts[7] = {{1,10},{2,12},{3,30},{4,45},{5,50},{6,60},{7,70}};
	insertInTree(&tree, NULL, &accounts[0]);
	insertInTree(&tree, &accounts[0], &accounts[1]);
	insertInTree(&tree, &accounts[0], &accounts[2]);
	insertInTree(&tree, &accounts[0], &accounts[3]);
	insertInTree(&tree, &accounts[1], &accounts[4]);
	ASSERT(1 == deleteFromTree(&tree, &accounts[2]));
	it = getChildren(tree, &accounts[0]);
	ASSERT(&accounts[1] == getNextChildData(&it));
	ASSERT(&accounts[3] == getNextChildData(&it));
	ASSERT(NULL == getNextChildData(&it));
}

