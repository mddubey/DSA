#include "tree.h"
#include "./include/dList.h"

typedef struct Tree_Node{
	struct Tree_Node* parent;
	DoubleList child;
	void* data;
}Tree_Node;

Tree_Node* getChildByIndex(Tree_Node *tNode, int index);
Tree_Node* checkEachNodes(DoubleList* list, Comparator* areEqual,
		 void* parentData);
Tree_Node* getTreeNode(Tree tree, void *parentData);
