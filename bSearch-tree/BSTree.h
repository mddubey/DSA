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
Children_data getChildrenData(BS_Tree tree, void* parentData);
BS_Tree createBSTree(CompareInTree* comp);
int insertInBSTree(BS_Tree* ptree, void* dataToInsert);