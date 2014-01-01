typedef int CompareInTree(void* first, void* second);
typedef struct{
	void* root;
	CompareInTree* comp;
}BS_Tree;

typedef struct {
	void* left;
	void* right;
}Children_data;

void* getRootData(BS_Tree tree);
BS_Tree createBSTree(CompareInTree* comp);
int deleteFromBSTree(BS_Tree* tree, void* data);
int searchInBSTree(BS_Tree tree, void* nodeData);
int insertInBSTree(BS_Tree* ptree, void* dataToInsert);
Children_data getChildrenData(BS_Tree tree, void* parentData);