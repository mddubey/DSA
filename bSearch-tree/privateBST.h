#include "BSTree.h"
typedef struct BST_Node{
	void* value;
	struct BST_Node* leftChild;
	struct BST_Node* rightChild;
}BST_Node;

BST_Node* createBTNode(void* dataToInsert);
BST_Node* getNode(BS_Tree tree, void* data);
BST_Node* checkEachNode(BST_Node *node, void* data, CompareInTree* comp);
int insertAsChild(BST_Node* node, void* dataToInsert, CompareInTree* comp);
int insertionInLeft(BST_Node* node, void* dataToInsert, CompareInTree* comp);
int insertionInRight(BST_Node* node, void* dataToInsert, CompareInTree* comp);