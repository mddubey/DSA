#include "tree.h"
#include <stdlib.h>
#include "./include/dList.h"

typedef struct Tree_Node{
	struct Tree_Node* parent;
	DoubleList child;
	void* data;
}Tree_Node;

Tree_Node* getChildByIndex(Tree_Node *tNode, int index);
Tree_Node* checkEachNodes(DoubleList* list, Comparator* areEqual,
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
	Tree_Node *parentNode, *nodeToInsert;
	if(NULL == parentData){
		ptree->root = createTreeNode(NULL, dataToInsert);
		return 1;
	}
	parentNode = searchParentNode(*ptree, parentData);
	if(!parentNode) return 0;
	nodeToInsert = createTreeNode(parentNode, dataToInsert);
	return insert(&(parentNode->child), parentNode->child.length,
	 nodeToInsert);
};

Iterator getChildren(Tree tree, void *parentData){
	Tree_Node* parentNode = searchParentNode(tree, parentData);
	Iterator it = getIterator(&parentNode->child);
	return it;
}

void* getNextChildData(Iterator* it){
	Tree_Node* tNode = it->next(it);
	if(NULL == tNode) return NULL;
	return tNode->data;
}

Tree_Node* checkEachNodes(DoubleList *list, Comparator* areEqual, void* parentData){
	Iterator it = getIterator(list);
	Tree_Node *tNode;
	int result;
	while(it.hasNext(&it)){
		tNode = (Tree_Node*)it.next(&it);
		result = areEqual(tNode->data,parentData);
		if(result)
			return tNode;
		if(tNode->child.length)
			checkEachNodes(&tNode->child, areEqual, parentData);
	}
	return NULL;
};

Tree_Node* searchParentNode(Tree tree, void *parentData){
	Tree_Node* root = tree.root;
	if(NULL == parentData)
		return NULL;
	if(tree.areEqual(root->data,parentData)) return root;
	return checkEachNodes(&root->child, tree.areEqual, parentData);
}