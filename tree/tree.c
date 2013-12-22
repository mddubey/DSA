#include "tree.h"
#include <stdlib.h>

typedef struct Tree_Node{
	struct Tree_Node* parent;
	DoubleList child;
	void* data;
}Tree_Node;
Tree_Node* getChildByIndex(Tree_Node tNode, int index);
Tree_Node* checkEachNodes(Tree_Node* tNode, Comparator* areEqual,
		 void* parentData);
Tree_Node* searchParentNode(Tree tree, void *parentData);


Tree createTree(Comparator *areNodesEqual){
	Tree tree = {NULL,areNodesEqual};
	return tree;
};

Tree_Node* createTreeNode(Tree_Node* parent, void* data){
	Tree_Node* pTNode = malloc(sizeof(Tree_Node));
	pTNode->child = create();
	pTNode->parent = parent;
	pTNode->data = data;
	return pTNode;
};

int insertInTree(Tree* ptree, void *parentData, void *dataToInsert){
	Tree_Node* parentNode;
	if(NULL == parentData){
		ptree->root = createTreeNode(NULL, dataToInsert);
		return 1;
	}
	parentNode = searchParentNode(*ptree, parentData);
	return insert(&parentNode->child, parentNode->child.length,
	 dataToInsert);
};

Iterator getChildren(Tree tree, void *parentData){
	Tree_Node* parentNode = searchParentNode(tree, parentData);
	Iterator it = getIterator(&parentNode->child);
	return it;
}

Tree_Node* getChildByIndex(Tree_Node tNode, int index){
	int i;
	Iterator it = getIterator(&tNode.child);
	Tree_Node* child;
	if(tNode.child.length == index)
		return NULL;
	for(i = 0; i < index; i++){
		child = it.next(&it);
	}
	return child;
}

Tree_Node* checkEachNodes(Tree_Node* tNode, Comparator* areEqual, void* parentData){
	int totalChildren = tNode->child.length;
	int i;
	void* data = tNode->data;
	Tree_Node *child;
	int result = areEqual(data, parentData);
	if(result)
		return tNode;
	if(totalChildren > 0){
		for(i = 0;i < totalChildren;i++){
			child = getChildByIndex(*tNode, i);
			return checkEachNodes(child, areEqual, parentData);
		}
	}
	return NULL;
};

Tree_Node* searchParentNode(Tree tree, void *parentData){
	Tree_Node* root = tree.root;
	if(NULL == parentData)
		return NULL;
	return checkEachNodes(root, tree.areEqual, parentData);
}