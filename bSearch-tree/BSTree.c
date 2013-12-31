#include "BSTree.h"
#include <stdlib.h>

typedef struct BST_Node{
	void* value;
	struct BST_Node* leftChild;
	struct BST_Node* rightChild;
}BST_Node;

BS_Tree createBSTree(CompareInTree *comp){
	BS_Tree tree = {NULL, comp};
	return tree;
}

BST_Node* createBTNode(BST_Node* parent, void* dataToInsert){
	BST_Node* ptNode = malloc(sizeof(BST_Node));
	ptNode->leftChild = ptNode->rightChild = NULL;
	ptNode->value = dataToInsert;
	return ptNode;
}

void* getRootData(BS_Tree tree){
	BST_Node *ptNode = tree.root;
	return ptNode->value;
}

int insertInBSTree(BS_Tree *ptree, void *parentData, void *dataToInsert){
	if(!ptree->root){
		ptree->root = createBTNode(NULL, dataToInsert);
	}
	return 1;
}

