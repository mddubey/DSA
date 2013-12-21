#include "tree.h"
#include <stdlib.h>

typedef struct Tree_Node{
	struct Tree_Node* parent;
	DoubleList* child;
	void* data;
}Tree_Node;

Tree createTree(Comparator *areNodesEqual){
	Tree tree = {NULL,areNodesEqual};
	return tree;
};

Tree_Node* createTreeNode(Tree_Node* parent, Tree_Node* child, void* data){
	Tree_Node* pTNode = malloc(sizeof(Tree_Node));
	pTNode->child->head = child;
	pTNode->parent = parent;
	pTNode->data = data;
	return pTNode;
};

int insertRoot(Tree *ptree, void *dataToInsert){
	Tree_Node* root = ptree->root;
	if(root == NULL){
		root = malloc(sizeof(Tree_Node));
		root->child->head = NULL;
		root->parent = NULL;
		root->data = dataToInsert;
	}
	ptree->root = root;
	return 1;
};

int insertInTree(Tree* ptree, void *parentData, void *dataToInsert){
	if(NULL == parentData)
		return insertRoot(ptree, dataToInsert);
	return 1;
};

void getChildren(Tree tree, void *data, DoubleList *list){
	Tree_Node* root = tree.root;
	list = (root->child);
}

Tree_Node* searchParentNode(Tree tree, void *parentData){
	if(NULL == parentData)
		return NULL;
	return NULL;
}