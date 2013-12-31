#include "privateBST.h"
#include <stdlib.h>

BST_Node* createBTNode(void* dataToInsert){
	BST_Node* ptNode = malloc(sizeof(BST_Node));
	ptNode->leftChild = ptNode->rightChild = NULL;
	ptNode->value = dataToInsert;
	return ptNode;
}

BS_Tree createBSTree(CompareInTree *comp){
	BS_Tree tree = {NULL, comp};
	return tree;
}

void* getRootData(BS_Tree tree){
	BST_Node *ptNode = tree.root;
	return ptNode->value;
}

int insertionInLeft(BST_Node* node, void* dataToInsert, CompareInTree* comp){
	if(!node->leftChild){
		node->leftChild = createBTNode(dataToInsert);
		return 1;
	}
	return insertAsChild(node->leftChild, dataToInsert, comp);
}

int insertionInRight(BST_Node* node, void* dataToInsert, CompareInTree* comp){
	if(!node->rightChild){
		node->rightChild = createBTNode(dataToInsert);
		return 1;
	}
	return insertAsChild(node->rightChild, dataToInsert, comp);
}

int insertAsChild(BST_Node* node, void* dataToInsert, CompareInTree* comp){
	int compResult = comp(node->value, dataToInsert);
	if(compResult == 0)
		return 0;
	if(compResult > 1)
		return insertionInLeft(node, dataToInsert, comp);	
	return insertionInRight(node, dataToInsert, comp);
}

int insertInBSTree(BS_Tree *ptree, void *dataToInsert){
	if(!ptree->root){
		ptree->root = createBTNode(dataToInsert);
		return 1;
	}
	return insertAsChild(ptree->root, dataToInsert, ptree->comp);
}