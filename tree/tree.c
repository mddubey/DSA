#include <stdlib.h>
#include "privateTree.h"

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
	parentNode = getTreeNode(*ptree, parentData);
	if(!parentNode) return 0;
	nodeToInsert = createTreeNode(parentNode, dataToInsert);
	return insert(&(parentNode->child), parentNode->child.length,
	 nodeToInsert);
};

Iterator getChildren(Tree tree, void *parentData){
	Tree_Node* parentNode = getTreeNode(tree, parentData);
	Iterator it;
	if(!parentNode) {
		it = getIterator(NULL);
		return it;
	}
	it = getIterator(&parentNode->child);
	return it;
}

void* getNextChildData(Iterator* it){
	Tree_Node* ptNode = it->next(it);
	if(NULL == ptNode) return NULL;
	return ptNode->data;
}

Tree_Node* checkEachNodes(DoubleList *list, Comparator* areEqual, void* parentData){
	Iterator it = getIterator(list);
	Tree_Node *ptNode;
	int result;
	while(it.hasNext(&it)){
		ptNode = (Tree_Node*)it.next(&it);
		result = areEqual(ptNode->data,parentData);
		if(result)
			return ptNode;
		if(ptNode->child.length)
			checkEachNodes(&ptNode->child, areEqual, parentData);
	}
	return NULL;
};

Tree_Node* getTreeNode(Tree tree, void *parentData){
	Tree_Node* root = tree.root;
	if(NULL == parentData || NULL == root)
		return NULL;
	if(tree.areEqual(root->data,parentData)) return root;
	return checkEachNodes(&root->child, tree.areEqual, parentData);
}

int getChildIndex(DoubleList list,void* childData, Comparator* areEqual){
	Iterator it = getIterator(&list);
	Tree_Node *ptNode;
	int result;
	while(it.hasNext(&it)){
		ptNode = it.next(&it);
		result = areEqual(ptNode->data, childData);
		if(result) return it.position - 1;
	}
	return -1;
}

int hasChildren(Tree_Node tNode){
	return tNode.child.head != NULL;
}

int deleteFromTree(Tree *ptree, void *data){
	Tree_Node *ptNode = getTreeNode(*ptree, data);
	Tree_Node *parentNode;
	int index;
	if(!ptNode) return 0;
	if(hasChildren(*ptNode)) return 0;
	dispose(ptNode->child);
	parentNode = ptNode->parent;
	if(!parentNode){
		free(ptNode);
		return 1;		
	}
	index = getChildIndex(parentNode->child, ptNode->data, ptree->areEqual);
	return delete_node(&parentNode->child, index);
}