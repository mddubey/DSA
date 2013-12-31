#include "BSTree.h"
#include <stdlib.h>
#include "testUtils.h"

//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

int areIntegerNodesEqual(void* first, void* second){
	return *(int*)first == *(int*)second;
}

void test_inserts_first_data_as_root_of_the_tree(){
	BS_Tree tree = createBSTree(areIntegerNodesEqual);
	int number = 15;
	ASSERT(insertInBSTree(&tree, NULL, &number));
	ASSERT(&number == getRootData(tree));
}
