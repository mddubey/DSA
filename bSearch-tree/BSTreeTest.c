#include "BSTree.h"
#include <stdlib.h>
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

int compareInetgerNodes(void* first, void* second){
	return *(int*)first - *(int*)second;
}

void test_inserts_first_data_as_root_of_the_tree(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int number = 15;
	Children_data result;
	ASSERT(insertInBSTree(&tree, &number));
	ASSERT(&number == getRootData(tree));
	result = getChildrenData(tree, &number);
	ASSERT(NULL == result.left);
	ASSERT(NULL == result.right);
}

void test_inserts_children_of_root_data(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int number = 15;
	int num2 = 12;
	Children_data result;
	ASSERT(insertInBSTree(&tree, &number));
	ASSERT(insertInBSTree(&tree, &num2));
	ASSERT(&number == getRootData(tree));
	result = getChildrenData(tree, &number);
	ASSERT(&num2 == result.left);
	ASSERT(NULL == result.right);	
}

void test_insertion_failed_when_data_is_already_present(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int num = 12;
	Children_data result;
	ASSERT(insertInBSTree(&tree, &num));
	ASSERT(0 == insertInBSTree(&tree, &num));
	result = getChildrenData(tree, &num);
	ASSERT(NULL == result.left);
	ASSERT(NULL == result.right);
}

void test_gives_the_children_of_the_node_which_data_is_given(){
	BS_Tree tree = createBSTree(compareInetgerNodes);
	int i, nums[5] = {9,10,4,8,2};
	Children_data result;
	for(i = 0;i<5;i++){
		ASSERT(insertInBSTree(&tree, &nums[i]));
	}
	result = getChildrenData(tree, &nums[2]);
	ASSERT(&nums[4] == result.left);
	ASSERT(&nums[3] == result.right);
}

void test_inserts_data_at_defferent_level(){
    BS_Tree tree = createBSTree(compareInetgerNodes);
    int number[8] = {22,24,20,6,30,40,50,12};
    int i;
    for(i = 0;i<8;i++){
        ASSERT(insertInBSTree(&tree, &number[i]));
    }
}