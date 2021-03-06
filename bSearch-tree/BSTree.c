#include <stdlib.h>
#include "privateBST.h"
#include "include/dList.h"

BST_Node* createBTNode(void* dataToInsert, BST_Node* node){
	BST_Node* ptNode = malloc(sizeof(BST_Node));
	ptNode->leftChild = ptNode->rightChild = NULL;
	ptNode->value = dataToInsert;
	ptNode->parent = node;
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
		node->leftChild = createBTNode(dataToInsert, node);
		return 1;
	}
	return insertAsChild(node->leftChild, dataToInsert, comp);
}

int insertionInRight(BST_Node* node, void* dataToInsert, CompareInTree* comp){
	if(!node->rightChild){
		node->rightChild = createBTNode(dataToInsert, node);
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
		ptree->root = createBTNode(dataToInsert, NULL);
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

void updateParent(BST_Node* nodeToDelete, BST_Node* newNode){
	BST_Node* parent = nodeToDelete->parent;
	if(parent->leftChild == nodeToDelete)
		parent->leftChild = newNode;
	else
		parent->rightChild = newNode;
}

BST_Node* getMaxInLeftSubTree(BST_Node* node){
	BST_Node* temp = node;
	while(temp->leftChild)
		temp = temp->leftChild;
	return temp;
}

int deleteLeaf(BST_Node* nodeToDelete){
	if(!nodeToDelete->parent){			//root node
		free(nodeToDelete);
		return 1;
	}									
	updateParent(nodeToDelete, NULL);
	free(nodeToDelete);
	return 1;
}

int deleteWhenOneChild(BST_Node* nodeToDelete, BST_Node* child){
	BST_Node* temp;
	if(!nodeToDelete->parent){
		temp = nodeToDelete;
		nodeToDelete = child;
		free(temp);
	}
	else{
		updateParent(nodeToDelete, child);
		free(nodeToDelete);
	}
	return 1;
}

int deleteNode(BST_Node* nodeToDelete){
	BST_Node *temp,*max_node;
	if(!nodeToDelete->leftChild && !nodeToDelete->rightChild)	//This is a leaf node
		return deleteLeaf(nodeToDelete);
	if(!nodeToDelete->rightChild)		// delete when left sub-tree is present
		return deleteWhenOneChild(nodeToDelete, nodeToDelete->leftChild);
	if(!nodeToDelete->leftChild)		// delete when right sub-tree is present
		return deleteWhenOneChild(nodeToDelete, nodeToDelete->rightChild);
	// delete when both child present
	max_node = getMaxInLeftSubTree(nodeToDelete);
	nodeToDelete->value = max_node->value;
	return deleteNode(max_node);
}

int deleteFromBSTree(BS_Tree *tree, void *data){
	BST_Node* nodeToDelete = getNode(*tree, data);
	if(!nodeToDelete) return 0;
	return deleteNode(nodeToDelete);
}

void disposeEachNode(BST_Node* node){
	if(node != NULL){
		disposeEachNode(node->leftChild);
		disposeEachNode(node->rightChild);
		free(node);
	}
}

void disposeBSTree(BS_Tree *tree){
	if(!tree) return;
	disposeEachNode(tree->root);
}

void getAllNodeData(BST_Node* root, DoubleList* list){
	if(root == NULL)
		return;
	getAllNodeData(root->leftChild, list);
	insert(list, list->length, root->value);
	getAllNodeData(root->rightChild, list);	
}

void balanceBSTree(BS_Tree* tree){
	BST_Node* node = (BST_Node*)tree->root;
	DoubleList* list = create();
	Iterator it;
	getAllNodeData(node, list);
	it = getIterator(list);
	while(it.hasNext(&it)){
		deleteFromBSTree(tree, it.next(&it));
	}
	tree->root = NULL;
}