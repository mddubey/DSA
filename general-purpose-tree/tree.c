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

void* getNextChildData(Iterator* it){
	Tree_Node *node;
    Iterator treeIterator = getIterator(it->list);
    treeIterator.position = it->position;
    node = treeIterator.next(&treeIterator);
    if(!node) return node;
    it->position++;
    return node->data;
}

Iterator getChildren(Tree tree, void *parentData){
	Tree_Node* parentNode = getTreeNode(tree, parentData);
	Iterator it;
	if(!parentNode) {
		it = getIterator(NULL);
		return it;
	}
	it = getIterator(&parentNode->child);
	it.next = &getNextChildData;
	return it;
}

void collectChildren(Tree_Node* ptNode, DoubleList *list){
	Iterator it_child;
	it_child = getIterator(&ptNode->child);
	while(it_child.hasNext(&it_child)){
		insert(list, list->length, it_child.next(&it_child));
	}
}

Tree_Node* performNext(DoubleList* list, Comparator* areEqual, void* nodeData){
	if(list->length)
		return checkEachNodes(list, areEqual, nodeData);
	dispose(list);
	return NULL;
}

Tree_Node* checkEachNodes(DoubleList *list, Comparator* areEqual, void* nodeData){
	Iterator it = getIterator(list);
	DoubleList tempList = create();
	Tree_Node *ptNode;
	while(it.hasNext(&it)){
		ptNode = (Tree_Node*)it.next(&it);
		if(areEqual(ptNode->data,nodeData)){
			dispose(&tempList);
			return ptNode;
		}
		collectChildren(ptNode, &tempList);
	}
	return performNext(&tempList, areEqual, nodeData);
};

Tree_Node* getTreeNode(Tree tree, void *nodeData){
	Tree_Node* root = tree.root;
	if(NULL == nodeData || NULL == root)
		return NULL;
	if(tree.areEqual(root->data, nodeData)) return root;
	return checkEachNodes(&root->child, tree.areEqual, nodeData);
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
	dispose(&ptNode->child);
	parentNode = ptNode->parent;
	if(!parentNode){
		free(ptNode);
		return 1;		
	}
	index = getChildIndex(parentNode->child, ptNode->data, ptree->areEqual);
	return delete_node(&parentNode->child, index);
}

int searchInTree(Tree tree, void *data){
	return getTreeNode(tree, data)!=NULL;
}

void* getRootData(Tree tree){
	Tree_Node root = *(Tree_Node*)tree.root;
	return root.data;
}

void freeNode(Tree_Node* ptNode){
	Iterator it = getIterator(&ptNode->child);
	while(it.hasNext(&it)){
		ptNode = it.next(&it);
		printf("%d\n", *(int*)ptNode->data);
		freeNode(ptNode);
	}
	dispose(&ptNode->child);
	ptNode->parent = NULL;
	free(ptNode);// This is the line which causing problem
}

void disposeTree(Tree* tree){
	Tree_Node* root = tree->root;
	freeNode(root);
}