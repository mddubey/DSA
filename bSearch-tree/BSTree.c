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
	if(compResult > 0)
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

BST_Node* checkEachNode(BST_Node *node, void* data, CompareInTree* comp){
	int compResult;
	if(!node) return node;
	compResult = comp(node->value, data);
	if(!compResult) return node;
	if(compResult > 0)
		return checkEachNode(node->leftChild, data, comp);
	return checkEachNode(node->rightChild, data, comp);
}

BST_Node* getNode(BS_Tree tree, void* data){
	BST_Node *root = (BST_Node*)(tree.root);
	if(!root) return root;
	return checkEachNode(root, data, tree.comp);
}

Children_data getChildrenData(BS_Tree tree, void *parentData){
	Children_data result = {NULL,NULL};
	BST_Node* ptNode = getNode(tree, parentData);
	if(!ptNode) return result;
	if(ptNode->leftChild)
		result.left = ptNode->leftChild->value;
	if(ptNode->rightChild)
		result.right = ptNode->rightChild->value;
	return result;
}

int searchInBSTree(BS_Tree tree, void *nodeData){
	return NULL != getNode(tree, nodeData);
}

int deleteFromBSTree(BS_Tree *tree, void *data){
	BST_Node* nodeToDelete = getNode(*tree, data);
	BST_Node* temp;
	if(!nodeToDelete) return 0;
	if(!nodeToDelete->leftChild && !nodeToDelete->rightChild){	//This is a leaf node
		temp = nodeToDelete;
		nodeToDelete = nodeToDelete->leftChild;	//still a problem
		free(temp);
		return 1;
	}
	if(!nodeToDelete->rightChild){		// delete when left sub-tree is present
		temp = nodeToDelete;
		nodeToDelete = nodeToDelete->leftChild;
		free(temp);
		return 1;
	}
	if(!nodeToDelete->leftChild){		// delete when right sub-tree is present
		temp = nodeToDelete;
		nodeToDelete = nodeToDelete->rightChild;
		free(temp);
		return 1;
	}

	return 0;
}