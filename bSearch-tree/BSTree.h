typedef int CompareInTree(void* first, void* second);
typedef struct{
	void* root;
	CompareInTree* comp;
}BS_Tree;

void* getRootData(BS_Tree tree);
BS_Tree createBSTree(CompareInTree* comp);
int insertInBSTree(BS_Tree* ptree, void* parentData, void* dataToInsert);