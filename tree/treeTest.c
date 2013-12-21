#include "tree.h"
#include <stdlib.h>
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

int areNodesEqual(void* nodeData, void* parentData){
	return (*(int*)nodeData == *(int*)parentData);
}

void test_inserts_a_root_node_into_tree(){
	Tree tree = createTree(areNodesEqual);
	int number = 12;
	DoubleList list = create();
	ASSERT(insertInTree(&tree, NULL, &number));
	getChildren(tree, &number, &list);
	ASSERT(NULL == list.head);
}
