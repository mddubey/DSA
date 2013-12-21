typedef struct type{
	void *data;
	struct type *next,*previous;
} Node;

typedef struct{
	int length;
	void *head,*tail;
} DoubleList;

typedef struct {
	Node* currentNode;
	DoubleList* list;
} ListIterator;

void* next(ListIterator* it);

int hasNext(ListIterator* it);

typedef int (*compare)(void *elementToCompare,void *element);

DoubleList create();
int insert(DoubleList* dList,int index,void *element);
int delete_node(DoubleList* dList,int index);
void dispose(DoubleList dList);
void* getNodeData(DoubleList list, int index);
void sort(DoubleList dList, compare cmpFunc);
ListIterator iterator(DoubleList* dList);