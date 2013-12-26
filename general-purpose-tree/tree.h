#include "../iterator.h"
typedef int Comparator(void* nodeData, void* parentData);


typedef struct{
	void* root;
	Comparator *areEqual;
}Tree;

Tree createTree(Comparator* areNodesEqual);
int insertInTree(Tree* ptree, void* parentData, void* dataToInsert);
int deleteFromTree(Tree* ptree, void* data);
int searchInTree(Tree tree, void *data);
void disposeTree(Tree* tree);
void* getRootData(Tree tree);
Iterator getChildren(Tree tree, void* parentData);