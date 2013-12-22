#include "tree.h"
#include <stdlib.h>
#include "testUtils.h"
#include "../iterator.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

int areNodesEqual(void* nodeData, void* parentData){
	return (*(int*)nodeData == *(int*)parentData);
}

void test_inserts_a_root_node_into_tree(){
	Tree tree = createTree(areNodesEqual);
	int number = 12;
	Iterator it;
	DoubleList list = create();
	ASSERT(insertInTree(&tree, NULL, &number));
	it = getChildren(tree, &number);
	ASSERT(NULL == it.next(&it));
}

void test_inserts_a_child_of_root_into_tree(){
	Tree tree = createTree(areNodesEqual);
	int nums[2] = {12,25};
	Iterator it;
	DoubleList list = create();
	ASSERT(insertInTree(&tree, NULL, &nums[0]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[1]));
	it = getChildren(tree, &nums[0]);
	ASSERT(25 == *(int*)it.next(&it));
}

void test_inserts_two_children_of_root_into_tree(){
	Tree tree = createTree(areNodesEqual);
	int nums[3] = {12,25,14};
	Iterator it;
	DoubleList list = create();
	ASSERT(insertInTree(&tree, NULL, &nums[0]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[1]));
	ASSERT(insertInTree(&tree, &nums[0], &nums[2]));
	it = getChildren(tree, &nums[0]);
	ASSERT(25 == *(int*)it.next(&it));
	ASSERT(14 == *(int*)it.next(&it));
}

