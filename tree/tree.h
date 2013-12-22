#include "./include/dl_list.h"
typedef int Comparator(void* nodeData, void* parentData);


typedef struct{
	void* root;
	Comparator *areEqual;
}Tree;

Tree createTree(Comparator* areNodesEqual);
int insertInTree(Tree* ptree, void* parentData, void* dataToInsert);
Iterator getChildren(Tree tree, void* parentData);